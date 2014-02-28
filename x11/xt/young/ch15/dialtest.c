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

/********************************************
 * dialtest.c : Test the Dial widget class
 ********************************************/
#include <Xm/Xm.h>
#include "Dial.h"
#include <stdio.h>

static void ValueChangedCallback ( Widget    w,
				   XtPointer clientData, 
                                   XtPointer callData );

void main ( int argc, char **argv )
{
    Widget       shell, dial;
    XtAppContext app;

    shell = XtAppInitialize ( &app, "Dial", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );  
  
   /*
    * Create a Dial widget and add a select callback.
    */

    dial = XtCreateManagedWidget ( "dial", xsDialWidgetClass, 
                                   shell, NULL, 0 );

    XtAddCallback ( dial, XmNvalueChangedCallback, 
                    ValueChangedCallback, NULL );

    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}
            
static void ValueChangedCallback ( Widget    w, 
                                   XtPointer clientData,
                                   XtPointer callData )
{
    XsDialCallbackStruct *cbs = ( XsDialCallbackStruct* ) callData;

    printf ( "Position = %d\n", cbs->value );
}
    
