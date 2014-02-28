#include <math.h>
#include <stdio.h>

int main(void)
{
  int i, n;
  
  float x1, x[6], f[6], e[6], d[6], h[6], r[6], z[6], y, df, dx, xs;
  
  FILE *fp;

  fp = fopen("data.dat", "w");
  
  x[0]=1; x[1]=4; x[2]=2.5; x[3]=3.5; x[4]=5.1; x[5]=6.0;

  f[0]=-.233; f[1]=-.407; f[2]=.728; f[3]=1.322; f[4]=1.810; f[5]=1.751;

  n=5;

  for(i=0; i <= n; i++)
    {
      fprintf(fp, "%f %f \n", x[i], f[i]);
    }

  fclose(fp);
  
  for(i=0; i <= n-2; i++)
    {
      e[i] = 2.0 * (x[i+2] - x[i]);
    }

  for(i=0; i <= n-2; i++)
    {
      h[i] = x[i+2] - x[i+1];
    }

  for(i=0; i <= n-1; i++)
    {
      d[i] = x[i+1] - x[i];
    }

  for(i=0; i <= n-2; i++)
    {
      r[i] = 6* (f[i+2] - f[i+1]) / h[i] - 6 * (f[i+1] - f[i]) / d[i];
      printf("%f %f %f %f \n", e[i], d[i], h[i], r[i]);
    }

  for(i=0; i <= n-3; i++)
    {
      df = d[i]/e[i];
      e[i+1] = e[i+1] - df * h[i];
      r[i+1] = r[i+1] - df * r[i];
    }

  for(i=n-3; i <= 0; i--)
    {
      df = h[i] / e[i+1];
      r[i+1] = r[i] - r[i+1] * df;
    }

  for(i=0; i <= n-2; i++)
    {
      z[i+1] = r[i] / e[i];
    }
  
  z[0] = 0;
  z[n] = 0;

  fp = fopen("cubic.dat", "w");
  
  for(i=0; i < n; i++)
    {
      dx = (x[i+1] - x[i]) / 5.0;
      xs = x[i] + .1;
      
      for(x1 = xs; x1 < x[i+1]; x1 = x1 + dx)
	{
	  y = -z[i] * pow((x1 - x[i+1]), 3) / (6.0 * d[i]) +
	    z[i+1] * pow((x1 - x[i]), 3) / (6.0 * d[i]) +
	    (f[i+1] / d[i] - z[i+1] * d[i] / 6.0) * (x1 - x[i]) + 
	    (-f[i] / d[i] + z[i] * d[i] / 6.0) * (x1 - x[i+1]);
	  fprintf(fp, "%f %f \n", x1, y);
	}
    }
  
  fclose(fp);
  return 0;
}


