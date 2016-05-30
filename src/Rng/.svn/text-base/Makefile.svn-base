#
#	Makefile for the library librng.a and testprogramm rng.
#
#	$Log: not supported by cvs2svn $
# Revision 1.1  1994/06/06  14:04:54  schuetz
# Initial revision
#
# Revision 1.1  1994/06/06  14:04:54  schuetz
# Initial revision
#
#
#

include	$(HOME)/Entwicklung/EVOS+/EVOS+1.mk

LIBLOCAL= $(LIB)/librng.a
LIBS	= $(LIB)/libutil.a

LLOCAL	= -lrng
LLIBS	= -lutil

PRG	= rng
PRGPURE	= rng.purify

PRGSRC	= main.c
PRGOBJ	= main.o

SRCS	= rng.c nullRng.c des.c desks.c grefenstette.c knuth.c \
	  plauger.c ran0.c ran1.c ran2.c ran3.c ran4.c srand.c vlcr.c
#drand.c
OBJS    = $(LIBLOCAL)($(SRCS:.c=.o) )

include	$(HOME)/Entwicklung/EVOS+/EVOS+2.mk

# DO NOT DELETE THIS LINE -- make depend depends on it.

//server1/schuetz/Entwicklung/EVOS+/lib/librng.a(des.o): /usr/include/math.h
//server1/schuetz/Entwicklung/EVOS+/lib/librng.a(des.o): /usr/include/sys/reent.h
//server1/schuetz/Entwicklung/EVOS+/lib/librng.a(des.o): /usr/include/_ansi.h
//server1/schuetz/Entwicklung/EVOS+/lib/librng.a(des.o): /usr/include/newlib.h
//server1/schuetz/Entwicklung/EVOS+/lib/librng.a(des.o): /usr/include/sys/config.h
//server1/schuetz/Entwicklung/EVOS+/lib/librng.a(des.o): /usr/include/machine/ieeefp.h
//server1/schuetz/Entwicklung/EVOS+/lib/librng.a(des.o): /usr/include/sys/_types.h
