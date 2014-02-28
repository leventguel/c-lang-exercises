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

/************************************************
 * filedemo.c: Get a file name from the user
 ************************************************/
#include <Xm/Xm.h>
#include <Xm/PushB.h>
#include <Xm/FileSB.h>
#include <stdio.h>

/* Forward declarations of callback functions */

void SelectFileCallback ( Widget    w, 
                          XtPointer clientData, 
                          XtPointer callData );
void CancelCallback ( Widget    w, 
                      XtPointer clientData, 
                      XtPointer callData );

void OKCallback ( Widget    w, 
                  XtPointer clientData, 
                  XtPointer callData );

void main ( int argc, char **argv )
{
    Widget       shell, button;
    XtAppContext app;

   /*
    * Initialize Xt
    */

    shell = XtAppInitialize ( &app, "Filedemo", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );


   /* Create a button and add a callback to launch a dialog */

    button = XtCreateManagedWidget ( "pushme", xmPushButtonWidgetClass,
                                     shell, NULL, 0 );

    XtAddCallback ( button, XmNactivateCallback, 
                    SelectFileCallback, ( XtPointer ) argv[2] );

   /*
    * Realize the shell and enter the event loop.
    */

    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}
                                
void SelectFileCallback ( Widget    w,
                          XtPointer clientData,
                          XtPointer callData)
{
    Widget text = (Widget) clientData;
    static Widget dialog = NULL;

    if ( !dialog )
    {
         dialog = XmCreateFileSelectionDialog ( w, "openFileDialog", 
                                                NULL, 0 );

         XtAddCallback ( dialog, XmNokCallback,
                         OKCallback, NULL );
         XtAddCallback ( dialog, XmNcancelCallback,
                         CancelCallback, NULL );
    }

    XtManageChild ( dialog );
}
    
void OKCallback ( Widget w, XtPointer clientData, XtPointer callData )
{
    XmFileSelectionBoxCallbackStruct *cbs = 
                         ( XmFileSelectionBoxCallbackStruct * ) callData;
    char *fileName;

   /*
    * Remove the widget from the screen.
    */

    XtUnmanageChild ( w );

   /*
    * Retrieve the character string from the compound string format.
    */

    XmStringGetLtoR ( cbs->value, XmFONTLIST_DEFAULT_TAG, &fileName );

   /*
    * For this demo, just echo the selected string to standard out.
    */

    printf ( "Selected file = %s\n", fileName );
}
                
void CancelCallback ( Widget    w,
                      XtPointer clientData,
                      XtPointer callData )
{
    XtUnmanageChild ( w );
}
        
