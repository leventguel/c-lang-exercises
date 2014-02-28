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

/**************************************************
 * setupicon.h: Install the xlogo as a window  
 *              manager icon  for a given shell
 **************************************************/
#include <Xm/Xm.h>
#include <X11/bitmaps/xlogo64>

void SetupIcon ( Widget shell )
{
    Display *dpy = XtDisplay (shell );
    Window root  = DefaultRootWindow ( dpy );

    Pixmap bitmap =  XCreateBitmapFromData ( dpy, root,
                                             xlogo64_bits,
                                             xlogo64_width, 
                                             xlogo64_height );

    XtVaSetValues ( shell, XmNiconPixmap, bitmap, NULL );
}
            



#include <Xm/Label.h>       /* Required by XmLabel widget */

void main ( int argc, char **argv )
{
    Widget       shell, msg; /* Widgets created by this application */
    XtAppContext app;        /* An application context, needed by Xt */
    XmString     xmstr;      /* Compound string used by Motif */

   /*
    * Initialize Xt
    */

    shell = XtAppInitialize ( &app, "Hello", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

    xmstr = XmStringCreateLtoR ( "Hello", XmFONTLIST_DEFAULT_TAG );

   /*
    * Create a Motif XmLabel widget to display the string
    */

    msg = XtVaCreateManagedWidget ( "hello", 
                                    xmLabelWidgetClass, shell, 
                                    XmNlabelString,     xmstr,
                                    NULL );

    XmStringFree ( xmstr );  /* Free the compound string */

   /*
    * Realize the shell and enter an event loop.
    */


    SetupIcon(shell);
    
    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

