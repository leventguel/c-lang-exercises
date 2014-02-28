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

/****************************************************************
 * driver.c: Driver program for experimenting with text fields
 ****************************************************************/
#include <Xm/Xm.h>
#include <Xm/TextF.h>
#include <stdio.h>

/* Function declarations */

extern Widget CreateInputField ( Widget parent );
static void EnterCallback ( Widget    w,
                            XtPointer clientData, 
                            XtPointer callData);

void main ( int argc, char **argv )
{
    Widget       shell, text;
    XtAppContext app;
    
   /*
    * Initialize Xt
    */
    
    shell = XtAppInitialize ( &app, "Inputtest", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

   /*
    * Create an input field and register a callback to 
    * be called when the user types a <Return> key
    */

    text = CreateInputField ( shell );

    XtAddCallback ( text, XmNactivateCallback, EnterCallback, NULL);

   /*
    * Realize the shell and enter the event loop.
    */
    
    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

extern char *GetPassword();

static void EnterCallback ( Widget    w,
                            XtPointer clientData, 
                            XtPointer callData )
{
    printf ( "text entered = %s\n", GetPassword() );
}

