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

/******************************************************************
 * xecute.c: Execute a command after the user confirms the action
 ******************************************************************/
#include <Xm/Xm.h>
#include <Xm/Label.h>
#include <Xm/PushB.h>
#include <Xm/BulletinB.h>
#include <stdlib.h>
#include <stdio.h>

/* Declarations of callback functions */

void YesCallback ( Widget w, XtPointer clientData, XtPointer callData );
void NoCallback ( Widget w, XtPointer clientData, XtPointer callData );

void main ( int argc, char **argv )
{
    Widget       shell, msg, bb, yes, no;
    XtAppContext app;
    XmString     xmstr;
    Dimension    height;

   /*
    * Initialize Xt
    */

    shell = XtAppInitialize ( &app, "Xecute", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

    if ( argc != 3 ) /* Make sure there are exactly two arguments */
    {
         fprintf (stderr, "Usage:  xecute message-string command\n" );
         exit ( 1 );
    }

   /* Create a simple manager widget to hold the other widgets */

    bb = XtVaCreateManagedWidget ( "bboard", xmBulletinBoardWidgetClass,
			                                   shell, NULL );

   /* Convert the first argument to the form expected by Motif */

    xmstr = XmStringCreate ( argv[1], XmFONTLIST_DEFAULT_TAG );

   /* Create a label widget as a child of the bulletinboard */

    msg = XtVaCreateManagedWidget ( "message", xmLabelWidgetClass,bb, 
                                    XmNlabelString, xmstr,
                                    XmNx, 0,
                                    XmNy, 0,
                                    NULL );

   /* 
    * Retrieve the height of the label widget, so we know
    * where to place the buttons 
    */

    XtVaGetValues ( msg, XmNheight, &height, NULL );

   /*
    * Create two button widgets for "yes" and "no"
    */

    yes = XtVaCreateManagedWidget ( "yes", xmPushButtonWidgetClass, bb, 
                                   XmNx, 0,
	                                   XmNy, height + 20,
                                   NULL );


    no = XtVaCreateManagedWidget ( "no", xmPushButtonWidgetClass, bb, 
                                   XmNx, 200,
	                                   XmNy, height + 20,
                                   NULL );

   /* 
    * Add a callback to each button, for "yes" and "no" 
    * Pass the command to be executed as client data
    */

    XtAddCallback ( yes, XmNactivateCallback, 
                    YesCallback, ( XtPointer ) argv[2] );

    XtAddCallback ( no, XmNactivateCallback, 
                    NoCallback, NULL );

   /*
    * Realize the shell and enter the event loop.
    */

    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

void YesCallback ( Widget w, XtPointer clientData, XtPointer callData )
{
     /* Cast the clientdata to the expected command string */

    char * cmd = (char *) clientData;

    if ( cmd )
        system ( cmd ); /* Execute the command */

     exit ( 0 ); 
}

void NoCallback ( Widget w, XtPointer clientData, XtPointer callData)
{
    /* No action is necessary, just exit. */

    exit ( 0 );
}

