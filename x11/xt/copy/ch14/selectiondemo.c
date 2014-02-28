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
 * selectiondemo.c: A simple demo of X selection functions
 ***********************************************************/
#include <Xm/Xm.h>
#include <Xm/Label.h>
#include <Xm/MainW.h>
#include "MenuSupport.h"
#include <X11/Xatom.h>
#include <stdio.h>

Widget    msg, selectionLabel;
Atom      TARGETS, DELETE;
Atom      COMPOUND_TEXT;
Atom      current_type = XA_STRING;
char *GetTextFromXmstring ( XmString string ) ;
extern void wprintf ( Widget w, const char *format, ... );
static void  SetStringType ( Widget    w, 
                             XtPointer clientData, 
                             XtPointer callData );

static void  SetCTType ( Widget    w, 
                         XtPointer clientData, 
                         XtPointer callData );
static void SetTargetType ( Widget    w,
                            XtPointer clientData,
                            XtPointer callData );

static void LoseSelection ( Widget w, Atom *selection );
static Boolean ConvertSelection ( Widget         w, 
                                  Atom          *selection, 
                                  Atom          *target,
                                  Atom          *type, 
                                  XtPointer     *value, 
                                  unsigned long *length, 
                                  int           *format );

static void ToggleType ( Widget    w, 
                         XtPointer clientData, 
                         XtPointer callData );
static void ShowSelection ( Widget        w, 
                            XtPointer     clientData, 
                            Atom         *selection, 
                            Atom         *type,
                            XtPointer     value, 
                            unsigned long *length, 
                            int          *format );
static void RequestSelection ( Widget    w, 
                               XtPointer clientData, 
                               XtPointer callData );
static void OwnSelection ( Widget    w, 
                           XtPointer clientData, 
                           XtPointer callData );

 static MenuDescription selectionPaneDesc[] = {
  { BUTTON,   "OwnSelection",       OwnSelection     },
  { BUTTON,   "RequestSelection",   RequestSelection },
  { NULL }
};

static MenuDescription typePaneDesc[] = {
  { TOGGLE,   "String",           SetStringType },
  { TOGGLE,   "CompoundString",   SetCTType     },
  { TOGGLE,   "Targets",          SetTargetType },
  { NULL }
};

static MenuDescription menuBarDesc[] = {
  { PULLDOWN,        "Selection",   NULL, NULL, selectionPaneDesc },
  { RADIOPULLDOWN,   "Type",        NULL, NULL, typePaneDesc },
  { NULL }
};
        
void main ( int argc, char **argv )
{
    Widget   shell, mainWindow;
    XtAppContext app;

   /*
    * Initialize Xt
    */
    
    shell = XtAppInitialize ( &app, "Clipboard", NULL, 0, 
                              &argc, argv, NULL, NULL, 0 );
   /*
    * Intern atoms used to identify data types and 
    * selection targets.
    */

    COMPOUND_TEXT = XInternAtom ( XtDisplay ( shell ), 
                                  "COMPOUND_TEXT", FALSE );
    TARGETS = XInternAtom ( XtDisplay ( shell ), 
                            "TARGETS", FALSE );
    DELETE = XInternAtom ( XtDisplay  ( shell ), 
                           "DELETE", FALSE );
   /*
    * Create window layout. A main window widget holds a menu bar,
    * a label to display the value of the selection, and another
    * another used to display status.
    */

    mainWindow = XtCreateManagedWidget ( "mainWindow",
                                        xmMainWindowWidgetClass,
                                        shell, NULL, 0 );

   CreateMenu ( MENUBAR, "menuBar", mainWindow, menuBarDesc, NULL );
    
   selectionLabel = XtCreateManagedWidget ( "label",
                                            xmLabelWidgetClass,
                                            mainWindow, NULL, 0 );

   msg = XtCreateManagedWidget ( "msgArea",
                                 xmLabelWidgetClass,
                                 mainWindow, NULL, 0 );

    XtVaSetValues ( mainWindow, XmNmessageWindow, msg, NULL );

    XtRealizeWidget ( shell );

    XtAppMainLoop ( app );

}
                            
static void RequestSelection ( Widget    w,
                              XtPointer clientData,
                              XtPointer callData )
{
     XmAnyCallbackStruct *cb = ( XmAnyCallbackStruct* ) callData;

     XtGetSelectionValue ( selectionLabel, 
                           XA_PRIMARY, 
                           current_type,
                           ShowSelection, 
                           clientData, 
                           cb->event->xbutton.time );

}
    

static void ShowSelection ( Widget         w, 
                            XtPointer      clientData,
                            Atom          *selection,
                            Atom          *type,
                            XtPointer      value,
                            unsigned long *length,
                            int           *format )
{
   /*
    * Check the type of the transfer and handle each accordingly.
    */

    if ( *type == COMPOUND_TEXT )
    {
        XtVaSetValues ( selectionLabel,  
                        XmNlabelString, XmCvtCTToXmString ( value ),
                        NULL );
        wprintf ( msg,
                 "Request Succeeded for selection as Compound Text" );
    }
    else if ( *type == XA_STRING )
    {
        wprintf ( selectionLabel, "%s", value );
        wprintf ( msg, "Request Succeeded for selection as String" ); 
    }
    else if ( *type == TARGETS )
    {
        int i;
        char buf [ 1000 ]; /* Danger: Fixed size array */

        sprintf ( buf,"Length = %d\0", length );

        for ( i=0; i < *length; i++ ) 
        {
            char *s = XGetAtomName ( XtDisplay ( selectionLabel ),
                                     (  (  Atom* ) value ) [ i ] );
            
            sprintf ( buf + strlen ( buf ), "\n ( %d ) %s", i, s );
        }

        wprintf ( selectionLabel, "%s", buf );
        wprintf ( msg, "Current Targets listed" );
    }
    else if ( *type == XT_CONVERT_FAIL || *type == None )
    {
        wprintf ( selectionLabel, " " );
        wprintf ( msg, "Request Failed" );
    }
}
                
static void  SetStringType ( Widget    w,
                             XtPointer clientData,
                             XtPointer callData )
{
    XmToggleButtonCallbackStruct *cb =
                          ( XmToggleButtonCallbackStruct* ) callData;
    
    if ( cb->set )
    {
        current_type = XA_STRING;
    }
}
    
static void  SetCTType ( Widget    w,
                         XtPointer clientData,
                         XtPointer callData )
{
    XmToggleButtonCallbackStruct *cb = 
                             ( XmToggleButtonCallbackStruct* ) callData;
    
    if ( cb->set )
    {
        current_type = COMPOUND_TEXT;
    }
}
    
static void SetTargetType ( Widget    w,
                            XtPointer clientData,
                            XtPointer callData )
{
    XmToggleButtonCallbackStruct *cb = 
                              ( XmToggleButtonCallbackStruct* ) callData;
    
    if ( cb->set )
    {
        current_type = TARGETS;
    }
}


static void OwnSelection ( Widget    w,
                           XtPointer clientData,
                           XtPointer callData )
{
    Display *dpy = XtDisplay ( selectionLabel );

   /*
    * Claim ownership of the PRIMARY selection.
    */
    
    if ( XtOwnSelection ( selectionLabel, XA_PRIMARY, 
                          XtLastTimestampProcessed ( dpy ),
                          ConvertSelection,  /* Handle requests */
                          LoseSelection,     /* Give up selection*/
                          NULL ) )
    {
        wprintf ( msg, "Selection Owned" );
    }

}
                        
static Boolean ConvertSelection ( Widget         w, 
                                  Atom          *selection, 
                                  Atom          *target,
                                  Atom          *type, 
                                  XtPointer     *value, 
                                  unsigned long *length, 
                                  int           *format )
{
   /*
    * Check the requested type, and handle accordingly
    */

    if ( *target == TARGETS )
    {
       /*
        * Initialize an array of Atoms to specify the types of data
        * this program can provide.
        */

        Atom *targets = ( Atom* ) XtMalloc ( sizeof ( Atom ) * 4 );
        targets[0] = XA_STRING;
        targets[1] = COMPOUND_TEXT;
        targets[2] = TARGETS;
        targets[3] = DELETE;

        *value = ( XtPointer ) targets;
        *format = 32;   
        *length = 4 * sizeof(Atom) >> 2;
        *type   = TARGETS;
        return ( TRUE );
    }

    if ( *target == DELETE ) 
    {
       /*
        * Delete the selection by clearing the label. Also report the
        * action using wprintf().
        */

        wprintf ( msg, "Selection Deleted" );
        wprintf ( selectionLabel, "" );

        *type   = DELETE;
        *value  = NULL;
        *length = 0;
        *format = 8;
        return ( TRUE );
    }

    if ( *target == COMPOUND_TEXT ) 
    {

       /*
        * If the requested type is compound text, convert the
        * string retrieved from the selectionLabel widget to CT.
        */

        XmString xmstr;

        XtVaGetValues ( selectionLabel, XmNlabelString, &xmstr, NULL );

        *type   = COMPOUND_TEXT;
        *value  = XmCvtXmStringToCT ( xmstr );
        *length = strlen ( *value );
        *format = 8;
        return ( TRUE );
    }

    if ( *target == XA_STRING ) 
    {

       /*
        * If the requestor is asking for an ASCII string, get the
        * compound string from the selectionLabel widget and convert
        * the results.
        */

        char     *str;
        XmString  xmstr;
        
        XtVaGetValues ( selectionLabel, 
                        XmNlabelString, &xmstr, 
                        NULL );
        
        *type   = XA_STRING;
        *value  = GetTextFromXmstring ( xmstr );
        *length = strlen ( *value );
        *format = 8;
        return ( TRUE );
    }

   /*
    * If we got here, the requested type was something we could
    * not handle, so return FALSE.
    */

   return ( FALSE );
}
                                                    

static void LoseSelection ( Widget w, Atom *selection )
{
    wprintf ( msg, "Selection Lost" );
}
    
