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
 * xclock: Demonstrate the use of timeout callbacks
 *****************************************************/
#include <Xm/Xm.h>
#include <Xm/Label.h>
#include <time.h>

extern void wprintf ( Widget w, const char * format, ... );
static void UpdateTime ( XtPointer    clientData,
                         XtIntervalId id );
  
void main ( int argc, char **argv ) 
{
    Widget       shell, face;
    XtAppContext app ;

    shell = XtAppInitialize ( &app, "XClock",  NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );
    
    face = XtCreateManagedWidget ( "face", xmLabelWidgetClass,
                                   shell, NULL, 0 );
   /*
    * Get the initial time.
    */
    
    UpdateTime ( ( XtPointer ) face, NULL );
    
    XtRealizeWidget ( shell );
    XtAppMainLoop ( app );
}
            
static void UpdateTime ( XtPointer clientData, XtIntervalId id ) 
{
    Widget w = ( Widget ) clientData;
    long   tloc, rounded_tloc, next_minute;
    
   /*
    * Get the system time.
    */
    
    time ( &tloc );
    
   /*
    * Convert the time to a string and display it,
    * after rounding it down to the last minute.
    */
    
    rounded_tloc = tloc / 60 * 60;
    
    wprintf ( w, "%s", ctime ( &rounded_tloc ) );
    
   /*
    * Adjust the time to reflect the time until
    * the next round minute.
    */
    
    next_minute = ( 60 - tloc % 60 ) * 1000;
    
   /*
    * Xt removes timeouts when they occur,
    * so re-register the function.
    */
    
    XtAppAddTimeOut ( XtWidgetToApplicationContext ( w ),   
                      next_minute, UpdateTime, ( XtPointer ) w );
}
                                
