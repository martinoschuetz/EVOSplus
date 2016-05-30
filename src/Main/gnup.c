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
 *	file:	gnup.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	14.05.1994
 *
 *   purpose:	Pipe communication with the gnuplot program.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:57:20  schuetz
 * pvm integrated
 *
 * Revision 1.3  1995/02/06  08:10:23  schuetz
 * GUI version
 *
 * Revision 1.2  1994/06/06  16:47:39  schuetz
 * rcsid deleted.
 *
 * Revision 1.2  1994/06/06  16:47:39  schuetz
 * rcsid deleted.
 *
 * Revision 1.1  1994/06/06  14:49:36  schuetz
 * Initial revision
 *
 * 
 */

#include "gnup.h"


#define	G_GNUPLOT	"gnuplot"
#define G_DATSTYL	"set data style lines\n"
#define G_SAMPLES	"set samples 10000\n"
#define G_LOGSTYL	"set logscale y\n"
#define G_PAUSE		"pause 10\n"
#define G_XTITLE	"set xlabel \"Generation\"\n"
#define G_YTITLE	"set ylabel \"Objective Function Value, %s\"\n"


/*
 *	Initialize the pipe.
 */


FILE	*gnInitGnuPipe(param_tPtr eps)

{	if(NULL == eps)
		panic(A_FATAL, "gnInitGnuPipe",
		      "Uninitialized parameter struct : %s : %d",
		      __FILE__, __LINE__);

	if ((eps->Gpp = popen(G_GNUPLOT, "w")) == NULL)
		panic(A_FATAL, "gnInitGnuPipe",
		      "Couldn't open pipe to %s : %s : %d",
		      G_GNUPLOT, __FILE__, __LINE__);

	if(eps->ScaFlg != 0)
		fprintf(eps->Gpp, G_LOGSTYL);
	fprintf(eps->Gpp, G_DATSTYL);
	fprintf(eps->Gpp, G_SAMPLES);
	fprintf(eps->Gpp, G_XTITLE);
	fprintf(eps->Gpp, G_YTITLE, eps->FctNme);
/*	fprintf(eps->Gpp, "plot \"%s\"\n",eps->OutFil);	*/

	fprintf(eps->Gpp, 
		"plot\
\"%s\" using 1:8  title \"AllBest\" w l 1,\
\"%s\" using 1:9  title \"Best\"    w l 2,\
\"%s\" using 1:10 title \"Avg\"     w l 3,\
\"%s\" using 1:11 title \"Wst\"     w l 4\n",
		eps->OutFil, eps->OutFil, eps->OutFil, eps->OutFil);

/*	fprintf(eps->Gpp, 
		"plot\
\"%s\" using \"%%f%%*f%%f\"             title \"AllBest\" w l 1,\
\"%s\" using \"%%f%%*f%%*f%%f\"         title \"Best\"    w l 2,\
\"%s\" using \"%%f%%*f%%*f%%*f%%f\"     title \"Avg\"     w l 3,\
\"%s\" using \"%%f%%*f%%*f%%*f%%*f%%f\" title \"Wst\"     w l 4\n",
		eps->OutFil, eps->OutFil, eps->OutFil, eps->OutFil);
*/

	fflush(eps->Gpp);

	return(eps->Gpp);

} /*** end gnInitGnuPipe ***/



/*
 *	Actualize the data plot.
 */

void gnPlotGnuPipe(param_tPtr eps)

{
	if(NULL == eps)
		panic(A_FATAL, "gnPlotGnuPipe",
		      "Uninitialized parameter struct : %s : %d",
		      __FILE__, __LINE__);

	if(NULL == eps->Gpp)
               panic(A_FATAL, "gnPlotGnuPipe",
		     "Uninitialized file pointer : %s : %d",
		     __FILE__, __LINE__);

	fprintf(eps->Gpp, "rep\n");

	fflush(eps->Gpp);

} /*** end plotGpp ***/



/*
 *	Quit the plot program.
 */

void gnQuitGnuPipe(param_tPtr eps)

{
	if(NULL == eps)
		panic(A_FATAL, "gnQuitGnuPipe",
		      "Uninitialized parameter struct : %s : %d",
		      __FILE__, __LINE__);

	if(NULL == eps->Gpp)
               panic(A_FATAL, "gnQuitGnuPipe",
		     "Uninitialized file pointer : %s : %d",
		     __FILE__, __LINE__);
									   
	fprintf(eps->Gpp, G_PAUSE); 
	fflush(eps->Gpp);	
	pclose(eps->Gpp);

} /*** end gnQuitGnuPipe ***/


/*** end of file ***/
