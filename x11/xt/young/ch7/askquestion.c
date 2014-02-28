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

/****************************************************************
 * AskQuestion.c: A function that posts a question dialog and
 *                does not return until the user has responded.
 ****************************************************************/
#include <Xm/Xm.h>
#include <Xm/PushB.h>
#include <Xm/MessageB.h>
#include <stdlib.h>

static void YesCallback ( Widget    w,
                          XtPointer clientData, 
                         XtPointer callData );

Boolean AskQuestion ( Widget parent, char *str )
{
    static int result;
    Widget dialog;

    dialog = XmCreateQuestionDialog ( parent, "question", NULL, 0 );

    XtVaSetValues ( dialog, 
                    XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
                    XtVaTypedArg, XmNmessageString, 
                    XmRString, str, strlen ( str ) + 1,
                    NULL );

   /*
    * Register a callback to be called if the user answers OK.
    * Pass a pointer to the variable "result".
    */

    XtAddCallback ( dialog, XmNokCallback,  
                    YesCallback, ( XtPointer ) &result );

   /*
    * Initialize the result to FALSE. If the user dismisses the dialog
    * in any way other than activating the OK button, the result will
    * be FALSE.
    */

    result = FALSE;

   /*
    * Manage the dialog to display it.
    */

    XtManageChild ( dialog );

   /*
    * Enter an event loop that lasts as long as the dialog is managed.
    * The event loop will be exited when the user dismisses the dialog
    * in any way.
    */

    while ( XtIsManaged ( dialog ) ) 
    {
        XEvent event;

        XtAppNextEvent ( XtWidgetToApplicationContext ( dialog ),
                         &event );

        XtDispatchEvent ( &event );
   }

    /* 
     * Destroy the dialog because it is no longer needed.
     */

     XtDestroyWidget ( dialog );
    /* 
     * Return the value of result, which may have been set by the 
     * YesCallback function.
     */

     return ( result );
}
                                                                
static void YesCallback ( Widget    w,
                          XtPointer clientData,
                          XtPointer callData )
{
    int *result = ( int * ) clientData;

    *result = TRUE;
}
        


void AskQuestionCallback ( Widget    w, 
                          XtPointer clientData, 
                          XtPointer callData )
{

   if(AskQuestion(w, "Do you want to quit?"))
       exit(0);
}

void main ( int argc, char **argv )
{
    Widget       shell, button;
    XtAppContext app;

   /*
    * Initialize Xt
    */

    shell = XtAppInitialize ( &app, "Askquestion", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );


   /* Create a button and add a callback to launch a dialog */

    button = XtCreateManagedWidget ( "Quit", 
                                     xmPushButtonWidgetClass,
                                     shell, NULL, 0 );

    XtAddCallback ( button, XmNactivateCallback, 
                    AskQuestionCallback, NULL );

   /*
    * Realize the shell and enter the event loop
    */

    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}
