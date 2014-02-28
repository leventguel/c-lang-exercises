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

/***********************************************************
 * mousetracks.c: Driver to test the mouse tracker module
 ***********************************************************/
#include <Xm/Xm.h>
#include <Xm/MainW.h>
#include <Xm/DrawingA.h>

extern Widget CreateMouseTracker ( Widget parent, Widget target );

void main ( int argc, char **argv ) 
{
    Widget       shell, mainWindow, target, tracker;
    XtAppContext app;

   /*
    * Initialize Xt.
    */

    shell = XtAppInitialize ( &app, "Mousetracks",  NULL,  0, 
                              &argc, argv,   NULL,  NULL, 0 );


   /*
    * Create a main window widget, to hold
    * all the other widgets.
    */

    mainWindow = XtCreateManagedWidget ( "mainW", 
                                         xmMainWindowWidgetClass,
                                         shell, NULL, 0 );
   /*
    *  Create the widget in which to track the 
    *  motion of the pointer.
    */

    target = XtCreateManagedWidget ( "target", 
                                     xmDrawingAreaWidgetClass,
                                     mainWindow, NULL, 0 );

    /*
     * Create the mouse tracker.
     */

    tracker = CreateMouseTracker ( mainWindow, target );

    	XtVaSetValues ( mainWindow, XmNworkWindow, target,
                                XmNmessageWindow, tracker,
                                NULL );

    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}
                                    
