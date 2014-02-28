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

/******************************************************
 * toggle.c: Demonstrate a Motif toggle button widget
 ******************************************************/
#include <Xm/Xm.h>
#include <Xm/ToggleB.h>
#include <stdio.h>

static void ValueChangedCallback ( Widget    w, 
				   XtPointer clientData, 
                                   XtPointer callData );

void main ( int argc, char **argv )
{
    Widget       shell, toggle;
    XtAppContext app;
    
   /*
    * Initialize Xt
    */
    
    shell = XtAppInitialize ( &app, "Toggle", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );
    
   /*
    * Create an XmToggleButton widget
    */
    
    toggle = XtCreateManagedWidget ( "toggle",
                                     xmToggleButtonWidgetClass,
                                     shell, NULL, 0 );

    XtAddCallback ( toggle, XmNvalueChangedCallback, 
                    ValueChangedCallback, NULL );

   /*
    * Realize the shell and enter the event loop.
    */
    
    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

static void ValueChangedCallback ( Widget    w,
                                   XtPointer clientData, 
                                   XtPointer callData )
{
    XmToggleButtonCallbackStruct *cbs = 
                          ( XmToggleButtonCallbackStruct * ) callData;
   /*
    * Report the new state of the toggle button for which this 
    * callback function was called.
    */

    if ( cbs->set )
        printf ( "button set\n" );
    else
        printf ( "button unset\n" );
}

