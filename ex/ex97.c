#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <wchar.h>
#include <printf.h>

typedef struct
{
  char *name;
}Widget;

int print_widget (FILE *stream,
	      const struct printf_info *info,
		  const void *const *args)
{
  const Widget *w;
  char *buffer;
  int len;
     
  /* Format the output into a string. */
  w = *((const Widget **) (args[0]));
  len = asprintf(&buffer, "<Widget %p: %s>", w, w->name); /* buffer is not an array yet! */
  if (len == -1)
    return -1;
     
  /* Pad to the minimum field width and print to the stream. */
  len = fprintf (stream, "%*s",
		 (info->left ? -info->width : info->width),
		 &buffer[0]); /* here buffer got filled and is an array of chars! */
     
  /* Clean up and return. */
  free (buffer);
  return len;
}
     
     
int print_widget_arginfo (const struct printf_info *info, size_t n,
			  int *argtypes, int *size)
{
  /* We always take exactly one argument and this is a pointer to the
   * structure.. */
  if (n > 0)
    {
      argtypes[0] = PA_POINTER;
      size[0] = (int) sizeof(int);
    }
  return 1;
}
     
     
int main (void)
{
  /* Make a widget to print. */
  Widget mywidget;
  mywidget.name = "mywidget";

  /* pa_fmt = register_printf_type(fmt_va); */

  /* Register the print function for widgets. */
  register_printf_specifier('W', print_widget, print_widget_arginfo);
     
  /* Now print the widget. */
  printf ("%W \n", &mywidget);
  printf ("%35W \n", &mywidget);
  printf ("%-35W \n", &mywidget);
     
  return 0;
}

#undef _GNU_SOURCE
