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
 *	file:	type.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	25.02.1994
 *
 *   purpose:	Encapsulation of all EVOSplus-datatypes
 *
 *    remark:	
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:58:47  schuetz
 * pvm integrated
 *
 *
 *
 */

#ifndef _TYPES_H
#define	_TYPES_H

#define bool	int
#define TRUE	1
#define FALSE	0


/****************************************************************************/
/* Definition of the datatype 'Ivector'				            */
/****************************************************************************/

typedef struct Ivector {
			unsigned long	dim;
			long		*data;
} Ivector_t, *Ivector_tPtr;


/****************************************************************************/
/* Definition of the datatype 'vector'					    */
/****************************************************************************/

typedef struct vector {
			unsigned long	dim;
			double		*data;
} vector_t, *vector_tPtr;


/****************************************************************************/
/* Definition of the datatype 'Imatrix'					    */
/****************************************************************************/

typedef struct Imatrix {
			unsigned long	dimRows;
			unsigned long	dimCols;
			long		**data;
} Imatrix_t, *Imatrix_tPtr;


/****************************************************************************/
/* Definition of the datatype 'matrix'					    */
/****************************************************************************/

typedef struct matrix {
			unsigned long	dimRows;
			unsigned long	dimCols;
			double		**data;
} matrix_t, *matrix_tPtr;


/****************************************************************************/
/* Definition of the datatype 'individual'				    */
/****************************************************************************/

typedef struct individual {
				vector_tPtr	x;
				double		lx, ux;
				Ivector_tPtr	d;
				long		ld, ud;
				vector_tPtr	sigma;
				double		lsigma, usigma;
				vector_tPtr	alpha;
				double		lalpha, ualpha;
				vector_tPtr	p;
				double		lp, up;
				double		fx;
} individual_t,	*individual_tPtr;


/****************************************************************************/
/* Definition of the datatype 'population'				    */
/****************************************************************************/

typedef struct population {
				unsigned long	mu;
				unsigned long	lambda;
				individual_tPtr	*parents_offspring;
/*				individual_tPtr	*offspring;		*/
} population_t,	*population_tPtr;

/****************************************************************************/
/* Definition of the several initialization types			    */
/****************************************************************************/

typedef enum {
		point, /* Init by lying a cube around a read in inital point. */
		standard, /* Init in a cube defined by the parameter ranges. */
		application /* Function dependend initialization. */
} init_t;

/****************************************************************************/
/* Definition of the several recombination types			    */
/****************************************************************************/

typedef enum {
	X_NO_RECO,	/* no recombination */
	X_LDS_RECO,	/* local  discrete recombination */
	X_GDS_RECO,	/* global discrete recombination */
	X_LIM_RECO,	/* local  intermediate recomb. */
	X_GIM_RECO,	/* global intermediate recomb. */
	X_LRI_RECO,	/* local  random intermediate rec. */
	X_GRI_RECO,	/* global random intermediate rec. */
	X_THA_RECO		/* Thales recombination */
} x_reco_t;

typedef enum {
	D_NO_RECO,	/* no recombination */
	D_LDS_RECO,	/* local  discrete recombination */
	D_GDS_RECO	/* global discrete recombination */
} d_reco_t;

typedef enum {
	SIGMA_NO_RECO,	/* no recombination */
	SIGMA_LDS_RECO,	/* local  discrete recombination */
	SIGMA_GDS_RECO,	/* global discrete recombination */
	SIGMA_LIM_RECO,	/* local  intermediate recomb. */
	SIGMA_GIM_RECO,	/* global intermediate recomb. */
	SIGMA_LRI_RECO,	/* local  random intermediate rec. */
	SIGMA_GRI_RECO,	/* global random intermediate rec. */
	SIGMA_LGE_RECO,	/* local geometric rekombination */
	SIGMA_GGE_RECO,	/* global geometric rekombination */
	SIGMA_THA_RECO	/* Thales recombination */
} sigma_reco_t;

typedef enum {
	ALPHA_NO_RECO,	/* no recombination */
	ALPHA_LDS_RECO,	/* local  discrete recombination */
	ALPHA_GDS_RECO,	/* global discrete recombination */
	ALPHA_LIM_RECO,	/* local  intermediate recomb. */
	ALPHA_GIM_RECO,	/* global intermediate recomb. */
	ALPHA_LRI_RECO,	/* local  random intermediate rec. */
	ALPHA_GRI_RECO,	/* global random intermediate rec. */
	ALPHA_THA_RECO	/* Thales recombination */
} alpha_reco_t;

typedef enum {
	P_NO_RECO,	/* no recombination */
	P_LDS_RECO,	/* local  discrete recombination */
	P_GDS_RECO,	/* global discrete recombination */
	P_LIM_RECO,	/* local  intermediate recomb. */
	P_GIM_RECO,	/* global intermediate recomb. */
	P_LRI_RECO,	/* local  random intermediate rec. */
	P_GRI_RECO,	/* global random intermediate rec. */
	P_LGE_RECO,	/* local geometric rekombination */
	P_GGE_RECO,	/* global geometric rekombination */
	P_THA_RECO	/* Thales recombination */
} p_reco_t;

typedef enum {
	LOCDIS_LENGTH_RECO,	/* local discrete length-recombination,
				   only for the 6-th 'RecScm' position. */
	GLODIS_LENGTH_RECO	/* global discrete length-recombination,
				   only for the 6-th 'RecScm' position. */
} ind_reco_t;

/****************************************************************************/
/* Definition of the several adaptation types				    */
/****************************************************************************/

typedef enum {
	NO_ADAPT,	/* no adation needed */
	MY_ADAPT,	/* my (binomial) form of length adaption  */
	ONE_3_ADAPT,	/* 1/3 apaption form */
	KURSAWE_ADAPT	/* adaption after Kursawe */
} adapt_t;

/****************************************************************************/
/* Definition of the several mutation types				    */
/****************************************************************************/

typedef enum {
	X_NO_MUTE,	/* no mutation needed */
	X_ADD_NOR_MUTE,	/* additiv-normal mutation scheme */
	X_ADD_NOR_COR_MUTE, /* additiv-normal mut. for correlated mut. */
	X_PLANT_MUTE, /* special mutation operator for the HDA-problem. */
	X_NACA_MUTE /* special mutation operator for the NACA airfoil problem. */
} x_mute_t;

typedef enum {
	D_NO_MUTE,	/* no mutation needed */
	D_STD_D_MUTE,	/* standard mut. scheme d_i */
	D_BIN_D_MUTE,	/* binomial mut. scheme d_i */
	D_SCP_MUTE		/* special mutation operator for set covering */
} d_mute_t;

typedef enum {
	SIGMA_NO_MUTE,		/* no mutation needed */
	SIGMA_LOG_NOR_2_MUTE,	/* log-normal mut.,global and local factor */
	SIGMA_LOG_NOR_MUTE,	/* log-normal mut., only local factor */
	SIGMA_PRODUCT_MUTE	/* mut. scheme after Rechenberg */
} sigma_mute_t;

typedef enum {
	ALPHA_NO_MUTE,		/* no mutation needed */
	ALPHA_ADD_NOR_MUTE	/* additiv-normal mutation scheme */
} alpha_mute_t;

typedef enum {
	P_NO_MUTE,	/* no mutation needed */
	P_LOG_NOR_2_MUTE,/* log-normal mut.,global and local factor */
	P_LOG_NOR_MUTE,	/* log-normal mut., only local factor */
	P_ADD_NOR_MUTE,	/* additiv-normal mutation scheme */
	P_LOGISTIC_MUTE,/* logistic mutation scheme */
	P_LOGISTIC2_MUTE,/* logistic mutation scheme in [1/l,1/2[*/
	P_PRODUCT_MUTE,	/* mut. scheme after Rechenberg */
	P_PROGRESS_MUTE, /* Mutation rate control via progress velocity. */
	P_TRIANGLE_MUTE /* Mutation of mutation rates after Emmerich  */
} p_mute_t;

/****************************************************************************/
/* Definition of the several transformation types			    */
/****************************************************************************/

typedef enum {
	X_NO_TRANSFORM,		/* no transformation needed */
	X_BOUNDS_TRANSFORM	/* throw values back into its range [l,u] */
} x_transform_t;

typedef enum {
	D_NO_TRANSFORM,		/* no transformation needed */
	D_BOUNDS_TRANSFORM	/* throw values back into its range [l,u] */
} d_transform_t;

typedef enum {
	SIGMA_NO_TRANSFORM,	    /* no transformation needed */
	SIGMA_LOWER_BOUNDS_TRANSFORM/*throw values back into its range [l,00(*/
} sigma_transform_t;

typedef enum {
	ALPHA_NO_TRANSFORM,	/* no transformation needed */
	ALPHA_ADD_NOR_TRANSFORM,/* dto. */
	ALPHA_BOUNDS_TRANSFORM	/* throw values back into its range [l,u] */
} alpha_transform_t;

typedef enum {
	P_NO_TRANSFORM,		/* no transformation needed */
	P_LOG_NOR_2_TRANSFORM,	/* [0,1]-transf. for the corresp. mut. */
	P_LOG_NOR_TRANSFORM,	/* dto. */
	P_ADD_NOR_TRANSFORM,	/* dto. */
	P_BOUNDS_TRANSFORM	/* throw values back into its range [l,u] */
} p_transform_t;


/****************************************************************************/
/*   Definition of the parallel version of EVOS+, called PEVOS+		    */
/****************************************************************************/

typedef enum {
	MIGRATION_BEST,	/* Best 'NoOfMigrants' parents will migrate. */
	MIGRATION_WORST,/* Worst 'NoOfMigrants' parents will migrate. */
	MIGRATION_RANDOM,/* Random specified 'NoOfMigrants' par. will migrate.*/
	MIGRATION_POSITION, /* 'NoOfMigrants' parents counted from a
			      special position will migrate. */
	MIGRATION_MEDIAN /*'NoOfMigrants' parents around the median fitness
			    will migrate. */
} migration_t;
	
typedef enum {
	TOPOLOGY_UNIDIRECTIONAL_RING,
	TOPOLOGY_BIDIRECTIONAL_RING,
	TOPOLOGY_GRID,
	TOPOLOGY_MOORE,
	TOPOLOGY_HELIX,
	TOPOLOGY_TORUS,
	TOPOLOGY_HYPERCUBUS
} topology_t;

typedef enum {
	COMMUNICATION_SYNCHRON,
	COMMUNICATION_ASYNCHRON
} communication_t;

#define	MSGTAG_IND	0
#define MSGTAG_BEST	1
#define MSGTAG_END	2
	

/****************************************************************************/
/*		   Definition of the general parameter structure	    */
/****************************************************************************/

typedef struct {
  
  bool GfxFlg,	/* flag for online-visualization */
	   ScaFlg,  /* flag for logarithmic scaling */
	   QryFlg,	/* directory name query flag */
	   HlpFlg,	/* help flag */
	   InzFlg,	/* initial point file flag */
	   ObjFlg,	/* output flag real valued object variables */
	   DisFlg,	/* output flag integer valued obj. vars. */
	   SigFlg,	/* output flag st. deviations */
	   AlpFlg,	/* output flag correlations */
	   RatFlg;  /* output flag mutation rates */
  
  init_t InitMode; /* Specifying the initialization mode
					  (see init_t in type.h). */

  time_t MaxTime;  /* Maximal cpu-Time in seconds. 
					  If this value is set to zero, only the TrlCnt is active. */
  time_t startTime;/* Starting time. */
  time_t clock;    /* Time used for termination criterion. */

  FILE *Gpp,   /* gnuplot pipe pointer */
	   *FpObj, /* file pointer real valued object variables */
	   *FpDis, /* file pointer integer valued obj. vars. */
	   *FpSig, /* file pointer st. deviations */
	   *FpAlp, /* file pointer correlations */
	   *FpRat, /* file pointer mutation rates */
	   *FpOut, /* file pointer statistic measures */
	   *FpLog; /* file pointer protocoll */

  unsigned long TotExp,	/* total number of experiments */
	            TotTrl,	/* total number of trials */
			    XDim,	/* dimension of the real valued obj.var. */
		 	    DDim,	/* dimension of the int. valued obj.var. */
			    SigDim,	/* dimension of the stand. dev. vector */
			    AlpDim,	/* dimension of the correlation vector */
			    PDim;	/* dimension of the mutationrates vector */

  double lx,	/* lower bound x */
		 ux;	/* upper bound x */
  long	 ld,	/* lower bound d */
		 ud;	/* upper bound p */
  double lsigma,	/* lower bound sigma */
		 usigma,	/* upper bound sigma */
		 lalpha,	/* lower bound alpha */
		 ualpha,	/* upper bound alpha */
		 lp,	/* lower bound p */
		 up;	/* upper bound p */

  unsigned long	GenCnt,	/* generation counter */
			    TrlCnt,	/* actual trial counter */
			    GfxIvl,	/* graphics update interval */
			    DtaIvl;	/* data collection interval */
  double OrgSed;	/* original seed for RNG */

  unsigned long	PopVal, /* number of populations */
			    MueVal,	/* number of parents */
			    LdaVal;	/* number of offspring */

  double TauGlb,	/* mutation rate meta-par. global */
		 TauLcl,	/* mutation rate meta-par. local */
		 TauOne,	/* mutation rate m-p., one sigma */
		 Beta,	/* correlations meta-parameter */
		 GamGlb, /* meta-par. for mutationrates global */
		 GamLcl, /* meta-par. for mutationrates local */
		 GamOne, /* meta-par. for mutationrates one p_i */
		 Alpha,	/* meta-par. for mutationrates (Rechenbeg) */
		 W,	/* meta-par. for var.dim mut. (F. Kursawe) */
		 SigStart,/* start stepsize (default 1.0) */
		 PStart;	/* start mutationrate (default 0.0, not used)*/
  unsigned long	L;	/* meta-par. for the binomial mutation */

/*	Variables just needed for the GUI (quick and dirty programming,
	hope for a total new programm.)
*/
	x_reco_t	xReco;
	d_reco_t	dReco;
	sigma_reco_t	sigmaReco;
	alpha_reco_t	alphaReco;
	p_reco_t	pReco;
	ind_reco_t	indReco;

	adapt_t		xAdapt,
			dAdapt,
			sigmaAdapt,
			alphaAdapt,
			pAdapt;

	x_mute_t	xMute;
	d_mute_t	dMute;
	sigma_mute_t	sigmaMute;
	alpha_mute_t	alphaMute;
	p_mute_t	pMute;

	x_transform_t	  xTrans;
	d_transform_t	  dTrans;
	sigma_transform_t sigmaTrans;
	alpha_transform_t alphaTrans;
	p_transform_t	  pTrans;

	int		SigmaCompletition,
			PCompletition,
			SelectionScheme;

	/* End: Variables for the GUI. */

	char		RecScm[7],	/* recombination mechanism */
			AdapScm[6],	/* adaption mechanism */
			MttScm[6],	/* mutation mechanism indicator */
			SigComp,	/* completion of the sigma vector */
			PComp,		/* completion of the p vector */
			TransScm[6],	/* transformation mechanism */
			SltScm,		/* selection mechanism */

			FctNme[BUFSIZ],	  /* name of objective function */
			RstNme[BUFSIZ],	  /* name of restriction function */
			RngNme[BUFSIZ],   /* name of the rng */

			Group[BUFSIZ],	/* group name for pvm */
			Suffix[BUFSIZ],	/* file name suffix */
			OutFil[BUFSIZ],	/* output file name */
			LogFil[BUFSIZ],	/* logging file name */
			InzFil[BUFSIZ],	/* initialization file */
			ObjFil[BUFSIZ],	/* file for real val. obj. variables */
			DisFil[BUFSIZ], /* file for int. val. obj. variables */
			SigFil[BUFSIZ],	/* file for st.-deviations */
			AlpFil[BUFSIZ],	/* file for correlations */
			RatFil[BUFSIZ], /* file for for mutationrates */
			FmtStr[BUFSIZ];	/* format string */

	double		AllBst,	/* all time best performance */
			CurBst,	/* current best performance*/
			CurAvg,	/* current average performance */
			CurWst,	/* current worst performance */
			SigMin,	/* minimum standard deviation */
			SigAvg,	/* average standard deviation */
			SigMax,	/* maximum standard deviation */
			CorMin,	/* minimum angle */
			CorAvg,	/* average angle */
			CorMax,	/* maximum angle */
			PMin,	/* minimum mutationrate */
			PAvg,	/* average mutationrate */
			PMax;	/* maximum mutationrate */

	Ivector_tPtr	ObjBit,	/* output specification real object vars. */
			DisBit,	/* output specification integer obj. vars. */
			SigBit,	/* output specification sigmas */
			AlpBit,	/* output specification correlations */
			RatBit,	/* output specification mutation rates */
			IndBit;	/* output specification individuals */

	individual_tPtr	BstInd;	/* actual best individual */
	unsigned long	BstCnt; /* correspoding generation counter */

	double fMinStart,/* start objective function value */
		   Progress, /* progress velocity */
		   ProgressOld;

	/* Parameter needed for parallelization under pvm. */

	unsigned int	Tasks,
			TasksFactor,
			IsolationTime;
	migration_t	MigrationType;
	unsigned long	NoOfMigrants;
	unsigned int	NoOfNeighbours,
			Neighbours;
	topology_t	Topology;
	communication_t	Communication;
	int		tid;
	int		inst;

} param_t, *param_tPtr;

#endif /* _TYPES_H */
