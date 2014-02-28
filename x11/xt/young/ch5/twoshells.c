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
 * twoshells.c: Demonstrate use of shells in a 
 *              multi-window program
 **************************************************/
#include <Xm/Xm.h> 
#include <Xm/MainW.h> 

void main ( int argc, char **argv )
{
    Widget       hiddenShell, shell1, shell2;
    XtAppContext app;
  
   /*
    * Initialize Xt
    */
  
    hiddenShell = XtVaAppInitialize ( &app, "Twoshells", NULL, 0, 
                                      &argc, argv, NULL, 
                                      XmNmappedWhenManaged, FALSE,
                                      NULL );
  
    XtRealizeWidget ( hiddenShell );
  
   /*
    * Create two TopLevelShell widgets as popups. 
    */
  
    shell1= XtCreatePopupShell ( "shell1", topLevelShellWidgetClass,
                                 hiddenShell, NULL, 0 );
  
    shell2 = XtCreatePopupShell ( "shell2", topLevelShellWidgetClass,
                                  hiddenShell, NULL, 0 );
  
   /*
    * Create children of each shell.
    */
  
    XtCreateManagedWidget ( "Widget", xmMainWindowWidgetClass, 
                            shell1, NULL, 0 );
  
    XtCreateManagedWidget ( "Widget2", xmMainWindowWidgetClass, 
                            shell2, NULL, 0 );
  
   /* 
    * Popup the shells to display them.
    */

    XtPopup ( shell1, XtGrabNone );
    XtPopup ( shell2, XtGrabNone );
  
   XtAppMainLoop ( app );
}
 
