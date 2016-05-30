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
 *	file:	rectangle.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	02.05.1995
 *
 *   purpose:	Implementation of a rectangle (standard or moore) topology.
 *
 *    remark:	The caller routine must work until RectangleNext gives
 *		a negative value, otherwise the topology results not
 *		in a rectangle.
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:40:28  schuetz
 * *** empty log message ***
 *
 * 
 */

#include "topology.h"
#include "getparm.h"


static	char	topology   = 'm';  /* moore neighbourhood default topology. */
static	int	neighbours = 1;    /* One neighbour to each side is default.*/
static	int	(*Next)(param_tPtr); /* Actual topology incarnation. */
static  int	SquareSize = 4;	     /*  Default square is 4x4. */

int	RectangleStandard(param_tPtr eps);
int	RectangleMoore(param_tPtr eps);


/*
 * RectangleInit -- convert parms to topology local data.
 */

static struct option TOPOLOGYopts[] =
{
        {"topology",   GP_VALSEP, 't'},
        {"neighbours", GP_VALSEP, 'n'},
        {0,	     0,		0}
};


bool RectangleInit(char *parms)

{
	extern 	param_t	eps; /* Short cut because of an bad design.*/

	char	optarg[BUFSIZ];
	int	c;

	if(NULL == parms) {
#ifdef DEBUG
		panic(A_WARN, "RectangleInit", "no parameters given : %s : %d",
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

		default: panic(A_WARN, "RectangleInit", 
			       "failed to parse : %s : %d", __FILE__, __LINE__);
			 topology = 'm';
			 return(FALSE);
	    }
	}

	if(topology == 'm')
		Next = RectangleMoore;
	else
		Next = RectangleStandard;

	SquareSize = (int) sqrt((double) eps.Tasks);

	if(sqrt((double) eps.Tasks) != SquareSize) {
		panic(A_FATAL, "Number of tasks no square number : %s : %d",
		      __FILE__, __LINE__);
		return(FALSE);
	}

	return(TRUE);
}



int	RectangleNext(param_tPtr eps)

{
	return(Next(eps));
}



int	RectangleStandard(param_tPtr eps)

{
	static int	inst = -1; /* New call of routine. */
	static bool	postion = 0;
	int		neighbour;


	if(eps->inst == 0)
		panic(A_FATAL,"RectangleBidirectional",
		      "master can't send individuals : %s :%d",
		      __FILE__, __LINE__);

	if(inst == -1)		/* First call; initialization. */
		inst = 1;

	if((postion == 0) && (inst > neighbours)) {
		inst = -1;
		return(inst);
	} /* Termination criterion. */

	switch(postion) {

	    case 0: neighbour = (eps->inst - inst <= 0) ? 
				eps->Tasks + eps->inst - inst : 
				eps->inst - inst;
	    neighbour = pvm_gettid(eps->Group, neighbour);
	    if(neighbour < 0)
	    	panic(A_FATAL,"RectangleBidirectional",
		      "can't get tid of neighbour (%d)", eps->inst);
	    left = FALSE;
	}
	else {
	    neighbour = (eps->inst + inst > eps->Tasks ) ? 
				eps->inst + inst - eps->Tasks : 
				eps->inst + inst;
	    neighbour = pvm_gettid(eps->Group, neighbour);
	    if(neighbour < 0)
		panic(A_FATAL,"RectangleBidirectional",
		     "can't get tid of neighbour (%d)", eps->inst);
	    left = TRUE;
	    inst++;
	}

	return(neighbour);
}



int	RectangleMoore(param_tPtr eps)

{
	fprintf(stderr,"\nNOT YET IMPLEMENTED\n");

	return(0);
}



bool	RectangleTerm(param_tPtr eps)

{
	return(TRUE);
}
