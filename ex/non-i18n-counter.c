#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main() {
  /* Non-executable part */
  int i, length, counter=0;
  char *mess, line[11], *info[]=
    {"digit", "digits"};
  /* Executable part */
  printf ("Please, type a line\n");
  fgets(line,11,stdin);
  length=strlen(line);
  for(i=0; i<length; i++)
    counter+=isdigit(line[i])?1:0;
  mess=counter>1?info[1]:info[0];
  printf ("You typed %d %s\n",
          counter,mess);
  exit(0); }
