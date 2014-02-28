/* 
 * File:   main.c
 * Author: Techplex.Engineer
 *
 * Created on February 14, 2012, 9:16 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <strings.h>
#include <stdint.h>
#include <printf.h>

typedef struct fasta_t
{
  char* name;
  char* sequence;
}Fasta;

static int printf_fasta_arginfo(
				const struct printf_info *info,
				size_t n,
				int *argtypes,
				int *size)
{
  /* We always take exactly one argument and this is a pointer to the
     structure.. */
  if (n > 0) argtypes[0] = PA_POINTER;
  return 1;
}



#define FPUTC(C) (ret+=(fputc(C,stream)==EOF?0:1))

/** handler for printf called by register_printf_function */

static int printf_fasta_handler(
				FILE *stream, /*  stream output */
				const struct printf_info *info, /* information about the various options */
				const void *const *args /* arguments */
				)
{
  int n=0;
  int ret=0;
  char* p;
  
  int lline =(info->prec<1?60:info->prec);
  const Fasta* fasta=*((const Fasta**)(args[0]));
  
  if(fasta->name!=NULL)
    {
      FPUTC('>');
      ret+=fputs(fasta->name,stream);
    }
  else
    {
      FPUTC('>');
    }
  
  if(fasta->sequence!=NULL)
    {
      p=(char*)fasta->sequence;
      while(p[n]!=0 && (info->width<1 || n< info->width))
	{
	  if(n%lline==0) 
	    {
	      FPUTC('\n');
	    }
	  FPUTC(p[n]);
	  ++n;
	}
    }
  FPUTC('\n');
  /* returns the number of characters writtern */
  return ret;
}



int main(int argc, char** argv)
{
  
  register_printf_specifier('W',/* the new modifier */
			    /* handler function */
			    printf_fasta_handler,
			    /* arginfo function */
			    printf_fasta_arginfo );
  
  printf("%W \n", 65);
  
  return (EXIT_SUCCESS);
}
