#include <stdio.h>
#include <stdlib.h>

int
main (void)
{
  printf ("Content-type: application/json\r\nStatus: 200 OK\r\n\"0.0.1\"\r\n\r\n");

  return 0;
}
