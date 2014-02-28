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
 * graphics.c: A display list that holds graphics objects
 *             and associated functions needed to
 *             display objects in a drawing area widget
 ***********************************************************/
#include <Xm/Xm.h>
#include <Xm/FileSB.h>
#include <stdio.h>
#include "draw.h"
#include <Xm/CutPaste.h> 
#include <Xm/DragDrop.h>

#define MAXOBJECTS 1000 /* The most objects the displayList can hold */

#define circle_width 16
#define circle_height 16
static unsigned char circle_bits[] = {
   0xc0, 0x01, 0x30, 0x06, 0x0c, 0x18, 0x04, 0x10, 0x02, 0x20, 0x02, 0x20,
   0x01, 0x40, 0x01, 0x40, 0x01, 0x40, 0x02, 0x20, 0x02, 0x20, 0x04, 0x10,
  0x0c, 0x18, 0x30, 0x06, 0xc0, 0x01, 0x00, 0x00};

#define filledcircle_width 16
#define filledcircle_height 16
static unsigned char filledcircle_bits[] = {
   0xf0, 0x07, 0xf8, 0x0f, 0xfc, 0x1f, 0xfe, 0x3f, 0xff, 0x7f, 0xff, 0x7f,
   0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xfe, 0x3f,
  0xfc, 0x1f, 0xf8, 0x0f, 0xf0, 0x07, 0x00, 0x00};

#define rectangle_width 16
#define rectangle_height 16
static unsigned char rectangle_bits[] = {
  0x00, 0x00, 0xfe, 0x7f, 0x02, 0x40, 0x02, 0x40, 0x02, 0x40, 0x02, 0x40,
  0x02, 0x40, 0x02, 0x40, 0x02, 0x40, 0x02, 0x40, 0x02, 0x40, 0x02, 0x40,
  0x02, 0x40, 0x02, 0x40, 0xfe, 0x7f, 0x00, 0x00};

#define filledrect_width 16
#define filledrect_height 16
static unsigned char filledrect_bits[] = {
   0x00, 0x00, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f,
   0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f,
  0xfe, 0x7f, 0xfe, 0x7f, 0xfe, 0x7f, 0x00, 0x00};

#define line_width 16
#define line_height 16
static unsigned char line_bits[] = {
   0x03, 0x00, 0x06, 0x00, 0x0c, 0x00, 0x18, 0x00, 0x30, 0x00, 0x60, 0x00,
   0xc0, 0x00, 0x80, 0x01, 0x00, 0x03, 0x00, 0x06, 0x00, 0x0c, 0x00, 0x18,
  0x00, 0x30, 0x00, 0x60, 0x00, 0xc0, 0x00, 0x80};

Atom   GRAPHICS_OBJECT = NULL;
Atom   TARGETS         = NULL;
Widget dragIcon;
Pixmap dragBitmap;

static void HandleDrop ( Widget    w, 
                         XtPointer clientData, 
                         XtPointer callData );
static void HandleDrag ( Widget    w, 
                         XtPointer clientData, 
                         XtPointer callData );
static void StartDrag ( Widget    w, 
                        XtPointer clientData,
                        XEvent   *event,
                        Boolean  *continueToDispatch );
static void TransferCallback ( Widget         w,
                        XtPointer      clientData,
                        Atom          *seltype,
                        Atom          *type,
                        XtPointer      value,
                        unsigned long *length,
                        int           *format );
static Boolean ExportObject ( Widget        w, 
                       Atom         *selection, 
                       Atom         *target, 
                       Atom          *type,
                       XtPointer     *value,
                       unsigned long *length,
                       int           *format );
static void SetDragIcon ( int type );

 
/*
 * Define a standard type for for all drawing function used in this 
 * module to allow all operation to be invoked with the same API.
 */

typedef void ( *DrawingFunction ) ( Window, GC, int, int, int, int );

/*
 * Define a data structure that describes a single visible 
 * object in the display list.
 */

typedef struct{
    int             x1, y1, x2, y2;
    DrawingFunction func;
    int             figureType;
    Pixel           foreground;
    GC              gc;
} GraphicsObject;

/*
 * The display list is just an array of GraphicsObjects
 */

GraphicsObject displayList[MAXOBJECTS];

/*
 * Various variables used within this module. All are global to
 * functions in this file, but static, so as to be hidden from
 * functions in other parts of the program.
 */

static int              nextSlot        = 0;    /* Next free spot 
                                                   in displayList */
static GraphicsObject  *currentObject   = NULL;/* Pointer to currently
                                                   selected object */
static DrawingFunction  currentFunction = NULL; /* Function that draws
                                                   current figure type */
static int              currentFigureType  = 0; /* Current figure type
                                                   being drawn. */
static Display         *display         = NULL;
static Colormap         colormap;
static GC               currentGC       = NULL;
static GC               xorGC           = NULL;
static Pixel            currentForeground = 0;
static Pixel            background      = 0;
static Widget           canvas          = NULL;
Position startX = 0, startY = 0, lastX = 0, lastY = 0;

/*
 * Functions that draw each figure type using the same arguments
 */

static void  DrawLine ( Window, GC, int, int, int, int );
static void  DrawCircle ( Window, GC, int, int, int, int );
static void  DrawRectangle ( Window, GC, int, int, int, int );
static void  DrawFilledCircle ( Window, GC, int, int, int, int );
static void  DrawFilledRectangle ( Window, GC, int, int, int, int );
void FixDataOrdering ( int *x, int *y, int *x2, int *y2 );

/*
 * Functions for "flattening" and "unflattening" an object
 */

static GraphicsObject *Unpack ( char *str );
static char           *Pack ( GraphicsObject *object );

/*
 * Callback functions
 */

 static void Redisplay ( Widget    w, 
                         XtPointer clientData, 
                         XtPointer callData );

 static void StartRubberBand ( Widget     w, 
                               XtPointer  clientData, 
                               XEvent    *event, 
                               Boolean   *flag );
 static void TrackRubberBand ( Widget     w, 
                               XtPointer  clientData, 
                               XEvent    *event, 
                               Boolean   *flag );
 static void EndRubberBand ( Widget     w, 
                             XtPointer  clientData, 
                             XEvent    *event, 
                             Boolean   *flag );
 static void LoadDataCallback ( Widget    w, 
                               XtPointer  clientData, 
                               XtPointer  callData );
static void CancelDialogCallback ( Widget     w, 
                                   XtPointer  clientData, 
                                   XtPointer  callData );
static void SaveDataCallback ( Widget     w, 
                               XtPointer  clientData, 
                               XtPointer  callData );
/*
 * Functions for storing, removing, moving and picking objects
 * in the display list.
 */

static void AddObject (  GraphicsObject *object );
static void StoreObject ( void );
static void MoveObject ( GraphicsObject *object, int x, int y );
static GraphicsObject *PickObject ( int x, int y );

void RemoveItem ( GraphicsObject *object );
void CutSelectedItem (void );
void PasteItem (void );
void CopySelectedItem (void );

extern void CopyToClipBoard(void);
extern void CopyFromClipBoard(void);

 void InitGraphics ( Widget w )
{
    XGCValues values;
    Arg       args[10];
    Atom      targets[1];
    int       n;

   /* 
    * Remember the given widget for use by other functions.
    * Retrieve the display and colormap for later use.
    */

    canvas = w; 
    
    display = XtDisplay ( canvas );
    XtVaGetValues ( canvas, XmNcolormap, &colormap, NULL );

    GRAPHICS_OBJECT = XInternAtom ( display, "GraphicsObject", 
                                    FALSE );

    TARGETS = XInternAtom (  display, "TARGETS", FALSE );
    
    targets[0] = GRAPHICS_OBJECT;
    
    n = 0;
    XtSetArg ( args[n], XmNdropSiteOperations, XmDROP_COPY ); n++;
    XtSetArg ( args[n], XmNimportTargets,      targets ); n++;
    XtSetArg ( args[n], XmNnumImportTargets,   1 ); n++;
    XtSetArg ( args[n], XmNdropProc,           HandleDrop ); n++;
    
    XmDropSiteRegister ( canvas, args, n );
    
   /*
    * Register a callback to redraw the display list when the
    * window is exposed, and event handlers to handle adding
    * new objects to the display list interactively
    */

    XtAddCallback ( canvas, XmNexposeCallback, Redisplay, NULL );
    
    XtAddEventHandler ( canvas, ButtonPressMask, FALSE,
                        StartRubberBand, NULL );
    XtAddEventHandler ( canvas, ButtonPressMask, FALSE,
                        StartDrag, NULL );
    XtAddEventHandler ( canvas, ButtonMotionMask, FALSE,
                        TrackRubberBand, NULL );
    XtAddEventHandler ( canvas, ButtonReleaseMask, FALSE,
                        EndRubberBand, NULL );
   /*
    * Get the colors of the canvas. 
    */
    
    XtVaGetValues ( canvas, 
                    XmNforeground, &currentForeground,
                    XmNbackground, &background,
                    NULL );
   /*
    * Fill in the values structure
    */  
    
    values.foreground = currentForeground ^ background;
    values.function   = GXxor;
    
   /*
    * Set the rubber band gc to use XOR 
    */
    
    xorGC =  XtGetGC ( canvas, 
                       GCForeground | GCFunction, 
                       &values );
} 
                                            
static void HandleDrop ( Widget    w, 
                         XtPointer clientData, 
                         XtPointer callData )
{
    XmDropProcCallbackStruct *cb = 
                            ( XmDropProcCallbackStruct * ) callData;
    Arg        args[10];
    int        n = 0;
    static XPoint          dropPosition;
    XmDropTransferEntryRec transfer_entries[2];
    
   /*
    * Check to see if the user asked for help. This function should 
    * provide some help information, but for this demo, just indicate
    * that the drop is invalid and return.
    */

    if ( cb->dropAction == XmDROP_HELP )
    {
         cb->dropSiteStatus = XmINVALID_DROP_SITE;
         return;
    }

   /*
    * Make sure that this is a drop and that the drop action
    * can be a copy. If not, indicate failure and that no 
    * transfers should be made.
    */

    if  ( cb->dropAction != XmDROP || cb->operation  != XmDROP_COPY )
    {
        n = 0;
        cb->operation      = XmDROP_NOOP;
        cb->dropSiteStatus = XmINVALID_DROP_SITE;
        XtSetArg ( args[n], XmNtransferStatus,
                            XmTRANSFER_FAILURE ); n++;
        XtSetArg ( args[n], XmNnumDropTransfers, 0 ); n++;
    }
    else
    {
       /*
        * If this is a valid drop, find out what types of data the
        * initiator is supporting.
        */

        Atom *targets;
        int   numTargets;
        int   i;
        
        XtVaGetValues ( cb->dragContext,
                        XmNexportTargets,    &targets,
                        XmNnumExportTargets, &numTargets,
                        NULL );
       /*
        * Loop through each exported type, checking to see if there 
        * is type we are interested in. In this case, the only 
        * supported type is GRAPHICS_OBJECT.
        */

        for ( i = 0; i < numTargets; i++ )
            if ( targets[i] == GRAPHICS_OBJECT )
            {
               /*
                * Fill in a structure that can be used to remember
                * the location of the drop so the Transfer callback
                * can positon the object in the right place.
                */

                dropPosition.x =  cb->x;
                dropPosition.y =  cb->y;
                
               /*
                * Initialize the transfer information.
                */

                transfer_entries[0].target = GRAPHICS_OBJECT;
                transfer_entries[0].client_data = &dropPosition;
                
                XtSetArg ( args[n], XmNdropTransfers,
                                    transfer_entries ); n++;
                XtSetArg ( args[n], XmNnumDropTransfers, 1 ); n++;

               /*
                * Specify that TransferCallback should be called
                * when the data has actually been transferred.
                */

                XtSetArg ( args[n], XmNtransferProc, 
                                    TransferCallback ); n++;
                cb->operation = XmDROP_COPY;
                break;
            }
    }
    
   /*
    * Notify the intiator to start the transfer.
    */

    XmDropTransferStart ( cb->dragContext, args, n );
}
                                                                            
static void TransferCallback ( Widget         w,
                               XtPointer      clientData,
                               Atom          *seltype,
                               Atom          *type,
                               XtPointer      value,
                               unsigned long *length,
                               int           *format )
{
    if ( value )
    {
        int width, height;
        
       /*
        * Get the point at which the drop occurred, and
        * unpack the transferred data to create a GraphicsObject.
        */

        XPoint *dropPosition =  ( XPoint * ) clientData;
        GraphicsObject *object = Unpack ( ( char * ) value );

       /*
        * Adjust the location of the object to match the 
        * drop site location.
        */
        
        width    = object->x2 - object->x1;
        height   = object->y2 - object->y1;
        
        object->x1 = dropPosition->x;
        object->y1 = dropPosition->y;
        object->x2 = object->x1 + width;
        object->y2 = object->y1 + height;

       /*
        * Add the object to the display list.
        */
        
        AddObject ( object );
    }
}
                        
static void StartDrag ( Widget    w,
                        XtPointer clientData,
                        XEvent   *event,
                        Boolean  *continueToDispatch )
{

    Widget drag_context;
    Arg    args[10];
    int    n;
    Atom   targets[1];
    Pixmap icon;
    GraphicsObject *item;

    if ( event->xbutton.button != Button2 )
       return;

   /*
    * Find the object under the pointer.
    */

    item = PickObject ( event->xbutton.x,
                        event->xbutton.y );
    
    if ( !item )
       	return;

   /*
    * Set the global variable, dragIcon, to a pixmap that 
    * represents the type of object being dragged.
    */

    SetDragIcon ( item->figureType );

   /* 
    * Indicate the types of data we can transfer.
    */

    targets[0] = GRAPHICS_OBJECT;

   /*
    * Set up the arguments to the drag. Specify a function to
    * be called to export the object, provide a drag icon,
    * and specify the supported data types.Also indicate
    * that a drop will only result in a copy and pass the
    * object being dragged as client data so that it is available
    * to ExportObject() when it is called.
    */


    n = 0;
    XtSetArg ( args[n], XmNconvertProc,      ExportObject ); n++;
    XtSetArg ( args[n], XmNsourceCursorIcon, dragIcon ); n++;
    XtSetArg ( args[n], XmNexportTargets,    targets ); n++;
    XtSetArg ( args[n], XmNnumExportTargets, 1 ); n++;
    XtSetArg ( args[n], XmNclientData,       item ); n++;
    XtSetArg ( args[n], XmNdragOperations,   XmDROP_COPY ); n++;

   /*
    * Start the drag.
    */

    drag_context =  XmDragStart ( w, event, args, n );
}
                                                    
static Boolean ExportObject ( Widget         w, 
                              Atom          *selection, 
                              Atom          *target, 
                              Atom          *type,
                              XtPointer     *value,
                              unsigned long *length,
                              int           *format )
{
    GraphicsObject *object;
    char           *str;

    if ( *target == TARGETS )
    {
        static Atom targets[1];
        targets[0] = GRAPHICS_OBJECT;

        *value =  ( XtPointer ) targets;
        *format = 32;   
        *length = 1;
        *type   = TARGETS;

        return ( TRUE );
    }
    else if ( *target == GRAPHICS_OBJECT )
    {

       /*
        * Retrieve the object stored in the clientData resource
        * and convert the object to a string format for transmission
        * to the drop site.
        */

        XtVaGetValues ( w, XmNclientData, &object, NULL );
    
        str = Pack ( object );
    
        *type   = XA_STRING;
        *format = 8;
        *value  = str;
        *length = strlen ( str ) + 1;

        return ( TRUE );
    }

    return ( FALSE );
}
                
static void SetDragIcon ( int type )
{
   /*
    * Create a pixmap for a specified figure type, and install
    * the result in an XmDragIcon widget. Do lazy evaluation
    * so pixmaps are not created unless they are needed. Reuse the
    * same pixmaps once they have been created.
    */

    static Pixmap lineBitmap = 0;
    static Pixmap circleBitmap = 0;
    static Pixmap rectBitmap = 0;
    static Pixmap filledRectBitmap = 0;
    static Pixmap filledCircleBitmap = 0;
    Pixmap pixmap;
    int    width, height, n;
    Arg    args[10];
    Window root = RootWindowOfScreen ( XtScreen ( canvas ) );

    switch ( type )
    {
      case LINE:
        
        if ( !lineBitmap )
            lineBitmap = XCreateBitmapFromData ( display, root,
                                                 line_bits,
                                                 line_width,
                                                 line_height );
        width  = line_width;
        height = line_height;
        pixmap = lineBitmap;
        break;
        
      case CIRCLE:
        
        if ( !circleBitmap )
            circleBitmap = XCreateBitmapFromData ( display, root,
                                                   circle_bits,
                                                   circle_width, 
                                                   circle_height );
        width  = circle_width;
        height = circle_height;
        pixmap = circleBitmap;        
        break;

      case RECTANGLE:
        
        if ( !rectBitmap )
            rectBitmap = XCreateBitmapFromData ( display, root,
                                                 rectangle_bits,
                                                 rectangle_width,
                                                 rectangle_height );
        width  = rectangle_width;
        height = rectangle_height;
        pixmap = rectBitmap;                
        break;
        
      case FILLEDCIRCLE:
        
        if ( !filledCircleBitmap )
            filledCircleBitmap = 
                       XCreateBitmapFromData ( display, root,
                                               filledcircle_bits,
                                               filledcircle_width,
                                                 filledcircle_height );
        width  = filledcircle_width;
        height = filledcircle_height;
        pixmap = filledCircleBitmap;                
        break;
        
      case FILLEDRECTANGLE:
        
        if ( !filledRectBitmap )
            filledRectBitmap = 
                         XCreateBitmapFromData ( display, root,
                                                 filledrect_bits,
                                                 filledrect_width,
                                                   filledrect_height );
        width  = filledrect_width;
        height = filledrect_height;
        pixmap = filledRectBitmap; 
        break;
    }

    if ( !dragIcon )
    {
       /*
        * Create a drag icon the first time this function is called.
        * Afterwards, just change resources for this icon widget.
        */

        n = 0;
        XtSetArg ( args[n], XmNwidth,      width ); n++;
        XtSetArg ( args[n], XmNheight,     height ); n++;
        XtSetArg ( args[n], XmNpixmap,     pixmap ); n++;
        XtSetArg ( args[n], XmNmask,       pixmap ); n++;
        dragIcon = XmCreateDragIcon ( canvas, "dragIcon", args, n );
    }
    else
        XtVaSetValues ( dragIcon, 
                        XmNwidth,  width,
                        XmNheight, height,
                        XmNpixmap, pixmap, 
                        XmNmask,   pixmap,
                        NULL );        
}
                                

static void DrawLine ( Window w, GC gc, int x, int y, int x2, int y2 )
{
    XDrawLine ( display,  w, gc, x, y, x2, y2 );
}
    
void DrawRectangle ( Window w, GC gc, int x, int y, int x2, int y2 )
{
    FixDataOrdering ( &x, &y, &x2, &y2 );
    
    XDrawRectangle ( display, w , gc,  x, y, x2 - x, y2 - y );
}
void DrawFilledRectangle ( Window w, GC gc, int x, int y, int x2, int y2 )
{
    FixDataOrdering ( &x, &y, &x2, &y2 );

    XFillRectangle ( display,  w, gc, x, y, x2 - x, y2 - y );
}
        
static void DrawCircle ( Window w, GC gc, int x, int y, int x2, int y2 )
{
    FixDataOrdering ( &x, &y, &x2, &y2 );

    XDrawArc ( display,  w, gc, x, y,
               x2 - x, y2 - y, 0, 64 * 360 );
}
static void DrawFilledCircle ( Window w, GC gc, int x, int y, int x2, int y2 )
{
    FixDataOrdering ( &x, &y, &x2, &y2 );

    XFillArc ( display,  w, gc, x, y,
               x2 - x, y2 - y, 0, 64 * 360 );
}
        
void FixDataOrdering ( int *x, int *y, int *x2, int *y2 )
{
   /*
    * Swap the given points so that x2 is greater than x 
    * and y2 is greater than y.
    */

    if ( *x2 < *x )
    { 
        int tmp = *x; 
        *x      = *x2; 
        *x2     = tmp;
    }
    
    if ( *y2 < *y )
    { 
        int tmp = *y; 
        *y      = *y2; 
        *y2     = tmp;
    }
}
            
static DrawingFunction TypeToFunction ( int type )
{

   /*
    * Return a pointer to a function that can draw the 
    * given type of figure.
    */

    switch ( type )
    {
      case NONE:
        return NULL;
      case LINE:
        return DrawLine;
      case CIRCLE:
        return DrawCircle;
      case RECTANGLE:
        return DrawRectangle;
      case FILLEDCIRCLE:
        return DrawFilledCircle;
      case FILLEDRECTANGLE:
        return DrawFilledRectangle;
    }
}
            
void SetDrawingFunction ( int type )
{
   /*
    * Set both the current type and the current function
    */

    currentFigureType = type;

    currentFunction = TypeToFunction ( type );
}
        
SetCurrentColor ( Pixel fg )
{
    currentForeground = fg;
}
    
static void Redisplay ( Widget    w, 
                        XtPointer clientData,
                        XtPointer callData )
{

    int i;

   /*
    * Loop though all objects in the display list, drawing 
    * each one in sequence.
    */

    for ( i = 0; i < nextSlot; i++ )
         ( *  ( displayList[i].func ) ) ( XtWindow ( w ), 
                                          displayList[i].gc,
                                          displayList[i].x1,
                                          displayList[i].y1,
                                          displayList[i].x2,
                                          displayList[i].y2 );

}
            
GraphicsObject *PickObject ( int x, int y )
{
    int i;
    
   /*
    * Search the display list for an object that encloses
    * the given point. Loop backwards so that the objects
    * on top are found first.
    */

    for ( i = nextSlot - 1; i >= 0; i-- )
    {
        if ( displayList[i].x1 <=  x && displayList[i].x2 >= x &&
            displayList[i].y1 <=  y && displayList[i].y2 >= y )
        {
            return  ( &displayList[i] );
        }
    }

    return ( NULL );
}
                
void MoveObject ( GraphicsObject *object, int dx, int dy )
{
    /*
     * Move an object by erasing it in its current position,
     * updating the position information, and then drawing 
     * the figure in its new position.
     */

     ( * ( object->func ) ) ( XtWindow ( canvas ), xorGC,
                              object->x1,
                              object->y1,
                              object->x2,
                              object->y2 );
     object->x1 += dx;
     object->y1 += dy;
     object->x2 += dx;
     object->y2 += dy;
    
     ( * ( object->func ) ) ( XtWindow ( canvas ), object->gc,
                              object->x1,
                              object->y1,
                              object->x2,
                              object->y2 );
}
                
static void AddObject (  GraphicsObject *object )
{
    DrawingFunction  temp;
    
    XGCValues values;
    
   /* 
    * Check for space.
    */
    
    if ( nextSlot >= MAXOBJECTS )
    {
        fprintf ( stderr, "Warning: Display List is full\n" );
        return;
    }
    
   /*
    * Copy the information into the next available slot
    * in the display list.
    */

    displayList[nextSlot].x1         = object->x1;
    displayList[nextSlot].y1         = object->y1;
    displayList[nextSlot].x2         = object->x2;
    displayList[nextSlot].y2         = object->y2;
    displayList[nextSlot].figureType = object->figureType;
    displayList[nextSlot].foreground = object->foreground;
   /*
    * Get a GC for this color. Using XtGetGC() ensures that
    * only as many GC’s will be created as there are colors.
    * Objects with the same color will share a GC.
    */

    values.foreground = object->foreground;
    values.background = background;
    
    displayList[nextSlot].gc = XtGetGC ( canvas, 
                                         GCBackground | GCForeground,
                                         &values );
    
    displayList[nextSlot].func = TypeToFunction ( object->figureType );
    
  /*
   * For all figures expect a line, permantly correct the bounding
   * box to allowing easy picking. For a line, the coordinates
   * canot be changed wihtout changing the appearance of the figure.
   */

    if (object->figureType != LINE )
        FixDataOrdering ( &displayList[nextSlot].x1, 
                          &displayList[nextSlot].y1,
                          &displayList[nextSlot].x2,
                          &displayList[nextSlot].y2 );
   /*
    * Increment the next position index.
    */
    
    nextSlot++;
}
                                            
static void StoreObject()
{
    GraphicsObject object;

   /*
    * Don’t store zero-sized figures.
    */
    if ( startX == lastX && startY == lastY )
        return;
    
    /*
     * Save the current values of all global variables 
     * in a GraphicsObject structure.
     */
    
    object.x1         = startX;
    object.y1         = startY;
    object.x2         = lastX;
    object.y2         = lastY;
    object.figureType = currentFigureType;
    object.foreground = currentForeground;
    
   /*
    * Add the object to the display list.
    */ 

    AddObject ( &object );
}
                        
static void StartRubberBand ( Widget    w,
                              XtPointer clientData,
                              XEvent   *event,
                              Boolean  *flag )
{

   /*
    * Ignore any events other than a button press for
    * mouse button one.
    */

    if ( event->xbutton.button != Button1 )
       return;
   
    if ( currentFunction )
    {

       /*
        * If there is a current drawing function, call it to
        * start positioning the new figure.
        */

        XGCValues values;
        
       /*
        * Get a GC for the current colors 
        */
        
        values.foreground = currentForeground;
        values.background = background;
        
        currentGC = XtGetGC ( w, 
                              GCBackground | GCForeground,
                              &values );
        
       /*
        * Store the starting point and draw the initial figure.
        */
        
        lastX = startX = event->xbutton.x;
        lastY = startY = event->xbutton.y;
        
        ( * ( currentFunction ) ) ( XtWindow ( w ), xorGC,
                                    startX, startY, 
                                    lastX, lastY );
    }
    else if ( !currentFunction && event->xbutton.button == Button1 )
    {
       /*
        * If there is no current function, treat Button1
        * as a pointer and find the graphics object the mouse
        * cursor is pointing to.
        */

        lastX = startX = event->xbutton.x;
        lastY = startY = event->xbutton.y;
        
        currentObject = PickObject ( event->xbutton.x,
                                     event->xbutton.y );
        if ( currentObject )
        {
           /*
            * If an object was found, any mouse motion will move
            * the object. Get a new graphics context whose colors
            * match the colors of the current object.
            */

            XGCValues values;
            
            XtReleaseGC ( w, xorGC );
            values.foreground = currentObject->foreground ^ 
                                background;
            values.function   = GXxor;
            
            /*
             * Change the color of the rubber band gc 
             */
            
            xorGC =  XtGetGC ( w,  GCForeground | GCFunction, 
                                   &values );
        }
    }
}
                                                        
static void TrackRubberBand ( Widget    w, 
                              XtPointer clientData,
                              XEvent   *event,
                              Boolean  *flag )
{ 
   /*
    * If there is a current drawing function, handle the 
    * rubberbanding of the new figure. Otherwise, if there
    * is a currently selected object, move it, tracking the
    * cursor position.
    */

    if ( currentFunction && 
        ( event->xmotion.state & Button1Mask ) )
    {
       /*
        * Erase the previous figure.
        */
        
        ( * ( currentFunction ) ) ( XtWindow ( w ), xorGC,
                                    startX, startY, 
                                    lastX, lastY );
       /*
        * Update the last point.
        */
        
        lastX  =  event->xmotion.x;
        lastY  =  event->xmotion.y;
        
       /*
        * Draw the figure in the new position.
        */
        
         ( * ( currentFunction ) ) ( XtWindow ( w ), xorGC,
                                     startX, startY, 
                                     lastX, lastY );
    }
    else if  ( currentObject    && 
               !currentFunction && 
               event->xmotion.state & Button1Mask )
    {
        MoveObject ( currentObject, 
                     event->xmotion.x - lastX, 
                     event->xmotion.y - lastY );
        
        lastX  =  event->xmotion.x;
        lastY  =  event->xmotion.y;
    }
}
                                
static void EndRubberBand ( Widget    w,
                            XtPointer clientData,
                            XEvent   *event,
                            Boolean   *flag )
{

   /*
    * Finalize the operation begun with StartRubberBand(). If there 
    * a current drawing function, clear the last XOR image and draw
    * the final figure. 
    */

    if ( currentFunction && 
         event->xbutton.button == Button1 )
    {
        /*
         * Erase the XOR image. 
         */
        
         ( * ( currentFunction ) ) ( XtWindow ( w ), xorGC,
                                     startX, startY, 
                                     lastX,  lastY );
        
        /*
         * Draw the figure using the normal GC. 
         */
        
         ( * ( currentFunction ) ) ( XtWindow ( w ), currentGC,
                                     startX, startY, 
                                     event->xbutton.x, 
                                     event->xbutton.y );
        
        /*
         * Update the data, and store the object in 
         * the display list.
         */
        
        lastX = event->xbutton.x;
        lastY = event->xbutton.y;
        
        StoreObject();
        
        currentObject = PickObject ( event->xbutton.x,
                                     event->xbutton.y );

    }
    else if  ( currentObject    && 
               !currentFunction && 
               event->xbutton.button == Button1 )
    {

       /*
        * If the operation was a drag, move the figure
        * to its final position.
        */

        MoveObject ( currentObject, 
                     event->xbutton.x - lastX,  
                     event->xbutton.y - lastY );

       /*
        * Force a complete redraw.
        */
        
        XClearArea ( display, XtWindow ( w ), 0, 0, 0, 0, TRUE );
    }
}
                                                
char *Pack ( GraphicsObject *object )
{

    /*
     * Convert an object to a string.
     */

    static char buf[1000];
    XColor      color;

    color.pixel = object->foreground;
    XQueryColor ( display, colormap, &color );
    
    sprintf ( buf, "%d %d %d %d %d %d %d %d",
              object->x1, object->y1, 
              object->x2, object->y2,
              object->figureType,
              color.red, color.green, color.blue );
    
    return ( buf );

}
GraphicsObject *Unpack ( char *str )
{

   /*
    * Convert a string to an object
    */

    static GraphicsObject object;
    XColor                color;

    sscanf ( str, "%d %d %d %d %d %hd %hd %hd", 
             &object.x1, &object.y1, 
             &object.x2, &object.y2, 
             &object.figureType, 
             &color.red, &color.green, &color.blue );

   /*
    * Get the pixel that corresponds to the given color.
    */

    XAllocColor ( display, colormap, &color );
    object.foreground = color.pixel;

    return ( &object );

}
                    
void SaveData()
{
    FILE  *fp;
    static Widget dialog = NULL;
        
   /*
    * Create the dialog if it doesn’t already exist. Install
    * callbacks for OK and Cancel actions.
    */

    if ( !dialog )
    {
         dialog = XmCreateFileSelectionDialog ( canvas, "saveDialog",
                                                NULL, 0 );

         XtAddCallback ( dialog, XmNokCallback,
                         SaveDataCallback,  ( XtPointer ) NULL );
         XtAddCallback ( dialog, XmNcancelCallback,
                         CancelDialogCallback,  ( XtPointer ) NULL );
     }
        
     XtManageChild ( dialog );

 }
            

void CancelDialogCallback ( Widget    w, 
                            XtPointer clientData,
                            XtPointer callData )
{
    XtUnmanageChild ( w );
}

void SaveDataCallback ( Widget    w,
                        XtPointer clientData,
                        XtPointer callData )
{
    FILE    *fp;
    char    *fileName;
    XmString xmstr;
    int      i;
    
   /*
    * Remove the dialog from the screen.
    */

    XtUnmanageChild ( w );
    
   /*
    * Retrieve the currently selected file.
    */

    XtVaGetValues (  w,
                     XmNdirSpec, &xmstr,
                     NULL );

   /*
    * Make sure a file was selected.
    */

    if ( !xmstr )
       return;

   /*
    * Retrieve the name of the file as ASCII.
    */
    
    XmStringGetLtoR (  xmstr, XmFONTLIST_DEFAULT_TAG, &fileName );

   /*
    * Try to open thefile for writing
    */
    
    if ( ( fp = fopen ( fileName, "w" ) ) == NULL )
        return;

   /*
    * Loop though the display list, writing each object to the
    * newly opened file.
    */


    for ( i = 0; i < nextSlot; i++ )
    {
        GraphicsObject *object = &( displayList[i] );
        
        fprintf ( fp, "%s\n", Pack ( object ) );
    }
    
    fclose ( fp );
}
                                
void LoadData()
{
    static Widget dialog = NULL;
    
   /*
    * Create a file selection dialog if it doesn’t already exist
    */

    if ( !dialog )
    {
        dialog = XmCreateFileSelectionDialog (  canvas, 
                                               "loadDialog",
                                                NULL, 0 );
        XtAddCallback ( dialog, XmNokCallback, 
                        LoadDataCallback,  ( XtPointer ) NULL );
        XtAddCallback ( dialog, XmNcancelCallback, 
                        CancelDialogCallback,  ( XtPointer ) NULL );
    }
    
   /*
    * Display the dialog
    */

    XtManageChild ( dialog );
}
            
void LoadDataCallback ( Widget w, XtPointer clientData, XtPointer callData )
{
   /*
    * This function is called if a user selects a file to load.
    * Extract the selected file name and read the data.
    */

    FILE          *fp;
    char          *fileName;
    XmString       xmstr;
    int            results;
    GraphicsObject object;
    XColor         color;

   /*
    * Remove the dialog from the screen.
    */

    XtUnmanageChild ( w );
    
   /*
    * Retrieve the selected file
    */

    XtVaGetValues (  w,
                     XmNdirSpec, &xmstr,
                     NULL );
   /* 
    * Confirm that a file was selected
    */

    if ( !xmstr )
        return;

   /*
    * Retrieve an ASCII string from the compound string.
    */

    XmStringGetLtoR ( xmstr, XmFONTLIST_DEFAULT_TAG, &fileName );
    
    if ( ( fp = fopen ( fileName, "r" ) ) == NULL )
        return;
    
    nextSlot = 0;
    
   /*
    * Read each object into the displayList
    */

    while ( ( results = fscanf ( fp, "%d %d %d %d %d %d %d %d",
                                 &object.x1, &object.y1, 
                                 &object.x2, &object.y2, 
                                 &object.figureType, 
                                 &color.red, &color.green,
                                 &color.blue ) ) != EOF )
    {
       /*
        * Get the pixel that corresponds to the given color.
        */

        XAllocColor ( display, colormap, &color );
        object.foreground = color.pixel;
        AddObject ( &object );
    }

   /*
    * Force a redraw.
    */

    XClearArea ( display, XtWindow ( canvas ), 0, 0, 0, 0, TRUE );
    
    fclose ( fp );
}
                                        

void CopyToClipBoard()
{
    int     result;
    long    itemid, dataid;
    XmString  xmstr;

    xmstr = XmStringCreateLocalized ( "Draw" );

    
   /*
    * Initalize the clipboard for a transfer by value.
    */

    while ( ( result = 
          XmClipboardStartCopy ( display, XtWindow ( canvas ),
                                 xmstr, 
                                 XtLastTimestampProcessed ( display ),
                                 NULL, NULL, 
                                 &itemid ) ) != ClipboardSuccess )
        ;

    XmStringFree ( xmstr );
    
   /*
    * Copy the data, which is identified as type "GraphicsObject"
    */
    
    while ( ( result =  
                   XmClipboardCopy ( display,  XtWindow ( canvas ), 
                                     itemid,
                                     "GraphicsObject", 
                                     ( char * ) currentObject,
                                     sizeof ( GraphicsObject ), 0,
                                     &dataid ) ) != ClipboardSuccess )
        ;
    
   /*
    * End the transaction.
    */
    
    while ( ( result = 
                 XmClipboardEndCopy ( display, XtWindow ( canvas ),
                                        itemid ) ) != ClipboardSuccess )
        ;
}
                

void CopyFromClipBoard ()
{ 
    GraphicsObject    object;
    int               result, pos; 
    long              id;
    int               done = FALSE; 
    unsigned long     numBytes;
    
   /* 
    * Retrieve the current contents of the clipboard. 
    */ 
    
    while  ( !done )
    {
        result = XmClipboardRetrieve ( display, XtWindow ( canvas ),
                                       "GraphicsObject", &object,
                                       sizeof ( GraphicsObject ),
                                       &numBytes, &id );
       /* 
        * Check the return value. If the clipboard is locked, try
        * again. If data is retrieved successfully, append it 
        * to the text buffer. Otherwise abort. 
        */ 
        
        switch ( result )
        { 
          case ClipboardSuccess: 
            
            AddObject ( &object );
            XClearArea ( display, XtWindow ( canvas ),
                         0, 0, 0, 0, TRUE );
            done = TRUE; 
            break; 
            
          case ClipboardTruncate: 
          case ClipboardNoData: 
            
            done = TRUE;
            break; 
            
          case ClipboardLocked: 
            break; 
        } 
    }
}
                    
void CutSelectedItem()
{
    if ( currentObject )
    {
        CopyToClipBoard();
        
        RemoveItem ( currentObject );
    }
}
    
void CopySelectedItem()
{
    if ( currentObject )
    {
        CopyToClipBoard();
    }
}
    
void PasteItem()
{
    CopyFromClipBoard();
}
    
void RemoveItem ( GraphicsObject *object )
{
    int i;
    
    for ( i = 0; i < nextSlot; i++ )
    {
       /*
        * Find the specified object
        */
        if ( object ==  &( displayList[i] ) )
        {
            int j;
            
           /*
            * Move all other objects up one slot, leaving out
            * the item to be removed.
            */

            for ( j = i; j < nextSlot - 1; j++ )
            {
                displayList[j].x1 =         displayList[j+1].x1;
                displayList[j].y1 =         displayList[j+1].y1;
                displayList[j].x2 =         displayList[j+1].x2;
                displayList[j].y2 =         displayList[j+1].y2;
                displayList[j].func =       displayList[j+1].func;
                displayList[j].foreground = 
                                       displayList[j+1].foreground;
                displayList[j].gc =         displayList[j+1].gc;
            }
            
            nextSlot--;
            
            if ( nextSlot < 0 )
                nextSlot = 0;

           /*
            * Force a redisplay to redraw all remaining objects.
            */

            XClearArea ( display, 
                        XtWindow ( canvas ),
                         0, 0, 0, 0, TRUE );
            
            return;
        }
    }
}
                    
