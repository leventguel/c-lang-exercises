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
 * customdialog.c: Demonstrate a custom dialog
 ***************************************************/
#include <Xm/Xm.h>
#include <Xm/Label.h>
#include <Xm/RowColumn.h>
#include <Xm/TextF.h>
#include <Xm/PushB.h>
#include <Xm/MessageB.h>

Widget CreateDialog ( Widget parent, char *name );

static void ShowDialogCallback ( Widget    w, 
                                 XtPointer clientData, 
                                 XtPointer callData )
{
    Widget     dialog = ( Widget ) clientData;

    XtManageChild ( dialog );
}

void main ( int argc, char **argv )
{
    Widget       shell, button, dialog;
    XtAppContext app;

   /*
    * Initialize Xt
    */

    shell = XtAppInitialize ( &app, "Customdialog", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );
    
    button = XtCreateManagedWidget ( "button", xmPushButtonWidgetClass,
                                     shell, NULL, 0);

   /*
    * Create a popup dialog and a register a callback
    * function to display the dialog when the button is activated.
    */

    dialog = CreateDialog ( button, "Dialog" );

    XtAddCallback ( button, XmNactivateCallback, 
                    ShowDialogCallback, dialog );
    
    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

const char *fields[] = {"Name", "Address", "Phone"};

Widget CreateDialog ( Widget parent, char *name )
{
    Widget dialog, rc;
    int    numFields = XtNumber ( fields );
    int    i;

   /*
    * Create the dialog widget.
    */

    dialog = XmCreateMessageDialog ( parent, name, NULL, 0 );

   /*
    * Remove unnneeded children.
    */

    XtUnmanageChild ( XmMessageBoxGetChild ( dialog, 
                                            XmDIALOG_SYMBOL_LABEL ) );
    XtUnmanageChild ( XmMessageBoxGetChild ( dialog,
                                             XmDIALOG_MESSAGE_LABEL ) );
   /*
    * Create a manager widget as a child of the dialog, to be used
    * as the work area of the dialog, replacing the label and icon.
    */

    rc = XtVaCreateManagedWidget ( "rc", xmRowColumnWidgetClass,dialog,
                                   XmNnumColumns,  2, 
                                   XmNpacking,     XmPACK_COLUMN, 
                                   XmNorientation, XmVERTICAL, 
                                   NULL );
   /*
    * Create children of the manager.
    */

    for ( i=0; i < numFields; i++ )
       XtCreateManagedWidget ( fields [i], xmLabelWidgetClass,
                               rc, NULL, 0 );
    for ( i=0; i < numFields; i++ )
       XtCreateManagedWidget ( fields [i], xmTextFieldWidgetClass,
                               rc, NULL, 0);
    return dialog;
}

