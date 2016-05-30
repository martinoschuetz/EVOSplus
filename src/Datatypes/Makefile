#	
#	Makefile for the library libtyp.a and testprogramms.
#
#	$Log: not supported by cvs2svn $
# Revision 1.1  1994/06/06  13:49:23  schuetz
# Initial revision
#
# Revision 1.1  1994/06/06  13:49:23  schuetz
# Initial revision
#
#
#

include	$(HOME)/Entwicklung/EVOS+/EVOS+1.mk

LIBLOCAL= $(LIB)/libtyp.a
LIBS	= $(LIB)/libutil.a

LLOCAL	= -ltyp
LLIBS	= -lutil

PRG	= datatypes
PRGPURE	= datatypes.purify

PRGSRC	= ind_t.c
PRGOBJ	= ind_t.o

SRCS	= ind.c matrix.c pop.c vector.c
OBJS    = $(LIBLOCAL)($(SRCS:.c=.o) )

include	$(HOME)/Entwicklung/EVOS+/EVOS+2.mk

# DO NOT DELETE THIS LINE -- make depend depends on it.
