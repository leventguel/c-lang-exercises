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

/*****************************************************************
 * label.c: Simple program for experimenting with label widgets
 *****************************************************************/
#include <Xm/Xm.h>          
#include <Xm/Label.h>     

void main ( int argc, char **argv )
{
     Widget       shell, label; 
    XtAppContext app;       

    shell = XtAppInitialize ( &app, "Label", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

   /*
    * Create a Motif XmLabel widget
    */

    label = XtCreateManagedWidget ( "label", xmLabelWidgetClass, shell,
                                    NULL, 0 );

   /*
    * Realize the shell and enter an event loop.
    */

    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

