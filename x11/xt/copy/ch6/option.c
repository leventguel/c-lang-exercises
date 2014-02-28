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

/***********************************************
 * option.c: Demonstrate an option menu
 ***********************************************/
#include <Xm/Xm.h>
#include <Xm/Label.h>
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>
#include <Xm/Separator.h>
#include <Xm/BulletinB.h>
#include <Xm/CascadeB.h>
#include <stdio.h>

void CreateOptionMenu ( Widget parent );
static void OptionChanged ( Widget    w,
                            XtPointer clientData,
                            XtPointer callData );


void main ( int argc, char ** argv ) 
{
    Widget       shell, bboard;
    XtAppContext app;

   /*
    * Initialize Xt
    */
    
    shell = XtAppInitialize (  &app, "Option", NULL, 0, 
                               &argc, argv, NULL, NULL, 0 );

    bboard = XtCreateManagedWidget ( "bboard", 
                                     xmBulletinBoardWidgetClass, 
                                     shell, NULL, 0 );

    CreateOptionMenu ( bboard );

    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

void CreateOptionMenu ( Widget parent ) 
{
    Widget menu, pane, button1, button2, button3;

   /*
    * Create an option menu
    */

    menu = XmCreateOptionMenu ( parent, "menu", NULL, 0 );

   /*
    * Create a pulldown pane and attach it to the option menu
    */

    pane = XmCreatePulldownMenu ( parent, "pane", NULL, 0 );

    XtVaSetValues ( menu, XmNsubMenuId, pane, NULL ); 

    XtManageChild ( menu );

   /*
    * Add buttons to the pane and register callbacks
    * to define the action associated with each menu entry.
    */

    button1 = XtCreateManagedWidget ( "Red", xmPushButtonWidgetClass,
                                      pane, NULL, 0 );

    XtAddCallback ( button1, XmNactivateCallback, 
                    OptionChanged, NULL );

    button2 = XtCreateManagedWidget ( "Blue", xmPushButtonWidgetClass,
                                      pane, NULL, 0 );

    XtAddCallback ( button2, XmNactivateCallback, 
                    OptionChanged, NULL );

    button3 = XtCreateManagedWidget ( "Green", xmPushButtonWidgetClass,
                                      pane, NULL, 0 );

    XtAddCallback ( button3, XmNactivateCallback, 
                    OptionChanged, NULL );
}

static void OptionChanged ( Widget    w,
                            XtPointer clientData,
                            XtPointer callData ) 
{
    printf ( "%s selected\n", XtName ( w ) );
}

