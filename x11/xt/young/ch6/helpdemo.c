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
 * helpdemo.c: Demonstrate context-sensitive help
 *****************************************************/
#include <Xm/Xm.h>
#include <Xm/MainW.h>
#include <Xm/PushB.h>
#include "MenuSupport.h"

static MenuDescription helpPane[] = {
{ BUTTON,    "HelpOnContext", ContextHelpCallback },
  END
};

static MenuDescription menuBar[] = {
 { HELPPANE, "Help",  NULL, NULL, helpPane },
   END
};

void main ( int argc, char ** argv ) 
{
    Widget       shell, mainWindow, button, help, menu;
    XtAppContext app;
    
    shell = XtAppInitialize (  &app, "Helpdemo", NULL, 0, 
                               &argc, argv, NULL, NULL, 0 );

    mainWindow = XtCreateManagedWidget ( "mainWindow", 
                                         xmMainWindowWidgetClass, 
                                         shell, NULL, 0 );

    XtAddCallback ( mainWindow, XmNhelpCallback,
                    ContextHelpCallback, mainWindow );
   /*
    * Create a menubar. Specify the bulletion board as default 
    * client data for the help menu callback.
    */

    menu =  CreateMenu ( MENUBAR, "menubar",  
                         mainWindow, menuBar, mainWindow );

    button = XtCreateManagedWidget ( "button", xmPushButtonWidgetClass,
                                     mainWindow, NULL, 0 );
    XtVaSetValues ( mainWindow, XmNmenuBar,    menu, 
                                XmNworkWindow, button,
                                NULL );

    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

