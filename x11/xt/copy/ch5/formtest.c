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

/*************************************************
 * formtest.c: demonstrate some XmForm attachments
 *************************************************/
#include <Xm/Xm.h>
#include <Xm/Form.h>
#include <Xm/PushB.h>

void main ( int argc, char ** argv ) 
{
    Widget       shell, form, button1, button2, button3;
    XtAppContext app;
    int          i;

    shell = XtAppInitialize ( &app, "Formtest",  NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

   /*
    * Create an XmForm manager widget
    */

    form = XtCreateManagedWidget ( "form", xmFormWidgetClass, 
                                   shell, NULL, 0 );

   /*
    * Add three XmPushButton widgets to the Form Widget.
    * Set constraint resources for each button, setting up
    * a shape like this:
    *          button one
    *          button two
    *          button three
    */

    button1 = 
          XtVaCreateManagedWidget ( "button1", xmPushButtonWidgetClass,
                                    form, 
                                    XmNtopAttachment,    XmATTACH_FORM,
                                    XmNbottomAttachment, XmATTACH_NONE,
                                    XmNleftAttachment,   XmATTACH_FORM,
                                    XmNrightAttachment,  XmATTACH_FORM,
                                    NULL );

    button2 = 
         XtVaCreateManagedWidget ( "button2", xmPushButtonWidgetClass, 
                                   form, 
                                   XmNtopAttachment,   XmATTACH_WIDGET,
                                   XmNtopWidget,       button1,
                                   XmNbottomAttachment,XmATTACH_NONE,
                                   XmNleftAttachment,  XmATTACH_FORM,
                                   XmNrightAttachment, XmATTACH_FORM,
                                   NULL );

    button3 = 
        XtVaCreateManagedWidget ( "button3", xmPushButtonWidgetClass, 
                                  form, 
                                  XmNtopAttachment,   XmATTACH_WIDGET,
                                  XmNtopWidget,       button2,
                                  XmNbottomAttachment,XmATTACH_FORM,
                                  XmNleftAttachment,  XmATTACH_FORM,
                                  XmNrightAttachment, XmATTACH_FORM,
                                  NULL );
    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

