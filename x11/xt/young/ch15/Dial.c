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

/***************************************************
 * Dial.c: Dial widget methods
 ***************************************************/
#include <Xm/XmP.h>
#include "DialP.h"
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define  RADIANS( x ) ( M_PI * ( x )  / 180.0 ) 
#define  DEGREES( x ) ( ( x )  / M_PI  * 180.0 ) 
#define  MIN_ANGLE   225.0
#define  MAX_ANGLE   270.0
#define  MIN( a,b ) ( ( ( a ) < ( b ) )  ? ( a )  : ( b ) ) 


static void SetIndicatorPosition ( Widget    w, 
                                   XEvent   *event, 
                                   String   *args, 
                                   Cardinal *n_args );
static void Initialize ( Widget    req,
                         Widget    widget, 
                         ArgList   args,
                         Cardinal *nArgs );
static void Redisplay ( Widget  w, 
                        XEvent *event, 
                        Region  region );
static void CalculateIndicatorPos ( XsDialWidget w );
static void Resize ( Widget w );
static void Destroy ( Widget widget );
static Boolean SetValues ( Widget    cur,
                           Widget    req,
                           Widget    widget,
                           ArgList   args,
                           Cardinal *numArgs );
extern void _XmDrawShadows ( Display *display, Window window, 
                             GC top_shadow, GC bottom_shadow,
                             Position x, Position y,
                             Dimension width, Dimension height,
                             Dimension shadow_thickness,
                             unsigned char shadow_type );
    
static char defaultTranslations[] = "<Btn1Down>: set-position() \n\
<Btn1Motion>: set-position() \n\
<EnterWindow>:     PrimitiveEnter() \n\
<LeaveWindow>:     PrimitiveLeave()";


static XtActionsRec actionsList[] = {
  { "set-position",   SetIndicatorPosition },
};

static XtResource resources[] = {
    
{ XmNmarkers, XmCMarkers, XmRInt, sizeof ( int ),
  XtOffset ( XsDialWidget, dial.markers ), XmRString, "10"  },
 
{ XmNminimum, XmCMin, XmRInt, sizeof ( int ),
  XtOffset ( XsDialWidget, dial.minimum ), XmRString, "0"   },
 
{ XmNmaximum, XmCMax, XmRInt, sizeof ( int ),
  XtOffset ( XsDialWidget, dial.maximum ), XmRString, "100" },
 
{ XmNshadowType, XmCShadowType, XmRShadowType, sizeof ( unsigned char ),  
  XtOffset ( XsDialWidget, dial.shadow_type ),
  XmRImmediate, ( XtPointer )  XmSHADOW_ETCHED_IN },
   
{ XmNvalue, XmCValue, XmRInt, sizeof ( int ),
  XtOffset ( XsDialWidget, dial.value ), XmRString, "0"  },
 
{ XmNmarkerLength,XmCLength,XmRDimension,sizeof ( Dimension ),
  XtOffset ( XsDialWidget, dial.marker_length ),
  XmRString, "5"                                         },
 
{ XmNvalueChangedCallback,XmCCallback,XmRCallback,sizeof ( XtPointer ),
  XtOffset ( XsDialWidget, dial.value_changed ), 
  XmRCallback, NULL                                      },
};

externaldef ( dialclassrec )  XsDialClassRec xsDialClassRec = {
{     /* CoreClassPart */
   ( WidgetClass )  &xmPrimitiveClassRec,  /* superclass         */
    "XsDial",                       /* class_name            */
    sizeof ( XsDialRec ),           /* widget_size           */
    NULL,                           /* class_initialize      */
    NULL,                           /* class_part_initialize */
    FALSE,                          /* class_inited          */
    Initialize,                     /* initialize            */
    NULL,                           /* initialize_hook       */
    XtInheritRealize,               /* realize               */
    actionsList,                    /* actions               */
    XtNumber ( actionsList ),       /* num_actions           */
    resources,                      /* resources             */
    XtNumber ( resources ),         /* num_resources         */
    NULLQUARK,                      /* xrm_class             */
    TRUE,                           /* compress_motion       */
    XtExposeCompressMaximal,        /* compress_exposure     */
    TRUE,                           /* compress_enterleave   */
    TRUE,                           /* visible_interest      */
    Destroy,                        /* destroy               */
    Resize,                         /* resize                */
    Redisplay,                      /* expose                */
    SetValues,                      /* set_values            */
   NULL,                           /* set_values_hook       */
   XtInheritSetValuesAlmost,       /* set_values_almost     */
   NULL,                           /* get_values_hook       */
   NULL,                           /* accept_focus          */
   XtVersion,                      /* version               */
   NULL,                           /* callback private      */
   defaultTranslations,            /* tm_table              */
   NULL,                           /* query_geometry        */
   NULL,                           /* display_accelerator   */
   NULL,                           /* extension             */
},
{          /* XmPrimitive        */
   XmInheritBorderHighlight,       /* border_highlight      */
   XmInheritBorderUnhighlight,     /* border_unhighlight    */
   XmInheritTranslations,          /* translations          */
   NULL,                           /* arm_and_activate      */
   NULL,                           /* synresources          */
   0,                              /* num syn_resources     */
   NULL,                           /* extension             */
},
/* Dial class fields */
{
    0,                              /* ignore                */
}
};
WidgetClass xsDialWidgetClass = ( WidgetClass )  &xsDialClassRec;
                                                                                                                                                                                                                                                                                                                                                        static void Initialize ( Widget req, Widget widget,
                         ArgList args, Cardinal *numArgs ) 
{
    XsDialWidget request = ( XsDialWidget ) req;
    XsDialWidget dw      = ( XsDialWidget ) widget;
    XGCValues    values;
    XtGCMask     valueMask;

   /*
    * Make sure the window size is not zero. The Core 
    * Initialize() method doesn't do this.
    */
    
    if ( request->core.width == 0 ) 
        dw->core.width = 100;
    if ( request->core.height == 0 ) 
        dw->core.height = 100;
   /*
    * Make sure the min and max dial settings are valid.
    */
    
    if ( dw->dial.minimum >= dw->dial.maximum )  
    {
        XtWarning ( "Maximum must be greater than the Minimum" );
        dw->dial.minimum = dw->dial.maximum - 1;
    }
    
    if ( dw->dial.value > dw->dial.maximum )  
    {
        XtWarning ( "Value exceeds the Dial Maximum" );
        dw->dial.value =  dw->dial.maximum;
    }
    
    if ( dw->dial.value < dw->dial.minimum )  
    {
        XtWarning ( "Value is less than the Dial Minimum" );
        dw->dial.value =  dw->dial.minimum;
    }
    
   /*
    * Allow only MAXSEGMENTS markers
    */
    
    if ( dw->dial.markers > MAXSEGMENTS ) 
    {
        XtWarning ( "Too many markers" );
        dw->dial.markers = MAXSEGMENTS;
    }
    
   /*
    * Create a graphics contexts used to erase
    * the indicator.
    */
    
    valueMask           = GCForeground | GCBackground;
    values.foreground   = dw->core.background_pixel;
    values.background   = dw->core.background_pixel;
    dw->dial.inverse_GC = XtGetGC ( ( Widget ) dw,
                                    valueMask, &values ); 

   /*
    * Call the widgetÕs resize method through the class
    * pointer to force certain values to be computed. Use the
    * class pointer to allow any subclasses to override method.
    */

    if ( dw->core.widget_class->core_class.resize )
        (*(dw->core.widget_class->core_class.resize)) ((Widget) dw);
}
                                        
static void Destroy ( Widget widget ) 
{
    XsDialWidget dw = ( XsDialWidget )  widget;
    
    XtReleaseGC ( ( Widget ) dw, dw->dial.inverse_GC );
    XtRemoveAllCallbacks ( ( Widget ) dw, XmNvalueChangedCallback );
}
    
static void Resize ( Widget w ) 
{
    XsDialWidget dw = ( XsDialWidget )  w;
    
    double    angle, cosine, sine, increment;
    int       i; 
    
   /*
    * Calculate the center of the widget
    */
    
    dw->dial.center_x = dw->core.width / 2; 
    dw->dial.center_y = dw->core.height / 2;   
    
   /* 
    *  Generate the segment array containing the points needed to   
    *  draw the tick marks on the face of the dial.    
    */ 
    
    increment           = RADIANS ( MAX_ANGLE )  / 
                               ( float ) ( dw->dial.markers -1 );
    dw->dial.outer_diam = 
                 ( MIN ( dw->core.width, dw->core.height ) -
                      2 * dw->primitive.shadow_thickness - 
                         2 * dw->primitive.highlight_thickness ) / 2;
    dw->dial.inner_diam = dw->dial.outer_diam - 
                                          dw->dial.marker_length;
    angle               = RADIANS ( MIN_ANGLE );  
    
    for ( i = 0; i < dw->dial.markers; i++ ) 
    {   
        int xdelta;
        
        cosine = cos ( angle );   
        sine   = sin ( angle ); 
        
        dw->dial.segments[i].x1 = dw->dial.center_x + 
                                         dw->dial.outer_diam * sine; 
        dw->dial.segments[i].y1 = dw->dial.center_y - 
                                         dw->dial.outer_diam * cosine;
        dw->dial.segments[i].x2 = dw->dial.center_x +
                                         dw->dial.inner_diam * sine; 
        dw->dial.segments[i].y2 = dw->dial.center_y - 
                                         dw->dial.inner_diam * cosine;
        
       /*
        * Compute a second set of points with which to draw
        * a top shadow for each mark on the dial. Depending on
        * the angle of the line, the shadow must be 
        * positioned differently.
        */

        if ( ( sine < 0 && cosine < 0 )  || 
             ( sine > 0 && cosine > 0 ) ) 
        {
            xdelta = 1;
        }
        else if ( ( sine < 0 && cosine > 0 )  ||
                  ( sine > 0 && cosine < 0 ) ) 
        {
            xdelta = -1;
        }
        
        dw->dial.highlights[i].x1 = dw->dial.segments[i].x1 + xdelta;
        dw->dial.highlights[i].x2 = dw->dial.segments[i].x2 + xdelta;
        dw->dial.highlights[i].y1 = dw->dial.segments[i].y1 + 1;
        dw->dial.highlights[i].y2 = dw->dial.segments[i].y2 + 1;
        
        angle += increment; 
    }  
    
    CalculateIndicatorPos ( dw ); 
} 
                                                
static void CalculateIndicatorPos ( XsDialWidget dw ) 
{
    double   normalized_pos, angle, sine, cosine;
    Position indicator_length;
    
   /*
    * Make the indicator two pixels shorter than the  
    * inner edge of the markers.
    */
    
    indicator_length = dw->dial.outer_diam - dw->dial.marker_length-2;
    
   /*
    * Normalize the indicator value to lie between zero
    * and 1, and then convert it to an angle.
    */
    
    normalized_pos = ( dw->dial.value - dw->dial.minimum ) /
                  ( float ) ( dw->dial.maximum - dw->dial.minimum );
    angle = RADIANS ( MIN_ANGLE + MAX_ANGLE  * normalized_pos );  
    
   /*
    * Find the x,y coordinates of the tip of the indicator.   
    */ 
    
    sine = sin ( angle ); 
    cosine = cos ( angle ); 
    
    if ( ( sine < 0 && cosine < 0 )  || 
         ( sine > 0 && cosine > 0 ) ) 
    {
        dw->dial.shadow_delta = 1;
    }
    else if ( ( sine < 0 && cosine > 0 )  ||
              ( sine > 0 && cosine < 0 ) ) 
    {
        dw->dial.shadow_delta =  -1;
    }
    
    dw->dial.indicator_x = dw->dial.center_x + 
                                  indicator_length * sine; 
    
    dw->dial.indicator_y = dw->dial.center_y - 
                                  indicator_length  * cosine;
} 
                        
static void Redisplay ( Widget w, XEvent *event, Region region ) 
{
    XsDialWidget  dw = ( XsDialWidget )  w;
    XsDialWidgetClass wc = (XsDialWidgetClass) XtClass(w);
    
    if ( dw->core.visible && XtIsRealized ( dw ) ) 
    {
	if( dw->primitive.highlighted )
	    (*(wc->primitive_class.border_highlight))( w );
	else
	    (*(wc->primitive_class.border_unhighlight))( w );

		/*
        * Draw the surrounding shadow 
        */
        
        _XmDrawShadows ( XtDisplay ( dw ),
                         XtWindow ( dw ),
                         dw->primitive.top_shadow_GC,
                         dw->primitive.bottom_shadow_GC,
                         0, 0, dw->core.width, dw->core.height,
                         dw->primitive.shadow_thickness,
                         dw->dial.shadow_type );
       /*
        * Draw the markers used for the dial face.
        */
        
        XDrawSegments ( XtDisplay ( dw ), XtWindow ( dw ),
                        dw->primitive.top_shadow_GC, 
                        dw->dial.highlights, dw->dial.markers );
        
        XDrawSegments ( XtDisplay ( dw ), XtWindow ( dw ),
                        dw->primitive.bottom_shadow_GC, 
                        dw->dial.segments, dw->dial.markers );

       /*
        * Draw the indicator at its current value.
        */
        
        XDrawLine ( XtDisplay ( dw ), XtWindow ( dw ),
                    dw->primitive.top_shadow_GC, 
                    dw->dial.center_x, dw->dial.center_y,   
                    dw->dial.indicator_x, dw->dial.indicator_y );   
        
        XDrawLine ( XtDisplay ( dw ), XtWindow ( dw ),
                    dw->primitive.bottom_shadow_GC, 
                    dw->dial.center_x + dw->dial.shadow_delta, 
                    dw->dial.center_y + 1,   
                    dw->dial.indicator_x + dw->dial.shadow_delta, 
                    dw->dial.indicator_y + 1 );   
    }
} 
                
static Boolean SetValues ( Widget    cur,
                           Widget    req,
                           Widget    widget,
                           ArgList   args,
                           Cardinal *numArgs ) 
{
    XsDialWidget current = ( XsDialWidget )  cur;
    XsDialWidget request = ( XsDialWidget )  req;
    XsDialWidget dw      = ( XsDialWidget )  widget;
    XGCValues  values;
    XtGCMask   valueMask;
    Boolean    redraw = FALSE;
    Boolean    redraw_indicator = FALSE;
    
   /*
    * Make sure the dw dial values are reasonable.
    */
    
    if ( dw->dial.minimum >= dw->dial.maximum )  
    {
        XtWarning ( "Dial Minimum must be less than Maximum" );
        dw->dial.minimum = 0;
        dw->dial.maximum = 100;
    }
    
    if ( dw->dial.value > dw->dial.maximum )  
    {
        XtWarning ( "Dial value is greater than the Maximum" );
        dw->dial.value = dw->dial.maximum;
    }
    
    if ( dw->dial.value < dw->dial.minimum )  
    {
        XtWarning ( "Dial value is less than the Minimum" );
        dw->dial.value = dw->dial.minimum;
    }
    
   /*
    * If the indicator color or background color 
    * has changed, generate the GC's.
    */
    
    if ( dw->core.background_pixel != current->core.background_pixel ) 
    {
        XtReleaseGC ( ( Widget ) current, current->dial.inverse_GC );
        
        valueMask         = GCForeground | GCBackground;
        values.foreground = dw->core.background_pixel;
        values.background = dw->core.background_pixel;
        
        dw->dial.inverse_GC = XtGetGC ( ( Widget ) dw, valueMask,
                                        &values );
        
        redraw_indicator = TRUE;     
    }
    
   /*
    * If the indicator value has changed, or if the min/max
    * values have changed, recompute the indicator coordinates.
    */
    if ( dw->dial.value   != current->dial.value ||
          dw->dial.minimum != current->dial.minimum ||
          dw->dial.maximum != current->dial.maximum ) 
    {
        CalculateIndicatorPos ( dw );
        redraw_indicator = TRUE;
    }
    
   /*
    * If only the indicator needs to be redrawn and
    * the widget is realized, erase the current indicator
    * and draw the new one. SetValues functions are not
    * expected to draw, but this reduces flicker caused
    * by redrawing the entire widget face. Be sure the 
    * widget is realized.
    */
    
    if ( redraw_indicator && !redraw &&
         XtIsRealized ( dw ) && dw->core.visible ) 
    {
        XDrawLine ( XtDisplay ( dw ), XtWindow ( dw ),
                    dw->dial.inverse_GC, 
                    current->dial.center_x + 
                                   current->dial.shadow_delta,
                    current->dial.center_y + 1,
                    current->dial.indicator_x +
                                   current->dial.shadow_delta, 
                    current->dial.indicator_y + 1 );    
        XDrawLine ( XtDisplay ( dw ), XtWindow ( dw ),
                    dw->dial.inverse_GC, 
                    current->dial.center_x, current->dial.center_y,
                    current->dial.indicator_x, 
                    current->dial.indicator_y );
        
        XDrawLine ( XtDisplay ( dw ), XtWindow ( dw ),  
                    dw->primitive.top_shadow_GC,  
                    dw->dial.center_x, dw->dial.center_y,
                    dw->dial.indicator_x, dw->dial.indicator_y );
        XDrawLine ( XtDisplay ( dw ), XtWindow ( dw ),  
                    dw->primitive.bottom_shadow_GC,  
                    dw->dial.center_x + dw->dial.shadow_delta, 
                    dw->dial.center_y + 1,
                    dw->dial.indicator_x + dw->dial.shadow_delta, 
                    dw->dial.indicator_y + 1 ); 
    } 
    
    return ( redraw ); 
} 
                                                
static void SetIndicatorPosition ( Widget    w,
                                   XEvent   *event,
                                   String   *args,
                                   Cardinal *n_args ) 
{
    XsDialWidget   dw = ( XsDialWidget )  w;
    Position       pos;
    double         angle;
    XsDialCallbackStruct cb;
    
    pos = dw->dial.value;
    
    if ( event->type == ButtonPress || 
         event->type == MotionNotify ) 
    {
        /* 
         * Get the angle in radians.
         */
        
         angle=atan2 ( ( double ) ( event->xbutton.y -
                                      dw->dial.center_y ),
                      ( double ) ( event->xbutton.x -
                                     dw->dial.center_x ) );
       /*
        * Convert to degrees from the MIN_ANGLE.
        */ 
        
        angle = DEGREES ( angle )  - ( MIN_ANGLE - 90.0 ); 
        if ( angle < 0 ) 
            angle = 360.0 + angle;
        
       /*  
        * Convert the angle to a value. 
        */ 
        
        pos = dw->dial.minimum + ( angle / 
                     MAX_ANGLE * ( dw->dial.maximum - dw->dial.minimum ) );
        if ( pos > dw->dial.maximum || pos < dw->dial.minimum ) 
            return;
    }  
    
   /*
    * Invoke the callback. Report the value in the call_data
    * structure
    */  
    
    cb.reason = XmCR_VALUE_CHANGED;
    cb.event  = event;
    cb.value  = pos;
    
    XtVaSetValues ( ( Widget )  dw, XmNvalue, pos, NULL );
    
    XtCallCallbacks ( ( Widget ) dw, XmNvalueChangedCallback, &cb ); 
} 
                        
Widget XsCreateDial ( Widget   parent,
                      char    *name,
                      ArgList  arglist,
                      Cardinal argcount )  
{
    return ( XtCreateWidget ( name, xsDialWidgetClass, 
                              parent, arglist, argcount ) );
}
    
