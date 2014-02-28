#include <stdio.h>


int main() 
{
  int i = 2;
  double d=i;
  double *dp=&d;
  void *vp=&d;
  void **vf=&dp;
  void **vk=*&dp;
  void *dm=*vf;
  void *vm=dp;
  printf("%d, %f, %f, %f, %f, %f, %f, %f, %f\n", i, d, *(&d), *dp, *((double*) vp), *((double*) *vf), *((double*) dm), *((double*) vk), *((double*) vm));
  return 0;
}
