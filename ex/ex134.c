#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
  
  char *s = NULL; int len;

  const char *src = "abcd";
  len = strlen(src) + 1;

  s = calloc(len, sizeof(char));
  
  strcpy(s, src);
  printf("%lu\n", strlen(s));
  printf("%s\n", s);
  
  const char *src2 = "efghijklmnoöp";
  len = strlen(src2) + 1;
  
  s = realloc(s, len * sizeof(char));
  
  s = strcpy(s, src2);
  printf("%lu\n", strlen(s));
  printf("%s\n", s);

  free(s);
  return 0;
}
  
