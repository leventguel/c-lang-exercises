CC = cc 
DEBUG = -O
CFLAGS = -DSYSV $(DEBUG) 

all: libXs.a

SOURCE =  concat.c str2flt.c invert.c quit.c talkto.c wprintf.c insert.c xmstr_to_str.c\
	send_msg.c xor.c strtoxmstr.c menus.c help_dialog.c pix_buttons.c

OBJS =  concat.o str2flt.o invert.o quit.o talkto.o wprintf.o insert.o xmstr_to_str.o\
	send_msg.o  xor.o strtoxmstr.o menus.o help_dialog.o pix_buttons.o

libXs.a: $(OBJS)
	ar ruv libXs.a $(OBJS)

