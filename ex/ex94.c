#include <stdio.h>

int squ(in) /* function to get the value of in squared */
int in;
{
  int square;
  square = in * in;
  return(square); /* This sets squ() = square */
}


int main(void) /* This is the main program*/
{
  int x,y;
  for(x = 0;x <= 7;x++) 
    {
      y = squ(x); /* go get the value of x*x */
      printf( "\tThe square of %d is %d \t\t The value of %d is %d \n", x,y, x,squ(x) );
    }
  return 0;
}
