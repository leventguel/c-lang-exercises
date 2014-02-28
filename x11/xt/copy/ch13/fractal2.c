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

/******************************************************************
 * fractal.c: main window and rendering code for a version of the
 *            fractal program that allows the user to select
 *            a region for closer viewing using rubberbanding
 ******************************************************************/
#include <Xm/Xm.h> 
#include <Xm/DrawingA.h> 
#include <Xm/MainW.h> 
#include <stdlib.h>
#include "MenuSupport.h"
#include "fractal.h"

extern ShowPreferences ( Widget parent, ImageData *data );

static void InitData ( Widget w, ImageData *data );

static void ResizeCallback ( Widget    w, 
                             XtPointer clientData,
                             XtPointer callData );
static void RedisplayCallback ( Widget    w, 
                                XtPointer clientData,
                                XtPointer callData );
static void ShowPreferencesCallback ( Widget    w, 
                                      XtPointer clientData,
                                      XtPointer callData );
static void QuitCallback ( Widget    w, 
                           XtPointer clientData,
                           XtPointer callData );
/*
 * Functions that can be called from preference module
 */

void CreateImage ( ImageData *data );
void SetupColorMap ( Widget shell, ImageData *data, Boolean ramp );

/*
 * Menu descriptions used by this program.
 */

static MenuDescription appPaneDesc[] = {
  { BUTTON,   "Preferences", ShowPreferencesCallback },
  { BUTTON,   "Quit",        QuitCallback },
  { NULL }
};

static MenuDescription menuBarDesc[] = {
  { PULLDOWN,   "Application", NULL, NULL, appPaneDesc },
  { NULL }
};

static void StartRubberBand ( Widget    w,
                              XtPointer clientData,
                              XEvent   *event,
                              Boolean  *flag );

static void TrackRubberBand ( Widget    w, 
                              XtPointer clientData,
                              XEvent   *event,
                              Boolean  *flag );

static void EndRubberBand ( Widget    w,
                            XtPointer clientData,
                            XEvent   *event,
                            Boolean   *flag );

static int startX, startY, lastX, lastY;
                            
void main ( int argc, char **argv ) 
{
    Widget       shell, canvas, mainWindow, menu;
    XtAppContext app;
    ImageData    data;

   /*
    * Initialize Xt
    */
    
    shell = XtAppInitialize ( &app, "Fractal", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

    mainWindow = XtCreateManagedWidget ( "mainWindow", 
                                         xmMainWindowWidgetClass, 
                                         shell, NULL, 0 );
   /*
    * Create the widget in which to display the fractal
    */
    
    canvas = XtCreateManagedWidget ( "canvas", 
                                     xmDrawingAreaWidgetClass, 
                                     mainWindow, NULL, 0 );

   /*
    * Create the GCs needed by the fractal program.
    */

    InitData ( canvas, &data );  

   /*
    * Create the menu bar and set up the window layout.
    */

    menu = CreateMenu ( MENUBAR, "menuBar",
                        mainWindow, menuBarDesc, &data );

    XtVaSetValues ( mainWindow,
                    XmNmenuBar,    menu,
                    XmNworkWindow, canvas, 
                    NULL );
   /*
    * Add callbacks to handle resize and exposures.
    */

    XtAddCallback ( canvas, XmNexposeCallback,
                    RedisplayCallback,  ( XtPointer ) &data ); 
    XtAddCallback ( canvas, XmNresizeCallback,
                    ResizeCallback, ( XtPointer )  &data ); 
   /*
    * Add event handlers to track the mouse and allow
    * the user to select a region with rubberband rectangle.
    */

    XtAddEventHandler ( canvas, ButtonPressMask, FALSE,
                        StartRubberBand, &data );
    XtAddEventHandler ( canvas, ButtonMotionMask, FALSE,
                        TrackRubberBand, &data );
    XtAddEventHandler ( canvas, ButtonReleaseMask, FALSE,
                        EndRubberBand, &data );

    XtRealizeWidget ( shell );

   /*
    * Once all widgets are realized, call an auxiliary function to
    * install a colormap in the canvas window, so the fractal can
    * be displayed with a full range of colors.
    */

    SetupColorMap( shell, &data, FALSE ); 

    XtAppMainLoop ( app );
}

static void InitData ( Widget w, ImageData *data ) 
{
    XGCValues values;

    /*
     * Get the size of the drawing area.
     */
    
     XtVaGetValues ( w,  
                     XmNwidth,  &data->width, 
                     XmNheight, &data->height, 
                     XmNbackground, &values.foreground,
                     NULL );

     data->canvas      = w;
     data->depth       = 20;
     data->origin.real = -1.4;
     data->origin.imag = 1.0;
     data->range       = 2.0;
     data->maxDistance = 4.0;
     data->coloration  = ITERATIONS;

    /*
     * Find out how many colors we have to work with, and  
     * create a default, writable, graphics context.
     */
    
     data->ncolors = 
                 XDisplayCells ( XtDisplay ( w ), 
                                 XDefaultScreen ( XtDisplay ( w ) ) );
    
     data->gc = XCreateGC ( XtDisplay ( w ),
                            DefaultRootWindow ( XtDisplay ( w ) ),
                            NULL, NULL ); 
   /*
    * Create a second GC set to XOR mode to use in the rubberbanding
    * functions that select a region into which to zoom.
    */

    values.function = GXxor;

    data->xorGC = XtGetGC ( w, 
                            GCForeground | GCFunction, 
                            &values );

    /*
     *  Initialize the pixmap to NULL.
     */
    
     data->pixmap = NULL;

}
                            
static void StartRubberBand ( Widget    w,
                              XtPointer clientData,
                              XEvent   *event,
                              Boolean  *flag )
{
    lastX = startX = event->xbutton.x;
    lastY = startY = event->xbutton.y;
}
    
static void TrackRubberBand ( Widget    w, 
                              XtPointer clientData,
                              XEvent   *event,
                              Boolean  *flag )
{
    int height;    
    ImageData *data = ( ImageData* ) clientData;

   /*
    * If a non-zero sized rectangle has been previously drawn,
    * erase it by drawing again in XOR mode.
    */

    if ( lastX - startX > 0 || lastY - startY > 0 )
        XDrawRectangle ( XtDisplay ( w ), XtWindow ( w ), data->xorGC,
                         startX, startY, 
                         lastX - startX, lastY -startY );
   /*
    * Update the last point. Force an aspect ratio that 
    * matches the shape of the window
    */
        
    lastX  =  event->xmotion.x;

    height = data->height * ( lastX - startX ) / data->width;

    lastY  =  startY + height;

    if ( lastX < startX )
        lastX = startX;

    if ( lastY < startY )
        lastY = startY;    
   /*
    * Draw the new rectangle in XOR mode so it can easily be erased.
    */

    XDrawRectangle ( XtDisplay ( w ), XtWindow ( w ), data->xorGC,
                     startX, startY, 
                     lastX - startX, lastY - startY );
}
                        
static void EndRubberBand ( Widget    w,
                            XtPointer clientData,
                            XEvent   *event,
                            Boolean   *flag )
{
    int height;
    ImageData *data = ( ImageData* ) clientData;

    /*
    * If a non-zero sized rectangle has been previously drawn,
    * erase it by drawing again in XOR mode.
    */

    if ( lastX - startX > 0 || lastY - startY > 0 )
        XDrawRectangle ( XtDisplay ( w ), XtWindow ( w ) , data->xorGC,
                         startX, startY, 
                         lastX - startX, lastY -startY );
    
   /*
    * Update the last point. Force an aspect ratio that 
    * matches the shape of the window
    */
        
    lastX  = event->xmotion.x;
    height = data->height * ( lastX - startX ) / data->width;

    lastY  =  startY + height;
   
   /*
    * Unless a non-zero sized region was selected, just return.
    */

    if ( lastX <= startX || lastY <= startY )
        return;
   /*
    * Convert the pixel-based corrdinates to the real coordinates
    * used to compute the fractal image.
    */

    data->origin.real += data->range * 
                        ( double ) startX / ( double ) data->width;
    data->origin.imag -= data->range *
                        ( double )  startY / ( double ) data->height;
    data->range = data->range * 
               ( double ) ( lastX - startX ) / ( double ) data->width;
   /*
    * Create a new image, based on the newly selected range and
    * origin. Also update the preference panel so it stays in sync.
    */

    CreateImage ( data );
    UpdatePreferences ( data );
}
                                        
static void ShowPreferencesCallback ( Widget    w,  
                                      XtPointer clientData, 
                                      XtPointer callData ) 
{
    ImageData *data = ( ImageData * ) clientData;
    
   /* Call external function to display pereference panel. */

    ShowPreferences ( XtParent ( w ), data );
}
            
static void QuitCallback ( Widget    w,  
                           XtPointer clientData, 
                           XtPointer callData ) 
{
    exit ( 0 );
}
    
void CreateImage ( ImageData *data ) 
{
    Widget w = data->canvas;
    int  x, y, iteration;

   /*
    * If the canvas is realized, erase it.
    */

    if ( XtIsRealized ( w ) ) 
        XClearArea ( XtDisplay ( w ), XtWindow ( w ), 
                     0, 0, 0, 0, TRUE );

   /*
    * Erase the pixmap by filling it with black.
    */

    XSetForeground ( XtDisplay ( w ), data->gc,
                     BlackPixelOfScreen ( XtScreen ( w ) ) );
  
    XFillRectangle ( XtDisplay ( w ), data->pixmap, data->gc, 0, 0, 
                     data->width,  data->height );
    
   /*
    * For each pixel on the window....
    */
    
    for ( y = 0; y < data->height; y++ ) 
    {
        ComplexNumber z, k;
            
        for ( x = 0; x < data->width; x++ ) 
        {
           /*
            * Initialize K to the normalized, floating coordinate
            * in the x, y plane. Init Z to ( 0.0, 0.0 ) .
            */
            
            z.real =  z.imag = 0.0;
            
            k.real =  data->origin.real + 
                ( double ) x / ( double ) data->width * data->range;
            k.imag =  data->origin.imag - 
                ( double ) y / ( double ) data->height * data->range;

           /*
            * Calculate z =  z * z + k over and over.
            */
            
              for ( iteration = 0; iteration < data->depth; iteration++)
            {
                double   real;
                int      distance;
                
                real   = z.real;
                z.real = z.real * z.real - z.imag * z.imag + k.real;
                z.imag = 2 * real * z.imag + k.imag;

                distance  =  ( int ) ( z.real * z.real + 
                                       z.imag * z.imag );
                
               /*
                * If the z point has moved off the plane, set the 
                * current foreground color to the distance (cast to 
                * an int and modulo the number of colors available),
                * and draw a point in the window and the pixmap.
                */
                
                if ( distance  >= data->maxDistance ) 
                {
                    Pixel color;

                    if ( data->coloration == DISTANCE ) 
                        color = ( Pixel ) ( distance % data->ncolors );
                    else if ( data->coloration == ITERATIONS ) 
                        color = ( Pixel ) iteration % data->ncolors;
                    
                    XSetForeground ( XtDisplay ( w ), 
                                     data->gc, color );

                    XDrawPoint ( XtDisplay ( w ),
                                 data->pixmap,
                                 data->gc, x, y );
                    if ( XtIsRealized ( w ) ) 
                        XDrawPoint ( XtDisplay ( w ),
                                     XtWindow ( w ), 
                                     data->gc,x,y );
                    break;
                }
            }
        }
    }
}
                                            
static void RedisplayCallback ( Widget    w, 
                                XtPointer clientData, 
                                XtPointer callData ) 
{
    ImageData                   *data = ( ImageData * ) clientData;
    XmDrawingAreaCallbackStruct *cb = 
                            ( XmDrawingAreaCallbackStruct * ) callData;
    
    XExposeEvent  *event = ( XExposeEvent * ) cb->event;
    
   /*
    * Extract the exposed area from the event and copy
    * from the saved pixmap to the window.
    */
    
    XCopyArea ( XtDisplay ( w ), data->pixmap,
                XtWindow ( w ), data->gc, 
                event->x, event->y, event->width, event->height, 
                event->x, event->y );
}
            
static void ResizeCallback ( Widget    w,
                             XtPointer clientData,
                             XtPointer callData ) 
{
    ImageData     *data = ( ImageData * ) clientData;

   /*
    *  Get the new window size.
    */
    
    XtVaGetValues ( w, 
                    XmNwidth,  &data->width,
                    XmNheight, &data->height,
                    NULL );
   /*
    * Clear the window, forcing an Expose event to be generated
    */
    
    if ( XtIsRealized ( w ) ) 
        XClearArea ( XtDisplay ( w ), XtWindow ( w ), 0, 0, 0, 0, TRUE );
    
   /*
    *  Free the old pixmap and create a new pixmap 
    *  the same size as the window.
    */
    
    if ( data->pixmap ) 
        XFreePixmap ( XtDisplay ( w ), data->pixmap );
    
    data->pixmap = 
           XCreatePixmap ( XtDisplay ( w ),
                           DefaultRootWindow ( XtDisplay ( w ) ),
                           data->width, data->height, 
                           DefaultDepthOfScreen ( XtScreen ( w ) ) );
    
    XSetForeground ( XtDisplay ( w ), data->gc,
                     BlackPixelOfScreen ( XtScreen ( w ) ) );
    
    XFillRectangle ( XtDisplay ( w ), data->pixmap, data->gc, 0, 0, 
                     data->width,  data->height );
    
   /*
    * Generate a new image.
    */
    
    CreateImage ( data );
}
                        
void SetupColorMap ( Widget shell, ImageData *data, Boolean ramp )
{
    int          red, green, blue, i;
    Display     *dpy = XtDisplay ( shell );
    XColor      *Colors;
    static Colormap  cmap = NULL;
    Window      windows [ 2 ];    
    
   /*
    * The first time, create a colormap and install it in the
    * canvas widget's window. Also set up the window manager
    * colormap windows list so both colormaps get installed,
    * if the system is capable of handling multiple colormaps.
    */
    
    if ( !cmap )
    {
        cmap = 
            XCreateColormap ( dpy, XtWindow(data->canvas),
                              DefaultVisual(dpy, DefaultScreen(dpy)),
                              AllocAll );

        XSetWindowColormap ( dpy, XtWindow ( data->canvas ), cmap );
        windows[0] = XtWindow ( shell );
        windows[1] = XtWindow ( data->canvas );    
        XSetWMColormapWindows ( dpy, XtWindow ( shell ), windows, 2 ); 
    }
    
    if ( ramp )
    {
       /*
        * If a ramp is to be set up, allocate enough colors
        * cells. Then fill in the cells with some computed colors.
        * This ramp runs from yellow to red.
        */

        Colors = ( XColor* ) XtMalloc ( sizeof ( XColor ) * 
                                        data->ncolors );
        
        Colors[0].pixel = 0;
        Colors[0].flags = DoRed|DoGreen|DoBlue;
        Colors[0].red   = Colors[0].blue = Colors[0].green =
	    BlackPixel(dpy, 0);
        green = 65535;
        
        for ( i = 1; i < data->ncolors; i++ )
        {
            Colors[i].pixel = i;
            Colors[i].flags = DoRed|DoGreen|DoBlue;
            Colors[i].red   = 65535;
            Colors[i].blue  = 0;
            Colors[i].green = green ;
            green          -= green / 8;
        }

       /*
        * install the color ramp in the canvas's colormap.
        */

        XStoreColors ( dpy, cmap, Colors, data->ncolors );
        
        XtFree ( (char *) Colors );
    }
    else
    {
        Colormap def;
        
       /*
        * If no ramp is chosen, just use whatever randomw colors
        * are in the default map. Copy the contents of the default
        * colormap to the canvas widget's colormap.
        */

        Colors = ( XColor* ) XtMalloc ( sizeof ( XColor ) *
                                        data->ncolors );
        def = DefaultColormap ( dpy, DefaultScreen ( dpy ) );

        for ( i = 0; i < data->ncolors; i++ )
        {
            Colors[i].pixel = i;
            Colors[i].flags = DoRed|DoGreen|DoBlue;
        }

        XQueryColors ( dpy, def, Colors, data->ncolors );
        
        XStoreColors ( dpy, cmap, Colors, data->ncolors );
        
        XtFree ( ( char * ) Colors );        
    }
}
