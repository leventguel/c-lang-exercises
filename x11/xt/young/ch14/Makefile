CC = cc
DEBUG = -O
#if HP, use this one
#CFLAGS = $(DEBUG) -I/usr/include/Motif1.2  -I../lib 
# else
CFLAGS = $(DEBUG)  -I../lib

# If SUN, use this lib
#LIBS =  -L../lib -lXs -lXpm -lXm -lXt -lX11 -lgen -lnsl -lsocket 
#if HP, use this
#LIBS =   -L../lib -lXs -L/usr/lib/Motif1.2 -L/usr/lib/X11R5 -lXpm -lXm -lXt -lX11 -lPW  
#if sgi use
#LIBS =  -L../lib -lXs -lXpm -lXm -lXt -lX11 -lPW 
LIBS =  -L../lib -lXs -lXpm -lXm -lXt -lX11

TARGETS=selectiondemo setupicon setupicon2

all: library $(TARGETS)

library:
	cd ../lib; make

selectiondemo: selectiondemo.o
	$(CC) $(CFLAGS) -o $@  $@.o  $(LIBS)
setupicon: setupicon.o
	$(CC) $(CFLAGS) -o $@  $@.o  $(LIBS)
setupicon2: setupicon2.o
	$(CC) $(CFLAGS) -o $@  $@.o  $(LIBS)


clean:
	rm -f *.o *~* *.a 
	rm -f $(TARGETS)
	cd Draw2; make clean
	cd Draw3; make clean

