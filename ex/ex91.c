#include <stdio.h>

int main(void)
{

  int a;
  long int b;
  short int c;
  unsigned int d;
  char e;
  float f;
  double g;
  
  a = 1023;
  b = 2222;
  c = 123;
  d = 1234;
  e = 'X';
  f = 3.14159;
  g = 3.1415926535898;
  
  printf("a = %d\n",a);
  printf("a = %o\n",a);
  printf("a = %x\n",a);
  printf("b = %ld\n",b);
  printf("c = %d\n",c);
  printf("d = %u\n",d);
  printf("e = %c\n",e);
  printf("f = %f\n",f);
  printf("g = %f\n",g);
  printf("\n");
  printf("a = %d\n",a);
  printf("a = %7d\n",a);
  printf("a = %-7d\n",a);
  printf("\n");
  printf("f = %f\n",f);
  printf("f = %12f\n",f);
  printf("f = %12.3f\n",f);
  printf("f = %12.5f\n",f);
  printf("f = %-12.5f\n",f);
  
  return 0;
}
