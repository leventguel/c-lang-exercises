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

/************************************************************
 * browser.c: a simple test program for the pixmap browser
 ************************************************************/
#include <Xm/Xm.h>
#include <Xm/PushB.h>

static unsigned char fgBitmap[32] = {   /*  foreground */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff  
};

#define fgWidth  16
#define fgHeight 16

static char *patterns[] = { "foreground", 
                            "background",
                            "25_foreground",
                            "50_foreground",
                            "75_foreground",
                            "vertical",
                            "horizontal",
                            "slant_right",
                            "slant_left",
                          };

void PostBrowserCallback ( Widget    w, 
                           XtPointer clientData, 
                           XtPointer callData );
void PixmapSelectedCallback ( Widget    w,
                              XtPointer clientData,
                              XtPointer callData );
extern Widget CreatePixmapBrowser ( Widget         w, 
                                    char         **patterns, 
                                    int            numPatterns, 
                                    XtCallbackProc callback );
extern void RegisterBitmap ( Widget  w, 
                             char   *name,  
                             char   *bits, 
                             int     width,
                             int     height );
Widget button;
            
void main ( int argc, char **argv )
{
    Widget       shell;
    XtAppContext app;
    
    shell = XtAppInitialize ( &app, "Browser", NULL, 0, 
                              &argc, argv, NULL, NULL, 0  );

    button = XtCreateManagedWidget ( "pushme", 
                                     xmPushButtonWidgetClass, 
                                     shell, NULL, 0 );

    XtAddCallback ( button, XmNactivateCallback, 
                    PostBrowserCallback, NULL );
  
    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

void PostBrowserCallback ( Widget    w, 
                           XtPointer clientData, 
                           XtPointer callData )
{
    static Widget pixmapBrowser = NULL;

    /*
     * Create the pixmap browser dialog the first time this function
     * is caled, registering the application-defined pattern first.
     */

    if ( !pixmapBrowser )
    {
        RegisterBitmap ( w, "foreground", fgBitmap,
                         fgWidth, fgHeight );

        pixmapBrowser = CreatePixmapBrowser ( w, patterns,
                                              XtNumber (patterns ), 
                                               PixmapSelectedCallback);
    }
    XtManageChild ( pixmapBrowser );
}
        
void PixmapSelectedCallback ( Widget    w, 
                              XtPointer clientData,
                              XtPointer callData )
{
    Pixmap pixmap = ( Pixmap ) clientData;

    XtVaSetValues ( button,
                    XmNlabelType,   XmPIXMAP,
                    XmNlabelPixmap, pixmap,
                    NULL );
}

