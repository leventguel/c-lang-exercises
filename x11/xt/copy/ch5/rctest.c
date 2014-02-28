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

/**************************************************
 * rctest.c: An example using a row column widget
 **************************************************/
#include <Xm/Xm.h>
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>

char *buttons[] = { "button1", "button2", "button3", 
                    "button4", "button5", "button6" };

void main ( int argc, char **argv ) 
{
    Widget       shell, rowcol;
    XtAppContext app;
    int          i;

    shell = XtAppInitialize ( &app, "Rctest", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );


   /*
    * Create an XmRowColumn widget.
    */ 

    rowcol = XtCreateManagedWidget ( "rowcol", xmRowColumnWidgetClass,
                                     shell, NULL, 0 );

   /*
    * Create the children of the XmRowColumn widget.
    */ 

    for ( i = 0; i < XtNumber ( buttons ); i++ )  
         XtCreateManagedWidget ( buttons[i], xmPushButtonWidgetClass,
                                 rowcol, NULL, 0 );

   XtRealizeWidget ( shell );
   XtAppMainLoop ( app );
}

