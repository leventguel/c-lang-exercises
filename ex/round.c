#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv) {

  float n=argv[1];

double roundd(double n, short mode) {
  short cw, newcw;
  
  __asm__("fstcw %w0" : "=m" (cw));
  newcw = (cw & 0xf3ff) | mode;
  __asm__("fldcw %w0" : : "m" (newcw));
  __asm__("frndint" : "+t" (n));
  __asm__("fldcw %w0" : : "m" (cw));
  return n;
}
 printf("%lf\n", n);

}
