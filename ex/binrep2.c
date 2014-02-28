#include <stdio.h>

char* pBinFill(long int x,char *so, char fillChar); // version with fill
char* pBin(long int x, char *so);                    // version without fill
#define width 64

char* pBin(long int x,char *so)
{
  char s[width+1];
  int    i=width;
  s[i--]=0x00;   // terminate string
 do
   { // fill in array from right to left
     s[i--]=(x & 1) ? '1':'0';  // determine bit
     x>>=1;  // shift right 1 bit
   } while( x > 0);
 i++;   // point to last valid character
 sprintf(so,"%s",s+i); // stick it in the temp string string
 return so;
}


char* pBinFill(long int x,char *so, char fillChar)
{ // fill in array from right to left
  char s[width+1];
  int    i=width;
  s[i--]=0x00;   // terminate string
 do
   {
     s[i--]=(x & 1) ? '1':'0';
     x>>=1;  // shift right 1 bit
   } while( x > 0);
 while(i>=0) s[i--]=fillChar;    // fill with fillChar 
 sprintf(so,"%s",s);
 return so;
}

void test()
{
  char so[width+1]; // working buffer for pBin
  long int   val=1;
 do
   {
     val*=11; // generate test data
     printf("%ld =\t\t%#lx =\t\t0b%s\n", val, val, pBinFill(val, so, 0));
   } while (val < 100000000);
}

int main(int argc, char *argv[]) {
  /* Process all arguments, outputting their binary. */
  
  test();
  return 0;
}
