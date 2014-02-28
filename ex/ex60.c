#include <stdio.h>

#define A abcd
#define B 1234
#define C "
#define STRA(A) #A 
#define STRB(B) #B
#define STRC(C) #C
#define conc(A,B,C) (STRC(C) STRA(A) " " STRB(B) STRC(C))

int main(void)
{
  printf("%s\n", conc(A,B,C));
  return 0;
}

#undef A
#undef B
#undef C
