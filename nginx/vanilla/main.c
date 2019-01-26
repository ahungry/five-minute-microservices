#include <stdio.h>
#include <stdlib.h>

int
main (void)
{
  // printf ("Content-type: application/json\r\nStatus: 200 OK\r\n\"0.0.1\"\r\n\r\n");
  printf ("HTTP/1.1 200 OK\n");
  printf ("Content-Type: text/html\n");
  printf ("Content-Length: 7\n");
  printf ("Connection: close\n\n");
  printf ("\"0.0.1\"");

  return 0;
}
