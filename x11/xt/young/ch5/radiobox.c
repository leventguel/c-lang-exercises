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

/**********************************************************
 * radiobox.c: Demonstrate the Motif radio box behavior
 **********************************************************/
#include <Xm/Xm.h>
#include <Xm/RowColumn.h>
#include <Xm/ToggleB.h>
#include <stdio.h>

char * buttons[] = { "button1", "button2", "button3", 
                     "button4", "button5", "button6" };

static void ValueChangedCallback ( Widget    w, 
                                   XtPointer clientData, 
                                   XtPointer callData );

void main ( int argc, char **argv ) 
{
    Widget       shell, rowcol;
    XtAppContext app;
    int          i;

    shell = XtAppInitialize ( &app, "Radio", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );


   /*
    * Create an XmRowColumn widget configured as a radio box.
    */ 

    rowcol = XmCreateRadioBox ( shell, "rowcol", NULL, 0 );

    XtManageChild ( rowcol );

   /*
    * Create the children of the XmRowColumn widget.
    */ 

    for ( i = 0; i < XtNumber ( buttons ); i++ )  
    {
        Widget toggle = 
                      XtCreateManagedWidget ( buttons[i], 
                                              xmToggleButtonWidgetClass,
                                              rowcol, NULL, 0 );
        XtAddCallback ( toggle, XmNvalueChangedCallback, 
                        ValueChangedCallback, NULL );
    }

    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

static void ValueChangedCallback ( Widget    w, 
                                   XtPointer clientData, 
                                   XtPointer callData ) 
{
    XmToggleButtonCallbackStruct *cbs =
                             ( XmToggleButtonCallbackStruct * )  callData;

    printf ( "%s: %s\n", XtName ( w ) , cbs->set ? "set" : "unset" );
}

