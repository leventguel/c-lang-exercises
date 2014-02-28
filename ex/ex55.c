#include <stdio.h>

char msg[] = "Aren't pointers fun!?";

char *get_message(void)
{
  return msg;
}

int main(void)
{
  char *string = get_message();
  puts(string);
  return 0;
}
