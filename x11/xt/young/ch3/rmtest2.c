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

/*****************************************************
 * rmtest2.c: Test the use of command-line arguments
 *****************************************************/
#include <Xm/Xm.h>
#include <stdio.h>

typedef struct {
   int      delay;
   Boolean  verbose;
} GlobalOptionsStruct;

static XtResource resources[] = {
{ "delay", "Delay", XmRInt, sizeof  ( int ),
  XtOffset ( GlobalOptionsStruct *, delay ),
  XmRImmediate,  ( XtPointer )  2 },
{ "verbose", "Verbose", XmRBoolean, sizeof  ( Boolean ),
  XtOffset ( GlobalOptionsStruct *, verbose ), 
  XmRString, "FALSE" },
};

XrmOptionDescRec options[] = {
  { "-verbose", "*verbose", XrmoptionNoArg, "TRUE" },
  { "-delay",   "*delay",   XrmoptionSepArg, NULL  }
};

GlobalOptionsStruct globalData;

void main ( int argc, char **argv ) 
{
    Widget       shell;
    XtAppContext app;

    shell = XtAppInitialize ( &app, "Rmtest",			 
                              options, XtNumber ( options ),
                              &argc, argv, NULL, NULL, 0 );  

   /*
    * Retrieve the application resources
    */

    XtGetApplicationResources ( shell, &globalData, resources, 
                                XtNumber ( resources ), NULL, 0 );
   /*
    * Print the results.
    */

    printf ( "delay = %d, verbose = %d\n", 
	             globalData.delay, globalData.verbose );
}

