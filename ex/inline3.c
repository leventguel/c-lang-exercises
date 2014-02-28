#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
  double a=1.0, b=-1.0, result, i;
  
  for(i=0.0; i<M_PI*100.0; i++)
    {

      __asm__ __volatile__ ("add %1, %2\n\t"
			    "add %2, %3\n\t"
			    "mov %3, %0"
			    : "=g" (result)
			    : "a" (a), "r" (b), "g" (i*sin(i))
			    : "0" "1", "2", "3"
			    );
      
      fprintf(stdout, "ebx=%g\n", result);
    }

  return 0;
}

