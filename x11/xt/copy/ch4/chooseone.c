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

/*****************************************************************
 * chooseone.c: Allow the user to select a command-line argument
 *****************************************************************/
#include <Xm/Xm.h>
#include <Xm/List.h>
#include <stdio.h>
#include <stdlib.h>

static void BrowseCallback ( Widget widget, 
                            XtPointer clientData, 
                            XtPointer callData );

const char usageString[] = "Usage: chooseone <non-zero list of choices>";

void main ( int argc, char **argv )
{
    Widget       shell, list;
    int          i;
    XmString    *xmstr;
    XtAppContext app;

    shell = XtAppInitialize ( &app, "Chooseone",  NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

    if ( argc <= 1 )
    {
        fprintf ( stderr, usageString );
        exit ( -1 );
    }

   /*
    * Convert all command-line arguments to an array of
    * type XmString, ignoring argv[0].
    */

    xmstr = ( XmString * ) XtMalloc ( sizeof ( XmString ) * argc - 1 );

    for ( i = 1; i < argc; i++ )
      xmstr [ i - 1 ] = XmStringCreateLtoR ( argv[i],
                                             XmFONTLIST_DEFAULT_TAG );

   /*
    * Create the list widget and register a browse callback.
    */

    list = XmCreateScrolledList ( shell, "list", NULL, 0 );
    XtManageChild ( list );

    XtVaSetValues ( list,
                    XmNitems,            xmstr,
                    XmNitemCount,        argc - 1,
                    XmNvisibleItemCount, 20,
                    NULL );

    XtAddCallback ( list, XmNbrowseSelectionCallback, 
                    BrowseCallback, NULL );

    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

static void BrowseCallback ( Widget    w, 
                             XtPointer clientData, 
                             XtPointer callData)
{
   XmListCallbackStruct *cbs = ( XmListCallbackStruct * ) callData;
   Boolean  result;
   char    *text;

  /*
   * Retrieve the character data from the compound string
   */

   if ( ( result = XmStringGetLtoR ( cbs->item, 
                                     XmFONTLIST_DEFAULT_TAG,
                                     &text ) ) == TRUE )
   {
      /*
       * If some text was retrieved, print it. Normally, this data 
       * should be freed, but the program is going to exit, anyway.
       */

       printf ( "%s\n", text );
   }

   exit ( 0 );
}

