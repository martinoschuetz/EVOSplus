#	Schuetz, 18.04.1994
#	Root-Makefile for PEVOS+ and EVOSS+.
#
#	$Log: not supported by cvs2svn $
#
#
include $(HOME)/Entwicklung/EVOS+/EVOS+1.mk

MAINSRC = es.c
MAINOBJ = $(MAINSRC:.c=.o)
PMAINSRC= pes.c
PMAINOBJ= $(PMAINSRC:.c=.o)

normal:
ifeq (.pvm,$(wildcard .pvm))
	$(MAKE) PVM=NO dependall
	$(MAKE) PVM=NO clobber
	$(RM) $(LIB)/libfct.a $(LIB)/libmain.a 
	$(MAKE) PVM=NO default
	$(RM) .pvm
else
	$(MAKE) PVM=NO default
endif

parallel:
ifneq (.pvm,$(wildcard .pvm))
	$(MAKE) PVM=YES dependall
	$(MAKE) PVM=YES clobber
	$(RM) $(LIB)/libfct.a $(LIB)/libmain.a 
	$(MAKE) PVM=YES default
	touch .pvm
else
	$(MAKE) PVM=YES default
endif

ifeq ($(PVM),YES)
default: $(PMAIN) $(SERVER)
else
default: $(MAIN)
endif

$(PMAIN): $(MAINOBJ)
		$(ECHO) 'checking libraries :' ; \
		for DIR in `$(ECHO) $(DIRS)` ; do \
			$(ECHO) -n "updating $$DIR "; \
			cd $$DIR ; $(MAKE) PVM=YES; $(ECHO) ' '; cd ..;\
		done ; \
		$(ECHO) ' '; $(ECHO) "linking $(@F)"; $(ECHO) ' '
		$(CC) -o $(PMAIN) $(MAINOBJ) $(LDFLAGS)
#		purify $(CC) -o $(PMAIN) $(MAINOBJ) $(LDFLAGS)

$(SERVER): $(PMAINOBJ)
		$(ECHO) ' '; $(ECHO) "linking $(@F)"
		$(CC) -o $(SERVER) $(CFLAGS) $(PMAINOBJ) $(OBJS) $(LDFLAGS)
#		purify $(CC) -o $(SERVER) $(CFLAGS) $(PMAINOBJ) $(OBJS) $(LDFLAGS)
		$(MAKE) $(TKMAIN)

$(MAIN): $(MAINOBJ)
		$(ECHO) 'checking libraries :' ; \
		for DIR in `$(ECHO) $(DIRS)` ; do \
			$(ECHO) -n "updating $$DIR "; \
			cd $$DIR ; $(MAKE) PVM=NO; $(ECHO) ' '; cd ..;\
		done ; \
		$(ECHO) ' '; $(ECHO) "linking $(@F)"; $(ECHO) ' '
		$(CC) -o $(MAIN) $(MAINOBJ) $(LDFLAGS)
#		purify $(CC) -o $(MAIN) $(MAINOBJ) $(LDFLAGS)
		$(MAKE) $(TKMAIN)

ifeq ($(PVM),YES)
$(TKMAIN): 	$(SRC)/Main/params.c
		$(ECHO) "creating GUI for `basename $(SERVER)`"
		$(GUI) $(SERVER)
		$(MV) $(@F) $(BIN)
		chmod 770 $(TKMAIN)
else
$(TKMAIN): 	$(SRC)/Main/params.c
		$(ECHO) "creating GUI for `basename $(MAIN)`"
		$(GUI) $(MAIN)
		$(MV) $(@F) $(BIN)
		chmod 770 $(TKMAIN)
endif


ifeq ($(PVM),YES)
clean:
	$(RM) $(SERVER) $(PMAIN) $(TKMAIN)
else
clean:
	$(RM) $(MAIN) $(TKMAIN)
endif

ifeq ($(PVM),YES)
clobber	:
	$(RM) $(MAINOBJ) $(PMAINOBJ)
else
clobber	:
	$(RM) $(MAINOBJ)
endif

ifeq ($(PVM),YES)
totalclobber:
	$(ECHO) 'total cleaning :' ; \
	$(ECHO) -n 'EVOS '; $(MAKE) PVM=YES clobber ; \
	for DIR in `$(ECHO) $(DIRS)` ; do \
		$(ECHO) -n "$$DIR "; cd $$DIR ; $(MAKE) PVM=YES clobber; cd ..;\
	done ; \
	$(ECHO)
else
totalclobber:
	$(ECHO) 'total cleaning :' ; \
	$(ECHO) -n 'EVOS '; $(MAKE) PVM=NO clobber ; \
	for DIR in `$(ECHO) $(DIRS)` ; do \
		$(ECHO) -n "$$DIR "; cd $$DIR ; $(MAKE) PVM=NO clobber; cd ..;\
	done ; \
	$(ECHO)
endif

ifeq ($(PVM),YES)
dependall:
	$(ECHO) 'making all dependencies :'; \
	$(ECHO) -n 'EVOS '; makedepend $(DPFLAGS) $(MAINSRC) $(PMAINSRC); \
	for DIR in `$(ECHO) $(DIRS)` ; do \
		$(ECHO) -n "$$DIR "; cd $$DIR ; $(MAKE) PVM=YES depend; cd ..;\
	done ; \
	$(ECHO)
else
dependall:
	$(ECHO) 'making all dependencies :'; \
	$(ECHO) -n 'EVOS '; makedepend $(DPFLAGS) $(MAINSRC) ; \
	for DIR in `$(ECHO) $(DIRS)` ; do \
		$(ECHO) -n "$$DIR "; cd $$DIR ; $(MAKE) PVM=NO depend; cd ..;\
	done ; \
	$(ECHO)
endif

# DO NOT DELETE THIS LINE -- make depend depends on it.
