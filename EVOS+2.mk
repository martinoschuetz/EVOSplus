#	Schuetz, 06.06.1994
#	'make' epilogue settings for EVOS+
#
#	$Log: not supported by cvs2svn $
#
#

LDFLAGS	= -L$(LIB) -L$(FLIB) $(LLOCAL) $(LLIBS) -lm

all : $(LIBLOCAL)

test : $(LIBLOCAL) $(LIBS) $(PRGOBJ)
	$(ECHO) 'linking'
	$(CC) -o $(PRG) $(PRGOBJ) $(LDFLAGS)

ptest : $(LIBLOCAL) $(LIBS) $(PRGOBJ)
	$(ECHO) 'purify linking'
	$(PURIFY) $(CC) -o $(PRGPURE) $(PRGOBJ) $(LDFLAGS)

$(LIBLOCAL): $(OBJS)
	$(RANLIB) $(LIBLOCAL)
	$(ECHO) -n " $(@F) done"

empty :
	$(ECHO) 'cleaning up purify files'
	$(RM) *pur*

clobber:
#	$(ECHO) 'cleaning up objects and library'
	$(RM) $(PRG) $(LIBLOCAL)

depend :
#	$(ECHO) "$(DPFLAGS)"
#	$(ECHO) 'making dependencies'
	makedepend $(DPFLAGS) $(PRGSRC)
	makedepend -a -p "$(LIBLOCAL)(" -o ".o)" $(DPFLAGS) $(SRCS)
	$(RM) Makefile.bak
