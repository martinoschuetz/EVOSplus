/****************************************************************/
/*                                                           	*/
/*  Copyright (c) 1992                                       	*/
/*  Thomas Baeck                                             	*/
/*  Computer Science Department, LSXI       			*/
/*  University of Dortmund                                   	*/
/*  Baroper Str. 301                                         	*/
/*  P.O. Box 50 05 00						*/
/*  D-4600 Dortmund 50						*/
/*  Germany							*/
/*								*/
/*  e-mail: baeck@home.informatik.uni-dortmund.de		*/
/*  	    baeck@ls11.informatik.uni-dortmund.de		*/
/*								*/
/*  Permission is hereby granted to copy all or any part of  	*/
/*  this program for free distribution.   The author's name  	*/
/*  and this copyright notice must be included in any copy.  	*/
/*                                                           	*/
/****************************************************************/

/*
 *	file:	pars.c
 *
 *    author: 	Thomas Baeck
 *
 *   created:	July 24th, 1992
 *
 *   purpose:	Simple parsing procedure for the format argument.
 *
 *  modified:	Schuetz, 23.03.1994
 *
 *	The modifications were made for getting a more flexible parser.
 *	Now the parser allocates the bitstrings used by the datacollection
 *	(see data.c) in dependence of the algorithm scheme.
 *	The new version in capable to interpret the (see below) same
 *	context free language, but the handling of the bit strings changed.
 *	If the dimension of a gen ist zero in the programm global
 *	parameter structure, the parser don't modify the corresponding
 *	bit vector, which is initially NULL (for all bit vectors).
 *	An initially dimension of zero indicates, that the corresponding
 *	gen will not be used in the actual algorithm scheme and therefor
 *	the datacollection ignores the gen.
 *	If the selector for a certain gen is '*', the parser allocates
 *	the corresponding bit vector with dimension zero.
 *	A vector of dimension zero causes the datacollection to record
 *	the hole corresponding gen.
 *	If the selector is specified, like 'x:1,5,10-25', the needed
 *	bit vector is allocated in dependence of the algorithm scheme.
 *	If the length mutation scheme of the gen in mind is not activated
 *	(fixed dimension), the vector is allocated with fixed dimension.
 *	In the example the allocation length would be 25, if 25 is the
 *	dimension of the x gen in the global parameter structure.
 *	In this case the datacollection can record the columns, which
 *	are less or equal the fixed dimension.
 *	If the algorithm scheme is set to variable dimension, the
 *	vector dimension is set to the maximum column number,
 *	25 in the case of our example.
 *	In this last case, the recordingmechanism can only collect those
 *	genpositions, which can be found in the bit vector.
 *	
 *
 *	$Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:57:20  schuetz
 * pvm integrated
 *
 *
 */

#include "pars.h"


/*
 *	Grammar for the format string argument:
 *	
 *	FORMAT	::=	empty 				| 
 *			x:SELECTOR FORMAT		|
 *			d:SELECTOR FORMAT		|
 *			s:SELECTOR FORMAT		|
 *			a:SELECTOR FORMAT		|
 *			p:SELECTOR FORMAT		|
 *			i:SELECTOR FORMAT	
 *	SELECTOR::=	*				|
 *			NUMBER COL
 *	COL	::=	empty				|
 *			D				|
 *			-NUMBER D
 *	D	::=	,NUMBER COL
 *	NUMBER	::=	<integer>
 *
 *	E.g.: "x:1,2,4-10s:1,2a:*i:" means: Process object variables
 *	number 1, 2, 4 to 10; standard deviations 1, 2, and all
 *	correlations of all individuals.
 */


void parsFormatString(param_tPtr eps)

{
	char		*Str;


	if(strlen(eps->FmtStr) == 0) 
		return;
	Str = strdup(eps->FmtStr);
	_psFormat(eps, Str);
	free(Str);

	return;

} /*** end parsFmtStr ***/


/*
 *	See the rules above. This is essentially a recursive
 *	descent parser.
 */

void _psFormat(param_tPtr eps	/* parameter structure */,
	       char *Str	/* format string */)

{
	int		Idx = X;
	char		Chr;

	if (_psChrTok(&Chr, Str)) {
		switch (Chr) {
			case 'x':	/* real object variable format */
				Idx = X;
				_psMatch(Str, 'x');
				break;
			case 'd':	/*  integer object variable format */
				Idx = D;
				_psMatch(Str, 'd');
				break;				
			case 's':	/* standard deviations */
				Idx = SIGMA;
				_psMatch(Str, 's');
				break;
			case 'a':	/* correlations */
				Idx = ALPHA;
				_psMatch(Str, 'a');
				break;
			case 'p':	/* mutation rates format */
				Idx = P;
				_psMatch(Str, 'p');
				break;				
			case 'i':	/* individuals */
				Idx = INDIVIDUAL;
				_psMatch(Str, 'i');
				break;
			case '\0':	/* empty token */
				return;
			default:	/* error */
				panic(A_FATAL,"_psFormat",
				      "Wrong token (%c) : %s : %d",
				      Chr, __FILE__, __LINE__);
		}
		_psMatch(Str, ':');
		_psSelector(eps, Str, Idx);
		_psFormat(eps, Str);
	}
	else
		panic(A_FATAL,"_psFormat",
		      "Wrong token (%c) : %s : %d", Chr, __FILE__, __LINE__);

} /*** end psFormat ***/


void _psSelector(param_tPtr	eps  /* parameter structure */,
		 char		*Str /* format string */,
		 int		Idx  /* index of format array */)

{
	unsigned long	Col, i;
	char		Chr;

	if (_psChrTok(&Chr, Str)) {
		switch (Chr) {
			case '*':	/* all elements of this component */
			  switch (Idx) {
			    case X: /* real object variable format */
				if(eps->XDim == 0)
					break;
				eps->ObjBit = veNewIVector(0);
				/* If all genpositions shall be collected,
				   there is no need of the bitvector. */
				eps->ObjFlg = TRUE;
				break;
			    case D:/*  integer object variable format */
				if(eps->DDim == 0) /* D-gen no part of the algo */
					break;
				eps->DisBit = veNewIVector(0);
				eps->DisFlg = TRUE;
				break;				
			    case SIGMA: /* standard deviations */
				if(eps->SigDim == 0)
					break;
				eps->SigBit = veNewIVector(0);
				eps->SigFlg = TRUE;
				break;
			    case ALPHA: /* correlations */
				if(eps->AlpDim == 0)
					break;
				eps->AlpBit = veNewIVector(0);
				eps->AlpFlg = TRUE;
				break;
			    case P:	/* mutation rates format */
				if(eps->PDim == 0)
					break;
				eps->RatBit = veNewIVector(0);
				eps->RatFlg = TRUE;
				break;				
			    case INDIVIDUAL: /* individuals */
				eps->IndBit = veNewIVector(eps->MueVal);
				for(i = 1; i <= eps->MueVal; i++)
				    veAssignIVectorComponent(i,1,eps->IndBit);
				break;
			    default: /* error */
				panic(A_FATAL,"_psSelector",
				      "Wrong  Index (%d) : %s : %d",
				      Idx, __FILE__, __LINE__);
			  }
			  _psMatch(Str, '*');
			  break;
			default:
				panic(A_FATAL,"_psSelector",
				      "Wrong token (%c) : %s : %d",
				      Chr, __FILE__, __LINE__);
		}
		return;
	}

	if (_psIntTok(&Col, Str)) {
		_psCol(eps, Str, Idx, Col);
		return;
	}

	panic(A_FATAL,"_psSelector",
	      "Wrong token (%c) : %s : %d", Chr, __FILE__, __LINE__);

} /*** end _psSelector ***/



void _psCol(param_tPtr		eps  /* parameter structure */,
	    char		*Str /* format string */,
	    int			Idx  /* format array index */,
	    unsigned long	Col  /* start column for output */)

{
	unsigned long	Col2;
	char		Chr;
	
	if (_psChrTok(&Chr, Str)) {
		switch(Chr) {
			case ',' :	/* set particular bit */
			case '\0':
			case 'x' :
			case 'd' :			
			case 's' :
			case 'a' :
			case 'p' :			
			case 'i' :
				_psSetBit(eps, Idx, Col, Col);
			  	if (Chr == ',')
					_psD(eps, Str, Idx);
			  	return;
			case '-':	/* a subrange */
			  	_psMatch(Str, '-');
			  	_psIntTok(&Col2, Str);
				_psSetBit(eps, Idx, Col, Col2);
			  	_psD(eps, Str, Idx);
			  	break;
			default:
				panic(A_FATAL,"_psCol",
				      "Wrong token (%c) : %s : %d", 
				      Chr, __FILE__, __LINE__);
				break;
		}
	}
	else
		panic(A_FATAL,"_psCol", "Wrong token (%c) : %s : %d", 
		      Chr, __FILE__, __LINE__);

} /*** end _psCol ***/


void _psD(param_tPtr	eps  /* parameter structure */,
	  char		*Str /* format string */,
	  int		Idx  /* format array index */)

{
	unsigned long	Col;
	char		Chr;

	if (_psChrTok(&Chr, Str)) {
		switch (Chr) {
			case ',':
				_psMatch(Str, ',');
				if (_psIntTok(&Col, Str)) {
					_psSetBit(eps, Idx, Col, Col);
					_psCol(eps, Str, Idx, Col);
				}
				else
					panic(A_FATAL,"_psD",
					      "Wrong token (%d) : %s : %d", 
					      Col, __FILE__, __LINE__);
				break;
			case '\0':
				return;
		}
	}
	else
		panic(A_FATAL,"_psD", "Wrong token (%c) : %s : %d", 
		      Chr, __FILE__, __LINE__);

} /*** end _psD ***/


void _psMatch(char *Str, char Chr)

{
	unsigned long	i = 0,
			j = 1;

	if (Str[0] != Chr)
		panic(A_FATAL,"_psMatch",
		      "Wrong match (%c,%c) : %s : %d",
			Chr, Str[0], __FILE__, __LINE__);

	while ((Str[i++] = Str[j++]) != '\0');

} /*** end _psMatch ***/


unsigned long _psChrTok(char *Chr /* character pointer */,
			char *Str /* format string */)

{
	*Chr = Str[0];
	switch (*Chr) {
		case '\0':
		case ',' :
		case ':' :
		case '-' :	
		case '*' :
		case 'x' :
		case 'd' :		
		case 's' :
		case 'a' :
		case 'p' :		
		case 'i' :
			return 1;
		default  :
			return 0;
	}

} /*** end _psChrTok ***/


unsigned long _psIntTok(unsigned long  *Int /* integer pointer */,
			char *Str /* format string */)

{
	unsigned long	Nbr,
			i,
			k = 0;

	if (sscanf(Str, "%ld", &Nbr) != 1) 
		return 0;
	*Int = Nbr;
	for (i = 0; isdigit(Str[i]); i++);
	while ((Str[k++] = Str[i++]) != '\0');
	return 1;

} /*** end _psIntTok ***/


	/*
	 *	Set output bits for a certain subrange of the arrays.
	 */

void _psSetBit(param_tPtr	eps  /* parameter structure */ ,
	       int		Idx  /* array indicator */,
	       unsigned long	Low  /* start position */,
	       unsigned long	Hgh  /* end position */)

{
	unsigned long	i;

	switch (Idx) {
		case X:		/* real valued object variable bits */
			if(eps->XDim == 0)
				break;
			if((NULL == eps->ObjBit) && (eps->ObjFlg == TRUE))
				panic(A_FATAL,"_psSetBit",
				      "uninitialized 'ObjBit' vector : %s : %d",
				      __FILE__, __LINE__);
			if (Low < 1 || Low > Hgh)
				panic(A_FATAL,"_psSetBit",
				      "dimension index error (%d,%d) : %s : %d",
				      Low, Hgh, __FILE__, __LINE__);
			if(eps->AdapScm[0] == NO_ADAP) {
			  if(!eps->ObjFlg) {
				eps->ObjBit = veNewIVector(eps->XDim);
				eps->ObjFlg = TRUE;
			  }
			}
			else {
			  if(eps->ObjFlg) 
				eps->ObjBit = veRenewIVector(Hgh, eps->ObjBit);
			  else {
				eps->ObjBit = veNewIVector(Hgh);
				eps->ObjFlg = TRUE;
			  }
			}
			for (i = Low; i <= Hgh; i++)
				veAssignIVectorComponent(i, 1, eps->ObjBit);
			break;
		case D:		/* integer valued object variable bits */
			if(eps->DDim == 0)
				break;
			if((NULL == eps->DisBit) && (eps->DisFlg == TRUE))
				panic(A_FATAL,"_psSetBit",
				      "uninitialized 'DisBit' vector : %s : %d",
				      __FILE__, __LINE__);
			if (Low < 1 || Low > Hgh)
				panic(A_FATAL,"_psSetBit",
				      "dimension index error (%d,%d) : %s : %d",
				      Low, Hgh, __FILE__, __LINE__);
			if(eps->AdapScm[1] == NO_ADAP) {
			  if(!eps->DisFlg) {
				eps->DisBit = veNewIVector(eps->DDim);
				eps->DisFlg = TRUE;
			  }
			}
			else {
			  if(eps->DisFlg) 
				eps->DisBit = veRenewIVector(Hgh, eps->DisBit);
			  else {
				eps->DisBit = veNewIVector(Hgh);
				eps->DisFlg = TRUE;
			  }
			}
			for (i = Low; i <= Hgh; i++)
				veAssignIVectorComponent(i, 1, eps->DisBit);
			break;
		case SIGMA:		/* standard deviation bits */
			if(eps->SigDim == 0)
				break;
			if((NULL == eps->SigBit) && (eps->SigFlg == TRUE))
				panic(A_FATAL,"_psSetBit",
				      "uninitialized 'SigBit' vector : %s : %d",
				      __FILE__, __LINE__);
			if (Low < 1 || Low > Hgh)
				panic(A_FATAL,"_psSetBit",
				      "dimension index error (%d,%d) : %s : %d",
				      Low, Hgh, __FILE__, __LINE__);
			if(eps->AdapScm[2] == NO_ADAP) {
			  if(!eps->SigFlg) {
				eps->SigBit = veNewIVector(eps->SigDim);
				eps->SigFlg = TRUE;
			  }
			}
			else {
			  if(eps->SigFlg) 
				eps->SigBit = veRenewIVector(Hgh, eps->SigBit);
			  else {
				eps->SigBit = veNewIVector(Hgh);
				eps->SigFlg = TRUE;
			  }
			}
			for (i = Low; i <= Hgh; i++)
				veAssignIVectorComponent(i, 1, eps->SigBit);
			break;
		case ALPHA:		/* correlation bits */
			if(eps->AlpDim == 0)
				break;
			if((NULL == eps->AlpBit) && (eps->AlpFlg == TRUE))
				panic(A_FATAL,"_psSetBit",
				      "uninitialized 'AlpBit' vector : %s : %d",
				      __FILE__, __LINE__);
			if (Low < 1 || Low > Hgh)
				panic(A_FATAL,"_psSetBit",
				      "dimension index error (%d,%d) : %s : %d",
				      Low, Hgh, __FILE__, __LINE__);
			if(eps->AdapScm[3] == NO_ADAP) {
			  if(!eps->AlpFlg) {
				eps->AlpBit = veNewIVector(eps->AlpDim);
				eps->AlpFlg = TRUE;
			  }
			}
			else {
			  if(eps->AlpFlg) 
				eps->AlpBit = veRenewIVector(Hgh, eps->AlpBit);
			  else {
				eps->AlpBit = veNewIVector(Hgh);
				eps->AlpFlg = TRUE;
			  }
			}
			for (i = Low; i <= Hgh; i++)
				veAssignIVectorComponent(i, 1, eps->AlpBit);
			break;
		case P:		/* mutation rate bits */
			if(eps->PDim == 0)
				break;
			if((NULL == eps->RatBit) && (eps->RatFlg == TRUE))
				panic(A_FATAL,"_psSetBit",
				      "uninitialized 'RatBit' vector : %s : %d",
				      __FILE__, __LINE__);
			if (Low < 1 || Low > Hgh)
				panic(A_FATAL,"_psSetBit",
				      "dimension index error (%d,%d) : %s : %d",
				      Low, Hgh, __FILE__, __LINE__);
			if(eps->AdapScm[4] == NO_ADAP) {
			  if(!eps->RatFlg) {
				eps->RatBit = veNewIVector(eps->PDim);
				eps->RatFlg = TRUE;
			  }
			}
			else {
			  if(eps->RatFlg) 
				eps->RatBit = veRenewIVector(Hgh, eps->RatBit);
			  else {
				eps->RatBit = veNewIVector(Hgh);
				eps->RatFlg = TRUE;
			  }
			}
			for (i = Low; i <= Hgh; i++)
				veAssignIVectorComponent(i, 1, eps->RatBit);
			break;
		case INDIVIDUAL:	/* individual indicators */
			if (Low < 1 || Low > Hgh)
				panic(A_FATAL,"_psSetBit",
				      "dimension index error (%d,%d) : %s : %d",
				      Low, Hgh, __FILE__, __LINE__);
			if(NULL == eps->IndBit)
				eps->IndBit = veNewIVector(eps->MueVal);
			for (i = Low; i <= Hgh; i++)
				veAssignIVectorComponent(i, 1, eps->IndBit);
			break;
		default:		/* this is an error */
			panic(A_FATAL,"_psSetBit",
			      "Unknown array type (%d) : %s : %d",
			      Idx, __FILE__, __LINE__);
	}

} /*** end _psSetBit ***/

/*** end of file ***/
