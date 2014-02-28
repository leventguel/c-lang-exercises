#include <stdio.h>

#define array_length(arr) (sizeof(arr) == 0 ? 0 : sizeof(arr)/sizeof(arr[0]))

int i;
int len;
char msgp[21];
/*FILE *fp; */

char *get_message(void)
{
  char msg[] = "Aren't pointers fun!?";
  for(i = 0; i < array_length(msg); i++)
    {
      msgp[i] = msg[i];
    }
  len = array_length(msg);
  return 0;
}

int main(void)
{
  /*  fp=fopen("/dev/stdout", "w"); */
  get_message();
  char *string = msgp;
  puts(string);
  printf("sizeof message == sizeof_array -1: %d", len-1); /* we can't use putc() here, cause we don't want len to be interpreted as char! */
  puts(""); /* empty string for newline effect (man 3 puts()) */
  /*  fclose(fp); */
  return 0;
}
