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
 * rmtest3.c: Test the StringToDebug type converter
 ****************************************************/
#include <Xm/Xm.h>
#include <stdio.h>
#include "dbg.h"

unsigned char debugLevel;

static XtResource resources[] = {
{ XmNdebugLevel, XmCDebugLevel, XmRDebugLevel, sizeof ( unsigned char ),
  ( Cardinal ) &debugLevel, XmRImmediate,  ( XtPointer )  LEVEL0 },
};

static XrmOptionDescRec options[] = { 
  { "-debug",   "*debugLevel",   XrmoptionSepArg, NULL }
};

void main ( int argc, char **argv ) 
{
    Widget       shell;
    XtAppContext app;

   /*
    * Initialize Xt
    */
    
    shell = XtAppInitialize ( &app, "Rmtest",
      			      options, XtNumber ( options ),
                              &argc, argv, NULL, NULL, 0 );  

   /*
    * Add the string to debug level type-converter.
    */

    XtSetTypeConverter ( XmRString, XmRDebugLevel,
                         CvtStringToDebugLevel,
                         ( XtConvertArgList )  NULL, 0,
                         XtCacheAll,  ( XtDestructor )  NULL );
   /*
    * Retrieve the resources.
    */

    XtGetApplicationResources ( shell, 0, resources, 
                                XtNumber ( resources ), NULL, 0 );
   /*
    * Print the result.
    */

    if ( debugLevel == LEVEL0 ) 
        printf ( "Debugging disabled\n" );
    else
        printf ( "debugging LEVEL%d enabled\n", debugLevel );
}

