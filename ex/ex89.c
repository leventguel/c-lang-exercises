#include <stdio.h>
#include <typeinfo>

/* The purpose of the file is to introduce additional data types */
int main(void)
{
  int i;
  int a,b,c;
  /* -32768 to 32767 with no decimal point */
  char x,y,z;
  /* 0 to 255 with no decimal point */
  float num,toy,thing;
  /* 10E-38 to 10E+38 with decimal point */
  a = b = c = -27;
  x = y = z = 'A';
  num = toy = thing = 3.6792;
  a = y;
  printf("%d \n", a);
  printf("%c \n", a);
  /* a is now 65 (character A) */
  x = b;
  printf("this is int x: %d \n", x);
  printf("this is char x: %c \n", x);
  /* x will now be a funny number */
  num = b;
  printf("%f \n", num);
  /* num will now be -27.00 */
  a = toy;
  printf("%d \n", a);
  /* a will now be 3 */

  return 0;
}
