#include <stdlib.h>
#include <string.h>
#include <stdio.h>
 
#define DBL_SIZE sizeof(double)
typedef struct {
  double *A;
  int n;
} str_t;
 
 
str_t *str_new(const double *A, const int n){
  str_t *p = NULL;    
  if ((p =  malloc(sizeof (str_t)))!=NULL)
    {
      p->n=n;
      if (A!=NULL && n>0){
	p->A=malloc(n*DBL_SIZE);
	if (p->A==NULL)
	  { 
	    perror("Could not allocate memory for A. Error: "); 
	    return NULL;
	  }
	memcpy(p->A, A, n*DBL_SIZE);
      } else {
	// This is OK (No prob!)
	p->A=NULL; 
      }
    }else {
    // Could not allocate memory for p:
    perror("Could not allocate memory for an str_t variable. Error: "); 
    return NULL;
  }
  return p;   
}
 
 
void print_str(str_t *s){
  int i;
  for (i=0; i < s->n; i++) printf("A[%d]=%.1f\n",i, *(s->A+i));   
}
 
int main(void){ 
  int n=3;
  double *A = malloc(n*DBL_SIZE);
  if (A==NULL) {
    perror("Could not allocate memory:");
    return EXIT_FAILURE;
  }
  A[0]=100.0;
  A[1]=200.0;
  A[2]=300.0;
        
  str_t *my_str = str_new(A,n);
  if (my_str==NULL){
    return EXIT_FAILURE;
  }
  print_str(my_str);
        
  free(my_str);   
  free(A);
  return EXIT_SUCCESS;
}
