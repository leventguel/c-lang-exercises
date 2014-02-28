#include <stdio.h>

int main(void)
{
  int i;
  int j;
  int k;
  i=3;
  j=5;
  k=9;
  printf("%3$d, %2$d, %1$d \n", i, j, k);
  printf("%2$d, %3$d, %1$d \n", i, j, k);
  printf("%3$d, %1$*2$d, %3$d \n", i, j, k);
  printf("%3$d, %2$*1$d, %3$d \n", i, j, k);
  printf("%3$d, %1$*2$d%3$d, %3$d \n", i, j, k);
  printf("%3$d, %3$*1$d, %3$*2$d \n", i, j, k);
  printf("%3$d, %1$*3$d, %2$*3$d \n", i, j, k);
  printf("%3$d, %3$*2$d, %3$*1$d \n", i, j, k);
  printf("%3$d, %3$*1$d, %3$*2$d \n", i, j, k);
  printf("%3$d, %3$*1$d, %3$*2$d, %3$*3$d \n", i, j, k);
  i=9; j=9; k=9;
  printf("%3$d, %2$d, %1$d \n", i, j, k);
  printf("%2$d, %3$d, %1$d \n", i, j, k);
  printf("%3$d, %1$*2$d, %3$d \n", i, j, k);
  printf("%3$d, %2$*1$d, %3$d \n", i, j, k);
  printf("%3$d, %1$*2$d%3$d, %3$d \n", i, j, k);
  printf("%3$d, %3$*1$d, %3$*2$d \n", i, j, k);
  printf("%3$d, %1$*3$d, %2$*3$d \n", i, j, k);
  printf("%3$d, %3$*2$d, %3$*1$d \n", i, j, k);
  printf("%3$d, %3$*1$d, %3$*2$d \n", i, j, k);
  printf("%3$d, %3$*1$d, %3$*2$d, %3$*3$d \n", i, j, k);
  return 0;
}
