#include <stdlib.h>
#include <string.h>
#include <stdio.h>
 
#define DBL_SIZE sizeof(double)
typedef struct {
  double *A;
  int n;
} str_t;
 
str_t *str_factory(const double *A, const int n){
  str_t *p = NULL;    
  if ((p =  malloc(sizeof (str_t)))!=NULL)
    {
      p->A=(double *)A;
      p->n=(int)n;
    }
  return p;
}
 
str_t *str_new(const double *A, const int n){
  str_t *p = NULL;    
  if ((p =  malloc(sizeof (str_t)))!=NULL)
    {
      p->n=n;
      if (A!=NULL && n>0){
	p->A=malloc(n*DBL_SIZE);
	memcpy(p->A, A, n*DBL_SIZE);
      } else {p->A=NULL;}             
    }
  return p;   
}
 
void print_str(str_t *s){
  int i;
  for (i=0; i <= s->n-1; i++) printf("A[%d]=%.1f\n",i, *(s->A+i));   
}
 
int main(void){
  int n=3;
  double *A = malloc(n*DBL_SIZE);
  A[0]=100.0;
  A[1]=200.0;
  A[2]=300.0;
  printf("Using str_factory:\n");
  str_t *my_str = str_factory(A, n);
  print_str(my_str);
  printf("Using str_new:\n");
 
  str_t *other_str = str_new(A,n);
  print_str(other_str);
 
  free(my_str);
  free(other_str);
  free(A);
  return 0;
}
