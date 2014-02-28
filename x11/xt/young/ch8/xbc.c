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

/*****************************************
 * xbc:An X interface to bc
 *****************************************/
#include <Xm/Xm.h>
extern Widget  CreateCalculator ( Widget parent );

void main ( int argc, char **argv ) 
{
    Widget       shell;
    XtAppContext app;
    
    /*
     * Initialize Xt
     */
    
    shell = XtAppInitialize ( &app, "XBc", NULL,  0, 
                              &argc, argv, NULL,  NULL, 0 );
    /* 
     * Create the UI for xbc
     */

    CreateCalculator ( shell );

    /*
     *  Realize the shell and enter the event loop
     */

    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}
                        
