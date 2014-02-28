#include <stdio.h>
#include <stdlib.h>

int main(void)
{

  /* int d[10];  d is a pointer to 10 ints, indexes 0-9, but is statically declared 
   * so can't be used and intermixed together with dynamic arrays */

  int count = 0;
  int i;
  int *d = malloc(10 * sizeof *d); /* reserve memory for an array of 10 ints dynamically, indexes 0-9 */

  if(d == NULL)
    {
      printf("out of memory\n");
      return -1;
	}

  *(d+3) = 5;  

  printf("sizeof d (an int pointer to 10 ints i.e. (int*)) is %lu \n", sizeof d);
  printf("*(d+3) = d[3] is %d = %d \n", *(d+3), d[3]);

  printf("sizeof d[3] (int) is %lu \n", sizeof *(d+3));

  printf("sizeof array d/d[3] (only one element yet set, but array still 10 elems) is %lu\n", (sizeof d) / (sizeof d[3]));
  printf("element count in array is sizeof(d/d[3]) -1 i.e. %lu \n", (sizeof d / sizeof d[3]) -1);

  d[9] = 2;
  printf("*(d+9) is %d \n", *(d+9));

  for(i=0; i <= 9; i++)
    {
      printf("array elements: %d \n", *(d+i));
      count = i;
    }

  printf("element count in array is %lu\n", ((sizeof d / sizeof d[i]) -1) * count+1);
  printf("indexes in array is 0-%lu \n", ((sizeof d / sizeof d[i]) -1) * count);

  free(d);
  d = NULL;

  return 0;

}
