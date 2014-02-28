#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{

  char* f(const char *s) 
  {
    unsigned int i=0;
    unsigned int j = strlen(s);
    char current, next, last, start;
    
    for(; i<j; i++)

      {

	start = *(s);
	current = *(s+i);
	next = *(s+i+1);
	last = *(s+j-1);

	if (next==current) 
	  {
	    printf(" detected doubles at: %d,%d\n", i,i+1);
	  } 
	else 
	  {
	    printf(", no doubles found\n");
	  }

      }
    printf("start is %c at 0\n", start);
    printf("last is %c at %d\n", last, (int) strlen(s)-1);
    return 0;
  };

  f("jellol");
  return 0;
}
