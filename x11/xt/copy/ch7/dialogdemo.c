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
 * dialogdemo.c: Demonstrate a simple Motif dialog widget
 ***********************************************************/
#include <Xm/Xm.h>
#include <Xm/MessageB.h>
#include <Xm/PushB.h>
#include <stdlib.h>

/* Declarations of callback functions */

void QuitCallback ( Widget    w, 
                    XtPointer clientData, 
                    XtPointer callData );
void ReallyQuitCallback ( Widget    w, 
                          XtPointer clientData, 
                          XtPointer callData );

void main ( int argc, char **argv )
{
    Widget       shell, button;
    XtAppContext app;

   /*
    * Initialize Xt
    */

    shell = XtAppInitialize ( &app, "Dialogdemo", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );


   /* Create a button and add a callback to launch a dialog */

    button = XtCreateManagedWidget ( "Quit", 
                                     xmPushButtonWidgetClass,
                                     shell, NULL, 0 );

    XtAddCallback ( button, XmNactivateCallback, 
                    QuitCallback, NULL );

   /*
    * Realize the shell and enter the event loop
    */

    XtRealizeWidget ( shell );

    XtAppMainLoop ( app );
}
                                
#define QUITMESSAGE "Do you really want to quit?"

void QuitCallback ( Widget    w,
                    XtPointer clientData,
                    XtPointer callData )
{
    static Widget dialog = NULL;

    if ( !dialog )
    {
        dialog = XmCreateQuestionDialog ( w, "dialog", NULL, 0 );

        XtVaSetValues ( dialog, 
                        XtVaTypedArg, XmNmessageString, XmRString, 
                        QUITMESSAGE, strlen ( QUITMESSAGE )+1, 
                        NULL );
        XtAddCallback ( dialog, XmNokCallback,
                        ReallyQuitCallback, NULL );
    }

    XtManageChild ( dialog );
}
    
void ReallyQuitCallback ( Widget    w,
                          XtPointer clientData,
                          XtPointer callData )
{
   exit ( 0 );
}

