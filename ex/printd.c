#include <stdio.h>
#define PRINTD(var) printf( "Variable " #var "=%d\n", var )
int main(void)
{
  int nTest=10;
  PRINTD(nTest);
  return 0;

} /* main */

