#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
  char buffer[512];
  int nread;
  nread = read(0, buffer, 512);
  printf("\n");
  if (nread == -1)
    write(2, "A read error has occurred\n", 26);
  if ((write(1,buffer,nread)) != nread)
    write(2, "A write error has occurred\n",27);
  printf("\n\n");
  exit(0);
}
