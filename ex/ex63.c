#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int i, j, n;
  
  float x1, *x, *y, df, df1, xl, a, b, y1;
  float S=0.0, Sx=0.0, Sy=0.0, Sxx=0.0, Syy=0.0, Sxy=0.0, D;

  FILE *fp, *fp1;

  n=125;

  x = (float*) malloc(n);
  y = (float*) malloc(n);

  fp1 = fopen("fit.data", "r");

  i=0;

  while(!feof(fp1))
    {
      fscanf(fp1, "%f %f", &x1, &y1); 
      x[i] = x1; 
      y[i] = y1;
      printf("%d %f \n", i, x[i]);
      i++;
    }

  fclose(fp1);

  n = i-1;

  for(i=0; i <= n; i++)
    {
      printf("%d %f %f \n", i, x[i], y[i]);
    }
 
  for(i=0; i <= n; i++)
    {
      S = S + i;
      Sx = Sx + x[i]; 
      Sy = Sy + y[i]; 
      Sxx = Sxx + x[i] * x[i]; 
      Syy = Syy + y[i] * y[i]; 
      Sxy = Sxy + x[i] * y[i];
    }
  
  D = S*Sxx - Sx*Sx;
  a = (S*Sxy  - Sx*Sy) / D;
  b = -(Sx*Sxy - Sxx*Sy) / D;
  printf("%f %f \n", a, b);
  return 0;

}

