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

/********************************************************
 * mousetracker2.c: Track the position of the pointer 
 *                  while the mouse button is held down
 ********************************************************/
#include <Xm/Xm.h>
#include <Xm/Label.h>

static void ShowMousePosition ( Widget     w, 
                                XtPointer  clientData, 
                                XEvent    *event, 
                                Boolean   *flag );

static void TrackMousePosition ( Widget    w,
                                  XtPointer clientData, 
                                  XEvent   *event, 
                                  Boolean   *flag );
static void ClearTracker ( Widget     w, 
                           XtPointer  clientData, 
                           XEvent    *event, 
                           Boolean    *flag );
extern void wprintf ( Widget w, const char * format, ...);

Widget CreateMouseTracker ( Widget parent, Widget target ) 
{
    Widget       tracker;

    /*
     * Create the tracker widget and register event 
     * handlers for the target widget. 
     */

    tracker = XtCreateManagedWidget ( "mousetracker", 
                                      xmLabelWidgetClass,
                                      parent, NULL, 0 );
    wprintf ( tracker, " " );

    XtAddEventHandler ( target, ButtonPressMask, FALSE,
                        ShowMousePosition, ( XtPointer ) tracker );

    XtAddEventHandler ( target, ButtonMotionMask, FALSE,
                        TrackMousePosition, ( XtPointer ) tracker );

    XtAddEventHandler ( target, 
                        ButtonReleaseMask | LeaveWindowMask,
                        FALSE, ClearTracker, ( XtPointer ) tracker );
  
    return ( tracker );
}
                                
static void ShowMousePosition ( Widget     w, 
                                XtPointer  clientData, 
                                XEvent    *event, 
                                Boolean   *flag ) 
{
    Widget  tracker = ( Widget ) clientData;

   /*
    * Extract the position of the pointer from the event
    * and display it in the tracker widget. 
    */

    wprintf ( tracker, "X: %04d, Y: %04d", 
              event->xbutton.x, event->xbutton.y );
}
            
static void TrackMousePosition ( Widget     w, 
                                 XtPointer  clientData, 
                                 XEvent    *event, 
                                 Boolean   *flag ) 
{
    Widget  tracker = ( Widget ) clientData;

   /*
    * Extract the position of the pointer from the event
    * and display it in the tracker widget. 
    */

    wprintf ( tracker, "X: %04d, Y: %04d", 
              event->xmotion.x, event->xmotion.y );
}
            
static void ClearTracker ( Widget     w,
                           XtPointer  clientData,
                           XEvent    *event, 
                           Boolean   *flag ) 
{
    Widget  tracker = ( Widget ) clientData;

   /*  
    * Display an empty string in the tracker widget. 
    */

    wprintf ( tracker, " " );
}
            
