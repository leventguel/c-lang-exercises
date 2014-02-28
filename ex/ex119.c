#include <stdio.h>
#include <string.h>

int main(void)
{
  char *a = "\xff";
  printf("%p \n", a);
  printf("%d \n", *a);
  printf("%u \n", *a);
  printf("%d \n", (int) strlen(a));
  return 0;
}
