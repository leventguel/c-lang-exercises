#include <stdio.h>
#include <stdlib.h>

int main(void)
{

  /* int d[10];  d is a pointer to 10 ints, indexes 0-9, but is statically declared */

  int *d = malloc(10 * sizeof *d); /* reserve memory for an array of 10 ints dynamically */
  
  printf("sizeof d: %lu\n", (sizeof d) / (sizeof d[0]));
  printf("sizeof *d: %lu\n", (sizeof d) / (sizeof *d));
  printf("sizeof *d: %lu\n", (sizeof *d) / (sizeof d[0]));
  printf("sizeof *d: %lu\n", (sizeof *d) / (sizeof d));
  printf("sizeof ...: %lu\n", (sizeof d[0]) / (sizeof *d));
  printf("sizeof ...: %lu\n", (sizeof d[0]) / (sizeof d));

  d[13] = 5; /* assign last element, static style */

  printf("a: %d\n", d[13]);

  *(d+3) = 4;

  printf("a: %d\n", d[3]);

  printf("sizeof d: %lu\n", (sizeof d) / (sizeof d[0]));
  printf("sizeof *d: %lu\n", (sizeof d) / (sizeof *d));
  printf("sizeof *d: %lu\n", (sizeof *d) / (sizeof d[0]));
  printf("sizeof *d: %lu\n", (sizeof *d) / (sizeof d));
  printf("sizeof ...: %lu\n", (sizeof d[0]) / (sizeof *d));
  printf("sizeof ...: %lu\n", (sizeof d[0]) / (sizeof d));



  d[3] = 8;
  printf("a: %d\n", d[3]);

  printf("sizeof d: %lu\n", (sizeof d) / (sizeof d[0]));
  printf("sizeof *d: %lu\n", (sizeof d) / (sizeof *d));
  printf("sizeof *d: %lu\n", (sizeof *d) / (sizeof d[0]));
  printf("sizeof *d: %lu\n", (sizeof *d) / (sizeof d));
  printf("sizeof ...: %lu\n", (sizeof d[0]) / (sizeof *d));
  printf("sizeof ...: %lu\n", (sizeof d[0]) / (sizeof d));


  printf("sizeof d: %lu \n", sizeof d);
  printf("sizeof d[0] %lu \n", sizeof d[0]);
  printf("sizeof *d %lu \n", sizeof *d);

  return 0;

}
