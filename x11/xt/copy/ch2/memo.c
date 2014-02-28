/********************************************************************
 *         This example code is from the book:
 *
 *           The X Window System: Programming and Applications with Xt
 *           Second OSF/Motif Edition
 *         by
 *           Douglas Young
 *           Prentice Hall, 1994
 *
 *         Copyright 1994 by Prentice Hall
 *         All Rights Reserved
 *
 *  Permission to use, copy, modify, and distribute this software for 
 *  any purpose except publication and without fee is hereby granted, provided 
 *  that the above copyright notice appear in all copies of the software.
 * *****************************************************************************/

/************************************************
 * memo.c: Display a string on the screen
 *************************************************/
#include <Xm/Xm.h>          /* Required by all Motif applications */
#include <Xm/Label.h>       /* Required by XmLabel widget */
#include <stdlib.h>         /* Needed for exit() */
#include <stdio.h>          /* Needed to use fprintf */

void main ( int argc, char **argv )
{
    Widget       shell, msg; /* Widgets created by this application */
    XtAppContext app;        /* An application context, needed by Xt */
    XmString     xmstr;      /* Compound string used by Motif */

   /*
    * Initialize Xt
    */

    shell = XtAppInitialize ( &app, "Memo", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

    if ( argc != 2 ) /* Make sure there is exactly one argument */
    {
        fprintf (stderr, "Usage:  memo message-string\n" );
        exit ( 1 );
    }

   /* Convert the first argument to the form expected by Motif */

    xmstr = XmStringCreateLtoR ( argv[1], XmFONTLIST_DEFAULT_TAG );

   /*
    * Create a Motif XmLabel widget to display the string
    */

    msg = XtVaCreateManagedWidget ( "message", 
                                    xmLabelWidgetClass, shell, 
                                    XmNlabelString,     xmstr,
                                    NULL );

    XmStringFree ( xmstr );  /* Free the compound string */

   /*
    * Realize the shell and enter an event loop.
    */

    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

