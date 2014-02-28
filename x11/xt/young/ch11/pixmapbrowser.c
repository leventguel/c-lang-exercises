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

/***********************************************************
 * pixmapBrowser.c  Display a selectable set of patterns
 ***********************************************************/
#include <Xm/Xm.h>
#include <Xm/ToggleB.h>
#include <Xm/RowColumn.h>
#include <Xm/MessageB.h>

 static void SelectPixmapCallback ( Widget    w,
                                   XtPointer clientData,
                                   XtPointer callData);
static void OkCallback ( Widget    w,
                         XtPointer clientData,
                         XtPointer callData );

Widget CreatePixmapBrowser ( Widget          parent,   
                             char          **patterns,
                             int             numPatterns,
                             XtCallbackProc  callback )
{
    Widget     browser, dialog;
    int        i;

    dialog = XmCreateTemplateDialog ( parent, "pixmapBrowser",
                                      NULL, 0 );
   /*
    * Create a "RadioBox" RowColumn widget.
    */
    browser = XmCreateRadioBox ( dialog, "pixmapBrowser", NULL, 0 );

    XtManageChild ( browser );
    
   /*
    * Create a button for each pixmap. 
    */
    
    for ( i = 0; i < numPatterns; i++ )
    {
        Pixmap  pixmap;
        Pixel   fg, bg;
        Widget  button;

        button = XtCreateManagedWidget ( patterns[i], 
                                         xmToggleButtonWidgetClass,
                                         browser, NULL, 0 );
       /*
        * Retrieve the colors used by this button
        */

        XtVaGetValues ( button, 
                        XtNforeground, &fg,
                        XtNbackground, &bg,
                        NULL );
       /*
        * Get the pattern using the colors of the toggle
        */

        pixmap = XmGetPixmap  ( XtScreen ( button ), 
                                patterns[i], fg, bg );

       /*
        * Install the pixmap in the toggle button.
        */

        XtVaSetValues ( button,  
                        XmNlabelType,   XmPIXMAP, 
                        XmNlabelPixmap, pixmap, 
                        XmNuserData,    pixmap, 
                        NULL );

       /*
        * Register a callback to be invoked when this pixmap 
        * is selected
        */

        XtAddCallback ( button, 
                        XmNvalueChangedCallback, 
                        SelectPixmapCallback, dialog );
    }

   /*
    * Register a callback to be called when the 
    * user dismisses the dialog. Specify the user-provided 
    * callback as client data.
    */

    XtAddCallback ( dialog, XmNokCallback, 
                    OkCallback, ( XtPointer ) callback );

    return ( dialog );
}                                            

void RegisterBitmap ( Widget w, char *name, char *bits, int width, int height )
{
    XImage *image = 
              XCreateImage ( XtDisplay ( w ),
                              DefaultVisualOfScreen ( XtScreen ( w ) ),
                             1, XYBitmap, 0, 
                             bits, width, height, 8, 2 );

    XmInstallImage ( image, name );
}

 static void SelectPixmapCallback ( Widget    w,
                                    XtPointer clientData,
                                    XtPointer callData )
 {
    Widget dialog =  ( Widget ) clientData;
    XmToggleButtonCallbackStruct *cbs =
                    ( XmToggleButtonCallbackStruct * ) callData;
    Pixmap pixmap;

   /*
    * If this widget has been selected, retrieve the
    * pixmap from the toggle button and store it in the dialog
    * where it can be retrieved by the caller.
    */

    if ( !cbs->set )
       return;

    XtVaGetValues ( w, XmNuserData, &pixmap, NULL );
    XtVaSetValues ( dialog, XmNuserData, pixmap, NULL );
}
            
static void OkCallback ( Widget    w,
                         XtPointer clientData,
                         XtPointer callData )
{
    Pixmap pixmap;
    XtCallbackProc callback =  ( XtCallbackProc ) clientData;

    XtVaGetValues ( w, XmNuserData, &pixmap, NULL );  

    if ( callback )
       ( *callback ) ( w,  ( XtPointer ) pixmap, callData );
}
    
