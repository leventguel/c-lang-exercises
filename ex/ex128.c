#include <stdio.h>

int count;
/* This is a global variable */
void head1(void);
void head2(void);
void head3(void);

int main(void)
{
  register int index;
  /* This variable is available only in main
   */
  head1();
  head2();
  head3();
  /* main "for" loop of this program
   */
  for (index = 8;index > 0;index--) {
    int stuff; /* This variable is only available in these braces */
    for (stuff = 0;stuff <= 6;stuff++)
      printf("%d",stuff);
    printf(" index is now %d\n",index);
  }
  return 0;
}

int counter;

void head1()
{
  /* This is available from this point on
   */
  int index;
  /* This variable is available only in head1
   */
  index = 23;
  printf("The header1 value is %d\n", index);
}

void head2()
{
  int count;
  /* This variable is available only in head2
   */
  /* and it displaces the global of the same name
   */
  count = 53;
  printf("The header2 value is %d\n", count);
  counter = 77;
}

void head3()
{
  printf("The header3 value is %d\n", counter);
}
