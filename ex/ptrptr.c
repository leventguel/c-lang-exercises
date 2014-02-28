/* ptrptr1.c */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int wert = 10;
  /* ptr ist ein Zeiger auf int wert. */
  int *ptr=&wert;
  /* ptr_ptr ist ein Zeiger auf den Zeiger int *ptr. */
  int **ptr_ptr =&ptr;

  printf("*ptr      : %d\n",*ptr);
  printf("**ptr_ptr : %d\n", **ptr_ptr);

  /* Verändert den Wert, auf den int *ptr zeigt. */
  **ptr_ptr = 100;
  printf("*ptr      : %d\n",*ptr);
  printf("**ptr_ptr : %d\n", **ptr_ptr);

  /* Verändert nochmals den Wert. */
  *ptr = 200;
  printf("*ptr      : %d, Wert: %d\n",*ptr, wert);
  printf("**ptr_ptr : %d\n", **ptr_ptr);
  return EXIT_SUCCESS;
}
