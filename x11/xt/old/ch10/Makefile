CC = cc 
XSLIBDIR = ../lib
DEBUG = 
# HP Machines
CFLAGS = $(DEBUG) -DSYSV  -I$(XSLIBDIR) 
# DEC and Sun
#CFLAGS = $(DEBUG) -I$(XSLIBDIR)

LIBS = ../lib/libXs.a -lXm -lXt -lX11

.o:.c

all: fractal fractal2 rubberband draw

fractal : fractal.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

fractal2 : fractal2.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

rubberband: rubberband.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

draw: draw.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

draw2: draw2.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)  


   