/* climaf.f -- translated by f2c (version of 27 September 1990  15:58:58).
   You must link the resulting object file with the libraries:
	-lF77 -lI77 -lm -lc   (in that order)
*/

#include "f2c.h"

/* Common Block Declarations */

union {
    struct {
	doublereal yalt[33], delta[33];
    } _1;
    struct {
	doublereal y[33], delta[33];
    } _2;
} trans_;

#define trans_1 (trans_._1)
#define trans_2 (trans_._2)

struct namelist_1_ {
    char name[231];
};

#define namelist_1 (*(struct namelist_1_ *) &namelist_)

struct expe_1_ {
    doublereal to1[18], ta1[18], ts1[18], q1[18], eva1[18], p1[18], rh1[18], 
	    foz[18], fat[18], flussq1[18], bew1[18], ap1[18], ro1[18], hu1[18]
	    , ra1[18], lp1[18], absa1[18], abso1[18], xa1[18], xo1[18], fl1[
	    18], phi[18];
};
struct expe_2_ {
    doublereal to1[18], ta1[18], ts1[18], q1[18], eva1[18], p1[18], rh1[18], 
	    flusso1[18], flussa1[18], flussq1[18], bew1[18], ap1[18], ro1[18],
	     hu1[18], ra1[18], lp1[18], absa1[18], abso1[18], la1[18], lo1[18]
	    , flussg1[18], phi[18];
};

#define expe_1 (*(struct expe_1_ *) &expe_)
#define expe_2 (*(struct expe_2_ *) &expe_)

struct {
    doublereal abd[7020]	/* was [13][540] */, x[540], y[540];
    integer ipvt[540];
    doublereal xstart[540];
} globdat_;

#define globdat_1 globdat_

struct {
    doublereal dxtol, dytol;
    integer kmax;
} globtol_;

#define globtol_1 globtol_

union {
    struct {
	doublereal pp[33], pstart[33];
	integer parnr[24], izahl;
    } _1;
    struct {
	doublereal pp[33], pstart[33];
	integer parnr[24], iz;
    } _2;
} globpar_;

#define globpar_1 (globpar_._1)
#define globpar_2 (globpar_._2)

union {
    struct {
	doublereal rh[180], ta[180], ts[180], dummy[360], rh1[180];
    } _1;
    struct {
	doublereal rh[180], ta0[180], ts0[180], tae[180], tse[180], rhe[180];
    } _2;
    struct {
	doublereal rh[180], ta[180], ts[180], ta1[180], ts1[180], rh1[180];
    } _3;
} bl5_;

#define bl5_1 (bl5_._1)
#define bl5_2 (bl5_._2)
#define bl5_3 (bl5_._3)

union {
    struct {
	doublereal param[33];
    } _1;
    struct {
	doublereal ypar[33];
    } _2;
    struct {
	doublereal panf[33];
    } _3;
    struct {
	doublereal y[33];
    } _4;
} coeffi_;

#define coeffi_1 (coeffi_._1)
#define coeffi_2 (coeffi_._2)
#define coeffi_3 (coeffi_._3)
#define coeffi_4 (coeffi_._4)

struct {
    integer nfcall;
} globnfc_;

#define globnfc_1 globnfc_

struct {
    doublereal dmcheps, deps3, depsrot, depsqad;
} globkon_;

#define globkon_1 globkon_

union {
    struct {
	doublereal to[180], tstr[180], tastr[180], eisl[2], bew[180], absorb[
		180], emit[180], hadley[2], h[180], alat[180], olat[180], 
		snow[2], aflux[180], qflux[180], oflux[180], pcrit[180], ra[
		180], ro[180], eva[180], ptotal[180], qstr[180], grat[180], 
		gratq[180];
    } _1;
    struct {
	doublereal to[180], ts[180], ta[180], eisl[2], bew[180], absorb[180], 
		lp[180], hadley[2], h[180], alat[180], olat[180], snow[2], 
		aflux[180], qflux[180], oflux[180], pcrit[180], ra[180], ro[
		180], eva[180], p[180], q[180], grat[180], gradq[180];
    } _2;
    struct {
	doublereal to[180], ts[180], ta[180], eisl[2], bew[180], absorb[180], 
		emit[180], hadley[2], h[180], alat[180], olat[180], snow[2], 
		aflux[180], qflux[180], oflux[180], pcrit[180], ra[180], ro[
		180], eva[180], ptotal[180], q[180], grat[180], gradq[180];
    } _3;
} druck_;

#define druck_1 (druck_._1)
#define druck_2 (druck_._2)
#define druck_3 (druck_._3)

struct {
    doublereal glcount, slcount;
} globcnt_;

#define globcnt_1 globcnt_

union {
    struct {
	doublereal alf2, soleil[180], eisfrei[180], eisf[180], sonne, tropos[
		180];
    } _1;
    struct {
	doublereal alf2, soleil[180], eisfrei[180], eisf[180], sun, tropos[
		180];
    } _2;
    struct {
	doublereal alf2, sonne[180], eisfrei[180], eisf[180], sun, tropos[180]
		;
    } _3;
} bl1_;

#define bl1_1 (bl1_._1)
#define bl1_2 (bl1_._2)
#define bl1_3 (bl1_._3)

union {
    struct {
	doublereal dx, zc[180], zs[180], cosm[180], fi[180], xst[180], gradc[
		180], sinm[180], hadk, grczw[180], fland[180], height[180], 
		xland[180], xheight[180];
    } _1;
    struct {
	doublereal dx, zc[180], zs[180], cosm[180], phi[180], xst[180], gradc[
		180], sinm[180], hadk, grczw[180], fland[180], height[180], 
		xland[180], xheight[180];
    } _2;
    struct {
	doublereal dx, zc[180], zs[180], cosm[180], phi[180], xst[180], gradc[
		180], sinm[180], hadkof, grczw[180], fland[180], height[180], 
		xland[180], xheight[180];
    } _3;
} bl3_;

#define bl3_1 (bl3_._1)
#define bl3_2 (bl3_._2)
#define bl3_3 (bl3_._3)

union {
    struct {
	doublereal du[8], hl[180], hu[180], du1[363];
    } _1;
    struct {
	doublereal laps, kap1, kap2, alf1, gam, unten, thick, wolk2, hl[180], 
		hu[180], wolk1, zk[180], zkk[180], cohle, qaps;
    } _2;
    struct {
	doublereal laps, kap1, kap2, alf1, gam, unten, thick, wolk2, hl[180], 
		hu[180], wolk1, zk[180], zkk[180], cohle, pl;
    } _3;
    struct {
	doublereal laps, zap1, zap2, alf1, gam, unten, thick, wolk2, hl[180], 
		hu[180], wolk1, zk[180], zkk[180], cohle, pl;
    } _4;
    struct {
	doublereal laps, kap1, kap2, alf1, gam, unten, thick, wolk2, du1[180],
		 du2[180], wolk1, zk[180], zkk[180], cohle, pl;
    } _5;
} bl10_;

#define bl10_1 (bl10_._1)
#define bl10_2 (bl10_._2)
#define bl10_3 (bl10_._3)
#define bl10_4 (bl10_._4)
#define bl10_5 (bl10_._5)

union {
    struct {
	doublereal ca, co, cq, cp, al, fok, ata, pi, cofda, cofdo, cofdq, cof,
		 ci, cl, tf, tanf, tend, re, cofat, cofoz, coffe;
    } _1;
    struct {
	doublereal ca, co, cq, cp, al, fok, ata, pi, cofda, cofdo, cofdq, cof,
		 ci, cland, tf, tanf, tend, re, cofat, cofoz, coffe;
    } _2;
} bl11_;

#define bl11_1 (bl11_._1)
#define bl11_2 (bl11_._2)

struct {
    doublereal tax[18], tox[18], qx[18], bex[18], apx[18], px[18], evx[18], 
	    flx[18], lpx[18], fax[18], fox[18], fqx[18], hux[18];
} druckx_;

#define druckx_1 druckx_

struct {
    doublereal glieder[2340]	/* was [180][13] */, gha, gap, gp, gta, gtau, 
	    gq, quot, ghl, ghu, f1[13], gbew;
} ausg_;

#define ausg_1 ausg_

union {
    struct {
	doublereal dumm[1080], flussa[180], flusso[180], flussq[180];
    } _1;
    struct {
	doublereal dummy[1080], flussa[180], flusso[180], flussq[180];
    } _2;
    struct {
	doublereal va[180], vq[180], vo[180], dka[180], dko[180], dkq[180], 
		flussa[180], flusso[180], flussq[180];
    } _3;
} ausg1_;

#define ausg1_1 (ausg1_._1)
#define ausg1_2 (ausg1_._2)
#define ausg1_3 (ausg1_._3)

union {
    struct {
	doublereal amda[180], lo[180], la[180], abso[180], absa[180], albl[
		180], albh2o[180], albw[180];
    } _1;
    struct {
	doublereal amda[180], sto[180], sta[180], abso[180], absa[180], albb[
		180], albh2o[180], albw[180];
    } _2;
} ausg2_;

#define ausg2_1 (ausg2_._1)
#define ausg2_2 (ausg2_._2)

union {
    struct {
	doublereal cquot[180], tau[180], contr[900], appa[180], w[180];
    } _1;
    struct {
	doublereal quot[180], contr[1080], kappa[180], w[180];
    } _2;
} ausg4_;

#define ausg4_1 (ausg4_._1)
#define ausg4_2 (ausg4_._2)

struct {
    doublereal lam[2], eisbed, swi[180], dice;
} bl4_;

#define bl4_1 bl4_

union {
    struct {
	doublereal va, vq, da, dq[2], dw[2];
    } _1;
    struct {
	doublereal vaa, vqq, daa, dqq[2], dww[2];
    } _2;
} bl9_;

#define bl9_1 (bl9_._1)
#define bl9_2 (bl9_._2)

union {
    struct {
	doublereal pc[2], rmin, rcrit, w0, beta, exbeta, qred[180];
    } _1;
    struct {
	doublereal pc[2], rmin, rr, w0, beta, exbeta, qred[180];
    } _2;
} bl12_;

#define bl12_1 (bl12_._1)
#define bl12_2 (bl12_._2)

struct {
    doublereal tab, tae, tsb, tse, rhb, rhe;
} transf_;

#define transf_1 transf_

struct {
    doublereal wegclw[180], wegcll[180];
} stmo_;

#define stmo_1 stmo_

/* Initialized data */

struct {
    char e_1[231];
    } namelist_ = { "VA=    VQ=    DA=    DQ(1)= DQ(2)= DW(1)= DW(2)= PC(1)="
	    " PC(2)= LAM(1)=LAM(2)=RMIN=  RCRIT= UNTEN= THICK= WOLK1= WOLK2= "
	    "TOP=   UPPER= GAM=   CO2=   ALF1=  ALF2=  KAP1=  EISBED=RSURF= D"
	    "ICE=  SONNE= HADKOF=BETA=  W0=    ALBL=  LAPS=  " };

struct {
    doublereal e_1[36];
    doublereal fill_2[18];
    doublereal e_3[54];
    doublereal fill_4[18];
    doublereal e_5[36];
    doublereal fill_6[18];
    doublereal e_7[36];
    doublereal fill_8[18];
    doublereal e_9[18];
    doublereal fill_10[18];
    doublereal e_11[18];
    doublereal fill_12[72];
    doublereal e_13[36];
    } expe_ = { 0., 0., 0., 3.33, 10.01, 17.66, 22.68, 25.75, 27.03, 27.7, 
	    26.88, 24.19, 19.49, 11.35, 6.95, 4.43, .5, 0., -25.5, -16.75, 
	    -6.8, 2.08, 9.85, 16.45, 22.15, 24.45, 26., 26.55, 26.15, 23., 
	    16.75, 9.2, 2.25, -4.65, -11.65, -16.31, {0}, .2, .9, 2.7, 4.1, 
	    6.4, 9.2, 12.4, 15.4, 17.2, 17.9, 16.9, 13.9, 10.4, 6.8, 4.8, 3.3,
	     2.1, .9, 0., .045, .174, .52, .895, 1.256, 1.416, 1.541, 1.304, 
	    1.235, 1.389, 1.246, 1.002, .64, .47, .333, .145, .042, .07, .228,
	     .548, 1.2, 1.26, .932, .74, 1.05, 1.49, 1.965, 1.139, .7, .77, 
	    .825, .761, .464, .24, .15, {0}, -.07, -.6, -1.82, -2.48, -2.65, 
	    -3.14, -3.48, -3.14, -1.66, .53, 1.99, 2.81, 2.48, 1.82, .83, .33,
	     .17, 0., -.08, -.16, -.41, -1.82, -2.98, -3.15, -2.15, -1.49, 
	    -.33, .66, 1.24, 1.74, 2.48, 2.98, 2.81, 1.66, .67, .16, {0}, .47,
	     .58, .83, .8, .7, .59, .52, .53, .58, .6, .53, .47, .57, .63, 
	    .71, .69, .68, .7, .62, .6, .51, .43, .36, .3, .25, .24, .24, .25,
	     .25, .27, .31, .36, .41, .45, .54, .59, {0}, 5., 4.5, 4., 4., 
	    4.3, 4.1, 4., 4.3, 5.3, 5.9, 5., 4.2, 5., 4.7, 4.5, 4.1, 3.1, 3.5,
	     {0}, 156., 170., 188., 193., 211., 229., 238., 247., 247., 252., 
	    247., 238., 223., 215., 206., 192., 178., 178., {0}, -.25, -.99, 
	    -2.31, -4.3, -5.63, -6.12, -5.63, -4.3, -1.99, 1.16, 3.48, 4.63, 
	    4.97, 4.63, 3.48, 1.99, .83, .17, -85., -75., -65., -55., -45., 
	    -35., -25., -15., -5., 5., 15., 25., 35., 45., 55., 65., 75., 85. 
	    };


/* Table of constant values */

static integer c__33 = 33;
static integer c__1 = 1;
static integer c__540 = 540;
static integer c__223 = 223;
static integer c__24 = 24;
static doublereal c_b53 = .33333333333333331;
static integer c__13 = 13;
static integer c__4 = 4;
static integer c__0 = 0;
static integer c__180 = 180;
static doublereal c_b148 = .001;
static doublereal c_b160 = .01;
static doublereal c_b178 = 1.;
static doublereal c_b179 = -10.;
static doublereal c_b180 = 10.;
static doublereal c_b229 = .3;
static doublereal c_b230 = .4;
static integer c__2 = 2;
static doublereal c_b241 = .1;
static doublereal c_b263 = .99;
static integer c__3 = 3;
static doublereal c_b275 = .36;


/* DATENBANK: ZONAL GEMITTELTE KLIMADATEN FUER BEIDE HAEMISPHAEREN */

/*# 5 "climaf.f"*/
/*# 6 "climaf.f"*/

/*# 8 "climaf.f"*/
/*# 9 "climaf.f"*/

/*# 11 "climaf.f"*/
/*# 12 "climaf.f"*/
/*# 13 "climaf.f"*/

/*# 17 "climaf.f"*/

/*# 23 "climaf.f"*/
/*# 25 "climaf.f"*/
/*# 27 "climaf.f"*/
/*# 29 "climaf.f"*/
/*# 31 "climaf.f"*/
/*     DATA BEW1/0.47,0.56,0.77,0.79,0.65,0.54,0.47,0.47,0.50, */
/*    +0.51,0.44,0.41,0.47,0.57,0.64,0.64,0.61,0.55/ */
/*# 35 "climaf.f"*/
/*# 37 "climaf.f"*/
/*# 39 "climaf.f"*/
/*     DATA FL1/-0.25,-0.95,-2.3,-3.85,-5.0,-5.4,-4.8,-3.35,-1.05, */
/*    +1.60,3.90,5.25,5.5,5.0,3.9,2.45,1.1,0.17/ */
/*# 43 "climaf.f"*/
/*# 45 "climaf.f"*/
/*     DATA FOZ/-0.07,-0.60,-1.55,-2.10,-2.25,-2.3,-2.45,-2.15,-0.65, */
/*    +1.1,2.7,3.55,3.05,2.1,1.3,0.75,0.35,0.0/ */
/*# 49 "climaf.f"*/
/*# 51 "climaf.f"*/
/*# 53 "climaf.f"*/
/*# 55 "climaf.f"*/

/*     VERSION VOM 26.2.94 */
/*     VERSION VOM 29.4.94 */
/*     VERSION VOM 15.4.94 */
/*     VERSION VOM 12.3.94 */
/*     VERSION VOM 20.5.94 */
/*     VERSION VOM 2.6.94 */
/*     VERSION VOM 1.7.94 */
/*     VERSION VOM 20.8.94 */
/*     VERSION VOM 31.8.94 */
/*     VERSION VOM 2.9.94 */
/*     VERSION VOM 15.6.95 */


/*      PROGRAM OPT */
/*# 70 "climaf.f"*/
/* Subroutine */ int jentsch_(integer *nxpj, doublereal *xpj, doublereal *
	zifu, doublereal *starte, doublereal *fall)
{

    extern /* Subroutine */ int init_(void);
    static doublereal pneu[24];
    static integer i;
    static doublereal p[24], glied[223];
    extern /* Subroutine */ int dcopy_(integer *, doublereal *, integer *, 
	    doublereal *, integer *);
    static integer iparam[6];
    static doublereal rparam[7];
    extern /* Subroutine */ int objfun_(integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *), eingabe_(doublereal *, 
	    doublereal *);
    static doublereal pastart[33];


/*     VERFAHREN MIT IMSL-ROUTINE DBCLSJ (LEVENBERG-MARQUARDT) */
/* * */
/************************************************************************
*****/
/* * */
/* *    NONLINEAR INVERSE PROBLEM FORMULATED AS AN OPTIMIZATION PROBLEM: 
*/
/* *    MINIMIZE */
/* *    G(X(P)), SUBJECT TO F(X(P),P)=0 AND -1 < P < +1 */
/* *    HERE X IS THE VECTOR OF DIMENSION MM=3*M CONSISTING OF RH,TA,TS */

/* *    (IN NORMALIZED FORM), P IS THE PARAMETER VECTOR OF DIMENSION NX. 
*/
/* *    THE PROBLEM IS SOLVED BY MEANS OF IMSL ROUTINE DBCLSJ. */
/* *    FOR A GIVEN VECTOR P WE SOLVE THE SET OF NONLINEAR EQUATIONS BY A 
*/
/* *    NEWTON METHOD (SUBR. NEWTON AND JAKFKT). THE SOLUTION IS CALLED X.
 */
/* *    THIS VECTOR OF LENGTH MM IS INSERTED INTO THE TARGET FUNCTION G */

/* *    OF SUBR. "OBJFUN". */
/**    THE GRADIENT OF THE TARGET FUNCTION IS COMPUTED IN SUBR. "OBJGRD". 
THE*/
/**    PROCEDURE IS AS FOLLOWS. INCREMENT VECTOR P, COMPUTE THE CORRESPOND
ING*/
/* *    SOLUTION XNEW, OBEYING F(X(P),P)=0 AT X=XNEW, P=PNEW */
/**    AND INSERT INTO G, GIVING GNEW. THE GRADIENT IS THEN (GNEW-G)/(PNEW
-P).*/
/* *    THE FACT THAT THE JACOBIAN OF THE UNDERLYING SYSTEM */
/* :    OF NONLINEAR EQUATIONS IS BANDED, IS ESSENTIAL, AS IT SAVES TIME! 
*/
/* * */
/* *  GLOBAL PARAMETERS: */
/* *    M      NUMBER OF GRID POINTS PER DEPENDENT VARIABLE (RH,TA,TS) */
/* *    MM     NUMBER OF EQUATIONS = NUMBER OF DEGREES OF FREEDOM */
/* *    ML     NUMBER OF LOWER CODIAGONALS */
/* *    MU     NUMBER OF UPPER CODIAGONALS */
/* *    NX     MAXIMUM NUMBER OF PARAMETERS */
/* *    N      NUMBER OF PARAMETERS ACTUALLY UNDER CONSIDERATION, N < NX 
*/
/* *    INTV   STEPSIZE FOR EACH OPTIMIZATION-ITERATION */
/**    NOBJ   NUMBER OF LEAST SQUARE FACTORS (=GLIED) IN THE OBJECT FUNCTI
ON*/
/* * */
/* *  VARIABLES: */
/* *    KMAX    MAX NUMBER FOR NEWTON-ITERAIONS */
/* *    PARNR   SELECTS N PARAMETERS OUT OF NX */
/* *    XSTART  STARTING VALUES FOR RH,TA,TS IN NORMALIZED FORM */
/* *    X()     ITERATED XSTART */
/* *    Y()     RIGHT HAND SIDE OF THE DIFFERENTIAL EQUATIONS Y=F(X(P),P) 
*/
/* *    PSTART  NX START PARAMETERS IN NORMALIZED FORM, USUALLY ALL ZERO 
*/
/* *    PP()    NX PARAMETERS IN NORMALIZED FORM */
/* *    P()     N PARAMETERS IN NORMALIZED FORM */
/* +    PNEU()  N PARAMETERS IN NORMALIZED FORM, FINAL RESULT */
/* *    PASTART NX PARAMETERS IN PHYSICAL SPACE, START VALUES */
/* *    PARAM   NX PARAMETERS IN PHYSICAL SPACE, RESULTING VALUES */
/* +    GLIED() FINAL VALUES OF LEAST SQUARE FACTORS AFTER EACH ITERATION 
*/
/* *    KLICK   DECIDES WHETHER OPTIMIZATION OR SIMPLY SENSITIVITY STUDY 
*/
/* *    KLICK=TRUE: OPTIMIZATION PLUS SENSITIVITY */
/* *    KLICK=FALSE: SENSITIVITY ONLY */

/* * */
/* *  ROUTINES: */
/* *    INIT    MACHINE CONSTANTS */
/* *    EINGABE CONSTANTS, FUNCTIONS AND INITIAL VALUES */
/* *    EINGAB1 INPUT DATA FROM TAPE */
/* *    AUSGABE OUTPUT OF RESULTS */
/* *    NEWTON  SOLUTION METHOD FOR THE SYSTEM OF NONLINEAR EQ. */
/* *    WOLF    CALLS FCN WHICH COMPUTES THE RIGHT HAND SIDE */
/* *            OF THE DISCRETIZED EQUATIONS */
/* *    OBJFUN  OBJECT FUNCTION, AS DEMANDED BY IMSL DBCLSJ; CALLS FUNCT 
*/
/* *    FUNCT   DEFINITION OF THE OBJECT FUNCTION */
/* :    JAC     JACOBIAN DG/DP OF THE OBJECT FUNCTION */
/* *    JAKFKT  JACOBIAN DY/DX OF THE NONLINEAR SYSTEM */
/* * */
/* *    LINPACK-ROUTINES */
/* *    DCOPY */
/* *    DNRM2 */
/* *    DGBFA */
/* *    DQRDC */
/* * */
/************************************************************************
******/

/*# 142 "climaf.f"*/
/*# 143 "climaf.f"*/

/*# 145 "climaf.f"*/

/*# 148 "climaf.f"*/
/*# 149 "climaf.f"*/
/*# 150 "climaf.f"*/
/*# 155 "climaf.f"*/

/*# 157 "climaf.f"*/
/*# 158 "climaf.f"*/
/*# 159 "climaf.f"*/
/*# 160 "climaf.f"*/
/*# 161 "climaf.f"*/
/*# 162 "climaf.f"*/
/*# 163 "climaf.f"*/
/*# 164 "climaf.f"*/
    /* Parameter adjustments */
    --xpj;

    /* Function Body */
/*# 165 "climaf.f"*/

/*      WRITE(*,108) */
/*  108 FORMAT(' KLICK = F(KEINE OPTIMIERUNG) ODER T( OPTIMIERUNG)') */
/*      READ(*,109) KLICK */
/*  109 FORMAT(L1) */
/*      IF(KLICK) THEN */
/*      WRITE(*,110) */
/*      READ(*,*) IZAHL */
/*  110 FORMAT(' ANZAHL DER ITERATIONEN=') */
/*      END IF */
/*# 176 "climaf.f"*/
    *fall = 0.;
/*# 177 "climaf.f"*/
    iparam[0] = 0;
/*# 178 "climaf.f"*/
    if (*starte > 0.) {
	goto L3333;
    }
/*# 179 "climaf.f"*/
    init_();
/* ************************************************** */
/*# 181 "climaf.f"*/
    for (i = 1; i <= 24; ++i) {
/*# 182 "climaf.f"*/
/* L1: */
	globpar_1.parnr[i - 1] = i;
    }

/*     SELECTION OF PARAMETERS 1,.,N (N<=NX) TO BE OPTIMIZIED */
/*# 185 "climaf.f"*/
    globpar_1.parnr[3] = 33;
/*# 186 "climaf.f"*/
    globpar_1.parnr[5] = 26;
/*# 187 "climaf.f"*/
    globpar_1.parnr[11] = 31;
/*# 188 "climaf.f"*/
    globpar_1.parnr[12] = 29;
/*     PARNR( 16)=32 */
/*# 190 "climaf.f"*/
    globpar_1.parnr[16] = 32;
/*# 191 "climaf.f"*/
    globpar_1.parnr[18] = 30;


/* *************************************************** */
/*     BERECHNUNG DER ZIELFKT. OBJF FUER STARTWETRE PSTART, XSTART */
/*# 196 "climaf.f"*/
    eingabe_(globpar_1.pstart, globdat_1.xstart);
/*# 197 "climaf.f"*/
    dcopy_(&c__33, coeffi_1.param, &c__1, pastart, &c__1);
/*# 198 "climaf.f"*/
    dcopy_(&c__33, globpar_1.pstart, &c__1, globpar_1.pp, &c__1);
/*# 199 "climaf.f"*/
    dcopy_(&c__540, globdat_1.xstart, &c__1, globdat_1.x, &c__1);

/*     SELECTION OF PARAMETERS TO BE VARIED */
/*# 202 "climaf.f"*/
    for (i = 1; i <= 24; ++i) {
/*# 203 "climaf.f"*/
/* L2: */
	p[i - 1] = globpar_1.pp[globpar_1.parnr[i - 1] - 1];
    }


/*      CALL NEWTON (ABD,LDA,ML,MU,IPVT,DXTOL,DYTOL,X,Y,PP, */
/*     +                1,IERR,K,KMAX,FALL) */
/*      IF (IERR.GT.0) THEN */
/*         WRITE(6,1000) IERR,K */
/* 1000    FORMAT(' ERR-NR ',I1,' IN NEWTON  K = ',I3) */
/*         STOP 'STOP 1' */
/*      END IF */


/*      CALL FUNCT (PP,X,OBJF,GLIED) */

/*      RES = DNRM2 (MM,Y,1) */
/*      WRITE(66,101) */
/*      WRITE(66,102) K,RES */
/*      WRITE(6,1010) OBJF */


/*     IF (.NOT.KLICK) GO TO 30 */
/*     NO OPTIMISATION (GO TO 30) */

/*     START OPTIMIZING */
/*     CALL DU4LSF, IF NON-DEFAULT VALUES FOR IPARAM, RPARAM ARE DESIRED 
*/
/*     CALL DU4LSF(IPARAM,RPARAM) */
/*     SET VALUES NOW */
/*# 230 "climaf.f"*/
    iparam[2] = 500;
/*# 231 "climaf.f"*/
    iparam[3] = 1000;
/*# 232 "climaf.f"*/
    iparam[4] = 1000;
/*# 233 "climaf.f"*/
    rparam[0] = 1e-6;
/*# 234 "climaf.f"*/
    rparam[1] = 1e-6;
/*# 235 "climaf.f"*/
    rparam[2] = 1e-6;
/*# 236 "climaf.f"*/
    rparam[3] = 1e-6;
/*# 237 "climaf.f"*/
    rparam[4] = 1e-6;

/*         CALL DBCLSJ (OBJFUN, JAC, NOBJ, N, P, IBTYPE, BL, BU, PSCALE, 
*/
/*     +           FSCALE, IPARAM, RPARAM, PNEU, GLIED, FJAC, LDFJAC) */

/*         WRITE(*,132) RPARAM */
/*         WRITE(*,133) IPARAM */
/*  132    FORMAT(' RPARAM',7E10.2) */
/*  133    FORMAT(' IPARAM',7I8) */

/* C      WRITE(66,11011) NOBJ */
/* C      WRITE(66,11012) N */
/* C      WRITE(66,11103) P */
/* C      WRITE(66,11104) GLIED */
/* C      WRITE(66,11013) FALL */
/* C      WRITE(66,11014) ZIFU */
/*# 253 "climaf.f"*/
    objfun_(&c__223, &c__24, p, glied, fall, zifu);
/*# 254 "climaf.f"*/
    *starte = 1.;
/*     CALL PUT(8HSTARTE  ,1,1,1.0,1.0,IT,ITM,ATM,LOBC) */
/*# 256 "climaf.f"*/
    *zifu = *fall * 1e5 + *zifu;
/*      OBJF=ZIFU */
/*      WRITE(66,1010) ZIFU */
/* C     WRITE(66,1020) M */
/* C      WRITE(66,1030) (I,NAME(I),PARAM(I),I=1,NX) */
/* C     WRITE(66,557) RH */
/* C      WRITE(66,557) TA */
/* C      WRITE(66,557) TS */
/*# 264 "climaf.f"*/
    return 0;
/*# 265 "climaf.f"*/
L3333:
    for (i = 1; i <= 24; ++i) {
/*# 266 "climaf.f"*/
	pneu[i - 1] = xpj[i];
/*# 267 "climaf.f"*/
/* L3334: */
    }

/*        INSERTING PNEU INTO COMPLETE PARAMETER VECTOR PP */
/*# 270 "climaf.f"*/
    for (i = 1; i <= 24; ++i) {
/*# 271 "climaf.f"*/
	p[i - 1] = pneu[i - 1];
/*# 272 "climaf.f"*/
/* L15: */
	globpar_1.pp[globpar_1.parnr[i - 1] - 1] = p[i - 1];
    }
/* C      WRITE(66,11011) NOBJ */
/* C      WRITE(66,11012) N */
/* C      WRITE(66,11103) P */
/* C      WRITE(66,11104) GLIED */
/* C      WRITE(66,11013) FALL */
/* C      WRITE(66,11014) ZIFU */
/* C11011 FORMAT(' NOBJ : ',I4) */
/* C11012 FORMAT(' N : ',I4) */
/* C11103 FORMAT(/' P'/5(D12.5)) */
/* C11104 FORMAT(/' GLIED'/5(D12.5)) */
/* C11013 FORMAT(' FALL : ',I4) */
/* C11014 FORMAT(' ZIFU : ',D12.5) */
/*# 285 "climaf.f"*/
    objfun_(&c__223, &c__24, p, glied, fall, zifu);
/*# 286 "climaf.f"*/
    *zifu = *fall * 1e5 + *zifu;
/*# 287 "climaf.f"*/
    return 0;

/*     COMPUTATION OF OBJECTIVE FUNCTION */
/*      CALL FUNCT (PP,X,OBJF,GLIED) */

/*      WRITE(66,103) PP */
/*      WRITE(66,1012) (NAME(I),PASTART(I),PARAM(I),I=1,NX) */
/*      WRITE(66,1011) NFCALL */
/*      WRITE(66,1010) ZIFU */
/*      DO 3 J=1,N */
/*      WRITE(66,560) J */
/*  3   WRITE(66,559) (FJAC(I,J),I=1,NOBJ) */

/*     DARSTELLUNG DER STARTWERTE FUER WEITERE VERWENDUNG */
/* 30   CONTINUE */
/*      WRITE(66,555) */
/* C      WRITE(66,1020) M */
/* C      WRITE(66,1030) (I,NAME(I),PARAM(I),I=1,NX) */
/* C      WRITE(66,557) RH */
/* C      WRITE(66,557) TA */
/* C      WRITE(66,557) TS */
/*      WRITE(66,555) */

/*      RETURN */

/*     CALL AUSGABE */

/*     CALL MONITOR */


/*# 317 "climaf.f"*/
/* L100: */
/*# 318 "climaf.f"*/
/* L101: */
/*# 319 "climaf.f"*/
/* L102: */
/*# 320 "climaf.f"*/
/* L103: */
/*# 321 "climaf.f"*/
/* L555: */
/*# 322 "climaf.f"*/
/* L557: */
/*# 323 "climaf.f"*/
/* L559: */
/*# 324 "climaf.f"*/
/* L560: */
/*# 325 "climaf.f"*/
/* L1010: */
/*# 326 "climaf.f"*/
/* L1011: */
/*# 327 "climaf.f"*/
/* L1012: */
/*# 328 "climaf.f"*/
/* L1040: */
/*# 329 "climaf.f"*/
/* L1020: */
/*# 330 "climaf.f"*/
/* L1030: */
/*# 331 "climaf.f"*/
/* L1070: */
/*      STOP 'OPTIMSL OK' */
/*# 333 "climaf.f"*/
} /* jentsch_ */


/****************************************************************************
***/
/*# 336 "climaf.f"*/
/* Subroutine */ int init_(void)
{
    /* Builtin functions */
    double sqrt(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal deps, dx, dy;


/* *    FIXES MACHINE DEPENDENT CONSTANTS AND INITIALIZES CERTAIN INDICES 
*/

/*# 340 "climaf.f"*/
/*# 341 "climaf.f"*/

/*# 343 "climaf.f"*/
/*# 344 "climaf.f"*/
/*# 345 "climaf.f"*/

/*# 347 "climaf.f"*/
    globnfc_1.nfcall = 0;

/*# 349 "climaf.f"*/
    deps = 1.;
/*# 350 "climaf.f"*/
    dx = 2.;
/*# 351 "climaf.f"*/
    dy = 1.;
/*# 352 "climaf.f"*/
L30:
    if (dx == dy) {
	goto L40;
    }
/*# 353 "climaf.f"*/
    deps *= .5;
/*# 354 "climaf.f"*/
    dx = deps + 1.;
/*# 355 "climaf.f"*/
    goto L30;
/*# 356 "climaf.f"*/
L40:
    globkon_1.dmcheps = deps * 2.;
/*# 357 "climaf.f"*/
    globkon_1.depsrot = sqrt(globkon_1.dmcheps);
/*# 358 "climaf.f"*/
    globkon_1.deps3 = pow_dd(&globkon_1.dmcheps, &c_b53);
/*# 359 "climaf.f"*/
    globkon_1.depsqad = globkon_1.dmcheps * globkon_1.dmcheps;

/*# 361 "climaf.f"*/
    globtol_1.dxtol = 1e-10;
/*# 362 "climaf.f"*/
    globtol_1.dytol = 1.0000000000000001e-9;
/*# 363 "climaf.f"*/
    globtol_1.kmax = 25;

/*      WRITE(66,1000) DMCHEPS,DEPSROT,DEPSQAD, */
/*     +              DXTOL, DYTOL, KMAX */

/*# 368 "climaf.f"*/
/* L1000: */

/*# 373 "climaf.f"*/
    return 0;
/*# 374 "climaf.f"*/
} /* init_ */


/****************************************************************************
***/

/*# 378 "climaf.f"*/
/* Subroutine */ int objfun_(integer *nobj, integer *np, doublereal *p, 
	doublereal *glied, doublereal *fall, doublereal *zifu)
{
    /* Initialized data */

    static integer izahl = 1;

    static doublereal objf;
    static integer ierr, i, k;
    extern /* Subroutine */ int funct_(doublereal *, doublereal *, doublereal 
	    *, doublereal *), newton_(doublereal *, integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *, integer *, 
	    integer *, doublereal *);


/* *    OBJECT FUNCTION, AS REQUIRED BY IMSL-ROUTINE DBCLSJ */

/*# 382 "climaf.f"*/
/*# 383 "climaf.f"*/
/*# 384 "climaf.f"*/

/*# 387 "climaf.f"*/

/*# 389 "climaf.f"*/
/*# 391 "climaf.f"*/

/*# 393 "climaf.f"*/
/*# 394 "climaf.f"*/
/*# 395 "climaf.f"*/
/*# 396 "climaf.f"*/
/*# 397 "climaf.f"*/
/*# 398 "climaf.f"*/
/*# 399 "climaf.f"*/
/*# 400 "climaf.f"*/

/*# 405 "climaf.f"*/
    /* Parameter adjustments */
    --glied;
    --p;

    /* Function Body */

/*# 407 "climaf.f"*/
    for (i = 1; i <= 24; ++i) {
/*# 408 "climaf.f"*/
/* L5: */
	globpar_2.pp[globpar_2.parnr[i - 1] - 1] = p[i];
    }

/*# 410 "climaf.f"*/
    newton_(globdat_1.abd, &c__13, &c__4, &c__4, globdat_1.ipvt, &
	    globtol_1.dxtol, &globtol_1.dytol, globdat_1.x, globdat_1.y, 
	    globpar_2.pp, &c__1, &ierr, &k, &globtol_1.kmax, fall);


/*# 414 "climaf.f"*/
    if (ierr > 0) {
/*         WRITE(6,1010) IERR,K */
/* 1010    FORMAT(' ERR-NR ',I1,' IN NEWTON  K =',I4) */
/*         WRITE(6,100) (I,NAME(I),YPAR(I),I=1,NX) */
/*         STOP 'STOP 2' */
/*# 419 "climaf.f"*/
	*fall = 2.;
/*# 420 "climaf.f"*/
	return 0;
/*# 421 "climaf.f"*/
    }

/*     COMPUTE OBJECT FUNCTION */
/*# 424 "climaf.f"*/
    funct_(globpar_2.pp, globdat_1.x, &objf, &glied[1]);
/*# 425 "climaf.f"*/
    *zifu = objf;

/*      WRITE(*,101) IZAHL, OBJF, YPAR(9), YPAR(12) */
/*  101 FORMAT(' NR=',I3,' OBJ=',D10.4,' PC(2)=',F6.4, */
/*     +        ' RMIN=',F6.3) */
/*      WRITE(66,100) (I,NAME(I),YPAR(I),I=1,NX) */
/*      WRITE(66,102) */
/*      WRITE(66,100) (I,NAME(I),PP(I),I=1,NX) */
/*      WRITE(66,102) */
/*      WRITE(66,102) */

/*     DIE OPTIMIERUNG WIRD NACH IZ ITERATIONEN ABGEBROCHEN, ERGEBNISSE */

/*    WERDEN AUSGEDRUCKT. WENN IZ GROSS (100 ODER MEHR), SOLLTE DIESE ABFR
AGE NICHT*/
/*     GREIFEN, DA DIE ROUTINE DANN ERFOLGREICH SEIN MUESSTE. */

/*      IF(IZAHL.EQ.IZ) THEN */
/*      WRITE(66,102) IZAHL */
/*      WRITE(66,100) (I,NAME(I),PP(I),I=1,NX) */
/*      WRITE(66,102)  IZAHL */
/*      WRITE(66,1020) M */
/*      WRITE(66,100) (I,NAME(I),YPAR(I),I=1,NX) */
/*      WRITE(66,557) RH */
/*      WRITE(66,557) TA */
/*      WRITE(66,557) TS */
/*      CALL AUSGABE */
/*      STOP */
/*      END IF */
/*# 452 "climaf.f"*/
/* L100: */
/*# 453 "climaf.f"*/
/* L102: */
/*# 454 "climaf.f"*/
/* L557: */
/*# 455 "climaf.f"*/
/* L1020: */

/*# 457 "climaf.f"*/
    ++izahl;
/*# 458 "climaf.f"*/
    return 0;
/*# 459 "climaf.f"*/
} /* objfun_ */

/* === */

/*# 462 "climaf.f"*/
/* Subroutine */ int eingab1_(doublereal *pp, doublereal *x)
{
    /* Format strings */
    static char fmt_1020[] = "(a4,i4)";
    static char fmt_1000[] = "(i2,1x,a7,2x,e19.12)";
    static char fmt_1010[] = "(3e19.12)";

    /* System generated locals */
    integer i_1;
    olist o_1;

    /* Builtin functions */
    integer f_open(olist *), s_rsfe(cilist *), do_fio(integer *, char *, 
	    ftnlen), e_rsfe(void), s_rsle(cilist *), e_rsle(void);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static char text[5];
    static integer i, j, l;
    static logical found;
    extern /* Subroutine */ int dcopy_(integer *, doublereal *, integer *, 
	    doublereal *, integer *);
    static integer lj;

    /* Fortran I/O blocks */
    static cilist io__21 = { 0, 3, 1, fmt_1020, 0 };
    static cilist io__25 = { 0, 3, 0, fmt_1000, 0 };
    static cilist io__28 = { 0, 3, 0, fmt_1010, 0 };
    static cilist io__29 = { 0, 3, 0, 0, 0 };



/*# 464 "climaf.f"*/
/*# 465 "climaf.f"*/
/*     PP() PARAMETERS IN PHYSICAL SPACE */

/*# 468 "climaf.f"*/
/*# 469 "climaf.f"*/
/*# 470 "climaf.f"*/
/*# 471 "climaf.f"*/

/*# 473 "climaf.f"*/
/*# 474 "climaf.f"*/

/*# 476 "climaf.f"*/
    /* Parameter adjustments */
    --x;
    --pp;

    /* Function Body */
    o_1.oerr = 0;
    o_1.ounit = 3;
    o_1.ofnmlen = 9;
    o_1.ofnm = "clima.dat";
    o_1.orl = 0;
    o_1.osta = 0;
    o_1.oacc = 0;
    o_1.ofm = 0;
    o_1.oblnk = 0;
    f_open(&o_1);
/*# 477 "climaf.f"*/
    o_1.oerr = 0;
    o_1.ounit = 66;
    o_1.ofnmlen = 10;
    o_1.ofnm = "OUTPUT.DAT";
    o_1.orl = 0;
    o_1.osta = 0;
    o_1.oacc = 0;
    o_1.ofm = 0;
    o_1.oblnk = 0;
    f_open(&o_1);
/*      OPEN(67,FILE='KAI.DAT') */

/*# 480 "climaf.f"*/
    found = FALSE_;
/*     SUCHE NACH DATENSATZ MIT GLEICHER AUFLOESUNG */
/*# 482 "climaf.f"*/
L1:
    i_1 = s_rsfe(&io__21);
    if (i_1 != 0) {
	goto L3;
    }
    i_1 = do_fio(&c__1, text, 5L);
    if (i_1 != 0) {
	goto L3;
    }
    i_1 = do_fio(&c__1, (char *)&l, (ftnlen)sizeof(integer));
    if (i_1 != 0) {
	goto L3;
    }
    i_1 = e_rsfe();
/*# 483 "climaf.f"*/
    if (l == 20) {
/*# 484 "climaf.f"*/
	lj = l + 1;
/*# 485 "climaf.f"*/
    } else {
/*# 486 "climaf.f"*/
	lj = l;
/*# 487 "climaf.f"*/
    }
/*# 488 "climaf.f"*/
    if (l == 180) {
/*# 489 "climaf.f"*/
	s_rsfe(&io__25);
	for (i = 1; i <= 33; ++i) {
	    do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
	    do_fio(&c__1, namelist_1.name + (i - 1) * 7, 7L);
	    do_fio(&c__1, (char *)&pp[i], (ftnlen)sizeof(doublereal));
	}
	e_rsfe();
/*# 490 "climaf.f"*/
	s_rsfe(&io__28);
	do_fio(&c__540, (char *)&x[1], (ftnlen)sizeof(doublereal));
	e_rsfe();
/*# 491 "climaf.f"*/
	found = TRUE_;
/*         WRITE(6,1040) */
/*# 493 "climaf.f"*/
    } else {
/*# 494 "climaf.f"*/
	i_1 = lj + 33;
	for (j = 1; j <= i_1; ++j) {
/*# 495 "climaf.f"*/
/* L32: */
	    s_rsle(&io__29);
	    e_rsle();
	}
/*# 496 "climaf.f"*/
	goto L1;
/*# 497 "climaf.f"*/
    }
/*# 498 "climaf.f"*/
    if (! found) {
	s_stop("NOT FOUND", 9L);
    }

/*# 500 "climaf.f"*/
/*# 501 "climaf.f"*/
/*# 502 "climaf.f"*/
/*# 503 "climaf.f"*/
/* L1040: */

/*# 505 "climaf.f"*/
    dcopy_(&c__33, &pp[1], &c__1, coeffi_3.panf, &c__1);
/*# 506 "climaf.f"*/
    return 0;
/*# 507 "climaf.f"*/
L3:
    s_stop("END OF INPUT", 12L);
/*# 508 "climaf.f"*/
} /* eingab1_ */

/* === */

/*# 511 "climaf.f"*/
/* Subroutine */ int jakfkt_(doublereal *a, integer *lda, integer *ml, 
	integer *mu, doublereal *x, doublereal *y, doublereal *p, integer *n, 
	integer *inf, doublereal *fall)
{
    /* System generated locals */
    integer a_dim1, a_offset, i_1, i_2, i_3, i_4;

    /* Local variables */
    extern /* Subroutine */ int wolf_(doublereal *, doublereal *, doublereal *
	    , doublereal *);
    static doublereal h;
    static integer i, j, k, iband, m1, m2;
    static doublereal xh[540], yr[540];
    extern /* Subroutine */ int fcn_(doublereal *, doublereal *, doublereal *)
	    ;


/*     COMPUTES THE JACOBIAN OF THE SYSTEM OF NONLINEAR EQUATIONS */
/*     BANDED STRUCTURE */
/*# 515 "climaf.f"*/
/*# 516 "climaf.f"*/
/*# 517 "climaf.f"*/
/*# 518 "climaf.f"*/


/*# 521 "climaf.f"*/

/*# 523 "climaf.f"*/
    /* Parameter adjustments */
    --p;
    --y;
    --x;
    a_dim1 = *lda;
    a_offset = a_dim1 + 1;
    a -= a_offset;

    /* Function Body */
    if (*inf == 1) {
	wolf_(&p[1], &x[1], &y[1], fall);
    }

/*# 525 "climaf.f"*/
    iband = *mu + *ml + 1;
/*# 526 "climaf.f"*/
    for (i = 1; i <= 540; ++i) {
/*# 527 "climaf.f"*/
/* L10: */
	xh[i - 1] = globkon_1.depsrot;
    }
/*# 528 "climaf.f"*/
    i_1 = iband;
    for (i = 1; i <= i_1; ++i) {
/*# 529 "climaf.f"*/
	i_2 = iband;
	for (j = i; i_2 < 0 ? j >= 540 : j <= 540; j += i_2) {
/*# 530 "climaf.f"*/
/* L50: */
	    x[j] += xh[j - 1];
	}
/*        CALL WOLF (P,X,YR,FALL) */
/*# 532 "climaf.f"*/
	fcn_(&x[1], yr, fall);
/*# 533 "climaf.f"*/
	i_2 = iband;
	for (j = i; i_2 < 0 ? j >= 540 : j <= 540; j += i_2) {
/*# 534 "climaf.f"*/
	    x[j] -= xh[j - 1];
/*# 535 "climaf.f"*/
/* Computing MAX */
	    i_3 = 1, i_4 = j - *mu;
	    m1 = max(i_3,i_4);
/*# 536 "climaf.f"*/
/* Computing MIN */
	    i_3 = 540, i_4 = j + *ml;
	    m2 = min(i_3,i_4);
/*# 537 "climaf.f"*/
	    h = 1. / xh[j - 1];
/*# 538 "climaf.f"*/
	    i_3 = m2;
	    for (k = m1; k <= i_3; ++k) {
/*# 539 "climaf.f"*/
/* L70: */
		a[k - j + iband + j * a_dim1] = (yr[k - 1] - y[k]) * h;
	    }
/*# 540 "climaf.f"*/
/* L60: */
	}
/*# 541 "climaf.f"*/
/* L40: */
    }

/*# 543 "climaf.f"*/
    return 0;
/*# 544 "climaf.f"*/
} /* jakfkt_ */

/* === */
/*# 546 "climaf.f"*/
/* Subroutine */ int newton_(doublereal *abd, integer *lda, integer *ml, 
	integer *mu, integer *ipvt, doublereal *dxtol, doublereal *restol, 
	doublereal *x, doublereal *y, doublereal *pp, integer *inf, integer *
	ierr, integer *k, integer *kmax, doublereal *fall)
{
    /* System generated locals */
    integer abd_dim1, abd_offset;
    doublereal d_1, d_2, d_3;

    /* Local variables */
    static logical flag_;
    static integer info;
    extern /* Subroutine */ int wolf_(doublereal *, doublereal *, doublereal *
	    , doublereal *);
    extern doublereal dnrm2_(integer *, doublereal *, integer *);
    extern /* Subroutine */ int dgbfa_(doublereal *, integer *, integer *, 
	    integer *, integer *, integer *, integer *);
    static integer i;
    static doublereal gamma;
    extern /* Subroutine */ int dgbsl_(doublereal *, integer *, integer *, 
	    integer *, integer *, integer *, doublereal *, integer *), dcopy_(
	    integer *, doublereal *, integer *, doublereal *, integer *);
    static doublereal dx, yh[540], xh[540];
    extern /* Subroutine */ int jakfkt_(doublereal *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, integer *, 
	    integer *, doublereal *);
    static doublereal resalt;
    extern /* Subroutine */ int fcn_(doublereal *, doublereal *, doublereal *)
	    ;
    static doublereal res;


/*# 549 "climaf.f"*/
/*# 550 "climaf.f"*/

/*# 552 "climaf.f"*/
/*# 553 "climaf.f"*/

/*# 555 "climaf.f"*/
/*# 556 "climaf.f"*/
/*# 558 "climaf.f"*/

/*# 560 "climaf.f"*/
/*# 561 "climaf.f"*/
/*     LOEST (HOFFENTLICH) DIE NICHTLINEAREN GLEICHUNGEN */
/*     PROBLEM BEI DIESEM VERFAHREN: GELEGENTLICH KONVERGIERT ES NICHT. */

/*     WARUM? */
/*# 565 "climaf.f"*/
    /* Parameter adjustments */
    --pp;
    --y;
    --x;
    --ipvt;
    abd_dim1 = *lda;
    abd_offset = abd_dim1 + 1;
    abd -= abd_offset;

    /* Function Body */
    *k = 0;
/*# 566 "climaf.f"*/
    *ierr = 0;
/*# 567 "climaf.f"*/
    wolf_(&pp[1], &x[1], &y[1], fall);
/*# 568 "climaf.f"*/
    res = dnrm2_(&c__540, &y[1], &c__1);

/*# 570 "climaf.f"*/
    if (res < *restol || *k >= *kmax) {
	return 0;
    }

/*# 572 "climaf.f"*/
L5:
    if (*inf > 0) {
/*# 573 "climaf.f"*/
	jakfkt_(&abd[abd_offset], lda, ml, mu, &x[1], &y[1], &pp[1], &c__33, &
		c__1, fall);
/*# 574 "climaf.f"*/
	dgbfa_(&abd[abd_offset], lda, &c__540, ml, mu, &ipvt[1], &info);
/*# 575 "climaf.f"*/
	if (info != 0) {
/*           WRITE(*,111) INFO */
/* 111       FORMAT(' INFO',I3) */
/*           STOP 'STOP 5' */
/*# 579 "climaf.f"*/
	    *fall = 5.;
/*# 580 "climaf.f"*/
	    return 0;
/*# 581 "climaf.f"*/
	}
/*# 582 "climaf.f"*/
	globcnt_1.glcount += 1;
/*# 583 "climaf.f"*/
    }

/*# 585 "climaf.f"*/
    dgbsl_(&abd[abd_offset], lda, &c__540, ml, mu, &ipvt[1], &y[1], &c__0);
/*# 586 "climaf.f"*/
    globcnt_1.slcount += 1;

/*# 588 "climaf.f"*/
    dcopy_(&c__540, &y[1], &c__1, yh, &c__1);
/*# 589 "climaf.f"*/
    gamma = 1.;
/*# 590 "climaf.f"*/
    resalt = res;
/*# 591 "climaf.f"*/
/* L100: */

/*        NEWTONSCHRITT DARF HOECHSTENS SO LANG SEIN, DASS DIE FEUCHTE */
/*        NICHT NEGATIV WIRD UND AUCH NICHT ZU GROSS WIRD */
/*# 595 "climaf.f"*/
    for (i = 1; i <= 540; i += 3) {
/*# 596 "climaf.f"*/
	if (x[i] - yh[i - 1] < -3.) {
/* Computing MIN */
	    d_2 = gamma, d_3 = (d_1 = (x[i] + 1.) / yh[i - 1], abs(d_1));
	    gamma = min(d_2,d_3);
	}
/*# 598 "climaf.f"*/
	if (x[i] - yh[i - 1] > 1.) {
/* Computing MIN */
	    d_2 = gamma, d_3 = (d_1 = (1. - x[i]) / yh[i - 1], abs(d_1));
	    gamma = min(d_2,d_3);
	}
/*# 600 "climaf.f"*/
/* L20: */
    }
/*# 601 "climaf.f"*/
    gamma = (1. - globkon_1.depsrot) * gamma;
/*# 602 "climaf.f"*/
    dx = dnrm2_(&c__540, yh, &c__1);

/*# 604 "climaf.f"*/
L30:
    for (i = 1; i <= 540; ++i) {
/*# 605 "climaf.f"*/
/* L40: */
	xh[i - 1] = x[i] - gamma * yh[i - 1];
    }
/*# 606 "climaf.f"*/
    fcn_(xh, &y[1], fall);
/*# 607 "climaf.f"*/
    res = dnrm2_(&c__540, &y[1], &c__1);
/*# 608 "climaf.f"*/
    gamma *= .5;
/*# 609 "climaf.f"*/
    if (res >= resalt * 1.05 && gamma >= 1e-6) {
	goto L30;
    }
/*# 610 "climaf.f"*/
    gamma *= 2.;
/*# 611 "climaf.f"*/
    dcopy_(&c__540, xh, &c__1, &x[1], &c__1);
/*# 612 "climaf.f"*/
    res = dnrm2_(&c__540, &y[1], &c__1);

/* 125  FORMAT(E10.3) */

/*# 616 "climaf.f"*/
    dx = gamma * dx;
/*# 617 "climaf.f"*/
    ++(*k);
/*# 618 "climaf.f"*/
    flag_ = res > *restol || dx > *dxtol;
/*# 619 "climaf.f"*/
    if (flag_ && *k < *kmax) {
	goto L5;
    }

/*# 621 "climaf.f"*/
    if (flag_ && *k >= *kmax) {
/*# 622 "climaf.f"*/
	*ierr = 1;
/*            WRITE(66,1000) K,RES,DX,GAMMA,INFO,INF */
/* 1000       FORMAT(1I4,3E10.3,2I4) */
/*            WRITE(66,1001) PP */
/* 1001       FORMAT(1X,E19.12) */
/*            DO 50 I=1,MM,3 */
/*            IF(X(I).LT.-3.0D0) THEN */
/*            WRITE(66,1002) I,X(I) */
/* 1002       FORMAT(' NEWTONITERATION =',I3,' X=',D12.4) */
/*            GO TO 51 */
/*            END IF */
/*   50       CONTINUE */
/*   51       CONTINUE */
/*# 635 "climaf.f"*/
    }

/*# 637 "climaf.f"*/
    return 0;
/*# 638 "climaf.f"*/
} /* newton_ */

/* === */

/*# 641 "climaf.f"*/
/* Subroutine */ int funct_(doublereal *xc, doublereal *yvec, doublereal *fc, 
	doublereal *glied)
{
    /* Initialized data */

    static doublereal g[6] = { .5,.1,2e14,.025,.05,.15 };

    /* System generated locals */
    doublereal d_1, d_2, d_3, d_4, d_5, d_6, d_7, d_8, d_9, d_10;

    /* Builtin functions */
    double cos(doublereal);

    /* Local variables */
    static doublereal bewg, tauh, quad;
    static integer i, j;
    static doublereal absag, absog, albwg;
    extern /* Subroutine */ int summe_(integer *, doublereal *, doublereal *);

    static integer i1, j2[18], i2;
    static doublereal ap[180], fl[180], pg, qg, gl;
    extern doublereal sprung_(doublereal *, doublereal *);
    static doublereal zusatz, tag, hlg, hlx[18], szc[18], tsg, hug, apg, gto;

/*     PROGRAMM NAME IN DER IMSL-BIBLIOTHEK: OBJFUNCT */

/*     COMPUTATION OF OBJECT FUNCTION FC, WEIGHT G, */
/*     VARIABLES WITH SUBSCRIPT "1" ARE DATA (TOTAL NUMBER L), */
/*     VARIABLES WITH SUBSCRIPT "X" */
/*     ARE NUMERICAL RESULTS ADJUSTED TO LATITUDES OF MEASUREMENTS */

/*# 649 "climaf.f"*/
/*# 650 "climaf.f"*/

/*# 653 "climaf.f"*/
/*# 654 "climaf.f"*/

/*# 657 "climaf.f"*/
/*# 658 "climaf.f"*/
/*# 660 "climaf.f"*/
/*# 661 "climaf.f"*/
/*# 662 "climaf.f"*/
/*# 664 "climaf.f"*/
/*# 668 "climaf.f"*/
/*# 670 "climaf.f"*/
/*# 673 "climaf.f"*/
/*# 675 "climaf.f"*/
/*# 676 "climaf.f"*/

/*# 679 "climaf.f"*/
/*# 680 "climaf.f"*/
/*# 681 "climaf.f"*/
/*# 682 "climaf.f"*/

/*# 684 "climaf.f"*/
    /* Parameter adjustments */
    --glied;
    --yvec;
    --xc;

    /* Function Body */



/*# 688 "climaf.f"*/
    if (globnfc_1.nfcall == 0) {
/*# 689 "climaf.f"*/
	for (i = 1; i <= 18; ++i) {
/*# 690 "climaf.f"*/
	    expe_2.q1[i - 1] *= .001;
/*# 691 "climaf.f"*/
	    expe_2.flussg1[i - 1] *= 1e15;
/*# 692 "climaf.f"*/
	    expe_2.flusso1[i - 1] *= 1e15;
/*# 693 "climaf.f"*/
	    expe_2.flussa1[i - 1] *= 1e15;
/*# 694 "climaf.f"*/
	    szc[i - 1] = cos(bl11_1.pi * expe_2.phi[i - 1] / 180.);
/*# 695 "climaf.f"*/
/* L36: */
	    expe_2.lp1[i - 1] = -expe_2.lp1[i - 1];
	}
/*# 696 "climaf.f"*/
	for (j = 1; j <= 18; ++j) {
/*# 697 "climaf.f"*/
	    for (i = 1; i <= 180; ++i) {
/*# 698 "climaf.f"*/
		if (bl3_1.fi[i - 1] >= expe_2.phi[j - 1]) {
/*# 699 "climaf.f"*/
		    j2[j - 1] = i;
/*# 700 "climaf.f"*/
		    goto L30;
/*# 701 "climaf.f"*/
		}
/*# 702 "climaf.f"*/
/* L31: */
	    }
/*# 703 "climaf.f"*/
L30:
	    ;
	}
/*# 704 "climaf.f"*/
    }


/*# 707 "climaf.f"*/
    ++globnfc_1.nfcall;

/*# 709 "climaf.f"*/
    for (i = 1; i <= 180; ++i) {
/*# 710 "climaf.f"*/
	ap[i - 1] = 1. - druck_2.absorb[i - 1] / (bl1_1.soleil[i - 1] * 340.);

/*# 711 "climaf.f"*/
/* L16: */
	fl[i - 1] = ausg1_1.flusso[i - 1] + ausg1_1.flussa[i - 1] + 
		ausg1_1.flussq[i - 1];
    }

/*     BERECHNUNG DER GERECHNETEN WERTE AN DEN MESSPUNKTEN (L=18) */
/*# 714 "climaf.f"*/
    for (j = 1; j <= 18; ++j) {
/*# 715 "climaf.f"*/
	i2 = j2[j - 1];
/*# 716 "climaf.f"*/
	i1 = i2 - 1;
/*# 717 "climaf.f"*/
	druckx_1.tax[j - 1] = druck_2.ta[i1 - 1] + (druck_2.ta[i2 - 1] - 
		druck_2.ta[i1 - 1]) * (expe_2.phi[j - 1] - bl3_1.fi[i1 - 1]) /
		 (bl3_1.fi[i2 - 1] - bl3_1.fi[i1 - 1]);
/*# 718 "climaf.f"*/
	druckx_1.tox[j - 1] = druck_2.to[i1 - 1] + (druck_2.to[i2 - 1] - 
		druck_2.to[i1 - 1]) * (expe_2.phi[j - 1] - bl3_1.fi[i1 - 1]) /
		 (bl3_1.fi[i2 - 1] - bl3_1.fi[i1 - 1]);
/*# 719 "climaf.f"*/
	druckx_1.qx[j - 1] = druck_2.q[i1 - 1] + (druck_2.q[i2 - 1] - 
		druck_2.q[i1 - 1]) * (expe_2.phi[j - 1] - bl3_1.fi[i1 - 1]) / 
		(bl3_1.fi[i2 - 1] - bl3_1.fi[i1 - 1]);
/*# 720 "climaf.f"*/
	hlx[j - 1] = bl10_1.hl[i1 - 1] + (bl10_1.hl[i2 - 1] - bl10_1.hl[i1 - 
		1]) * (expe_2.phi[j - 1] - bl3_1.fi[i1 - 1]) / (bl3_1.fi[i2 - 
		1] - bl3_1.fi[i1 - 1]);
/*# 721 "climaf.f"*/
	druckx_1.hux[j - 1] = bl10_1.hu[i1 - 1] + (bl10_1.hu[i2 - 1] - 
		bl10_1.hu[i1 - 1]) * (expe_2.phi[j - 1] - bl3_1.fi[i1 - 1]) / 
		(bl3_1.fi[i2 - 1] - bl3_1.fi[i1 - 1]);
/*# 722 "climaf.f"*/
	druckx_1.bex[j - 1] = druck_2.bew[i1 - 1] + (druck_2.bew[i2 - 1] - 
		druck_2.bew[i1 - 1]) * (expe_2.phi[j - 1] - bl3_1.fi[i1 - 1]) 
		/ (bl3_1.fi[i2 - 1] - bl3_1.fi[i1 - 1]);
/*# 723 "climaf.f"*/
	druckx_1.apx[j - 1] = ap[i1 - 1] + (ap[i2 - 1] - ap[i1 - 1]) * (
		expe_2.phi[j - 1] - bl3_1.fi[i1 - 1]) / (bl3_1.fi[i2 - 1] - 
		bl3_1.fi[i1 - 1]);
/*# 724 "climaf.f"*/
	druckx_1.lpx[j - 1] = druck_2.lp[i1 - 1] + (druck_2.lp[i2 - 1] - 
		druck_2.lp[i1 - 1]) * (expe_2.phi[j - 1] - bl3_1.fi[i1 - 1]) /
		 (bl3_1.fi[i2 - 1] - bl3_1.fi[i1 - 1]);
/*# 725 "climaf.f"*/
	druckx_1.evx[j - 1] = druck_2.eva[i1 - 1] + (druck_2.eva[i2 - 1] - 
		druck_2.eva[i1 - 1]) * (expe_2.phi[j - 1] - bl3_1.fi[i1 - 1]) 
		/ (bl3_1.fi[i2 - 1] - bl3_1.fi[i1 - 1]);
/*# 726 "climaf.f"*/
	druckx_1.px[j - 1] = druck_2.p[i1 - 1] + (druck_2.p[i2 - 1] - 
		druck_2.p[i1 - 1]) * (expe_2.phi[j - 1] - bl3_1.fi[i1 - 1]) / 
		(bl3_1.fi[i2 - 1] - bl3_1.fi[i1 - 1]);
/*# 727 "climaf.f"*/
	druckx_1.flx[j - 1] = fl[i1 - 1] + (fl[i2 - 1] - fl[i1 - 1]) * (
		expe_2.phi[j - 1] - bl3_1.fi[i1 - 1]) / (bl3_1.fi[i2 - 1] - 
		bl3_1.fi[i1 - 1]);
/*# 728 "climaf.f"*/
	druckx_1.fox[j - 1] = ausg1_1.flusso[i1 - 1] + (ausg1_1.flusso[i2 - 1]
		 - ausg1_1.flusso[i1 - 1]) * (expe_2.phi[j - 1] - bl3_1.fi[i1 
		- 1]) / (bl3_1.fi[i2 - 1] - bl3_1.fi[i1 - 1]);
/*# 730 "climaf.f"*/
	druckx_1.fax[j - 1] = ausg1_1.flussa[i1 - 1] + (ausg1_1.flussa[i2 - 1]
		 - ausg1_1.flussa[i1 - 1]) * (expe_2.phi[j - 1] - bl3_1.fi[i1 
		- 1]) / (bl3_1.fi[i2 - 1] - bl3_1.fi[i1 - 1]);
/*# 732 "climaf.f"*/
	druckx_1.fqx[j - 1] = ausg1_1.flussq[i1 - 1] + (ausg1_1.flussq[i2 - 1]
		 - ausg1_1.flussq[i1 - 1]) * (expe_2.phi[j - 1] - bl3_1.fi[i1 
		- 1]) / (bl3_1.fi[i2 - 1] - bl3_1.fi[i1 - 1]);
/*# 734 "climaf.f"*/
/* L32: */
    }

/*     OBERE SCHRANKE FUER RH */
/*     DO 15 I=1,M */
/*       GLIEDER(I,12) = 1.D3*SPRUNG(RH(I)-0.91,0.5D-2) */
/*  15 CONTINUE */
/*# 740 "climaf.f"*/
    for (j = 1; j <= 2; ++j) {
/*# 741 "climaf.f"*/
	glied[j + 198] = 0.;
/*# 742 "climaf.f"*/
	for (i = 1; i <= 180; ++i) {
/*# 743 "climaf.f"*/
/* L14: */
	    glied[j + 198] += ausg_1.glieder[i + (j + 11) * 180 - 181];
	}
    }

/*     LEAST SQUARES: Z.B. BEDEUTET DAS GEWICHT 0,02, */
/*    DA# BEI 2% FEHLER DER BETREFFENDEN GR÷#E EIN BEITRAG ZUR ZIELFKT VON
*/
/*    1*SZC(I) ENTSTEHT. DER BEITRAG WIRD IN DEN VEKTOR GLIED AUFGENOMMEN,
 DEN*/
/*     IMSL-ROUTINE DBCLSJ BENOETIGT */
/*# 749 "climaf.f"*/
    for (i = 1; i <= 18; ++i) {
/*# 750 "climaf.f"*/
	ausg_1.glieder[i - 1] = (expe_2.ta1[i - 1] - druckx_1.tax[i - 1]) * 
		szc[i - 1] / g[0];
/*# 751 "climaf.f"*/
	ausg_1.glieder[i + 179] = (expe_2.to1[i - 1] - druckx_1.tox[i - 1]) * 
		szc[i - 1] / g[0];
/*# 752 "climaf.f"*/
	ausg_1.glieder[i + 359] = (1. - druckx_1.qx[i - 1] / expe_2.q1[i - 1])
		 * szc[i - 1] / g[1];
/*# 753 "climaf.f"*/
	ausg_1.glieder[i + 539] = (1. - druckx_1.bex[i - 1] / expe_2.bew1[i - 
		1]) * szc[i - 1] / g[4];
/*# 754 "climaf.f"*/
	ausg_1.glieder[i + 719] = (1. - druckx_1.apx[i - 1] / expe_2.ap1[i - 
		1]) * szc[i - 1] / g[3];
/*# 755 "climaf.f"*/
	ausg_1.glieder[i + 899] = (expe_2.flusso1[i - 1] - druckx_1.fox[i - 1]
		) * szc[i - 1] / g[2];
/*# 756 "climaf.f"*/
	ausg_1.glieder[i + 1439] = (expe_2.eva1[i - 1] - druckx_1.evx[i - 1]) 
		* szc[i - 1] / g[4];
/*# 757 "climaf.f"*/
	ausg_1.glieder[i + 1079] = (expe_2.hu1[i - 1] - druckx_1.hux[i - 1]) *
		 szc[i - 1] / g[5];
/*# 758 "climaf.f"*/
	ausg_1.glieder[i + 1259] = (1. - druckx_1.lpx[i - 1] / expe_2.lp1[i - 
		1]) * szc[i - 1] / g[3];
/*# 759 "climaf.f"*/
	ausg_1.glieder[i + 1619] = (expe_2.p1[i - 1] - druckx_1.px[i - 1]) * 
		szc[i - 1] / g[4];
/*# 760 "climaf.f"*/
	ausg_1.glieder[i + 1799] = (expe_2.flussg1[i - 1] - druckx_1.flx[i - 
		1]) * szc[i - 1] / g[2];
/*# 761 "climaf.f"*/
/* L20: */
    }

/*# 763 "climaf.f"*/
    for (j = 1; j <= 11; ++j) {
/*# 764 "climaf.f"*/
	for (i = 1; i <= 18; ++i) {
/*# 765 "climaf.f"*/
/* L17: */
	    glied[(j - 1) * 18 + i] = ausg_1.glieder[i + j * 180 - 181];
	}
    }

/*# 767 "climaf.f"*/
    summe_(&c__180, druck_2.p, &pg);
/*# 768 "climaf.f"*/
    summe_(&c__180, druck_2.ta, &tag);
/*# 769 "climaf.f"*/
    summe_(&c__180, druck_2.ts, &tsg);
/*# 770 "climaf.f"*/
    summe_(&c__180, druck_2.q, &qg);
/*# 771 "climaf.f"*/
    summe_(&c__180, ausg2_1.absa, &absag);
/*# 772 "climaf.f"*/
    summe_(&c__180, druck_2.bew, &bewg);
/*# 773 "climaf.f"*/
    summe_(&c__180, ausg2_1.abso, &absog);
/*# 774 "climaf.f"*/
    summe_(&c__180, ausg2_1.albw, &albwg);
/*# 775 "climaf.f"*/
    summe_(&c__180, bl10_1.hl, &hlg);
/*# 776 "climaf.f"*/
    summe_(&c__180, bl10_1.hu, &hug);
/*# 777 "climaf.f"*/
    summe_(&c__180, ausg4_1.tau, &tauh);
/*# 778 "climaf.f"*/
    summe_(&c__180, ausg4_1.tau, &tauh);

/* INTEGRAL CONSTRAINTS */

/*# 782 "climaf.f"*/
    apg = 1. - (absag + absog) / 340.;
/*# 783 "climaf.f"*/
    ausg_1.gha = (druck_2.hadley[1] - 30.) / .1;
/*# 784 "climaf.f"*/
    ausg_1.gap = (apg - .3) / .01;
/*# 785 "climaf.f"*/
    ausg_1.gta = (tag - 14.77) / .05;
/*# 786 "climaf.f"*/
    ausg_1.gp = (pg - 1.) / .02;
/*# 787 "climaf.f"*/
    gto = (tsg - 17.54) / .05;
/*# 788 "climaf.f"*/
    ausg_1.gtau = (tauh - .2) / .005;
/*# 789 "climaf.f"*/
    ausg_1.gbew = (bewg - .6) / .01;
/*     GHL  = (HL(90)-1.4)/0.01 */
/*     GHU  = (HU(90)-6.0D0)/0.02 */
/*# 792 "climaf.f"*/
    d_1 = bl10_1.hu[0] + .5 - bl10_1.hu[89];
    ausg_1.ghu = sprung_(&d_1, &c_b148) * 100.;
/*     QUOT= (ABSAG/ABSOG-0.44)/0.02 */

/*    PARAMETEREINSCHR<SIGMA>NKUNGEN, SOWEIT DIE IM HAUPTPROGRAMM GESETZTE
N*/
/*     NICHT AUSREICHEN */
/*     SONSTIGE CONSTRAINTS: EINIGE WERTE SIND BESONDERS */
/*    GEFRAGT, DESHALB WERDEN STRAFEN VERHAENGT, WENN DIESE WERTE NICHT ER
REICHT*/
/*     WERDEN */
/*     NIEDERSCHLAG MITTL. BREITEN */
/*# 801 "climaf.f"*/
    d_1 = 1.25 - druckx_1.px[4];
    ausg_1.f1[0] = sprung_(&d_1, &c_b148) * 100.;
/*     TOP */
/*# 803 "climaf.f"*/
    d_1 = 10. - coeffi_4.y[17];
    ausg_1.f1[1] = sprung_(&d_1, &c_b148) * 1e3;
/*     NIEDERSCHLAG EQUATOR */
/*# 805 "climaf.f"*/
    d_1 = 1.8 - druckx_1.px[9];
    ausg_1.f1[2] = sprung_(&d_1, &c_b148) * 100.;
/*     CO2 */
/*# 807 "climaf.f"*/
    d_1 = .059 - coeffi_4.y[20];
    d_2 = coeffi_4.y[20] - .072;
    ausg_1.f1[3] = (sprung_(&d_1, &c_b148) + sprung_(&d_2, &c_b148)) * 1e3;
/*     LAPS */
/*# 810 "climaf.f"*/
    d_1 = coeffi_4.y[32] - 7.;
    d_2 = 6. - coeffi_4.y[32];
    ausg_1.f1[4] = (sprung_(&d_1, &c_b148) + sprung_(&d_2, &c_b148)) * 1e3;
/*     RSURF */
/*# 813 "climaf.f"*/
    d_1 = coeffi_4.y[25] - .18;
    ausg_1.f1[5] = sprung_(&d_1, &c_b148) * 100.;
/*     ALBEDO LAND */
/*# 815 "climaf.f"*/
    d_1 = .15 - coeffi_4.y[31];
    d_2 = coeffi_4.y[31] - .2;
    ausg_1.f1[6] = (sprung_(&d_1, &c_b148) + sprung_(&d_2, &c_b148)) * 100.;
/*     ALBEDO WOLKEN GLOBAL */
/*     F1(8) = 1.D2*SPRUNG(0.40D0-ALBWG,0.1D-2) */
/*     GAM */
/*     F1(9) = 1.D3*(SPRUNG(0.83-Y(20),0.1D-2) */
/*    +                  +SPRUNG(Y(20)-1.01,0.1D-2)) */
/*     BETA (FEUCHTEABNAHME) */
/*# 823 "climaf.f"*/
    d_1 = coeffi_4.y[29] - .37;
    ausg_1.f1[9] = sprung_(&d_1, &c_b148) * 1e3;
/*     ALFA1 */
/*     F1(11) = 1.D3*(SPRUNG(0.075-Y(22),0.1D-2) */
/*    +                  +SPRUNG(Y(22)-0.10,0.1D-2)) */
/*     FLUSSQ MITTL. BREITEN */
/*# 828 "climaf.f"*/
    d_1 = (druckx_1.fqx[3] + 1e15) / g[2];
    ausg_1.f1[10] = sprung_(&d_1, &c_b160) * 50.;
/*     HL (ROSS-BREITEN) */
/*# 830 "climaf.f"*/
    ausg_1.f1[11] = (bl10_1.hl[89] + .5 - bl10_1.hl[119]) / .02;
/*     BEDINGUNG BEWOELKUNG AEQUATOR */
/*# 832 "climaf.f"*/
    d_1 = .6 - druck_2.bew[89];
    ausg_1.f1[12] = sprung_(&d_1, &c_b148) * 100.;
/*     ZUSATZ */
/*# 834 "climaf.f"*/
    zusatz = 0.;
/*# 835 "climaf.f"*/
    for (i = 1; i <= 13; ++i) {
/*# 836 "climaf.f"*/
/* L120: */
/* Computing 2nd power */
	d_1 = ausg_1.f1[i - 1];
	zusatz += d_1 * d_1;
    }
/*# 837 "climaf.f"*/
    glied[201] = ausg_1.gta;
/*# 838 "climaf.f"*/
    glied[202] = ausg_1.gbew;
/*# 839 "climaf.f"*/
    glied[203] = ausg_1.gha;
/*# 840 "climaf.f"*/
    glied[204] = ausg_1.gp;
/*     GLIED(LL+7) = GTO */
/*# 842 "climaf.f"*/
    glied[206] = ausg_1.gtau;
/*# 843 "climaf.f"*/
    glied[207] = ausg_1.gap;
/*# 844 "climaf.f"*/
    glied[208] = ausg_1.quot;
/*# 845 "climaf.f"*/
    glied[209] = ausg_1.ghl;
/*# 846 "climaf.f"*/
    glied[210] = ausg_1.ghu;
/*# 847 "climaf.f"*/
    for (i = 1; i <= 13; ++i) {
/*# 848 "climaf.f"*/
/* L121: */
	glied[i + 210] = ausg_1.f1[i - 1];
    }


/* SKALIERUNG */
/*# 852 "climaf.f"*/
    for (i = 1; i <= 223; ++i) {
/*# 853 "climaf.f"*/
/* L23: */
	glied[i] *= .01;
    }
/*# 854 "climaf.f"*/
    *fc = 0.;
/*# 855 "climaf.f"*/
    for (i = 1; i <= 180; ++i) {
/*# 856 "climaf.f"*/
	gl = 0.;
/*# 857 "climaf.f"*/
	for (j = 1; j <= 13; ++j) {
/*# 858 "climaf.f"*/
/* L22: */
/* Computing 2nd power */
	    d_1 = ausg_1.glieder[i + j * 180 - 181];
	    gl += d_1 * d_1;
	}
/*# 859 "climaf.f"*/
/* L24: */
	*fc += gl;
    }
/*# 860 "climaf.f"*/
/* Computing 2nd power */
    d_1 = ausg_1.gha;
/* Computing 2nd power */
    d_2 = ausg_1.gap;
/* Computing 2nd power */
    d_3 = ausg_1.gp;
/* Computing 2nd power */
    d_4 = ausg_1.gta;
/* Computing 2nd power */
    d_5 = ausg_1.gtau;
/* Computing 2nd power */
    d_6 = ausg_1.gq;
/* Computing 2nd power */
    d_7 = ausg_1.quot;
/* Computing 2nd power */
    d_8 = ausg_1.ghl;
/* Computing 2nd power */
    d_9 = ausg_1.ghu;
/* Computing 2nd power */
    d_10 = ausg_1.gbew;
    quad = d_1 * d_1 + d_2 * d_2 + d_3 * d_3 + d_4 * d_4 + d_5 * d_5 + d_6 * 
	    d_6 + d_7 * d_7 + d_8 * d_8 + d_9 * d_9 + d_10 * d_10;
/*# 862 "climaf.f"*/
    *fc = *fc + quad + zusatz;

/*# 864 "climaf.f"*/
    return 0;
/*# 865 "climaf.f"*/
} /* funct_ */

/* === */

/*# 868 "climaf.f"*/
/* Subroutine */ int eingabe_(doublereal *xc, doublereal *yvec)
{
    /* Initialized data */

    static doublereal cland[4] = { .270232222982,.305149369507,.0808488720115,
	    .0831306019308 };
    static doublereal hoch[4] = { .631862171505,.496757316274,-.222806946035,
	    -.031034731623 };
    static doublereal caa = 1e7;
    static doublereal coo = 2e8;
    static doublereal cpp = 1e3;
    static doublereal all = 2.5e6;
    static doublereal sun[5] = { 1.,-.477,-.045,.008,.014 };

    /* System generated locals */
    doublereal d_1;

    /* Builtin functions */
    double atan(doublereal), cos(doublereal), sin(doublereal), exp(doublereal)
	    ;

    /* Local variables */
    static doublereal albl, ydat[540], corr;
    extern doublereal sump_(doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal xzwi[180];
    static integer i, j;
    static doublereal gsued, gnord, upper, rsurf, hadkof;
    extern /* Subroutine */ int legend_(doublereal *, integer *, doublereal *)
	    ;
    static integer ij;
    extern /* Subroutine */ int eingab1_(doublereal *, doublereal *);
    static doublereal polzwi[1800]	/* was [180][10] */, pol[1800]	/* 
	    was [180][10] */, dxx, top, tos;


/*  WIRD NUR ZU ANFANG GERUFEN */

/*# 872 "climaf.f"*/
/*# 873 "climaf.f"*/
/*# 874 "climaf.f"*/
/*# 875 "climaf.f"*/
/*# 876 "climaf.f"*/


/*# 880 "climaf.f"*/
/*# 881 "climaf.f"*/
/*# 883 "climaf.f"*/
/*# 884 "climaf.f"*/
/*# 885 "climaf.f"*/
/*# 886 "climaf.f"*/
/*# 888 "climaf.f"*/
/*# 890 "climaf.f"*/
/*# 891 "climaf.f"*/
/*# 892 "climaf.f"*/
/*# 893 "climaf.f"*/


/*# 896 "climaf.f"*/
    /* Parameter adjustments */
    --yvec;
    --xc;

    /* Function Body */
/*# 898 "climaf.f"*/
/*# 900 "climaf.f"*/
/*# 901 "climaf.f"*/

/*     STATEMENT FUNCTIONS */

/*# 905 "climaf.f"*/

/* ********************************** */


/*# 910 "climaf.f"*/
    transf_1.tab = -10.;
/*# 911 "climaf.f"*/
    transf_1.tae = 10.;
/*# 912 "climaf.f"*/
    transf_1.tsb = -10.;
/*# 913 "climaf.f"*/
    transf_1.tse = 10.;
/*# 914 "climaf.f"*/
    transf_1.rhb = .5;
/*# 915 "climaf.f"*/
    transf_1.rhe = 1.;

/*# 917 "climaf.f"*/
    bl11_1.ata = atan(1.);
/*# 918 "climaf.f"*/
    bl11_1.pi = bl11_1.ata * 4;
/*# 919 "climaf.f"*/
    bl3_1.dx = bl11_1.pi / 180;
/*# 920 "climaf.f"*/
    dxx = bl3_1.dx;
/*# 921 "climaf.f"*/
    for (i = 1; i <= 90; ++i) {
/*# 922 "climaf.f"*/
	j = 180 - i + 1;
/*# 923 "climaf.f"*/
	xzwi[i - 1] = -bl3_1.dx * (90 - i + 1);
/*# 924 "climaf.f"*/
	xzwi[j - 1] = -xzwi[i - 1] - bl3_1.dx;
/*# 925 "climaf.f"*/
	bl3_1.xst[i - 1] = -bl3_1.dx * (90 - i + .5);
/*# 926 "climaf.f"*/
	bl3_1.xst[j - 1] = -bl3_1.xst[i - 1];
/*# 927 "climaf.f"*/
	bl3_1.fi[i - 1] = bl3_1.xst[i - 1] * 180. / bl11_1.pi;
/*# 928 "climaf.f"*/
	bl3_1.fi[j - 1] = -bl3_1.fi[i - 1];
/*# 929 "climaf.f"*/
	bl3_1.cosm[i - 1] = cos(xzwi[i - 1]);
/*# 930 "climaf.f"*/
	bl3_1.cosm[j - 1] = cos(xzwi[j - 1]);
/*# 931 "climaf.f"*/
	bl3_1.sinm[i - 1] = sin(xzwi[i - 1]);
/*# 932 "climaf.f"*/
	bl3_1.sinm[j - 1] = sin(xzwi[j - 1]);
/*# 933 "climaf.f"*/
	bl3_1.zc[i - 1] = cos(bl3_1.xst[i - 1]);
/*# 934 "climaf.f"*/
	bl3_1.zc[j - 1] = bl3_1.zc[i - 1];
/*# 935 "climaf.f"*/
	bl3_1.zs[i - 1] = sin(bl3_1.xst[i - 1]);
/*# 936 "climaf.f"*/
	bl3_1.zs[j - 1] = -bl3_1.zs[i - 1];
/*# 937 "climaf.f"*/
/* L19: */
    }


/* +++++++++++++++++++++++++++++++++++++++++++ */
/*# 941 "climaf.f"*/
    eingab1_(trans_2.y, ydat);
/* +++++++++++++++++++++++++++++++++++++++++++ */

/*# 944 "climaf.f"*/
    for (i = 1; i <= 180; ++i) {
/*# 945 "climaf.f"*/
	bl5_3.rh1[i - 1] = ydat[i - 1];
/*# 946 "climaf.f"*/
	bl5_3.ta1[i - 1] = ydat[i + 179];
/*# 947 "climaf.f"*/
/* L40: */
	bl5_3.ts1[i - 1] = ydat[i + 359];
    }


/*     MAPPING OF YDAT ONTO (-1,+1) */

/*# 952 "climaf.f"*/
    for (i = 1; i <= 180; ++i) {
/*# 953 "climaf.f"*/
	yvec[i * 3 - 2] = (bl5_3.rh1[i - 1] * 2 - (transf_1.rhe + 
		transf_1.rhb)) / (transf_1.rhe - transf_1.rhb);
/*# 954 "climaf.f"*/
	yvec[i * 3 - 1] = (bl5_3.ta1[i - 1] * 2 - (bl5_3.ta1[i - 1] * 2 + 
		transf_1.tab + transf_1.tae)) / (transf_1.tae - transf_1.tab);

/*# 955 "climaf.f"*/
	yvec[i * 3] = (bl5_3.ts1[i - 1] * 2 - (bl5_3.ts1[i - 1] * 2 + 
		transf_1.tsb + transf_1.tse)) / (transf_1.tse - transf_1.tsb);

/*# 956 "climaf.f"*/
/* L55: */
    }

/*  NEUE ZUORDNUNG FÜR EINIGE PARAMETER */

/*# 960 "climaf.f"*/
    bl9_1.va = trans_2.y[0];
/*# 961 "climaf.f"*/
    bl9_1.vq = trans_2.y[1];
/*# 962 "climaf.f"*/
    bl9_1.da = trans_2.y[2];
/*# 963 "climaf.f"*/
    bl9_1.dq[0] = trans_2.y[3];
/*# 964 "climaf.f"*/
    bl9_1.dq[1] = trans_2.y[4];
/*# 965 "climaf.f"*/
    bl9_1.dw[0] = trans_2.y[5];
/*# 966 "climaf.f"*/
    bl9_1.dw[1] = trans_2.y[6];
/*# 967 "climaf.f"*/
    bl12_1.pc[0] = trans_2.y[7];
/*# 968 "climaf.f"*/
    bl12_1.pc[1] = trans_2.y[8];
/*# 969 "climaf.f"*/
    bl4_1.lam[0] = trans_2.y[9];
/*# 970 "climaf.f"*/
    bl4_1.lam[1] = trans_2.y[10];
/*# 971 "climaf.f"*/
    bl12_1.rmin = trans_2.y[11];
/*# 972 "climaf.f"*/
    bl12_1.rcrit = trans_2.y[12];
/*# 973 "climaf.f"*/
    bl10_2.unten = trans_2.y[13];
/*# 974 "climaf.f"*/
    bl10_2.thick = trans_2.y[14];
/*# 975 "climaf.f"*/
    bl10_2.wolk1 = trans_2.y[15];
/*# 976 "climaf.f"*/
    bl10_2.wolk2 = trans_2.y[16];
/*# 977 "climaf.f"*/
    top = trans_2.y[17];
/*# 978 "climaf.f"*/
    upper = trans_2.y[18];
/*# 979 "climaf.f"*/
    bl10_2.gam = trans_2.y[19];
/*# 980 "climaf.f"*/
    bl10_2.cohle = trans_2.y[20];
/*# 981 "climaf.f"*/
    bl10_2.alf1 = trans_2.y[21];
/*# 982 "climaf.f"*/
    bl1_1.alf2 = trans_2.y[22];
/*# 983 "climaf.f"*/
    bl10_2.kap1 = trans_2.y[23];
/*# 984 "climaf.f"*/
    bl4_1.eisbed = trans_2.y[24];
/*# 985 "climaf.f"*/
    rsurf = trans_2.y[25];
/*# 986 "climaf.f"*/
    bl4_1.dice = trans_2.y[26];
/*# 987 "climaf.f"*/
    bl1_1.sonne = trans_2.y[27];
/*# 988 "climaf.f"*/
    hadkof = trans_2.y[28];
/*# 989 "climaf.f"*/
    bl12_1.beta = trans_2.y[29];
/*# 990 "climaf.f"*/
    bl12_1.w0 = trans_2.y[30];
/*# 991 "climaf.f"*/
    albl = trans_2.y[31];
/*# 992 "climaf.f"*/
    bl10_2.laps = trans_2.y[32];


/*# 995 "climaf.f"*/
    bl10_2.kap2 = bl10_2.kap1 + .03;
/*# 996 "climaf.f"*/
    bl3_1.hadk = hadkof * bl10_2.laps;
/*# 997 "climaf.f"*/
    bl12_1.exbeta = exp(-bl12_1.beta);

/*# 999 "climaf.f"*/
    for (i = 1; i <= 33; ++i) {
/*# 1000 "climaf.f"*/
/* L80: */
	xc[i] = 0.;
    }

/*      WRITE(66,132) */
/*      WRITE(66,102) (NAME(I),Y(I),I=1,NX) */



/* *************************************************** */
/* CONSTANTEN */
/*# 1009 "climaf.f"*/
    bl11_1.cq = 3e3;
/*# 1010 "climaf.f"*/
    bl11_1.re = 6.37e6;
/*# 1011 "climaf.f"*/
    bl11_1.fok = 86400.;
/*# 1012 "climaf.f"*/
    bl11_1.tf = 273.;
/*# 1013 "climaf.f"*/
    bl11_1.tanf = -bl4_1.dice;
/*# 1014 "climaf.f"*/
    bl11_1.tend = bl4_1.dice;
/*# 1015 "climaf.f"*/
    bl11_1.ca = caa / bl11_1.fok;
/*# 1016 "climaf.f"*/
    bl11_1.co = coo / bl11_1.fok;
/*# 1017 "climaf.f"*/
    bl11_1.ci = bl11_1.co / 50.;
/*# 1018 "climaf.f"*/
    bl11_1.cl = bl11_1.ca / 2.;
/*# 1019 "climaf.f"*/
    bl11_1.cp = cpp / bl11_1.fok;
/*# 1020 "climaf.f"*/
    bl11_1.al = all / bl11_1.fok;
/*# 1021 "climaf.f"*/
    bl11_1.cofda = bl11_1.pi * 2 * bl11_1.fok * bl11_1.ca;
/*# 1022 "climaf.f"*/
    bl11_1.cofdo = bl11_1.pi * 2 * bl11_1.fok * bl11_1.co;
/*# 1023 "climaf.f"*/
    bl11_1.cofdq = bl11_1.pi * 2 * bl11_1.fok * bl11_1.al * bl11_1.cq;
/*# 1024 "climaf.f"*/
/* Computing 2nd power */
    d_1 = bl11_1.re;
    bl11_1.cof = bl11_1.pi * 2 * (d_1 * d_1);
/*# 1025 "climaf.f"*/
    bl11_1.cofat = bl11_1.cofda / bl11_1.cof;
/*# 1026 "climaf.f"*/
    bl11_1.cofoz = bl11_1.cofdo / bl11_1.cof;
/*# 1027 "climaf.f"*/
    bl11_1.coffe = bl11_1.cofdq / bl11_1.cof;


/*# 1030 "climaf.f"*/
    for (i = 1; i <= 180; ++i) {
/*# 1031 "climaf.f"*/
	for (j = 1; j <= 10; ++j) {
/*# 1032 "climaf.f"*/
	    legend_(&bl3_1.sinm[i - 1], &j, &polzwi[i + j * 180 - 181]);
/*# 1033 "climaf.f"*/
/* L84: */
	    legend_(&bl3_1.zs[i - 1], &j, &pol[i + j * 180 - 181]);
	}
/*# 1034 "climaf.f"*/
/* L83: */
    }

/*# 1036 "climaf.f"*/
    for (i = 1; i <= 90; ++i) {
/*# 1037 "climaf.f"*/
	j = 180 - i + 1;
/*# 1038 "climaf.f"*/
	tos = sun[0];
/*# 1039 "climaf.f"*/
	for (ij = 1; ij <= 4; ++ij) {
/*# 1040 "climaf.f"*/
/* L14: */
	    tos += pol[i + ij * 360 - 181] * sun[ij];
	}
/*# 1041 "climaf.f"*/
	bl1_1.soleil[i - 1] = tos;
/*# 1042 "climaf.f"*/
	bl1_1.soleil[j - 1] = bl1_1.soleil[i - 1];
/*# 1043 "climaf.f"*/
/* L12: */
    }

/*# 1045 "climaf.f"*/
    for (i = 1; i <= 180; ++i) {
/*# 1046 "climaf.f"*/
	tos = cland[0];
/*# 1047 "climaf.f"*/
	for (ij = 1; ij <= 3; ++ij) {
/*# 1048 "climaf.f"*/
/* L20: */
	    tos += pol[i + ij * 180 - 181] * cland[ij];
	}
/*# 1049 "climaf.f"*/
	d_1 = bl3_1.fi[i - 1] + 75.;
	gsued = 1. - sump_(&d_1, &c_b178, &c_b179, &c_b180);
/*# 1050 "climaf.f"*/
	d_1 = 75. - bl3_1.fi[i - 1];
	gnord = sump_(&d_1, &c_b178, &c_b179, &c_b180);
/*# 1051 "climaf.f"*/
	bl3_1.fland[i - 1] = gnord * tos + gsued + 1e-20;

/*# 1053 "climaf.f"*/
	tos = cland[0];
/*# 1054 "climaf.f"*/
	for (ij = 1; ij <= 3; ++ij) {
/*# 1055 "climaf.f"*/
/* L24: */
	    tos += polzwi[i + ij * 180 - 181] * cland[ij];
	}
/*# 1056 "climaf.f"*/
	d_1 = xzwi[i - 1] * 180. / bl11_1.pi + 75.;
	gsued = 1. - sump_(&d_1, &c_b178, &c_b179, &c_b180);
/*# 1057 "climaf.f"*/
	d_1 = 75. - xzwi[i - 1] * 180. / bl11_1.pi;
	gnord = sump_(&d_1, &c_b178, &c_b179, &c_b180);
/*# 1058 "climaf.f"*/
	bl3_1.xland[i - 1] = gnord * tos + gsued + 1e-20;

/*# 1060 "climaf.f"*/
	tos = hoch[0];
/*# 1061 "climaf.f"*/
	for (ij = 1; ij <= 3; ++ij) {
/*# 1062 "climaf.f"*/
/* L22: */
	    tos += pol[i + ij * 180 - 181] * hoch[ij];
	}
/*# 1063 "climaf.f"*/
	d_1 = bl3_1.fi[i - 1] + 75.;
	gsued = 1. - sump_(&d_1, &c_b178, &c_b179, &c_b180);
/*# 1064 "climaf.f"*/
/* Computing 2nd power */
	d_1 = bl3_1.fi[i - 1] / 35. - 1.;
	corr = .3 / (d_1 * d_1 * 10. + 1.) + .2;
/*# 1065 "climaf.f"*/
	bl3_1.height[i - 1] = tos * corr + gsued * 2.272;
/*# 1066 "climaf.f"*/
	bl12_1.qred[i - 1] = exp(-bl12_1.beta * bl3_1.height[i - 1]);

/*# 1068 "climaf.f"*/
	tos = hoch[0];
/*# 1069 "climaf.f"*/
	for (ij = 1; ij <= 3; ++ij) {
/*# 1070 "climaf.f"*/
/* L25: */
	    tos += polzwi[i + ij * 180 - 181] * hoch[ij];
	}
/*# 1071 "climaf.f"*/
	d_1 = xzwi[i - 1] * 180. / bl11_1.pi + 75.;
	gsued = 1. - sump_(&d_1, &c_b178, &c_b179, &c_b180);
/*# 1072 "climaf.f"*/
/* Computing 2nd power */
	d_1 = xzwi[i - 1] * 180. / bl11_1.pi / 35. - 1.;
	corr = .3 / (d_1 * d_1 * 10. + 1.) + .2;
/*# 1074 "climaf.f"*/
	bl3_1.xheight[i - 1] = tos * corr + gsued * 2.272;

/*# 1076 "climaf.f"*/
/* L21: */
    }

/*# 1078 "climaf.f"*/
    for (i = 1; i <= 90; ++i) {
/*# 1079 "climaf.f"*/
	j = 180 - i + 1;
/*# 1080 "climaf.f"*/
/* Computing 2nd power */
	d_1 = bl3_1.zs[i - 1];
	bl10_2.zk[i - 1] = d_1 * d_1;
/*# 1081 "climaf.f"*/
	bl10_2.zk[j - 1] = bl10_2.zk[i - 1];
/*# 1082 "climaf.f"*/
	bl1_1.tropos[i - 1] = top - (top - 10.) * 3. * bl10_2.zk[i - 1];
/*# 1083 "climaf.f"*/
	bl1_1.tropos[j - 1] = bl1_1.tropos[i - 1];
/*# 1084 "climaf.f"*/
	bl1_1.eisfrei[i - 1] = rsurf * (1. - bl1_1.soleil[i - 1] * .5);
/*# 1085 "climaf.f"*/
	bl1_1.eisfrei[j - 1] = bl1_1.eisfrei[i - 1];
/*# 1086 "climaf.f"*/
	bl3_1.gradc[i - 1] = -bl3_1.hadk * (bl3_1.zc[i - 1] / bl3_1.zs[i - 1])
		;
/*# 1087 "climaf.f"*/
	bl3_1.gradc[j - 1] = -bl3_1.gradc[i - 1];
/*       SWI(I) = SUMP(DABS(FI(I))-70.0D0,0.5D0,-3.0D0,3.0D0) */
/*       SWI(J) = SWI(I) */
/*       EISF(I) = ALBL*(1.0D0-SWI(I))+ALBE*SWI(I) */
/*# 1091 "climaf.f"*/
	bl1_1.eisf[i - 1] = albl;
/*# 1092 "climaf.f"*/
	bl1_1.eisf[j - 1] = bl1_1.eisf[i - 1];
/*# 1093 "climaf.f"*/
	bl10_2.zkk[i - 1] = bl1_1.soleil[i - 1] * .5 / (1. - bl1_1.soleil[i - 
		1] * .5);
/*# 1094 "climaf.f"*/
	bl10_2.zkk[j - 1] = bl10_2.zkk[i - 1];
/*# 1095 "climaf.f"*/
/* L10: */
    }


/*# 1098 "climaf.f"*/
/* L132: */
/*# 1099 "climaf.f"*/
/* L102: */
/*# 1100 "climaf.f"*/
/* L110: */
/*# 1101 "climaf.f"*/
/* L111: */
/*# 1102 "climaf.f"*/
/* L108: */
/*# 1103 "climaf.f"*/
/* L109: */
/*# 1104 "climaf.f"*/
/* L121: */
/*# 1105 "climaf.f"*/
    return 0;
/*# 1106 "climaf.f"*/
} /* eingabe_ */

/* === */

/*# 1109 "climaf.f"*/
/* Subroutine */ int wolf_(doublereal *xc, doublereal *yvec, doublereal *fvec,
	 doublereal *fall)
{
    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static doublereal albl;
    static integer i, j;
    static doublereal upper, rsurf, hadkof;
    extern /* Subroutine */ int fcn_(doublereal *, doublereal *, doublereal *)
	    ;
    static doublereal top;

/* ZWISCHENGESCHALTETES PROGRAMM, NUR FUER OPTIMIERUNG */
/* CALLS FCN */

/*# 1113 "climaf.f"*/
/*# 1114 "climaf.f"*/
/*# 1115 "climaf.f"*/
/*# 1116 "climaf.f"*/

/*# 1118 "climaf.f"*/
/*# 1119 "climaf.f"*/

/*# 1121 "climaf.f"*/
/*# 1122 "climaf.f"*/
/*# 1124 "climaf.f"*/
/*# 1125 "climaf.f"*/
/*# 1126 "climaf.f"*/
/*# 1127 "climaf.f"*/
/*# 1129 "climaf.f"*/
/*# 1131 "climaf.f"*/
/*# 1132 "climaf.f"*/
/*# 1136 "climaf.f"*/
/*# 1137 "climaf.f"*/

/*     Y() PARAMETERS IN PHYSICAL SPACE */
/*     VARIATIONSBEREICH VON Y:  PLUS/MINUS DELTA*PSTART */
/*     VARIATIONSBEREICH VON XC: 2 */
/*     VERKLEINERUNG VON DELTA VERRINGERT DEN GRADIENTEN  BZGL. XC */
/*     DELTA KANN INDIVIDUELL ANGEPASST WERDEN, ENTSPRECHEND DEM */
/*     GEWUENSCHTEN BEREICH VON Y() */

/*# 1146 "climaf.f"*/
    /* Parameter adjustments */
    --fvec;
    --yvec;
    --xc;

    /* Function Body */
    for (i = 1; i <= 33; ++i) {
/*# 1147 "climaf.f"*/
/* L333: */
	trans_1.delta[i - 1] = .3;
    }
/*# 1148 "climaf.f"*/
    trans_1.delta[8] = .9;
/*# 1149 "climaf.f"*/
    for (i = 1; i <= 33; ++i) {
/*# 1150 "climaf.f"*/
/* L69: */
	coeffi_4.y[i - 1] = trans_1.yalt[i - 1] * (xc[i] * trans_1.delta[i - 
		1] + 1.);
    }

/*# 1152 "climaf.f"*/
    bl9_1.va = coeffi_4.y[0];
/*# 1153 "climaf.f"*/
    bl9_1.vq = coeffi_4.y[1];
/*# 1154 "climaf.f"*/
    bl9_1.da = coeffi_4.y[2];
/*# 1155 "climaf.f"*/
    bl9_1.dq[0] = coeffi_4.y[3];
/*# 1156 "climaf.f"*/
    bl9_1.dq[1] = coeffi_4.y[4];
/*# 1157 "climaf.f"*/
    bl9_1.dw[0] = coeffi_4.y[5];
/*# 1158 "climaf.f"*/
    bl9_1.dw[1] = coeffi_4.y[6];
/*# 1159 "climaf.f"*/
    bl12_1.pc[0] = coeffi_4.y[7];
/*# 1160 "climaf.f"*/
    bl12_1.pc[1] = coeffi_4.y[8];
/*# 1161 "climaf.f"*/
    bl4_1.lam[0] = coeffi_4.y[9];
/*# 1162 "climaf.f"*/
    bl4_1.lam[1] = coeffi_4.y[10];
/*# 1163 "climaf.f"*/
    bl12_1.rmin = coeffi_4.y[11];
/*# 1164 "climaf.f"*/
    bl12_1.rcrit = coeffi_4.y[12];
/*# 1165 "climaf.f"*/
    bl10_3.unten = coeffi_4.y[13];
/*# 1166 "climaf.f"*/
    bl10_3.thick = coeffi_4.y[14];
/*# 1167 "climaf.f"*/
    bl10_3.wolk1 = coeffi_4.y[15];
/*# 1168 "climaf.f"*/
    bl10_3.wolk2 = coeffi_4.y[16];
/*# 1169 "climaf.f"*/
    top = coeffi_4.y[17];
/*# 1170 "climaf.f"*/
    upper = coeffi_4.y[18];
/*# 1171 "climaf.f"*/
    bl10_3.gam = coeffi_4.y[19];
/*# 1172 "climaf.f"*/
    bl10_3.cohle = coeffi_4.y[20];
/*# 1173 "climaf.f"*/
    bl10_3.alf1 = coeffi_4.y[21];
/*# 1174 "climaf.f"*/
    bl1_1.alf2 = coeffi_4.y[22];
/*# 1175 "climaf.f"*/
    bl10_3.kap1 = coeffi_4.y[23];
/*# 1176 "climaf.f"*/
    bl4_1.eisbed = coeffi_4.y[24];
/*# 1177 "climaf.f"*/
    rsurf = coeffi_4.y[25];
/*# 1178 "climaf.f"*/
    bl4_1.dice = coeffi_4.y[26];
/*# 1179 "climaf.f"*/
    bl1_1.sonne = coeffi_4.y[27];
/*# 1180 "climaf.f"*/
    hadkof = coeffi_4.y[28];
/*# 1181 "climaf.f"*/
    bl12_1.beta = coeffi_4.y[29];
/*# 1182 "climaf.f"*/
    bl12_1.w0 = coeffi_4.y[30];
/*# 1183 "climaf.f"*/
    albl = coeffi_4.y[31];
/*# 1184 "climaf.f"*/
    bl10_3.laps = coeffi_4.y[32];

/*# 1186 "climaf.f"*/
    bl11_1.tanf = -bl4_1.dice;
/*# 1187 "climaf.f"*/
    bl11_1.tend = bl4_1.dice;
/*# 1188 "climaf.f"*/
    bl10_3.kap2 = bl10_3.kap1 + .03;
/*# 1189 "climaf.f"*/
    bl3_2.hadk = hadkof * bl10_3.laps;
/*# 1190 "climaf.f"*/
    bl10_3.pl = 34.15 / bl10_3.laps;
/*# 1191 "climaf.f"*/
    bl12_1.exbeta = exp(-bl12_1.beta);


/*# 1194 "climaf.f"*/
    for (i = 1; i <= 90; ++i) {
/*# 1195 "climaf.f"*/
	j = 180 - i + 1;
/*# 1196 "climaf.f"*/
	bl1_1.tropos[i - 1] = top - (top - 10.) * 3. * bl10_3.zk[i - 1];
/*# 1197 "climaf.f"*/
	bl1_1.eisfrei[i - 1] = rsurf * (1. - bl1_1.soleil[i - 1] * .5);
/*# 1198 "climaf.f"*/
	bl3_2.gradc[i - 1] = -bl3_2.hadk * (bl3_2.zc[i - 1] / bl3_2.zs[i - 1])
		;
/*# 1199 "climaf.f"*/
	bl1_1.eisf[i - 1] = albl;
/*       EISF(I) = ALBL*(1.0D0-SWI(I))+ALBE*SWI(I) */
/*# 1201 "climaf.f"*/
	bl1_1.tropos[j - 1] = bl1_1.tropos[i - 1];
/*# 1202 "climaf.f"*/
	bl1_1.eisfrei[j - 1] = bl1_1.eisfrei[i - 1];
/*# 1203 "climaf.f"*/
	bl3_2.gradc[j - 1] = -bl3_2.gradc[i - 1];
/*# 1204 "climaf.f"*/
	bl1_1.eisf[j - 1] = bl1_1.eisf[i - 1];
/*# 1205 "climaf.f"*/
/* L10: */
    }
/*# 1206 "climaf.f"*/
    for (i = 1; i <= 180; ++i) {
/*# 1207 "climaf.f"*/
/* L11: */
	bl12_1.qred[i - 1] = exp(-bl12_1.beta * bl3_2.height[i - 1]);
    }

/* +++++++++++++++++++++++++++++++++++++++ */
/*# 1210 "climaf.f"*/
    fcn_(&yvec[1], &fvec[1], fall);
/* +++++++++++++++++++++++++++++++++++++++++ */

/*# 1213 "climaf.f"*/
    return 0;
/*# 1214 "climaf.f"*/
} /* wolf_ */

/* === */

/*# 1217 "climaf.f"*/
/* Subroutine */ int fcn_(doublereal *y, doublereal *f, doublereal *fall)
{
    /* Initialized data */

    static doublereal sol = 340.;
    static doublereal null[180] = { 0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0. };
    static doublereal epst = .1;
    static doublereal epsb = .02;
    static doublereal bland = 2.;
    static doublereal umrech = 2.739726027;

    /* System generated locals */
    doublereal d_1, d_2, d_3;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    extern /* Subroutine */ int hadl_(doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *);
    static doublereal refl[180], bewl[180], qsta, qsti[180], qstl[180];
    extern doublereal sump_(doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal qsto[180], blam1[180], blam2[180], blam3, absaa[180];
    static integer i, k;
    static doublereal lamda[180], p[180], q[180], absal[180], eland[180], 
	    divfa[180], gradq[180], absol[180], albwl[180], absoo[180], divfo[
	    180];
    extern /* Subroutine */ int eisli_(doublereal *, doublereal *);
    static doublereal divfq[180], oland, albww[180], qstli[180];
    extern /* Subroutine */ int moist_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static doublereal quotl[180], quotw[180], la[180], lo[180], ql[180], 
	    gradta[180], ps[180], kappal[180], schalt[180], gradto[180], 
	    kappaw[180], rl, rw, fx, fy, fz;
    extern /* Subroutine */ int strahl_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal switch_[180], contrl[1080], rsonne, contrw[1080];
    extern doublereal sprung_(doublereal *, doublereal *);
    static doublereal had[2], taa[180], gra[180], ira[180], ref[180], hll[180]
	    , tal[180], irl[180], hul[180], hlw[180], tll[180], eisland, too[
	    180], huw[180], rla, rwa, tss[180];
    extern /* Subroutine */ int diskret_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static doublereal ewasser[180], owasser;


/*# 1219 "climaf.f"*/
/*# 1220 "climaf.f"*/
/*# 1221 "climaf.f"*/

/*# 1223 "climaf.f"*/
/*# 1224 "climaf.f"*/

/*# 1226 "climaf.f"*/


/*# 1236 "climaf.f"*/
/*# 1237 "climaf.f"*/
/*# 1239 "climaf.f"*/
/*# 1240 "climaf.f"*/
/*# 1241 "climaf.f"*/
/*# 1243 "climaf.f"*/
/*# 1245 "climaf.f"*/

/*# 1247 "climaf.f"*/
/*# 1251 "climaf.f"*/
/*# 1252 "climaf.f"*/
/*# 1254 "climaf.f"*/
/*# 1255 "climaf.f"*/


/*# 1258 "climaf.f"*/
    /* Parameter adjustments */
    --f;
    --y;

    /* Function Body */
/*# 1259 "climaf.f"*/
/*# 1260 "climaf.f"*/
/*# 1261 "climaf.f"*/


/* STATEMENT FUNCTIONS */

/*# 1266 "climaf.f"*/
/*     SCH(TOS) = 0.5D0*DATAN(70.0D0*(TOS-273.0D0))/ATA */
/*     EST, ESTI IN DER BEDEUTUNG VON DAMPFDRUCK */
/*# 1269 "climaf.f"*/
/*# 1270 "climaf.f"*/


/*# 1273 "climaf.f"*/
    eisland = bl4_1.eisbed + .1;
/*# 1274 "climaf.f"*/
    for (i = 1; i <= 180; ++i) {
/*# 1275 "climaf.f"*/
	bl5_3.rh[i - 1] = (y[i * 3 - 2] * (transf_1.rhe - transf_1.rhb) + (
		transf_1.rhe + transf_1.rhb)) * .5;
/*# 1276 "climaf.f"*/
	taa[i - 1] = (y[i * 3 - 1] * (transf_1.tae - transf_1.tab) + 
		bl5_3.ta1[i - 1] * 2. + transf_1.tab + transf_1.tae) * .5 + 
		273.;
/*# 1277 "climaf.f"*/
	tss[i - 1] = (y[i * 3] * (transf_1.tse - transf_1.tsb) + bl5_3.ts1[i 
		- 1] * 2. + transf_1.tsb + transf_1.tse) * .5 + 273.;
/*# 1278 "climaf.f"*/
	bl5_3.ta[i - 1] = taa[i - 1] - 273.;
/*# 1279 "climaf.f"*/
	bl5_3.ts[i - 1] = tss[i - 1] - 273.;

/*# 1281 "climaf.f"*/
	if ((d_1 = bl5_3.ta[i - 1], abs(d_1)) > 150.) {
/*          WRITE(*,*) 'ABS(TA) GT. 150' */
/*          WRITE(*,*) I,TA(I) */
/*          STOP 'STOP 8' */
/*# 1285 "climaf.f"*/
	    *fall = 8.;
/*# 1286 "climaf.f"*/
	    return 0;
/*# 1287 "climaf.f"*/
	}

/*# 1289 "climaf.f"*/
	d_1 = bl5_3.ta[i - 1] * 7.5 / (bl5_3.ta[i - 1] + 237.);
	qsta = pow_dd(&c_b180, &d_1) * 6.107 * 6.22e-4;
/*# 1290 "climaf.f"*/
	q[i - 1] = bl5_3.rh[i - 1] * qsta;

/*# 1292 "climaf.f"*/
	if (bl5_3.rh[i - 1] >= 1.) {
/*          WRITE(*,*) ' RH GROESSER ALS EINS' */
/*          WRITE(*,*) I,RH(I) */
/*          STOP 'STOP 9' */
/*# 1296 "climaf.f"*/
	    *fall = 9.;
/*# 1297 "climaf.f"*/
	    return 0;
/*# 1298 "climaf.f"*/
	}

/*# 1300 "climaf.f"*/
	if (bl5_3.rh[i - 1] <= 0.) {
/*          WRITE(*,*) ' RH KLEINER ALS NULL' */
/*          WRITE(*,*) I,RH(I) */
/*          STOP 'STOP 10' */
/*# 1304 "climaf.f"*/
	    *fall = 10.;
/*# 1305 "climaf.f"*/
	    return 0;
/*# 1306 "climaf.f"*/
	}

/*# 1308 "climaf.f"*/
	d_1 = bl5_3.ts[i - 1] * 7.5 / (bl5_3.ts[i - 1] + 237.);
	qsto[i - 1] = pow_dd(&c_b180, &d_1) * 6.107 * 6.22e-4;
/*# 1309 "climaf.f"*/
	d_1 = bl5_3.ts[i - 1] * 9.5 / (bl5_3.ts[i - 1] + 265.5);
	qsti[i - 1] = pow_dd(&c_b180, &d_1) * 6.107 * 6.22e-4;
/*# 1310 "climaf.f"*/
	d_1 = tss[i - 1] - bl11_1.tf;
	too[i - 1] = bl11_1.tf + sprung_(&d_1, &bl11_1.tend);
/*# 1311 "climaf.f"*/
	druck_1.to[i - 1] = too[i - 1] - 273.;
/*# 1312 "climaf.f"*/
	d_1 = tss[i - 1] - bl11_1.tf;
	schalt[i - 1] = sump_(&d_1, &epst, &bl11_1.tanf, &bl11_1.tend);
/*# 1313 "climaf.f"*/
	ref[i - 1] = bl1_2.eisfrei[i - 1] * schalt[i - 1] + bl4_1.eisbed * (
		1. - schalt[i - 1]);
/*# 1314 "climaf.f"*/
	ausg2_2.albh2o[i - 1] = ref[i - 1];

/*       LAND...... */
/*# 1317 "climaf.f"*/
	tal[i - 1] = taa[i - 1] - bl10_4.laps * bl3_1.height[i - 1];
/*# 1318 "climaf.f"*/
	tll[i - 1] = tal[i - 1];
/* SWITCH(LAND) ENTSPRICHT SCHALT(WASSER), DIE BREITE DES */
/* NICHTLINEAREN STUECKS IST GEGEN DAS WASSER UM DEN FAKTOR */
/* BLAND VERGR÷#ERT; HIER: BLAND=2 */
/*# 1322 "climaf.f"*/
	qstl[i - 1] = qsta * bl12_1.qred[i - 1];
/*# 1323 "climaf.f"*/
	d_1 = bl5_3.ta[i - 1] * 9.5 / (bl5_3.ta[i - 1] + 265.5);
	qstli[i - 1] = pow_dd(&c_b180, &d_1) * 6.107 * 6.22e-4 * bl12_1.qred[
		i - 1];
/*# 1324 "climaf.f"*/
	d_1 = tll[i - 1] - bl11_1.tf;
	d_2 = -bland * bl4_1.dice;
	d_3 = bland * bl4_1.dice;
	switch_[i - 1] = sump_(&d_1, &epst, &d_2, &d_3);
/*# 1325 "climaf.f"*/
	ql[i - 1] = q[i - 1] * bl12_1.qred[i - 1];
/*# 1326 "climaf.f"*/
	druck_1.tastr[i - 1] = tal[i - 1] * bl3_1.fland[i - 1] + taa[i - 1] * 
		(1. - bl3_1.fland[i - 1]) - 273.;
/*# 1327 "climaf.f"*/
	druck_1.tstr[i - 1] = bl3_1.fland[i - 1] * tll[i - 1] + (1. - 
		bl3_1.fland[i - 1]) * tss[i - 1] - 273.;
/*# 1328 "climaf.f"*/
	druck_1.qstr[i - 1] = bl3_1.fland[i - 1] * ql[i - 1] + (1. - 
		bl3_1.fland[i - 1]) * q[i - 1];
/*# 1329 "climaf.f"*/
	refl[i - 1] = bl1_2.eisf[i - 1] * switch_[i - 1] + eisland * (1. - 
		switch_[i - 1]);
/*# 1330 "climaf.f"*/
	ausg2_2.albb[i - 1] = refl[i - 1];
/*# 1331 "climaf.f"*/
	d_1 = 1. - epsb;
	druck_1.bew[i - 1] = sump_(&bl5_3.rh[i - 1], &epsb, &bl12_1.rmin, &
		d_1);
/*       BEW(I) = SUMP(RH(I),EPSB,RMIN*(1.0+0.1*HEIGHT(I)),1.0D0-EPSB)
 */
/*# 1333 "climaf.f"*/
	bewl[i - 1] = druck_1.bew[i - 1] * .75;
/*# 1334 "climaf.f"*/
/* L20: */
    }

/*# 1336 "climaf.f"*/
    for (i = 2; i <= 179; ++i) {
/*# 1337 "climaf.f"*/
	gradta[i - 1] = (bl5_3.ta[i] - bl5_3.ta[i - 2]) / (bl3_1.dx * 2);
/*# 1338 "climaf.f"*/
	gradto[i - 1] = (bl5_3.ts[i] - bl5_3.ts[i - 2]) / (bl3_1.dx * 2);
/*# 1339 "climaf.f"*/
	gradq[i - 1] = (q[i] - q[i - 2]) / (bl3_1.dx * 2);
/*# 1340 "climaf.f"*/
/* L32: */
    }
/*# 1341 "climaf.f"*/
    gradta[0] = (bl5_3.ta[1] - bl5_3.ta[0]) / (bl3_1.dx * 2);
/*# 1342 "climaf.f"*/
    gradta[179] = (bl5_3.ta[179] - bl5_3.ta[178]) / (bl3_1.dx * 2);

/*# 1344 "climaf.f"*/
    gradq[0] = (q[1] - q[0]) / (bl3_1.dx * 2);
/*# 1345 "climaf.f"*/
    gradto[0] = (bl5_3.ts[1] - bl5_3.ts[0]) / (bl3_1.dx * 2);
/*# 1346 "climaf.f"*/
    gradto[179] = (bl5_3.ts[179] - bl5_3.ts[178]) / (bl3_1.dx * 2);
/*# 1347 "climaf.f"*/
    gradq[179] = (q[179] - q[178]) / (bl3_1.dx * 2);
/*# 1348 "climaf.f"*/
    for (i = 1; i <= 180; ++i) {
/*# 1349 "climaf.f"*/
	gra[i - 1] = (d_1 = gradta[i - 1], abs(d_1));
/*# 1350 "climaf.f"*/
/* L33: */
    }


/* EISLINIE */
/*# 1354 "climaf.f"*/
    eisli_(tss, druck_1.eisl);

/* SCHNEELINIE */
/*# 1357 "climaf.f"*/
    eisli_(taa, druck_1.snow);


/* HADLEY LINIE */
/*# 1361 "climaf.f"*/
    hadl_(&bl3_1.dx, bl3_1.xst, gradta, bl3_1.gradc, had);
/*# 1362 "climaf.f"*/
    for (k = 1; k <= 2; ++k) {
/*# 1363 "climaf.f"*/
/* L29: */
	druck_1.hadley[k - 1] = had[k - 1] * 180. / bl11_1.pi;
    }

/*  WIND (LAMDA) UND VERTICALGESCHW. (W), WELCHE DIE WOLKENDICKE BESTIMMT 
*/
/*# 1366 "climaf.f"*/
    for (i = 1; i <= 180; ++i) {
/*# 1367 "climaf.f"*/
	d_1 = 1. - gradta[i - 1] / bl3_1.gradc[i - 1];
	blam1[i - 1] = sprung_(&d_1, &c_b229);
/*# 1368 "climaf.f"*/
	d_2 = 1. - (d_1 = bl3_1.gradc[i - 1] / gradta[i - 1], abs(d_1));
	blam2[i - 1] = sprung_(&d_2, &c_b230);
/*# 1369 "climaf.f"*/
	d_1 = 1. - gradta[i - 1] * 3. / bl3_1.gradc[i - 1];
	blam3 = sprung_(&d_1, &c_b229);
/*     LAMDA(I) = LAM(1)+LAM(2)*GRA(I)*BLAM2(I) */
/*     W(I) = 1.0 + PC(2)*GRA(I)*BLAM2(I) */
/*# 1372 "climaf.f"*/
	lamda[i - 1] = bl4_1.lam[0] + gra[i - 1] * (bl4_1.lam[1] * bl3_1.zc[i 
		- 1] * blam2[i - 1] + bl4_1.lam[0] * .07 * blam1[i - 1]);
/*# 1374 "climaf.f"*/
	ausg4_2.w[i - 1] = blam3 + bl3_1.zc[i - 1] * bl12_1.pc[1] * gra[i - 1]
		 * blam2[i - 1];
/*# 1375 "climaf.f"*/
/* L62: */
    }





/* ******************************************* */
/*# 1382 "climaf.f"*/
    diskret_(taa, tss, tss, q, divfa, divfo, divfq, gradta, gradto, gradq, 
	    gra, blam1, schalt);
/* ********************************************* */
/*     1. RUF VON STRAHL F<^N>R DIE MEERESOBERFL<SIGMA>CHE (H÷HE=NULL) */
/*     2. RUF VON STRAHL F<^N>R DIE LANDOBERFL<SIGMA>CHE (H÷HE=HEIGHT) */

/* **************************************************************** */
/*# 1389 "climaf.f"*/
    strahl_(taa, tss, absaa, absoo, la, lo, druck_1.bew, ref, null, bl5_3.rh, 
	    q, &c__1, albww, contrw, hlw, huw, kappaw, quotw, ausg4_2.w, fall)
	    ;

/*# 1392 "climaf.f"*/
    strahl_(taa, tll, absal, absol, ira, irl, bewl, refl, bl3_1.height, 
	    bl5_3.rh, q, &c__2, albwl, contrl, hll, hul, kappal, quotl, 
	    ausg4_2.w, fall);
/* ***************************************************************** */

/*# 1396 "climaf.f"*/
    for (i = 1; i <= 180; ++i) {
/*# 1397 "climaf.f"*/
	bl10_4.hl[i - 1] = hll[i - 1] * bl3_1.fland[i - 1] + hlw[i - 1] * (1. 
		- bl3_1.fland[i - 1]);
/*# 1398 "climaf.f"*/
	bl10_4.hu[i - 1] = hul[i - 1] * bl3_1.fland[i - 1] + huw[i - 1] * (1. 
		- bl3_1.fland[i - 1]);
/*# 1399 "climaf.f"*/
	ausg4_2.contr[i - 1] = contrl[i - 1] * bl3_1.fland[i - 1] + contrw[i 
		- 1] * (1. - bl3_1.fland[i - 1]);
/*# 1400 "climaf.f"*/
	ausg4_2.contr[i + 179] = contrl[i + 179] * bl3_1.fland[i - 1] + 
		contrw[i + 179] * (1. - bl3_1.fland[i - 1]);
/*# 1401 "climaf.f"*/
	ausg4_2.contr[i + 359] = contrl[i + 359] * bl3_1.fland[i - 1] + 
		contrw[i + 359] * (1. - bl3_1.fland[i - 1]);
/*# 1402 "climaf.f"*/
	ausg4_2.contr[i + 539] = contrl[i + 539] * bl3_1.fland[i - 1] + 
		contrw[i + 539] * (1. - bl3_1.fland[i - 1]);
/*# 1403 "climaf.f"*/
	ausg4_2.contr[i + 719] = contrl[i + 719] * bl3_1.fland[i - 1] + 
		contrw[i + 719] * (1. - bl3_1.fland[i - 1]);
/*# 1404 "climaf.f"*/
	ausg4_2.contr[i + 899] = contrl[i + 899] * bl3_1.fland[i - 1] + 
		contrw[i + 899] * (1. - bl3_1.fland[i - 1]);
/*# 1405 "climaf.f"*/
	ausg2_2.albw[i - 1] = albwl[i - 1] * bl3_1.fland[i - 1] + albww[i - 1]
		 * (1. - bl3_1.fland[i - 1]);
/*# 1406 "climaf.f"*/
	ausg4_2.quot[i - 1] = quotl[i - 1] * bl3_1.fland[i - 1] + quotw[i - 1]
		 * (1. - bl3_1.fland[i - 1]);
/*# 1407 "climaf.f"*/
	ausg4_2.kappa[i - 1] = kappal[i - 1] * bl3_1.fland[i - 1] + kappaw[i 
		- 1] * (1. - bl3_1.fland[i - 1]);
/*# 1408 "climaf.f"*/
/* L17: */
    }

/* ********************************************* */
/*# 1411 "climaf.f"*/
    moist_(qsto, qstl, qsti, qstli, lamda, ewasser, eland, p, druck_1.bew, 
	    bewl, bl5_3.rh, ps, schalt, q);
/* ***************************************************************** */


/*# 1416 "climaf.f"*/
    for (i = 1; i <= 180; ++i) {
/*# 1417 "climaf.f"*/
	druck_1.bew[i - 1] = bl3_1.fland[i - 1] * bewl[i - 1] + (1. - 
		bl3_1.fland[i - 1]) * druck_1.bew[i - 1];
/*# 1418 "climaf.f"*/
	ausg2_2.amda[i - 1] = lamda[i - 1];
/*# 1419 "climaf.f"*/
	druck_1.grat[i - 1] = gradta[i - 1];
/*# 1420 "climaf.f"*/
	druck_1.gratq[i - 1] = gradq[i - 1];
/*# 1421 "climaf.f"*/
	druck_1.pcrit[i - 1] = ps[i - 1];
/* PTOTAL: TOTAL PRECIPITATION */
/*# 1423 "climaf.f"*/
	druck_1.ptotal[i - 1] = p[i - 1] + druck_1.pcrit[i - 1];
/*# 1424 "climaf.f"*/
	rsonne = sol * bl1_2.soleil[i - 1] * bl1_2.sun;
/* ABSORB: TOTAL SHORTWAVE ABSORPTION */
/*# 1426 "climaf.f"*/
	druck_1.absorb[i - 1] = (bl3_1.fland[i - 1] * (absol[i - 1] + absal[i 
		- 1]) + (1. - bl3_1.fland[i - 1]) * (absaa[i - 1] + absoo[i - 
		1])) * rsonne;
/* EMIT: TOTAL LONGWAVE EMISSION TO SPACE */
/*# 1429 "climaf.f"*/
	druck_1.emit[i - 1] = bl3_1.fland[i - 1] * (irl[i - 1] + ira[i - 1]) 
		+ (1. - bl3_1.fland[i - 1]) * (la[i - 1] + lo[i - 1]);
/* ABSA, ABSO: SHORTWAVE ABSORPTION OF ATMOSPHERE(A) AND OCEAN(O) */
/*# 1432 "climaf.f"*/
	ausg2_2.absa[i - 1] = (bl3_1.fland[i - 1] * absal[i - 1] + (1. - 
		bl3_1.fland[i - 1]) * absaa[i - 1]) * rsonne;
/*# 1434 "climaf.f"*/
	ausg2_2.abso[i - 1] = (bl3_1.fland[i - 1] * absol[i - 1] + (1. - 
		bl3_1.fland[i - 1]) * absoo[i - 1]) * rsonne;
/* STA, STO: LONGWAVE EMISSION OF ATMOSPHERE(A) AND OCEAN(O) */
/*# 1437 "climaf.f"*/
	ausg2_2.sta[i - 1] = bl3_1.fland[i - 1] * ira[i - 1] + (1. - 
		bl3_1.fland[i - 1]) * la[i - 1];
/*# 1439 "climaf.f"*/
	ausg2_2.sto[i - 1] = bl3_1.fland[i - 1] * irl[i - 1] + (1. - 
		bl3_1.fland[i - 1]) * lo[i - 1];
/* RLA: RADIATION BALANCE OF ATMOSPHERE OVER LAND */
/*# 1442 "climaf.f"*/
	rla = absal[i - 1] * rsonne + ira[i - 1];
/* RL: RADIATION BALANCE OF LAND SURFACE */
/*# 1444 "climaf.f"*/
	rl = absol[i - 1] * rsonne + irl[i - 1];
/* RWA: RADIATION BALANCE OF ATMOSPHERE OVER WATER */
/*# 1446 "climaf.f"*/
	rwa = absaa[i - 1] * rsonne + la[i - 1];
/* RW: RADIATION BALANCE OF WATER SURFACE */
/*# 1448 "climaf.f"*/
	rw = absoo[i - 1] * rsonne + lo[i - 1];
/* RA: TOTAL RADIATION BALANCE OF ATMOSPHERE */
/*# 1450 "climaf.f"*/
	druck_1.ra[i - 1] = bl3_1.fland[i - 1] * rla + (1. - bl3_1.fland[i - 
		1]) * rwa;
/* RO: TOTAL RADIATION BALANCE OF OCEAN */
/*# 1452 "climaf.f"*/
	druck_1.ro[i - 1] = bl3_1.fland[i - 1] * rl + (1. - bl3_1.fland[i - 1]
		) * rw;
/* H:  SENSIBLE VERTICAL HEAT FLUX */
/*# 1454 "climaf.f"*/
	druck_1.h[i - 1] = (1. - bl3_1.fland[i - 1]) * lamda[i - 1] * (tss[i 
		- 1] - taa[i - 1]);
/*# 1455 "climaf.f"*/
	druck_1.alat[i - 1] = bl11_1.al * druck_1.ptotal[i - 1] * umrech;
/* EVA: EVAPORATION */
/*# 1457 "climaf.f"*/
	druck_1.eva[i - 1] = bl3_1.fland[i - 1] * eland[i - 1] + (1. - 
		bl3_1.fland[i - 1]) * ewasser[i - 1];
/*# 1458 "climaf.f"*/
	druck_1.olat[i - 1] = bl11_1.al * druck_1.eva[i - 1] * umrech;
/*# 1459 "climaf.f"*/
	oland = bl11_1.al * eland[i - 1] * umrech;
/*# 1460 "climaf.f"*/
	owasser = bl11_1.al * ewasser[i - 1] * umrech;
/*# 1461 "climaf.f"*/
	druck_1.aflux[i - 1] = divfa[i - 1] * bl11_1.cofat;
/*# 1462 "climaf.f"*/
	druck_1.oflux[i - 1] = divfo[i - 1] * bl11_1.cofoz;
/*# 1463 "climaf.f"*/
	druck_1.qflux[i - 1] = divfq[i - 1] * bl11_1.coffe;
/*# 1464 "climaf.f"*/
	fx = druck_1.aflux[i - 1] + druck_1.h[i - 1] + druck_1.alat[i - 1] + 
		druck_1.ra[i - 1] + bl3_1.fland[i - 1] * rl - bl3_1.fland[i - 
		1] * oland;
/*# 1466 "climaf.f"*/
	fy = druck_1.oflux[i - 1] / (1. - bl3_1.fland[i - 1]) - druck_1.h[i - 
		1] / (1. - bl3_1.fland[i - 1]) + rw - owasser;
/*# 1467 "climaf.f"*/
	fz = druck_1.olat[i - 1] + druck_1.qflux[i - 1] - druck_1.alat[i - 1];

/*# 1468 "climaf.f"*/
	f[i * 3] = fy * .01;
/*# 1469 "climaf.f"*/
	f[i * 3 - 1] = fx * .01;
/*# 1470 "climaf.f"*/
	f[i * 3 - 2] = fz * .01;
/*# 1471 "climaf.f"*/
/* L16: */
    }

/*# 1473 "climaf.f"*/
    return 0;
/*# 1474 "climaf.f"*/
} /* fcn_ */

/* === */

/*# 1477 "climaf.f"*/
/* Subroutine */ int diskret_(doublereal *ta, doublereal *ts, doublereal *to, 
	doublereal *q, doublereal *divfa, doublereal *divfo, doublereal *
	divfq, doublereal *gradta, doublereal *gradto, doublereal *gradq, 
	doublereal *gra, doublereal *fx, doublereal *schalt)
{
    /* System generated locals */
    doublereal d_1, d_2;

    /* Builtin functions */
    double d_sign(doublereal *, doublereal *);

    /* Local variables */
    static doublereal adva[180], scha, rfak, advq[180];
    extern doublereal sump_(doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static integer i;
    static doublereal osued[180], onord[180], f1, f2, fxzwi, da[180], ga[180],
	     dq[180], go[180], gq[180], dw[180], difusa, da0, flinks, difuso, 
	    difusq;
    extern doublereal sprung_(doublereal *, doublereal *);
    static doublereal fy1, fy2, aflussa[180], dflussa[180], frechts, aflusso[
	    180], aflussq[180], dflusso[180], dflussq[180];


/*# 1480 "climaf.f"*/
/*# 1481 "climaf.f"*/

/*# 1483 "climaf.f"*/
/*# 1488 "climaf.f"*/

/*# 1490 "climaf.f"*/
/*# 1492 "climaf.f"*/
/*# 1493 "climaf.f"*/
/*     COMMON/BL12/PC(2),RMIN,RCRIT,W0,BETA,QRED(M) */
/*# 1496 "climaf.f"*/

/*# 1498 "climaf.f"*/
/*# 1499 "climaf.f"*/


/*# 1502 "climaf.f"*/
    /* Parameter adjustments */
    --schalt;
    --fx;
    --gra;
    --gradq;
    --gradto;
    --gradta;
    --divfq;
    --divfo;
    --divfa;
    --q;
    --to;
    --ts;
    --ta;

    /* Function Body */
    for (i = 2; i <= 180; ++i) {
/*# 1503 "climaf.f"*/
	ga[i - 1] = (ta[i] - ta[i - 1]) / bl3_1.dx;
/*# 1504 "climaf.f"*/
	gq[i - 1] = (q[i] - q[i - 1]) / bl3_1.dx;
/*# 1505 "climaf.f"*/
	go[i - 1] = (to[i] - to[i - 1]) / bl3_1.dx;
/*# 1506 "climaf.f"*/
/* L10: */
    }
/*# 1507 "climaf.f"*/
    ga[0] = 0.;


/*# 1510 "climaf.f"*/
    for (i = 1; i <= 180; ++i) {
/*# 1511 "climaf.f"*/
	ausg1_3.vq[i - 1] = bl9_2.vqq * fx[i] * gradta[i];
/*# 1512 "climaf.f"*/
	ausg1_3.dkq[i - 1] = bl9_2.dqq[1] * gra[i] + bl9_2.dqq[0];
/*# 1513 "climaf.f"*/
	ausg1_3.dka[i - 1] = bl9_2.daa * gra[i] + bl9_2.dqq[0] + bl9_2.vaa * 
		fx[i] * ta[i] * bl11_2.re;
/*  57 DKO(I) = DWW(2)*SCHALT(I)*(1.0D0-2.0D0*ZS(I)**2+ZS(I)**4)+DWW(1
) */
/*# 1515 "climaf.f"*/
/* L57: */
/* Computing 2nd power */
	d_1 = bl3_1.zs[i - 1];
/* Computing 4th power */
	d_2 = bl3_1.zs[i - 1], d_2 *= d_2;
	ausg1_3.dko[i - 1] = bl9_2.dww[1] * (1. - d_1 * d_1 * 2. + d_2 * d_2) 
		+ bl9_2.dww[0];
    }

/* DKO: DIFFUSION COEFFICIENT OCEAN */
/* DKA: DIFFUSION COEFFICIENT ATMOSPHERE */
/* DKQ: DIFFUSION COEFFICIENT HUMIDITY */
/* VQ: ADVECTION HUMIDITY */
/* DQ,DW,DA: DIFFUSION COEFFICIENTS FOR DISCRETIZATION FORMULAE */

/*# 1523 "climaf.f"*/
    for (i = 2; i <= 180; ++i) {
/*# 1524 "climaf.f"*/
	rfak = (d_1 = ga[i - 1], abs(d_1));
/*# 1525 "climaf.f"*/
	d_1 = ga[i - 1] * bl3_1.sinm[i - 1] / (bl3_1.hadk * bl3_1.cosm[i - 1])
		 + 1.;
	fxzwi = sprung_(&d_1, &c_b229);
/*# 1526 "climaf.f"*/
	dq[i - 1] = bl9_2.dqq[1] * rfak + bl9_2.dqq[0];
/*# 1527 "climaf.f"*/
	da0 = bl9_2.daa * rfak + bl9_2.dqq[0];
/*# 1528 "climaf.f"*/
	d_1 = (ts[i] + ts[i - 1]) * .5 - bl11_2.tf;
	scha = sump_(&d_1, &c_b241, &bl11_2.tanf, &bl11_2.tend);
/*       DW(I) = (DWW(2)*SCHA*(1.0D0-2.0D0*SINM(I)**2+SINM(I)**4)+DWW(
1)) */
/*    +          *(1.0D0-XLAND(I)) */
/*# 1531 "climaf.f"*/
/* Computing 2nd power */
	d_1 = bl3_1.sinm[i - 1];
/* Computing 4th power */
	d_2 = bl3_1.sinm[i - 1], d_2 *= d_2;
	dw[i - 1] = (bl9_2.dww[1] * (1. - d_1 * d_1 * 2. + d_2 * d_2) + 
		bl9_2.dww[0]) * (1. - bl3_1.xland[i - 1]);
/*# 1533 "climaf.f"*/
/* L58: */
	da[i - 1] = da0 + bl9_2.vaa * bl11_2.re * fxzwi * (ta[i] + ta[i - 1]) 
		* .5;
    }


/*# 1536 "climaf.f"*/
    for (i = 1; i <= 180; ++i) {
/*# 1537 "climaf.f"*/
	aflussa[i - 1] = 0.;
/*# 1538 "climaf.f"*/
	aflusso[i - 1] = 0.;
/*# 1539 "climaf.f"*/
	aflussq[i - 1] = bl3_1.zc[i - 1] * ausg1_3.vq[i - 1] * q[i] * 
		bl11_2.cofdq * bl11_2.re;
/*# 1540 "climaf.f"*/
	dflussa[i - 1] = -bl3_1.zc[i - 1] * ausg1_3.dka[i - 1] * gradta[i] * 
		bl11_2.cofda;
/*# 1541 "climaf.f"*/
	dflusso[i - 1] = -bl3_1.zc[i - 1] * ausg1_3.dko[i - 1] * gradto[i] * 
		bl11_2.cofdo;
/*# 1542 "climaf.f"*/
	dflussq[i - 1] = -bl3_1.zc[i - 1] * ausg1_3.dkq[i - 1] * gradq[i] * 
		bl11_2.cofdq;
/* FLUSSA, FLUSSO, FLUSSQ: TOTAL FLUXES FOR ATMOS, OCEAN, HUMIDITY */
/*# 1544 "climaf.f"*/
	ausg1_3.flussa[i - 1] = aflussa[i - 1] + dflussa[i - 1];
/*# 1545 "climaf.f"*/
	ausg1_3.flusso[i - 1] = (aflusso[i - 1] + dflusso[i - 1]) * (1. - 
		bl3_1.fland[i - 1]);
/*# 1546 "climaf.f"*/
	ausg1_3.flussq[i - 1] = aflussq[i - 1] + dflussq[i - 1];
/*# 1547 "climaf.f"*/
/* L56: */
    }


/* ADVECTION */
/* ADVECTIVE FLUX OF ATMOSPHERE CAN BE SUBSUMIZED UNDER DIFFUSION, BECAUSE
 */
/* ADVECTIVE AND DIFFUSIVE FLUX ARE OF EQUAL SIGN */
/*ADVECTIVE FLUX OF HUMIDITY IS OPPOSITE TO DIFFUSIVE FLUX OF HUMIDITY, SO
*/
/* IT MUST BE TREATED SEPARATELY */
/*# 1555 "climaf.f"*/
    for (i = 1; i <= 180; ++i) {
/*# 1556 "climaf.f"*/
	scha = (d_sign(&c_b178, &ga[i - 1]) + 1.) * .5 - (1. - d_sign(&c_b178,
		 &ga[i - 1])) * .5;
/*# 1557 "climaf.f"*/
	onord[i - 1] = (scha + 1.) * .5;
/*# 1558 "climaf.f"*/
	osued[i - 1] = (1. - scha) * .5;
/*# 1559 "climaf.f"*/
	onord[i - 1] = (d_sign(&c_b178, &ga[i - 1]) + 1.) * .5;
/*# 1560 "climaf.f"*/
	osued[i - 1] = (1. - d_sign(&c_b178, &ga[i - 1])) * .5;
/*# 1561 "climaf.f"*/
/* L33: */
    }


/* ADVQ : ADVECTION OF HUMIDITY */


/*# 1567 "climaf.f"*/
    d_1 = 1. - ga[1] / bl3_1.gradc[0];
    f2 = sprung_(&d_1, &c_b229);
/*# 1568 "climaf.f"*/
    d_1 = 1. - ga[1] / bl3_1.gradc[1];
    fy2 = sprung_(&d_1, &c_b229);
/*# 1569 "climaf.f"*/
    frechts = ga[1] * q[1] * bl3_1.zc[0] * f2 * onord[0] + ga[1] * q[2] * 
	    bl3_1.zc[1] * fy2 * osued[0];
/*# 1571 "climaf.f"*/
    flinks = 0.;
/*# 1572 "climaf.f"*/
    advq[0] = bl9_2.vqq * (frechts - flinks);

/*# 1574 "climaf.f"*/
    d_1 = 1. - ga[179] / bl3_1.gradc[178];
    f1 = sprung_(&d_1, &c_b229);
/*# 1575 "climaf.f"*/
    d_1 = 1. - ga[179] / bl3_1.gradc[179];
    fy1 = sprung_(&d_1, &c_b229);

/*# 1577 "climaf.f"*/
    for (i = 2; i <= 179; ++i) {
/*# 1578 "climaf.f"*/
	d_1 = 1. - ga[i] / bl3_1.gradc[i - 1];
	f2 = sprung_(&d_1, &c_b229);
/*# 1579 "climaf.f"*/
	d_1 = 1. - ga[i] / bl3_1.gradc[i];
	fy2 = sprung_(&d_1, &c_b229);
/*# 1580 "climaf.f"*/
	flinks = frechts;
/*# 1581 "climaf.f"*/
	frechts = ga[i] * q[i] * bl3_1.zc[i - 1] * f2 * onord[i - 1] + ga[i] *
		 q[i + 1] * bl3_1.zc[i] * fy2 * osued[i - 1];
/*# 1583 "climaf.f"*/
	advq[i - 1] = bl9_2.vqq * (frechts - flinks);
/*# 1584 "climaf.f"*/
/* L62: */
    }


/*# 1587 "climaf.f"*/
    flinks = ga[179] * q[179] * bl3_1.zc[178] * f1 * onord[179] + ga[179] * q[
	    180] * bl3_1.zc[179] * fy1 * osued[179];
/*# 1589 "climaf.f"*/
    frechts = 0.;
/*# 1590 "climaf.f"*/
    advq[179] = bl9_2.vqq * (frechts - flinks);

/*# 1592 "climaf.f"*/
    for (i = 1; i <= 180; ++i) {
/*# 1593 "climaf.f"*/
	adva[i - 1] = 0.;
/*# 1594 "climaf.f"*/
	advq[i - 1] *= bl11_2.re;
/*# 1595 "climaf.f"*/
/* L44: */
    }

/* DIFFUSION */
/*# 1598 "climaf.f"*/
    for (i = 2; i <= 179; ++i) {
/*# 1599 "climaf.f"*/
	difusa = da[i] * bl3_1.cosm[i] * ga[i] - da[i - 1] * bl3_1.cosm[i - 1]
		 * ga[i - 1];
/*# 1601 "climaf.f"*/
	divfa[i] = (difusa - adva[i - 1]) / (bl3_1.dx * bl3_1.zc[i - 1]);
/*# 1602 "climaf.f"*/
	difusq = dq[i] * bl3_1.cosm[i] * gq[i] - dq[i - 1] * bl3_1.cosm[i - 1]
		 * gq[i - 1];
/*# 1603 "climaf.f"*/
	divfq[i] = (difusq - advq[i - 1]) / (bl3_1.dx * bl3_1.zc[i - 1]);
/*# 1604 "climaf.f"*/
	difuso = dw[i] * bl3_1.cosm[i] * go[i] - dw[i - 1] * bl3_1.cosm[i - 1]
		 * go[i - 1];
/*# 1605 "climaf.f"*/
	divfo[i] = difuso / (bl3_1.dx * bl3_1.zc[i - 1]);
/*# 1606 "climaf.f"*/
/* L12: */
    }

/*# 1608 "climaf.f"*/
    difusa = da[1] * bl3_1.cosm[1] * ga[1];
/*# 1609 "climaf.f"*/
    divfa[1] = (difusa - adva[0]) / (bl3_1.dx * bl3_1.zc[0]);
/*# 1610 "climaf.f"*/
    difusa = -da[179] * bl3_1.cosm[179] * ga[179];
/*# 1611 "climaf.f"*/
    divfa[180] = (difusa - adva[179]) / (bl3_1.dx * bl3_1.zc[179]);
/*# 1612 "climaf.f"*/
    difusq = dq[1] * bl3_1.cosm[1] * gq[1];
/*# 1613 "climaf.f"*/
    divfq[1] = (difusq - advq[0]) / (bl3_1.dx * bl3_1.zc[0]);
/*# 1614 "climaf.f"*/
    difusq = -dq[179] * bl3_1.cosm[179] * gq[179];
/*# 1615 "climaf.f"*/
    divfq[180] = (difusq - advq[179]) / (bl3_1.dx * bl3_1.zc[179]);
/*# 1616 "climaf.f"*/
    difuso = dw[1] * bl3_1.cosm[1] * go[1];
/*# 1617 "climaf.f"*/
    divfo[1] = difuso / (bl3_1.dx * bl3_1.zc[0]);
/*# 1618 "climaf.f"*/
    difuso = dw[179] * bl3_1.cosm[179] * go[179];
/*# 1619 "climaf.f"*/
    divfo[180] = -difuso / (bl3_1.dx * bl3_1.zc[179]);

/*# 1621 "climaf.f"*/
    return 0;
/*# 1622 "climaf.f"*/
} /* diskret_ */

/* === */

/*# 1625 "climaf.f"*/
/* Subroutine */ int strahl_(doublereal *ta, doublereal *to, doublereal *absa,
	 doublereal *abso, doublereal *la, doublereal *lo, doublereal *bew, 
	doublereal *ass, doublereal *berg, doublereal *rh, doublereal *q, 
	integer *l, doublereal *albw, doublereal *contr, doublereal *hls, 
	doublereal *hus, doublereal *kappa, doublereal *cquot, doublereal *w, 
	doublereal *fall)
{
    /* Initialized data */

    static doublereal co2 = 350.;
    static doublereal sigma = 5.7e-8;
    static doublereal a1 = 237.;
    static doublereal a2 = 17.2694;

    /* System generated locals */
    doublereal d_1;

    /* Builtin functions */
    double log(doublereal), exp(doublereal), pow_dd(doublereal *, doublereal *
	    );

    /* Local variables */
    static doublereal wegh[180], tauh, wegu[180], tauu;
    extern doublereal sump_(doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal wegl0[180], taul0, feedb;
    static integer i;
    static doublereal dicke[180], clear, wegub[180], downh, trans, r1, r2, 
	    kappa1, kappa2, downl0, fa[180], ch, ff[180], fl, lg, hl[180], bq,
	     aclear, cu, hu[180], tl, qr, acloud, sclear, zm, zr, tu, fu, 
	    fenstc, cl0, cloudy, fenstw, q1000[180], fam, fum;
    extern doublereal tau_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *);
    static doublereal upc, zrh, zum, upw, acloudy, counter, scloudy;

/*  TA IST IMMER AUF HEIGHT=0 BEZOGENE GROESSE */
/*  TO IST TLAND, WENN L=2 */

/*# 1630 "climaf.f"*/
/*# 1631 "climaf.f"*/
/*# 1632 "climaf.f"*/

/*# 1634 "climaf.f"*/

/*# 1636 "climaf.f"*/
/*# 1640 "climaf.f"*/
/*# 1641 "climaf.f"*/
/*# 1643 "climaf.f"*/
/*# 1645 "climaf.f"*/
/*# 1646 "climaf.f"*/

/*# 1648 "climaf.f"*/
    /* Parameter adjustments */
    --w;
    --cquot;
    --kappa;
    --hus;
    --hls;
    --contr;
    --albw;
    --q;
    --rh;
    --berg;
    --ass;
    --bew;
    --lo;
    --la;
    --abso;
    --absa;
    --to;
    --ta;

    /* Function Body */
/*# 1649 "climaf.f"*/

/*     STATEMENT FUNCTIONS */
/*# 1652 "climaf.f"*/
/*# 1653 "climaf.f"*/
/*# 1654 "climaf.f"*/


/*# 1657 "climaf.f"*/
    switch (*l) {
	case 1:  goto L30;
	case 2:  goto L31;
    }
/*# 1658 "climaf.f"*/
L30:
    for (i = 1; i <= 180; ++i) {
/*# 1659 "climaf.f"*/
	q1000[i - 1] = q[i] * 1e3;
/*# 1660 "climaf.f"*/
	fa[i - 1] = sigma * (ta[i] * ta[i]) * (ta[i] * ta[i]);
/*# 1661 "climaf.f"*/
	ff[i - 1] = sigma * (to[i] * to[i]) * (to[i] * to[i]);
/*       WEGH: PATH-LENGTH FROM BERG TO TROPOS */
/*# 1663 "climaf.f"*/
	wegh[i - 1] = q1000[i - 1] / bl12_2.beta;
/*# 1664 "climaf.f"*/
	zr = sump_(&rh[i], &c_b160, &c_b160, &c_b263);
/*# 1665 "climaf.f"*/
	zrh = zr * .9999 + 1e-4;
/*# 1666 "climaf.f"*/
	hl[i - 1] = -bl10_5.unten * a1 / (a2 * bl10_5.laps) * log(zrh);
/*# 1667 "climaf.f"*/
	if (hl[i - 1] > bl1_3.tropos[i - 1] - .05) {
/*# 1668 "climaf.f"*/
	    hl[i - 1] = bl1_3.tropos[i - 1] - .05;
/*# 1669 "climaf.f"*/
	    hu[i - 1] = bl1_3.tropos[i - 1];
/*# 1670 "climaf.f"*/
	    goto L11;
/*# 1671 "climaf.f"*/
	}

/*# 1673 "climaf.f"*/
	dicke[i - 1] = bl10_5.thick * .758 * (w[i] + 1.);
/*# 1674 "climaf.f"*/
	hu[i - 1] = dicke[i - 1] + hl[i - 1];
/*# 1675 "climaf.f"*/
	if (hu[i - 1] > bl1_3.tropos[i - 1]) {
	    hu[i - 1] = bl1_3.tropos[i - 1];
	}
/*  ES SOLLTE GELTEN: BERG<HL(I)<HU(I)<TROPOS  !! */
/*# 1677 "climaf.f"*/
L11:
/*# 1678 "climaf.f"*/
	r1 = exp(-bl12_2.beta * hl[i - 1]) / bl12_2.beta;
/*# 1679 "climaf.f"*/
	r2 = exp(-bl12_2.beta * hu[i - 1]) / bl12_2.beta;
/*  WEGUB: PATH-LENGTH FROM HL TO HU */
/*# 1681 "climaf.f"*/
	wegub[i - 1] = q1000[i - 1] * (r1 - r2);
/*# 1682 "climaf.f"*/
	stmo_1.wegclw[i - 1] = wegub[i - 1];
/*  WEGL0: PATH-LENGTH FROM BERG TO HL */
/*# 1684 "climaf.f"*/
	wegl0[i - 1] = wegh[i - 1] - q1000[i - 1] * r1;
/*  WEGU: PATH-LENGTH FROM HU TO TROPOS */
/*# 1686 "climaf.f"*/
	wegu[i - 1] = q1000[i - 1] * r2;
/*# 1687 "climaf.f"*/
/* L10: */
    }
/*# 1688 "climaf.f"*/
    goto L13;

/*# 1690 "climaf.f"*/
L31:
    for (i = 1; i <= 180; ++i) {
/*# 1691 "climaf.f"*/
	fa[i - 1] = sigma * (ta[i] * ta[i]) * (ta[i] * ta[i]);
/*# 1692 "climaf.f"*/
	ff[i - 1] = fa[i - 1];
/*# 1693 "climaf.f"*/
	wegh[i - 1] *= bl12_2.qred[i - 1];
/*# 1694 "climaf.f"*/
	hl[i - 1] += berg[i];
/*# 1695 "climaf.f"*/
	if (hl[i - 1] > bl1_3.tropos[i - 1] - .05) {
/*# 1696 "climaf.f"*/
	    hl[i - 1] = bl1_3.tropos[i - 1] - .05;
/*# 1697 "climaf.f"*/
	    hu[i - 1] = bl1_3.tropos[i - 1];
/*# 1698 "climaf.f"*/
	    goto L14;
/*# 1699 "climaf.f"*/
	}
/*# 1700 "climaf.f"*/
	hu[i - 1] = dicke[i - 1] + hl[i - 1];
/*# 1701 "climaf.f"*/
	if (hu[i - 1] > bl1_3.tropos[i - 1]) {
/*# 1702 "climaf.f"*/
	    hu[i - 1] = bl1_3.tropos[i - 1];
/*# 1703 "climaf.f"*/
	    goto L14;
/*# 1704 "climaf.f"*/
	} else {
/*# 1705 "climaf.f"*/
	    wegub[i - 1] *= bl12_2.qred[i - 1];
/*# 1706 "climaf.f"*/
	    wegl0[i - 1] *= bl12_2.qred[i - 1];
/*# 1707 "climaf.f"*/
	    wegu[i - 1] *= bl12_2.qred[i - 1];
/*# 1708 "climaf.f"*/
	}
/*# 1709 "climaf.f"*/
	goto L15;
/*# 1710 "climaf.f"*/
L14:
/*# 1711 "climaf.f"*/
	r1 = exp(-bl12_2.beta * hl[i - 1]) / bl12_2.beta;
/*# 1712 "climaf.f"*/
	r2 = exp(-bl12_2.beta * hu[i - 1]) / bl12_2.beta;
/*# 1713 "climaf.f"*/
	wegub[i - 1] = q1000[i - 1] * (r1 - r2);
/*# 1714 "climaf.f"*/
	wegl0[i - 1] = wegh[i - 1] - q1000[i - 1] * r1;
/*# 1715 "climaf.f"*/
	wegu[i - 1] = q1000[i - 1] * r2;
/*# 1716 "climaf.f"*/
L15:
	stmo_1.wegcll[i - 1] = wegub[i - 1];
/*# 1717 "climaf.f"*/
/* L12: */
    }



/*  SHORTWAVE */
/*# 1722 "climaf.f"*/
L13:
    for (i = 1; i <= 180; ++i) {
/*  ALBEDO CLOUDS (ACLOUD) */
/*# 1724 "climaf.f"*/
	if (wegub[i - 1] > 0.) {
/*# 1725 "climaf.f"*/
	    acloud = 1. - exp(-bl1_3.alf2 * pow_dd(&wegub[i - 1], &
		    bl10_5.wolk1) / bl10_5.zkk[i - 1]);
/*         ACLOUD = 1.0D0-DEXP(-ALF2*CLOUDW/ZKK(I)) */
/*# 1727 "climaf.f"*/
	} else {
/*          WRITE(*,*) 'STRAHL, I',I,WEGUB(I) */
/*          STOP 'STOP 11' */
/*# 1730 "climaf.f"*/
	    *fall = 11.;
/*# 1731 "climaf.f"*/
	    return 0;
/*# 1732 "climaf.f"*/
	}
/*  ABSORPTION KURZWELLIG (KAPPA) */
/*# 1734 "climaf.f"*/
	qr = wegh[i - 1] * .005 / (wegh[i - 1] * .01 + 1.);
/*# 1735 "climaf.f"*/
	kappa1 = bl10_5.kap1 + qr;
/*# 1736 "climaf.f"*/
	kappa2 = bl10_5.kap2 + qr;
/*# 1737 "climaf.f"*/
	kappa[i] = kappa1 * (1 - bew[i]) + kappa2 * bew[i];
/*  DURCHLAESSIGKEIT (TRANS) */
/*# 1739 "climaf.f"*/
	trans = 1. - kappa1 - bl10_5.alf1;
/*  ABSORPTION ATMOS (A) UND BODEN (S) */
/*# 1741 "climaf.f"*/
	bq = 1. - bl10_5.alf1 * ass[i];
/*# 1742 "climaf.f"*/
/* Computing 2nd power */
	d_1 = trans;
	aclear = 1. - bl10_5.alf1 - (d_1 * d_1 * ass[i] + trans * (1. - ass[i]
		) / bq);
/*# 1743 "climaf.f"*/
	sclear = trans * (1 - ass[i]) / bq;
/*# 1744 "climaf.f"*/
	trans = 1. - kappa2 - acloud;
/*# 1745 "climaf.f"*/
	bq = 1. - acloud * ass[i];
/*# 1746 "climaf.f"*/
/* Computing 2nd power */
	d_1 = trans;
	acloudy = 1. - acloud - (d_1 * d_1 * ass[i] + trans * (1. - ass[i]) / 
		bq);
/*# 1747 "climaf.f"*/
	scloudy = trans * (1 - ass[i]) / bq;

/*# 1749 "climaf.f"*/
	absa[i] = (1. - bew[i]) * aclear + bew[i] * acloudy;
/*# 1750 "climaf.f"*/
	abso[i] = (1. - bew[i]) * sclear + bew[i] * scloudy;
/*# 1751 "climaf.f"*/
	albw[i] = acloud;
/*# 1752 "climaf.f"*/
/* L20: */
    }

/* LONGWAVE */
/*# 1755 "climaf.f"*/
    for (i = 1; i <= 180; ++i) {
/*# 1756 "climaf.f"*/
	ch = co2 * .1 * (bl1_3.tropos[i - 1] - berg[i]);
/*# 1757 "climaf.f"*/
	if (ch < 0.) {
/*          WRITE(*,*) 'CH ',CH,I,TROPOS(I),BERG(I) */
/*          STOP 'STOP 12' */
/*# 1760 "climaf.f"*/
	    *fall = 12.;
/*# 1761 "climaf.f"*/
	    return 0;
/*# 1762 "climaf.f"*/
	}
/*# 1763 "climaf.f"*/
	cl0 = co2 * .1 * (hl[i - 1] - berg[i]);
/*# 1764 "climaf.f"*/
	cu = co2 * .1 * (bl1_3.tropos[i - 1] - hu[i - 1]);
/*# 1765 "climaf.f"*/
	if (cu < 0.) {
/*          WRITE(*,*) 'CU ',CU */
/*          STOP 'STOP 13' */
/*# 1768 "climaf.f"*/
	    *fall = 13.;
/*# 1769 "climaf.f"*/
	    return 0;
/*# 1770 "climaf.f"*/
	}
/*# 1771 "climaf.f"*/
	d_1 = wegh[i - 1] * .1;
	tauh = tau_(&d_1, &ch, &bl10_5.gam, &bl10_5.cohle, &c__1, fall);
/*# 1772 "climaf.f"*/
	d_1 = wegl0[i - 1] * .1;
	taul0 = tau_(&d_1, &cl0, &bl10_5.gam, &bl10_5.cohle, &c__2, fall);
/*# 1773 "climaf.f"*/
	d_1 = wegu[i - 1] * .1;
	tauu = tau_(&d_1, &cu, &bl10_5.gam, &bl10_5.cohle, &c__3, fall);
/*# 1774 "climaf.f"*/
	zm = bl1_3.tropos[i - 1] * bl12_2.exbeta + berg[i] * (1. - 
		bl12_2.exbeta);
/*# 1775 "climaf.f"*/
	d_1 = ta[i] - bl10_5.laps * zm;
	fam = sigma * (d_1 * d_1) * (d_1 * d_1);
/*# 1776 "climaf.f"*/
	tl = ta[i] - bl10_5.laps * hl[i - 1];
/*# 1777 "climaf.f"*/
	fl = sigma * (tl * tl) * (tl * tl);
/*# 1778 "climaf.f"*/
	tu = ta[i] - bl10_5.laps * hu[i - 1];
/*# 1779 "climaf.f"*/
	fu = sigma * (tu * tu) * (tu * tu);
/*# 1780 "climaf.f"*/
	zum = bl1_3.tropos[i - 1] * bl12_2.exbeta + hu[i - 1] * (1. - 
		bl12_2.exbeta);
/*# 1781 "climaf.f"*/
	d_1 = ta[i] - bl10_5.laps * zum;
	fum = sigma * (d_1 * d_1) * (d_1 * d_1);
/*# 1782 "climaf.f"*/
	downh = (1. - tauh) * fa[i - 1];
/*# 1783 "climaf.f"*/
	downl0 = (1. - taul0) * fa[i - 1];
/*# 1784 "climaf.f"*/
	counter = downh * (1. - bew[i]) + (downl0 + taul0 * fl) * bew[i];
/*# 1785 "climaf.f"*/
	lo[i] = counter - ff[i - 1];

/*# 1787 "climaf.f"*/
	fenstw = fu * tauu;
/*# 1788 "climaf.f"*/
	fenstc = tauh * ff[i - 1];
/*# 1789 "climaf.f"*/
	upw = fum * (1. - tauu);
/*# 1790 "climaf.f"*/
	upc = fam * (1. - tauh);
/*# 1791 "climaf.f"*/
	clear = fenstc + upc;
/*# 1792 "climaf.f"*/
	cloudy = fenstw + upw;
/*# 1793 "climaf.f"*/
	lg = -(1. - bew[i]) * clear - bew[i] * cloudy;
/*# 1794 "climaf.f"*/
	la[i] = lg - lo[i];
/*# 1795 "climaf.f"*/
	hls[i] = hl[i - 1];
/*# 1796 "climaf.f"*/
	hus[i] = hu[i - 1];
/*# 1797 "climaf.f"*/
	feedb = clear - cloudy;
/*# 1798 "climaf.f"*/
	cquot[i] = feedb / clear;
/*# 1799 "climaf.f"*/
	contr[i] = tauh;
/*# 1800 "climaf.f"*/
	contr[i + 180] = wegh[i - 1];
/*# 1801 "climaf.f"*/
	contr[i + 360] = fenstc;
/*# 1802 "climaf.f"*/
	contr[i + 540] = fenstw;
/*# 1803 "climaf.f"*/
	contr[i + 720] = upc;
/*# 1804 "climaf.f"*/
	contr[i + 900] = upw;
/*# 1805 "climaf.f"*/
/* L21: */
    }

/*# 1807 "climaf.f"*/
    return 0;
/*# 1808 "climaf.f"*/
} /* strahl_ */

/**************************************************************************/
/*# 1810 "climaf.f"*/
doublereal tau_(doublereal *wasser, doublereal *carbon, doublereal *parw, 
	doublereal *parc, integer *num, doublereal *fall)
{
    /* System generated locals */
    doublereal ret_val, d_1;

    /* Builtin functions */
    double d_lg10(doublereal *), pow_dd(doublereal *, doublereal *), exp(
	    doublereal);

    /* Local variables */
    static doublereal c, w;

/*# 1811 "climaf.f"*/
/*# 1812 "climaf.f"*/
/*# 1813 "climaf.f"*/
    if (*carbon >= 0.) {
/*        C=PARC*CARBON/(1.0D0+CARBON**0.85D0) */
/*# 1815 "climaf.f"*/
	d_1 = *carbon + 1.;
	c = *parc * d_lg10(&d_1);
/*# 1816 "climaf.f"*/
    } else {
/*         WRITE(*,*) 'CARBON, NUM', CARBON, NUM */
/*         STOP 'STOP 14' */
/*# 1819 "climaf.f"*/
	*fall = 14.;
/*# 1820 "climaf.f"*/
	ret_val = 0.;
/* C    TAU=0 just set for cross-compiled C-Version. Schuetz */
/*# 1822 "climaf.f"*/
	return ret_val;
/*# 1823 "climaf.f"*/
    }
/*# 1824 "climaf.f"*/
    if (*wasser >= 0.) {
/*        W=PARW*WASSER/(1.0D0+DSQRT(WASSER)) */
/*# 1826 "climaf.f"*/
	w = *parw * pow_dd(wasser, &c_b275);
/*# 1827 "climaf.f"*/
    } else {
/*         WRITE(*,*) 'WASSER, NUM', WASSER, NUM */
/*         STOP 'STOP 15' */
/*# 1830 "climaf.f"*/
	*fall = 15.;
/*# 1831 "climaf.f"*/
	ret_val = 0.;
/* C    TAU=0 just set for cross-compiled C-Version. Schuetz */
/*# 1833 "climaf.f"*/
	return ret_val;
/*# 1834 "climaf.f"*/
    }
/*# 1835 "climaf.f"*/
    ret_val = exp(-w - c);
/*# 1836 "climaf.f"*/
    return ret_val;
/*# 1837 "climaf.f"*/
} /* tau_ */

/* === */

/*# 1840 "climaf.f"*/
/* Subroutine */ int moist_(doublereal *qsto, doublereal *qstl, doublereal *
	qsti, doublereal *qstli, doublereal *lamda, doublereal *ewasser, 
	doublereal *eland, doublereal *p, doublereal *bew, doublereal *bewl, 
	doublereal *rh, doublereal *pcrit, doublereal *sch, doublereal *q)
{
    /* Initialized data */

    static doublereal eps2 = .02;
    static doublereal xh = 0.;

    /* System generated locals */
    doublereal d_1;

    /* Local variables */
    static doublereal weff;
    static integer i;
    static doublereal pland, ev;
    extern doublereal sprung_(doublereal *, doublereal *);
    static doublereal evi, pwasser;


/*# 1843 "climaf.f"*/
/*# 1844 "climaf.f"*/

/*# 1846 "climaf.f"*/
/*# 1847 "climaf.f"*/

/*# 1851 "climaf.f"*/
/*# 1853 "climaf.f"*/
/*# 1855 "climaf.f"*/
/*# 1856 "climaf.f"*/

/*# 1858 "climaf.f"*/
    /* Parameter adjustments */
    --q;
    --sch;
    --pcrit;
    --rh;
    --bewl;
    --bew;
    --p;
    --eland;
    --ewasser;
    --lamda;
    --qstli;
    --qsti;
    --qstl;
    --qsto;

    /* Function Body */
/*     PARAMETER: PC(1), RMIN, RCRIT, */
/*     RMIN<RCRIT<0.90 */

/*     EVA UND P IN M/YEAR */

/*# 1864 "climaf.f"*/
    for (i = 1; i <= 180; ++i) {
/*# 1865 "climaf.f"*/
	ev = qsto[i] - q[i];
/*# 1866 "climaf.f"*/
	evi = qsti[i] - q[i];
/*# 1867 "climaf.f"*/
	ewasser[i] = lamda[i] / bl11_1.cp * .365 * (sch[i] * ev + (1. - sch[i]
		) * evi * 1.135);
/*       LAND.. */
/*# 1870 "climaf.f"*/
	ev = qstl[i] - q[i] * bl12_1.qred[i - 1];
/*# 1871 "climaf.f"*/
	evi = qstli[i] - q[i] * bl12_1.qred[i - 1];
/*# 1872 "climaf.f"*/
	eland[i] = lamda[i] / bl11_1.cp * .365 * (sch[i] * bl12_1.w0 * ev + (
		1. - sch[i]) * evi * 1.135);

/*# 1875 "climaf.f"*/
	weff = 1.;
/*# 1876 "climaf.f"*/
	pwasser = weff * bl12_1.pc[0] * stmo_1.wegclw[i - 1] * bew[i];
/*# 1877 "climaf.f"*/
	pland = (xh * bl3_1.height[i - 1] + 1.) * weff * bl12_1.pc[0] * 
		stmo_1.wegcll[i - 1] * bewl[i];
/*# 1878 "climaf.f"*/
	d_1 = rh[i] - bl12_1.rcrit;
	pcrit[i] = sprung_(&d_1, &eps2) / eps2;
/*       PCRIT(I)=0. */
/*# 1880 "climaf.f"*/
	p[i] = bl3_1.fland[i - 1] * pland + (1. - bl3_1.fland[i - 1]) * 
		pwasser;

/*# 1882 "climaf.f"*/
/* L10: */
    }

/*# 1884 "climaf.f"*/
    return 0;
/*# 1885 "climaf.f"*/
} /* moist_ */

/* === */

/*# 1888 "climaf.f"*/
/* Subroutine */ int legend_(doublereal *x, integer *j, doublereal *pp)
{
    /* System generated locals */
    integer i_1;

    /* Local variables */
    static integer i;
    static doublereal p[41];

/* LEGENDRE POLYNOMIALS */

/*# 1891 "climaf.f"*/
/*# 1892 "climaf.f"*/
/*# 1893 "climaf.f"*/
    p[0] = 1.;
/*# 1894 "climaf.f"*/
    p[1] = *x;
/*# 1895 "climaf.f"*/
    i_1 = *j;
    for (i = 2; i <= i_1; ++i) {
/*# 1896 "climaf.f"*/
	p[i] = (((i << 1) - 1) * *x * p[i - 1] - (i - 1) * p[i - 2]) / i;
/*# 1897 "climaf.f"*/
/* L10: */
    }
/*# 1898 "climaf.f"*/
    *pp = p[*j];
/*# 1899 "climaf.f"*/
    return 0;
/*# 1900 "climaf.f"*/
} /* legend_ */

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*# 1902 "climaf.f"*/
/* Subroutine */ int summe_(integer *n, doublereal *f, doublereal *wert)
{
    /* Initialized data */

    static integer lauf = 0;

    static integer i;
    static doublereal sum1, sum2;


/*# 1904 "climaf.f"*/
/*# 1905 "climaf.f"*/

/*# 1907 "climaf.f"*/
/*# 1908 "climaf.f"*/
/*# 1910 "climaf.f"*/

/*# 1912 "climaf.f"*/
    /* Parameter adjustments */
    --f;

    /* Function Body */

/*# 1914 "climaf.f"*/
    if (lauf == 0) {
	goto L12;
    }
/*# 1915 "climaf.f"*/
    goto L13;
/*# 1916 "climaf.f"*/
L12:
    sum1 = 0.;
/*# 1917 "climaf.f"*/
    for (i = 1; i <= 180; ++i) {
/*# 1918 "climaf.f"*/
/* L14: */
	sum1 += bl3_3.zc[i - 1];
    }
/*# 1919 "climaf.f"*/
L13:
    sum2 = 0.;
/*# 1920 "climaf.f"*/
    for (i = 1; i <= 180; ++i) {
/*# 1921 "climaf.f"*/
/* L10: */
	sum2 += bl3_3.zc[i - 1] * f[i];
    }
/*# 1922 "climaf.f"*/
    *wert = sum2 / sum1;
/*# 1923 "climaf.f"*/
    lauf = 1;
/*# 1924 "climaf.f"*/
    return 0;
/*# 1925 "climaf.f"*/
} /* summe_ */

/* ******************************************* */
/*# 1927 "climaf.f"*/
/* Subroutine */ int summ_(doublereal *f, doublereal *wert)
{
    /* Initialized data */

    static integer lauf = 0;

    /* Builtin functions */
    double atan(doublereal), cos(doublereal);

    /* Local variables */
    static integer i;
    static doublereal pi, zc[18], ata, sum1, sum2;


/*# 1929 "climaf.f"*/
/*# 1930 "climaf.f"*/

/*# 1932 "climaf.f"*/
/*# 1933 "climaf.f"*/
/*# 1934 "climaf.f"*/
/*# 1937 "climaf.f"*/

/*# 1939 "climaf.f"*/
    /* Parameter adjustments */
    --f;

    /* Function Body */

/*# 1941 "climaf.f"*/
    if (lauf == 0) {
	goto L12;
    }
/*# 1942 "climaf.f"*/
    goto L13;
/*# 1943 "climaf.f"*/
L12:
/*# 1944 "climaf.f"*/
    ata = atan(1.);
/*# 1945 "climaf.f"*/
    pi = ata * 4;
/*# 1946 "climaf.f"*/
    for (i = 1; i <= 18; ++i) {
/*# 1947 "climaf.f"*/
/* L15: */
	zc[i - 1] = cos(expe_2.phi[i - 1] * pi / 180.);
    }
/*# 1948 "climaf.f"*/
    sum1 = 0.;
/*# 1949 "climaf.f"*/
    for (i = 1; i <= 9; ++i) {
/*# 1950 "climaf.f"*/
/* L14: */
	sum1 += zc[i - 1];
    }
/*# 1951 "climaf.f"*/
L13:
    sum2 = 0.;
/*# 1952 "climaf.f"*/
    for (i = 1; i <= 18; ++i) {
/*# 1953 "climaf.f"*/
/* L10: */
	sum2 += zc[i - 1] * f[i];
    }
/*# 1954 "climaf.f"*/
    *wert = sum2 * .5 / sum1;
/*# 1955 "climaf.f"*/
    lauf = 1;
/*# 1956 "climaf.f"*/
    return 0;
/*# 1957 "climaf.f"*/
} /* summ_ */

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/*# 1959 "climaf.f"*/
/* Subroutine */ int hadl_(doublereal *dx, doublereal *xs, doublereal *gradta,
	 doublereal *gradc, doublereal *had)
{
    static integer i, j;
    static doublereal dif, gra[90], grc[90], pru, xst[90];


/*# 1961 "climaf.f"*/
/*# 1962 "climaf.f"*/
/*# 1963 "climaf.f"*/

/*# 1966 "climaf.f"*/
    /* Parameter adjustments */
    --had;
    --gradc;
    --gradta;
    --xs;

    /* Function Body */
    for (i = 1; i <= 179; ++i) {
/*# 1967 "climaf.f"*/
	dif = gradta[i] - gradta[i + 1];
/*# 1968 "climaf.f"*/
	if (dif != 0.) {
	    goto L1;
	}
/*# 1969 "climaf.f"*/
/* L10: */
    }
/*# 1970 "climaf.f"*/
    had[1] = xs[1];
/*# 1971 "climaf.f"*/
    had[2] = xs[180];
/*# 1972 "climaf.f"*/
    return 0;
/*# 1973 "climaf.f"*/
L1:
/*     SUED */
/*# 1975 "climaf.f"*/
    for (i = 1; i <= 90; ++i) {
/*# 1976 "climaf.f"*/
	j = 91 - i;
/*# 1977 "climaf.f"*/
	xst[i - 1] = xs[j];
/*# 1978 "climaf.f"*/
	gra[i - 1] = gradta[j];
/*# 1979 "climaf.f"*/
/* L70: */
	grc[i - 1] = gradc[j];
    }
/*# 1980 "climaf.f"*/
    for (i = 1; i <= 89; ++i) {
/*# 1981 "climaf.f"*/
	pru = (gra[i - 1] - grc[i - 1]) * (gra[i] - grc[i]);
/*# 1982 "climaf.f"*/
	if (pru > 0.) {
	    goto L2;
	}
/*# 1983 "climaf.f"*/
	had[1] = xst[i - 1] - *dx * (grc[i - 1] - gra[i - 1]) / (gra[i] - gra[
		i - 1] - (grc[i] - grc[i - 1]));
/*# 1985 "climaf.f"*/
	goto L4;
/*# 1986 "climaf.f"*/
L2:
	;
    }

/*# 1988 "climaf.f"*/
    had[1] = xs[1];
/*# 1989 "climaf.f"*/
L4:
/*     NORD */
/*# 1991 "climaf.f"*/
    for (i = 1; i <= 90; ++i) {
/*# 1992 "climaf.f"*/
	j = i + 90;
/*# 1993 "climaf.f"*/
	xst[i - 1] = xs[j];
/*# 1994 "climaf.f"*/
	grc[i - 1] = gradc[j];
/*# 1995 "climaf.f"*/
/* L71: */
	gra[i - 1] = gradta[j];
    }
/*# 1996 "climaf.f"*/
    for (i = 1; i <= 89; ++i) {
/*# 1997 "climaf.f"*/
	pru = (gra[i - 1] - grc[i - 1]) * (gra[i] - grc[i]);
/*# 1998 "climaf.f"*/
	if (pru > 0.) {
	    goto L3;
	}
/*# 1999 "climaf.f"*/
	had[2] = xst[i - 1] + *dx * (grc[i - 1] - gra[i - 1]) / (gra[i] - gra[
		i - 1] - (grc[i] - grc[i - 1]));
/*# 2001 "climaf.f"*/
	goto L5;
/*# 2002 "climaf.f"*/
L3:
	;
    }
/*# 2003 "climaf.f"*/
    had[2] = xs[180];
/*# 2004 "climaf.f"*/
L5:
    return 0;
/*# 2005 "climaf.f"*/
} /* hadl_ */

/* **********************************************8 */

/*# 2008 "climaf.f"*/
/* Subroutine */ int eisli_(doublereal *ts, doublereal *eisl)
{
    static integer i;
    static doublereal xs, dif, pru;

/*# 2009 "climaf.f"*/
/*# 2010 "climaf.f"*/
/*# 2011 "climaf.f"*/
/*# 2012 "climaf.f"*/
/*# 2014 "climaf.f"*/


/*# 2018 "climaf.f"*/
    /* Parameter adjustments */
    --eisl;
    --ts;

    /* Function Body */
    for (i = 1; i <= 179; ++i) {
/*# 2019 "climaf.f"*/
	dif = ts[i] - ts[i + 1];
/*# 2020 "climaf.f"*/
	if (dif != 0.) {
	    goto L1;
	}
/*# 2021 "climaf.f"*/
/* L10: */
    }
/*# 2022 "climaf.f"*/
    if (ts[90] < bl11_1.tf) {
/*# 2023 "climaf.f"*/
	eisl[1] = 0.;
/*# 2024 "climaf.f"*/
	eisl[2] = 0.;
/*# 2025 "climaf.f"*/
    } else {
/*# 2026 "climaf.f"*/
	eisl[1] = -90.;
/*# 2027 "climaf.f"*/
	eisl[2] = 90.;
/*# 2028 "climaf.f"*/
    }
/*# 2029 "climaf.f"*/
    return 0;
/*# 2030 "climaf.f"*/
L1:
/*# 2031 "climaf.f"*/
    for (i = 1; i <= 89; ++i) {
/*# 2032 "climaf.f"*/
	pru = (ts[i] - bl11_1.tf) * (ts[i + 1] - bl11_1.tf);
/*# 2033 "climaf.f"*/
	if (pru > 0.) {
	    goto L47;
	}
/*# 2034 "climaf.f"*/
	xs = bl3_3.xst[i - 1] + bl3_3.dx * (bl11_1.tf - ts[i]) / (ts[i + 1] - 
		ts[i]);
/*# 2035 "climaf.f"*/
	goto L50;
/*# 2036 "climaf.f"*/
L47:
	;
    }
/*# 2037 "climaf.f"*/
    if (ts[89] < bl11_1.tf) {
	eisl[1] = 0.;
    }
/*# 2038 "climaf.f"*/
    if (ts[1] >= bl11_1.tf) {
	eisl[1] = -90.;
    }
/*# 2039 "climaf.f"*/
    goto L52;
/*# 2040 "climaf.f"*/
L50:
    eisl[1] = xs * 180. / bl11_1.pi;
/*# 2041 "climaf.f"*/
L52:
/*# 2042 "climaf.f"*/
    for (i = 90; i <= 179; ++i) {
/*# 2043 "climaf.f"*/
	pru = (ts[i] - bl11_1.tf) * (ts[i + 1] - bl11_1.tf);
/*# 2044 "climaf.f"*/
	if (pru > 0.) {
	    goto L49;
	}
/*# 2045 "climaf.f"*/
	xs = bl3_3.xst[i - 1] + bl3_3.dx * (bl11_1.tf - ts[i]) / (ts[i + 1] - 
		ts[i]);
/*# 2046 "climaf.f"*/
	goto L48;
/*# 2047 "climaf.f"*/
L49:
	;
    }
/*# 2048 "climaf.f"*/
    if (ts[91] < bl11_1.tf) {
	eisl[2] = 0.;
    }
/*# 2049 "climaf.f"*/
    if (ts[180] >= bl11_1.tf) {
	eisl[1] = 90.;
    }
/*# 2050 "climaf.f"*/
    return 0;
/*# 2051 "climaf.f"*/
L48:
    eisl[2] = xs * 180. / bl11_1.pi;
/*# 2052 "climaf.f"*/
    return 0;
/*# 2053 "climaf.f"*/
} /* eisli_ */

/* *************************************** */
/*# 2055 "climaf.f"*/
doublereal sump_(doublereal *x, doublereal *eps, doublereal *x0, doublereal *
	x1)
{
    /* Initialized data */

    static doublereal a = 0.;
    static doublereal b = 1.;

    /* System generated locals */
    doublereal ret_val, d_1;

    /* Local variables */
    static doublereal r1, r2;
    extern doublereal sprung_(doublereal *, doublereal *);

/*# 2056 "climaf.f"*/

/*# 2058 "climaf.f"*/

/*# 2060 "climaf.f"*/
    if (*x > *x1 + *eps) {
/*# 2061 "climaf.f"*/
	ret_val = b;
/*# 2062 "climaf.f"*/
	return ret_val;
/*# 2063 "climaf.f"*/
    }
/*# 2064 "climaf.f"*/
    if (*x < *x0 - *eps) {
/*# 2065 "climaf.f"*/
	ret_val = a;
/*# 2066 "climaf.f"*/
	return ret_val;
/*# 2067 "climaf.f"*/
    }
/*# 2068 "climaf.f"*/
    d_1 = *x - *x0;
    r1 = sprung_(&d_1, eps);
/*# 2069 "climaf.f"*/
    d_1 = *x - *x1;
    r2 = sprung_(&d_1, eps);
/*# 2070 "climaf.f"*/
    ret_val = a + (b - a) / (*x1 - *x0) * (r1 - r2);
/*# 2071 "climaf.f"*/
    return ret_val;
/*# 2072 "climaf.f"*/
} /* sump_ */

/* *************************************** */
/*# 2074 "climaf.f"*/
doublereal sprung_(doublereal *x, doublereal *eps)
{
    /* System generated locals */
    doublereal ret_val, d_1, d_2, d_3, d_4;


/*# 2076 "climaf.f"*/
/*# 2077 "climaf.f"*/
    if (*x < -(*eps)) {
	goto L1;
    }
/*# 2078 "climaf.f"*/
    if (*x > *eps) {
	goto L2;
    }
/*# 2079 "climaf.f"*/
/* Computing 3rd power */
    d_1 = *x + *eps, d_2 = d_1;
/* Computing 3rd power */
    d_3 = *eps, d_4 = d_3;
    ret_val = d_2 * (d_1 * d_1) * (*eps * 3 - *x) / (d_4 * (d_3 * d_3) * 16);
/*# 2080 "climaf.f"*/
    return ret_val;
/*# 2081 "climaf.f"*/
L1:
    ret_val = 0.;
/*# 2082 "climaf.f"*/
    return ret_val;
/*# 2083 "climaf.f"*/
L2:
    ret_val = *x;
/*# 2084 "climaf.f"*/
    return ret_val;
/*# 2085 "climaf.f"*/
} /* sprung_ */

/* ********************************************** */

/*   IMSL ROUTINE NAME   - VBLA=DCOPY */

/* ----------------------------------------------------------------------- */

/*   COMPUTER            - IBM/DOUBLE */

/*   LATEST REVISION     - JANUARY 1, 1978 */

/*   PURPOSE             - COPY A VECTOR X TO A VECTOR Y, BOTH */
/*                           DOUBLE PRECISION */

/*   USAGE               - CALL DCOPY (N,DX,INCX,DY,INCY) */

/*   ARGUMENTS    N      - LENGTH OF VECTORS X AND Y. (INPUT) */
/*                DX     - DOUBLE PRECISION VECTOR OF LENGTH */
/*                           MAX(N*IABS(INCX),1). (INPUT) */
/*                INCX   - DISPLACEMENT BETWEEN ELEMENTS OF DX. (INPUT) */
/*                           X(I) IS DEFINED TO BE.. */
/*                           DX(1+(I-1)*INCX) IF INCX.GE.0 OR */
/*                           DX(1+(I-N)*INCX) IF INCX.LT.0. */
/*                DY     - DOUBLE PRECISION VECTOR OF LENGTH */
/*                           MAX(N*IABS(INCY),1). (OUTPUT) */
/*                           DCOPY COPIES X(I) TO Y(I) FOR I=1,...,N. */
/*                           X(I) AND Y(I) REFER TO SPECIFIC ELEMENTS */
/*                           OF DX AND DY, RESPECTIVELY. SEE INCX AND */
/*                           INCY ARGUMENT DESCRIPTIONS. */
/*                INCY   - DISPLACEMENT BETWEEN ELEMENTS OF DY. (INPUT) */
/*                           Y(I) IS DEFINED TO BE.. */
/*                           DY(1+(I-1)*INCY) IF INCY.GE.0 OR */
/*                           DY(1+(I-N)*INCY) IF INCY.LT.0. */

/*   PRECISION/HARDWARE  - DOUBLE/ALL */

/*   REQD. IMSL ROUTINES - NONE REQUIRED */

/*   NOTATION            - INFORMATION ON SPECIAL NOTATION AND */
/*                           CONVENTIONS IS AVAILABLE IN THE MANUAL */
/*                           INTRODUCTION OR THROUGH IMSL ROUTINE UHELP */

/*   COPYRIGHT           - 1978 BY IMSL, INC. ALL RIGHTS RESERVED. */

/*   WARRANTY            - IMSL WARRANTS ONLY THAT IMSL TESTING HAS BEEN */
/*                           APPLIED TO THIS CODE. NO OTHER WARRANTY, */
/*                           EXPRESSED OR IMPLIED, IS APPLICABLE. */

/* ----------------------------------------------------------------------- */

/*# 2135 "climaf.f"*/
/* Subroutine */ int dcopy_(integer *n, doublereal *dx, integer *incx, 
	doublereal *dy, integer *incy)
{
    /* System generated locals */
    integer i_1, i_2;

    /* Local variables */
    static integer i, m, ns, iy, ix, mp1;


/*                                  SPECIFICATIONS FOR ARGUMENTS */
/*# 2138 "climaf.f"*/
/*# 2139 "climaf.f"*/
/*                                  SPECIFICATIONS FOR LOCAL VARIABLES */
/*# 2141 "climaf.f"*/
/*                                  FIRST EXECUTABLE STATEMENT */
/*# 2143 "climaf.f"*/
    /* Parameter adjustments */
    --dy;
    --dx;

    /* Function Body */
    if (*n <= 0) {
	return 0;
    }
/*# 2144 "climaf.f"*/
    if (*incx == *incy) {
	if ((i_1 = *incx - 1) < 0) {
	    goto L5;
	} else if (i_1 == 0) {
	    goto L15;
	} else {
	    goto L35;
	}
    }
/*# 2145 "climaf.f"*/
L5:
/*                                  CODE FOR UNEQUAL OR NONPOSITIVE */
/*                                    INCREMENTS. */
/*# 2148 "climaf.f"*/
    ix = 1;
/*# 2149 "climaf.f"*/
    iy = 1;
/*# 2150 "climaf.f"*/
    if (*incx < 0) {
	ix = (-(*n) + 1) * *incx + 1;
    }
/*# 2151 "climaf.f"*/
    if (*incy < 0) {
	iy = (-(*n) + 1) * *incy + 1;
    }
/*# 2152 "climaf.f"*/
    i_1 = *n;
    for (i = 1; i <= i_1; ++i) {
/*# 2153 "climaf.f"*/
	dy[iy] = dx[ix];
/*# 2154 "climaf.f"*/
	ix += *incx;
/*# 2155 "climaf.f"*/
	iy += *incy;
/*# 2156 "climaf.f"*/
/* L10: */
    }
/*# 2157 "climaf.f"*/
    return 0;
/*                                  CODE FOR BOTH INCREMENTS EQUAL TO 1 */

/*                                    CLEAN-UP LOOP SO REMAINING VECTOR */

/*                                    LENGTH IS A MULTIPLE OF 7. */
/*# 2161 "climaf.f"*/
L15:
    m = *n - *n / 7 * 7;
/*# 2162 "climaf.f"*/
    if (m == 0) {
	goto L25;
    }
/*# 2163 "climaf.f"*/
    i_1 = m;
    for (i = 1; i <= i_1; ++i) {
/*# 2164 "climaf.f"*/
	dy[i] = dx[i];
/*# 2165 "climaf.f"*/
/* L20: */
    }
/*# 2166 "climaf.f"*/
    if (*n < 7) {
	return 0;
    }
/*# 2167 "climaf.f"*/
L25:
    mp1 = m + 1;
/*# 2168 "climaf.f"*/
    i_1 = *n;
    for (i = mp1; i <= i_1; i += 7) {
/*# 2169 "climaf.f"*/
	dy[i] = dx[i];
/*# 2170 "climaf.f"*/
	dy[i + 1] = dx[i + 1];
/*# 2171 "climaf.f"*/
	dy[i + 2] = dx[i + 2];
/*# 2172 "climaf.f"*/
	dy[i + 3] = dx[i + 3];
/*# 2173 "climaf.f"*/
	dy[i + 4] = dx[i + 4];
/*# 2174 "climaf.f"*/
	dy[i + 5] = dx[i + 5];
/*# 2175 "climaf.f"*/
	dy[i + 6] = dx[i + 6];
/*# 2176 "climaf.f"*/
/* L30: */
    }
/*# 2177 "climaf.f"*/
    return 0;
/*                                  CODE FOR EQUAL, POSITIVE, NONUNIT */
/*                                    INCREMENTS. */
/*# 2180 "climaf.f"*/
L35:
/*# 2181 "climaf.f"*/
    ns = *n * *incx;
/*# 2182 "climaf.f"*/
    i_1 = ns;
    i_2 = *incx;
    for (i = 1; i_2 < 0 ? i >= i_1 : i <= i_1; i += i_2) {
/*# 2183 "climaf.f"*/
	dy[i] = dx[i];
/*# 2184 "climaf.f"*/
/* L40: */
    }
/*# 2185 "climaf.f"*/
    return 0;
/*# 2186 "climaf.f"*/
} /* dcopy_ */


/*   IMSL ROUTINE NAME   - VBLA=DNRM2 */

/* ----------------------------------------------------------------------- */

/*   COMPUTER            - IBM/DOUBLE */

/*   LATEST REVISION     - JANUARY 1, 1978 */

/*   PURPOSE             - COMPUTE THE EUCLIDEAN LENGTH OR L2 NORM */
/*                           OF A DOUBLE PRECISION VECTOR */

/*   USAGE               - FUNCTION DNRM2 (N,DX,INCX) */

/*   ARGUMENTS    DNRM2  - DOUBLE PRECISION SQUARE ROOT OF THE SUM FROM */
/*                           I=1 TO N OF X(I)**2. (OUTPUT) */
/*                           X(I) REFERS TO A SPECIFIC ELEMENT OF DX. */
/*                           SEE INCX ARGUMENT DESCRIPTION. */
/*                N      - LENGTH OF VECTOR X. (INPUT) */
/*                DX     - DOUBLE PRECISION VECTOR OF LENGTH N*INCX. */
/*                           (INPUT) */
/*                INCX   - DISPLACEMENT BETWEEN ELEMENTS OF DX. (INPUT) */
/*                           X(I) IS DEFINED TO BE DX(1+(I-1)*INCX). */
/*                           INCX MUST BE GREATER THAN ZERO. */

/*   PRECISION/HARDWARE  - DOUBLE/ALL */

/*   REQD. IMSL ROUTINES - NONE REQUIRED */

/*   NOTATION            - INFORMATION ON SPECIAL NOTATION AND */
/*                           CONVENTIONS IS AVAILABLE IN THE MANUAL */
/*                           INTRODUCTION OR THROUGH IMSL ROUTINE UHELP */

/*   COPYRIGHT           - 1978 BY IMSL, INC. ALL RIGHTS RESERVED. */

/*   WARRANTY            - IMSL WARRANTS ONLY THAT IMSL TESTING HAS BEEN */
/*                           APPLIED TO THIS CODE. NO OTHER WARRANTY, */
/*                           EXPRESSED OR IMPLIED, IS APPLICABLE. */

/* ----------------------------------------------------------------------- */

/*# 2228 "climaf.f"*/
doublereal dnrm2_(integer *n, doublereal *dx, integer *incx)
{
    /* Initialized data */

    static doublereal zero = 0.;
    static doublereal one = 1.;
    static doublereal cutlo = 8.232e-11;
    static doublereal cuthi = 1.304e19;

    /* Format strings */
    static char fmt_15[] = "";
    static char fmt_20[] = "";
    static char fmt_35[] = "";
    static char fmt_40[] = "";

    /* System generated locals */
    integer i_1, i_2;
    doublereal ret_val, d_1;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static doublereal xmax;
    static integer next, i, j, nn;
    static doublereal hitest, sum;

    /* Assigned format variables */
    char *next_fmt;


/*                                  SPECIFICATIONS FOR ARGUMENTS */
/*# 2231 "climaf.f"*/
/*# 2232 "climaf.f"*/
/*                                  SPECIFICATIONS FOR LOCAL VARIABLES */
/*# 2234 "climaf.f"*/
/*# 2235 "climaf.f"*/
/*# 2236 "climaf.f"*/
    /* Parameter adjustments */
    --dx;

    /* Function Body */
/*# 2237 "climaf.f"*/
/*                                  FIRST EXECUTABLE STATEMENT */
/*# 2239 "climaf.f"*/
    if (*n > 0) {
	goto L5;
    }
/*# 2240 "climaf.f"*/
    ret_val = zero;
/*# 2241 "climaf.f"*/
    goto L70;

/*# 2243 "climaf.f"*/
L5:
    next = 0;
    next_fmt = fmt_15;
/*# 2244 "climaf.f"*/
    sum = zero;
/*# 2245 "climaf.f"*/
    nn = *n * *incx;
/*                                  BEGIN MAIN LOOP */
/*# 2247 "climaf.f"*/
    i = 1;
/*# 2248 "climaf.f"*/
L10:
    switch (next) {
	case 0: goto L15;
	case 1: goto L20;
	case 2: goto L35;
	case 3: goto L40;
    }
/*# 2249 "climaf.f"*/
L15:
    if ((d_1 = dx[i], abs(d_1)) > cutlo) {
	goto L55;
    }
/*# 2250 "climaf.f"*/
    next = 1;
    next_fmt = fmt_20;
/*# 2251 "climaf.f"*/
    xmax = zero;
/*                                  PHASE 1. SUM IS ZERO */
/*# 2253 "climaf.f"*/
L20:
    if (dx[i] == zero) {
	goto L65;
    }
/*# 2254 "climaf.f"*/
    if ((d_1 = dx[i], abs(d_1)) > cutlo) {
	goto L55;
    }
/*                                  PREPARE FOR PHASE 2. */
/*# 2256 "climaf.f"*/
    next = 2;
    next_fmt = fmt_35;
/*# 2257 "climaf.f"*/
    goto L30;
/*                                  PREPARE FOR PHASE 4. */
/*# 2259 "climaf.f"*/
L25:
    i = j;
/*# 2260 "climaf.f"*/
    next = 3;
    next_fmt = fmt_40;
/*# 2261 "climaf.f"*/
    sum = sum / dx[i] / dx[i];
/*# 2262 "climaf.f"*/
L30:
    xmax = (d_1 = dx[i], abs(d_1));
/*# 2263 "climaf.f"*/
    goto L45;
/*                                  PHASE 2. SUM IS SMALL. SCALE TO */
/*                                    AVOID DESTRUCTIVE UNDERFLOW. */
/*# 2266 "climaf.f"*/
L35:
    if ((d_1 = dx[i], abs(d_1)) > cutlo) {
	goto L50;
    }
/*                                  COMMON CODE FOR PHASES 2 AND 4. IN */
/*                                    PHASE 4 SUM IS LARGE. SCALE TO */
/*                                    AVOID OVERFLOW. */
/*# 2270 "climaf.f"*/
L40:
    if ((d_1 = dx[i], abs(d_1)) <= xmax) {
	goto L45;
    }
/*# 2271 "climaf.f"*/
/* Computing 2nd power */
    d_1 = xmax / dx[i];
    sum = one + sum * (d_1 * d_1);
/*# 2272 "climaf.f"*/
    xmax = (d_1 = dx[i], abs(d_1));
/*# 2273 "climaf.f"*/
    goto L65;

/*# 2275 "climaf.f"*/
L45:
/* Computing 2nd power */
    d_1 = dx[i] / xmax;
    sum += d_1 * d_1;
/*# 2276 "climaf.f"*/
    goto L65;
/*                                  PREPARE FOR PHASE 3. */
/*# 2278 "climaf.f"*/
L50:
    sum = sum * xmax * xmax;
/*                                  FOR REAL OR D.P. SET HITEST = */
/*                                    CUTHI/N FOR COMPLEX SET HITEST = */
/*                                    CUTHI/(2*N) */
/*# 2282 "climaf.f"*/
L55:
    hitest = cuthi / (doublereal) (*n);
/*                                  PHASE 3. SUM IS MID-RANGE. NO */
/*                                    SCALING. */
/*# 2285 "climaf.f"*/
    i_1 = nn;
    i_2 = *incx;
    for (j = i; i_2 < 0 ? j >= i_1 : j <= i_1; j += i_2) {
/*# 2286 "climaf.f"*/
	if ((d_1 = dx[j], abs(d_1)) >= hitest) {
	    goto L25;
	}
/*# 2287 "climaf.f"*/
/* L60: */
/* Computing 2nd power */
	d_1 = dx[j];
	sum += d_1 * d_1;
    }
/*# 2288 "climaf.f"*/
    ret_val = sqrt(sum);
/*# 2289 "climaf.f"*/
    goto L70;

/*# 2291 "climaf.f"*/
L65:
/*# 2292 "climaf.f"*/
    i += *incx;
/*# 2293 "climaf.f"*/
    if (i <= nn) {
	goto L10;
    }
/*                                  END OF MAIN LOOP. COMPUTE SQUARE */
/*                                    ROOT AND ADJUST FOR SCALING. */
/*# 2296 "climaf.f"*/
    ret_val = xmax * sqrt(sum);
/*# 2297 "climaf.f"*/
L70:
/*# 2298 "climaf.f"*/
    return ret_val;
/*# 2299 "climaf.f"*/
} /* dnrm2_ */


/*# 2301 "climaf.f"*/
/* Subroutine */ int dgbfa_(doublereal *abd, integer *lda, integer *n, 
	integer *ml, integer *mu, integer *ipvt, integer *info)
{
    /* System generated locals */
    integer abd_dim1, abd_offset, i_1, i_2, i_3, i_4;

    /* Local variables */
    static integer i, j, k, l, m;
    static doublereal t;
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *, 
	    integer *), daxpy_(integer *, doublereal *, doublereal *, integer 
	    *, doublereal *, integer *);
    static integer i0, j0, j1, lm, mm, ju;
    extern integer idamax_(integer *, doublereal *, integer *);
    static integer jz, kp1, nm1;

/*# 2302 "climaf.f"*/
/*# 2303 "climaf.f"*/

/*     DGBFA FACTORS A DOUBLE PRECISION BAND MATRIX BY ELIMINATION. */

/*     DGBFA IS USUALLY CALLED BY DGBCO, BUT IT CAN BE CALLED */
/*     DIRECTLY WITH A SAVING IN TIME IF  RCOND  IS NOT NEEDED. */

/*     ON ENTRY */

/*        ABD     DOUBLE PRECISION(LDA, N) */
/*                CONTAINS THE MATRIX IN BAND STORAGE.  THE COLUMNS */
/*                OF THE MATRIX ARE STORED IN THE COLUMNS OF  ABD  AND */
/*                THE DIAGONALS OF THE MATRIX ARE STORED IN ROWS */
/*                ML+1 THROUGH 2*ML+MU+1 OF  ABD . */
/*                SEE THE COMMENTS BELOW FOR DETAILS. */

/*        LDA     INTEGER */
/*                THE LEADING DIMENSION OF THE ARRAY  ABD . */
/*                LDA MUST BE .GE. 2*ML + MU + 1 . */

/*        N       INTEGER */
/*                THE ORDER OF THE ORIGINAL MATRIX. */

/*        ML      INTEGER */
/*                NUMBER OF DIAGONALS BELOW THE MAIN DIAGONAL. */
/*                0 .LE. ML .LT. N . */

/*        MU      INTEGER */
/*                NUMBER OF DIAGONALS ABOVE THE MAIN DIAGONAL. */
/*                0 .LE. MU .LT. N . */
/*                MORE EFFICIENT IF  ML .LE. MU . */
/*     ON RETURN */

/*        ABD     AN UPPER TRIANGULAR MATRIX IN BAND STORAGE AND */
/*                THE MULTIPLIERS WHICH WERE USED TO OBTAIN IT. */
/*                THE FACTORIZATION CAN BE WRITTEN  A = L*U  WHERE */
/*                L  IS A PRODUCT OF PERMUTATION AND UNIT LOWER */
/*                TRIANGULAR MATRICES AND  U  IS UPPER TRIANGULAR. */

/*        IPVT    INTEGER(N) */
/*                AN INTEGER VECTOR OF PIVOT INDICES. */

/*        INFO    INTEGER */
/*                = 0  NORMAL VALUE. */
/*                = K  IF  U(K,K) .EQ. 0.0 .  THIS IS NOT AN ERROR */
/*                     CONDITION FOR THIS SUBROUTINE, BUT IT DOES */
/*                     INDICATE THAT DGBSL WILL DIVIDE BY ZERO IF */
/*                     CALLED.  USE  RCOND  IN DGBCO FOR A RELIABLE */
/*                     INDICATION OF SINGULARITY. */

/*     BAND STORAGE */

/*           IF  A  IS A BAND MATRIX, THE FOLLOWING PROGRAM SEGMENT */
/*           WILL SET UP THE INPUT. */

/*                   ML = (BAND WIDTH BELOW THE DIAGONAL) */
/*                   MU = (BAND WIDTH ABOVE THE DIAGONAL) */
/*                   M = ML + MU + 1 */
/*                   DO 20 J = 1, N */
/*                      I1 = MAX0(1, J-MU) */
/*                      I2 = MIN0(N, J+ML) */
/*                      DO 10 I = I1, I2 */
/*                         K = I - J + M */
/*                         ABD(K,J) = A(I,J) */
/*                10    CONTINUE */
/*                20 CONTINUE */

/*           THIS USES ROWS  ML+1  THROUGH  2*ML+MU+1  OF  ABD . */
/*           IN ADDITION, THE FIRST  ML  ROWS IN  ABD  ARE USED FOR */
/*           ELEMENTS GENERATED DURING THE TRIANGULARIZATION. */
/*           THE TOTAL NUMBER OF ROWS NEEDED IN  ABD  IS  2*ML+MU+1 . */
/*           THE  ML+MU BY ML+MU  UPPER LEFT TRIANGLE AND THE */
/*           ML BY ML  LOWER RIGHT TRIANGLE ARE NOT REFERENCED. */

/*     LINPACK. THIS VERSION DATED 08/14/78 . */
/*     CLEVE MOLER, UNIVERSITY OF NEW MEXICO, ARGONNE NATIONAL LAB. */

/*     SUBROUTINES AND FUNCTIONS */

/*     BLAS DAXPY,DSCAL,IDAMAX */
/*     FORTRAN MAX0,MIN0 */

/*     INTERNAL VARIABLES */

/*# 2387 "climaf.f"*/
/*# 2388 "climaf.f"*/


/*# 2391 "climaf.f"*/
    /* Parameter adjustments */
    --ipvt;
    abd_dim1 = *lda;
    abd_offset = abd_dim1 + 1;
    abd -= abd_offset;

    /* Function Body */
    m = *ml + *mu + 1;
/*# 2392 "climaf.f"*/
    *info = 0;

/*     ZERO INITIAL FILL-IN COLUMNS */

/*# 2396 "climaf.f"*/
    j0 = *mu + 2;
/*# 2397 "climaf.f"*/
    j1 = min(*n,m) - 1;
/*# 2398 "climaf.f"*/
    if (j1 < j0) {
	goto L30;
    }
/*# 2399 "climaf.f"*/
    i_1 = j1;
    for (jz = j0; jz <= i_1; ++jz) {
/*# 2400 "climaf.f"*/
	i0 = m + 1 - jz;
/*# 2401 "climaf.f"*/
	i_2 = *ml;
	for (i = i0; i <= i_2; ++i) {
/*# 2402 "climaf.f"*/
	    abd[i + jz * abd_dim1] = 0.;
/*# 2403 "climaf.f"*/
/* L10: */
	}
/*# 2404 "climaf.f"*/
/* L20: */
    }
/*# 2405 "climaf.f"*/
L30:
/*# 2406 "climaf.f"*/
    jz = j1;
/*# 2407 "climaf.f"*/
    ju = 0;

/*     GAUSSIAN ELIMINATION WITH PARTIAL PIVOTING */

/*# 2411 "climaf.f"*/
    nm1 = *n - 1;
/*# 2412 "climaf.f"*/
    if (nm1 < 1) {
	goto L130;
    }
/*# 2413 "climaf.f"*/
    i_1 = nm1;
    for (k = 1; k <= i_1; ++k) {
/*# 2414 "climaf.f"*/
	kp1 = k + 1;

/*        ZERO NEXT FILL-IN COLUMN */

/*# 2418 "climaf.f"*/
	++jz;
/*# 2419 "climaf.f"*/
	if (jz > *n) {
	    goto L50;
	}
/*# 2420 "climaf.f"*/
	if (*ml < 1) {
	    goto L50;
	}
/*# 2421 "climaf.f"*/
	i_2 = *ml;
	for (i = 1; i <= i_2; ++i) {
/*# 2422 "climaf.f"*/
	    abd[i + jz * abd_dim1] = 0.;
/*# 2423 "climaf.f"*/
/* L40: */
	}
/*# 2424 "climaf.f"*/
L50:

/*        FIND L = PIVOT INDEX */

/*# 2428 "climaf.f"*/
/* Computing MIN */
	i_2 = *ml, i_3 = *n - k;
	lm = min(i_2,i_3);
/*# 2429 "climaf.f"*/
	i_2 = lm + 1;
	l = idamax_(&i_2, &abd[m + k * abd_dim1], &c__1) + m - 1;
/*# 2430 "climaf.f"*/
	ipvt[k] = l + k - m;

/*        ZERO PIVOT IMPLIES THIS COLUMN ALREADY TRIANGULARIZED */

/*# 2434 "climaf.f"*/
	if (abd[l + k * abd_dim1] == 0.) {
	    goto L100;
	}

/*           INTERCHANGE IF NECESSARY */

/*# 2438 "climaf.f"*/
	if (l == m) {
	    goto L60;
	}
/*# 2439 "climaf.f"*/
	t = abd[l + k * abd_dim1];
/*# 2440 "climaf.f"*/
	abd[l + k * abd_dim1] = abd[m + k * abd_dim1];
/*# 2441 "climaf.f"*/
	abd[m + k * abd_dim1] = t;
/*# 2442 "climaf.f"*/
L60:

/*           COMPUTE MULTIPLIERS */

/*# 2446 "climaf.f"*/
	t = -1. / abd[m + k * abd_dim1];
/*# 2447 "climaf.f"*/
	dscal_(&lm, &t, &abd[m + 1 + k * abd_dim1], &c__1);

/*           ROW ELIMINATION WITH COLUMN INDEXING */

/*# 2451 "climaf.f"*/
/* Computing MIN */
/* Computing MAX */
	i_3 = ju, i_4 = *mu + ipvt[k];
	i_2 = max(i_3,i_4);
	ju = min(i_2,*n);
/*# 2452 "climaf.f"*/
	mm = m;
/*# 2453 "climaf.f"*/
	if (ju < kp1) {
	    goto L90;
	}
/*# 2454 "climaf.f"*/
	i_2 = ju;
	for (j = kp1; j <= i_2; ++j) {
/*# 2455 "climaf.f"*/
	    --l;
/*# 2456 "climaf.f"*/
	    --mm;
/*# 2457 "climaf.f"*/
	    t = abd[l + j * abd_dim1];
/*# 2458 "climaf.f"*/
	    if (l == mm) {
		goto L70;
	    }
/*# 2459 "climaf.f"*/
	    abd[l + j * abd_dim1] = abd[mm + j * abd_dim1];
/*# 2460 "climaf.f"*/
	    abd[mm + j * abd_dim1] = t;
/*# 2461 "climaf.f"*/
L70:
/*# 2462 "climaf.f"*/
	    daxpy_(&lm, &t, &abd[m + 1 + k * abd_dim1], &c__1, &abd[mm + 1 + 
		    j * abd_dim1], &c__1);
/*# 2463 "climaf.f"*/
/* L80: */
	}
/*# 2464 "climaf.f"*/
L90:
/*# 2465 "climaf.f"*/
	goto L110;
/*# 2466 "climaf.f"*/
L100:
/*# 2467 "climaf.f"*/
	*info = k;
/*# 2468 "climaf.f"*/
L110:
/*# 2469 "climaf.f"*/
/* L120: */
	;
    }
/*# 2470 "climaf.f"*/
L130:
/*# 2471 "climaf.f"*/
    ipvt[*n] = *n;
/*# 2472 "climaf.f"*/
    if (abd[m + *n * abd_dim1] == 0.) {
	*info = *n;
    }
/*# 2473 "climaf.f"*/
    return 0;
/*# 2474 "climaf.f"*/
} /* dgbfa_ */


/*# 2476 "climaf.f"*/
/* Subroutine */ int dgbsl_(doublereal *abd, integer *lda, integer *n, 
	integer *ml, integer *mu, integer *ipvt, doublereal *b, integer *job)
{
    /* System generated locals */
    integer abd_dim1, abd_offset, i_1, i_2, i_3;

    /* Local variables */
    extern doublereal ddot_(integer *, doublereal *, integer *, doublereal *, 
	    integer *);
    static integer k, l, m;
    static doublereal t;
    extern /* Subroutine */ int daxpy_(integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *);
    static integer kb, la, lb, lm, nm1;

/*# 2477 "climaf.f"*/
/*# 2478 "climaf.f"*/

/*     DGBSL SOLVES THE DOUBLE PRECISION BAND SYSTEM */
/*     A * X = B  OR  TRANS(A) * X = B */
/*     USING THE FACTORS COMPUTED BY DGBCO OR DGBFA. */

/*     ON ENTRY */

/*        ABD     DOUBLE PRECISION(LDA, N) */
/*                THE OUTPUT FROM DGBCO OR DGBFA. */

/*        LDA     INTEGER */
/*                THE LEADING DIMENSION OF THE ARRAY  ABD . */

/*        N       INTEGER */
/*                THE ORDER OF THE ORIGINAL MATRIX. */

/*        ML      INTEGER */
/*                NUMBER OF DIAGONALS BELOW THE MAIN DIAGONAL. */

/*        MU      INTEGER */
/*                NUMBER OF DIAGONALS ABOVE THE MAIN DIAGONAL. */

/*        IPVT    INTEGER(N) */
/*                THE PIVOT VECTOR FROM DGBCO OR DGBFA. */

/*        B       DOUBLE PRECISION(N) */
/*                THE RIGHT HAND SIDE VECTOR. */

/*        JOB     INTEGER */
/*                = 0         TO SOLVE  A*X = B , */
/*                = NONZERO   TO SOLVE  TRANS(A)*X = B , WHERE */
/*                            TRANS(A)  IS THE TRANSPOSE. */

/*     ON RETURN */

/*        B       THE SOLUTION VECTOR  X . */

/*     ERROR CONDITION */

/*        A DIVISION BY ZERO WILL OCCUR IF THE INPUT FACTOR CONTAINS A */
/*        ZERO ON THE DIAGONAL.  TECHNICALLY THIS INDICATES SINGULARITY */

/*        BUT IT IS OFTEN CAUSED BY IMPROPER ARGUMENTS OR IMPROPER */
/*        SETTING OF LDA .  IT WILL NOT OCCUR IF THE SUBROUTINES ARE */
/*        CALLED CORRECTLY AND IF DGBCO HAS SET RCOND .GT. 0.0 */
/*        OR DGBFA HAS SET INFO .EQ. 0 . */

/*     TO COMPUTE  INVERSE(A) * C  WHERE  C  IS A MATRIX */
/*     WITH  P  COLUMNS */
/*           CALL DGBCO(ABD,LDA,N,ML,MU,IPVT,RCOND,Z) */
/*           IF (RCOND IS TOO SMALL) GO TO ... */
/*           DO 10 J = 1, P */
/*              CALL DGBSL(ABD,LDA,N,ML,MU,IPVT,C(1,J),0) */
/*        10 CONTINUE */

/*     LINPACK. THIS VERSION DATED 08/14/78 . */
/*     CLEVE MOLER, UNIVERSITY OF NEW MEXICO, ARGONNE NATIONAL LAB. */

/*     SUBROUTINES AND FUNCTIONS */

/*     BLAS DAXPY,DDOT */
/*     FORTRAN MIN0 */

/*     INTERNAL VARIABLES */

/*# 2543 "climaf.f"*/
/*# 2544 "climaf.f"*/

/*# 2546 "climaf.f"*/
    /* Parameter adjustments */
    --b;
    --ipvt;
    abd_dim1 = *lda;
    abd_offset = abd_dim1 + 1;
    abd -= abd_offset;

    /* Function Body */
    m = *mu + *ml + 1;
/*# 2547 "climaf.f"*/
    nm1 = *n - 1;
/*# 2548 "climaf.f"*/
    if (*job != 0) {
	goto L50;
    }

/*        JOB = 0 , SOLVE  A * X = B */
/*        FIRST SOLVE L*Y = B */

/*# 2553 "climaf.f"*/
    if (*ml == 0) {
	goto L30;
    }
/*# 2554 "climaf.f"*/
    if (nm1 < 1) {
	goto L30;
    }
/*# 2555 "climaf.f"*/
    i_1 = nm1;
    for (k = 1; k <= i_1; ++k) {
/*# 2556 "climaf.f"*/
/* Computing MIN */
	i_2 = *ml, i_3 = *n - k;
	lm = min(i_2,i_3);
/*# 2557 "climaf.f"*/
	l = ipvt[k];
/*# 2558 "climaf.f"*/
	t = b[l];
/*# 2559 "climaf.f"*/
	if (l == k) {
	    goto L10;
	}
/*# 2560 "climaf.f"*/
	b[l] = b[k];
/*# 2561 "climaf.f"*/
	b[k] = t;
/*# 2562 "climaf.f"*/
L10:
/*# 2563 "climaf.f"*/
	daxpy_(&lm, &t, &abd[m + 1 + k * abd_dim1], &c__1, &b[k + 1], &c__1);
/*# 2564 "climaf.f"*/
/* L20: */
    }
/*# 2565 "climaf.f"*/
L30:

/*        NOW SOLVE  U*X = Y */

/*# 2569 "climaf.f"*/
    i_1 = *n;
    for (kb = 1; kb <= i_1; ++kb) {
/*# 2570 "climaf.f"*/
	k = *n + 1 - kb;
/*# 2571 "climaf.f"*/
	b[k] /= abd[m + k * abd_dim1];
/*# 2572 "climaf.f"*/
	lm = min(k,m) - 1;
/*# 2573 "climaf.f"*/
	la = m - lm;
/*# 2574 "climaf.f"*/
	lb = k - lm;
/*# 2575 "climaf.f"*/
	t = -b[k];
/*# 2576 "climaf.f"*/
	daxpy_(&lm, &t, &abd[la + k * abd_dim1], &c__1, &b[lb], &c__1);
/*# 2577 "climaf.f"*/
/* L40: */
    }
/*# 2578 "climaf.f"*/
    goto L100;
/*# 2579 "climaf.f"*/
L50:

/*        JOB = NONZERO, SOLVE  TRANS(A) * X = B */
/*        FIRST SOLVE  TRANS(U)*Y = B */

/*# 2584 "climaf.f"*/
    i_1 = *n;
    for (k = 1; k <= i_1; ++k) {
/*# 2585 "climaf.f"*/
	lm = min(k,m) - 1;
/*# 2586 "climaf.f"*/
	la = m - lm;
/*# 2587 "climaf.f"*/
	lb = k - lm;
/*# 2588 "climaf.f"*/
	t = ddot_(&lm, &abd[la + k * abd_dim1], &c__1, &b[lb], &c__1);
/*# 2589 "climaf.f"*/
	b[k] = (b[k] - t) / abd[m + k * abd_dim1];
/*# 2590 "climaf.f"*/
/* L60: */
    }

/*        NOW SOLVE TRANS(L)*X = Y */

/*# 2594 "climaf.f"*/
    if (*ml == 0) {
	goto L90;
    }
/*# 2595 "climaf.f"*/
    if (nm1 < 1) {
	goto L90;
    }
/*# 2596 "climaf.f"*/
    i_1 = nm1;
    for (kb = 1; kb <= i_1; ++kb) {
/*# 2597 "climaf.f"*/
	k = *n - kb;
/*# 2598 "climaf.f"*/
/* Computing MIN */
	i_2 = *ml, i_3 = *n - k;
	lm = min(i_2,i_3);
/*# 2599 "climaf.f"*/
	b[k] += ddot_(&lm, &abd[m + 1 + k * abd_dim1], &c__1, &b[k + 1], &
		c__1);
/*# 2600 "climaf.f"*/
	l = ipvt[k];
/*# 2601 "climaf.f"*/
	if (l == k) {
	    goto L70;
	}
/*# 2602 "climaf.f"*/
	t = b[l];
/*# 2603 "climaf.f"*/
	b[l] = b[k];
/*# 2604 "climaf.f"*/
	b[k] = t;
/*# 2605 "climaf.f"*/
L70:
/*# 2606 "climaf.f"*/
/* L80: */
	;
    }
/*# 2607 "climaf.f"*/
L90:
/*# 2608 "climaf.f"*/
L100:
/*# 2609 "climaf.f"*/
    return 0;
/*# 2610 "climaf.f"*/
} /* dgbsl_ */


/*# 2612 "climaf.f"*/
/* Subroutine */ int daxpy_(integer *n, doublereal *da, doublereal *dx, 
	integer *incx, doublereal *dy, integer *incy)
{
    /* System generated locals */
    integer i_1;

    /* Local variables */
    static integer i, m, ix, iy, mp1;


/*     CONSTANT TIMES A VECTOR PLUS A VECTOR. */
/*     USES UNROLLED LOOPS FOR INCREMENTS EQUAL TO ONE. */
/*     JACK DONGARRA, LINPACK, 3/11/78. */
/*     MODIFIED 12/3/93, ARRAY(1) DECLARATIONS CHANGED TO ARRAY(*) */

/*# 2619 "climaf.f"*/
/*# 2620 "climaf.f"*/

/*# 2622 "climaf.f"*/
    /* Parameter adjustments */
    --dy;
    --dx;

    /* Function Body */
    if (*n <= 0) {
	return 0;
    }
/*# 2623 "climaf.f"*/
    if (*da == 0.) {
	return 0;
    }
/*# 2624 "climaf.f"*/
    if (*incx == 1 && *incy == 1) {
	goto L20;
    }

/*        CODE FOR UNEQUAL INCREMENTS OR EQUAL INCREMENTS */
/*          NOT EQUAL TO 1 */

/*# 2629 "climaf.f"*/
    ix = 1;
/*# 2630 "climaf.f"*/
    iy = 1;
/*# 2631 "climaf.f"*/
    if (*incx < 0) {
	ix = (-(*n) + 1) * *incx + 1;
    }
/*# 2632 "climaf.f"*/
    if (*incy < 0) {
	iy = (-(*n) + 1) * *incy + 1;
    }
/*# 2633 "climaf.f"*/
    i_1 = *n;
    for (i = 1; i <= i_1; ++i) {
/*# 2634 "climaf.f"*/
	dy[iy] += *da * dx[ix];
/*# 2635 "climaf.f"*/
	ix += *incx;
/*# 2636 "climaf.f"*/
	iy += *incy;
/*# 2637 "climaf.f"*/
/* L10: */
    }
/*# 2638 "climaf.f"*/
    return 0;

/*        CODE FOR BOTH INCREMENTS EQUAL TO 1 */


/*        CLEAN-UP LOOP */

/*# 2645 "climaf.f"*/
L20:
    m = *n % 4;
/*# 2646 "climaf.f"*/
    if (m == 0) {
	goto L40;
    }
/*# 2647 "climaf.f"*/
    i_1 = m;
    for (i = 1; i <= i_1; ++i) {
/*# 2648 "climaf.f"*/
	dy[i] += *da * dx[i];
/*# 2649 "climaf.f"*/
/* L30: */
    }
/*# 2650 "climaf.f"*/
    if (*n < 4) {
	return 0;
    }
/*# 2651 "climaf.f"*/
L40:
    mp1 = m + 1;
/*# 2652 "climaf.f"*/
    i_1 = *n;
    for (i = mp1; i <= i_1; i += 4) {
/*# 2653 "climaf.f"*/
	dy[i] += *da * dx[i];
/*# 2654 "climaf.f"*/
	dy[i + 1] += *da * dx[i + 1];
/*# 2655 "climaf.f"*/
	dy[i + 2] += *da * dx[i + 2];
/*# 2656 "climaf.f"*/
	dy[i + 3] += *da * dx[i + 3];
/*# 2657 "climaf.f"*/
/* L50: */
    }
/*# 2658 "climaf.f"*/
    return 0;
/*# 2659 "climaf.f"*/
} /* daxpy_ */


/*# 2661 "climaf.f"*/
integer idamax_(integer *n, doublereal *dx, integer *incx)
{
    /* System generated locals */
    integer ret_val, i_1;
    doublereal d_1;

    /* Local variables */
    static doublereal dmax_;
    static integer i, ix;


/*     FINDS THE INDEX OF ELEMENT HAVING MAX. ABSOLUTE VALUE. */
/*     JACK DONGARRA, LINPACK, 3/11/78. */
/*     MODIFIED 3/93 TO RETURN IF INCX .LE. 0. */
/*     MODIFIED 12/3/93, ARRAY(1) DECLARATIONS CHANGED TO ARRAY(*) */

/*# 2668 "climaf.f"*/
/*# 2669 "climaf.f"*/

/*# 2671 "climaf.f"*/
    /* Parameter adjustments */
    --dx;

    /* Function Body */
    ret_val = 0;
/*# 2672 "climaf.f"*/
    if (*n < 1 || *incx <= 0) {
	return ret_val;
    }
/*# 2673 "climaf.f"*/
    ret_val = 1;
/*# 2674 "climaf.f"*/
    if (*n == 1) {
	return ret_val;
    }
/*# 2675 "climaf.f"*/
    if (*incx == 1) {
	goto L20;
    }

/*        CODE FOR INCREMENT NOT EQUAL TO 1 */

/*# 2679 "climaf.f"*/
    ix = 1;
/*# 2680 "climaf.f"*/
    dmax_ = abs(dx[1]);
/*# 2681 "climaf.f"*/
    ix += *incx;
/*# 2682 "climaf.f"*/
    i_1 = *n;
    for (i = 2; i <= i_1; ++i) {
/*# 2683 "climaf.f"*/
	if ((d_1 = dx[ix], abs(d_1)) <= dmax_) {
	    goto L5;
	}
/*# 2684 "climaf.f"*/
	ret_val = i;
/*# 2685 "climaf.f"*/
	dmax_ = (d_1 = dx[ix], abs(d_1));
/*# 2686 "climaf.f"*/
L5:
	ix += *incx;
/*# 2687 "climaf.f"*/
/* L10: */
    }
/*# 2688 "climaf.f"*/
    return ret_val;

/*        CODE FOR INCREMENT EQUAL TO 1 */

/*# 2692 "climaf.f"*/
L20:
    dmax_ = abs(dx[1]);
/*# 2693 "climaf.f"*/
    i_1 = *n;
    for (i = 2; i <= i_1; ++i) {
/*# 2694 "climaf.f"*/
	if ((d_1 = dx[i], abs(d_1)) <= dmax_) {
	    goto L30;
	}
/*# 2695 "climaf.f"*/
	ret_val = i;
/*# 2696 "climaf.f"*/
	dmax_ = (d_1 = dx[i], abs(d_1));
/*# 2697 "climaf.f"*/
L30:
	;
    }
/*# 2698 "climaf.f"*/
    return ret_val;
/*# 2699 "climaf.f"*/
} /* idamax_ */


/*# 2701 "climaf.f"*/
/* Subroutine */ int dscal_(integer *n, doublereal *da, doublereal *dx, 
	integer *incx)
{
    /* System generated locals */
    integer i_1, i_2;

    /* Local variables */
    static integer i, m, nincx, mp1;


/*     SCALES A VECTOR BY A CONSTANT. */
/*     USES UNROLLED LOOPS FOR INCREMENT EQUAL TO ONE. */
/*     JACK DONGARRA, LINPACK, 3/11/78. */
/*     MODIFIED 3/93 TO RETURN IF INCX .LE. 0. */
/*     MODIFIED 12/3/93, ARRAY(1) DECLARATIONS CHANGED TO ARRAY(*) */

/*# 2709 "climaf.f"*/
/*# 2710 "climaf.f"*/

/*# 2712 "climaf.f"*/
    /* Parameter adjustments */
    --dx;

    /* Function Body */
    if (*n <= 0 || *incx <= 0) {
	return 0;
    }
/*# 2713 "climaf.f"*/
    if (*incx == 1) {
	goto L20;
    }

/*        CODE FOR INCREMENT NOT EQUAL TO 1 */

/*# 2717 "climaf.f"*/
    nincx = *n * *incx;
/*# 2718 "climaf.f"*/
    i_1 = nincx;
    i_2 = *incx;
    for (i = 1; i_2 < 0 ? i >= i_1 : i <= i_1; i += i_2) {
/*# 2719 "climaf.f"*/
	dx[i] = *da * dx[i];
/*# 2720 "climaf.f"*/
/* L10: */
    }
/*# 2721 "climaf.f"*/
    return 0;

/*        CODE FOR INCREMENT EQUAL TO 1 */


/*        CLEAN-UP LOOP */

/*# 2728 "climaf.f"*/
L20:
    m = *n % 5;
/*# 2729 "climaf.f"*/
    if (m == 0) {
	goto L40;
    }
/*# 2730 "climaf.f"*/
    i_2 = m;
    for (i = 1; i <= i_2; ++i) {
/*# 2731 "climaf.f"*/
	dx[i] = *da * dx[i];
/*# 2732 "climaf.f"*/
/* L30: */
    }
/*# 2733 "climaf.f"*/
    if (*n < 5) {
	return 0;
    }
/*# 2734 "climaf.f"*/
L40:
    mp1 = m + 1;
/*# 2735 "climaf.f"*/
    i_2 = *n;
    for (i = mp1; i <= i_2; i += 5) {
/*# 2736 "climaf.f"*/
	dx[i] = *da * dx[i];
/*# 2737 "climaf.f"*/
	dx[i + 1] = *da * dx[i + 1];
/*# 2738 "climaf.f"*/
	dx[i + 2] = *da * dx[i + 2];
/*# 2739 "climaf.f"*/
	dx[i + 3] = *da * dx[i + 3];
/*# 2740 "climaf.f"*/
	dx[i + 4] = *da * dx[i + 4];
/*# 2741 "climaf.f"*/
/* L50: */
    }
/*# 2742 "climaf.f"*/
    return 0;
/*# 2743 "climaf.f"*/
} /* dscal_ */


/*# 2745 "climaf.f"*/
doublereal ddot_(integer *n, doublereal *dx, integer *incx, doublereal *dy, 
	integer *incy)
{
    /* System generated locals */
    integer i_1;
    doublereal ret_val;

    /* Local variables */
    static integer i, m;
    static doublereal dtemp;
    static integer ix, iy, mp1;


/*     FORMS THE DOT PRODUCT OF TWO VECTORS. */
/*     USES UNROLLED LOOPS FOR INCREMENTS EQUAL TO ONE. */
/*     JACK DONGARRA, LINPACK, 3/11/78. */
/*     MODIFIED 12/3/93, ARRAY(1) DECLARATIONS CHANGED TO ARRAY(*) */

/*# 2752 "climaf.f"*/
/*# 2753 "climaf.f"*/

/*# 2755 "climaf.f"*/
    /* Parameter adjustments */
    --dy;
    --dx;

    /* Function Body */
    ret_val = 0.;
/*# 2756 "climaf.f"*/
    dtemp = 0.;
/*# 2757 "climaf.f"*/
    if (*n <= 0) {
	return ret_val;
    }
/*# 2758 "climaf.f"*/
    if (*incx == 1 && *incy == 1) {
	goto L20;
    }

/*        CODE FOR UNEQUAL INCREMENTS OR EQUAL INCREMENTS */
/*          NOT EQUAL TO 1 */

/*# 2763 "climaf.f"*/
    ix = 1;
/*# 2764 "climaf.f"*/
    iy = 1;
/*# 2765 "climaf.f"*/
    if (*incx < 0) {
	ix = (-(*n) + 1) * *incx + 1;
    }
/*# 2766 "climaf.f"*/
    if (*incy < 0) {
	iy = (-(*n) + 1) * *incy + 1;
    }
/*# 2767 "climaf.f"*/
    i_1 = *n;
    for (i = 1; i <= i_1; ++i) {
/*# 2768 "climaf.f"*/
	dtemp += dx[ix] * dy[iy];
/*# 2769 "climaf.f"*/
	ix += *incx;
/*# 2770 "climaf.f"*/
	iy += *incy;
/*# 2771 "climaf.f"*/
/* L10: */
    }
/*# 2772 "climaf.f"*/
    ret_val = dtemp;
/*# 2773 "climaf.f"*/
    return ret_val;

/*        CODE FOR BOTH INCREMENTS EQUAL TO 1 */


/*        CLEAN-UP LOOP */

/*# 2780 "climaf.f"*/
L20:
    m = *n % 5;
/*# 2781 "climaf.f"*/
    if (m == 0) {
	goto L40;
    }
/*# 2782 "climaf.f"*/
    i_1 = m;
    for (i = 1; i <= i_1; ++i) {
/*# 2783 "climaf.f"*/
	dtemp += dx[i] * dy[i];
/*# 2784 "climaf.f"*/
/* L30: */
    }
/*# 2785 "climaf.f"*/
    if (*n < 5) {
	goto L60;
    }
/*# 2786 "climaf.f"*/
L40:
    mp1 = m + 1;
/*# 2787 "climaf.f"*/
    i_1 = *n;
    for (i = mp1; i <= i_1; i += 5) {
/*# 2788 "climaf.f"*/
	dtemp = dtemp + dx[i] * dy[i] + dx[i + 1] * dy[i + 1] + dx[i + 2] * 
		dy[i + 2] + dx[i + 3] * dy[i + 3] + dx[i + 4] * dy[i + 4];
/*# 2790 "climaf.f"*/
/* L50: */
    }
/*# 2791 "climaf.f"*/
L60:
    ret_val = dtemp;
/*# 2792 "climaf.f"*/
    return ret_val;
/*# 2793 "climaf.f"*/
} /* ddot_ */

