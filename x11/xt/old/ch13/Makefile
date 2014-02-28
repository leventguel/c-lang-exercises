CC = cc 
XSLIBDIR = ../lib
DEBUG = 
# HP Machines
CFLAGS = $(DEBUG) -DSYSV  -I$(XSLIBDIR) 
# DEC and Sun
#CFLAGS = $(DEBUG) -I$(XSLIBDIR)

LIBS = ../lib/libXs.a -lXm -lXt -lX11

.o:.c

all: lib rowtest

lib : Row.o
	ar clq ../lib/libXs.a Row.o

rowtest: rowtest.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
