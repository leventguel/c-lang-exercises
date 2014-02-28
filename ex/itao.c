#include <stdio.h>

void itoa(int val, char *buf) {
  for(int i = 4; val && i ; --i, val /= 10) {
    printf("%d - %c\n",i,"1234567890"[val % 10]);
    buf[i] = "0123456789"[val % 10];
  }
}
     
int main(void) {
  char bla[5] = { '\0' };
  int x = 1923;
       
  itoa(x,bla);        
       
  printf("--> %s <--\n", bla);
}

