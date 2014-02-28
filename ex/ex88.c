#include <stdio.h>

int main(void)
{
  int a,c;
  
  /* Interger variables for examples */
  a = 12;
  
  a = a + 1; /* incrementing a variable */
  
  int b = 3;
  b = b * 5;
  int b = b * 2;
  
  c = a + b; /* simple addition */
  c = a - b; /* simple subtraction */
  c = a * b; /* simple multiplication */
  c = a / b; /* simple addition */
  c = a % b; /* simple modulo (remainder) */
  c = 12*a + b/2 - a*b*2/(a*c + b*2);
  c = c/4+13*(a + b)/3 - a*b + 2*a*a;
  
  a = b = c = 20;
  /* multiple assignment */
  a = b = c = 12*13/4;
  return 0;
}
