/* hallo_x2.c */
#include <stdio.h>
#include <stdlib.h>
#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "my_delay.h"
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 300
/* Funktionsprototypen */
static int create_window (void);
static void process_event (XEvent report);
static void eventloop (void);
static void close_window (void);
extern int delay(int i);
extern int time_diff(void);
/* Globale Variablen */
static unsigned int width, height;
static Display *display;
static int screen;
static int depth;
static Window win;
/* Die Funktionen create_window(), process_event(), eventloop(),
 * close_window() bitte vom Listing hallo_x.c übernehmen oder das
 * komplette Listing auf der Buch-CD verwenden
 */
static int create_window (void) {
  char *window_name = "Einfaches Fenster - hallo_x";
  char *icon_name = "window";
  static XSizeHints size_hints;
  Window rootwin;
  width = WINDOW_WIDTH;
  height = WINDOW_HEIGHT;
  /* X-Sitzung öffnen */
  display = XOpenDisplay (NULL);
  /* Fehlerüberprüfung */
  if (display == NULL) {
    printf ("Verbindung zum X-Server fehlgeschlagen?!?\n");
    exit(EXIT_FAILURE);
  }
  /* Standardbildschirm eines Displays */
  screen = XDefaultScreen (display);
  /* Standardtiefe des Screens - Anzahl der Ebenen */
  depth = XDefaultDepth (display, screen);
  rootwin = RootWindow (display, screen);
  win = XCreateSimpleWindow ( display, rootwin, 100, 10,
                              width, height, 5,
                              BlackPixel (display, screen),
                              WhitePixel (display, screen) );
  size_hints.flags = PSize | PMinSize | PMaxSize;
  size_hints.min_width =  width-10;
  size_hints.max_width =  width+10;
  size_hints.min_height = height-10;
  size_hints.max_height = height+10;
  XSetStandardProperties ( display, win, window_name, icon_name,
                           None, 0, 0, &size_hints );
  /* Erwünschte Events, auf die das Fenster reagieren soll ... */
  XSelectInput (display, win, ButtonPressMask | KeyPressMask | LeaveWindowMask | EnterWindowMask | FocusChangeMask | ExposureMask | StructureNotifyMask);
  /* Fenster anzeigen */
  XMapWindow (display, win);
  return 1;
}

static void close_window (void) {
  XDestroyWindow(display, win);
  XCloseDisplay (display);
}

static void eventloop (void) {
  XEvent xev;
  int num_events;
  XFlush (display);
  num_events = XPending (display);
  while ((num_events != 0)) {
    num_events--;
    XNextEvent (display, &xev);
    process_event (xev);
  }
}

static void process_event (XEvent report) {
  KeySym key;
  switch (report.type) {
  case KeyPress:
    key = XLookupKeysym (&report.xkey, 0);
    if(key) {
      printf("Tastatur-Event\n");
    }
    break;
  case KeyRelease:
    key = XLookupKeysym (&report.xkey, 0);
    if(key) {
      printf("Tastatur-Event\n");
    }
    break;
  case ButtonPressMask:
    printf ("Maus-Event\n");
    break;
  case EnterNotify:
    printf ("Enter-Window-Event\n");
    break;
  case LeaveNotify:
    printf ("Leave-Window-Event\n");
    break;
  case ConfigureNotify:
    printf ("Configure-Notify-Event\n");
  case FocusIn:
    printf ("Focus-In-Request-Event\n");
    break;
  case FocusOut:
    printf ("Focus-Out-Request-Event\n");
    break;
  case ResizeRequest:
    printf ("Resize-Request-Event\n");
    break;
  case Expose:
    printf ("Exposure-Event\n");
    break;
  default:
    break;
  }
}


int main(int argc, char **argv) {
  int quit = 0;
  int pause = 0;
  int td;
  create_window();
  gettimeofday(&st, NULL);
  while(!quit) {
    gettimeofday(&rt, NULL);
    td = time_diff();
    pause = delay(FRAME_LEN - td + pause);
    st = rt;
    eventloop();
  }
  close_window();
  return EXIT_SUCCESS;
}
