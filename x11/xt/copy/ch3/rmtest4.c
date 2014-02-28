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

/*******************************************************
 * rmtest4.c: Test Motif's enumerated type converter
 *******************************************************/
#include <Xm/Xm.h>
#include <Xm/RepType.h>
#include <stdio.h>

typedef enum  { LEVEL0, LEVEL1, LEVEL2, LEVEL3, LEVEL4 } DebugLevel;
char *debugLevelNames[] = {
     "level0", "level1", "level2", "level3", "level4"
};

#define XmNdebugLevel "debugLevel"
#define XmCDebugLevel "DebugLevel"
#define XmRDebugLevel "DebugLevel"

unsigned char debugLevel;

static XtResource resources[] = {
{ XmNdebugLevel, XmCDebugLevel, XmRDebugLevel, sizeof  ( unsigned char ),
    ( Cardinal ) &debugLevel, XmRImmediate,  ( XtPointer )  LEVEL0 },
};

static XrmOptionDescRec options[] = { 
  {"-debug", "*debugLevel", XrmoptionSepArg, NULL}
};

void main ( int argc, char **argv ) 
{
    Widget       shell;
    XtAppContext app;
    XmRepTypeId  id;
    
   /*
    * Initialize Xt
    */
    
    shell = XtAppInitialize ( &app, "Rmtest",
                              options, XtNumber ( options  ),
                              &argc, argv, NULL, NULL, 0  );  

   /*
    *   Add the string to debug level type-converter.
    */

    id = XmRepTypeRegister ( XmRDebugLevel,
                             debugLevelNames, NULL, 
                             XtNumber ( debugLevelNames ) );
   /*
    *  Retrieve the resources.
    */

    XtGetApplicationResources ( shell, 0, resources, 
                                XtNumber ( resources  ), NULL, 0 );
   /*
    * Print the result. Check the result just to demonstrate
    * how this function is called. Note that by the time we get here,
    * the type converter will have assured that the value is within
    * range, so this check is redundant in this case.
    */

    if ( XmRepTypeValidValue ( id, debugLevel, shell ) )
    {
       	if ( debugLevel == LEVEL0  ) 
            printf ( "Debugging disabled\n"  );
       	else
            printf ( "debugging LEVEL%d enabled\n", debugLevel );
    }
}

