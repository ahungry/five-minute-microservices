// Copyright (C) 2015-2020 Matthew Carter <m@ahungry.com>

// https://docs.microsoft.com/en-us/windows/win32/winsock/initializing-winsock

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
// For windows
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
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

WSADATA wsaData;

void *
thread_fn (void *ptr)
{
  intptr_t csock = (intptr_t) ptr;
  fprintf (stderr, "I am the thread and you called me on %ld!\n", csock);
  printf ("HELLO FROM %ld\n", csock);

  /* http_send_client_response (csock); */
  /* close(csock); */

  return NULL;
}


int main(int argc, char *argv[])
{
  int iResult;

  // BEGIN thread test
  int csock = 5;
  pthread_t pth;
  pthread_create(&pth, NULL, thread_fn, (void*)(intptr_t)csock);
  // END thread test

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

  SOCKET ClientSocket;

  ClientSocket = INVALID_SOCKET;

  // TODO: Fix this lame attempt
  // https://docs.microsoft.com/en-us/windows/win32/winsock/accepting-a-connection
  // Accept a client socket
  ClientSocket = accept (ListenSocket, NULL, NULL);
  if (ClientSocket == INVALID_SOCKET)
    {
      printf ("accept failed: %d\n", WSAGetLastError());
      closesocket (ListenSocket);
      WSACleanup ();

      return 1;
    }

  return 0;
}
