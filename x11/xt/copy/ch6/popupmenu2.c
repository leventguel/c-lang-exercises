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
 * popupmenu.c: Demonstrate how to create a popup
 ****************************************************/
#include <Xm/Xm.h>
#include <Xm/BulletinB.h>
#include "MenuSupport.h"

static void SampleCallback ( Widget    w, 
			     XtPointer clientData, 
                             XtPointer callData ) 
/*
 * Setup the menu structure for the cascading menu pane,
 * and then the popup menu pane.
 */

static MenuDescription submenu[] = {
 { LABEL,    "Title" }.
 { SEPARATOR         },
 { BUTTON,    "Item1A", SampleCallback },
 { BUTTON,    "Item2A", SampleCallback },
   END
};

static MenuDescription pane[] = {
 { LABEL,    "Title" }.
 { SEPARATOR         },
 { BUTTON,   "Item1", SampleCallback },
 { BUTTON,   "Item2", SampleCallback },
 { PULLDOWN, "menu",  NULL, NULL, submenu },
 { BUTTON,   "Item3", SampleCallback },
   END
};

void main ( int argc, char ** argv ) 
{
    Widget       shell, bboard;
    XtAppContext app;
    
    shell = XtAppInitialize (  &app, "Popupmenu", NULL, 0, 
                               &argc, argv, NULL, NULL, 0 );

    bboard = XtCreateManagedWidget ( "bboard", 
                                     xmBulletinBoardWidgetClass, 
                                     shell, NULL, 0 );
   /*
    * Create a popup menu, to be popped up from the bulletin board
    */

    CreateMenu ( POPUP, "popup", bboard, pane, NULL );

    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

