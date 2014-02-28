#include <stdio.h>
#include <string.h>


char * reverseSubString( char *haystack, char *needle){
  char 
    *startPoint = NULL,
    *endPoint = NULL,
           tmp
    ;
  
  /**Filtering Input parameters **/
  if( !needle  || strlen(needle) < 2) {
    printf("invalid substring..\n");
    return NULL;
  }
  
  printf("Finding substring..\n");
  startPoint = strstr(haystack, needle);
  endPoint = startPoint + strlen(needle) -1;

  
  while( startPoint <= endPoint){
    tmp = *startPoint;
    *startPoint = *endPoint;
    *endPoint = tmp;
    ++startPoint; --endPoint;
  }
  

  return haystack;
}


int main(){
  
  char hayStack[]="sonu is shas shashank Friend";
  char needle[]="shashank";
  
  char *result = NULL;
  result  = reverseSubString(hayStack, needle);
  printf( "Result string: %s\n", result   );

  return 0;
}
