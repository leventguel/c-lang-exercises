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

/***********************************************************
 * sort.c: Display a binary sort tree using the tree widget.
 ***********************************************************/
#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/Label.h>
#include <Xm/PushB.h>
#include <Xm/ScrolledW.h>
#include "Tree.h"

/*
 * Define the structure for a node in the binary sort tree.
 */

typedef struct _node {
   int           key;
   struct _node *left;
   struct _node *right;
} Node;

Node *InsertNode ( int key,
                   Node *head );
Node *MakeNode ( int key );
void ShowTree ( Widget  parent,
                Node   *branch,
                Widget  super_node);
void main ( int argc, char **argv )
{
    Widget        shell, sw, tree;
    Node         *head = NULL;
    int           digit, i; 
    XtAppContext  app;
 
   /*
    * Initialize Xt.
    */
 
    shell = XtAppInitialize ( &app, "Sort", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 ); 
 
   /*
    * Create a scrolled tree.
    */
 
    tree = XsCreateScrolledTree ( shell, "tree", NULL, 0 );

    XtManageChild ( tree );
 
   /*
    * Create a binary sort tree from data read from stdin.
    */
 
    while ( scanf("%d", &digit) != EOF )
        head = InsertNode ( digit, head );
 
   /*
    * Create the widgets representing the tree.
    */
 
    ShowTree ( tree, head, NULL );
    XtRealizeWidget ( shell );

    XtAppMainLoop ( app );
}

Node *InsertNode ( int   key,
                   Node *head )
{
    Node *prev, *ptr = head;
 
   /*
    * If the tree doesn’t exist, just create and 
    * return a new node.
    */
 
    if ( !head )
        return ( MakeNode ( key ) );
 
   /*
    * Otherwise, find a leaf node, always following the 
    * left branches if the key is less than the value in each 
    * node, and the right branch otherwise.
    */
 
    while ( ptr != NULL )
    {
        prev = ptr; 
        ptr = ( key < ptr->key ) ? ptr->left : ptr->right;
    } 
 
   /*
    * Make a new node and attach it to the appropriate branch.
    */
 
    if ( key < prev->key )
        prev->left = MakeNode ( key );
    else 
        prev->right = MakeNode (key );
 
    return ( head );
}
Node *MakeNode ( int key )
{
    Node *ptr = ( Node * ) XtMalloc ( sizeof ( Node ) );
 
    ptr->key  = key;
    ptr->left = ptr->right = NULL;
 
    return ( ptr );
}

void ShowTree ( Widget  parent,
                Node   *branch,
                Widget  super_node)
{
    Widget w;
    char   buf[10];
 
    /*
     * If we’ve hit a leaf, return.
     */
 
    if ( !branch ) 
      return;
 
   /*
    * Create a widget for the node, specifying the
    * given super_node constraint.
    */
 
    sprintf ( buf, "%d", branch->key );
 
    w = XtVaCreateManagedWidget ( buf, xmPushButtonWidgetClass, 
                  	   parent, 
                           XmNsuperNode, super_node, 
                           NULL );
  /*
   * Recursively create the subnodes, giving this node’s 
   * widget as the super_node.
   */
 
   ShowTree ( parent, branch->left,  w );
   ShowTree  (parent, branch->right, w );
}

