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


/****************************************************************
 * textFromXmString.c: Retrieve the text components
 *                        from a multi-segment compound string
 *                        Treat separators as newlines
 ***************************************************************/
#include <Xm/Xm.h>

char *GetTextFromXmstring ( XmString xmstr ) 
{ 
    XmStringContext   context; 
   char             *text; 
   XmStringCharSet   tag; 
   XmStringDirection dir; 
   Boolean           separator; 
   char             *buf = NULL; 
   int               length;

   XmStringInitContext ( &context, xmstr );

   length = 0;
   while ( XmStringGetNextSegment ( context, &text, &tag,
                                    &dir, &separator ) )
   { 
       /* Allocate room for the text and copy the retrieved text 
        * into the buffer 
        */

        if ( text )
        {
            buf = XtRealloc ( buf, length + strlen ( text ) + 1 );
	    if(length == 0)
		strcpy ( buf, text );
	    else
		strcat ( buf, text );

	    length += strlen ( text );
	    
            XtFree ( text ); 
        }
        
        /* 
         * If the next segment is a separator, append a newline
        */

        if ( separator )
        {
             buf = XtRealloc ( buf, length + 2 );
             strcat ( buf, "\n" );
	     length += 2;
        }
     }
   
     XmStringFreeContext ( context );

     return buf;
}

