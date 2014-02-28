#include <stdio.h>

int i;
char msgp[21];

char *get_message(void)
{
  char msg[21] = "Aren't pointers fun!?";
  for(i = 0; i < 22; i++)
    {
      msgp[i] = msg[i];
    }
  return 0;
}

int main(void)
{
  get_message();
  char *string = msgp;
  puts(string);
  return 0;
}
