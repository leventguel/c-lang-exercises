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

/************************************************
 * list.c: Use different fonts in a list widget
 ************************************************/
#include <Xm/Xm.h>
#include <Xm/List.h>

void main ( int argc, char **argv )
{
    Widget       shell, list;
    XmString    xmstr[4];
    XtAppContext app;

    shell = XtAppInitialize ( &app, "List",  NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );
   /*
    * Create an array of compound strings to be displayed in the
    * list widget. Each item can have its own font tag.
    */

    xmstr[0] = XmStringCreateLtoR ("Normal", XmFONTLIST_DEFAULT_TAG );
    xmstr[1] = XmStringCreateLtoR ("bold",   "bold" );
    xmstr[2] = XmStringCreateLtoR ("italic", "italic" );
    xmstr[3] = XmStringCreateLtoR ("Normal", XmFONTLIST_DEFAULT_TAG );

   /*
    * Create the list widget.
    */

    list = XmCreateScrolledList ( shell, "list", NULL, 0 );
    XtManageChild ( list );

    XtVaSetValues ( list,
                    XmNitems,            xmstr,
                    XmNitemCount,        4,
                    XmNvisibleItemCount, 4,
                    NULL );

    XtRealizeWidget ( shell );

    XtAppMainLoop ( app );
}
                    
