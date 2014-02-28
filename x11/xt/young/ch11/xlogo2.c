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

/*****************************************************************
 * xlogo.c: First example of manipulating and displaying pixmaps
 *****************************************************************/
#include <Xm/Xm.h>
#include <Xm/DrawingA.h>
#include <X11/Xutil.h>
#include <X11/bitmaps/xlogo64>

static void RedisplayCallback ( Widget, XtPointer, XtPointer );
static void ResizeCallback ( Widget, XtPointer, XtPointer  );
static void InstallPixmap ( Widget w );

Pixmap xlogoPixmap;
GC     gc;
void main ( int argc, char **argv )
{
    Widget       shell, canvas;
    XtAppContext app;

    shell = XtAppInitialize ( &app, "Xlogo", NULL, 0, 
                              &argc, argv, NULL, NULL, 0  );
    
   /*
    * Create a widget in which to display the logo.
    */
    
    canvas = XtCreateManagedWidget ( "canvas", 
                                     xmDrawingAreaWidgetClass,
                                     shell, NULL, 0 );
    InstallPixmap ( canvas );

    XtRealizeWidget ( shell );

    XtAppMainLoop ( app );
}
            
static void InstallPixmap ( Widget w )
{
    XGCValues    values;

   /*
    * Use the foreground and background colors
    * of the canvas to create a graphics context.
    */
    
    XtVaGetValues ( w, 
                    XmNforeground, &values.foreground, 
                    XmNbackground, &values.background, 
                    NULL );
    
    gc = XtGetGC ( w, GCForeground | GCBackground, &values );
    
   /*
    * Create the bitmap of the X logo. 
    */
    
    xlogoPixmap = 
           XCreateBitmapFromData ( XtDisplay ( w ), 
                                   RootWindowOfScreen ( XtScreen (w)),
                                   xlogo64_bits,
                                   xlogo64_width,
                                   xlogo64_height );
   /*
    * Register callbacks to display the pixmap and keep it
    * centered in the XmDrawingArea widget.
    */
 
   XtAddCallback ( w, XmNexposeCallback, RedisplayCallback,  NULL );
   XtAddCallback ( w, XmNresizeCallback, ResizeCallback,     NULL );
}   
                                                                
static void RedisplayCallback  ( Widget w,
                                 XtPointer clientData,
                                 XtPointer callData )
{
    Dimension width, height;

   /* 
    * Get the current size of the widget window.
    */
    XtVaGetValues ( w,  
                    XmNwidth,  &width, 
                    XmNheight, &height,
                    NULL  );
    
   /*
    * Copy plane 1 of the bitmap to the center
    * of the window, using the widget's foreground 
    * and background color.
    */
    
    XCopyPlane ( XtDisplay ( w ), xlogoPixmap, XtWindow ( w ),
                 gc, 0, 0,  xlogo64_width, xlogo64_height, 
                 ( width - xlogo64_width ) / 2,  
                 ( height - xlogo64_height ) / 2, 1 );
}
                                            
static void ResizeCallback ( Widget    w,
                             XtPointer clientData,
                             XtPointer callData )
{
    if ( XtIsRealized ( w ) )
        XClearArea ( XtDisplay ( w ), 
                     XtWindow ( w ), 
                     0, 0, 0, 0, TRUE );
}
    
