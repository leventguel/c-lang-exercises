#include <stdio.h>

#define MAX 10

int A[MAX];
void recSS(int A[], int i, int n);

int main()
{
  static int i, n;
  /* read and store input in A */
  for (n = 0; n < MAX && scanf("%d", &A[n]) != EOF; n++);
  recSS(A,i,n); /* sort A */
  for (i=0; i < n; i++)
    printf("%d\n", A[i]); /* print A */
  return 0;
}

void recSS(int A[], int i, int n)
{
  int j, small, temp;
  if (i < n-1) {/* basis is when i = n-1, in which case */
    /* the function returns without changing A */
    /* induction follows */
    small = i;
    for (j = i+1; j < n; j++)
      if (A[j] < A[small])
	small = j;
    temp = A[small];
    A[small] = A[i];
    A[i] = temp;
    recSS(A, i+1, n);
  }
}
