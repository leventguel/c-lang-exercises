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
 * dbg.c: An example Xt type converter
 *****************************************/
#include "dbg.h"
#include <strings.h>

Boolean CvtStringToDebugLevel ( Display     *dpy,
				XrmValue    *args,
				Cardinal    *nargs,
				XrmValue    *fromVal,
				XrmValue    *toVal,
				XtPointer   *data ) 
{
    static DebugLevel result;

   /*
    * Make sure the number of args is correct.
    */

    if ( *nargs != 0 ) 
        XtWarning ( "String to DebugLevel conversion needs no args" );

   /*
    * Convert the string in the fromVal to a DebugLevel
    */

    if ( !strcasecmp ( fromVal->addr, "LEVEL0" ) ) 
        result =  LEVEL0;
    else if ( !strcasecmp ( fromVal->addr, "LEVEL1" ) ) 
        result =  LEVEL1;
    else if ( !strcasecmp ( fromVal->addr, "LEVEL2" ) ) 
        result =  LEVEL2;
    else if ( !strcasecmp ( fromVal->addr, "LEVEL3" ) ) 
        result =  LEVEL3;
    else if ( !strcasecmp ( fromVal->addr, "LEVEL4" ) ) 
        result =  LEVEL4;
    else 
    {
        XtDisplayStringConversionWarning( dpy, 
					   fromVal->addr, 
                                           XmRDebugLevel );
        return FALSE;
    }

   /*
    * Make toVal point to the result.
    */

    toVal->size = sizeof ( DebugLevel ); 
    *( ( DebugLevel* ) toVal->addr ) = result; 

    return ( TRUE );
}

