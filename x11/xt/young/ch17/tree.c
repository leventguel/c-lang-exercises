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

/********************************************************************
 * tree.c: Display tree from parent child pairs read from stdin
 ********************************************************************/
#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/DrawnB.h>
#include <Xm/PushBG.h>
#include <Xm/ScrolledW.h>
#include "Tree.h"

void main ( int argc, char **argv )
{
    Widget        shell, tree;
    XtAppContext  app;
    char          parent[500], parentLabel[500], 
                  child[500], childLabel[500];
 
    shell = XtAppInitialize ( &app, "Ttree", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 ); 
 
   /*
    * Create a scrolled tree.
    */
 
    tree = XsCreateScrolledTree ( shell, "tree", NULL, 0 );
    XtManageChild ( tree );

   /*
    * Read node relationships and labels from stdin.
    */
 
    while ( scanf ( "%s %s %s %s", &parent, &parentLabel,
                                   &child, &childLabel ) != EOF )
    {
        Widget p, c;
        
       /*
        * If a parent identifier was read, check to see if this name
        * has already been used as a widget. If so, use the existing
        * widget as the supernode of the given child.
        */
 
        if ( parent )
            p = XtNameToWidget ( tree, parent );

        if ( !p )
        {
           /*
            * Otherwise, create a new widget for this node.
            */

            p = XtVaCreateManagedWidget ( parent, 
                                          xmPushButtonGadgetClass,
                                          tree,
                                          XtVaTypedArg, XmNlabelString,
                                          XmRString,    parentLabel, 
                                          strlen ( parentLabel ) + 1,
                                          NULL );
        }

       /*
        * If a child identifier was read, check to see if this name
        * has already been used as a widget. If so, use the existing
        * widget as the subnode of the given parent.
        */

        if ( child )
            c = XtNameToWidget ( tree, child );

        if ( !c )
        {

           /*
            * Otherwise, create a new widget for this node.
            */

            c =XtVaCreateManagedWidget ( child, 
                                         xmDrawnButtonWidgetClass,
                                         tree,
                                         XmNsuperNode, p, 
                                         XtVaTypedArg, XmNlabelString,
                                         XmRString,    childLabel, 
                                         strlen ( childLabel ) + 1,
                                         NULL );
        }
    }

    XtRealizeWidget ( shell );

    XtAppMainLoop ( app );
}
                                                
