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
 *	file:	reflection.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	Objective function reflection3, an optical problem
 *		of an design contest.
 *		The problem is called 'hot mirror'.
 *	
 *   purpose:
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:36:16  schuetz
 * pvm integrated
 *
 * Revision 1.1  1995/02/06  08:11:42  schuetz
 * Initial revision
 *
 */

#include "fct.h"
#include "getparm.h"
#include "util.h"

static	unsigned long	m1 = 320,	/* number of wavelengths, 1. section.*/
			m2 = 625,	/* number of wavelengths, 2. section.*/
    			k;		/* dimension of the filter. */
static	double		XAir = 1.0,	/* refractory index of incident medium.
					   Default medium is air */
			XSub = 1.47,	/* refractory index of substrate. */
			lower1 = 400.0,	/* Lower wavel. of the 1. section */
			upper1 = 719.0,	/* Upper wavel. of the 1. sectuib */
			lower2 = 750.0,	/* Lower wavel. of the 2. section */
			upper2 = 1998.0,/* Upper wavel. of the 2. section */
    			stepsize1 = 1.0,/* stepsize of the 1. section */
    			stepsize2 = 2.0,/* stepsize of the 2. section */
    			ConsI = 1.0 * 1.47 * 4.0;

static char	SpectralProfil[BUFSIZ];
static FILE	*spectralprofil;
static bool	SpectralFlag = FALSE;

static double	RefInd[4] = {1.46, 1.62, 2.05, 2.35};	
/* Refractive indices. Normally the materials and their indices are:
   silica :	eta = 1.46 - j 0
   alumina:	eta = 1.62 - j 0 
   tantala:	eta = 2.05 - j 0.0002
   titania:	eta = 2.35 - j 0.0005	*/
   

double _reflection3(vector_tPtr x, Ivector_tPtr d, double lower, double upper,
		    unsigned long m, double stepsize, bool refl);


/*
 * reflectionInit3 -- convert parms to function local data.
 */

static struct option reflectionOpts3[] =
{
	{"lowerWave1", GP_VALSEP, 'l'},
	{"upperWave1", GP_VALSEP, 'u'},
	{"lowerWave2", GP_VALSEP, 'L'},
	{"upperWave2", GP_VALSEP, 'U'},
        {"waveSteps1", GP_VALSEP, 'w'},
        {"waveSteps2", GP_VALSEP, 'W'},
	{"inIndex"   , GP_VALSEP, 'i'},
        {"subIndex"  , GP_VALSEP, 's'},
        {0,	    0,		0}
};


bool reflectionInit3(char *parms, population_tPtr pop)

{
	char	optarg[BUFSIZ];
	int	c;
	static bool first = FALSE;

	if(first == FALSE) {
	  first = TRUE;	
	  if(NULL == parms) {
#ifdef DEBUG
		panic(A_WARN, "reflectionInit3",
		      "no parameters given : %s : %d",  __FILE__, __LINE__);
#endif
		return(TRUE);	/* take default parameterization */
	  }

	  while((c = getparm(parms, reflectionOpts3, optarg)) != EOF) {
		switch (c) {
		case 'l':
		  lower1 = 1000.0 * (double) atof(optarg);
		  break;
		case 'L':
		  lower2 = 1000.0 * (double) atof(optarg);
		  break;
		case 'u':
		  upper1 = 1000.0 * (double) atof(optarg);
		  break;
		case 'U':
		  upper2 = 1000.0 * (double) atof(optarg);
		  break;
		case 'w':
		  m1 = (unsigned long) atoi(optarg);
		  break;
		case 'W':
		  m2 = (unsigned long) atoi(optarg);
		  break;
		case 'i':
		  XAir = (double) atof(optarg);
		  break;
		case 's':
		  XSub = (double) atof(optarg);
		  break;
		default:
		  panic(A_WARN, "reflectionInit",
				"failed to parse : %s : %d",
				__FILE__, __LINE__);
		  return(FALSE);
		}
	  }

	  stepsize1 = (upper1 - lower1) / (double)(m1 - 1);
	  stepsize2 = (upper2 - lower2) / (double)(m2 - 1);
	  ConsI = XAir * XSub * 4.0;

	  return(TRUE);
	}
	return(TRUE);
}


double reflection3(vector_tPtr x, Ivector_tPtr d)

{
  const double	c = 0.3678794412; /* c = 1/exp(1) */

  
  if((k = veGetVectorLength(x)) != veGetIVectorLength(d))
      panic(A_FATAL, "reflection3",
	    "dimension mismatching : %s : %d", __FILE__, __LINE__);

  return(200.0 - _reflection3(x, d, lower1, upper1, m1, stepsize1, FALSE) -
	         _reflection3(x, d, lower2, upper2, m2, stepsize2, TRUE ) +
	 (c * exp((double) k /50.0)));
	 /*  exp((L - 50)/50) = exp(1)^-1 * exp(L/50) */
}


double _reflection3(vector_tPtr x, Ivector_tPtr d, double lower, double upper,
		    unsigned long m, double stepsize, bool refl)

{
    	unsigned long	i, j;
	double		Refl, Wale, Delta, XMerit = 0.0,
			Y11, Y12, Y21, Y22, X11, X12, X21, X22, 
			Z11, Z12, Z21, Z22, QQ1, QQ2, AA;

	for (i = 1; i <= m; i++) {
	    Wale  = lower + stepsize * ((double) i-1);

	    Delta = 2.0 * PI * veGetVectorComponent(1, x) *
		    RefInd[veGetIVectorComponent(1, d)] / Wale;
#ifdef SUN
	    /* Nonstandard solution: needs 14 % less time! */
	    sincos(Delta, &AA, & Y11); 
	    Y22 = Y11;
#else
	    /* POSIX solution */
	    Y11 = Y22 = cos(Delta);
	    AA  = sin(Delta);
#endif
	    Y12   = AA / RefInd[veGetIVectorComponent(1, d)];
	    Y21   = AA * RefInd[veGetIVectorComponent(1, d)];
	    /* With this precalculation the multiplication with
	       the identity matrix can be omitted. */

	    for (j = 2; j <= k; j++) {
	        Delta = 2.0 * PI * veGetVectorComponent(j, x) *
			RefInd[veGetIVectorComponent(j, d)] / Wale;
#ifdef SUN
		/* Nonstandard solution: needs 14 % less time! */
		sincos(Delta, &AA, &X11);
		X22 = X11;
#else
		/* POSIX solution */
		X11 = X22 = cos(Delta);
		AA  = sin(Delta);
#endif

		X21 = AA * RefInd[veGetIVectorComponent(j, d)];
		X12 = AA / RefInd[veGetIVectorComponent(j, d)];

		Z11 = Y11 * X11 - Y12 * X21;
		Z12 = Y11 * X12 + Y12 * X22;
		Z21 = Y21 * X11 + Y22 * X21;
		Z22 = - Y21 * X12 + Y22 * X22;
		Y11 = Z11;
		Y12 = Z12;
		Y21 = Z21;
		Y22 = Z22;

	    }/* end calculation of M(lambda)	*/

	    QQ1	   = XAir * Y11 + XSub * Y22;
	    QQ2	   = XAir * XSub * Y12 + Y21;

	    if(refl)
		Refl = 1.0 - ConsI / (QQ1 * QQ1 + QQ2 * QQ2);
	    else
		Refl = ConsI / (QQ1 * QQ1 + QQ2 * QQ2);

	    if(SpectralFlag) {
		if(refl)
		    fprintf(spectralprofil, "%.10e\t\t%.10e\n",
			    Wale/1000.0, Refl);
		else
		    fprintf(spectralprofil, "%.10e\t\t%.10e\n",
			    Wale/1000.0, 1.0 - Refl);
		/* Output as Reflection. */
	    }

	    XMerit = XMerit + (Refl * stepsize);
	}

	if(SpectralFlag)
		fprintf(spectralprofil, "\n");

	return(100.0 * (XMerit/(upper - lower + stepsize)));
}



bool reflectionTerm3(param_tPtr eps)

{
	unsigned long   i = 1, layers = 1;
	double          thickness = 0.0, accuThickness = 0.0;
	char		Final[BUFSIZ],
			LayerProfil[BUFSIZ];
	FILE		*final,
			*layerprofil;
#ifndef PVM
	int		getpid(void);
			

	sprintf(Final,		"%s%s%d.%s%ld", eps->Suffix, PTHSEP, getpid(),
		"FinalTransmission_", eps->TotExp);
	sprintf(LayerProfil,	"%s%s%d.%s%ld", eps->Suffix, PTHSEP, getpid(),
		"LayerProfil_", eps->TotExp);
	sprintf(SpectralProfil, "%s%s%d.%s%ld", eps->Suffix, PTHSEP, getpid(),
		"SpectralProfil_", eps->TotExp);
#else
	sprintf(Final,          "%s%s%d.%s%ld", eps->Suffix, PTHSEP,
		eps->inst, "FinalReflection_", eps->TotExp);
	sprintf(LayerProfil,    "%s%s%d.%s%ld", eps->Suffix, PTHSEP,
		eps->inst, "LayerProfil_", eps->TotExp);
	sprintf(SpectralProfil, "%s%s%d.%s%ld", eps->Suffix, PTHSEP,
		eps->inst, "SpectralProfil_", eps->TotExp);
#endif

	SpectralFlag = TRUE;

	if((final = fopen(Final, "w")) == NULL)
	    panic(A_FATAL, "reflectionTerm",
		  "Couldn't open logfile (%s) : %s : %d",
		  Final, __FILE__, __LINE__);
	if((layerprofil = fopen(LayerProfil, "w")) == NULL)
	    panic(A_FATAL, "reflectionTerm",
		  "Couldn't open logfile (%s) : %s : %d",
		  LayerProfil, __FILE__, __LINE__);
	if((spectralprofil = fopen(SpectralProfil, "w")) == NULL)
	    panic(A_FATAL, "reflectionTerm",
		  "Couldn't open logfile (%s) : %s : %d",
		  Final, __FILE__, __LINE__);

	fprintf(spectralprofil, "\n\n# Merit = %g",
		reflection3(inGetX(eps->BstInd), inGetD(eps->BstInd)));
	

	fprintf(final, "Layer\tIndex\tGeometrical(nm)\t\tOptical(mikrom)\n");
	fprintf(final, "\n%ld\t%.4g\t",
		layers, RefInd[inGetDComponent(1, eps->BstInd)]);
	thickness = inGetXComponent(1, eps->BstInd);

	fprintf(layerprofil, "#thickness (mikrom)\tindex\n\n");
	fprintf(layerprofil, "%.10e\t%.4g\n", 0.0, 0.0);
	fprintf(layerprofil, "%.10e\t%.4g\n",
		0.0, RefInd[inGetDComponent(1, eps->BstInd)]);

	for(i = 1; i < inGetXLength(eps->BstInd); i++) {
		if(inGetDComponent(i,eps->BstInd) !=
		   inGetDComponent(i+1, eps->BstInd)) {
			fprintf(final, "%.10e\t%.10e\n",
				thickness,
				thickness /1000.0 *
				RefInd[inGetDComponent(i,eps->BstInd)]);
			accuThickness += thickness;
			fprintf(layerprofil, "%.10e\t%.4g\n",
				accuThickness/1000.0,
				RefInd[inGetDComponent(i+1, eps->BstInd)]);
			thickness = 0;
			layers++;
			fprintf(final, "%ld\t%.4g\t",
				layers,
				RefInd[inGetDComponent(i+1, eps->BstInd)]);
		}
		thickness += inGetXComponent(i+1,eps->BstInd);
	}

	fprintf(final, "%.10e\t%.10e\n\n",
		thickness,
		thickness /1000.0 *
		RefInd[inGetDComponent(i,eps->BstInd)]);

	accuThickness += thickness;
	fprintf(layerprofil, "%.10e\t%.4g\n",
		accuThickness/1000.0,
		RefInd[inGetDComponent(i, eps->BstInd)]);
	fprintf(layerprofil, "%.10e\t%.4g\n",
		accuThickness/1000.0, 0.0);

	fclose(final);
	fclose(layerprofil);
	fclose(spectralprofil);
	
	return(TRUE);
}

/** end of file **/
