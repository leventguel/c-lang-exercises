#include <stdio.h>
 
int main(){
  int x = 10;
  int y = 20;
    
  void *vp = &x;
  int *pint = vp;
  *pint *= -1;
    
  vp = &y;
  pint = vp;
  *pint *= -1;
    
  printf("x: %d, y: %d\n", x,y);
  return 0;
}
