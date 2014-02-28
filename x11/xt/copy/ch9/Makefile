CC = cc 
DEBUG = -O
#if HP, use this one
#CFLAGS = $(DEBUG) -I/usr/include/Motif1.2  -I../lib 
# else
CFLAGS = $(DEBUG) 

# If SUN, use this lib
#LIBS =  -L../lib -lXs -lXm -lXt -lX11 -lgen -lnsl -lsocket 
#if HP, use this
#LIBS =   -L../lib -lXs -L/usr/lib/Motif1.2 -L/usr/lib/X11R5  -lXm -lXt -lX11 -lPW  
#if sgi use
LIBS =  -L../lib -lXs -lXm -lXt -lX11 -lPW


TARGETS=coloredit getpixel getpixelbyname loadrgb

all: library $(TARGETS)


library:
	cd ../lib; make

coloredit: coloredit.o paletteEditor.o
	$(CC) $(CFLAGS) -o $@  coloredit.o paletteEditor.o  $(LIBS)

getpixel: getpixel.o
	$(CC) $(CFLAGS) -o $@  $@.o  $(LIBS)

getpixelbyname: getpixelbyname.o
	$(CC) $(CFLAGS) -o $@  $@.o  $(LIBS)

loadrgb: loadrgb.o
	$(CC) $(CFLAGS) -o $@  $@.o  $(LIBS)


clobber:
	rm -f *.o *~* *.a 
	rm -f $(TARGETS)

