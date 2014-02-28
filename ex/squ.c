#include <stdio.h>

int main()
/* This is the main program*/
{
  int squ(in)
    int in; /* function to get the value of in squared */
  {
    int square;
    square = in * in;
    return(square); /* This sets squ() = square */
  }

  int x,y;
  for(x = 0;x < 7;x++) 
    {
      y = squ(x);
      /* go get the value of x*x  */
      printf("The square of %d is %d\n",x,y);
    }
  
  for (x = 0;x <= 7; ++x)
    {
      printf("The value of %d is %d\n",x,squ(x));
    }

  return 0;
}

