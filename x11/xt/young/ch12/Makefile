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

TARGETS=pixlabel list

all: library $(TARGETS)

library:
	cd ../lib; make

pixlabel: pixlabel.o
	$(CC) $(CFLAGS) -o $@  $@.o  $(LIBS)

list: list.o
	$(CC) $(CFLAGS) -o $@  $@.o  $(LIBS)

clean:
	rm -f *.o *~* *.a 
	rm -f $(TARGETS)

