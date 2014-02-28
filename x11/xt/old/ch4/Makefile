CC = cc 
XSLIBDIR = ../lib
DEBUG = 
# HP Machines
CFLAGS = $(DEBUG) -DSYSV  -I$(XSLIBDIR) 
# DEC and Sun
#CFLAGS = $(DEBUG) -I$(XSLIBDIR)

LIBS = ../lib/libXs.a -lXm -lXt -lX11

.o:.c

all: generic twoshells pushbutton formedit chooseone \
     rctest traverse formtest formtest1 menu menu2 \
     menu3 dialog helptest

generic : generic.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
dialog : dialog.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
twoshells : twoshells.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
pushbutton : pushbutton.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
formedit : formedit.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
rctest : rctest.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
traverse : traverse.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
formtest : formtest.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
formtest1 : formtest1.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
helptest : helptest.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
menu : menu.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
menu2 : menu2.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
menu3 :: menu3.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
chooseone :: chooseone.o
	$(CC) $(CFLAGS) -o $@ $@.o $(LIBS)
