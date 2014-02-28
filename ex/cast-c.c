#include <stdio.h>
#include <stdlib.h>


int main(void)
{
  double *x = (double*) malloc(sizeof *x);
  if (x) {
    *x = 4;
    printf("%f\n", *x);

    printf("sizeof x: %d\n", (int) sizeof x);
    printf("sizeof *x: %ld\n", sizeof *x);

    printf("sizeof double: %d\n", (int) sizeof(double));
    printf("sizeof void: %ld\n", sizeof(void));

    printf("sizeof double*: %ld\n", sizeof(double*));
    printf("sizeof void*: %ld\n", sizeof(void*));

    free(x);
  }
  return 0;
}
