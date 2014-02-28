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

/***************************************************************
 * getpixel.c: Implement GetPixel(), a function that allocates 
 *             a color to represent the given rgb value
 ***************************************************************/
#include <Xm/Xm.h> 

Pixel GetPixel ( Widget w, short red, short green, short blue ) 
{
    Display *dpy  = XtDisplay ( w );
    int      scr  = DefaultScreen ( dpy );
    Colormap cmap = DefaultColormap ( dpy, scr );
    XColor   color;

   /* 
    * Fill in the color structure.
    */

    color.red   = red;
    color.green = green;
    color.blue  = blue;
    color.flags = DoRed | DoGreen | DoBlue;

   /* 
    * Try to allocate the color.
    */

    if ( XAllocColor ( dpy, cmap, &color ) ) 
      return ( color.pixel );
    else 
    {
       XtWarning ( "Couldn't allocate requested color" );
       return ( BlackPixel ( dpy, scr ) );
    }
}
                        
main()
{
    printf("This isn't a complete program, just an example function\n");
}
