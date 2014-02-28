#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{

  int f(const char *s) 
  {
    unsigned int i=1;
    unsigned long j = strlen(s)-1;

    unsigned long pos_start, pos_next, pos_last;
    unsigned char start, next, last;



    int count=0;
    int counter=1;

    do
      {

	start = *(s);
	next = *(s+i);
	last = *(s+j);
	
	pos_start = (unsigned long) (s);
	pos_next = (unsigned long) (s+i);
	pos_last = (unsigned long) (s+j);
	
	if(start == next)
	  {
	    counter++;
	  }

	pos_start++; pos_next++; pos_last--;
	i++;j--;
	count = counter;
	printf("%c,%ld %c,%ld %c,%ld \n", start, pos_start, next, pos_next, last,pos_last);
      }
    while((pos_start <= pos_last));
    
    printf("%d\n", count);
    printf("%s\n", s);
    return 0;
  };

  f("jellol");
  return 0;
}
