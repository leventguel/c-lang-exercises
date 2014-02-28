#include <stdio.h>

int main(void)
{
  int arr[5];
  
  arr[3]=128;
  /* *((short*) &arr[6]) = 2 */
  ((short*) arr)[6] = 2;

  printf("%hd \n", ((short*) arr)[6]);
  printf("%d \n", ((int*) arr)[3]);
  printf("%d \n", arr[3]);
  printf("%hd \n", arr[6]);
  printf("%hd \n", *((short*) &arr[6]));
  *((short*) &arr[6]) = 2;
  printf("%hd \n", *((short*) &arr[6]));
  printf("%d \n", arr[3]);
  printf("%hd \n", arr[6]);
  return 0;
}
