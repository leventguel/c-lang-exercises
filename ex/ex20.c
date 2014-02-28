#include <math.h>
#include <stdio.h>

int main()
{
  int num[]={10,20,30,40,50};
  int i, m, *j;
  m=5;
  j=&m;

  // if you comment out pass by reference or pass by value one after the other and compile this program you may get the results you expect, but when
  // both parts are uncommented the modifying behaviour of the print() function on the variable m is seen
  // when you want the behaviour of this one the same as before put m back to 5 after the pass by reference part

  /* Pass by reference */

  print(5, num, j); // j = &m, m=5, buth within print() j=*l=15 and since j is pointing to m m gets set to 15 here i.e. m is modified thru print()
  printf("%d %d\n", num[4], m); // here m is 15 not 5

  // comment this in or out!
  m=5;

  /* Pass by value */

  print1(num[3],m);
  printf("%d %d\n", num[3], m);
  return 0;
}

int print(n,b,l)
int n, b[5], *l;
{
  int i;
  b[4]=60;
  *l=15;
  for(i=0; i<=4;i++)
    {
      printf("%u %d %d\n", (unsigned int) &b[i], b[i], *l);
    }
  return 0;
}

int print1(int k, int n)
{
  int i;
  k=80;
  n=20;
  printf("%d %d\n", k, n);
  return 0;
}
