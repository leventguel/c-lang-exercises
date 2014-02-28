#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
  char * Fred="text";
  char * Okfred;
  int a=46;
  int * d=&a;
  char * Fred2=Fred;
  int * ptra = &a;
  int c = *ptra;
  int b[2];
  int * Ptrb=b;
  *++ptra;
  ++(*d) ;
    
  Okfred=(char *)malloc(strlen("david")+1) ;
  Fred=Okfred;
  *Okfred++='d';
  *Okfred++='a';
  *Okfred++='v';
  *Okfred++='i';
  *Okfred++='d';
  *Okfred= '\0';

  *(Fred+1)='2';

  printf("C= %i\n\r",c) ;
  printf("*d= %i\n\r",*d) ;
  printf("d= %i\n\r",d) ;
  printf("Fred = %s\n\r",Fred) ;
  printf("Fred2 = %s\n\r",Fred2) ;
  printf("Address of b[0] is 0x%x\n\r",b) ;
  printf("Address of b[0] is 0x%x\n\r",&b[0]) ;
  printf("Address of b[1] is 0x%x\n\r",&b[1]) ;
  printf("Address of Ptrb is 0x%x\n\r",Ptrb++) ;
  printf("Address of Ptrb is 0x%x\n\r",Ptrb) ;
  return 0;
}
