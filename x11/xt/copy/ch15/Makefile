CC = cc 
DEBUG = -O


#if HP, use this one
#CFLAGS = $(DEBUG) -I/usr/include/Motif1.2 
# else
CFLAGS = $(DEBUG) 

# If SUN, use this lib
#LIBS = -lXm -lXt -lX11 -lgen -lnsl -lsocket -lm
#if HP, use this
#LIBS =  -L/usr/lib/Motif1.2 -L/usr/lib/X11R5  -lXm -lXt -lX11 -lPW  -lm
#if sgi use
LIBS =  -lXm -lXt -lX11 -lPW -lm


TARGETS= dialtest

all: $(TARGETS)

dialtest: dialtest.o Dial.o
	$(CC) $(CFLAGS) -o $@ dialtest.o Dial.o $(LIBS)

clobber:
	rm -f *.o *~* *.a 
	rm -f $(TARGETS)

