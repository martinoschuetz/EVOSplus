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
 *	file:	params.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	19.09.1995
 *
 *   purpose:	Definition of parameter structure.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:57:20  schuetz
 * pvm integrated
 *
 * 
 */

#include "define.h"
#include "getparam.h"	

/****************************************************************************/
/* Definition of the input parameters, used by getparam.c		    */
/****************************************************************************/

param_ascii_t Param[] = {

/* Global parameters (Base Window)*/
{
	"totexp",
	"Total number of experiments",
	INT,
	">0",
	"1",
	OPTIONAL,
	offsetof(param_t, TotExp)
},
{
	"tottrl",
	"Total number of trials. Inactive if set to zero.",
	INT,
	">0",
	"1000",
	OPTIONAL,
	offsetof(param_t, TotTrl)
},
{
	"maxtime",
	"Maximal cpu-time. Inactive if set to zero.",
	INT,
	">=0",
	"0",
	OPTIONAL,
	offsetof(param_t, MaxTime)
},
{
	"x-dim",
	"Dimension real variable",
	INT,
	">-1",
	"15",
	OPTIONAL,
	offsetof(param_t, XDim)
},
{
	"d-dim",
	"Dimension integer variable",
	INT,
	">-1",
	"0",
	OPTIONAL,
	offsetof(param_t, DDim)
},
{
	"sigma-dim",
	"Dimension standarddeviations",
	INT,
	">-1",
	"1",
	OPTIONAL,
	offsetof(param_t, SigDim)
},
{
	"p-dim",
	"Dimension mutations rates",
	INT,
	">-1",
	"0",
	OPTIONAL,
	offsetof(param_t, PDim)
},
{
	"g-interval",
	"Graphics update interval",
	INT,
	">-1",
	"0",
	OPTIONAL,
	offsetof(param_t, GfxIvl)
},
{
	"scaling",
	"logarithmic scaling of graphical output",
	ENUM,
	"no|yes",
	"yes",
	OPTIONAL,
	offsetof(param_t, ScaFlg)
},
{
	"d-interval",
	"Data collection interval",
	INT,
	">-1",
	"10",
	OPTIONAL,
	offsetof(param_t, DtaIvl)
},
{
	"sel-scheme",
	"Selection scheme",
	ENUM,
	"comma|plus",
	"comma",
	OPTIONAL,
	offsetof(param_t, SelectionScheme)
},
{
	"seed",
	"Original seed for RNG",
	DOUBLE,
	"0..1",
	"",
	OPTIONAL,
	offsetof(param_t, OrgSed)
},
{
	"mu",
	"Number of parents",
	INT,
	">0",
	"15",
	OPTIONAL,
	offsetof(param_t, MueVal)
},
{
	"lambda",
	"Number of offspring",
	INT,
	">0",
	"100",
	OPTIONAL,
	offsetof(param_t, LdaVal)
},
{
	"fct-name",
	"Function name",
	STRING,
	"[A-Za-z0-9=]*",
	"sphere control = continous",
	OPTIONAL,
	offsetof(param_t, FctNme)
},
{
	"rst-name",
	"Restriction name",
	STRING,
	"[A-Za-z0-9=]*",
	"null no parameters",
	OPTIONAL,
	offsetof(param_t, RstNme)
},
{
	"rng-name",
	"RNG name",
	STRING,
	"[A-Za-z0-9=]*",
	"knuth",
	OPTIONAL,
	offsetof(param_t, RngNme)
},
{
	"suffix",
	"Output directory suffix",
	STRING,
	"[A-Za-z0-9]*",
	"",
	OPTIONAL,
	offsetof(param_t, Suffix)
},
{
	"format-string",
	"Format string for output",
	STRING,
	"[A-Za-z0-9]*",
	"",
	OPTIONAL,
	offsetof(param_t, FmtStr)
},
#ifdef PVM

/* Parallelization options (Extra window entitled 'Parallelization'). */
{ "parallel",     "Parallelization", LABEL},

{
	"tasks",
	"Number of evolution strategies for the migration modell",
	INT,
	">0",
	"1",
	OPTIONAL,
	offsetof(param_t, Tasks)
},

{
	"tasksfactor",
	"Number of rows with tasks",
	INT,
	">0",
	"1",
	OPTIONAL,
	offsetof(param_t, TasksFactor)
},

{
	"isolationtime",
	"Number of generations for which the isolation holds",
	INT,
	">0",
	"10",
	OPTIONAL,
	offsetof(param_t, IsolationTime)
},

{
	"migrationtype",
	"migration type",
	ENUM,
	"best|worst|random|position|median",
	"best",
	OPTIONAL,
	offsetof(param_t, MigrationType)
},

{
	"noofmigrants",
	"Number of migrants",
	INT,
	">0",
	"1",
	OPTIONAL,
	offsetof(param_t, NoOfMigrants)
},

{
	"topology",
	"type of migration topology",
	ENUM,
	"uniring|biring|grid|moore|helix|torus|hypercubus",
	"biring",
	OPTIONAL,
	offsetof(param_t, Topology)
},

{
	"neighbourhoodsize",
	"Number of neighbours in one direction",
	INT,
	">0",
	"1",
	OPTIONAL,
	offsetof(param_t, NoOfNeighbours)
},

{
	"communication",
	"type of inteprocess communication",
	ENUM,
	"synchron|asynchron",
	"asynchron",
	OPTIONAL,
	offsetof(param_t, Topology)
},
#endif

/* Ranges for the several genes (Extra window entitled 'Parameter Ranges'). */
{ "ranges",     "Parameter Ranges", LABEL},

{
	"lower-x",
	"Lower init bound x",
	DOUBLE,
	"-1.797693e+308..1.797693e+308",
	"-32767",
	OPTIONAL,
	offsetof(param_t, lx)
},
{
	"upper-x",
	"Upper init bound x",
	DOUBLE,
	"-1.797693e+308..1.797693e+308",
	"32767",
	OPTIONAL,
	offsetof(param_t, ux)
},
{
	"lower-d",
	"Lower init bound d",
	INT,
	"-2147483647..2147483647",
	"-32767",
	OPTIONAL,
	offsetof(param_t, ld)
},
{
	"upper-d",
	"Upper init bound d",
	INT,
	"-2147483647..2147483647",
	"32767",
	OPTIONAL,
	offsetof(param_t, ud)
},
{
	"lower-sigma",
	"Lower init bound sigma",
	DOUBLE,
	">0",
	"1.4013e-45",
	OPTIONAL,
	offsetof(param_t, lsigma)
},
{
	"upper-sigma",
	"Upper init bound sigma",
	DOUBLE,
	">0",
	"32767",
	OPTIONAL,
	offsetof(param_t, usigma)
},
{
	"lower-alpha",
	"Lower init bound alpha",
	DOUBLE,
	"-3.141593..3.141593",
	"-3.141593",
	OPTIONAL,
	offsetof(param_t, lalpha)
},
{
	"upper-alpha",
	"Upper init bound alpha",
	DOUBLE,
	"-3.141593..3.141593",
	"3.141593",
	OPTIONAL,
	offsetof(param_t, ualpha)
},
{
	"lower-p",
	"Lower init bound p",
	DOUBLE,
	"0..1",
	"0",
	OPTIONAL,
	offsetof(param_t, lp)
},
{
	"upper-p",
	"Upper init bound p",
	DOUBLE,
	"0..1",
	"1",
	OPTIONAL,
	offsetof(param_t, up)
},

/* External parameters (Extra window entitled 'External Parameters'). */
{ "external",   "External Parameters", LABEL},

{
	"tau-global",
	"Global learning sigmas",
	DOUBLE,
	">0",
	"",
	OPTIONAL,
	offsetof(param_t, TauGlb)
},
{
	"tau-local",
	"Local learning sigmas",
	DOUBLE,	">0",
	"",
	OPTIONAL,
	offsetof(param_t, TauLcl)
},
{	"tau-one",
	"Learning parameter one sigma",
	DOUBLE,
	">0",
	"",
	OPTIONAL,
	offsetof(param_t, TauOne)
},
{
	"beta",
	"Correlation parameter",
	DOUBLE,
	">0",
	"0.0872664639",
	OPTIONAL,
	offsetof(param_t, Beta)
},
{
	"gamma-global",
	"Global learning p",
	DOUBLE,
	">0",
	"",
	OPTIONAL,
	offsetof(param_t, GamGlb)
},
{
	"gamma-local",
	"Local learning p",
	DOUBLE,
	">0",
	"",
	OPTIONAL,
	offsetof(param_t, GamLcl)
},
{
	"gamma-one",
	"Learning parameter one p",
	DOUBLE,
	">0",
	"",
	OPTIONAL,
	offsetof(param_t, GamOne)
},
{
	"alpha",
	"Learning p (Rechenberg)",
	DOUBLE,
	">0",
	"1.5",
	OPTIONAL,
	offsetof(param_t, Alpha)
},
{
	"w",
	"Variable dimension (Kursawe)",
	DOUBLE,
	"0..1",
	"0.05",
	OPTIONAL,
	offsetof(param_t, W)
},
{
	"sigma-start",
	"Start stepsizes sigmas",
	DOUBLE,
	">0",
	"1.0",
	OPTIONAL,
	offsetof(param_t, SigStart)
},
{	"p-start",
	"Start mutationrates p",
	DOUBLE,
	"0..1",
	"0.0",
	OPTIONAL,
	offsetof(param_t, PStart)
},
{
	"l",
	"Variable dimension (Binomial)",
	INT,
	">0",
	"3",
	OPTIONAL,
	offsetof(param_t, L)
},

/* Several initialization schemes. */

{ "initialization", "Initialization", LABEL},

{
	"init-filename",
	"File name for initialization file",
	STRING,
	"[A-Za-z0-9]*",
	"",
	OPTIONAL,
	offsetof(param_t, InzFil)
},
{
	"init-type",
	"Type of initialization",
	ENUM,
	"point|standard|application",
	"standard",
	OPTIONAL,
	offsetof(param_t, InitMode)
},

/* Recombination schemes for the several genes
   (Extra window entitled 'Recombination'). */
{ "recombination","Recombination", LABEL},

{
	"x-reco",
	"x gen recombination",
	ENUM,
	"no|local-discrete|global-discrete|local-intermediate|global-intermediate|local-random-intermediate|global-random-intermediate",
	"no",
	OPTIONAL,
	offsetof(param_t, xReco)
},
{
	"d-reco",
	"d gen recombination",
	ENUM,
	"no|local-discrete|global-discrete",
	"no",
	OPTIONAL,
	offsetof(param_t, dReco)
},
{
	"sigma-reco",
	"sigma gen recombination",
	ENUM,
	"no|local-discrete|global-discrete|local-intermediate|global-intermediate|local-random-intermediate|global-random-intermediate|local-geometric|global-geometric",
	"no",
	OPTIONAL,
	offsetof(param_t, sigmaReco)
},
{
	"alpha-reco",
	"alpha gen recombination",
	ENUM,
	"no|local-discrete|global-discrete|local-intermediate|global-intermediate|local-random-intermediate|global-random-intermediate",
	"no",
	OPTIONAL,
	offsetof(param_t, alphaReco)
},
{
	"p-reco",
	"p gen recombination",
	ENUM,
	"no|local-discrete|global-discrete|local-intermediate|global-intermediate|local-random-intermediate|global-random-intermediate|local-geometric|global-geometric",
	"no",
	OPTIONAL,
	offsetof(param_t, pReco)
},
{
	"ind-reco",
	"variable recombination",
	ENUM,
	"local-discrete|global-discrete",
	"global-discrete",
	OPTIONAL,
	offsetof(param_t, indReco)
},


/* Adaptation schemes for the several genes
   (Extra window entitled 'Adaptation'). */
{ "adaptation", "Adaptation", LABEL},

{
	"x-adapt",
	"x gen adaptation",
	ENUM,
	"no|binomial|one-third|kursawe",
	"no",
	OPTIONAL,
	offsetof(param_t, xAdapt)
},
{
	"d-adapt",
	"d gen adaptation",
	ENUM,
	"no|binomial|one-third|kursawe",
	"no",
	OPTIONAL,
	offsetof(param_t, dAdapt)
},
{
	"sigma-adapt",
	"sigma gen adaptation",
	ENUM,
	"no|binomial|one-third|kursawe",
	"no",
	OPTIONAL,
	offsetof(param_t, sigmaAdapt)
},
{
	"alpha-adapt",
	"alpha gen adaptation",
	ENUM,
	"no|binomial|one-third|kursawe",
	"no",
	OPTIONAL,
	offsetof(param_t, alphaAdapt)
},
{
	"p-adapt",
	"p gen adaptation",
	ENUM,
	"no|binomial|one-third|kursawe",
	"no",
	OPTIONAL,
	offsetof(param_t, pAdapt)
},

/* Mutation schemes for the several genes
   (Extra window entitled 'Mutation'). */
{ "mutation",	"Mutation", LABEL},

{
	"x-mute",
	"x gen mutation",
	ENUM,
	"no|additiv|correlated|plant|naca",
	"additiv",
	OPTIONAL,
	offsetof(param_t, xMute)
},
{
	"d-mute",
	"d gen mutation",
	ENUM,
	"no|uniform|binomial|scp",
	"no",
	OPTIONAL,
	offsetof(param_t, dMute)
},
{
	"sigma-mute",
	"sigma gen mutation",
	ENUM,
	"no|global-lognormal|local-lognormal|product",
	"global-lognormal",
	OPTIONAL,
	offsetof(param_t, sigmaMute)
},
{
	"alpha-mute",
	"alpha gen mutation",
	ENUM,
	"no|additiv",
	"no",
	OPTIONAL,
	offsetof(param_t, alphaMute)
},
{
	"p-mute",
	"p gen mutation",
	ENUM,
	"no|global-lognormal|local-lognormal|additiv|logistic|global-logistic|product|progress|triangle",
	"no",
	OPTIONAL,
	offsetof(param_t, pMute)
},
{
	"sigma-comp",
	"sigma completition",
	ENUM,
	"fix|random",
	"fix",
	OPTIONAL,
	offsetof(param_t, SigmaCompletition)
},
{
	"p-comp",
	"p completition",
	ENUM,
	"fix|random",
	"fix",
	OPTIONAL,
	offsetof(param_t, PCompletition)
},


/* Transformation schemes for the several genes
   (Extra window entitled 'Transformation'). */
{ "transformation","Transformation", LABEL},

{
	"x-transform",
	"x gen transformation",
	ENUM,
	"no|bounds",
	"no",
	OPTIONAL,
	offsetof(param_t, xTrans)
},
{
	"d-transform",
	"d gen transformation",
	ENUM,
	"no|bounds",
	"no",
	OPTIONAL,
	offsetof(param_t, dTrans)
},
{
	"sigma-transform",
	"sigma gen transformation",
	ENUM,
	"no|lower-bound",
	"lower-bound",
	OPTIONAL,
	offsetof(param_t, sigmaTrans)
},
{
	"alpha-transform",
	"alpha gen transformation",
	ENUM,
	"no|bijective|cyclic",
	"no",
	OPTIONAL,
	offsetof(param_t, alphaTrans)
},
{
	"p-transform",
	"p gen transformation",
	ENUM,
	"no|global-lognormal|local-lognormal|bijective|bounds",
	"no",
	OPTIONAL, offsetof(param_t, pTrans)
},
END_PARAMS
};
