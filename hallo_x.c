/* hallo_x.c */
#include <stdio.h>
#include <stdlib.h>
#include <X11/keysym.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 300
/* Funktionsprototypen */
static int create_window (void);
static void process_event (XEvent report);
static void eventloop (void);
static void close_window (void);
/* Globale Variablen */
static unsigned int width, height;
static Display *display;
static int screen;
static int depth;
static Window win;
/* Funktion erzeugt ein Fenster */
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
  size_hints.min_width =  width;
  size_hints.max_width =  width;
  size_hints.min_height = height;
  size_hints.max_height = height;
  XSetStandardProperties ( display, win, window_name, icon_name,
                           None, 0, 0, &size_hints );
  /* Erwünschte Events, auf die das Fenster reagieren soll ... */
  XSelectInput (display, win, ButtonPressMask | KeyPressMask);
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
  case ButtonPressMask:
    printf ("Maus-Event\n");
    break;
  default:
    break;
  }
}
int main (int argc, char **argv) {
  int quit = 0;
  create_window ();
  while (!quit) {
    eventloop ();
  }
  close_window ();
  return EXIT_SUCCESS;
}
/*
  $ gcc -o hallo_x hallo_x.c -L/usr/X11R6/lib -lX11
  $ ./hallo_x
*/
