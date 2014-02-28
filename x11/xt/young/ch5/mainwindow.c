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

/**********************************************************
 * mainwindow.c: Demonstrate the XmMainWindow widget
 **********************************************************/
#include <Xm/Xm.h>
#include <Xm/RowColumn.h>
#include <Xm/MainW.h>
#include <Xm/Frame.h>
#include <Xm/Label.h>
#include <Xm/ToggleB.h>

 void main ( int argc, char ** argv ) 
{
    XtAppContext app;
    Widget       menu, shell, mainwindow, rowcol, frame, label;
    int          i;
 
   /*
    * Initialize Xt
    */
    
    shell = XtAppInitialize ( &app, "Mainwindow", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

    mainwindow = XtVaCreateManagedWidget ( "mainwindow", 
                                           xmMainWindowWidgetClass,
                                           shell, NULL, 0 );

    frame = XtCreateManagedWidget ( "frame", xmFrameWidgetClass,
                                    mainwindow, NULL, 0 );

    label = XtVaCreateManagedWidget ( "label", xmLabelWidgetClass,
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

    for ( i = 0; i < 4; i++ )  
    {
        Widget toggle = 
                     XtCreateManagedWidget ( "toggle", 
                                             xmToggleButtonWidgetClass,
                                             rowcol, NULL, 0 );
    }

    menu = XmCreateMenuBar ( mainwindow, "menu", NULL, 0 );

   /*
    * Specify the widgets to be used as a work area and menu bar.
    */

    XtVaSetValues ( mainwindow,
                    XmNmenuBar,    menu, 
                    XmNworkWindow, frame,
                    NULL );

    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

