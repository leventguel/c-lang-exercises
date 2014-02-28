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

/******************************************************
 * paletteEditor.c: create a palette editor
 ******************************************************/
#include <Xm/Xm.h>
#include <Xm/Form.h>
#include <Xm/Frame.h>
#include <Xm/Scale.h>
#include <Xm/RowColumn.h>
#include <Xm/DrawnB.h>
#include <Xm/ToggleB.h>
#include <Xm/Label.h>
#include <Xm/MessageB.h>
#include <stdio.h>

/* Widgets globally available within this file. */

static Widget  swatch, currentToggle = NULL; 
static Widget  redSlider, blueSlider, greenSlider;

/* Function declarations and callbacks */

static Widget  CreateControlArea ( Widget parent );
static Widget  MakeSlider ( char          *name, 
                            Widget         parent, 
                            XtCallbackProc callback );
static Widget  CreateColorSelector ( Widget parent, int ncolors );
static void    RedSliderMoved ( Widget    w, 
                                XtPointer clientData, 
                                XtPointer callData );
static void    BlueSliderMoved ( Widget    w, 
                                 XtPointer clientData, 
                                 XtPointer callData );
static void    GreenSliderMoved ( Widget    w, 
                                  XtPointer clientData, 
                                  XtPointer callData );
static void    SelectColorCallback ( Widget    w,  
                                     XtPointer clientData,
                                     XtPointer callData );
static void    WarnUserNoColor ( Widget parent );
static void    SetShadowColors ( Widget parent );
                    
Widget CreatePaletteEditor ( Widget parent, int ncolors ) 
{
    Widget form, colors, controls, separator;

   /* 
    * Create a base to hold everything.
    */

    form = XtCreateManagedWidget ( "base", xmFormWidgetClass, 
                                   parent, NULL, 0 );

   /*
    * Create the controls that allow the user to manipulate
    * the colors in the palette.
    */

    controls = CreateControlArea ( form );

    XtVaSetValues ( controls, 
                    XmNtopAttachment,    XmATTACH_NONE,
                    XmNbottomAttachment, XmATTACH_FORM,
                    XmNleftAttachment,   XmATTACH_FORM,
                    XmNrightAttachment,  XmATTACH_FORM,
                    XmNleftOffset,       10,
                    XmNtopOffset,        10,
                    XmNbottomOffset,     10,
                    XmNrightOffset,      10,
                    NULL );

   /* 
    * Create a grid of buttons, one for each 
    * color in the palette, from which the user can choose.
    */

    colors = CreateColorSelector ( form, ncolors );

    XtVaSetValues ( colors, 
                    XmNtopAttachment,    XmATTACH_FORM,
                    XmNbottomAttachment, XmATTACH_WIDGET,
                    XmNbottomWidget,     controls,
                    XmNleftAttachment,   XmATTACH_FORM,
                    XmNrightAttachment,  XmATTACH_FORM,
                    XmNleftOffset,       10,
                    XmNtopOffset,        10,
                    XmNbottomOffset,     10,
                    XmNrightOffset,      10,
                    NULL );
}
                        
static Widget CreateControlArea ( Widget parent ) 
{    
    Widget form, frame, sliders;

   /*
    * Create a form widget to manage the overall layout.
    */

    form = XtCreateManagedWidget ( "controls", xmFormWidgetClass,
                                   parent, NULL, 0 );

  /*
   * The swatch displays the color cell currently being edited.
   * The swatch itself is a drawn button, and is placed inside
   * a labeled frame for visual effect.
   */

   frame = 
        XtVaCreateManagedWidget ( "frame", xmFrameWidgetClass, form,
                                  XmNtopAttachment,    XmATTACH_FORM,
                                  XmNbottomAttachment, XmATTACH_FORM,
                                  XmNleftAttachment,   XmATTACH_NONE,
                                  XmNrightAttachment,  XmATTACH_FORM,
                                  XmNbottomOffset,     20,
                                  XmNrightOffset,      20,
                                  NULL );

   XtVaCreateManagedWidget ( "swatchLabel", xmLabelWidgetClass, 
                             frame,
                             XmNchildType, XmFRAME_TITLE_CHILD,
                             NULL );

   swatch = XtVaCreateManagedWidget ( "display",
                                      xmDrawnButtonWidgetClass,
                                      frame,
                                      XmNwidth,            100,
                                      XmNheight,           100,
                                      NULL );
   /*
    * Create a row column widget to contain three sliders,
    * one for each color component.
    */

    sliders = 
      XtVaCreateManagedWidget ( "sliderpanel", 
                                xmRowColumnWidgetClass, form, 
                                XmNtopAttachment,    XmATTACH_FORM,
                                XmNbottomAttachment, XmATTACH_NONE,
                                XmNleftAttachment,   XmATTACH_FORM,
                                XmNrightAttachment,  XmATTACH_WIDGET,
                                XmNrightWidget,      swatch,
                                XmNrightOffset,      20,
                                NULL );

    redSlider   = MakeSlider ( "redSlider", 
                               sliders, RedSliderMoved );
    greenSlider = MakeSlider ( "greenSlider",
                               sliders, GreenSliderMoved );
    blueSlider  = MakeSlider ( "blueSlider", 
                               sliders, BlueSliderMoved );
    
    return ( form );
}
                            
Widget MakeSlider ( char * name, Widget parent, XtCallbackProc callback ) 
{
    Widget  w;
    
   /*
    * Create an XmScale widget.
    */
    
    w = XtVaCreateManagedWidget ( name, xmScaleWidgetClass, parent,
                                  XmNminimum,     0,
                                  XmNmaximum,     255,
                                  XmNshowValue,   TRUE,
                                  XmNorientation, XmHORIZONTAL,
                                  NULL );
    
   /*
    * Add callbacks to be invoked when the slider moves.
    */
    
    XtAddCallback ( w, XmNvalueChangedCallback, callback, NULL );
    XtAddCallback ( w, XmNdragCallback,         callback, NULL );
    
    return ( w );
}
            
static Widget CreateColorSelector ( Widget parent, int ncolors ) 
{
    Widget  panel, frame;
    int     i;
    Pixel   *pixels;

   /*
    * Allocate an array of pixels large enough for the palette
    * plus top and bottom shadow colors for each background.
    */

    pixels = ( Pixel* ) XtMalloc ( sizeof ( Pixel ) * ncolors * 3 );

    if ( !XAllocColorCells ( XtDisplay ( parent ),
                     DefaultColormapOfScreen ( XtScreen ( parent ) ),
                             FALSE, NULL, 0,
                             pixels, ncolors * 3 ) ) 
        XtError ( "Can't allocate color cells" );

   /*
    * Put everything inside a labeled frame widget 
    */
    
    frame = XtCreateManagedWidget ( "frame", xmFrameWidgetClass,
                                    parent, NULL, 0 );

    XtVaCreateManagedWidget ( "selectorLabel", xmLabelWidgetClass,
                              frame, 
                              XmNchildType, XmFRAME_TITLE_CHILD,
                              NULL );

   /*
    * Place the palette entries in a 4-column radio box.
    */

    panel = XtVaCreateManagedWidget ( "colorpanel",
                                      xmRowColumnWidgetClass, frame, 
                                      XmNradioBehavior, TRUE,
                                      XmNnumColumns,    4,
                                      XmNpacking,      XmPACK_COLUMN,
                                      XmNadjustLast,    FALSE,
                                      NULL );
    
   /*
    * Create an XmToggleButton widget for each color in the palette.
    * Just assign the background color to an allocated pixel. Actual
    * initial color displayed by each button is random. Also
    * assign top and bottom shadows to allocated color cells.
    */

    for ( i = 0; i < ncolors; i++ ) 
    {
        Widget toggle;
        char   name[10];

        sprintf ( name,"%d", pixels[i] );

        toggle   = 
            XtVaCreateManagedWidget ( name, 
                                  xmToggleButtonWidgetClass, panel, 
                                  XmNbackground, pixels[i],
                                  XmNtopShadowColor, 
                                             pixels[i + ncolors],
                                  XmNbottomShadowColor, 
                                             pixels[i + 2 * ncolors],
                                  NULL );
       /*
        * Initialize the shadows of each button. The background is
        * random, but at least the shadows should look right.
        */

        SetShadowColors ( toggle );

       /*
        * Callback to set the currently editable color cell.
        */

        XtAddCallback ( toggle, XmNvalueChangedCallback,
                        SelectColorCallback, ( XtPointer ) NULL );
    }

    XtFree ( (char *) pixels );
    
    return ( frame );
}
                                                
static void SelectColorCallback ( Widget    w,  
                                  XtPointer clientData,
                                  XtPointer callData ) 
{
    XColor color;
    Pixel bg, tsc, bsc;
    XmToggleButtonCallbackStruct *cbs =
                         ( XmToggleButtonCallbackStruct* ) callData;
    /*
     * Ignore calls that result from a button being unset.
     */
 
     if ( cbs->set == FALSE )
	         return;

    /*
     * Register the selected toggle button as the
     * currently selected widget
     */

     currentToggle = w;

    /*
     * Retrieve the colors used by the currently selected widget,
     * and assign these colors to the swatch widget.
     */

     XtVaGetValues ( currentToggle, 
                     XmNbackground,        &bg,
                     XmNtopShadowColor,    &tsc, 
                     XmNbottomShadowColor, &bsc, 
                     NULL );
     XtVaSetValues ( swatch,
                     XmNbackground,        bg,
                     XmNtopShadowColor,    tsc,
                     XmNbottomShadowColor, bsc,
                     NULL );
    /*
     * Get the color components (rgb) of the selected color cell.
     */

     color.flags = DoRed | DoGreen | DoBlue;
     color.pixel = bg;

     XQueryColor ( XtDisplay ( w ),
                   DefaultColormapOfScreen ( XtScreen ( w ) ),
                   &color );
    /*
     * Use each color component value to determine the 
     * new position of the corresponding slider.
     */

    XtVaSetValues ( redSlider,   XmNvalue, color.red   / 256,   NULL );
    XtVaSetValues ( greenSlider, XmNvalue, color.green / 256,   NULL );
    XtVaSetValues ( blueSlider,  XmNvalue, color.blue  / 256,   NULL );
}
                                    
static void RedSliderMoved ( Widget    w, 
                             XtPointer clientData,
                             XtPointer callData ) 
{
    XColor color;
    Pixel pixel;
    XmScaleCallbackStruct *cb = ( XmScaleCallbackStruct * ) callData;

   /*
    * Make sure there is a color to edit.
    */

    if ( !currentToggle ) 
    {
       WarnUserNoColor ( w );
       return;
    }

   /*
    * Retrieve the background pixel of the swatch widget
    * and change the red component of the color according to
    * the new value of the red slider.
    */

    XtVaGetValues ( swatch, XmNbackground, &pixel, NULL );

    color.red   =  cb->value * 256;
    color.pixel =  pixel;
    color.flags =  DoRed;
    XStoreColor ( XtDisplay ( w ), 
                  DefaultColormapOfScreen ( XtScreen ( w ) ),
                  &color );
   /*
    * Correct the shadow colors.
    */

    SetShadowColors ( currentToggle );
}
                        
static void BlueSliderMoved ( Widget    w,
                              XtPointer clientData, 
                              XtPointer callData ) 
{
    XColor color;
    Pixel pixel;
    XmScaleCallbackStruct *cb = ( XmScaleCallbackStruct * ) callData;
  
   /*
    * Make sure there is a color to edit.
    */

    if ( !currentToggle ) 
    {
        WarnUserNoColor ( w );
        return;
    }

   /*
    * Retrieve the background pixel of the swatch widget
    * and change the blue component of the color according to
    * the new value of the blue slider.
    */

    XtVaGetValues ( swatch, XmNbackground, &pixel, NULL );    
    color.blue  =  cb->value * 256;
    color.pixel =  pixel;
    color.flags =  DoBlue;

    XStoreColor ( XtDisplay ( w ), 
                  DefaultColormapOfScreen ( XtScreen ( w ) ),
                  &color );
   /*
    * Correct the shadow colors.
    */

     SetShadowColors ( currentToggle );
}
                        
static void GreenSliderMoved ( Widget    w, 
                               XtPointer clientData, 
                               XtPointer callData ) 
{
    XColor color;
    Pixel  pixel;
    XmScaleCallbackStruct *cb = ( XmScaleCallbackStruct * ) callData;
   
   /*
    * Make sure there is a color to edit.
    */

    if ( !currentToggle ) 
    {
      WarnUserNoColor ( w );
      return;
    }
 
   /*
    * Retrieve the background pixel of the swatch widget
    * and change the greem component of the color according to
    * the new value of the green slider.
    */

    XtVaGetValues ( swatch, XmNbackground, &pixel, NULL );    
    color.green =  cb->value * 256;
    color.pixel =  pixel;
    color.flags =  DoGreen;

    XStoreColor ( XtDisplay ( w ), 
                  DefaultColormapOfScreen ( XtScreen ( w ) ),
                  &color );
   /*
    * Correct the shadow colors.
    */

    SetShadowColors ( currentToggle );
}
                        
static void WarnUserNoColor ( Widget parent ) 
{
    static Widget dialog = NULL;

    if ( !dialog ) 
       dialog = XmCreateWarningDialog ( parent, 
                                        "noColorWarningDialog",
                                        NULL, 0 );
    XtManageChild ( dialog );
}
    
static void SetShadowColors ( Widget w ) 
{
    XColor       select, fg, bs, ts, bg;
    XmColorProc  proc = XmGetColorCalculation();

    bg.flags = DoRed | DoBlue | DoGreen;
    ts.flags = DoRed | DoBlue | DoGreen;
    bs.flags = DoRed | DoBlue | DoGreen;

   /*
    * Get the top, bottom, and background pixels of the
    * given widget and determine the color components
    * of the background color.
    */

    XtVaGetValues ( w, 
                    XmNbackground,        &bg.pixel,
                    XmNtopShadowColor,    &ts.pixel, 
                    XmNbottomShadowColor, &bs.pixel, 
                    NULL );

    XQueryColor ( XtDisplay ( w ), 
                  DefaultColormapOfScreen ( XtScreen ( w ) ), &bg );

   /*
    * Call the currently installed Motif color calculation function
    * to fill in the rgb components of the top and bottom shadow
    * colors that match the given background.
    */

   ( *proc ) ( &bg, &fg, &select, &ts, &bs );

  /*
   * The calculation function fills in the color structures. Now we
   * have to store the colors in the corresponding color cells to
   * display these colors.
   */

   XStoreColor ( XtDisplay ( w ), 
                 DefaultColormapOfScreen ( XtScreen ( w ) ),
                 &ts );
   XStoreColor ( XtDisplay ( w ), 
                 DefaultColormapOfScreen ( XtScreen ( w ) ),
                 &bs );
}
                                        
