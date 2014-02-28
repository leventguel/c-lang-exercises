CC = cc 
XSLIBDIR = ../lib
DEBUG = -g
# HP Machines
CFLAGS = $(DEBUG) -DSYSV  -I$(XSLIBDIR) 
# DEC and Sun
#CFLAGS = $(DEBUG) -I$(XSLIBDIR)

LIBS = ../lib/libXs.a -lXm -lXt -lX11

all: memo memo1 memo2 memo3 memo4 memo5

memo :  memo.o
	$(CC) $(CFLAGS) -o memo memo.c $(LIBS)

memo1 :  memo1.o
	$(CC) $(CFLAGS) -o memo1 memo1.c $(LIBS)

memo2 :  memo2.o
	$(CC) $(CFLAGS) -o memo2 memo2.c $(LIBS)

memo3 :  memo3.o
	$(CC) $(CFLAGS) -o memo3 memo3.c $(LIBS)

memo4 :  memo4.o
	$(CC) $(CFLAGS) -o memo4 memo4.c $(LIBS)

memo5 :  memo5.o
	$(CC) $(CFLAGS) -o memo5 memo5.c $(LIBS)



