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
 *	file:	reflection1.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	See the problem formulated by
 *		S. Martin, A. Brunet-Bruneau and J. Rivory,
 *		Darwinian evolution of homogeneous multilayer systems:
 *		a new method for optical coatings design",
 *		to apper in
 *		"The proceedings of the international symposium on optical
 *		 interference coatings, Grenoble, 6 - 10 June 1994".
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
 * 
 */

#include "fct.h"
#include "getparm.h"
#include "util.h"

static	unsigned long	m = 26;		/* number of wavelengths. */
static	double		XAir = 1.0,	/* refractory index of incident medium.
					   Default medium is air */
			XSub = 1.5,	/* refractory index of substrate.
					   Default medium is glass.*/
			lower = 0.5,	/* Lower wavel. of the band of interest. */
			upper = 1.0,    /* Upper wavel. of the band of interest. */
			stepsize = 20.0;

static char	SpectralProfil[BUFSIZ];
static FILE	*spectralprofil;
static bool	SpectralFlag = FALSE;

static double	CauchyInd[3][5] =
	{ { 1.378,   1.606,   2.255,    1.448,   2.0 },
	  { 1.77e-3, 5.5e-3,  3.572e-2,	3.28e-3, 1.0e-2 },
	  { 9.38e-6, 6.56e-6, 1.14e-3,  3.0e-5,  5.17e-4}
	};
/* Indizes for calculating the refactory indices in
   the 'second' problem incarnation. */

static double RefInd[5];
/* Average reflectory indices of the five
   materials of the second problem incarnation.
   MgF_2, AL_2O_3, ZnS, SiO_2, Si_3N4. */
   


/*
 * reflectionInit1 -- convert parms to function local data.
 */

static struct option reflectionOpts1[] =
{
	{"lowerWave", GP_VALSEP, 'l'},
	{"upperWave", GP_VALSEP, 'u'},
        {"waveSteps", GP_VALSEP, 'w'},
        {"inIndex"  , GP_VALSEP, 'i'},
        {"subIndex" , GP_VALSEP, 's'},
        {0,	    0,		0}
};


bool reflectionInit1(char *parms, population_tPtr pop)

{
	char	optarg[BUFSIZ];
	int	c, i, j;
	double  lambda = 0.5;
	static bool first = FALSE;
		

	if(first == FALSE) {
	  first = TRUE;
	  if(parms != NULL) {
		while((c = getparm(parms, reflectionOpts1, optarg)) != EOF) {
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
			panic(A_WARN, "reflectionInit",
				  "failed to parse : %s : %d",
				  __FILE__, __LINE__);
			return(FALSE);
		  }
		}
	  }
	  
	  stepsize = 1000.0 * (upper - lower) / (double)(m - 1);
	  
	  /* Averaging of the refractory indizes */
	  for(i = 0; i < 5; i++) {
	    RefInd[i] = 0.0;
	    for(j = 1; j <= m; j++) {
		  lambda = lower * 1000.0 + stepsize * (double)(j-1);
		  RefInd[i] += ( CauchyInd[0][i] +
						 (CauchyInd[1][i] / (lambda * lambda)) +
						 (CauchyInd[2][i] / (lambda * lambda *
											 lambda * lambda)));
	    }
	    RefInd[i] = RefInd[i] / (double) m;
	  }

	  return(TRUE);
	}
	
	return(TRUE);
}



double reflection1(vector_tPtr x, Ivector_tPtr d)

{
    	unsigned long	i, j, k;
    	double 		ConsI, Refl, Wale, Delta,
			XMerit = 0.0,
			Y11, Y12, Y21, Y22, X11, X12, X21, X22, 
			Z11, Z12, Z21, Z22, QQ1, QQ2, AA,
			scaling = 0.0;


	if((k = veGetVectorLength(x)) != veGetIVectorLength(d))
	panic(A_FATAL, "reflection1",
		  "dimension mismatching : %s : %d", __FILE__, __LINE__);

	/* Scaling of the filter to an total optical thickness of 2000nm. */
        scaling = 0.0;
        for (i = 1; i <= k; i++)
            scaling += (veGetVectorComponent(i, x) *
                        RefInd[veGetIVectorComponent(i, d)]);
        scaling = 2000.0 / scaling;

	ConsI = XAir * XSub * 4.0;
	for (i = 1; i <= m; i++) {

	    Wale  = lower * 1000.0 + stepsize * ((double) i-1);

/*	    Delta = 2.0 * PI * veGetVectorComponent(1, x) *
		    RefInd[veGetIVectorComponent(1, d)] / Wale; */
	    Delta = 2.0 * PI * veGetVectorComponent(1, x) *
		    scaling *
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
/*		Delta = 2.0 * PI * veGetVectorComponent(j, x) *
			RefInd[veGetIVectorComponent(j, d)] / Wale;*/
		Delta = 2.0 * PI * veGetVectorComponent(j, x) *
			scaling *
			RefInd[veGetIVectorComponent(j, d)] / Wale;
		/* Only change in phenotype */
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

	    } /* end calculation of M(lambda_i)	*/

	    QQ1	   = XAir * Y11 + XSub * Y22;
	    QQ2	   = XAir * XSub * Y12 + Y21;
	    Refl   = 1.0 - ConsI / (QQ1 * QQ1 + QQ2 * QQ2);
	    if(SpectralFlag)
		fprintf(spectralprofil, "%.10e\t\t%.10e\n", Wale/1000.0, Refl);
	    XMerit = XMerit + Refl * Refl;
	}

	return(-1.0/ XMerit);
}



bool reflectionTerm1(param_tPtr eps)

{
	unsigned long   i = 1, layers = 1, k = 1;
	double          thickness = 0.0, accuThickness = 0.0;
	char		Final[BUFSIZ],
			LayerProfil[BUFSIZ];
	FILE		*final,
			*layerprofil;
	double		scaling = 0.0;
#ifndef PVM
	int		getpid(void);
#endif

	if((k = inGetXLength(eps->BstInd)) != inGetDLength(eps->BstInd))
	panic(A_FATAL, "reflectionTerm1",
		  "dimension mismatching : %s : %d", __FILE__, __LINE__);

	/* Scaling of the filter to an total optical thickness of 2000nm. */
        for (i = 1; i <= k; i++)
            scaling += (inGetXComponent(i, eps->BstInd) *
                        RefInd[inGetDComponent(i, eps->BstInd)]);
        scaling = 2000.0 / scaling;

	for (i = 1; i <= k; i++)
  	    inAssignXComponent(i, inGetXComponent(i, eps->BstInd) * scaling,
			       eps->BstInd);

#ifndef PVM
	sprintf(Final,	       "%s%s%d.%s%ld", eps->Suffix, PTHSEP, getpid(),
		"FinalReflection_", eps->TotExp);
	sprintf(LayerProfil,   "%s%s%d.%s%ld", eps->Suffix, PTHSEP, getpid(),
		"LayerProfil_", eps->TotExp);
	sprintf(SpectralProfil,"%s%s%d.%s%ld", eps->Suffix, PTHSEP,getpid(),
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
		reflection1(inGetX(eps->BstInd), inGetD(eps->BstInd)));
	

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
