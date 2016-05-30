/****************************************************************/
/*                                                           	*/
/*  Copyright (c) 1995                                       	*/
/*  Martin Schuetz                                             	*/
/*  Computer Science Department, LSXI       			*/
/*  University of Dortmund                                   	*/
/*  Baroper Str. 301                                         	*/
/*  D-44221 Dortmund						*/
/*  Germany							*/
/*								*/
/*  e-mail: schuetz@ls11.informatik.uni-dortmund.de		*/
/*								*/
/*  Permission is hereby granted to copy all or any part of  	*/
/*  this program for free distribution.   The author's name  	*/
/*  and this copyright notice must be included in any copy.  	*/
/*                                                           	*/
/****************************************************************/

/*
 *	file:	topology.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	02.05.1995
 *
 *   purpose:	Device-Manager for the topology library
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:40:37  schuetz
 * *** empty log message ***
 *
 * 
 */

#include "topology.h"


bool InitTOPOLOGY(char *parms);


static TOPOLOGYdevice TOPOLOGYtable[] = {

{
"null",
"\nnull : dummy device",
"no parameters",
NULL, NullTopologyInit, NullTopologyNext, NullTopologyTerm
},

{
"circle",
"Implementation of a ring topology with variable neighbourhood size.\n\
neighbours (in each direction) must be >= 1",
"topology = bidirectional|unidirectional, neighbours = <value>",
NULL, CircleInit, CircleNext, CircleTerm
}/*,

{
"rectangle",
"Implementation of a rectangle topology with variable neighbourhood size.\n\
neighbours (in each direction) must be >= 1",
"topology = standard|moore, neighbours = <value>",
NULL, RectangleInit, RectangleNext, RectangleTerm
}
*/
};

#define TOPOLOGY_DEVICES     (sizeof(TOPOLOGYtable)/sizeof(TOPOLOGYdevice))


/* currently active function */
static TOPOLOGYdevice	*TOPOLOGY     = &TOPOLOGYtable[0];
static int		TOPOLOGYdevno = 0;


/* create a new TOPOLOGY device/object */
/* TOPOLOGYdevice *newTOPOLOGY(char *id,...)*/
TOPOLOGYdevice *newTOPOLOGY(char *id, char *parms)

{
/*	va_list args;
	char	*parms;*/
	int	i;


/*	VA_START(args, id);
	parms = va_arg(args, char *);
	va_end(args);
*/
	for (i = 0; i < TOPOLOGY_DEVICES; i++) {
		if (!strcmp(TOPOLOGYtable[i].id, id)) {
			TOPOLOGY = (TOPOLOGYdevice *) &TOPOLOGYtable[i];
			TOPOLOGYdevno = i;
			if (TOPOLOGY->parms != NULL)
				free(TOPOLOGY->parms);
			if(parms != NULL)
				if(NULL == (TOPOLOGY->parms = strdup(parms)))
					panic(A_WARN, "newTOPOLOGY",
					      "not enough memory : %s : %d",
					      __FILE__, __LINE__);


			if(FALSE == InitTOPOLOGY(TOPOLOGY->parms)) {
				free(TOPOLOGY->parms);
				TOPOLOGY->parms= NULL;
			}
			break;
		}
	}
	
	if(i == TOPOLOGY_DEVICES && TOPOLOGYdevno != i)
		panic(A_FATAL, "newTOPOLOGY", "No such TOPOLOGY device '%s',\
stick with `%s' : '%s' : %d",id ,thisTOPOLOGY()->id, __FILE__, __LINE__);

        return ((TOPOLOGYdevice *) TOPOLOGY);
}



TOPOLOGYdevice *thisTOPOLOGY(void)
{
	return ((TOPOLOGYdevice *) TOPOLOGY);
}


/* delete TOPOLOGY device/object */
void deleteTOPOLOGY(param_tPtr eps	/* parameter structure */)
{
	int             i;

	for (i = 0; i < TOPOLOGY_DEVICES; i++)
		if (TOPOLOGYtable[i].parms != NULL) {
			free(TOPOLOGYtable[i].parms);
			TOPOLOGYtable[i].parms = NULL;
		}

	(*TOPOLOGY->term)(eps);
/* Termination of the current function device; perhaps freeing local memory. */
}


/* test */
void testTOPOLOGY(void)

{
	fprintf(stderr,"\nTest not yet implemented\n");
}

/* return actual tablesize */
int tableSizeTOPOLOGY(void)
{
        return(TOPOLOGY_DEVICES);
}

/* list all available TOPOLOGY devices */
void listTOPOLOGY(void)
{
	int             i;

	fprintf(stderr, "total %d object functions\n", TOPOLOGY_DEVICES);
	for (i = 0; i < TOPOLOGY_DEVICES; i++) {
		fprintf(stderr, "%-8s %s\n", TOPOLOGYtable[i].id, TOPOLOGYtable[i].note);
		fprintf(stderr, "usage: %s\n\n", TOPOLOGYtable[i].usage);
	}
}


/* return the id string of currently used TOPOLOGY device */
char *activeTOPOLOGY(void)

{
	return (TOPOLOGY->id);
}



/* Initialization of the current function device; parameter parsing. */
bool InitTOPOLOGY(char *parms)

{
	return((*TOPOLOGY->init)(parms));
}



/* Realization of an function evaluation. */
int NextTOPOLOGY(param_tPtr eps)

{
	return((*TOPOLOGY->next)(eps));
}
