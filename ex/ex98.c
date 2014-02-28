#include <stdio.h>

char Format[] = "Hello world, %d\n";

int main (void)
{
   __asm__ __volatile__
     (
      // Make stack space for arguments to printf
      "subl $8, %esp\n"
      "movl $3, 4(%esp)\n"
      "movl $Format, (%esp)\n"
      "call printf\n"
      // Clean-up the stack
      "addl $8, %esp\n"
      );
   return 0;
}
