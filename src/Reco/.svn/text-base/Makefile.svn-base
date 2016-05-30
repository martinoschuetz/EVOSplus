#
#	Makefile for the library libreco.a and testprogramm reco.
#
#	$Log: not supported by cvs2svn $
# Revision 1.2  1994/07/06  07:09:06  schuetz
# Version fuer die Testlauefe.
#
# Revision 1.1  1994/06/06  14:29:05  schuetz
# Initial revision
#
#

include	$(HOME)/Entwicklung/EVOS+/EVOS+1.mk

LIBLOCAL= $(LIB)/libreco.a
LIBS	= $(LIB)/librng.a	\
	  $(LIB)/libtyp.a	\
	  $(LIB)/libutil.a

LLOCAL	= -lreco
LLIBS	= -lrng -ltyp -lutil

PRG	= reco
PRGPURE	= reco.purify

PRGSRC	= main.c
PRGOBJ	= main.o

SRCS	= reco.c disLengthReco.c discreteReco.c geometricReco.c\
	  intermedReco.c noReco.c thalesReco.c
OBJS    = $(LIBLOCAL)($(SRCS:.c=.o) )

include	$(HOME)/Entwicklung/EVOS+/EVOS+2.mk

# DO NOT DELETE THIS LINE -- make depend depends on it.

main.o: /usr/include/sys/types.h /usr/include/_ansi.h /usr/include/newlib.h
main.o: /usr/include/sys/config.h /usr/include/machine/ieeefp.h
main.o: /usr/include/sys/_types.h /usr/include/machine/types.h
main.o: /usr/include/sys/time.h
