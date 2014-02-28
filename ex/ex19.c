#include <math.h>
#include <stdio.h>

int main()
{
  int i; char **marker, *course[2];
  
  course[0]="numerical";
  course[1]="methods";
  
  marker=&course[0];
  
  for(i=0;i<=8;i++)
    {
      printf("%u %u %c\n", (unsigned int) &marker[i], (unsigned int) &course[i], *(*marker));
      (*marker)++;
    }
}

