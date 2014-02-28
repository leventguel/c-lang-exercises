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
 * editor.c: Drawing editor user interface module
 ****************************************************/
#include <Xm/Xm.h>
#include <Xm/MainW.h>
#include <Xm/DrawingA.h>
#include <Xm/MessageB.h>
#include <Xm/Protocols.h>
#include <X11/cursorfont.h>
#include <stdlib.h>
#include "MenuSupport.h"
#include "draw.h"

extern void  PasteItem(void);
extern void  CutSelectedItem(void);
extern void  CopySelectedItem(void);  

/* 
 * Callbacks used by menu items.
 */

static void QuitCallback ( Widget    w, 
                           XtPointer clientData, 
                           XtPointer callData );
static void SaveCallback ( Widget    w, 
                           XtPointer clientData, 
                           XtPointer callData );
static void LoadCallback ( Widget    w, 
                           XtPointer clientData, 
                           XtPointer callData );
static void CopyCallback ( Widget    w, 
                           XtPointer clientData, 
                           XtPointer callData );
static void CutCallback ( Widget    w, 
                          XtPointer clientData, 
                          XtPointer callData );
static void PasteCallback ( Widget    w, 
                            XtPointer clientData, 
                            XtPointer callData );

static void SetFigureCallback ( Widget    w, 
                                XtPointer clientData, 
                                XtPointer callData );
static void SetColorCallback ( Widget    w, 
                               XtPointer clientData, 
                               XtPointer callData );

/*
 * Declare external functions called from this module
 */

extern void XmRepTypeInstallTearOffModelConverter ( void );
extern void SetDrawingFunction ( int type );
extern void SetCurrentColor ( Pixel pixel );
extern void LoadData ( void );
extern void SaveData ( void );
extern InitGraphics ( Widget w );

/*
 * Descriptions of contents of the menu bar. See Chapter 6
 */

static MenuDescription drawingCommandsDesc[] = {
  { TOGGLE,   "None",       SetFigureCallback, ( XtPointer ) NONE   },
  { TOGGLE,   "Line",       SetFigureCallback, ( XtPointer ) LINE   },
  { TOGGLE,   "Circle",     SetFigureCallback, ( XtPointer ) CIRCLE },
  { TOGGLE,   "Rectangle",   
                          SetFigureCallback, ( XtPointer ) RECTANGLE },
  { TOGGLE,   "FilledRectangle",
                     SetFigureCallback, ( XtPointer ) FILLEDRECTANGLE },
  { TOGGLE,   "FilledCircle",
                        SetFigureCallback, ( XtPointer ) FILLEDCIRCLE },
  { NULL }
};

static MenuDescription colorDesc[] = {
  { TOGGLE,   "Black",   SetColorCallback },
  { TOGGLE,   "White",   SetColorCallback },
  { TOGGLE,   "Red",     SetColorCallback },
  { TOGGLE,   "Green",   SetColorCallback },
  { TOGGLE,   "Blue",    SetColorCallback },
  { TOGGLE,   "Magenta", SetColorCallback },
  { TOGGLE,   "Cyan",    SetColorCallback },
  { NULL }
};

static MenuDescription filePaneDesc[] = {
  { BUTTON,   "Save",            SaveCallback },
  { BUTTON,   "Load",            LoadCallback },
  { SEPARATOR                                 },
  { BUTTON,   "Quit",            QuitCallback },
  { NULL }
};

 static MenuDescription editPaneDesc[] = {
  { BUTTON,   "Copy",   CopyCallback  },
  { BUTTON,   "Cut",    CutCallback   },
  { BUTTON,   "Paste",  PasteCallback },
  { NULL }
};
 
static MenuDescription helpPaneDesc[] = {
  { BUTTON,   "HelpOnContext",   ContextHelpCallback },
  { NULL }
};

static MenuDescription menuBarDesc[] = {
  { PULLDOWN,        "File",   NULL, NULL, filePaneDesc },
  { PULLDOWN,        "Edit",   NULL, NULL, editPaneDesc },
  { RADIOPULLDOWN,   "Colors", NULL, NULL, colorDesc    },
  { RADIOPULLDOWN,   "DrawingCommands",
                               NULL, NULL, drawingCommandsDesc    },
  { HELPPANE,        "Help",   NULL, NULL, helpPaneDesc   },
  { NULL }
};
                    
Widget CreateDrawingEditor ( Widget parent )
{
    Widget canvas, mainWindow;

   /*
    * Install the tear-off type converter to allow
    * the tear-off model to be set in a resource file.
    */

    XmRepTypeInstallTearOffModelConverter();

   /*
    * Create a main window widget to handle the layout
    * for the drawing editor.
    */
    
    mainWindow = XtCreateManagedWidget ( "mainWindow", 
                                         xmMainWindowWidgetClass, 
                                         parent, NULL, 0 );
   /*
    * Add a menu bar to the window. Pass the main window widget
    * as the default client, needed primarily by the help callback.
    */

    CreateMenu ( MENUBAR, "menuBar", mainWindow,
                 menuBarDesc, ( XtPointer ) mainWindow );

   /*
    * Create the widget used as a drawing surface 
    */
    
    canvas = XtCreateManagedWidget ( "canvas",
                                     xmDrawingAreaWidgetClass, 
                                     mainWindow, NULL, 0 );
   /*
    * Initialize the display list and other related functions.
    */
    
    InitGraphics ( canvas );
    
    return mainWindow;
}
                                        
static void QuitCallback ( Widget    w, 
                           XtPointer clientData,
                           XtPointer callData )
{
     exit ( 0 );
}
    
static void SaveCallback ( Widget    w, 
                           XtPointer clientData,
                           XtPointer callData )
{
    SaveData();
}
    
static void LoadCallback ( Widget    w,
                           XtPointer clientData,
                           XtPointer callData )
{
    LoadData();
}
    
static void SetColorCallback ( Widget    w,
                               XtPointer clientData,
                               XtPointer callData )
{
    Widget     widget = XtParent ( w );
    Display   *dpy  = XtDisplay ( w );
    int        scr    = DefaultScreen ( dpy );
    Colormap   cmap   = DefaultColormap ( dpy, scr );
    XColor     color, ignore;
    XmToggleButtonCallbackStruct *cbs =
                         ( XmToggleButtonCallbackStruct * ) callData;

   /* 
    * Allocate the color named by the name of the widget that
    * invoked this callback and call SetCurrentColor to install
    * the resulting pixel and the current color.
    */

    if ( cbs->set &&
         XAllocNamedColor ( dpy, cmap, XtName ( w ), 
                            &color, &ignore ) )
        SetCurrentColor ( color.pixel );
}
                    
static void SetFigureCallback ( Widget    w, 
                                XtPointer clientData,
                                XtPointer callData )
{
    unsigned char command =  ( unsigned char ) clientData;
    XmToggleButtonCallbackStruct *cbs =
                         ( XmToggleButtonCallbackStruct * ) callData;
   /*
    * Set the current command from the parameter passed as clientData
    */

    if ( cbs->set )
        SetDrawingFunction ( command );
}
        
    
static void CopyCallback ( Widget    w,
                           XtPointer clientData, 
                           XtPointer callData )
{
    CopySelectedItem();
}

static void CutCallback ( Widget    w,
                          XtPointer clientData,
                          XtPointer callData )
{
    CutSelectedItem();
}

static void PasteCallback ( Widget    w, 
                            XtPointer clientData,
                            XtPointer callData )
{
    PasteItem();
}

