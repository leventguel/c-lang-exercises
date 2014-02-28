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
 * wprintf.c: A convenient function that displays text
 *            in a label or button, providing the same
 *            syntax as printf()
 ****************************************************/
/* #include <varargs.h> */
#include <stdarg.h>
#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/Label.h>

void wprintf( void *fmt, ... ) 
{
    Widget    w;
    char      *format;
    va_list   args;
    char      str[4096];  /* DANGER: Fixed buffer size */
    Arg       wargs[1];
    XmString  xmstr;
    
    /*
     * Init the variable length args list.
     */
    
    va_start( args, fmt );
    
    /*
     * Extract the destination widget.
     * Make sure it is a subclass of XmLabel.
     */
    
    w = va_arg( args, Widget );
    
    if ( !XtIsSubclass ( w, xmLabelWidgetClass )  ) 
        XtError ( "wprintf ()  requires a Label Widget" );
    
    /*
     * Extract the format to be used.
     */
    
    format = va_arg( args, void* );
    
    /*
     * Use vsprintf to format the string to be displayed in the
     * XmLabel widget, then convert it to a compound string
     */
    
    vsprintf( str, format, args );
    
    xmstr =  XmStringCreateLtoR( str, XmFONTLIST_DEFAULT_TAG );
    
    XtVaSetValues( w, XmNlabelString, xmstr, NULL );

    XmStringFree( xmstr );
    
    va_end( args );
}

