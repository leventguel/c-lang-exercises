#include <stdio.h>

char s1[15];

main(int argc, char **argv)
{
  char s2[4]; /* array declared static */
  
  s2 = "Jim"; /* you cannot assign to static array */
  return 0;
}
