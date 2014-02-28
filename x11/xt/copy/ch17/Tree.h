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
 * Tree.h: Public header file for the Tree widget class.
 ********************************************************/
#ifndef XSTREE_H
#define XSTREE_H

#ifdef __cplusplus
extern "C" {
#endif

extern WidgetClass xsTreeWidgetClass;

typedef struct _XsTreeClassRec *XsTreeWidgetClass;
typedef struct _XsTreeRec      *XsTreeWidget;

#define XmNhorizontalSpace    "horizontalSpace"
#define XmNverticalSpace      "verticalSpace"
#define XmCPad                "Pad"
#define XmNsuperNode          "superNode"
#define XmCSuperNode          "SuperNode"

Widget XsCreateTree ( Widget   parent,
                      char    *name,
                      ArgList  arglist,
                      Cardinal argcount );

Widget XsCreateScrolledTree ( Widget   parent,
                              char    *name,
                              ArgList  arglist,
                              Cardinal argcount );

#ifdef __cplusplus
}
#endif

#endif
        
