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
 * frame.c: Show a typical use of a titled frame.
 ***************************************************/
#include <Xm/Xm.h>
#include <Xm/RowColumn.h>
#include <Xm/ToggleB.h>
#include <Xm/Frame.h>
#include <Xm/Label.h>
#include <Xm/Form.h>

char *buttons[] = { "button1", "button2", "button3", 
                    "button4", "button5", "button6" };

void main ( int argc, char **argv ) 
{
    Widget       shell, rowcol, frame, label, form;
    XtAppContext app;
    int          i;
    
    shell = XtAppInitialize ( &app, "Frame", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );
   /*
    * Create a form to add a margin around the frame
    */

    form = XtCreateManagedWidget ( "form", xmFormWidgetClass, shell,
                                    NULL, 0 );
   /*
    * Create a frame to hold a labeled radio box
    */

    frame = XtCreateManagedWidget ( "frame", xmFrameWidgetClass, form,
                                     NULL, 0 );

    label = XtVaCreateManagedWidget ( "label",  xmLabelWidgetClass,
                                      frame,
                                      XmNchildType,XmFRAME_TITLE_CHILD,
                                      NULL );
   /*
    * Create an XmRowColumn widget configured as a radio box.
    */ 

    rowcol = XmCreateRadioBox ( frame, "rowcol", NULL, 0 );

    XtManageChild ( rowcol );

   /*
    * Create children of the XmRowColumn widget.
    */ 

    for ( i = 0; i < XtNumber ( buttons ); i++ )  
    {
        Widget toggle = 
                      XtCreateManagedWidget ( buttons[i], 
                                              xmToggleButtonWidgetClass,
                                              rowcol, NULL, 0 );
    }

    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

