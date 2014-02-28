#include <math.h>
#include <stdio.h>

int main()
{
  float x,y;
  float *z; // z is a pointer;

  y=10.0;
  z=&y; // z is now pointing to y
  x=*z; // x has now the value of y, because *z is the value of 'z which points to y'
  printf("y=%f x=%f\n", y, x);

  // the two steps above with z=&y; x=*z, could have bee merged into x=*&y, for that replace in x=*z z for its assignment which is &y so x=*z gets x=*(z) => x=*(&y) => x=*&y
  
  *z=9.0; // z which is pointing to y gets the value 9.0 assigned

  printf("y=%f x=%f\n", y, x);
  printf("y=%f x=%f\n", *&y, x); // *&y is shorthand for dereference the value at the address of y
  printf("y=%f x=%f\n", *&x, x);
  return 0;
}
