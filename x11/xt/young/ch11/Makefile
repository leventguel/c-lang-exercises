CC = cc
DEBUG = -O
#if HP, use this one
#CFLAGS = $(DEBUG) -I/usr/include/Motif1.2  -I../lib 
# else
CFLAGS = $(DEBUG) 

# If SUN, use this lib
#LIBS =  -L../lib -lXs -lXpm -lXm -lXt -lX11 -lgen -lnsl -lsocket 
#if HP, use this
#LIBS =   -L../lib -lXs -lXpm -L/usr/lib/Motif1.2 -L/usr/lib/X11R5  -lXm -lXt -lX11 -lPW  
#if sgi use
#LIBS =  -L../lib -lXs -lXpm -lXm -lXt -lX11 -lPW
LIBS =  -L../lib -lXs -lXpm -lXm -lXt -lX11

TARGETS=xlogo xlogo2 xlogo3 xpmlogo xpmlogo2 pixmaps

all: library $(TARGETS)

library:
	cd ../lib; make

xlogo: xlogo.o
	$(CC) $(CFLAGS) -o $@  $@.o  $(LIBS)
xlogo2: xlogo2.o
	$(CC) $(CFLAGS) -o $@  $@.o  $(LIBS)
xlogo3: xlogo3.o
	$(CC) $(CFLAGS) -o $@  $@.o  $(LIBS)
xpmlogo: xpmlogo.o
	$(CC) $(CFLAGS) -o $@  $@.o  $(LIBS)
xpmlogo2: xpmlogo2.o
	$(CC) $(CFLAGS) -o $@  $@.o  $(LIBS)

pixmaps: pixmapbrowser.o browser.o
	$(CC) $(CFLAGS) -o $@  pixmapbrowser.o browser.o  $(LIBS)
clean:
	rm -f *.o *~* *.a 
	rm -f $(TARGETS)

