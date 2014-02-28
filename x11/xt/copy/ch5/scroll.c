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

/*****************************************************
 * scroll.c: Demonstrate an XmScrolledWindow widget
 *****************************************************/
#include <Xm/Xm.h>
#include <Xm/Label.h>
#include <Xm/ScrolledW.h>

void main ( int argc, char **argv ) 
{
    Widget       shell, swindow, label;
    XtAppContext app;
    
   /*
    * Initialize Xt
    */
    
    shell = XtAppInitialize ( &app, "Scroll", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

    swindow = 
         XtVaCreateManagedWidget ( "scrolledWindow", 
                                   xmScrolledWindowWidgetClass, shell,
                                   XmNscrollingPolicy, XmAUTOMATIC,
                                   XmNscrollBarDisplayPolicy, XmSTATIC,
                                   NULL );
                              
    label = XtCreateManagedWidget ( "label",xmLabelWidgetClass,
                                    swindow, NULL, 0 );

    XtManageChild ( swindow );

   /*
    * Realize the shell and enter the event loop.
    */
    
    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

