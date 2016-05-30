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
 *	file:	reflection4.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	objective function reflection4
 *		see: Robust Optical Coating with ES, Horst Greiner
 *	
 *   purpose:
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * 
 */

#include "fct.h"
#include "getparm.h"
#include "util.h"

static	unsigned long	m = 81;		/* number of wavelengths. */
static	double		XAir = 1.0,	/* refractory index of incident medium.
					   Default medium is air */
			XSub = 1.52,	/* refractory index of substrate.
					   Default medium is germaium.
					   Glass has a refractory index 1.5.*/
			lower = 3.8,	/* Lower wavel. of the band of interest. */
			upper = 7.8,   /* Upper wavel. of the band of interest. */
			stepsize = 50.0;

static double	RefInd[3] = {1.38, 1.63, 2.12}; /* Refractive indices */
   
static char	SpectralProfil[BUFSIZ];
static FILE	*spectralprofil;
static bool	SpectralFlag = FALSE;

/*
 * reflectionInit4 -- convert parms to function local data.
 */

static struct option reflection4Opts[] =
{
	{"lowerWave", GP_VALSEP, 'l'},
	{"upperWave", GP_VALSEP, 'u'},
        {"waveSteps", GP_VALSEP, 'w'},
        {"inIndex"  , GP_VALSEP, 'i'},
        {"subIndex" , GP_VALSEP, 's'},
        {0,	    0,		0}
};


bool reflectionInit4(char *parms, population_tPtr pop)

{
	char	optarg[BUFSIZ];
	int	c;
	static bool first = FALSE;
		

	if(first == FALSE) {
	  first = TRUE;		
	  if(NULL == parms) {
#ifdef DEBUG
		panic(A_WARN, "reflectionInit4",
		      "no parameters given : %s : %d",  __FILE__, __LINE__);
#endif
		return(TRUE);	/* take default parameterization */
	  }
	  
	  while((c = getparm(parms, reflection4Opts, optarg)) != EOF) {
		switch (c) {
		case 'l':
		  lower = (double) atof(optarg);
		  break;
		case 'u':
		  upper = (double) atof(optarg);
		  break;
		case 'w':
		  m = (unsigned long) atoi(optarg);
		  break;
		case 'i':
		  XAir = (double) atof(optarg);
		  break;
		case 's':
		  XSub = (double) atof(optarg);
		  break;
		default:
		  panic(A_WARN, "reflectionInit4",
				"failed to parse : %s : %d",
				__FILE__, __LINE__);
		  return(FALSE);
		}
	  }
	  
	  stepsize = 1000.0 * (upper - lower) / (double)(m - 1);
	  
	  return(TRUE);
	}
	return(TRUE);
}



double reflection4(vector_tPtr x, Ivector_tPtr d)

{
    	unsigned long	i, j, k;
    	double 		ConsI, Refl, Wale, Delta,
			XMerit = 0.0,
			Y11, Y12, Y21, Y22, X11, X12, X21, X22, 
			Z11, Z12, Z21, Z22, QQ1, QQ2, AA;


	if((k = veGetVectorLength(x)) != veGetIVectorLength(d))
		panic(A_FATAL, "reflection4",
		      "dimension mismatching : %s : %d", __FILE__, __LINE__);

	ConsI = XAir * XSub * 4.0;
	for (i = 1; i <= m; i++) {
	    Wale  = lower * 1000.0 + stepsize * ((double) i-1);

	    Delta = 2.0 * PI * veGetVectorComponent(1, x) *
		    RefInd[veGetIVectorComponent(1, d)] / Wale;
#ifdef SUN
	    /* Nonstandard solution: needs 14 % less time! */
	    sincos(Delta, &AA, &Y11); 
	    Y22 = Y11;
#else
	    /*  POSIX solution */
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
		/* Minus results from the complex calculation */
		Y11 = Z11;
		Y12 = Z12;
		Y21 = Z21;
		Y22 = Z22;
	    }/* end calculation of M(lambda_i)	*/

	    QQ1	 = XAir * Y11 + XSub * Y22;
	    QQ2	 = XAir * XSub * Y12 + Y21;
	    Refl = 1.0 - ConsI / (QQ1 * QQ1 + QQ2 * QQ2);

	    if(SpectralFlag)
		fprintf(spectralprofil, "%.10e\t\t%.10e\n", Wale/1000.0, Refl);
	    XMerit = XMerit + Refl * Refl;
	}

	return(100.0 * sqrt(XMerit / (double) m));
}



bool reflectionTerm4(param_tPtr eps)

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
		"FinalReflection_", eps->TotExp);
	sprintf(LayerProfil,	"%s%s%d.%s%ld", eps->Suffix, PTHSEP, getpid(),
		"LayerProfil_", eps->TotExp);
	sprintf(SpectralProfil,	"%s%s%d.%s%ld", eps->Suffix, PTHSEP, getpid(),
		"SpectralProfil_", eps->TotExp);
#else
 	sprintf(Final,		"%s%s%d.%s%ld", eps->Suffix, PTHSEP,
		eps->inst, "FinalReflection_", eps->TotExp);
	sprintf(LayerProfil,	"%s%s%d.%s%ld", eps->Suffix, PTHSEP,
		eps->inst, "LayerProfil_", eps->TotExp);
	sprintf(SpectralProfil,	"%s%s%d.%s%ld", eps->Suffix, PTHSEP,
		eps->inst, "SpectralProfil_", eps->TotExp);
#endif

	SpectralFlag = TRUE;

	if((final = fopen(Final, "w")) == NULL)
	    panic(A_FATAL, "reflectionTerm4",
		  "Couldn't open logfile (%s) : %s : %d",
		  Final, __FILE__, __LINE__);
	if((layerprofil = fopen(LayerProfil, "w")) == NULL)
	    panic(A_FATAL, "reflectionTerm4",
		  "Couldn't open logfile (%s) : %s : %d",
		  LayerProfil, __FILE__, __LINE__);
	if((spectralprofil = fopen(SpectralProfil, "w")) == NULL)
	    panic(A_FATAL, "reflectionTerm4",
		  "Couldn't open logfile (%s) : %s : %d",
		  Final, __FILE__, __LINE__);

	fprintf(spectralprofil, "\n\n# Merit = %g",
		reflection4(inGetX(eps->BstInd), inGetD(eps->BstInd)));
	

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
