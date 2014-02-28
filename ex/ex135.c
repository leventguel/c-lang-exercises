#include <stdio.h>

int main(void)
{ 
  char *p = "12345"; 
  unsigned n = 0; 
  while (*p) 
    { 
      n = n*10 + (*p++ - '0'); /* 0*10+'1'-'0', 1*10+'2'-'0', 12*10+'3'-'0' */
      printf("%u", n);
    } 

  return 0;
}
