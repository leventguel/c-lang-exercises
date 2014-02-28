#include <stdio.h>
 
int main()
{
  int i, array[10];
  i = 0;
  array[i] = 10;
  printf("array[i]: %d\n"
	 "[i]: %d\n", array[i], i);
 
  /* change increment operator after you see the wrong result 
   * with [++i] and see it how it works
   */
  array[i++] = 20; 
  printf("array[i]: %d\n"
	 "[i]: %d\n", array[i], i);
  return 0;
}
