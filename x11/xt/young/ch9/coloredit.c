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

/****************************************************
 * coloredit.c: A simple color palette editor
 ****************************************************/
#include <Xm/Xm.h>

#define NUMCOLORS   16

extern Widget CreatePaletteEditor ( Widget parent, int ncolors );

void main ( int argc, char **argv ) 
{
    XtAppContext app;
    Widget    shell, colorEditor;

   /*
    * Initialize Xt
    */
    
    shell = XtAppInitialize ( &app, "Coloredit", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );

   /* Create the color editor UI */

    colorEditor = CreatePaletteEditor ( shell, NUMCOLORS );

   /* Realize widgets and enter event loop */

    XtRealizeWidget ( shell );

    XtAppMainLoop ( app );
}
                                
