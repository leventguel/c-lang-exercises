#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(void)
{
  srand(time(0));
  register int op1, op2, sum, acc;
  op1 = rand(); op2 = rand();
  
  __asm__ __volatile__("movl %1, %0\n\t"
		       "addl %2, %0"
		       : "=r" (sum)/* output operands */
		       : "r" (op1), "r" (op2) /* input operands */
		       : "0");/* clobbered operands */
  
  acc = sum;
  
  __asm__ __volatile__("addl %1, %0\n\t"
		       "addl %2, %0"
		       : "=r" (acc)
		       : "0" (acc), "g" (op1), "r" (op2)
		       : "0");
  
  printf("%F\n%d\n%d\n", (double) acc, op1, op2);
  return 0;
}
