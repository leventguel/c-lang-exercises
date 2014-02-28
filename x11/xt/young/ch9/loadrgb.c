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

/********************************************************
 * loadrgb.c: Implement LoadRGB(), a sample function 
 *            that allocates and returns three colors
 ********************************************************/
#include <Xm/Xm.h>

void LoadRGB ( Widget w, Pixel *red, Pixel *green, Pixel *blue ) 
{
    Display *dpy  = XtDisplay ( w );
    int      scr  = DefaultScreen ( dpy );
    Colormap cmap = DefaultColormap ( dpy, scr );
    XColor   color;
    Pixel    cells[3];

   /*
    *  Try to allocate three consecutive color cells.
    */

    if ( XAllocColorCells ( dpy, cmap, True, 
                            NULL, 0, cells, 3 ) ) 
    {

       /* 
        *  If successful, create a red color struct, and store
        *  it in the first allocated cell. 
        */

        color.red = 65535;
        color.green = color.blue = 0;
        *red = color.pixel = cells[0];
        XStoreColor ( dpy, cmap, &color );

       /*
        *  Store green in the second cell.
        */

        color.green = 65535;
        color.red   =  color.blue = 0;
       *green = color.pixel = cells[1];
        XStoreColor ( dpy, cmap, &color );

       /* 
        * Store blue in the second cell.
        */

        color.blue = 65535;
        color.red  = color.green = 0;
        *blue = color.pixel = cells[2];
        XStoreColor ( dpy, cmap, &color );
    }
    else
    {
        XtWarning ( "Couldn't allocate color cells" );

        *blue = *red = *green = BlackPixel ( dpy, scr );
    }
}
                                    

main()
{
    printf("This isn't a complete program, just an example function\n");
}
