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
 * TreeP.h: Private header file for the Tree widget class.
 **********************************************************/
#ifndef XSTREEP_H
#define XSTREEP_H

#include "Tree.h"
#include <Xm/ManagerP.h>

typedef struct _XsTreeClassPart {
    int   ignore;
} XsTreeClassPart;

typedef struct _XsTreeClassRec {
  CoreClassPart       core_class;
  CompositeClassPart  composite_class;
  ConstraintClassPart constraint_class;
  XmManagerClassPart  manager_class;
  XsTreeClassPart     tree_class;
} XsTreeClassRec;
extern XsTreeClassRec xsTreeClassRec;
            
typedef struct {
    Dimension  *array;
    int         size;
 }  XsVariableArray;

typedef struct {
    Dimension         h_min_space;
    Dimension         v_min_space;
    XsVariableArray  *horizontal;
    XsVariableArray  *vertical;
    Widget            tree_root;
} XsTreePart;

typedef struct _XsTreeRec {
    CorePart        core;
    CompositePart   composite;
    ConstraintPart  constraint;
    XmManagerPart   manager;
    XsTreePart      tree;
}  XsTreeRec;

typedef struct _XsTreeConstraintPart {
  Widget        super_node;
  WidgetList    sub_nodes;
  long          n_sub_nodes;
  long          max_sub_nodes;
  Position      x, y;
} XsTreeConstraintPart;

typedef struct _XsTreeConstraintsRec {
   XmManagerConstraintPart   manager;
   XsTreeConstraintPart      tree;
} XsTreeConstraintsRec, *XsTreeConstraints;

#endif 

