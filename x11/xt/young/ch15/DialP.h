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
 * DialP.h: Private header file for the Dial widget class
 ***********************************************************/
#ifndef DIALP_H
#define DIALP_H

#include <Xm/PrimitiveP.h>
#include "Dial.h"

#define MAXSEGMENTS 200
        
typedef struct _XsDialClassPart{
       int ignore;
} XsDialClassPart;

typedef struct _XsDialClassRec{
   CoreClassPart        core_class;
   XmPrimitiveClassPart primitive_class;
   XsDialClassPart      dial_class;
} XsDialClassRec;


extern XsDialClassRec XsdialClassRec;

typedef struct _XsDialPart {
   int       minimum;          /* minimum value          */
   int       maximum;          /* maximum value          */
   int       markers;          /* number of marks        */
   Dimension marker_length;    /* in pixels              */
   int       value;            /* indicator position     */
   Position  indicator_x;      /* x,y position of tip    */
   Position  indicator_y;      /*     of the indicator   */
   Position  shadow_delta;
   Position  center_x;         /* coordinates of the     */
   Position  center_y;         /*     dial center        */
   Position  inner_diam;       /* inside of markers      */
   Position  outer_diam;       /* outside of markers     */  
   GC        inverse_GC;       /* Used to clear indicator*/
   unsigned  char shadow_type; /* type of frame          */
   XSegment  segments[MAXSEGMENTS];   /* dark shadow lines */
   XSegment  highlights[MAXSEGMENTS]; /* light shadow lines */
   XtCallbackList value_changed;      /* callback list          */
} XsDialPart;
                                                                                                                                
typedef struct _XsDialRec {
   CorePart          core;
   XmPrimitivePart   primitive;
   XsDialPart        dial;
} XsDialRec;
#endif /*DIALP_H */

