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

/****************************************************
 * layout.c: Demonstrate typical XmForm attachments
 ****************************************************/
#include <Xm/Xm.h>
#include <Xm/Form.h>
#include <Xm/PushB.h>
#include <Xm/Label.h>
#include <Xm/RowColumn.h>
#include <Xm/Text.h>
#include <Xm/ToggleB.h>

void main ( int argc, char ** argv ) 
{
    Widget       shell, form, button, button1, button2, text, 
                 options, label;
    XtAppContext app;
    int          i;

    shell = XtAppInitialize ( &app, "Layout",  NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

   /*
    * Create an XmForm manager widget
    */

    form = XtCreateManagedWidget ( "form", xmFormWidgetClass, 
                                   shell, NULL, 0 );
   /*
    * Create a label, attached to the upper left corner of the form
    */

    label = 
       XtVaCreateManagedWidget ( "label", xmLabelWidgetClass,
                                 form, 
                                 XmNalignment, XmALIGNMENT_BEGINNING,
                                 XmNleftAttachment,   XmATTACH_FORM,
                                 XmNtopAttachment,    XmATTACH_FORM,
                                 XmNrightAttachment,  XmATTACH_NONE,
                                 XmNbottomAttachment, XmATTACH_NONE,
                                 XmNleftOffset,       10, 
                                 NULL ) ;
   /*
    * Create the row of buttons along the bottom. The first button
    * serves as an anchor, attaching to the bottom left corner
    * while setting an offset from left and bottom for visual
    * aesthetics. All other buttons are forced to align top and
    * bottom with this first button, and are attached in order.
    */

    button = 
         XtVaCreateManagedWidget ( "button", xmPushButtonWidgetClass,
                                   form, 
                                   XmNtopAttachment,    XmATTACH_NONE,
                                   XmNbottomAttachment, XmATTACH_FORM,
                                   XmNbottomOffset,     10,
                                   XmNleftAttachment,   XmATTACH_FORM,
                                   XmNleftOffset,       10,
                                   XmNrightAttachment,  XmATTACH_NONE,
                                   NULL );
    
    button1 = 
        XtVaCreateManagedWidget ( "button1", xmPushButtonWidgetClass,
                        form, 
                        XmNtopAttachment,    XmATTACH_OPPOSITE_WIDGET,
                        XmNtopWidget,        button,
                        XmNbottomAttachment, XmATTACH_OPPOSITE_WIDGET,
                        XmNbottomWidget,     button,
                        XmNleftAttachment,   XmATTACH_WIDGET,
                        XmNleftWidget,       button,
                        XmNrightAttachment,  XmATTACH_NONE, 
                        NULL ) ;

    button2 = 
        XtVaCreateManagedWidget ( "button2", xmPushButtonWidgetClass,
                        form,
                        XmNtopAttachment,    XmATTACH_OPPOSITE_WIDGET,
                        XmNtopWidget,        button,
                        XmNbottomAttachment, XmATTACH_OPPOSITE_WIDGET,
                        XmNbottomWidget,     button,               
                        XmNleftAttachment,   XmATTACH_WIDGET,
                        XmNleftWidget,       button1,
                        XmNrightAttachment,  XmATTACH_NONE,
                        NULL ) ;

   /*
    * Create a row column widget to hold a column of toggle buttons.
    * Make the top of the row column aline with the bottom of the 
    * label, attach the right edge to the form, and let the left
    * side float. The bottom needs to be attached to the top of the
    * row of buttons so the two can’t overlay each other.
    */

    options = 
       XtVaCreateManagedWidget ( "options", xmRowColumnWidgetClass,
                                 form,
                                 XmNtopAttachment,    XmATTACH_WIDGET,
                                 XmNtopWidget,        label,
                                 XmNbottomAttachment, XmATTACH_NONE,
                                 XmNleftAttachment,   XmATTACH_NONE,
                                XmNrightAttachment,  XmATTACH_FORM,
                                XmNbottomAttachment, XmATTACH_WIDGET,
                                XmNbottomWidget,     button,
                                NULL );
   /*
    * Add some toggle buttons to the rwo column widget. These
    * are not involved in the form constraints.
    */

    for ( i = 0 ; i < 4; i++ )
         XtCreateManagedWidget ( "toggle", xmToggleButtonWidgetClass,
                                 options, NULL, 0 ) ;
   /*
    * Attach the text widget to the label on the top, to the form
    * on the left, to the option row column on the right, and to
    * the top of the buttons on the bottom. Becase the text widget is
    * the only widget attached on all four sides, this widget 
    * stretches when the form is resized.
    */

    text = 
      XtVaCreateManagedWidget ( "text", xmTextWidgetClass, form, 
                                XmNtopAttachment,    XmATTACH_WIDGET,
                                XmNtopWidget,        label,
                                XmNbottomAttachment, XmATTACH_WIDGET,
                                XmNbottomWidget,     button1, 
                                XmNleftAttachment,   XmATTACH_FORM,
                                XmNleftOffset,       10,
                                XmNrightAttachment,  XmATTACH_WIDGET,
                                XmNrightWidget,      options,
                                NULL );
    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

