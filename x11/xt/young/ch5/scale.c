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

/**********************************************
 * scale.c: Demonstrate an XmScale widget
 **********************************************/
#include <Xm/Xm.h>
#include <Xm/Scale.h>
#include <Xm/Separator.h>
#include <Xm/Form.h>
#include <stdio.h>

static void ReportValueCallback ( Widget    w, 
                                  XtPointer clientData, 
                                  XtPointer callData );
static void ClickCallback ( Widget    w, 
                            XtPointer clientData, 
                            XtPointer callData );

void main ( int argc, char **argv ) 
{
    Widget       shell, scale, form;
    XtAppContext app;
    int          i;

   /*
    * Initialize Xt and create a form to hold a scale
    */
    
    shell = XtAppInitialize ( &app, "Scale", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

    form = XtCreateManagedWidget ( "form", xmFormWidgetClass,
                                   shell, NULL, 0 ); 

   /*
    * Create a scale with min = 0, max = 100, and display
    * the current value.
    */
 
    scale = XtVaCreateManagedWidget ( "scale", xmScaleWidgetClass,
                                      form, 
                                      XmNshowValue,  TRUE, 
                                      XmNminimum,       0, 
                                      XmNmaximum,     100, 
                                      XmNscaleHeight, 300, 
                                      NULL );
    
   /*
    * Add one callback to report the value when the slider
    * moves, and another to force the thumb to click to
    * intervals of 10 when dragged.
    */

    XtAddCallback ( scale, XmNvalueChangedCallback, 
                    ReportValueCallback, NULL );
    XtAddCallback ( scale, XmNdragCallback, ClickCallback, NULL );

   /*
    * Add tick marks.
    */

    for ( i = 0; i < 11; i++ ) 
        XtCreateManagedWidget  ( "sep",xmSeparatorWidgetClass,
                                 scale, NULL, 0 );

   /*
    * Realize the shell and enter the event loop.
    */
    
    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

static void ReportValueCallback ( Widget    w, 
                                  XtPointer clientData, 
                                  XtPointer callData ) 
{
    XmScaleCallbackStruct *cbs = ( XmScaleCallbackStruct * ) callData;

    printf ( "value = %d\n", cbs->value );
}

static void ClickCallback ( Widget    w,
                            XtPointer clientData, 
                            XtPointer callData ) 
{
    XmScaleCallbackStruct *cbs =  ( XmScaleCallbackStruct * )  callData;

   /* Round the value to the nearest multiple of 10 */

    int value = ( ( cbs->value + 5 )  / 10 )  * 10;

   /* Move the slider to the rounded value. */

    XmScaleSetValue ( w, value );
}

