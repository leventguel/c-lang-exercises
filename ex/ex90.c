#include <stdio.h>

#define max(a,b) \
  ({ typeof (a) _a = (a); \
  typeof (b) _b = (b); \
  _a > _b ? _a : _b; })

int main(void)
{
  int a = 3, b = 2;
  
  printf("a is %d, b is %d \n", a, b);
  printf("max of (a, b) is %d \n", max(a, b));
  return 0;
}
