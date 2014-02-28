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


TARGETS=busy xbc tracker1 tracker2

all: library $(TARGETS)


library:
	cd ../lib; make

busy: busy.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
xbc: xbc.o calc.o
	$(CC) $(CFLAGS) -o $@ xbc.o calc.o $(LIBS)
tracker1:  mousetracks.o mousetracker.o
	$(CC) $(CFLAGS) -o $@ mousetracks.o mousetracker.o $(LIBS)
tracker2:  mousetracks.o mousetracker2.o
	$(CC) $(CFLAGS) -o $@ mousetracks.o mousetracker2.o $(LIBS)


clobber:
	rm -f *.o *~* *.a 
	rm -f $(TARGETS)

