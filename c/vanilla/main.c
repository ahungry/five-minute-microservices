// Copyright (C) 2015,2016,2018 Matthew Carter <m@ahungry.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#ifdef _WIN32
// For windows
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

// Taken from posix/wait.h
#define WNOHANG          0x00000001

// Taken from unistd.h
#define SHUT_RDWR 0x02

#else
// For good systems
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <unistd.h>
#endif

#include <signal.h>
#include "config.h"
#include <pthread.h>
#include <stdint.h>

#define MAX_ENQUEUED 20
#define BUF_LEN 512
#define MAX_HTML_FILE_SIZE 8192
#define PORT_STR "12003"

static volatile int keep_running = 1;

int server_sock;

void
int_handler (int dummy)
{
  keep_running = 0;
  printf ("Shutting down, freeing socket.\n");

  if (server_sock)
    {
#ifdef _WIN32
  closesocket (server_sock);
  WSACleanup ();
  exit (EXIT_SUCCESS);
#else
  close (server_sock);
  exit (EXIT_SUCCESS);
#endif
    }
}

/**
 * Send out the successful HTTP header
 *
 * @param int csock The client socket to write to
 * @return void
 */
void http_send_header_success (int csock)
{
  (void) send (csock, "HTTP/1.1 200 OK\n", 16, 0);
  (void) send (csock, "Content-Type: text/html\n", 24, 0);
  (void) send (csock, "Content-Length: 7\n", 18, 0);
  (void) send (csock, "Connection: close\n\n", 19, 0);
}

/* ------------------------------------------------------------ */
/* How to clean up after dead child processes                   */
/* ------------------------------------------------------------ */
// void wait_for_zombie(int s)
#ifdef _WIN32
void wait_for_zombie () {}
#else
void wait_for_zombie()
{
  while(waitpid(-1, NULL, WNOHANG) > 0) ;
}
#endif

/* ------------------------------------------------------------ */
/* Core of implementation of a child process                    */
/* ------------------------------------------------------------ */
void http_send_client_response(int csock)
{
  char buf[130];

  read (csock, buf, 130);

  http_send_header_success (csock);
  (void) send (csock, "\"0.0.1\"", 7, 0);

  // Politely hang up the call (if we do not send the length).
  // If we don't use this, error rate increases.
  shutdown (csock, SHUT_RDWR);
}

// ptr is the csock waiting to be serviced
void *
thread_fn (void *ptr)
{
  intptr_t csock = (intptr_t) ptr;

  http_send_client_response (csock);
  close(csock);

  return NULL;
}

/* ------------------------------------------------------------ */
/* Core of implementation of the parent process                 */
/* ------------------------------------------------------------ */
void take_connections_forever(int ssock)
{
  // https://stackoverflow.com/questions/2876024/linux-is-there-a-read-or-recv-from-socket-with-timeout
#ifdef _WIN32
  // FIXME: For some reason, this doesn't assist with not-pausing on win...
  // WINDOWS
  // DWORD timeout = timeout_in_seconds * 1000;
  DWORD timeout = 500;
  setsockopt (ssock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof timeout);
#else
  // LINUX
  struct timeval tv;
  tv.tv_sec = 0;
  // We need a way to dynamically set this after first received byte in read() call
  tv.tv_usec = 500000; // 500,000 would be half a second, as this is micro seconds
  setsockopt (ssock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
#endif

  while (keep_running)
    {
      struct sockaddr addr;
      socklen_t addr_size = sizeof(addr);
      int csock;
      pthread_t pth;

      /* Block until we take one connection to the server socket */
      csock = accept(ssock, &addr, &addr_size);

      if (csock < 0) continue;

      if (csock == -1) {
        perror("accept");
      } else {
        pthread_create(&pth, NULL, thread_fn, (void*)(intptr_t)csock);
      }
    }
}

#ifdef _WIN32

WSADATA wsaData;

int
make_sock ()
{
  int iResult;

  // Initialize Winsock
  iResult = WSAStartup (MAKEWORD (2,2), &wsaData);

  if (iResult != 0)
    {
      printf ("WSAStartup failed: %d\n", iResult);
      return 1;
    }

  struct addrinfo *result = NULL, *ptr = NULL, hints;

  ZeroMemory (&hints, sizeof (hints));

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE;

  iResult = getaddrinfo (NULL, PORT_STR, &hints, &result);
  if (iResult != 0)
    {
      printf ("getaddrinfo failed: %d\n", iResult);
      WSACleanup ();

      return 1;
    }

  SOCKET ListenSocket = INVALID_SOCKET;
  ListenSocket = socket (result->ai_family, result->ai_socktype,
                         result->ai_protocol);

  if (ListenSocket == INVALID_SOCKET) {
    printf ("Error at socket(): %ld\n", WSAGetLastError ());
    freeaddrinfo (result);
    WSACleanup ();

    return 1;
  }

  // https://linux.die.net/man/3/setsockopt
  int enable = 1;
  setsockopt (ListenSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof (int));

  // Setup the TCP listening socket
  iResult = bind (ListenSocket, result->ai_addr, (int) result->ai_addrlen);

  if (iResult == SOCKET_ERROR)
    {
      printf ("bind failed with error: %d\n", WSAGetLastError ());
      freeaddrinfo (result);
      closesocket (ListenSocket);
      WSACleanup ();

      return 1;
    }

  freeaddrinfo (result);

  if (listen (ListenSocket, SOMAXCONN) == SOCKET_ERROR)
    {
      printf ("Listen failed with error: %ld\n", WSAGetLastError ());
      closesocket (ListenSocket);
      WSACleanup ();

      return 1;
    }

  /* SOCKET ClientSocket; */

  /* ClientSocket = INVALID_SOCKET; */

  /* // TODO: Fix this lame attempt */
  /* // https://docs.microsoft.com/en-us/windows/win32/winsock/accepting-a-connection */
  /* // Accept a client socket */
  /* ClientSocket = accept (ListenSocket, NULL, NULL); */
  /* if (ClientSocket == INVALID_SOCKET) */
  /*   { */
  /*     printf ("accept failed: %d\n", WSAGetLastError()); */
  /*     closesocket (ListenSocket); */
  /*     WSACleanup (); */

  /*     return 1; */
  /*   } */

  return ListenSocket;
}
#else
int
make_sock ()
{
  struct addrinfo hints, *res;
  struct sigaction sa;
  int sock;
  char portno[10];

  // strcpy (portno, argc > 1 ? argv[1] : PORT_STR);
  strcpy (portno, PORT_STR); //

  /* Look up the address to bind to */
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;

  if ( getaddrinfo(NULL, portno, &hints, &res) != 0 ) {
    perror("getaddrinfo");
    exit(EXIT_FAILURE);
  }

  /* Make a socket */
  if ( (sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1 ) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  /* Arrange to clean up child processes (the workers) */
  sa.sa_handler = wait_for_zombie;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if ( sigaction(SIGCHLD, &sa, NULL) == -1 ) {
    perror("sigaction");
    exit(EXIT_FAILURE);
  }

  // https://linux.die.net/man/3/setsockopt
  int enable = 1;
  setsockopt (sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof (int));

  /* Associate the socket with its address */
  if ( bind(sock, res->ai_addr, res->ai_addrlen) != 0 ) {
    perror("bind");
    exit(EXIT_FAILURE);
  }

  freeaddrinfo(res);

  /* State that we've opened a server socket and are listening for connections */
  if ( listen(sock, MAX_ENQUEUED) != 0 ) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  return sock;

  /* /\* Serve the listening socket until killed *\/ */
  /* take_connections_forever(sock); */
  /* return EXIT_SUCCESS; */
}
#endif

/* ------------------------------------------------------------ */
/* The server process's one-off setup code                      */
/* ------------------------------------------------------------ */

int
main(int argc, char *argv[])
{
  signal (SIGINT, int_handler);

  int sock = make_sock ();
  server_sock = sock;

  /* Serve the listening socket until killed */
  take_connections_forever (sock);

  return EXIT_SUCCESS;
}
