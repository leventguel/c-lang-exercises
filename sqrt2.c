/* 
    Caution added by Martin L. Buchanan, mlb@backgroundtask.com, Wed 11/16/2005: 
     
    If number is the maximum unsigned int value, call it MAX_VAL, then the first  
    evaluation of NEXT(n, number), with n == 1, produces an overflow when  
    1 + MAX_VAL/1 is evaluated. For an unsigned type the overflow typically  
    wraps around and yields zero as the macro result and zero as the  
    overall function result. 
*/  
    #include <stdlib.h>  
      
#define NEXT(n, i)  (((n) + (i)/(n)) >> 1)  
      
unsigned int isqrt(int number) {  
  unsigned int n  = 1;  
  unsigned int n1 = NEXT(n, number);  
      
  while(abs(n1 - n) > 1) {  
    n  = n1;  
    n1 = NEXT(n, number);  
  }  
  while(n1*n1 > number)  
    n1--;  
  return n1;  
}  
