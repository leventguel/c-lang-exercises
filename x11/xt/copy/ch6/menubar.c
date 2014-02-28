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
 * menubar.c: demonstrate a typical menu bar
 ****************************************************/
#include <Xm/Xm.h>
#include <Xm/RowColumn.h>
#include <Xm/MainW.h>
#include <Xm/PushB.h>
#include <Xm/BulletinB.h>
#include <Xm/CascadeB.h>
#include <Xm/Text.h>

/* Declarations of convenience functions */

Widget CreateMenuBar ( Widget parent );
void   CreateFilePane ( Widget parent );
void   CreateEditPane ( Widget parent );
void   CreateHelpPane ( Widget parent );

/*
 * Stub callback functions. If implemented these would perform
 * an action when the corresponding menu item is selected.
 */

void PasteCallback ( Widget w, XtPointer clientData, XtPointer callData ) 
{
     /* Empty Stub Function */
}

void CutCallback ( Widget w, XtPointer clientData, XtPointer callData ) 
{
     /* Empty Stub Function */
}

void OpenCallback ( Widget w, XtPointer clientData, XtPointer callData ) 
{
     /* Empty Stub Function */
}

void CloseCallback ( Widget w, XtPointer clientData, XtPointer callData ) 
{
     /* Empty Stub Function */
}

void HelpCallback ( Widget w, XtPointer clientData, XtPointer callData )
{
     /* Empty Stub Function */
}


void main ( int argc, char ** argv ) 
{
    XtAppContext app;
    Widget       menu, shell, mainwindow, text;
 
   /*
    * Initialize Xt and create an XmMainWindow widget to handle layout
    */
    
    shell = XtAppInitialize ( &app, "Mainwindow", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

    mainwindow = XtCreateManagedWidget ( "mainwindow", 
                                         xmMainWindowWidgetClass, 
                                         shell, NULL, 0 );

    text = XmCreateScrolledText ( mainwindow, "text", NULL, 0 );
    XtManageChild ( text );

   /* Create the menu bar */

    menu = CreateMenuBar ( mainwindow );

   /*
    * Specify the widgets to be used as a work area and menu bar.
    * Because XmCreateScrolledText() returns a grandchild of
    * its parent, XtParent() must be called to get the true child
    * to be set as the work area.
    */

    XtVaSetValues ( mainwindow,
                    XmNmenuBar,    menu, 
                    XmNworkWindow, XtParent ( text ),
                    NULL );

    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

Widget CreateMenuBar ( Widget parent ) 
{
    Widget menu;

   /*
    *  Create a menu bar and then call additional
    *  menu panes before returning the menu widget.
    */

    menu = XmCreateMenuBar ( parent, "menu", NULL, 0 );

    CreateFilePane ( menu );
   CreateEditPane ( menu );
   CreateHelpPane ( menu );
    
   XtManageChild ( menu );

   return menu;
}

void CreateFilePane ( Widget parent ) 
{
    Widget cascade, submenu, button1, button2;

   /*
    * Create the cascading submenu pane that is popped up when
    * the user clicks on the File cascade button.
    */

    submenu = XmCreatePulldownMenu ( parent, "fileSubmenu", 
                                     NULL, 0 );

   /*
    * Create a cascade button named "File". This is the
    * label seen in the menu bar.
    * Attach the menu pane to the cascade button.
    */

    cascade = XtVaCreateManagedWidget ( "File",
                                        xmCascadeButtonWidgetClass,
                                        parent, 
                                        XmNsubMenuId, submenu,
                                        NULL  );
   /*
    * Add the content of the menu pane.
    */

    button1 = XtCreateManagedWidget ( "Open", xmPushButtonWidgetClass,
                                      submenu, NULL, 0 );

    XtAddCallback ( button1, XmNactivateCallback, 
                    OpenCallback, NULL );

    button2 = XtCreateManagedWidget ( "Close", xmPushButtonWidgetClass,
                                      submenu, NULL, 0 );

    XtAddCallback ( button2, XmNactivateCallback, 
                    CloseCallback, NULL );
}

void CreateEditPane ( Widget parent ) 
{
    Widget cascade, submenu, button1, button2;

    submenu = XmCreatePulldownMenu ( parent, "editSubmenu", NULL, 0 );

    cascade = XtVaCreateManagedWidget ( "Edit",
                                        xmCascadeButtonWidgetClass,
                                        parent, 
                                        XmNsubMenuId, submenu, 
                                        NULL );

    button1 = XtCreateManagedWidget ( "Cut", xmPushButtonWidgetClass,
                                      submenu, NULL, 0 );

    XtAddCallback ( button1, XmNactivateCallback, 
                    CutCallback, NULL );

    button2 = XtCreateManagedWidget ( "Paste",xmPushButtonWidgetClass,
                                      submenu, NULL, 0 );

    XtAddCallback ( button2, XmNactivateCallback, 
                    PasteCallback, NULL );
}

void CreateHelpPane ( Widget parent ) 
{
    Widget cascade, submenu, button1;

   /*
    * Create the pulldown pane
    */

    submenu = XmCreatePulldownMenu ( parent, "helpSubmenu", NULL, 0 );

   /*
    * Create the cascade button from which to pull down the
    * help menu pane.
    */

    cascade = XtVaCreateManagedWidget ( "Help",
                                        xmCascadeButtonWidgetClass,
                                        parent, 
                                        XmNsubMenuId, submenu,
                                        NULL );
   /*
    * Establish this widget as the help menu widget for
    * this menu bar.
    */

    XtVaSetValues ( parent, XmNmenuHelpWidget, cascade, NULL );

   /*
    * Create the help menu items.
    */

    button1 = XtCreateManagedWidget ( "Help", xmPushButtonWidgetClass,
                                      submenu, NULL, 0 );

    XtAddCallback ( button1, XmNactivateCallback, 
                    HelpCallback, NULL );
}

