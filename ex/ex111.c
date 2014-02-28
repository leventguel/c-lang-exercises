#include <stdio.h>
void areaperi(int, float *, float *);

void main(void)
{
  int radius ;
  float area, perimeter ;
  printf ( "\nEnter radius of a circle " ) ;
  scanf ( "%d", &radius ) ;
  areaperi ( radius, &area, &perimeter ) ;
  printf ( "Area = %f", area ) ;
  printf ( "\nPerimeter = %f\n", perimeter ) ;
}

void areaperi ( int r, float *a, float *p )
{
  *a = 3.14 * r * r ;
  *p = 2 * 3.14 * r ;
}
