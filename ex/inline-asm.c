#include <stdio.h>
#include <stdlib.h>
#include <time.h>
    
int main (void) 
{
  srand(time(0));
  register int operand1, operand2, sum, accumulator, i;
  
  
  for(i=0; i<10000; i++)
    {

      operand1 = rand(); operand2 = rand();
      
      __asm__ ("movl %1, %0\n\t"
	       "addl %2, %0"
	       : "=r" (sum)/* output operands */
	       : "r" (operand1), "r" (operand2) /* input operands */
	       : "0");/* clobbered operands */
      
      accumulator = sum;
      
      __asm__ ("addl %1, %0\n\t"
	       "addl %2, %0"
	       : "=r" (accumulator)
	       : "0" (accumulator), "g" (operand1), "r" (operand2)
	       : "0");/* clobbered operands */

      fprintf(stdout, "%g\n", (double) ((accumulator > 0) ? accumulator : -accumulator));
      
    }
  
  return 0;
}
