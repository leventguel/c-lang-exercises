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

/**************************************************************
 * traverse.c: simple example for experimenting with keyboard
 *             traversal between tab groups
 **************************************************************/
#include <Xm/Xm.h>
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>

char *buttons_one[] = { "button1", "button2", "button3" };
char *buttons_two[] = { "button4", "button5", "button6" };

void main ( int argc, char **argv ) 
{
    Widget       shell, rowcol, box1, box2;
    int          i;
    XtAppContext app;

   /*
    * Initialize Xt
    */
    
    shell = XtAppInitialize ( &app, "Traverse",   NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

   /*
    * Create an XmRowColumn widget with two children, each
    * of which are XmRowColumn widgets as well. Each widget 
    * will be in its own tab group.
    */

    rowcol = XtCreateManagedWidget ( "rowcol", xmRowColumnWidgetClass,
                                     shell, NULL, 0 );

    box1 = XtCreateManagedWidget ( "box1", xmRowColumnWidgetClass,
                                   rowcol, NULL, 0 );

    box2 = XtCreateManagedWidget ( "box2", xmRowColumnWidgetClass,
                                   rowcol, NULL, 0 );
   /*
    * Create three children of each XmRowColumn widget.
    */ 

    for ( i = 0;i < XtNumber ( buttons_one ); i++ )   
        XtCreateManagedWidget ( buttons_one[i], xmPushButtonWidgetClass,
                                box1, NULL, 0 );

    for ( i = 0;i < XtNumber ( buttons_two ); i++ )   
        XtCreateManagedWidget ( buttons_one[i], xmPushButtonWidgetClass,
                                box2, NULL, 0 );
    
    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

