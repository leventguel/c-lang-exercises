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

/*******************************************************************
 * editor.c: An example Motif interface used to discuss resources
 *******************************************************************/
#include <Xm/Xm.h>
#include <Xm/DrawingA.h>
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>
#include <Xm/Form.h>

void main ( int argc, char **argv ) 
{
    Widget       shell, canvas, panel, commands, options;
    XtAppContext app;
  
   /*
    * Initialize Xt.
    */

    shell = XtAppInitialize ( &app, "Editor", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

   /*
    * The overall window layout is handled by an XmForm widget.
    */

    panel = XtCreateManagedWidget ( "panel", xmFormWidgetClass, 
                                    shell, NULL, 0 );
   /*
    * An XmRowColumn widget holds the buttons along the top
    * of the window.
    */

    commands = 
      XtVaCreateManagedWidget ( "commands", xmRowColumnWidgetClass,
                                panel,
                                XmNnumColumns,       3,
                                XmNorientation,      XmHORIZONTAL,
                                XmNtopAttachment,    XmATTACH_FORM,
                                XmNrightAttachment,  XmATTACH_FORM,
                                XmNleftAttachment,   XmATTACH_FORM,
                                XmNbottomAttachment, XmATTACH_NONE,
                                NULL );
   /*
    * Another XmRowColumn widget contains a column of buttons
    * along the left side of the window.
    */

    options = 
       XtVaCreateManagedWidget ( "options", xmRowColumnWidgetClass, 
                                 panel,
                                 XmNnumColumns,      1,
                                 XmNorientation,     XmVERTICAL,
                                 XmNtopAttachment,   XmATTACH_WIDGET,
                                 XmNtopWidget,       commands,
                                 XmNrightAttachment, XmATTACH_NONE,
                                 XmNleftAttachment,  XmATTACH_FORM,
                                 XmNbottomAttachment,XmATTACH_FORM,
                                 NULL );
   /*
    * The middle window, in which the application can display
    * text or graphics is an XmDrawingArea widget.
    */

    canvas = 
       XtVaCreateManagedWidget ( "canvas", xmDrawingAreaWidgetClass,
                                 panel,    
                                 XmNtopAttachment,   XmATTACH_WIDGET,
                                 XmNtopWidget,       commands,
                                 XmNrightAttachment, XmATTACH_FORM,
                                 XmNleftWidget,      options,
                                 XmNleftAttachment,  XmATTACH_WIDGET,
                                 XmNbottomAttachment,XmATTACH_FORM,
                                 NULL );

   /*
    * The buttons in the commands and options panels are
    * created as XmPushButton widgets.
    */

    XtCreateManagedWidget ( "button1", xmPushButtonWidgetClass, 
                            commands, NULL, 0 );
    XtCreateManagedWidget ( "button2", xmPushButtonWidgetClass, 
                            commands, NULL, 0 );
    XtCreateManagedWidget ( "button3", xmPushButtonWidgetClass, 
                            commands, NULL, 0 );
    XtCreateManagedWidget ( "button1", xmPushButtonWidgetClass, 
                            options, NULL, 0 );
    XtCreateManagedWidget ( "button2", xmPushButtonWidgetClass, 
                            options, NULL, 0 );
    XtCreateManagedWidget ( "button3", xmPushButtonWidgetClass, 
                            options, NULL, 0 );
  
    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

