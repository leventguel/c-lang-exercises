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
 * xecute.c: Execute a command if the user confirms
 *****************************************************/
#include <Xm/Xm.h>
#include <Xm/MessageB.h>
#include <stdio.h>
#include <stdlib.h>

/* Declarations of callback functions */

void YesCallback ( Widget w, XtPointer clientData, XtPointer callData );
void NoCallback ( Widget w, XtPointer clientData, XtPointer callData );

void main ( int argc, char **argv )
{
    Widget       shell, mb;
    XtAppContext app;
    XmString     xmstr;
    Dimension    height;

    shell = XtAppInitialize ( &app, "Xecute", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

    if ( argc != 3 ) /* Make sure there are exactly two arguments */
    {
         fprintf (stderr, "Usage:  xecute message-string command\n" );
         exit ( 1 );
    }

   /* Create a simple manager widget to hold the other widgets */

    mb = XtVaCreateManagedWidget ( "bboard", xmMessageBoxWidgetClass,
                                   shell,
                                   XtVaTypedArg, XmNmessageString, 
                                   XmRString, 
                                   argv[1], strlen ( argv[1] ) + 1,
                                   XmNdialogType, XmDIALOG_QUESTION,
                                   NULL );
   /* 
    * Add a callback to each button, for "yes" and "no" 
    * Pass the command to be executed as client data
    */

    XtAddCallback ( mb, XmNokCallback, 
                    YesCallback, ( XtPointer ) argv[2] );

    XtAddCallback ( mb, XmNcancelCallback, 
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
                
