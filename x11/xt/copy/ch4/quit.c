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

/*******************************************************
 * quit.c: A utility function that adds a quit button 
 *******************************************************/
#include <Xm/Xm.h>
#include <Xm/PushB.h>

/* 
 * Define three callbacks. Make them static - no need 
 * to make them known outside this file.
 */

static void ArmCallback ( Widget    w,
                          XtPointer clientData, 
                          XtPointer callData )
{
    int *flag = ( int * ) clientData;

    *flag = FALSE; /* Initialize a flag when the button is pressed */
}

static void ActivateCallback ( Widget    w,
                               XtPointer clientData, 
                               XtPointer callData )
 {
    int *flag = ( int * ) clientData;

    /* Set the flag to indicate that the button 
       has been activated. */

    *flag = TRUE;
}

static void DisarmCallback ( Widget    w,
                             XtPointer clientData, 
                             XtPointer callData )
{
    int * flag = ( int * ) clientData;

    if ( *flag )
       exit ( 0 );
}
/* 
 * Function to add a quit button as a child of any widget.
 */

Widget CreateQuitButton ( Widget parent )
{
    Widget     w;
    static int reallyQuit;

    w = XtCreateManagedWidget ( "quit", xmPushButtonWidgetClass,
                                 parent, NULL, 0 );

    XtAddCallback ( w, XmNarmCallback, 
                    ArmCallback, ( XtPointer ) &reallyQuit );
    XtAddCallback ( w, XmNdisarmCallback, 
                    DisarmCallback, ( XtPointer ) &reallyQuit );
    XtAddCallback ( w, XmNactivateCallback, 
                    ActivateCallback, ( XtPointer ) &reallyQuit );   
    return ( w );
}

