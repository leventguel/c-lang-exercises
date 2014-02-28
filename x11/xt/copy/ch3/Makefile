CC = cc 
DEBUG = -O

#if HP, use this one
#CFLAGS = $(DEBUG) -I/usr/include/Motif1.2 -I../lib
# else
CFLAGS = $(DEBUG)  -I../lib

# If SUN, use this lib
#LIBS =  -lXm -lXt -lX11 -lgen -lnsl -lsocket 
#if HP, use this
#LIBS =   -L/usr/lib/Motif1.2 -L/usr/lib/X11R5  -lXm -lXt -lX11 -lPW  
#if sgi use
LIBS =  -L../lib -lXs -lXm -lXt -lX11 -lPW

TARGETS= editor rmtest rmtest2 rmtest3 rmtest4

all: library $(TARGETS)

library:
	cd ../lib; make

rmtest: rmtest.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

rmtest2: rmtest2.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

rmtest3: rmtest3.o 
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

rmtest4: rmtest4.o 
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

editor: editor.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

clobber:
	rm -f *.o *~* *.a 
	rm -f $(TARGETS)

