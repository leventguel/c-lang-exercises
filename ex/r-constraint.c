int main(void)
{
  int x = 10, y;
  
  asm (
       "movl %1,%%eax\n\t"
       "movl %%eax,%0"
       :"=&r"(y)/* y is output operand */
       :"r"(x)/* x is input operand */
       :"%eax");/* %eax is clobbered register */
}

