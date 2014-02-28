#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void) 
{
  char *foo = (char*)malloc(sizeof (char*) * 80);
  foo="abc cde efg hij";
  unsigned int i = 0; 
  for(i = 0; i < strlen(foo) - 1; i++)
    { 
      if(isspace(foo[i]))
	{printf("isspace\n");}
    }
  return 0;
}
