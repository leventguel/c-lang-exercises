#include <stdio.h>
#include <stdlib.h>

double *x; /* x is of type pointer to double ! */

int main(void)
{
  x = malloc(sizeof *x); /* we reserve space for as much as that pointers size and let the pointer point to that area */
  if (x) { /* if the pointer points to anything, i.e. is not a NULL pointer !*/
    *x = 4; /* we write 4 into the area x is pointing to  */
    printf("%f\n", *x); /* we print the content of the area x is pointing to */
    free(x); /* we destroy the pointer x, not the area x was pointing to, thereby releasing that area !*/

    /* memory area handling is OS stuff and even the OS does not destroy anything, what is meant is the area is left as is after some operation or it is
     * written 0 bytes into it, thereby nulled (erased), so bit contents of areas should be explicitly nulled at least once at program start, but we
     * don't do it here, nor is that strictly required (but would be a lil'bit more secure !) */

  }
  return 0;
}
