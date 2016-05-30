/****************************************************************/
/*                                                           	*/
/*  Copyright (c) 1993                                       	*/
/*  Martin Schuetz                                             	*/
/*  Computer Science Department, LSXI       			*/
/*  University of Dortmund                                   	*/
/*  Baroper Str. 301                                         	*/
/*  D-44221 Dortmund						*/
/*  Germany							*/
/*								*/
/*  e-mail: schuetz@edna.informatik.uni-dortmund.de		*/
/*  	    schuetz@ls11.informatik.uni-dortmund.de		*/
/*								*/
/*  Permission is hereby granted to copy all or any part of  	*/
/*  this program for free distribution.   The author's name  	*/
/*  and this copyright notice must be included in any copy.  	*/
/*                                                           	*/
/****************************************************************/

/*
 *	file:	rst.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	11.03.1994
 *
 *   purpose:	Device-Manager for the restriction-library
 *
 *    remark:	The Program is based on the interface to JAZZ-C's
 *		ENV device manager which is written by
 *		Joerg Heitkoetter (c) 1994.
 *
 *		It is expected that restrictions have the form
 *
 *		g (x,d) >= 0, forall i in {1,...,m}
 *		 i
 *		h (x,d) = 0,  forall j in { 1,...,l}
 *		 j
 *
 *		(g ,...,g ,h ,...,h )(x,d) = R(x,d) (a vectorvalued Function)
 *		  1	 m  1	   l
 *
 *		where x is the real-valued part of the object variable vector
 *		and d the discrete part.
 *		So we have to interesting forms of penalties:
 *
 *		1.) We are just interested in wether a restriction is
 *		    violated or not. In this case we want to
 *		    parameterize the restriction function with
 *		    "penalty = TRUE". The returned double can be interpreted
 *		    as an boolean. 'TRUE' is returned if a restriction
 *		    is violated, 'FALSE' otherwise.
 *		2.) A penalty function of the Form  S(x,d) = f(x,d) + R(x,d)
 *		    is given.
 *		    So we are interested in the value of R, which may be
 *		    reached by the parameter choice "penalty = FALSE".
 *
 *		Each restriction has an identifier string,
 *		a restriction description, a usage string and a
 *		parameter string, which is initially NULL.
 *		The parameter string is parseble and therefore can be
 *		taken for restriction initialization.
 *		Additionally each restriction is seperated into three
 *		subroutines 'init', 'eval' and 'term'.
 *		'init' serves for parameter parsing and checks against
 *		fixed restriction dimensions.
 *		'eval' constitutes a restriction evaluation.
 *		'term' may for example free memory allocated by 'init'.
 *		(see RSTdvice in rst.h)
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:38:26  schuetz
 * pvm integrated
 *
 * Revision 1.4  1995/02/06  08:13:36  schuetz
 * GUI version
 *
 * Revision 1.3  1994/06/06  16:43:18  schuetz
 * rcsid deleted.
 *
 * Revision 1.3  1994/06/06  16:43:18  schuetz
 * rcsid deleted.
 *
 * Revision 1.2  1994/05/08  16:24:53  schuetz
 * bugfix.
 *
 * Revision 1.1  1994/04/18  09:26:39  schuetz
 * Initial revision
 *
 * 
 */



#include "rst.h"


bool InitRST(char *parms);


static RSTdevice RSTtable[] = {

{
"null",
"\nnull : dummy device",
"no parameters",
NULL, NullRstInit, NullRstEval, NullRstTerm
},

{
"naca",
"Restriction for NACA airfoil optimization",
"no parameters",
NULL, NacaRstInit, NacaRstEval, NacaRstTerm
},

{
"reflection",
"Restriction for the optical problem form Greiner.",
"no parameters",
NULL, reflectionRstInit, reflectionRstEval, reflectionRstTerm
},

{
"standard",
"\nStandard Restriction :\n\
\t LowerBound <= x_i <= UpperBound",
"lower = <value>, upper = <value>",
NULL, StandardInit, StandardEval, StandardTerm
}

};

#define RST_DEVICES     (sizeof(RSTtable)/sizeof(RSTdevice))


/* currently active restriction */
static RSTdevice *RST	  = &RSTtable[0];
static int	 RSTdevno = 0;


/* create a new RST device/object */
/* RSTdevice *newRST(char *id,...)*/
RSTdevice *newRST(char *id, char *parms)

{
/*	va_list args;
	char	*parms;*/
	int	i;


/*	VA_START(args, id);
	parms = va_arg(args, char *);
	va_end(args);
*/
	for (i = 0; i < RST_DEVICES; i++) {
		if (!strcmp(RSTtable[i].id, id)) {
			RST = (RSTdevice *) &RSTtable[i];
			RSTdevno = i;
			if (RST->parms != NULL)
				free(RST->parms);
			if(parms != NULL)
				if(NULL == (RST->parms = strdup(parms)))
						panic(A_WARN, "newRST",
						      "not enough memory : %s : %d",
						      __FILE__, __LINE__);

		      	if(FALSE == InitRST(RST->parms))
				RST->parms = NULL;
			break;
		}
	}
	
	if (i == RST_DEVICES && RSTdevno != i)
		panic(A_WARN, "newRST", "No such RST device '%s',\
stick with `%s': '%s' : %d", id, thisRST()->id, __FILE__, __LINE__);

        return ((RSTdevice *) RST);
}



RSTdevice *thisRST(void)
{
	return ((RSTdevice *) RST);
}


/* delete RST device/object */
void deleteRST(void)
{
	int             i;

	for (i = 0; i < RST_DEVICES; i++)
		if (RSTtable[i].parms != NULL) {
                        free(RSTtable[i].parms);
                        RSTtable[i].parms = NULL;
		}

	(*RST->term)();
/*	Termination of the current restriction device;
	perhaps freeing local memory. */
}


/* test */
void testRST(void)

{
	fprintf(stderr,"\nTest not yet implemented\n");
}


/* return actual tablesize */
int tableSizeRST(void)
{
	return(RST_DEVICES);
}

/* list all available RST devices */
void listRST(void)
{
	int             i;

	fprintf(stderr, "total %d restriction functions\n", RST_DEVICES);
	for (i = 0; i < RST_DEVICES; i++) {
		fprintf(stderr, "%-8s %s\n", RSTtable[i].id, RSTtable[i].note);
		fprintf(stderr, "usage: %s\n\n", RSTtable[i].usage);
	}
}


/* return the id string of currently used RST device */
char *activeRST(void)

{
	return (RST->id);
}



/* Initialization of the current restriction device; parameter parsing. */
bool InitRST(char *parms)

{
	return((*RST->init)(parms));
}



/* Realization of an restriction evaluation. */
double EvalRST(vector_tPtr x, Ivector_tPtr d)

{
	return((*RST->eval)(x,d));
}
