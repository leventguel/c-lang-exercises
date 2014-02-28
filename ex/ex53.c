#include <math.h>
#include <stdio.h>

int main(void)
{

  int i, j, n;

  float x1, x[5], f[5], y, df, df1;

  FILE *fp;

  fp = fopen("data.dat", "w");
  
  x[0] = 2.5; x[1] = 3.75; x[2] = 5.0; x[3] = 6.25;
  f[0] = -28.62; f[1] = -159.26; f[2] = -513.97;

  f[3] = -1265.45;

  n = 3;

  for(i=0; i <= n; i++)
    {
      fprintf(fp, "%f %f \n", x[i], f[i]);
    }
  fclose(fp);

  for(j=0; j < n; j++)
    {
      df = f[j];

      for(i=1; i <= (n-j); i++)
	{
	  df1 = df;
	  df = (f[i+j] - f[i+j-1]) / (x[i+j] - x[i-1]);
	  if (i > 1) f[i+j-1] = df1;
	}
      
      f[n] = df;
      printf("%d %f \n", j, f[j+1]);
    }

  fp = fopen("newton.dat", "w");
  for(x1=2.6; x1 <= 6.25; x1 = x1 + 0.2)
    {
      y = f[0] + (x1 - x[0]) * ( f[1] + (x1 - x[1]) * ( f[2] + (x1 -x[2]) * f[3]) );
      fprintf(fp, "%f %f \n", x1, y);
    }

  fclose(fp);
  return 0;
}
