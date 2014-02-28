CC = cc
DEBUG = -O1 -Wall -Wextra
#if HP, use this one
#CFLAGS = $(DEBUG) -I/usr/include/Motif1.2  -I../lib 
# else
CFLAGS = $(DEBUG) -I../lib

# If SUN, use this lib
#LIBS =  -L../lib -lXs -lXm -lXt -lX11 -lgen -lnsl -lsocket -lm
#if HP, use this
#LIBS =   -L../lib -lXs -L/usr/lib/Motif1.2 -L/usr/lib/X11R5  -lXm -lXt -lX11 -lPW  -lm
#if sgi use
#LIBS =  -L../lib -lXs -lXm -lXt -lX11 -lPW -lm
LIBS =  -L../lib -lXs -lXpm -lXm -lXt -lX11 -lm

TARGETS= fractal fractal2 rubberband draw

all: library $(TARGETS)

library:
	cd ../lib; make

fractal: fractal.o preference.o
	$(CC) $(CFLAGS) -o $@ fractal.o preference.o $(LIBS)

fractal2: fractal2.o preference.o
	$(CC) $(CFLAGS) -o $@ fractal2.o preference.o $(LIBS)

rubberband: rubberband.o
	$(CC) $(CFLAGS) -o $@ rubberband.o $(LIBS)

draw: main.o graphics.o editor.o
	$(CC) $(CFLAGS) -o $@ main.o graphics.o editor.o $(LIBS)

clean:
	rm -f *.o *~* *.a 
	rm -f $(TARGETS)

