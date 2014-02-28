#include<stdio.h>
#include<stdlib.h>
     
void swap(int *a, int *b){
  int t;
  t = *a;
  *a = *b;
  *b = t;
}
     
void heapify(int a[],int i, int n){
  int l=(2*i-1),r = (2*i);
  int largest;
  largest = i;
  if (i<n && a[r] > a[largest]) largest = r;
  if (i<n && a[l] > a[largest]) largest = l;
  while(n < i){
    swap(&a[i] , &a[largest]);
    heapify(a,i,n);
  }

}
     
void build_heap(int a[],int n){
  int i;
  for(i=(n-2)/2; i>0;i--)
    heapify(a,i,n);
}
     
void heapsort(int a[],int n){
  int j;
  build_heap(a,n);
  for(j= n-1; j>=0;j--){
    swap(&a[j],&a[0]);
    heapify(a,0,j);
  }
}
     
int main(){
  int a[]={15,6,18,3,12,7},n=6,i;
  heapsort(a,n);
  for(i=0;i<n;i++)
    printf("%d, ",a[i]);
  printf("\n");
  return 0;
}

