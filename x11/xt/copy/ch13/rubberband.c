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
 * rubberband.c: rubberband line example
 ***********************************************/
#include <Xm/Xm.h>
#include <X11/cursorfont.h>
#include <Xm/DrawingA.h>

static int startX, startY, lastX, lastY;
static GC  gc;

static void StartRubberBand ( Widget    w, 
                              XtPointer clientData, 
                              XEvent   *event, 
                              Boolean   *flag );
static void EndRubberBand ( Widget     w, 
                            XtPointer  clientData, 
                            XEvent    *event, 
                            Boolean   *flag );
static void TrackRubberBand ( Widget    w, 
                              XtPointer clientData, 
                              XEvent    *event, 
                              Boolean   *flag );
        
void main ( int argc, char **argv )
{
    Widget       shell, canvas;
    XtAppContext app;
    XGCValues    values;
    
    shell = XtAppInitialize ( &app, "Rubberband", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );
   /*
    * Create a drawing surface, and add event handlers for
    * ButtonPress, ButtonRelease and MotionNotify events.
    */
    
    canvas = XtCreateManagedWidget ( "canvas", 
                                     xmDrawingAreaWidgetClass, 
                                     shell, NULL, 0 );
    XtAddEventHandler ( canvas, ButtonPressMask, FALSE,
                        StartRubberBand, NULL );
    XtAddEventHandler ( canvas, ButtonMotionMask, FALSE,
                        TrackRubberBand, NULL );
    XtAddEventHandler ( canvas, ButtonReleaseMask,
                        FALSE, EndRubberBand, NULL );
    
    XtRealizeWidget ( shell );
    
   /*
    * Establish a passive grab, for any button press.
    * Force the mouse cursor to stay within the canvas window,
    * and change the mouse cursor to a cross_hair.
    */
    
    XGrabButton ( XtDisplay ( canvas ), AnyButton, AnyModifier, 
                  XtWindow ( canvas ), TRUE, 
                  ButtonPressMask | ButtonMotionMask | 
                  ButtonReleaseMask,
                  GrabModeAsync, GrabModeAsync,
                  XtWindow ( canvas ), 
                  XCreateFontCursor ( XtDisplay ( canvas ),
                                      XC_crosshair ) );
   /*
    * Create the GC used by the rubber banding functions.
    */
    
    XtVaGetValues ( canvas, 
                    XmNforeground, &values.foreground,
                    XmNbackground, &values.background,
                    NULL );

   /*
    * Set the foreground color to the XOR of the foreground
    * and background colors, so that if an image is drawn 
    * on the background using this GC, it will be displayed as  
    * the foreground color, and vice-versa.
    */
    
    values.foreground = values.foreground ^ values.background;
    
   /*
    * Set the rubber band gc to use XOR mode and draw 
    * a dashed line.
    */
    
    values.line_style = LineOnOffDash;
    values.function   = GXxor;

    gc = XtGetGC ( canvas, GCForeground | GCBackground | 
                           GCFunction | GCLineStyle, 
                           &values );
    
    XtAppMainLoop ( app );
}
                                                        
 static void StartRubberBand ( Widget    w, 
                               XtPointer clientData, 
                               XEvent   *event, 
                               Boolean   *flag )
{
    lastX  = startX = event->xbutton.x;
   lastY  = startY = event->xbutton.y;

   XDrawLine ( XtDisplay ( w ), XtWindow ( w ), 
               gc, startX, startY, lastX, lastY );
}
    
static void TrackRubberBand ( Widget    w, 
                              XtPointer clientData, 
                              XEvent   *event, 
                              Boolean  *flag )
{
   /*
    * Draw once to clear the previous line.
    */
    
    XDrawLine ( XtDisplay ( w ), XtWindow ( w ), gc, 
                startX,startY, 
                lastX, lastY );
    
   /*
    * Update the endpoints.
    */
    
    lastX  =  event->xbutton.x;
    lastY  =  event->xbutton.y;
    
   /*
    * Draw the new line.
    */
    
    XDrawLine ( XtDisplay ( w ), XtWindow ( w ), gc, 
                startX, startY, 
                lastX, lastY );

}
                
static void EndRubberBand ( Widget    w, 
                            XtPointer clientData, 
                            XEvent    *event, 
                            Boolean   *flag )
{
   /*
    * Clear the current line and update the endpoint info.
    */
    
    XDrawLine ( XtDisplay ( w ), XtWindow ( w ), gc, 
                startX, startY, 
                lastX, lastY );
    
    lastX  =  event->xbutton.x;
    lastY  =  event->xbutton.y;

}
        
