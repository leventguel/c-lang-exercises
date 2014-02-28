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

/*****************************************************
 * explicit.c: Demo programmatic tab group control
 *****************************************************/
#include <Xm/Xm.h>
#include <Xm/Label.h>
#include <Xm/RowColumn.h>
#include <Xm/TextF.h>

static void traverseNextCallback ( Widget    w, 
                                   XtPointer clientData, 
                                   XtPointer callData ) 
{
    XmProcessTraversal ( w,  XmTRAVERSE_NEXT_TAB_GROUP );
}

static char *fields[] = { "Name", "Address", "Phone" };

void main ( int argc, char **argv ) 
{
    XtAppContext app;
    Widget       shell, rc, *editors, *labels;
    int          numFields = XtNumber ( fields );
    int          i;

   /*
    * Initialize Xt
    */

    shell = XtAppInitialize ( &app, "Explicit", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

    rc = XtVaCreateManagedWidget ( "rc", xmRowColumnWidgetClass, shell,
                                  XmNnumColumns,  2, 
                                  XmNpacking,     XmPACK_COLUMN, 
                                  XmNorientation, XmVERTICAL, 
                                  NULL );

    for ( i = 0; i < numFields; i++ ) 
    {
        Widget label = XtCreateManagedWidget ( fields[i],
                                               xmLabelWidgetClass,
                                               rc, NULL, 0 );
    }

    for ( i = 0; i < numFields; i++ ) 
    {
        Widget editor = 
                   XtCreateManagedWidget ( fields[i], 
                                           xmTextFieldWidgetClass,
                                           rc, NULL, 0 );
        if ( i == 0 )
            XtVaSetValues ( rc, XmNinitialFocus, editor, NULL );

        XtAddCallback ( editor, XmNactivateCallback, 
                        traverseNextCallback, NULL );      
    }    

    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

