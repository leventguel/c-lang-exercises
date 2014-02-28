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

/*******************************************************************
 * getpixelbyname.c: Get a Pixel value to represent a named color
 *******************************************************************/
#include <Xm/Xm.h>

Pixel GetPixelByName ( Widget w, char *colorname ) 
{
    Display *dpy  = XtDisplay ( w );
    int      scr  = DefaultScreen ( dpy );
    Colormap cmap = DefaultColormap ( dpy, scr );
    XColor   color, ignore;

   /* 
    * Allocate the named color.
    */

    if ( XAllocNamedColor ( dpy, cmap, colorname, &color, &ignore ) ) 
        return ( color.pixel );
    else
    {
        XtWarning ( "Couldn't allocate color" );

        return ( BlackPixel ( dpy, scr ) );
    }
}
                
main()
{
    printf("This isn't a complete program, just an example function\n");
}
