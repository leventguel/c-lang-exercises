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
 * busy.c: Demonstrate the use of a work procedure
 *         to unset a busy cursor
 *****************************************************/
#include <Xm/Xm.h>
#include <Xm/PushB.h>
#include <X11/cursorfont.h>
#include <unistd.h>

static void DoTask ( Widget    w, 
                     XtPointer clientData, 
                     XtPointer callData );
static void DisplayBusyCursor ( Widget w );
static Boolean RemoveBusyCursor ( XtPointer clientData );

void main ( int argc, char **argv ) 
{
    Widget   shell, button;
    
    XtAppContext app;
    
   /*
    * Initialize Xt and create a button that starts a long task
    */
    
    shell = XtAppInitialize ( &app, "Busy", NULL,  0, 
                              &argc, argv, NULL, NULL, 0 );

    button = XtCreateManagedWidget ( "pushme", xmPushButtonWidgetClass,
                                     shell, NULL, 0 );

    XtAddCallback ( button, XmNactivateCallback, 
                    DoTask, NULL );

    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

static void DoTask ( Widget w, XtPointer clientData, XtPointer callData ) 
{
    DisplayBusyCursor ( w );

    sleep ( 5 ); /* simulate a long activity */
}
            
void DisplayBusyCursor ( Widget w ) 
{
    static cursor = NULL;

    if ( !cursor ) 
        cursor = XCreateFontCursor ( XtDisplay ( w ), XC_watch );  

    XDefineCursor ( XtDisplay ( w ), XtWindow ( w ), cursor );

    XFlush ( XtDisplay ( w ) );

    XtAppAddWorkProc ( XtWidgetToApplicationContext ( w ), 
                       RemoveBusyCursor, ( XtPointer ) w );
}
    
Boolean RemoveBusyCursor ( XtPointer clientData ) 
{
    Widget w = ( Widget ) clientData;

    XUndefineCursor ( XtDisplay ( w ), XtWindow ( w ) );

    return ( TRUE );
}
        
                
