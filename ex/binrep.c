#include <stdio.h> /* only needed for the printf() in main(). */
#include <string.h>
#include <stdlib.h>

/* Create a string of binary digits based on the input value.
   Input:
       val:  value to convert.
       buff: buffer to write to must be >= sz+1 chars.
       sz:   size of buffer.
   Returns address of string or NULL if not enough space provided.
*/
static char *binrep (unsigned int val, char *buff, int sz) {
  char *pbuff = buff;

  /* Must be able to store one character at least. */
  if (sz < 1) return NULL;

  /* Special case for zero to ensure some output. */
  if (val == 0) {
    *pbuff++ = '0';
    *pbuff = '\0';
    return buff;
  }

  /* Work from the end of the buffer back. */
  pbuff += sz;
  *pbuff-- = '\0';

  /* For each bit (going backwards) store character. */
  while (val != 0) {
    if (sz-- == 0) return NULL;
    *pbuff-- = ((val & 1) == 1) ? '1' : '0';

    /* Get next bit. */
    val >>= 1;
  }
  return pbuff+1;
}

#define SZ 64
int main(int argc, char *argv[]) {
  int i;
  int n;
  char buff[SZ+1];

  /* Process all arguments, outputting their binary. */
  for (i = 1; i < argc; i++) {
    n = atoi (argv[i]);
    printf("[%3d] %9d -> %s (from '%s')\n", i, n,
	   binrep(n,buff,SZ), argv[i]);
  }

  return 0;
}
