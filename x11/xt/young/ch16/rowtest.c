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

/*******************************************
 * rowtest.c : Demo the Row widget class
 *******************************************/
#include <Xm/Xm.h>
#include <Xm/PushB.h>
#include <Xm/PushBG.h> 
#include "Row.h"

static void  GrowCallback ( Widget, XtPointer, XtPointer ); 
static void  UnmanageCallback ( Widget, XtPointer, XtPointer ); 
static void  ManageCallback ( Widget, XtPointer, XtPointer ); 

void main ( int argc, char **argv )
{
    Widget       shell, row;
    Widget       button1, button2, button3, button4;
    XtAppContext app;

   /*
    * Initialize Xt.
    */

    shell = XtAppInitialize ( &app, "RowTest", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );    
   /*
    * Create a Row widget.
    */

    row = XtCreateManagedWidget ( "row", xsRowWidgetClass,
                                  shell, NULL, 0 );

   /*
    * Add children to the Row widget.
    */

    button1 = XtCreateManagedWidget ( "button1",
                                      xmPushButtonGadgetClass,
                                      row, NULL, 0 );

    button2 = XtCreateManagedWidget ( "button2",
                                      xmPushButtonWidgetClass,
                                      row, NULL, 0 );

    button3 = XtCreateManagedWidget ( "button3",
                                       xmPushButtonWidgetClass,
                                       row, NULL, 0 );

    button4 = XtCreateManagedWidget ( "button4",
                                       xmPushButtonWidgetClass,
                                       row, NULL, 0);

    XtAddCallback ( button1, XmNactivateCallback,
                    GrowCallback, NULL );
    XtAddCallback ( button2, XmNactivateCallback,
                    UnmanageCallback, NULL );
    XtAddCallback ( button3, XmNactivateCallback,
                    ManageCallback, ( XtPointer ) button2 );
    XtAddCallback ( button4, XmNactivateCallback,
                    GrowCallback, NULL );

    XtRealizeWidget ( shell );

    XtAppMainLoop ( app ); 
}
                        
static void GrowCallback ( Widget    w, 
                           XtPointer clientData, 
                           XtPointer callData)
{
    Dimension  width, height;

   /*
    *  Get the current width and height of the widget.
    */

    XtVaGetValues ( w, 
                    XmNwidth,  &width,
                    XmNheight, &height,
                    NULL );
   /*
    * Increment the width and height by 10 pixels before
    * setting the size.
    */

    width  +=10;
    height +=10;

    XtVaSetValues ( w, 
                    XmNwidth,  width,
                    XmNheight, height,
                    NULL );

}
            
void UnmanageCallback ( Widget    w,
                        XtPointer clientData,
                        XtPointer callData)
{
    XtUnmanageChild ( w );
}

void ManageCallback ( Widget    w,
                      XtPointer clientData,
                     XtPointer callData )
{
    Widget button = ( Widget ) clientData;

    XtManageChild ( button );
}

