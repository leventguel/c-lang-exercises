#include <stdio.h>
#include <string.h>

int main(void)
{
  char *name = "Levent Guel";
  printf("My name is %s\n", name);
  /*  printf("The address of name is 0x%x\n", (unsigned int) &name); */
  /* printf("The address that *name points to is 0x%x\n", (unsigned int) name); */
  printf("The address of name is %p\n", &name);
  printf("The address that *name points to is %p\n", name);
  return 0;
}
