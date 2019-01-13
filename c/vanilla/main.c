// Copyright (C) 2015,2016,2018 Matthew Carter <m@ahungry.com>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include "config.h"
#include <pthread.h>
#include <stdint.h>

#define MAX_ENQUEUED 20
#define BUF_LEN 512
#define MAX_HTML_FILE_SIZE 8192
#define PORT_STR "12003"

/**
 * Send out the successful HTTP header
 *
 * @param int csock The client socket to write to
 * @return void
 */
void http_send_header_success (int csock)
{
  (void) write (csock, "HTTP/1.1 200 OK\n", 16);
  (void) write (csock, "Content-Type: text/html\n", 24);
  (void) write (csock, "Content-Length: 7\n", 18);
  (void) write (csock, "Connection: close\n\n", 19);
}

/* ------------------------------------------------------------ */
/* How to clean up after dead child processes                   */
/* ------------------------------------------------------------ */
// void wait_for_zombie(int s)
void wait_for_zombie()
{
  while(waitpid(-1, NULL, WNOHANG) > 0) ;
}

/* ------------------------------------------------------------ */
/* Core of implementation of a child process                    */
/* ------------------------------------------------------------ */
void http_send_client_response(int csock)
{
  char buf[130];

  read (csock, buf, 130);

  http_send_header_success (csock);
  (void) write (csock, "\"0.0.1\"", 7);

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
  for(;;) {
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

/* ------------------------------------------------------------ */
/* The server process's one-off setup code                      */
/* ------------------------------------------------------------ */

int main(int argc, char *argv[])
{
  struct addrinfo hints, *res;
  struct sigaction sa;
  int sock;
  char portno[10];

  strcpy (portno, argc > 1 ? argv[1] : PORT_STR);

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

  /* Serve the listening socket until killed */
  take_connections_forever(sock);
  return EXIT_SUCCESS;
}
