/**************************************************************
* memo.c  Display a string on the screen
****************************************************************/

#include <Xm/Xm.h>       /* motif lib */ /* Required by all motif widgets */
#include <Xm/Label.h>    /* Required by XmLabel widget */
#include <stdlib.h>      /* Needed for exit() */
#include <stdio.h>       /* Needed for fprintf() */

void main(int argc, char ** argv)    /* Non-Ansi C */
{
  Widget shell, msg; /* Widgets created by this application */
  XtAppContext app; /* an application context needed by Xt */
  XmString xmstr;   /* compound string used by motif */

  /*
   * Iinitialize Xt
   */

  shell = XtAppInitialize(&app, "Memo", NULL, 0, &argc, argv, NULL, NULL, 0);

  if (argc!=2) /* Make sure there is exactly one argument */
    {
      fprintf(stderr, "Usage: memo message-string\n");
      exit(1);
    }

  /* convert the first argument to the form expected by Motif */
  
  xmstr = XmStringCreateLtoR(argv[1], XmFONTLIST_DEFAULT_TAG);

  /*
   * Create a motif XmLabel string to display the string
   */

  msg = XtVaCreateManagedWidget("message", xmLabelWidgetClass, shell, XmNlabelString, xmstr, NULL);



  /*
   * Realize the shell and enter an event loop.
   */

  XtRealizeWidget(shell);
  XtAppMainLoop(app);

  XmStringFree(xmstr); /* Free the compound string */
}
