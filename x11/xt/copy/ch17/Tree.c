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
 * Tree.c: The Tree Widget Source File
 ***************************************************/
#include         <Xm/XmP.h>
#include         <Xm/ScrolledW.h>
#include         "TreeP.h"

#define   MAX(a,b) ((a) > (b) ? (a) : (b))
static void Initialize ( Widget req, Widget new_w, 
                          ArgList args, Cardinal *numArgs );
static Boolean ConstraintSetValues ( Widget    current,
                                     Widget    request,
                                     Widget    new_w, 
                                     ArgList   args, 
                                     Cardinal *numArgs );
static void ConstraintInitialize ( Widget request, Widget new_w,
                                   ArgList args, Cardinal *numArgs );
static void ConstraintDestroy ( Widget w );
static Boolean SetValues ( Widget cur, Widget req, Widget widget, 
                           ArgList args, Cardinal *numArgs );
static XtGeometryResult GeometryManager ( Widget           w,
                                         XtWidgetGeometry *request,
                                         XtWidgetGeometry *reply );
static void ChangeManaged ( Widget w );
static void DeleteNode ( Widget super_node, Widget node );
static void Redisplay ( Widget w, XEvent *event, Region region );
static XsVariableArray  *CreateOffset ( long size );
static int ComputePositions ( XsTreeWidget tw,
                              Widget       w,
                              long         level );
static void SetPositions ( XsTreeWidget tw,
                           Widget       w,
                           int     level );
static void Reset ( XsVariableArray  *offset );
static void NewLayout ( XsTreeWidget tw );
static void ShiftSubtree ( Widget    w,
                           Dimension offset );
static Position CurrentPosition ( XsVariableArray  *offset,
                                  long              position );
static void SetCurrentPosition ( XsVariableArray  *offset,
                                 int               index,
                                 Dimension         value );
static Position SumOfPositions ( XsVariableArray  *offset,
                                 long              index );
static void InsertNewNode ( Widget super_node, Widget node );
#define TREE_CONSTRAINT( w ) \
            ( ( XsTreeConstraints ) ( ( w )->core.constraints ) ) 

 static XtResource resources[] = {
        
 { XmNhorizontalSpace,XmCSpace,XmRDimension,sizeof ( Dimension ),
   XtOffset ( XsTreeWidget, tree.h_min_space ), XtRString,"20" },
 
 { XmNverticalSpace,XmCSpace, XmRDimension,sizeof ( Dimension ),
   XtOffset ( XsTreeWidget, tree.v_min_space ), XtRString, "20" },
};

static XtResource treeConstraintResources[] = {
{ XmNsuperNode, XmCSuperNode, XmRPointer, sizeof ( Widget ),
  XtOffset ( XsTreeConstraints, tree.super_node ),
  XtRPointer, NULL },
};

XsTreeClassRec xsTreeClassRec = {
{ 
    /* core_class fields */
    ( WidgetClass ) &xmManagerClassRec,       /* superclass         */
    "Tree",                                   /* class_name         */
    sizeof ( XsTreeRec ),                     /* widget_size        */
    NULL,                                     /* class_init         */
    NULL,                                     /* class_part_init    */
    FALSE,                                    /* class_inited       */
    Initialize,                               /* initialize         */
    NULL,                                     /* initialize_hook    */
    XtInheritRealize,                         /* realize            */
    NULL,                                     /* actions            */
    0,                                        /* num_actions        */
    resources,                                /* resources          */
    XtNumber ( resources ) ,                  /* num_resources      */
    NULLQUARK,                                /* xrm_class          */
    TRUE,                                     /* compress_motion    */
    XtExposeCompressMaximal,                  /* compress_exposure  */
    TRUE,                                     /* compress_enterleave*/
    TRUE,                                     /* visible_interest   */
    NULL,                                     /* destroy            */
    NULL,                                     /* resize             */
    Redisplay,                                /* expose             */
    SetValues,                                /* set_values         */
    NULL,                                     /* set_values_hook    */
    XtInheritSetValuesAlmost,                 /* set_values_almost  */
    NULL,                                     /* get_values_hook    */
    NULL,                                     /* accept_focus       */
    XtVersion,                                /* version            */
    NULL,                                     /* callback_private   */
    XtInheritTranslations,                                     /* tm_table           */
    NULL,                                     /* query_geometry     */
    NULL,                                     /* display_accelerator*/
    NULL,                                     /* extension          */
},
{
   /* composite_class fields */
     GeometryManager,                           /* geometry_manager */
     ChangeManaged,                             /* change_managed */
    XtInheritInsertChild,                      /* insert_child    */
    XtInheritDeleteChild,                      /* delete_child    */
    NULL,                                      /* extension       */
},
{ 
    /* constraint_class fields */
    treeConstraintResources,                   /* subresources      */
    XtNumber ( treeConstraintResources ),      /* subresource_count */
    sizeof ( XsTreeConstraintsRec ),           /* constraint_size   */
    ConstraintInitialize,                      /* initialize        */
    ConstraintDestroy,                         /* destroy           */
    ConstraintSetValues,                       /* set_values        */
    NULL,                                      /* extension         */
},
{ 
    /* manager class */
    XtInheritTranslations,                /* translations           */
    NULL,                                 /* syn resources          */
    0,                                    /* num syn_resources      */
    NULL,                                 /* get_cont_resources     */
    0,                                    /* num_get_cont_resources */
    XmInheritParentProcess,               /* parent_process       */
    NULL,                                 /* extension              */
},
{
    /* Tree class fields */
    NULL,                                   /* ignore                 */
}
};

WidgetClass xsTreeWidgetClass = ( WidgetClass ) &xsTreeClassRec;

static void Initialize ( Widget req, Widget new_w,
                         ArgList args, Cardinal *numArgs ) 
{
    XsTreeWidget tw = ( XsTreeWidget ) new_w;
    XsTreeWidget request = ( XsTreeWidget ) req;
 
   /*
    * Make sure the widget’s width and height are 
    * greater than zero.
    */
 
    if ( tw->core.width <= 0 ) 
        tw->core.width = 100;
    if ( tw->core.height <= 0 ) 
        tw->core.height = 100;

    tw->tree.tree_root = ( Widget ) NULL;    
 
   /*
    * Create the hidden root widget.
    */
 
    tw->tree.tree_root = 
             XtVaCreateWidget ( "root", widgetClass, ( Widget ) tw, 
                                XmNwidth,  1,
                                XmNheight, 1,
                                XmNmappedWhenManaged, FALSE,
                                NULL );
   /*
    * Allocate the tables used by the layout algorithm.
    */
 
    tw->tree.horizontal = CreateOffset ( 10 );
    tw->tree.vertical   = CreateOffset ( 10 );
} 
                    
static void ConstraintInitialize ( Widget request, Widget new_w,
                                   ArgList args, Cardinal *numArgs ) 
{
    XsTreeConstraints tree_const = TREE_CONSTRAINT ( new_w );
    XsTreeWidget tw = ( XsTreeWidget ) XtParent ( new_w );
 
   /*
    * Initialize the widget to have no sub-nodes.
    */
 
    tree_const->tree.n_sub_nodes   = 0;
    tree_const->tree.max_sub_nodes = 0;
    tree_const->tree.sub_nodes = ( WidgetList ) NULL;
    tree_const->tree.x         = tree_const->tree.y = 0; 
 
   /*
    * If this widget has a supernode, add it to that 
    * widget’s subnodes list. Otherwise make it a subnode of 
    * the tree_root widget.
    */
 
    if ( tree_const->tree.super_node ) 
        InsertNewNode ( tree_const->tree.super_node, new_w );
    else
        if ( tw->tree.tree_root ) 
            InsertNewNode ( tw->tree.tree_root, new_w );
} 
                    
static Boolean SetValues ( Widget new_w, Widget old, Widget widget, 
                           ArgList args, Cardinal *numArgs ) 
{
    XsTreeWidget tw = ( XsTreeWidget ) new_w;
    XsTreeWidget current = ( XsTreeWidget ) old;
 
    int redraw = FALSE;
 
   /*
    * If the minimum spacing has changed, recalculate the
    * tree layout. NewLayout() does a redraw, so we don’t
    * need SetValues to do another one. The redraw flag is not
    * really needed for this simple function, but set it up
    * to allow for future expansion.
    */
 
    if ( tw->tree.v_min_space != current->tree.v_min_space ||
         tw->tree.h_min_space != current->tree.h_min_space ) 
    { 
        NewLayout ( tw );
        redraw = FALSE;
    }
 
    return ( redraw );
}
                        
static Boolean ConstraintSetValues ( Widget current,
                                     Widget    request,
                                     Widget    new_w, 
                                     ArgList   args, 
                                     Cardinal *numArgs ) 
{
    XsTreeConstraints newconst      = TREE_CONSTRAINT ( new_w );
    XsTreeConstraints current_const = TREE_CONSTRAINT ( current );
    XsTreeWidget tw = ( XsTreeWidget ) XtParent ( new_w );

    /*
     * The book missed this one. We must check that the specified
     * widget is a rect object.
     */

    if (!XtIsRectObj (new_w))
	return (False);    
 
   /*
    * If the super_node field has changed, remove the widget
    * from the old widget's sub_nodes list and add it to the
    * new one.
    */
 
    if ( current_const->tree.super_node != newconst->tree.super_node )
    {
        if ( current_const->tree.super_node ) 
           DeleteNode ( current_const->tree.super_node, new_w );
        
        if ( newconst->tree.super_node ) 
           InsertNewNode ( newconst->tree.super_node, new_w );
        else
	    if ( tw->tree.tree_root ) 	    
		InsertNewNode ( tw->tree.tree_root, new_w );
        
       /*
        * If the Tree widget has been realized, 
        * compute new layout.
        */
        
        if ( XtIsRealized ( tw ) ) 
           NewLayout ( tw );
    } 
 
    return ( False );
}
                        
static void InsertNewNode ( Widget super_node, Widget node ) 
{
    XsTreeConstraints super_const = TREE_CONSTRAINT ( super_node );
    XsTreeConstraints node_const  = TREE_CONSTRAINT ( node );
 
    int index = super_const->tree.n_sub_nodes;
 
    node_const->tree.super_node = super_node;
 
   /*
    * If there is no more room in the sub_nodes array, 
    * allocate additional space.
    */ 
 
    if ( super_const->tree.n_sub_nodes ==
         super_const->tree.max_sub_nodes ) 
    {
        super_const->tree.max_sub_nodes += 
                         ( super_const->tree.max_sub_nodes / 2 ) + 2;
        
        super_const->tree.sub_nodes = 
          (WidgetList) XtRealloc ((char *) super_const->tree.sub_nodes,
                                         ( super_const->tree.max_sub_nodes ) *
                                         sizeof ( Widget ) );
    } 
 
   /*
    * Add the sub_node in the next available slot and 
    * increment the counter.
    */
 
    super_const->tree.sub_nodes[index] = node;
    super_const->tree.n_sub_nodes++;
}
                    
static void DeleteNode ( Widget super_node, Widget node ) 
{
    XsTreeConstraints node_const = TREE_CONSTRAINT ( node );
    XsTreeConstraints super_const;
    int pos, i;
   /*
    * Make sure the super_node exists.
    */
 
    if ( !super_node ) 
        return; 
 
    super_const = TREE_CONSTRAINT ( super_node );
 
   /*
    * Find the sub_node on its super_node’s list.
    */
 
    for ( pos = 0; pos < super_const->tree.n_sub_nodes; pos++ ) 
        if ( super_const->tree.sub_nodes[pos] == node ) 
            break;
 
    if ( pos == super_const->tree.n_sub_nodes )
        return;
   /*
    * Decrement the number of sub_nodes
    */ 
 
    super_const->tree.n_sub_nodes--;
 
   /*
    * Fill in the gap left by the sub_node.
    * Zero the last slot for good luck.
    */
 
    for ( i = pos; i < super_const->tree.n_sub_nodes; i++ ) 
       super_const->tree.sub_nodes[i] = 
                                  super_const->tree.sub_nodes[i+1];
 
    super_const->tree.sub_nodes[super_const->tree.n_sub_nodes] = 0;
}
                        
static void ConstraintDestroy ( Widget w ) 
{ 
    XsTreeConstraints tree_const = TREE_CONSTRAINT ( w );
    XsTreeWidget parent          = ( XsTreeWidget ) XtParent ( w );
    int i;
 
   /* 
    * Remove the widget from its parent’s sub-nodes list and
    * make all this widget’s sub-nodes sub-nodes of the parent.
    */
 
    if ( tree_const->tree.super_node ) 
    { 
        DeleteNode ( tree_const->tree.super_node, w );
        
        for ( i = 0; i < tree_const->tree.n_sub_nodes; i++ ) 
            InsertNewNode ( tree_const->tree.super_node, 
                            tree_const->tree.sub_nodes[i] );

    }
 }
            
static XtGeometryResult GeometryManager ( Widget            w,
                                          XtWidgetGeometry *request,
                                          XtWidgetGeometry *reply ) 
{
    XsTreeWidget tw = ( XsTreeWidget ) XtParent ( w );
 

    /*
     * To allow the Tree widget to change geometries on the fly, becuase
     * a superNode resource has changed, the Tree widget must allow x,y
     * requests.
     */
    
    if ( request->request_mode & CWX )
        w->core.x = request->x;
    if ( request->request_mode & CWY )
        w->core.y = request->y;

    /*
    * Allow all resize requests.
    */
 
    if ( request->request_mode & CWWidth ) 
        w->core.width = request->width;
 
    if ( request->request_mode & CWHeight ) 
        w->core.height = request->height;
 
    if ( request->request_mode & CWBorderWidth ) 
        w->core.border_width = request->border_width;
 
   /*
    * Compute the new layout based on the new widget sizes;
    */
 
    NewLayout ( tw );

    return ( XtGeometryYes );
}
                
static void ChangeManaged ( Widget w ) 
{
    XsTreeWidget tw = ( XsTreeWidget ) w;
    NewLayout ( tw );

    _XmNavigChangeManaged ( w );        
}
    
static void Redisplay ( Widget w, XEvent *event, Region region ) 
{
    XsTreeWidget      tw = ( XsTreeWidget ) w;
    int               i, j;
    XsTreeConstraints tree_const;
    Widget            child;
 
   /*
    * If the Tree widget is visible, redraw all lines and gadgets.
    */
 
    if ( XtIsRealized ( tw ) && tw->core.visible ) 
    {
       /*
        * Redraw all gadgets.
        */
    
        _XmRedisplayGadgets ( w, event, region );

        for ( i = 0; i < tw -> composite.num_children; i++ ) 
        {
            child = tw -> composite.children[i];
            tree_const = TREE_CONSTRAINT ( child );
         
           /*
            * Draw a line between the right edge of each widget
            * and the left edge of each of its sub_nodes. Don’t
            * draw lines from the fake tree_root. Lines are drawn
            * "manhattan" style, so that all lines are either 
            * vertical or horizontal, like this:
            *
            *            |---- node
            *            |
            *   node ----
            *            |
            *            |---- node
            */
         
            if ( child != tw->tree.tree_root && 
                 tree_const->tree.n_sub_nodes ) 
            {
                for ( j = 0; j < tree_const->tree.n_sub_nodes; j++ ) 
                {

                    /*
                     * Any two given nodes can be connected by 
                     * drawing three line segments. The line   
                     * segments can be described using three x  
                     * values and two y values: 
                     *
                     *            x1    midX      x2
                     *            |      |        |
                     *
                     *  y1-              |-------- node
                     *                   |
                     *                   |  
                     *  y2-  node -------|
                     */

                    int x1 = XtX ( child ) + XtWidth ( child );
                    int y1 = XtY ( child ) + XtHeight ( child ) / 2;
                    int x2 = XtX ( tree_const->tree.sub_nodes[j] );
                    int y2 = XtY ( tree_const->tree.sub_nodes[j] ) + 
                        XtHeight ( tree_const->tree.sub_nodes[j] ) / 2;
                    int midX = x1 + ( x2 - x1 ) / 2;
                     
                   /* 
                    *  Draw the first line, once for the bottom  
                    *  shadow and once for the top, one pixel lower.
                    */
                 
                    XDrawLine ( XtDisplay ( tw ) , XtWindow ( tw ) , 
                                tw->manager.top_shadow_GC,
                                x1, y1, midX, y1 );
                    XDrawLine ( XtDisplay ( tw ) , XtWindow ( tw ) , 
                                tw->manager.bottom_shadow_GC,
                                x1,   y1 + 1, 
                                midX, y1 + 1 );
                     
                   /* 
                    *  Draw the other horizontal line, both bottom  
                    *  shadow and top shadow.
                    */
                 
                    XDrawLine ( XtDisplay ( tw ) , XtWindow ( tw ) , 
                                tw->manager.top_shadow_GC,
                                midX, y2, x2,   y2 );
                    XDrawLine ( XtDisplay ( tw ) , XtWindow ( tw ) , 
                                tw->manager.bottom_shadow_GC,
                                midX, y2 +1,
                                x2,   y2 + 1 );
                   /*
                    *  Because the "etched" lines are not   
                    *  symmetrical, the coordinates of the vertical
                    *  lines varies with the direction of the line.
                    */

                    if ( y1 < y2 ) 
                    {
                        XDrawLine ( XtDisplay ( tw ), XtWindow ( tw ),
                                    tw->manager.top_shadow_GC,
                                    midX, y1,
                                    midX, y2 );
                         XDrawLine ( XtDisplay ( tw ), XtWindow ( tw ),
                                    tw->manager.bottom_shadow_GC,
                                    midX + 1, y1,
                                    midX + 1, y2 - 1 );
                    }
                    else if ( y2 < y1 ) 
                    {
                        XDrawLine ( XtDisplay ( tw ), XtWindow ( tw ),
                                    tw->manager.top_shadow_GC,
                                    midX, y1,
                                    midX, y2 + 1 );

                        XDrawLine ( XtDisplay ( tw ), XtWindow ( tw ),
                                    tw->manager.bottom_shadow_GC,
                                    midX + 1, y1,
                                    midX + 1, y2 + 2 );

                    }
                }
            }
        }
    }
}
                                                                                                                                    
static void NewLayout ( XsTreeWidget tw ) 
{
   /*
    * Reset the auxiliary tables.
    */
 
    Reset ( tw->tree.vertical );
    Reset ( tw->tree.horizontal );
 
   /*
    * Compute each widget's x,y position
    */
 
    ComputePositions ( tw, tw->tree.tree_root, 0 );
 
   /*
    * Move each widget into place.
    */
 
    SetPositions ( tw, tw->tree.tree_root, 0 );
 
   /*
    *  Trigger a redisplay of the lines connecting nodes.
    */
 
    if ( XtIsRealized ( tw ) ) 
          XClearArea ( XtDisplay ( tw ), XtWindow ( tw ), 0, 0, 0, 0, TRUE );
}
                    
static int ComputePositions ( XsTreeWidget tw, Widget w, long level )
{
    Position current_hpos, current_vpos;
    int      i, depth = 0;
    XsTreeConstraints tree_const = TREE_CONSTRAINT ( w );
 
   /*
    * Get the current positions for this level.
    */
 
    current_hpos = CurrentPosition ( tw->tree.horizontal, level );
    current_vpos = CurrentPosition ( tw->tree.vertical, level );
 
   /*
    * Set the current horizontal width to the max widths of all
    * widgets at this level.
    */
 
    SetCurrentPosition ( tw->tree.horizontal, level, 
                         MAX ( current_hpos, XtWidth ( w ) ) );
 
   /*
    * If the node has no sub_nodes, just set the vertical 
    * position to the next available space.
    */
 
    if ( tree_const->tree.n_sub_nodes == 0 ) 
    {
        tree_const->tree.y = current_vpos;
    }
    else 
    {
        Widget            first_kid, last_kid;
        XsTreeConstraints const1, const2;
        Position          top, bottom;
        
       /*
        * If the node has sub_nodes, recursively figure the 
        * positions of each sub_node.
        */
        
        for ( i = 0; i < tree_const->tree.n_sub_nodes; i++ ) 
           depth = ComputePositions ( tw, 
                                      tree_const->tree.sub_nodes[i],
                                      level + 1 );
        
       /*
        * Now that the vertical positions of all children are 
        * known, find the vertical extent of all sub_nodes.
        */
        
        first_kid= tree_const->tree.sub_nodes[0];
        last_kid = 
           tree_const->tree.sub_nodes[tree_const->tree.n_sub_nodes-1];
        const1 = TREE_CONSTRAINT ( first_kid );
        const2 = TREE_CONSTRAINT ( last_kid );
        top = const1->tree.y + XtHeight ( first_kid ) / 2; 
        bottom = const2->tree.y + XtHeight ( last_kid ) / 2;
        
       /*
        * Set the node's position to the center of its sub_nodes.
        */
        
         tree_const->tree.y =( top + bottom ) /2 - (XtHeight ( w ) / 2 );
        
       /*
        * If this position is less than the next available 
        * position, correct it to be the next available
        * position, calculate the amount by which all sub_nodes
        * must be shifted, and shift the entire sub-tree.
        */
        
        if ( tree_const->tree.y < current_vpos ) 
        {
           Dimension offset = current_vpos - tree_const->tree.y;

           for ( i = 0; i < tree_const->tree.n_sub_nodes; i++ ) 
              ShiftSubtree ( tree_const->tree.sub_nodes[i], offset );
         
         /*
          * Adjust the next available space at all levels below
          * the current level.
          */
         
           for ( i = level + 1; i <= depth; i++ ) 
           {
              Position pos = CurrentPosition ( tw->tree.vertical,
                                               i );

              SetCurrentPosition ( tw->tree.vertical, i,
                                   pos + offset );
         }
         
         tree_const->tree.y = current_vpos;
         
        }
    }
 
   /*
    * Record the current vertical position at this level.
    */
 
    SetCurrentPosition ( tw->tree.vertical, level,
                         tw->tree.v_min_space + 
                         tree_const->tree.y + XtHeight ( w ) );
 
    return ( MAX ( depth, level ) );
}
                                                                        

static void ShiftSubtree ( Widget w, Dimension offset ) 
{
    int i;
    XsTreeConstraints tree_const = TREE_CONSTRAINT ( w );
 
   /*
    * Shift the node by the offset.
    */
 
    tree_const->tree.y += offset; 
 
   /*
    * Shift each sub-node into place.
    */
 
    for ( i=0; i< tree_const->tree.n_sub_nodes; i++ ) 
        ShiftSubtree ( tree_const->tree.sub_nodes[i], offset );
}
            
static void SetPositions ( XsTreeWidget tw, Widget w, int level ) 
{
    int i;
    Dimension        replyWidth = 0, replyHeight = 0;
    XtGeometryResult result;
 
    if ( w ) 
    {
        XsTreeConstraints tree_const = TREE_CONSTRAINT ( w );
        
       /*
        * Add up the sum of the width’s of all nodes to this 
        * depth, and use it as the x position.
        */
        
        tree_const->tree.x = ( level * tw->tree.h_min_space ) + 
                        SumOfPositions ( tw->tree.horizontal, level );
        
       /*
        * Move the widget into position.
        */
        
        _XmMoveObject ( w, tree_const->tree.x, tree_const->tree.y );
        
       /*
        * If the widget position plus its width or height doesn’t
        * fit in the tree, ask if the tree can be resized.
        */
        
        if ( XtWidth ( tw ) < tree_const->tree.x + XtWidth ( w ) ||
            XtHeight ( tw ) < tree_const->tree.y + XtHeight ( w ) ) 
        {
            result = 
                XtMakeResizeRequest ( ( Widget ) tw, 
                                       MAX ( XtWidth ( tw ),
                                             tree_const->tree.x + 
                                                    XtWidth ( w ) ),
                                       MAX ( XtHeight ( tw ) , 
                                             tree_const->tree.y +
                                                    XtHeight ( w ) ),
                                       &replyWidth, &replyHeight );
         
            /*
             * Accept any compromise.
             */
         
             if ( result == XtGeometryAlmost ) 
                 XtMakeResizeRequest ( ( Widget ) tw, replyWidth,
                                       replyHeight, 
                                       NULL, NULL );
        }
        
       /*
        * Set the positions of all sub_nodes.
        */
        
        for ( i = 0; i < tree_const->tree.n_sub_nodes; i++ ) 
            SetPositions ( tw, 
                           tree_const->tree.sub_nodes[i], level+1 );
 }
}
                                
static XsVariableArray  *CreateOffset ( long size ) 
{
    XsVariableArray  *offset = 
          (XsVariableArray *) XtMalloc ( sizeof ( XsVariableArray ) );
 
    offset->size = size;
 
    offset->array = 
            ( Dimension * ) XtMalloc ( size * sizeof ( Dimension ) );

    Reset ( offset );
 
    return ( offset );
}
    
static void Reset ( XsVariableArray  *offset ) 
{
    long i;
 
    for ( i = 0; i < offset->size; i++ ) 
        offset->array[i] = 0;
}
    
static Position CurrentPosition ( XsVariableArray  *offset,
                                  long              position ) 
{
    if ( position >= offset->size ) 
        return ( 0 );
    else
        return ( offset->array [ position ] );
}
    
static void SetCurrentPosition ( XsVariableArray  *offset,
                                 int               index,
                                 Dimension         value ) 
{
 
    if ( index >= offset->size ) 
    {
        int oldSize = offset->size;
        int i;

        offset->size = index + index / 2;
        offset->array =
             ( Dimension * ) XtRealloc ( ( char* ) offset->array, 
                                offset->size * sizeof ( Dimension ) );

        for ( i = oldSize; i < offset->size; i++ )
            offset->array[i] = 0;
    }
 
    offset->array[index] = value;
}
    
static Position SumOfPositions ( XsVariableArray  *offset,
                                 long              index ) 
{
    int      i;
    Position sum  = 0;
    long     stop = index;
 
    if ( index > offset->size ) 
        stop = offset->size;
 
    for ( i = 0; i < stop; i++ ) 
        sum += offset->array[i];
 
    return ( sum );
}
    
Widget XsCreateScrolledTree ( Widget parent, char *name,
                              ArgList arglist, Cardinal argcount ) 
{
    Widget sw, tw;
    char  *sw_name;
    Arg   *args;
    int    n;

   /*
    * Generate a name for the scrolled window widget by appending
    * the letters "SW" to the name of the Tree widget.
    */

    sw_name = XtMalloc ( strlen ( name ) + 3 ); 
    strcpy ( sw_name, name );
    strcat ( sw_name, "SW" );

   /*
    * Create an ArgList that can be passed into the scrolled window
    * widget after appending some additional arguments. Malloc
    * the list to match the number of arguments passed in, plus
    * one more. Copy all specified arguments to the new list.
    */

    args = ( ArgList ) XtMalloc ( ( argcount + 1 ) * sizeof ( Arg ) );
 
    for ( n = 0; n < argcount; n++ ) 
    {
        args[n].name = arglist[n].name;
        args[n].value = arglist[n].value;
    }
 
    XtSetArg ( args[n], XmNscrollingPolicy, XmAUTOMATIC ); n++;
 
   /*
    * Create an XmScrolledWindow widget, passing in all arguments.
    * The widget will ignore any that don’t apply.
    */

    sw = XtCreateManagedWidget ( sw_name, xmScrolledWindowWidgetClass,
                                parent, args, n );
   /*
    * Create the Tree widget as a child of the scrolled window
    * widget. Pass in the original argument list. Any arguments that 
    * were meant for the scrolled window widget and that are not
    * recognized by the Tree widget will be ignored.
    */

    tw = XtCreateWidget ( name, xsTreeWidgetClass, 
                          sw, arglist, argcount );
   /*
    * Clean up.
    */

    XtFree ( ( char * ) args );
    XtFree ( ( char * ) sw_name );
 
   /*
    * The caller gets a pointer to the Tree widget, not the scrolled
    * window, so if the tree is destroyed, the scrolled window could
    * be left hanging around. Catch destruction of the Tree widget
    * and destroy the scrolled window to prevent this.
    */

    XtAddCallback ( tw, XmNdestroyCallback, 
                    _XmDestroyParentCallback, NULL );
 
    return ( tw );
}
                                                                        
