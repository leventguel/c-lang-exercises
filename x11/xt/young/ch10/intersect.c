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

/***********************************************************
 * intersect.c: Demonstrate simple use of Region functions.
 *              Determine whether two Regions intersect.
 ***********************************************************/
#include <X11/Xlib.h>
#include <X11/Xutil.h> /* Contains Region declarations */


int DoesIntersect ( Region region1, Region region2 )
{
    int    is_empty;
    Region intersection;

   /*
    * Create the empty intersection region.
    */

   intersection = XCreateRegion();

   /*
    * Get the intersection of the two regions.
    */

   XIntersectRegion ( region1, region2, intersection );

   /*
    * Check whether the result is an empty region.
    */

   is_empty = XEmptyRegion ( intersection );

   /*
    * Free the region before returning the result.
    */

   XDestroyRegion ( intersection );

   return ( !is_empty );
}

main()
{
    printf("Not a complete program. Just a function\n");
}
