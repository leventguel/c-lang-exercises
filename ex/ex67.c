#include <stdlib.h>
#include <stdio.h>
 
int main(void){
  char *a = malloc(10L);
  if (a==NULL){
    perror("Could not allocate memory:");
    return EXIT_FAILURE;
  }else{
    return EXIT_SUCCESS;   
  }
}
