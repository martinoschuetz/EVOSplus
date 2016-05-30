#
#	Makefile for the library libadapt.a.
#

include	$(HOME)/Entwicklung/EVOS+/EVOS+1.mk

LIBLOCAL= $(LIB)/libadapt.a

LIBS	= $(LIB)/librng.a	\
	  $(LIB)/libutil.a	\
	  $(LIB)/libtyp.a

LLOCAL	= -ladapt
LLIBS	= -lRNG -lutil -ltyp

PRG	= adapt

PRGSRC	= main.c
PRGOBJ	= main.o

SRCS	= adapt.c athirdAdapt.c binomialAdapt.c kursaweAdapt.c nullAdapt.c
OBJS	= $(LIBLOCAL)($(SRCS:.c=.o) )

include	$(HOME)/Entwicklung/EVOS+/EVOS+2.mk

# DO NOT DELETE THIS LINE -- make depend depends on it.
