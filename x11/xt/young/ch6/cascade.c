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

/*****************************************************
 * popupmenu.c: Demonstrate how to create a popup
 *****************************************************/
#include <Xm/Xm.h>
#include <Xm/Label.h>
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>
#include <Xm/Separator.h>
#include <Xm/BulletinB.h>
#include <Xm/CascadeB.h>
#include <stdio.h>
#include "MenuSupport.h"
/*
 * Event handlers and callback functions used in the menu.
 */

static void PostMenu( Widget    w, 
                       XtPointer clientData,
                       XEvent   *event, 
                       Boolean  *flag );

static void SampleCallback( Widget    w, 
                             XtPointer clientData, 
                             XtPointer callData );

void CreatePopupMenu( Widget parent ); /* Utility function */
void CreateCascadingPane( Widget parent ); /* Utility function */

void main( int argc, char ** argv ) 
{
    Widget       shell, bboard;
    XtAppContext app;

   /*
    * Initialize Xt and create a widget
    */
    
    shell = XtAppInitialize(  &app, "Popupmenu", NULL, 0, 
                               &argc, argv, NULL, NULL, 0 );

    bboard = XtCreateManagedWidget( "bboard", 
                                     xmBulletinBoardWidgetClass,
                                     shell, NULL, 0 );
   /*
    * Create the popup menu, to be popped up from the bulletin board
    */

    CreatePopupMenu( bboard );

    XtRealizeWidget( shell );
    XtAppMainLoop( app );
}

static void PostMenu(  Widget    w, 
                        XtPointer clientData, 
                        XEvent    *event, 
                        Boolean   *flag ) 
{
    Widget  menu = ( Widget )  clientData;
    
    if ( event->xbutton.button == Button3 ) 
    {
        
       /*
        * Position the menu over the pointer and post the menu
        */
        
        XmMenuPosition( menu, ( XButtonPressedEvent * ) event );
        XtManageChild( menu );
    }
}

static void SampleCallback( Widget    w,
                             XtPointer clientData,
                             XtPointer callData ) 
{
    printf ( "%s selected\n",  XtName ( w ) );
}

void CreatePopupMenu( Widget parent ) 
{
    Widget menu, button1, button2, button3;

   /*
    * Step 1. Create a popup menu. Add an event handler
    * to the given widget to pop up the menu when
    * a mouse button is pressed.
    */

    menu = XmCreatePopupMenu( parent, "menu", NULL, 0 );

    XtAddEventHandler( parent, ButtonPressMask,  FALSE,
                        PostMenu, menu );

   /*
    * Step 2. Add buttons, labels, and separators to the pane.
    * Step 3. Register callbacks to define the action
    *         associated with each menu entry.
    */

    XtCreateManagedWidget( "Title", xmLabelWidgetClass, menu,
                            NULL, 0 );

    XtCreateManagedWidget( "separator", 
                            xmSeparatorWidgetClass,
                            menu, NULL, 0 );

    button1 = XtCreateManagedWidget( "Item1",xmPushButtonWidgetClass,
                                      menu, NULL, 0 );

    XtAddCallback( button1, XmNactivateCallback, 
                    SampleCallback, NULL );

    button2 = XtCreateManagedWidget( "Item2", xmPushButtonWidgetClass, 
                                      menu, NULL, 0 );

    XtAddCallback( button2, XmNactivateCallback, 
                     SampleCallback, NULL );

    CreateCascadingPane( menu );

    button3 = XtCreateManagedWidget( "Item3", xmPushButtonWidgetClass,
                                      menu, NULL, 0 );

    XtAddCallback( button3, XmNactivateCallback, 
                    SampleCallback, NULL );
}

void CreateCascadingPane( Widget parent )
{
     Widget cascade, submenu, button1, button2;

    /*
     * Create a pulldown menu pane as a child of the given widget
     */

     submenu = XmCreatePulldownMenu( parent, "submenu", NULL, 0 );

    /*
     * Create a cascade button widget as a sibling of the submenu.
     * Attach the menu pane to the cascade button so it will
     * automatically post when the button is selected.
     */

     cascade = XtVaCreateManagedWidget( "Submenu",
                                         xmCascadeButtonWidgetClass,
                                         parent, 
                                         XmNsubMenuId, submenu, 
                                         NULL);
    /*
     * Add buttons and other items to the cascading menu pane.
     */

     button1 = XtCreateManagedWidget( "item1A",xmPushButtonWidgetClass,
                                       submenu, NULL, 0 );

     XtAddCallback( button1, XmNactivateCallback, 
                     SampleCallback, NULL );

     button2 = XtCreateManagedWidget( "item2A",xmPushButtonWidgetClass,
                                       submenu, NULL, 0 );

     XtAddCallback( button2, XmNactivateCallback, 
                     SampleCallback, NULL );
}

