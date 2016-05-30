#	Schuetz, 06.06.1994
#	'make' prologue settings for EVOS+
#
#	$Log: not supported by cvs2svn $
#
#.SILENT:

.PRECIOUS: *.c *.h
.EXPORT_ALL_VARIABLES:

OS      = WINDOWS
PVM     = NO
DEBUG	= NO

EVOSPLUS= $(HOME)/Entwicklung/EVOS+
BIN		= $(EVOSPLUS)/bin
DOC		= $(EVOSPLUS)/doc
INCLUDE = $(EVOSPLUS)/inc
LIB		= $(EVOSPLUS)/lib
SRC		= $(EVOSPLUS)/src

PVM_HOME= $(HOME)/pvm3/bin/$(PVM_ARCH)
PVMINC	= $(PVM_ROOT)/include

PURIFY 	= purify
RANLIB	= ranlib
INSTALL = install
WHICH	= which
ARFLAGS	= rc
MV		= mv
CP		= cp
CC		= gcc
GUI     = $(BIN)/GUI
ifeq ($(OS),SOLARIS)
MAKE	= make
ECHO	= /usr/ucb/echo
else
MAKE	= make
ECHO	= echo
endif
ifeq ($(OS),WINDOWS)
MAIN	= $(BIN)/EVOS+.exe
PMAIN	= $(BIN)/PEVOS+.exe
SERVER	= $(BIN)/EVOSS+.exe
ifeq ($(PVM),YES)
TKMAIN	= $(BIN)/TkEVOSS+.exe
else
TKMAIN	= $(BIN)/TkEVOS+.exe
endif
else
MAIN	= $(BIN)/EVOS+
PMAIN	= $(BIN)/PEVOS+
SERVER	= $(BIN)/EVOSS+
ifeq ($(PVM),YES)
TKMAIN	= $(BIN)/TkEVOSS+
else
TKMAIN	= $(BIN)/TkEVOS+
endif
endif


.c.a:
	$(ECHO) -n '.'
#	$(ECHO) 'compiling $<'
	$(COMPILE.c) $<
	$(AR) $(ARFLAGS) $@ $%
	$(RM) $%

.f.a:
	$(ECHO) -n '.'
#	$(ECHO) 'compiling $<'
	$(COMPILE.f) $<
	$(AR) $(ARFLAGS) $@ $%
	$(RM) $%


ifeq ($(OS),LINUX)
#GCC_INCLUDE = /usr/lib/gcc-lib/i486-linux/3.3.2/include
GCC_INCLUDE = /usr/lib/gcc-lib/i386-linux/3.3.2/include
GNU_INCLUDE =
XTRALIBS	=
#FLIB	    = /home/ls11/lib
#FLIBS       = -lf2cF77 -lf2cI77
FLIB	    = 
FLIBS       = 
endif

ifeq ($(OS),WINDOWS)
OS		= LINUX
GCC_INCLUDE = 
#/usr/lib/gcc-lib/i686-pc-cygwin/3.2/include/
GNU_INCLUDE =
XTRALIBS	=
#FLIB	    = /home/ls11/lib
#FLIBS       = -lf2cF77 -lf2cI77
FLIB	    = 
FLIBS       = 
endif

ifeq ($(OS),SUN)
GCC_INCLUDE = $(GCC_INCLUDE_DIR)
GNU_INCLUDE = $(TOOL_INCLUDE_DIR)
XTRALIBS	=
FLIB	    = /home/ls11soft/lib
FLIBS		= -lf2cF77 -lf2cI77
endif

ifeq ($(OS),SOLARIS)
OS			= LINUX
#GCC_INCLUDE = $(GCC_INCLUDE_DIR)
#GNU_INCLUDE = $(TOOL_INCLUDE_DIR)
GCC_INCLUDE =
GNU_INCLUDE =
XTRALIBS	= -lnsl -lsocket
FLIB	    = /home/soft1/lib
FLIBS       = -lf2c
endif

# Fuer die Schnittstelle zum  Aspen-Simulator.
NORMALDPFLAGS	= -I$(INCLUDE) -I$(GCC_INCLUDE) -I$(GNU_INCLUDE)\
-D$(OS)
#-D$(OS) -DSTRERROR_MISSING -DUNIX -DAACHEN
DEBUGDPFLAGS	= -I$(INCLUDE) -I$(GCC_INCLUDE) -I$(GNU_INCLUDE)\
-D$(OS) -DDEBUG
#-D$(OS) -DSTRERROR_MISSING -DUNIX -DAACHEN -DDEBUG
#NORMALCFLAGS 	= $(NORMALDPFLAGS) -O3 -pipe -ansi -Wall -pedantic
DEBUGCFLAGS		= $(DEBUGDPFLAGS)  -g3 -pipe -ansi -Wall -pedantic
NORMALCFLAGS 	= $(NORMALDPFLAGS) -O3 -pipe -ansi -pedantic
#DEBUGCFLAGS		= $(DEBUGDPFLAGS)  -g3 -pipe -ansi -pedantic

ifeq ($(PVM),NO)
DIRS    = Adapt Datatypes Fct Main Mute Reco Rng Rst Utilities Transform
ifeq ($(DEBUG),NO)
DPFLAGS	= $(NORMALDPFLAGS)
CFLAGS	= $(NORMALCFLAGS)
else
DPFLAGS	= $(DEBUGDPFLAGS)
CFLAGS	= $(DEBUGCFLAGS)
endif
LDFLAGS = -L$(LIB)\
-lmain -lmute -lreco -lrng -lfct -lrst -lutil -ltyp -ltransform -ladapt\
-lm -lc
LIBS    = $(LIB)/libutil.a  $(LIB)/libtyp.a  $(LIB)/librng.a            \
          $(LIB)/libfct.a   $(LIB)/librst.a  $(LIB)/libreco.a           \
          $(LIB)/libadapt.a $(LIB)/libmute.a $(LIB)/libtransform.a      \
          $(LIB)/libmain.a
#-lmain -lmute -lreco -lrng -lfct -lrst -lutil -ltyp -ltransform -ladapt\
#-L$(FLIB) $(FLIBS) -lm -lc
else
DIRS    = Adapt Datatypes Fct Main Mute Reco Rng Rst Utilities Transform Topology
ifeq ($(DEBUG),NO)
DPFLAGS	= $(NORMALDPFLAGS) -I$(PVMINC) -DPVM
CFLAGS	= $(NORMALCFLAGS)  -I$(PVMINC) -DPVM
else
DPFLAGS	= $(DEBUGDPFLAGS)  -I$(PVMINC) -DPVM
CFLAGS	= $(DEBUGCFLAGS)   -I$(PVMINC) -DPVM
endif
LDFLAGS = -L$(LIB) -lmain -lmute -lreco -lrng -lfct -lrst -lutil -ltyp\
-ltransform -ladapt -ltop\
-lm -lc\
-L$(PVM_ROOT)/lib/$(PVM_ARCH) -lpvm3 -lgpvm3
#-L$(FLIB) $(XTRALIBS) $(FLIBS) -lm -lc\
#-L$(XMDB_HOME)/lib -lmdb
LIBS    = $(LIB)/libutil.a  $(LIB)/libtyp.a  $(LIB)/librng.a            \
          $(LIB)/libfct.a   $(LIB)/librst.a  $(LIB)/libreco.a           \
          $(LIB)/libadapt.a $(LIB)/libmute.a $(LIB)/libtransform.a      \
          $(LIB)/libtop.a   $(LIB)/libmain.a
endif

