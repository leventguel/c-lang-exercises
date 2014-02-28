CC = cc 
DEBUG = -O

#if HP, use this one
#CFLAGS = $(DEBUG) -I/usr/include/Motif1.2  -I../lib 
# else
CFLAGS = $(DEBUG)  -I../lib

# If SUN, use this lib
#LIBS =  -L../lib -lXs -lXm -lXt -lX11 -lgen -lnsl -lsocket 
#if HP, use this
#LIBS =   -L../lib -lXs -L/usr/lib/Motif1.2 -L/usr/lib/X11R5  -lXm -lXt -lX11 -lPW  
#if sgi use
LIBS =  -L../lib -lXs -lXm -lXt -lX11 -lPW

TARGETS= helpdemo menubar option option2 popupmenu cascade tearoff

all: library $(TARGETS)


library:
	cd ../lib; make

helpdemo: helpdemo.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

menubar: menubar.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
option: option.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

option2: option2.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

popupmenu: popupmenu.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
cascade: cascade.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
tearoff: tearoff.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)

clobber:
	rm -f *.o *~* *.a 
	rm -f $(TARGETS)

