#include <stdio.h>
#include <stdlib.h>

int compare_int(const void *p, const void *q)
{
 
  int a, b;
 
  a = *( (int *)p );
  b = *( (int *)q );
 
  if(a < b){ return -1; }
  if(a > b){ return  1; }
  return 0;
}
 
void print_numbers(int *array, size_t len)
{
  printf("{ ");
 
  int i;
  for(i=0; i<len; i++){
    printf("%d ", array[i]);
  }
 
  printf("}\n");
}
 
int main()
{
  int numbers[10] = { 5, 3, 0, 10, -2, 8, 7, 3, 4, -4 };
 
  print_numbers(numbers, sizeof numbers / sizeof numbers[0]);
 
  qsort(numbers, 
	sizeof numbers / sizeof numbers[0],
	sizeof numbers[0], 
	compare_int);
 
  print_numbers(numbers, 10);
 
  return 0;
}
