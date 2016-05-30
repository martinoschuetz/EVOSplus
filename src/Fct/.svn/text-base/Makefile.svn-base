#
#	Makefile for the library libfct.a and testprogramm fct.
#
#	$Log: not supported by cvs2svn $
# Revision 1.1  1994/07/06  07:07:50  schuetz
# Initial revision
#
#
#
#

include	$(HOME)/Entwicklung/EVOS+/EVOS+1.mk

LIBLOCAL= $(LIB)/libfct.a

LIBS	= $(LIB)/librst.a \
		  $(LIB)/librng.a \
		  $(LIB)/libutil.a	\
		  $(LIB)/libtyp.a

LLOCAL	= -lfct
LLIBS	= -lrst -lrng -lutil -ltyp

PRG	    = fct
PRGPURE	= fct.purify

PRGSRC	= main.c
PRGOBJ	= main.o

#clima.c climaf.c
SRCS	= fct.c arma.c bpp.c counting.c constant.c \
		  ellepsoid.c exposum.c fletcherPow.c genRosenbrock.c \
		  trintF0.c trintF1.c trintF3.c \
		  nullFct.c \
		  parable.c simplePlain.c sphere.c reflection.c reflection1.c \
		  reflection2.c reflection3.c reflection4.c mscp.c mscp2.c
#		  naca.c rmatrix.c heap.c mkrt2.c rinterface.c routing.c \
#		  plant.c consist_check.c default_plant.c eval_sim.c \
#		  if_generator.c init_plant.c interface_get.c interface_set.c \
#		  load_plant.c save_plant.c subsystem_translation.c
		 
OBJS    = $(LIBLOCAL)($(SRCS:.c=.o) )

include	$(HOME)/Entwicklung/EVOS+/EVOS+2.mk

# DO NOT DELETE THIS LINE -- make depend depends on it.
