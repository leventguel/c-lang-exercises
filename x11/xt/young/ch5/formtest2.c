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

/******************************************************
 * formtest.c: demonstrate position-based attachments
 ******************************************************/
#include <Xm/Xm.h>
#include <Xm/Form.h>
#include <Xm/PushB.h>

void main ( int argc, char ** argv ) 
{
    Widget       shell, form, button1, button2, button3;
    XtAppContext app;
    int          i;

    shell = XtAppInitialize ( &app, "Formtest", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

   /*
    * Create an XmForm manager widget
    */

    form = XtCreateManagedWidget ( "form", xmFormWidgetClass, 
                                   shell, NULL, 0 );

   /*
    * Create three children of the form. Attachments are specified
    * in a resource file.
    */

    button1 = 
          XtCreateManagedWidget ( "button1",xmPushButtonWidgetClass,
                                   form, NULL, 0 );

    button2 = 
          XtCreateManagedWidget ( "button2", xmPushButtonWidgetClass, 
                                   form, NULL, 0 );

    button3 = 
        XtCreateManagedWidget ( "button3", xmPushButtonWidgetClass, 
                                form, NULL, 0 );

    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

