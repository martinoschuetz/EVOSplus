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
 *	file:	fio.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	20.03.1994
 *
 *   purpose:	File I/O operations and filename generation.
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:57:20  schuetz
 * pvm integrated
 *
 * Revision 1.4  1995/02/06  08:10:23  schuetz
 * GUI version
 *
 * Revision 1.3  1994/07/06  07:03:35  schuetz
 * Version fuer die Testlauefe.
 *
 * Revision 1.2  1994/06/06  16:47:39  schuetz
 * rcsid deleted.
 *
 * Revision 1.1  1994/06/06  14:49:36  schuetz
 * Initial revision
 *
 * 
 */

#include "fio.h"



/*
 *	Read an initial point from the data file InzFil.
 *	The file structure is expected to be simply a list of the
 *	object variables with newlines in between, i.e.:
 *
 *				x1
 *				x2
 *				.
 *				.
 *				.
 *				xn
 */

void fioReadInzPnt(param_tPtr eps, individual_tPtr ind)

{
	FILE	       *fp;
	double		HlpDouble;
	long		HlpLong;
	unsigned long	i;
	

	if ((fp = fopen(eps->InzFil, "r")) == NULL)
		panic(A_FATAL, "fioReadInzPnt",
		      "Couldn't open initialization file (%s)\n",
		      eps->InzFil);

	for (i = 1; i <= inGetXLength(ind); i++) {
		if (fscanf(fp, "%lf\n", &HlpDouble) != 1)
			panic(A_FATAL, "fioReadInzPnt",
			      "Wrong format of initialization file (%s)\n",
			      eps->InzFil);
		inAssignXComponent(i,HlpDouble,ind);
	}

	for (i = 1; i <= inGetDLength(ind); i++) {
		if (fscanf(fp, "%ld\n", &HlpLong) != 1)
			panic(A_FATAL, "fioReadInzPnt",
			      "Wrong format of initialization file (%s)\n",
			      eps->InzFil);
		inAssignDComponent(i, HlpLong,ind);
	}

	fclose(fp);

} /*** end fioReadInzPnt ***/


/*
 *	Create a default directory name if the user does not provide one.
 */

char *fioCrtDirName(param_tPtr eps)

{
  /*	char Fil[BUFSIZ],*/
	char *Fil,
		 Str[BUFSIZ];
	/*	char *hlp = NULL;*/

	/*	getcwd(Fil, BUFSIZ);*/
	Fil = getcwd(NULL, BUFSIZ);
	sprintf(Str, "%s%s.", PTHSEP, eps->FctNme);
	strcat(Fil, Str);

	if(strcmp(activeRST(),"null") != 0) {
		sprintf(Str, "%s.", eps->RstNme);
		strcat(Fil, Str);
	}

	sprintf(Str, "%ld.%ld", eps->XDim, eps->DDim);
	strcat(Fil, Str);

	if(eps->SigDim > 0) {
		sprintf(Str, ".%ld", eps->SigDim);
		strcat(Fil, Str);
	}
	if(eps->AlpDim > 0) {
		sprintf(Str, ".%ld", eps->AlpDim);
		strcat(Fil, Str);
	}
	if(eps->PDim > 0) {
		sprintf(Str, ".%ld", eps->PDim);
		strcat(Fil, Str);
	}

	switch (eps->SltScm) {
		case STD_SEL:
			sprintf(Str, ":%ld,%ld.", eps->MueVal, eps->LdaVal);
			strcat(Fil, Str);
			break;
		case PLS_SEL:
			sprintf(Str, ":%ld+%ld.", eps->MueVal, eps->LdaVal);
			strcat(Fil, Str);
			break;
		default:
			break;
	}

	sprintf(Str,"%s.%s.%s.%c.%c.%s.%.3f.%.3f.%.3f.%.3f",
		eps->RecScm,eps->AdapScm,eps->MttScm,
		eps->SigComp,eps->PComp,eps->TransScm,
		eps->TauLcl, eps->TauGlb, eps->GamLcl, eps->GamGlb);
	strcat(Fil, Str);

	/*	hlp = strdup(Fil);
		return(hlp); */
	return(Fil);

}/*** end fioCrtDirName ***/


/*
 *	Make recursively a directory, if it does not yet exist;
 *	return(-1) if there's any error.
 */

int fioCrtDir(char *dir /* directory name */ )

{
	struct	stat	 sbuf;
	
/*	char		*p;	*/
	char		 Msg[BUFSIZ];

/*	int		 rc;	*/

	/* 
	 *	If the directory does already exist, it is
	 *	removed completely in a first step !
	 *	!! The rekursive version is to dangerous when
	 *	used with absolute pathes.
	 *	So a nonrecursive simple version is taken.
	 */

	if (stat(dir, &sbuf) == 0) {
		sprintf(Msg, "rm -r %s", dir);
		system(Msg);
	}

	if (mkdir(dir,0775) < 0) {
		sprintf(Msg, "Cannot mkdir(%s)", dir);
		perror(Msg);
		return(-1);
	}

/*	while (stat(dir,&sbuf) < 0) {
		switch(errno) {
			case ENOENT:	 dir does not exist 
			case ENOTDIR:	 uncomplete path to dir 
				if ((p = strrchr(dir,'/')) != NULL) {
					*p = '\0';
					rc = fioCrtDir(dir);
					*p = '/';
					if (rc != 0) {
						return(-1);
					}
				}

				if (mkdir(dir,0775) < 0) {
					sprintf(Msg, "Cannot mkdir(%s)", dir);
					perror(Msg);
					return(-1);
				}
				break;

			default:	 should not happen 
				sprintf(Msg, "Cannot stat(%s)", dir);
				perror(Msg);
				return(-1);
		}
	}

	if (!S_ISDIR(sbuf.st_mode)) {
		sprintf(Msg, "%s: not a directory", dir);
		perror(Msg);
		return(-1);
	}
*/
	errno = 0;

	return(0);

} /* end fioCrtDir */



/*
 *	Add a time information to the log file.
 */

void fioTimeOut(param_tPtr	eps )

{
  FILE   *fp;
  char   Msg[BUFSIZ];
	
  if ((fp = fopen(eps->LogFil, "a")) != NULL) {
	time(&(eps->clock));
	strcpy(Msg, ctime(&(eps->clock)));
	fprintf(fp, "Time: %s\n", Msg);
	if(eps->startTime == 0)
	  eps->startTime = eps->clock;
	else
	  fprintf(fp, "Time used: %g seconds\n",
			  difftime(eps->clock,eps->startTime));
	
	fclose(fp);
  }
  
} /*** end fioTimeOut ***/
