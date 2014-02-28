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

/******************************************************
 * main.c: Driver for drawing program
 ******************************************************/
#include <Xm/Xm.h>

extern Widget CreateDrawingEditor ( Widget parent );

void main ( int argc, char **argv )
{
    Widget       shell;
    XtAppContext app;
    
    /*
     * Initialize Xt, creating an application shell.
     * Call an external functionmto create the drawing 
     * editor as a child of the shell.
     */

    shell = XtAppInitialize ( &app, "Draw", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

    CreateDrawingEditor ( shell );
    
    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}

