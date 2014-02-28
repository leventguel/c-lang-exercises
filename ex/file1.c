#include <stdio.h>

static int array[] = {1, 2, 3, 0};
int arraysz = sizeof(array)/sizeof(array[0]);

int main()
{
  int i;

  for(i=0; i < arraysz-1; i++)
    {
      printf("%d \n", array[i]);
    }
  return 0;
}
