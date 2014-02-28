#include <stdio.h>

#define __STDC_VERSION__  199901L

int main(void)
{

  printf("\n**************"); /* Top of the Box */  

  for(int count = 1; count <= 8; count++)
    {
      printf("\n*             *\n");
    }

  printf("\n**************"); /* Bottom of the Box */

  return 0;
}
