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
 *	file:	circle.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	02.05.1995
 *
 *   purpose:	Implementation of a circle topology
 *
 *    remark:	The caller routine must work until CircleNext gives
 *		a negative value, otherwise the topology results not
 *		in a ring.
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:39:51  schuetz
 * *** empty log message ***
 *
 * 
 */

#include "topology.h"
#include "getparm.h"


static	char	topology   = 'b';  /* bidirectional ring default topology. */
static	int	neighbours = 1;    /* One neighbour to each side is default.*/
static	int	(*Next)(param_tPtr); /* Actual topology incarnation. */

int	CircleUnidirectional(param_tPtr eps);
int	CircleBidirectional(param_tPtr eps);


/*
 * CircleInit -- convert parms to topology local data.
 */

static struct option TOPOLOGYopts[] =
{
        {"topology",   GP_VALSEP, 't'},
        {"neighbours", GP_VALSEP, 'n'},
        {0,	     0,		0}
};


bool CircleInit(char *parms)

{
	char	optarg[BUFSIZ];
	int	c;

	if(NULL == parms) {
#ifdef DEBUG
		panic(A_WARN, "CircleInit", "no parameters given : %s : %d",
		      __FILE__, __LINE__);
#endif
		return(TRUE);
	}

	while((c = getparm(parms, TOPOLOGYopts, optarg)) != EOF) {
	    switch (c) {
		case 't': topology = *optarg;
			  break;

		case 'n': neighbours = atoi(optarg);
			  break;

		default: panic(A_WARN, "CircleInit", 
			       "failed to parse : %s : %d", __FILE__, __LINE__);
			 topology = 'b';
			 return(FALSE);
	    }
	}

	if(topology == 'u')
		Next = CircleUnidirectional;
	else
		Next = CircleBidirectional;

	return(TRUE);
}



int	CircleNext(param_tPtr eps)

{
	return(Next(eps));
}



int	CircleUnidirectional(param_tPtr eps)

{
	static int	inst = -1; /* New call of routine. */
	int		neighbour;


	if(eps->inst == 0)
		panic(A_FATAL,"CircleBidirectional",
		      "master can't send individuals : %s :%d",
		      __FILE__, __LINE__);

	if(inst == -1)		/* First call; initialization. */
		inst = 1;

	if(inst > neighbours) {
		inst = -1;
		return(inst);
	} /* Termination criterion. */

	neighbour = (eps->inst + inst > eps->Tasks ) ? 
				eps->inst + inst - eps->Tasks : 
				eps->inst + inst;
	neighbour = pvm_gettid(eps->Group, neighbour);
	if(neighbour < 0)
		panic(A_FATAL,"CircleBidirectional",
		     "can't get tid of neighbour (%d)", eps->inst);
	inst++;

	return(neighbour);
}



int	CircleBidirectional(param_tPtr eps)

{
	static int	inst = -1; /* New call of routine. */
	static bool	left = TRUE;
	int		neighbour;

	if(eps->inst == 0)
		panic(A_FATAL,"CircleBidirectional",
		      "master can't send individuals : %s :%d",
		      __FILE__, __LINE__);

	if(inst == -1)		/* First call; initialization. */
		inst = 1;

	if((left == TRUE) && (inst > neighbours)) {
		inst = -1;
		return(inst);
	} /* Termination criterion. */

	if(left == TRUE) {
	    neighbour = (eps->inst - inst <= 0) ? 
				eps->Tasks + eps->inst - inst : 
				eps->inst - inst;
	    neighbour = pvm_gettid(eps->Group, neighbour);
	    if(neighbour < 0)
	    	panic(A_FATAL,"CircleBidirectional",
		      "can't get tid (%d) of left neighbour (%d)", neighbour,eps->inst);
	    left = FALSE;
	}
	else {
	    neighbour = (eps->inst + inst > eps->Tasks ) ? 
				eps->inst + inst - eps->Tasks : 
				eps->inst + inst;
	    neighbour = pvm_gettid(eps->Group, neighbour);
	    if(neighbour < 0)
		panic(A_FATAL,"CircleBidirectional",
		      "can't get tid (%d) of right neighbour (%d)", neighbour,eps->inst);
	    left = TRUE;
	    inst++;
	}

	return(neighbour);
}



bool	CircleTerm(param_tPtr eps)

{
	return(TRUE);
}
