/* 
 * File:   main.c
 * Author: Techplex.Engineer
 *
 * Created on February 14, 2012, 9:16 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <strings.h>
#include <stdint.h>
#include <printf.h>

  int printf_arginfo_M(const struct printf_info *info, size_t n, int *argtypes) {
    /* "%M" always takes one argument, a pointer to uint8_t[6]. */
    if (n > 0) {
      argtypes[0] = PA_POINTER;
    }
    return 1;
  } /* printf_arginfo_M */
  
  int printf_output_M(FILE *stream, const struct printf_info *info, const void *const *args) {
    int value = 0;
    int len;
    
    value =  **((int **) (args[0]));
    //Begin My Code ------------------------------------------------------------
    char buffer [50] = ""; //Is this bad?
    char buffer2 [50] = ""; //Is this bad?
    int bits = info->width;
    if (bits <= 0)
      bits = 8; //Default to 8 bits
    
    int mask = pow(2, bits - 1);
    while (mask > 0) {
      sprintf(buffer, "%s", (((value & mask) > 0) ? "1" : "0"));
      strcat(buffer2, buffer);
      mask >>= 1;
    }
    strcat(buffer2, "\n");
    //End my code --------------------------------------------------------------
    len = fprintf(stream, "%s", buffer2);
    return len;
  } /* printf_output_M */

int main(int argc, char** argv) {
  
  register_printf_function('B', printf_output_M, printf_arginfo_M);
  
  printf("%B \n", 65);
  
  return (EXIT_SUCCESS);
}
