CC = cc 
XSLIBDIR = ../lib
DEBUG = -g
# HP Machines
CFLAGS = $(DEBUG) -DSYSV  -I$(XSLIBDIR) 
# DEC and Sun
#CFLAGS = $(DEBUG) -I$(XSLIBDIR)

LIBS = ../lib/libXs.a -lXm -lXt -lX11

.o:.c

all: libXs.a sort

libXs.a : Tree.o
	ar ruv ../lib/libXs.a Tree.o

sort : sort.o libXs.a
	$(CC) $(CFLAGS) -o $@ $@.o  $(LIBS)





