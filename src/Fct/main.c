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
 *	file:	main.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	11.03.1994
 *
 *   purpose:	Testenvironment for the function device manager
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:36:16  schuetz
 * pvm integrated
 *
 * Revision 1.4  1995/02/06  08:11:42  schuetz
 * GUI version
 *
 * Revision 1.3  1994/07/06  07:05:45  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.2  1994/06/06  16:34:16  schuetz
 * y
 * rcsid deleted.
 *
 * Revision 1.1  1994/04/18  09:26:39  schuetz
 * Initial revision
 *
 * 
 */

#include "fct.h"
#include "rst.h"


char		*program_name;
param_t		eps;
unsigned long	ExpNbr;



void main(int argc, char ** argv)

{
	vector_tPtr	x;
	Ivector_tPtr	d;
	double		a = 0.0, b = 0.0;
	unsigned long	i, j;
	FCTdevicePtr	FCT;
	RSTdevicePtr	RST;
	bool		help;
	char		str[BUFSIZ];

	

	program_name = argv[0];



	x = veNewVector(4);
	d = veNewIVector(4);

/*	Problem 0: 20 layers and 0.709% reflection	*/
/*
        veAssignVectorComponent(1 , 1.0819822585e+03, x);
        veAssignIVectorComponent(1, 0,		      d);
        veAssignVectorComponent(2 , 6.1277255757e+02, x);
        veAssignIVectorComponent(2, 1,		      d);	
        veAssignVectorComponent(3 , 5.0830318550e+02, x);
        veAssignIVectorComponent(3, 0,		      d);	
        veAssignVectorComponent(4 , 1.1610263125e+02, x);
        veAssignIVectorComponent(4, 1,		      d);	
        veAssignVectorComponent(5 , 1.2158915158e+03, x);
        veAssignIVectorComponent(5, 0,		      d);	
        veAssignVectorComponent(6 , 7.5142677885e+02, x);
        veAssignIVectorComponent(6, 1,		      d);	
        veAssignVectorComponent(7 , 1.0909662598e+02, x);
        veAssignIVectorComponent(7, 0,		      d);	
        veAssignVectorComponent(8 , 3.2366440049e+02, x);
        veAssignIVectorComponent(8, 1,		      d);	
        veAssignVectorComponent(9 , 6.5878182893e+02, x);
        veAssignIVectorComponent(9, 0,		      d);	
        veAssignVectorComponent(10, 7.8080759237e+01, x);
        veAssignIVectorComponent(10,1,		      d);	
        veAssignVectorComponent(11, 3.6210056683e+02, x);
        veAssignIVectorComponent(11,0 ,		      d);	
        veAssignVectorComponent(12, 3.3889502150e+02, x);
        veAssignIVectorComponent(12,1 ,		      d);	
        veAssignVectorComponent(13, 1.8672281305e+02, x);
        veAssignIVectorComponent(13,0 ,		      d);	
        veAssignVectorComponent(14, 6.1813463325e+02, x);
        veAssignIVectorComponent(14,1 ,		      d);	
        veAssignVectorComponent(15, 5.2099949003e+02, x);
        veAssignIVectorComponent(15,0 ,		      d);	
        veAssignVectorComponent(16, 1.9882394067e+02, x);
        veAssignIVectorComponent(16,1 ,		      d);	
        veAssignVectorComponent(17, 3.4426063152e+02, x);
        veAssignIVectorComponent(17,0 ,		      d);	
        veAssignVectorComponent(18, 1.6389079436e+02, x);
        veAssignIVectorComponent(18,1 ,		      d);	
        veAssignVectorComponent(19, 1.9649193973e+02, x);
        veAssignIVectorComponent(19,0 ,		      d);	
        veAssignVectorComponent(20, 2.3215495089e+03, x);
        veAssignIVectorComponent(20,1 ,		      d);
*/
/*	Problem 1: 20 layers and 0.163% average reflection	*/
/*
	veAssignVectorComponent( 1,  134.636, x);
	veAssignIVectorComponent(1,  0	    , d);
	veAssignVectorComponent( 2,  0.32067, x);
	veAssignIVectorComponent(2,  1	    , d);
	veAssignVectorComponent( 3,  28.7055, x);
	veAssignIVectorComponent(3,  2	    , d);
	veAssignVectorComponent( 4,  23.477 , x);
	veAssignIVectorComponent(4,  4	    , d);
	veAssignVectorComponent( 5,  2.86917, x);
	veAssignIVectorComponent(5,  2	    , d);
	veAssignVectorComponent( 6,  30.1207, x);
	veAssignIVectorComponent(6,  1	    , d);
	veAssignVectorComponent( 7,  47.1711, x);
	veAssignIVectorComponent(7,  2	    , d);
	veAssignVectorComponent( 8,  143.914, x);
	veAssignIVectorComponent(8,  1	    , d);
	veAssignVectorComponent( 9,  59.5529, x);
	veAssignIVectorComponent(9,  0	    , d);
	veAssignVectorComponent( 10, 266.724, x);
	veAssignIVectorComponent(10, 1	    , d);
	veAssignVectorComponent( 11, 26.0391, x);
	veAssignIVectorComponent(11, 0	    , d);
	veAssignVectorComponent( 12, 262.199, x);
	veAssignIVectorComponent(12, 1	    , d);
	veAssignVectorComponent( 13, 54.6255, x);
	veAssignIVectorComponent(13, 0	    , d);
	veAssignVectorComponent( 14, 24.3362, x);
	veAssignIVectorComponent(14, 1	    , d);
	veAssignVectorComponent( 15, 0.23059, x);
	veAssignIVectorComponent(15, 2	    , d);
	veAssignVectorComponent( 16, 3.70298, x);
	veAssignIVectorComponent(16, 1	    , d);
	veAssignVectorComponent( 17, 22.8798, x);
	veAssignIVectorComponent(17, 3	    , d);
	veAssignVectorComponent( 18, 75.2460, x);
	veAssignIVectorComponent(18, 0	    , d);
	veAssignVectorComponent( 19, 25.0136, x);
	veAssignIVectorComponent(19, 1	    , d);
	veAssignVectorComponent( 20, 32.4506, x);
	veAssignIVectorComponent(20, 0	    , d);
*/
/*	Problem 3: Test design, 47 layers, physical thichnesses in nm.
		   Tvis = 98.4%, Rir = 85%, Pen = 0.94, D = 17.22	*/

/*	veAssignVectorComponent(1  , 73.7, x);
	veAssignIVectorComponent(1 , 0, d);
	veAssignVectorComponent(2  , 99.3, x);
	veAssignIVectorComponent(2 , 3, d);
	veAssignVectorComponent(3  , 158.6, x);
	veAssignIVectorComponent(3 , 0, d);
	veAssignVectorComponent(4  , 104.9, x);
	veAssignIVectorComponent(4 , 3, d);
	veAssignVectorComponent(5  , 157.1, x);
	veAssignIVectorComponent(5 , 0, d);
	veAssignVectorComponent(6  , 100.2, x);
	veAssignIVectorComponent(6 , 3, d);
	veAssignVectorComponent(7  , 159.3, x);
	veAssignIVectorComponent(7 , 0, d);
	veAssignVectorComponent(8  , 108.5, x);
	veAssignIVectorComponent(8 , 3, d);
	veAssignVectorComponent(9  , 178.3, x);
	veAssignIVectorComponent(9 , 0, d);
	veAssignVectorComponent(10 , 28.9, x);
	veAssignIVectorComponent(10, 3, d);
	veAssignVectorComponent(11 , 14.3, x);
	veAssignIVectorComponent(11, 0, d);
	veAssignVectorComponent(12 , 125.0, x);
	veAssignIVectorComponent(12, 3, d);
	veAssignVectorComponent(13 , 13.0, x);
	veAssignIVectorComponent(13, 0, d);
	veAssignVectorComponent(14 , 28.8, x);
	veAssignIVectorComponent(14, 3, d);
	veAssignVectorComponent(15 , 182.3, x);
	veAssignIVectorComponent(15, 0, d);
	veAssignVectorComponent(16 , 117.0, x);
	veAssignIVectorComponent(16, 3, d);
	veAssignVectorComponent(17 , 190.8, x);
	veAssignIVectorComponent(17, 0, d);
	veAssignVectorComponent(18 , 29.4, x);
	veAssignIVectorComponent(18, 3, d);
	veAssignVectorComponent(19 , 18.7, x);
	veAssignIVectorComponent(19, 0, d);
	veAssignVectorComponent(20 , 109.4, x);
	veAssignIVectorComponent(20, 3, d);
	veAssignVectorComponent(21 , 17.6, x);
	veAssignIVectorComponent(21, 0, d);
	veAssignVectorComponent(22 , 26.8, x);
	veAssignIVectorComponent(22, 3, d);
	veAssignVectorComponent(23 , 189.5, x);
	veAssignIVectorComponent(23, 0, d);
	veAssignVectorComponent(24 , 16.3, x);
	veAssignIVectorComponent(24, 3, d);
	veAssignVectorComponent(25 , 15.2, x);
	veAssignIVectorComponent(25, 0, d);
	veAssignVectorComponent(26 , 132.5, x);
	veAssignIVectorComponent(26, 3, d);
	veAssignVectorComponent(27 , 31.0, x);
	veAssignIVectorComponent(27, 0, d);
	veAssignVectorComponent(28 , 23.3, x);
	veAssignIVectorComponent(28, 3, d);
	veAssignVectorComponent(29 , 224.4, x);
	veAssignIVectorComponent(29, 0, d);
	veAssignVectorComponent(30 , 26.1, x);
	veAssignIVectorComponent(30, 3, d);
	veAssignVectorComponent(31 , 22.0, x);
	veAssignIVectorComponent(31, 0, d);
	veAssignVectorComponent(32 , 180.1, x);
	veAssignIVectorComponent(32, 3, d);
	veAssignVectorComponent(33 , 27.2, x);
	veAssignIVectorComponent(33, 0, d);
	veAssignVectorComponent(34 , 22.8, x);
	veAssignIVectorComponent(34, 3, d);
	veAssignVectorComponent(35 , 232.2, x);
	veAssignIVectorComponent(35, 0, d);
	veAssignVectorComponent(36 , 21.7, x);
	veAssignIVectorComponent(36, 3, d);
	veAssignVectorComponent(37 , 31.8, x);
	veAssignIVectorComponent(37, 0, d);
	veAssignVectorComponent(38 , 143.6, x);
	veAssignIVectorComponent(38, 3, d);
	veAssignVectorComponent(39 , 28.4, x);
	veAssignIVectorComponent(39, 0, d);
	veAssignVectorComponent(40 , 17.6, x);
	veAssignIVectorComponent(40, 3, d);
	veAssignVectorComponent(41 , 211.3, x);
	veAssignIVectorComponent(41, 0, d);
	veAssignVectorComponent(42 , 18.0, x);
	veAssignIVectorComponent(42, 3, d);
	veAssignVectorComponent(43 , 31.2, x);
	veAssignIVectorComponent(43, 0, d);
	veAssignVectorComponent(44 , 141.6, x);
	veAssignIVectorComponent(44, 3, d);
	veAssignVectorComponent(45 , 31.5, x);
	veAssignIVectorComponent(45, 0, d);
	veAssignVectorComponent(46 , 17.1, x);
	veAssignIVectorComponent(46, 3, d);
	veAssignVectorComponent(47 , 50.0, x);
	veAssignIVectorComponent(47, 0, d);
*/

/*

	FCT = newFCT("genRosenbrock", NULL);
	RST = newRST("standard", "lower = -5, upper = 5");
	FCT = newFCT("ellepsoid", NULL);
	FCT = newFCT("fletcherPowell","control = mixed");	
*/

	RST = newRST("reflection" , NULL);
	FCT = newFCT("reflection3", NULL);

/*
	RST = newRST("null" , NULL);
	FCT = newFCT("fletcherPowell", "control=fix");

	for (a = -10.0; a <= 10.0; a+= 0.1)
		printf("%g\n",a);
		
	for (b = -10.0; b <= 10.0; b+= 0.1)
		printf("%g\n",b);

	for (a = -10.0; a <= 10.0; a+= 0.1) {
		for (b = -10.0; b <= 10.0; b+= 0.1) {
			veAssignVectorComponent(1, a, x);
			veAssignVectorComponent(2, b, x);
			printf("%g\n",EvalFCT(x,d));
		}
	}
*/	
	veAssignIVectorComponent(1, 0, d);
        veAssignVectorComponent(2, 10.0, x);
        veAssignIVectorComponent(2, 1, d);
        veAssignVectorComponent(3, 10.0, x);
        veAssignIVectorComponent(3, 2, d);
/*        veAssignVectorComponent(4, 100.0, x);	*/
        veAssignIVectorComponent(4, 3, d);
/*        veAssignIVectorComponent(5, 4, d);	*/

/*	veAssignIVectorComponent(1, 0, d);
        veAssignIVectorComponent(2, 1, d);
*/
	for (a = 0.0; a <= 1.0; a+= 0.01)
		printf("%g\n", a);
	for (b = 0.0; b <= 1.0; b+= 0.01)
		printf("%g\n", b);
	for (a = 0.0; a <= 1.0; a+= 0.01) {
		for (b = 0.0; b <= 1.0; b+= 0.01) {
			veAssignVectorComponent(1, a*1000.0/1.46, x);
			veAssignVectorComponent(4, b*1000.0/2.35, x);
			printf("%g ",EvalFCT(x,d));
		}
		printf("\n");
	}
/*
	for(i = 26; i <= 1000;i++) {
		sprintf(str,"waveSteps = %ld", i);
		FCT = newFCT("reflection1" , str);
		printf("\n%s",str);
		printf("Merit = %g\n", EvalFCT(x,d));
	}
		
*/
/*	printf("\nF(x) = %g\n", EvalFCT(x, d));*/
/*
	for(i = -10; i <= 10; i++) {
		printf("\n");
		veAssignVectorComponent(1, (double) i, x);
		for(j = -10; j <= 10; j++) {
		veAssignVectorComponent(2, (double) j, x);
		help = (bool) EvalRST(x,(Ivector_tPtr) NULL);
		if(FALSE == help)
			printf("\n%g %g %g",veGetVectorComponent(1,x),
					    veGetVectorComponent(2,x),
					    EvalFCT(x, (Ivector_tPtr) NULL));*/
		/* EvalRST returning 'FALSE' if no restriction is violated */
/*		else
			fprintf(stderr,"\n%g %g invalid",
				veGetVectorComponent(1,x),
				veGetVectorComponent(2,x));
		}
	}

	printf("\n");
*/

	deleteFCT(&eps);
	deleteRST();

	x = veDeleteVector(x);
	d = veDeleteIVector(d);

}
