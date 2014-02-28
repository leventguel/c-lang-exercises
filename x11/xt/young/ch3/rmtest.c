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

/***************************************************
 * rmtest.c: Demo the resource manager
 ***************************************************/
#include <Xm/Xm.h>
#include <stdio.h>

typedef struct {
   int      delay;
   Boolean  verbose;
} GlobalOptionsStruct;

static XtResource resources[] = {
  { "delay", "Delay", XtRInt, sizeof  ( int ),
    XtOffset ( GlobalOptionsStruct *, delay ),
    XtRImmediate,  ( XtPointer )  2 },
  { "verbose", "Verbose", XtRBoolean, sizeof  ( Boolean ),
    XtOffset ( GlobalOptionsStruct *, verbose ), 
    XtRString, "FALSE" },
};

GlobalOptionsStruct globalData;

void main ( int argc, char **argv ) 
{
    Widget          shell;
    XtAppContext    app;

   /*
    * Initialize Xt
    */

    shell = XtAppInitialize ( &app, "Rmtest",  NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );  

   /*
    * Retrieve the application resources.
    */

    XtGetApplicationResources ( shell, &globalData,
                                resources, XtNumber ( resources ), 
                                NULL, 0 );
   /*
    * Print the results and exit.
    */

    printf ( "delay = %d, verbose = %d\n", 
             globalData.delay, globalData.verbose );
}

