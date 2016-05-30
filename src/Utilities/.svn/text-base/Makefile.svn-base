#
#	Makefile for the library <lib> and testprogramm <test>.
#
#	$Log: not supported by cvs2svn $
# Revision 1.1  1994/06/06  14:48:10  schuetz
# Initial revision
#
# Revision 1.1  1994/06/06  14:48:10  schuetz
# Initial revision
#
#

include	$(HOME)/Entwicklung/EVOS+/EVOS+1.mk

LIBLOCAL= $(LIB)/libutil.a
LIBS	=

LLOCAL	= -lutil
LLIBS	=

PRG	= 
PRGPURE	= 

PRGSRC	= 
PRGOBJ	= 

#SRCS	= getopt.c getopt1.c getparm.c getparam.c panic.c
SRCS	= getparam.c getparm.c panic.c
OBJS    = $(LIBLOCAL)($(SRCS:.c=.o) )

include	$(HOME)/Entwicklung/EVOS+/EVOS+2.mk

getopt : getopt.c
	$(CC) -o getopt $(CFLAGS) -DTEST getopt.c

getopt1: getopt.o getopt1.c
	$(CC) -o getopt1 $(CFLAGS) -DTEST getopt1.c getopt.o
		  
getparm: getparm.c
	 $(CC) -o getparm $(CFLAGS) -DTEST getparm.c

# DO NOT DELETE THIS LINE -- make depend depends on it.

//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(getparam.o): /usr/include/stdio.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(getparam.o): /usr/include/_ansi.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(getparam.o): /usr/include/newlib.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(getparam.o): /usr/include/sys/config.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(getparam.o): /usr/include/machine/ieeefp.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(getparam.o): /usr/include/sys/reent.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(getparam.o): /usr/include/sys/_types.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(getparam.o): /usr/include/sys/types.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(getparam.o): /usr/include/machine/types.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(getparam.o): /usr/include/sys/stdio.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(getparam.o): /usr/include/ctype.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(getparam.o): /usr/include/string.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(getparm.o): /usr/include/stdio.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(getparm.o): /usr/include/_ansi.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(getparm.o): /usr/include/newlib.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(getparm.o): /usr/include/sys/config.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(getparm.o): /usr/include/machine/ieeefp.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(getparm.o): /usr/include/sys/reent.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(getparm.o): /usr/include/sys/_types.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(getparm.o): /usr/include/sys/types.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(getparm.o): /usr/include/machine/types.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(getparm.o): /usr/include/sys/stdio.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(getparm.o): /usr/include/ctype.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(getparm.o): /usr/include/string.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(panic.o): /usr/include/stdio.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(panic.o): /usr/include/_ansi.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(panic.o): /usr/include/newlib.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(panic.o): /usr/include/sys/config.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(panic.o): /usr/include/machine/ieeefp.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(panic.o): /usr/include/sys/reent.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(panic.o): /usr/include/sys/_types.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(panic.o): /usr/include/sys/types.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(panic.o): /usr/include/machine/types.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(panic.o): /usr/include/sys/stdio.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(panic.o): /usr/include/errno.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(panic.o): /usr/include/sys/errno.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(panic.o): /usr/include/time.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(panic.o): /usr/include/machine/time.h
//server1/schuetz/Entwicklung/EVOS+/lib/libutil.a(panic.o): /usr/include/sys/features.h
