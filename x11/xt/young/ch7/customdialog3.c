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

Widget CreateDialog ( Widget parent, char *name, 
                      XtCallbackProc OkCallback,
                      XtCallbackProc ApplyCallback,
                      XtCallbackProc CancelCallback );

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

    dialog = CreateDialog ( button, "Dialog" , NULL, NULL, NULL );

    XtAddCallback ( button, XmNactivateCallback, 
                    ShowDialogCallback, dialog );
    
    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}
                    
const char *fields[] = {"Name", "Address", "Phone"};

typedef struct {
    Widget name, addr, phone;
} DialogWidgets;

Widget CreateDialog ( Widget parent, char *name, 
                      XtCallbackProc OkCallback,
                      XtCallbackProc ApplyCallback,
                      XtCallbackProc CancelCallback )
{
    Widget         dialog, rc, apply;
    DialogWidgets *widgets;
    int            i;

    widgets = ( DialogWidgets * ) XtMalloc ( sizeof ( DialogWidgets ) );
    
   /*
    * Create the template dialog.
    */

    dialog = XmCreateTemplateDialog ( parent, name, NULL, 0 );
    
   /*
    * Add an apply button if there is a callback
    */

    if ( ApplyCallback )
       apply = XtCreateManagedWidget ( "apply",
                                       xmPushButtonWidgetClass,
                                       dialog, NULL, 0 );
   /*
    * Add callbacks. Note different treatment of apply button
    */

    if ( OkCallback )
        XtAddCallback ( dialog, XmNokCallback, OkCallback, widgets );
    if ( CancelCallback )
        XtAddCallback ( dialog, XmNokCallback,
                        CancelCallback, widgets );
    if ( ApplyCallback )
        XtAddCallback ( apply, XmNactivateCallback,
                        ApplyCallback, widgets );
   /* 
    * Create a manager widget to handle the dialog layout
    */

    rc = XtVaCreateManagedWidget ( "rc", xmRowColumnWidgetClass,dialog,
                                   XmNnumColumns,  2, 
                                   XmNpacking,     XmPACK_COLUMN, 
                                   XmNorientation, XmVERTICAL, 
                                   NULL );
   /*
    * Create the labels
    */

    XtCreateManagedWidget ( "Name", xmLabelWidgetClass, rc, NULL, 0 );
    XtCreateManagedWidget ( "Address", xmLabelWidgetClass,
                            rc, NULL, 0 );
    XtCreateManagedWidget ( "Phone", xmLabelWidgetClass,
                            rc, NULL, 0 );
   /*
    * Create the text input field
    */

    widgets->name = XtCreateManagedWidget ( "name",
                                            xmTextFieldWidgetClass,
                                            rc, NULL, 0);
    widgets->addr = XtCreateManagedWidget ( "addr",
                                            xmTextFieldWidgetClass,
                                            rc, NULL, 0);
    widgets->phone = XtCreateManagedWidget ( "phone",
                                             xmTextFieldWidgetClass,
                                             rc, NULL, 0);

    return dialog;
}
                            

