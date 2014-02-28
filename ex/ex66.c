#include <stdio.h>
#include <string.h>

struct student
{
  char *name;
  char suid[8];
  int numUnits;
};


int main(void)
{
  
  struct student pupils[4];
  pupils[0].numUnits = 21;
  pupils[2].name = strdup("Adam");

  pupils[3].name = pupils[0].suid + 2;
  strcpy(pupils[0].suid, "40415xx");
  
  printf("%d \n", pupils[0].numUnits);
  printf("%s \n", pupils[2].name);
  printf("%s \n", pupils[3].name);
  
  return 0;
}
