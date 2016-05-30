/****************************************************************/
/*                                                           	*/
/*  Copyright (c) 1993                                       	*/
/*  Martin Schuetz                                             	*/
/*  Computer Science Department, LSXI							*/
/*  University of Dortmund                                   	*/
/*  Baroper Str. 301                                         	*/
/*  D-44221 Dortmund											*/
/*  Germany														*/
/*																*/
/*  e-mail: schuetz@edna.informatik.uni-dortmund.de				*/
/*  	    schuetz@ls11.informatik.uni-dortmund.de				*/
/*																*/
/*  Permission is hereby granted to copy all or any part of  	*/
/*  this program for free distribution.   The author's name  	*/
/*  and this copyright notice must be included in any copy.  	*/
/*                                                           	*/
/****************************************************************/

/*
 *	file:	fct.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	11.03.1994
 *
 *   purpose:	Device-Manager for the functionlibrary
 *
 *    remark:	The Program is based on the interface to JAZZ-C's
 *		ENV device manager which is written by
 *		Joerg Heitkoetter (c) 1994.
 *
 *		It is expected that function have the form f(x,d), where
 *		x is the real-valued part of the object variable vector
 *		and d the discrete part.
 *		Each function has an identifier string, a function description,
 *		a usage string and a parameter string, which is initially NULL.
 *		The parameter string is parseble and therefore can be
 *		taken for function initialization.
 *		Additionally each function is seperated into three
 *		subroutines 'init', 'eval' and 'term'.
 *		'init' serves for parameter parsing and checks against
 *		fixed function dimensions.
 *		'eval' constitutes a function evaluation.
 *		'term' may for example free memory allocated by 'init'.
 *		(see FCTdvice in fct.h)
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:36:16  schuetz
 * pvm integrated
 *
 * Revision 1.5  1995/02/06  08:11:42  schuetz
 * GUI version
 *
 * Revision 1.4  1994/07/06  07:05:45  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.3  1994/06/06  16:34:16  schuetz
 * y
 * rcsid deleted.
 *
 * Revision 1.2  1994/05/11  12:38:40  schuetz
 * genRosenbrock function added.
 *
 * Revision 1.1  1994/04/18  09:26:39  schuetz
 * Initial revision
 *
 * 
 */




#include "fct.h"


static FCTdevice FCTtable[] = {

{
"null",
"\nnull : dummy device",
"no parameters",
NULL, NullFctInit, NullFctEval, NullFctTerm
},
	 

{
"arma",
"\nParameter estimation for time series.\n",
"no parameters",
NULL, armaInit, armaEval, armaTerm
},
/*
{
"clima",
"\nOptimization of the clima modell designed by Jentsch.\n",
"no parameters",
NULL, climaInit, climaEval, climaTerm
},
*/
{
"constant",
"\nConstant function : f(x,d) = c\n",
"constant = <value>",
NULL, constantInit, constantEval, constantTerm
},

{
"counting",
"\nImplementation of the generalized (modified) counting ones problem (cop).\n\
Normally the cop is defined on bit strings and is known as a standard GA\n\
problem. If 'a' is a bit string of length n, one searches for the\n\
maximum of f(a) = sum_{i=1}^n a_i. So the maximum point is the 'one'\n\
bit string. The above task can be extended to strings of length n\n\
over an alphabet 0, ..., b-1, of 'cardinality b'.\n\
This time the fitness function will 'count' how often 'i' occures in the\n\
string 'a'. f(a) = sum_{j=1}^n delta_{i,a_j}, where the	Kroneckersymbol\n\
delta_{i,j} is defined to 1 if i=j, 0 otherwise. This leads to the 'i'-string\n\
as optimum vector and a maximum fitness value of n*i.\n\
Here the extended cop will be used for exploring the mutation mechanismen\n\
for mutation rates, wich Schuetz proposed in his diploma thesis.\n\
If the algorithm is able to learn the rates (one rate) one should observe\n\
decreasing rates during the approximation of the optimum.\n\
Even if the optimum is 'shift'ed after some 'm' iteration,\n\
for example the problem is changed to the counting i+1 problem, the rates\n\
should decrease during the run.	In order to check the learnig of the rate(s),\n\
n-f(a)/n will be minimized (n is added to get positiv function values,\n\
the division by scale the fitness between 0 and 1).\n\
Furthermore the implementation hides the possibility\n\
to choose wether a switching of the optimum should happen (setting m != 0\n\
indicates the number of function evaluations after which the switch shall\n\
happen) or not	(m == 0). The setting of i, the counting number is also\n\
possible. If switching is omitted, the counting i problem is set,\n\
otherwise i is the start number for the switch (successor switch i, i+1, i+2,\n\
..., (shift = 's') and random switch i, U(0,b-1) (shift = 'r')).\n\
The last important setting is the 'cardinality b' of the allowed alphabet,\n\
which enables a checking of the genom and restricts i to b-1.\n",
"shift = <value>, count = <value>, switch = random | successor",
NULL, countingInit, countingEval, countingTerm
},

{
"ellepsoid",
"\nobjective function, hyperellepsoid.\n\
f(x) = sum_{i=1}^n (sum_{j=1}^i x_j)^2.\n\
Problem according to Schw77, problem 1.2",
"no parameters",
NULL, ellepsoidInit, ellepsoidEval, ellepsoidTerm
},

{
"exposum",
"\nexponention sum function after Goldberg for testing\n\
building blocks. Also real coded version.\n\
f(x) = sum_{i=0}^{n-1} 2^i x_i.",
"control = <binary|real>",
NULL, ExpoSumInit, ExpoSumEval, ExpoSumTerm
},

{
"fletcherPowell",
"objective function, according to Fletcher and Powell.\n\
See also Schwefels problem 2.13.\n\
f(x) = sum_{i=1}^n (A_i - B_i)**2\n\
 \n\
A_i =  sum_{j=1}^n (a_{ij} sin(alpha_j) + b_{ij} cos(alpha_j))\n\
B_i =  sum_{j=1}^n (a_{ij} sin(x_j)     + b_{ij} cos(x_j))\n\
i = 1, ..., n\n\
a_{ij}, b_{ij} ~ U(-100,...,100), alpha_j ~ U(-pi, pi)\n\
remark:   For test reasons ist possible to choose a special form\n\
	  of the problem.\n\
If control == fix, then a_{ij} = 1, b_{ij} = 0 and alpha_j = 0.\n\
So the problem shrinks to a simplified form :\n\
f(x) = n * ( sum_{j=1}^n x_j)**2.\n\
For this special form a mixed-integer test function is\n\
created, which is activated by control = mixed.\n\
f(x) = (n_x + n_d) * (sum_{j=1}^n sin(x_j) + sum_{j=1}^n sin(d_j))**2.",
"control = random | fix | mixed",
NULL, fletcherPowInit, fletcherPowEval, fletcherPowTerm
},

{
"genRosenbrock",
"\nGeneralized Rosenbrock function :\n\
\t\tsum_{i=1}^{n-1} (100 * (x_{i+1} - x_i^2)^2 + (x_i - 1)^2)",
"no parameter",
NULL, genRosenbrockInit, genRosenbrockEval, genRosenbrockTerm
},

{
"trint0",
"\nTrint function F0. Extended mixed-integer sphere model",
"A = <value>",
NULL, trintF0Init, trintF0Eval, trintF0Term
},

{
"trint1",
"\nTrint function F. Biased mixed-integer sphere model",
"A = <value>",
NULL, trintF1Init, trintF1Eval, trintF1Term
},

{
"trint3",
"\nTrint varialbe-dimensional function F3",
"A = <value>",
NULL, trintF3Init, trintF3Eval, trintF3Term
},
/*
{
"naca",
"\nNaca airfoil optimization",
"no parameter",
NULL, NacaInit, NacaEval, NacaTerm
},
*/
{
"simplePlain",
"\nSimple plain: f(x) = - c_1 * x_1",
"constant = <value>",
NULL, simplePlainInit, simplePlainEval, simplePlainTerm
},

{
"parable",
"\nParable ridge : f(x) = -x_1 +c*sum_{i=2}^n x_i^\alpha",
"c = <value>, alpha = <value>",
NULL, ParableInit, ParableEval, ParableTerm
},
/*
{
"plant",
"\nOptimization of an HDA-Chemical Engineering Plant",
"lowerConv   = <value>, upperConv   = <value>,\n\
 lowerFrac   = <value>, upperFrac   = <value>,\n\
 lowerTemp   = <value>, upperTemp   = <value>,\n\
 lowerPres   = <value>, upperPres   = <value>,\n\
 lowerPresC1 = <value>, upperPresC1 = <value>,\n\
 lowerPresC2 = <value>, upperPresC2 = <value>,\n\
 lowerPresC3 = <value>, upperPresC3 = <value>",
NULL, PlantInit, PlantEval, PlantTerm
},
*/
{
"sphere",
"\nSphere model :\n\
\t\tDiscretized version: sum (floor x_i)\n\
\t\tDiscretized version: sum (floor x_i) + 0.5\n\
\t\tmixed integer version: sum x_i^2 + sum d_i^2\n\
\t\tContinuous version: sum x_i^2\n\
\t\tscaled version: sum x_i^2 * i^2\n\
\t\tScaled version: sum x_i^2 * 2^(n-i)\n\
\t\tmixed Scaled: sum x_i^2 * i^2 + sum d_i^2 * i^2\n\
\t\tMixed Scaled: sum (x_i - d_i)^2 + (d_i - i)^2",
"control = <discrete|half|integermixed|continous|scaled|Scaled|mixedScaled|MixedScaled>",
NULL, SphereInit, SphereEval, SphereTerm
},

{
"reflection",
"Objective function reflection, optical problems.\n\
(Horst Greiner, Philips Aachen)",
"lowerWave = <value>, upperWave = <value>, waveSteps = <value>,\n\
inIndex = <value>, subIndex = <value>",
NULL,
reflectionInit,
reflection,
reflectionTerm
},

{
"reflection1",
"See the problem formulated by S. Martin, A. Brunet-Bruneau and J. Rivory,\n\
Darwinian evolution of homogeneous multilayer systems:\n\
a new method for optical coatings design to apper in\n\
'The proceedings of the international symposium on optical\n\
interference coatings, Grenoble, 6 - 10 June 1994'",
"lowerWave = <value>, upperWave = <value>, waveSteps = <value>,\n\
inIndex = <value>, subIndex = <value>",
NULL,
reflectionInit1,
reflection1,
reflectionTerm1
},

{
"reflection2",
"Objective function reflection2, an optical problem refering to a privat\n\
correspondence with H.Greiner. The problem is called 'hot mirror'",
"lowerWave = <value>, upperWave = <value>, waveSteps = <value>,\n\
border = <value>, inIndex = <value>, subIndex = <value>",
NULL,
reflectionInit2,
reflection2,
reflectionTerm2
},

{
"reflection3",
"Objective function reflection3, an optical problem taken\n\
form a design contest. The problem is called 'hot mirror'",
"lowerWave1 = <value>, upperWave1 = <value>,\n\
lowerWave2 = <value>, upperWave2 = <value>,\n\
waveSteps1 = <value>, waveSteps2 = <value>,\n\
inIndex = <value>, subIndex = <value>",
NULL,
reflectionInit3,
reflection3,
reflectionTerm3
},

{
"reflection4",
"objective function reflection4\n\
see: Robust Optical Coating with ES, Horst Greiner.",
"lowerWave = <value>, upperWave = <value>, waveSteps = <value>,\n\
inIndex = <value>, subIndex = <value>",
NULL,
reflectionInit4,
reflection4,
reflectionTerm4
},
/*
{
"routing",
"Siemens Routing-Problem",
"waysplits = <value>",
NULL,
routingInit,
routing,
routingTerm
},
*/
{
"mscp",
"Implementation of the non unicost set covering problem (binary representation).",
"inputfile = <name>, function = 1|2|3, repair = <value>",
NULL,
mscpInit,
mscp,
mscpTerm
},

{
"mscp2",
"Implementation of the non unicost set covering problem (integer representation).",
"inputfile = <name>, function = 1|2|3, repair = <value>",
NULL,
mscp2Init,
mscp2,
mscp2Term
},

{
"bpp",
"Implementation of the decreasing first-fit\n\
greedy heuristic for the bin packing problem",
"inputfile = <name>",
NULL,
bppInit,
bpp,
bppTerm
}

};

#define FCT_DEVICES     (sizeof(FCTtable)/sizeof(FCTdevice))


/* currently active function */
static FCTdevice *FCT	  = &FCTtable[0];
static int	 FCTdevno = 0;


/* create a new FCT device/object */
/*FCTdevice *newFCT(char *id,...)*/
FCTdevice *newFCT(char *id, char *parms, population_tPtr pop)

{
/*	va_list args;
	char	*parms;*/
	int	i;


/*	VA_START(args, id);
	parms = va_arg(args, char *);
	va_end(args);
*/
	for (i = 0; i < FCT_DEVICES; i++) {
		if (!strcmp(FCTtable[i].id, id)) {
			FCT = (FCTdevice *) &FCTtable[i];
			FCTdevno = i;
			if (FCT->parms != NULL)
				free(FCT->parms);
			if(parms != NULL)
				if(NULL == (FCT->parms = strdup(parms)))
					panic(A_WARN, "newFCT",
					      "not enough memory : %s : %d",
					      __FILE__, __LINE__);


			if(FALSE == InitFCT(FCT->parms, pop)) {
				free(FCT->parms);
				FCT->parms= NULL;
			}
			break;
		}
	}
	
	if (i == FCT_DEVICES && FCTdevno != i)
		panic(A_FATAL, "newFCT", "No such FCT device '%s',\
stick with `%s' : '%s' : %d",id ,thisFCT()->id, __FILE__, __LINE__);

        return ((FCTdevice *) FCT);
}



FCTdevice *thisFCT(void)
{
	return ((FCTdevice *) FCT);
}


/* delete FCT device/object */
void deleteFCT(param_tPtr eps	/* parameter structure */)
{
	int             i;

	for (i = 0; i < FCT_DEVICES; i++)
		if (FCTtable[i].parms != NULL) {
			free(FCTtable[i].parms);
			FCTtable[i].parms = NULL;
		}

	(*FCT->term)(eps);
/* Termination of the current function device; perhaps freeing local memory. */
}


/* test */
void testFCT(void)

{
	fprintf(stderr,"\nTest not yet implemented\n");
}

/* return actual tablesize */
int tableSizeFCT(void)
{
        return(FCT_DEVICES);
}

/* list all available FCT devices */
void listFCT(void)
{
	int             i;

	fprintf(stderr, "total %d object functions\n", FCT_DEVICES);
	for (i = 0; i < FCT_DEVICES; i++) {
		fprintf(stderr, "%-8s %s\n", FCTtable[i].id, FCTtable[i].note);
		fprintf(stderr, "usage: %s\n\n", FCTtable[i].usage);
	}
}


/* return the id string of currently used FCT device */
char *activeFCT(void)

{
	return (FCT->id);
}



/* Initialization of the current function device; parameter parsing. */
bool InitFCT(char *parms, population_tPtr pop)

{
	return((*FCT->init)(parms, pop));
}



/* Realization of an function evaluation. */
double EvalFCT(vector_tPtr x, Ivector_tPtr d)

{
	return((*FCT->eval)(x,d));
}
