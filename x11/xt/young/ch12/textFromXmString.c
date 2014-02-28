/************************************************************
 * TextFromXmString.c: Retrieve the text components
 *                     from a multi-segment compound string
 *                     Treat separators as newlines
 ************************************************************/
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
            strcat ( buf, text );                        
            XtFree ( text ); 
        }
        
       /* 
        * If the next segment is a separator, append a newline
        */

        if ( separator )
        {
             buf = XtRealloc ( buf, length + 2 );
             strcat ( buf, "\n" );                        
        }

        length += strlen ( buf );
     }
   
     XmStringFreeContext ( context );

     return ( buf );
}
                            
