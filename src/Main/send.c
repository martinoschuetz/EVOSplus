/****************************************************************/
/*                                                           	*/
/*  Copyright (c) 1995                                       	*/
/*  Martin Schuetz                                             	*/
/*  Computer Science Department, LSXI       			        */
/*  University of Dortmund                                   	*/
/*  Baroper Str. 301                                         	*/
/*  D-44221 Dortmund						                    */
/*  Germany							                            */
/*								                                */
/*  e-mail: schuetz@ls11.informatik.uni-dortmund.de		        */
/*								                                */
/*  Permission is hereby granted to copy all or any part of  	*/
/*  this program for free distribution.   The author's name  	*/
/*  and this copyright notice must be included in any copy.  	*/
/*                                                           	*/
/****************************************************************/

/*
 *	file:	send.c
 *
 *    author: 	Martin Schuetz
 *
 *   created:	25.04.1995
 *
 *   purpose:	PVM communication
 *
 *    remark:	Not usable for variable dimension !!!!!
 *
 * $Log: not supported by cvs2svn $
 * Revision 2.0  1995/09/19  07:57:20  schuetz
 * pvm integrated
 *
 * 
 */

#include "send.h"


void pack_ind(individual_tPtr ind, unsigned long position)

{
  unsigned long	length = 0;
  double		help;
  int		info = 0;
  

  info = pvm_pkulong(&position, 1, 1); /*The position in it's old population. */
  
  length = inGetXLength(ind);
  info = pvm_pkulong(&length, 1, 1);
  if(length != 0)
	info = pvm_pkdouble(veGetVectorDataField(inGetX(ind)), length, 1);
  info = pvm_pkdouble(&(ind->lx), 1, 1);
  info = pvm_pkdouble(&(ind->ux), 1, 1);
  
  length = inGetDLength(ind);
  info = pvm_pkulong(&length, 1, 1);
  if(length != 0)
	info = pvm_pklong(veGetIVectorDataField(inGetD(ind)), length, 1);
  info = pvm_pklong(&(ind->ld), 1, 1);
  info = pvm_pklong(&(ind->ud), 1, 1);
  
  length = inGetSigmaLength(ind);
  info = pvm_pkulong(&length, 1, 1);
  if(length != 0)
	info = pvm_pkdouble(veGetVectorDataField(inGetSigma(ind)), length, 1);
  info = pvm_pkdouble(&(ind->lsigma), 1, 1);
  info = pvm_pkdouble(&(ind->usigma), 1, 1);
  
  length = inGetAlphaLength(ind);
  info = pvm_pkulong(&length, 1, 1);
  if(length != 0)
	info = pvm_pkdouble(veGetVectorDataField(inGetAlpha(ind)), length, 1);
  info = pvm_pkdouble(&(ind->lalpha), 1, 1);
  info = pvm_pkdouble(&(ind->ualpha), 1, 1);
  
  length = inGetPLength(ind);
  info = pvm_pkulong(&length, 1, 1);
  if(length != 0)
	info = pvm_pkdouble(veGetVectorDataField(inGetP(ind)), length, 1);
  info = pvm_pkdouble(&(ind->lp), 1, 1);
  info = pvm_pkdouble(&(ind->up), 1, 1);
  
  help = inGetFx(ind);
  info = pvm_pkdouble(&help, 1, 1);
  
  if (info < 0)
	panic(A_FATAL, "pack_ind", "packing error %d : %s : %d\n", info, __FILE__, __LINE__);
  return;
}



void unpack_ind(individual_tPtr ind)
	 
{
  unsigned long	length = 0;
  int		info = 0;
/*  unsigned long position = 0;*/
  
  
  /*info = pvm_upkulong(&position, 1, 1); The position in it's old population. */
  
  info = pvm_upkulong(&length, 1, 1);
  if(length != 0)
	info = pvm_upkdouble(veGetVectorDataField(inGetX(ind)), length, 1);
  info = pvm_upkdouble(&(ind->lx), 1, 1);
  info = pvm_upkdouble(&(ind->ux), 1, 1);
  
  info = pvm_upkulong(&length, 1, 1);
  if(length != 0)
	info = pvm_upklong(veGetIVectorDataField(inGetD(ind)), length, 1);
  info = pvm_upklong(&(ind->ld), 1, 1);
  info = pvm_upklong(&(ind->ud), 1, 1);
  
  info = pvm_upkulong(&length, 1, 1);
  if(length != 0)
	info = pvm_upkdouble(veGetVectorDataField(inGetSigma(ind)), length, 1);
  info = pvm_upkdouble(&(ind->lsigma), 1, 1);
  info = pvm_upkdouble(&(ind->usigma), 1, 1);
  
  info = pvm_upkulong(&length, 1, 1);
  if(length != 0)
	info = pvm_upkdouble(veGetVectorDataField(inGetAlpha(ind)), length, 1);
  info = pvm_upkdouble(&(ind->lalpha), 1, 1);
  info = pvm_upkdouble(&(ind->ualpha), 1, 1);
  
  info = pvm_upkulong(&length, 1, 1);
  if(length != 0)
	info = pvm_upkdouble(veGetVectorDataField(inGetP(ind)), length, 1);
  info = pvm_upkdouble(&(ind->lp), 1, 1);
  info = pvm_upkdouble(&(ind->up), 1, 1);
  
  info = pvm_upkdouble(&(ind->fx), 1, 1);
  
  if (info < 0)
	panic(A_FATAL, "unpack_ind", "unpacking error %d: %s : %d\n", info, __FILE__, __LINE__);
  return;
}



void send_Best(param_tPtr eps, population_tPtr pop)
	 
{
  int	ptid = 0;
  
  if (pvm_initsend(PvmDataRaw) < 0)
	panic(A_FATAL,"send_Best", "initsend for group %d failed : %s : %d",
		  eps->inst, __FILE__, __LINE__);
  
  if((ptid = pvm_parent()) == PvmNoParent)
	panic(A_FATAL,"send_Best", "parent do not exist : : %s : %d",
		  __FILE__, __LINE__);

  pvm_pkint(&(eps->tid), 1, 1);
  pvm_pkulong(&(eps->GenCnt), 1, 1);
  pvm_pkulong(&(eps->TrlCnt), 1, 1);
  pack_ind(poGetIndividual(1, pop), 1);
#ifdef DEBUG
  fprintf(stderr,"\nTask %d sending best to master %d\n",
		  eps->inst, ptid);
#endif
  if(pvm_send(ptid, MSGTAG_BEST) < 0)
	panic(A_WARN, "send_neighbours", "best sending to parent %d failed : %s : %d",
		  ptid, __FILE__, __LINE__);
  
  return;
}



int recv_async_Best(param_tPtr eps, individual_tPtr ind,
					unsigned long *GenCnt, unsigned long *TrlCnt)
	 
{
  unsigned long	position;
  int		state, tid;
  
  
  if((state = pvm_nrecv(-1, MSGTAG_BEST)) < 0)
	panic(A_FATAL, "recv_async_Best", "receiving best failed (%d) :%s : %d",
		  state, __FILE__, __LINE__);
#ifdef DEBUG
  if(state == 0)
	fprintf(stderr,"\nMaster %d none areceiving\n", pvm_mytid());
#endif
  if(state > 0) {
	pvm_upkint(&tid, 1, 1);
	pvm_upkulong(GenCnt, 1, 1);
	pvm_upkulong(TrlCnt, 1, 1);
	pvm_upkulong(&position, 1, 1);
	unpack_ind(ind);
#ifdef DEBUG
	fprintf(stderr,"\nMaster areceiving best from neigbhour %d\n",
			pvm_getinst(eps->Group, tid));
#endif
  }
  
  return(state);
}


void recv_sync_Best(param_tPtr eps,individual_tPtr ind,
					unsigned long *GenCnt, unsigned long *TrlCnt)
	 
{
  unsigned long	position;
  int		state, tid;
  
  
  if((state = pvm_recv(-1, MSGTAG_BEST)) < 0)
	panic(A_FATAL, "recv_Best", "receiving best failed (%d) :%s : %d",
		  state, __FILE__, __LINE__);
  
  pvm_upkint(&tid, 1, 1);
  pvm_upkulong(GenCnt, 1, 1);
  pvm_upkulong(TrlCnt, 1, 1);
  pvm_upkulong(&position, 1, 1);
  unpack_ind(ind);
#ifdef DEBUG
  fprintf(stderr,"\nMaster receiving best from neigbhour %d\n", eps->inst);
#endif
  
  return;
}



void send_Neighbours(param_tPtr eps, population_tPtr pop)
	 
{
  unsigned long	migrant = 1;
  int		neighbour;
  
  while((neighbour = NextTOPOLOGY(eps)) > 0) {
	
	while((migrant = miMigrants(eps)) != 0) {
	  if(pvm_initsend(PvmDataRaw) < 0)
		panic(A_FATAL,"send_neighbours", "initsend for group %d failed : %s : %d",
			  eps->inst, __FILE__, __LINE__);
	  pack_ind(poGetIndividual(migrant, pop), migrant);
#ifdef DEBUG
	  fprintf(stderr, "\nTask %d sending migrant %ld to neigbhour %d\n",
			  eps->inst,migrant,pvm_getinst(eps->Group, neighbour));
#endif
	  if(pvm_send(neighbour, MSGTAG_IND) < 0)
		panic(A_WARN, "send_neighbours","sending to neighbour %d failed : %s : %d",
		      neighbour, __FILE__, __LINE__);
	}
  }
  
  return;
}



void recv_sync(param_tPtr eps, individual_tPtr *MigrationBuffer)
	 /*void recv_sync(param_tPtr eps, population_tPtr pop)*/
	 
{
  int		i, neighbour;
  unsigned long	position, j = 0;
  
  
  while((neighbour = NextTOPOLOGY(eps)) > 0) {
	
	for (i = 1; i <= eps->NoOfMigrants; i++) {
	  
	  if(pvm_recv(neighbour, MSGTAG_IND) < 0)
		panic(A_FATAL, "recv_sync", "can't receive synchron from %d :%s : %d",
			  neighbour, __FILE__, __LINE__);
#ifdef DEBUG
	  fprintf(stderr,"\nTask %d receiving migrant %d from neigbhour %d\n",
			  eps->inst, i, pvm_getinst(eps->Group, neighbour));
#endif
	  pvm_upkulong(&position, 1, 1);
	  /* The position in the population. */
	  
	  unpack_ind(MigrationBuffer[j]);
	  /*		unpack_ind(poGetIndividual(position, pop));	*/
	  
	  j++;		
	}
  }
  
  return;
}



void recv_async(param_tPtr eps, individual_tPtr *MigrationBuffer)
	 /*void recv_async(param_tPtr eps, population_tPtr pop)*/
	 
{
  int		state, neighbour,
	NoOfMigrants;
  unsigned long	position, j = 0;
  
  
  while((neighbour = NextTOPOLOGY(eps)) > 0) {
	
	NoOfMigrants = eps->NoOfMigrants;
	
	while (((state = pvm_nrecv(neighbour, MSGTAG_IND)) > 0) &&
		   NoOfMigrants > 0) {
	  pvm_upkulong(&position, 1, 1);
	  unpack_ind(MigrationBuffer[j]);
	  /*		unpack_ind(poGetIndividual(position, pop));	*/
	  NoOfMigrants--; j++;
#ifdef DEBUG
	  fprintf(stderr,"\nTask %d areceiving migrant %ld from neigbhour %d\n",
			  eps->inst, eps->NoOfMigrants - NoOfMigrants,
			  pvm_getinst(eps->Group, neighbour));
#endif
	}
	
	if (state < 0)
	  panic(A_FATAL, "recv_async",
			"%d %d: recv from neighbour (%X) %d failed :%s : %d",
			eps->inst, eps->tid, neighbour, state, __FILE__, __LINE__);
	
  }
  
  return;
}
