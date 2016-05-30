#
#	Makefile for the library libtransform.a and testprogramm trans.
#
#	$Log: not supported by cvs2svn $
# Revision 1.2  1994/07/06  07:10:09  schuetz
# Version fuer die Testlauefe.
#
# Revision 1.1  1994/06/06  14:28:30  schuetz
# Initial revision
#
#

include	$(HOME)/Entwicklung/EVOS+/EVOS+1.mk

LIBLOCAL= $(LIB)/libtransform.a
LIBS	= $(LIB)/libmute.a	\
	  $(LIB)/libtyp.a	\
	  $(LIB)/libutil.a

LLOCAL	= -ltransform
LLIBS	= -ltyp -lutil

PRG	= trans
PRGPURE	= trans.purify

PRGSRC	= main.c
PRGOBJ	= main.o

SRCS	= transform.c bijecTrans.c nullTransform.c rangeTrans.c
OBJS    = $(LIBLOCAL)($(SRCS:.c=.o) )

include	$(HOME)/Entwicklung/EVOS+/EVOS+2.mk

# DO NOT DELETE THIS LINE -- make depend depends on it.
