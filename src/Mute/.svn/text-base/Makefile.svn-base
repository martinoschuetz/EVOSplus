#
#	Makefile for the library libmute.a and testprogramm mute.
#
#	$Log: not supported by cvs2svn $
# Revision 1.2  1994/07/06  07:06:35  schuetz
# Version fuer die Testlauefe.
#
# Revision 1.1  1994/06/06  14:36:06  schuetz
# Initial revision
#
#
#

include	$(HOME)/Entwicklung/EVOS+/EVOS+1.mk

LIBLOCAL= $(LIB)/libmute.a
LIBS	= $(LIB)/libtransform.a \
	  $(LIB)/librng.a	\
	  $(LIB)/libtyp.a	\
	  $(LIB)/libutil.a

LLOCAL	= -lmute
LLIBS	= -ltransform -lrng -ltyp -lutil

PRG	= mute
PRGPURE	= mute.purify

PRGSRC	= main.c
PRGOBJ	= main.o

SRCS	= mute.c addNormalMute.c binomiIntMute.c logNormalMute.c\
		  logisticMute.c logistic2Mute.c progressMute.c nullMute.c ranMulMute.c\
		  uniIntMute.c mscpMute.c plantMute.c nacaMute.c triangleMute.c
OBJS    = $(LIBLOCAL)($(SRCS:.c=.o) )

include	$(HOME)/Entwicklung/EVOS+/EVOS+2.mk

# DO NOT DELETE THIS LINE -- make depend depends on it.

main.o: /usr/include/sys/types.h /usr/include/_ansi.h /usr/include/newlib.h
main.o: /usr/include/sys/config.h /usr/include/machine/ieeefp.h
main.o: /usr/include/sys/_types.h /usr/include/machine/types.h
main.o: /usr/include/sys/time.h

//server1/schuetz/Entwicklung/EVOS+/lib/libmute.a(plantMute.o): /usr/include/string.h
//server1/schuetz/Entwicklung/EVOS+/lib/libmute.a(plantMute.o): /usr/include/_ansi.h
//server1/schuetz/Entwicklung/EVOS+/lib/libmute.a(plantMute.o): /usr/include/newlib.h
//server1/schuetz/Entwicklung/EVOS+/lib/libmute.a(plantMute.o): /usr/include/sys/config.h
//server1/schuetz/Entwicklung/EVOS+/lib/libmute.a(plantMute.o): /usr/include/machine/ieeefp.h
//server1/schuetz/Entwicklung/EVOS+/lib/libmute.a(plantMute.o): /usr/include/sys/reent.h
//server1/schuetz/Entwicklung/EVOS+/lib/libmute.a(plantMute.o): /usr/include/sys/_types.h
//server1/schuetz/Entwicklung/EVOS+/lib/libmute.a(nacaMute.o): /usr/include/string.h
//server1/schuetz/Entwicklung/EVOS+/lib/libmute.a(nacaMute.o): /usr/include/_ansi.h
//server1/schuetz/Entwicklung/EVOS+/lib/libmute.a(nacaMute.o): /usr/include/newlib.h
//server1/schuetz/Entwicklung/EVOS+/lib/libmute.a(nacaMute.o): /usr/include/sys/config.h
//server1/schuetz/Entwicklung/EVOS+/lib/libmute.a(nacaMute.o): /usr/include/machine/ieeefp.h
//server1/schuetz/Entwicklung/EVOS+/lib/libmute.a(nacaMute.o): /usr/include/sys/reent.h
//server1/schuetz/Entwicklung/EVOS+/lib/libmute.a(nacaMute.o): /usr/include/sys/_types.h
