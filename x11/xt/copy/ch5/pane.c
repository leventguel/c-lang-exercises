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

/***************************************************
 * pane.c: demonstrate an XmPanedWindow widget.
 ***************************************************/
#include <Xm/Xm.h> 
#include <Xm/PanedW.h>
#include <Xm/PushB.h>

void main ( int argc, char **argv )  
{
    Widget shell, button1, button2, button3, pane;
    XtAppContext app;

   shell = XtAppInitialize ( &app, "Pane", NULL, 0, 
                             &argc, argv, NULL, NULL, 0 );

  /* 
   * Create a paned window widget with three children. 
   */ 

   pane =  XtCreateManagedWidget ( "pane", xmPanedWindowWidgetClass,
                                   shell, NULL, 0 );

   button1 =  XtCreateManagedWidget ( "button1",
                                      xmPushButtonWidgetClass,
                                      pane, NULL, 0 );
   button2 =  XtCreateManagedWidget ( "button2",
                                      xmPushButtonWidgetClass,
                                      pane, NULL, 0 );
   button3 =  XtCreateManagedWidget ( "button3", 
                                      xmPushButtonWidgetClass,
                                      pane, NULL, 0 );

   XtRealizeWidget ( shell );
   XtAppMainLoop ( app );
}
