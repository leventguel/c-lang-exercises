#include<stdio.h>
#include<stdlib.h>

void swap(int *a, int *b){
  int t;
  t = *a;
  *a = *b;
  *b = t;
}
     
void heapify(int *a,int i, int n){
  int root=i;
  while( root*2+1 < n)
    {
      int child = root * 2 + 1;
      if( (child + 1 < n) && ( a[child] < a[child+1] ) )
	{
	  child += 1;
	}
      if( (a[root] < a[child] ))
	{
	  swap(&a[child], &a[root]);
	  root = child;
	}
      else
	return;
    }
}
     
void heapsort(int *a,int n){
  int i,j;

  for(i=(n-2)/2;i>=0;i--)
    {
      heapify(a, i, n);
    }
  for(j=n-1;j>0;j--)
    {
    swap(&a[j],&a[0]);
    heapify(a,0,j);
    }
}
     
int main(void)
{
  int a[]={15,6,18,3,12,7},n=6,i;
  heapsort(a,n);
  for(i=0;i<n;i++)
    printf("%d, ",a[i]);
  printf("\n");
  return 0;
}
