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
 *	file:	send.h
 *
 *    author: 	Martin Schuetz
 *
 *   created:	02.05.1995
 *
 *   purpose:	prototype declarations for send.c
 *
 *    remark:
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:58:47  schuetz
 * pvm integrated
 *
 * 
 */

#ifndef SEND_H
#define SEND_H

#include "define.h"
#include "pop.h"

 
/* send.c */
void pack_ind PP((individual_tPtr ind, unsigned long position));
void unpack_ind PP((individual_tPtr ind));
void send_Best PP((param_tPtr eps, population_tPtr pop));
void recv_sync_Best  PP((param_tPtr eps, individual_tPtr ind, unsigned long *GenCnt, unsigned long *TrlCnt));
int  recv_async_Best PP((param_tPtr eps, individual_tPtr ind, unsigned long *GenCnt, unsigned long *TrlCnt));
void send_Neighbours PP((param_tPtr eps, population_tPtr pop));
void recv_sync PP((param_tPtr eps, individual_tPtr *MigrationBuffer));
/*void recv_sync PP((param_tPtr eps, population_tPtr pop));*/
void recv_async PP((param_tPtr eps, individual_tPtr *MigrationBuffer));
/*void recv_async PP((param_tPtr eps, population_tPtr pop));*/

#endif	/* SEND_H */
