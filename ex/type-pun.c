#include <stdio.h>
 
struct MyRecord {
  int value;
  char *text;
};
 
/* Print the contents of an array of ints with the given stride */
void print_some_ints(const int *arr, int length, size_t stride)
{
  int i;
  printf("Address\t\tValue\n");
  for (i=0; i < length; ++i) {
    printf("%p\t%d\n", arr, arr[0]);
    arr = (int *)((unsigned char *)arr + stride);
  }
}
 
int main(void)
{
  int ints[100] = {0};
  struct MyRecord records[100] = {{0}}; /* initialize array of structs */
 
  print_some_ints(&ints[0], 100, sizeof ints[0]);
  print_some_ints(&records[0].value, 100, sizeof records[0]);
  return 0;
}
