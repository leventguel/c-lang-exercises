#include <math.h>
#include <stdio.h>

int main()
{
  int arr[6]={1, 2, 3, 4, 5}; /* index-1 element array (of index-1 length) */
  int i;
  
  arr[5]=6; /* setting the element at index 5 means setting the 5+1'th element i.e the 6'th one */

  /* when you see array declarations you use index-1, but when setting themselves you use index+1 */

  for(i=0;i<=5;i++) /* our index runs at most to (index-1) of the array index i.e 6-1=5 */
    {
      printf("%lu %lu %d %d %d \n", (unsigned long int) (arr[i]), (unsigned long int) (arr[i]), arr[i], *(arr+i), (arr[i]));
    }
  
  return 0;
}
