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

/*********************************************************
 * Dial.h: Public header file for the Dial widget class
 *********************************************************/
#ifndef  DIAL_H
#define  DIAL_H

#ifdef __cplusplus
extern "C" {
#endif

extern WidgetClass xsDialWidgetClass;
typedef struct _XsDialClassRec * XsDialWidgetClass;
typedef struct _XsDialRec      * XsDialWidget;

/*
 * Define resource strings for the Dial widget.
 */

#define XmNmarkers        "markers"
#define XmNposition       "position"
#define XmNmarkerLength   "markerLength"

#define XmCMarkers        "Markers"
#define XmCMin            "Min"
#define XmCMax            "Max"

/*
 * Structure used for call data argument to Dial callbacks
 */


typedef struct {
    int     reason;
    XEvent *event;
    int     value;
} XsDialCallbackStruct;

Widget XsCreateDial ( Widget   parent,
                      char    *name,
                      ArgList  arglist,
                      Cardinal argcount );
#ifdef __cplusplus
}
#endif
#endif
            
