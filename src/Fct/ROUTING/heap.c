#include "heap.h"

/**********************************************************************
* function: allc_arr
*   author: jz
* modified: 16.10.95
*  purpose:
*          alloc memory for an array of size k the call of this function
*          must be:   allc_arr(&y,k);
*          where int *y; must be declared in the calling function
*          (to change the value of a pointer, you have to give the
*          pointer of the pointer.)
***********************************************************************/
int allc_arr(ARRTYPE **arr,int k)
{
/*  if (*arr!=NULL){
	free(*arr);
	*arr=NULL;
  } */
  if ((*arr= (ARRTYPE *) malloc (k * sizeof(ARRTYPE))) == NULL) {
    fprintf(stderr,"\nERROR : alloc_arr : failure in memory allocation\n");
  return(1);
  }
  return (0);
}


int cp_arr(ARRTYPE *arr, KEY *arx, int n)
{
  int i;
  for (i=1-OFFSET;i<n+1-OFFSET;i++){
    arr[i].key=arx[i];
    arr[i].ptr=i;
  } /* end for i-loop*/
  return(0);
}

/************************************************************************/
/* Function(s)	: heapsort2, uses reheap2				*/
/* Purpose	: heapsort building a sorted array MINIMUM at 		*/
/*		  arr[0].key						*/
/* Parameters	: pointer on an array of type ARRTYPE (in test.h)	*/
/* Method	: building a heap, change the top-element to the end    */
/*		  and call the reheap on that				*/
/* Dates	: 25.10.95, 19.3.96					*/
/* Status	: tested 						*/
/* Specials	: if you call the reheap only k-times, you have the	*/
/*		  k-smallest elements of the array			*/
/*		 -sorts the .key of the array, while ptr can be a 	*/
/*		  pointer to the sorted structure, now it is int, for	*/
/*		  to represent the array-fieldnumber... 		*/
/*		  changes may be made in typedef of KEY in heap.h	*/
/* author	: Joerg Ziegenhirt					*/
/*									*/
/*									*/
/************************************************************************/

int reheap2(ARRTYPE *arr, int i, int p)
{
  int j;
  ARRTYPE change;
  while (i+i+OFFSET<p)
  {
    if ((i+i+OFFSET+1)>=p){       /* untersuchter Knoten hat nur einen Nachfolger*/
        j=i+i+OFFSET;
    }else{
      if (arr[i+i+OFFSET].key>arr[i+i+OFFSET+1].key){  
        j=i+i+OFFSET;
      } else {
        j=i+i+OFFSET+1;
      }
    }
    if (arr[i].key>arr[j].key){break;}	
    else{
      change=arr[i];
      arr[i]=arr[j];
      arr[j]=change;
      i=j;
    }
  }
return(0);
}

int heapsort2(ARRTYPE *arr,long int n)
{
  int i,j;
  ARRTYPE change;
/* heapaufbau */
 for (i=n/2;i>=0;i--){
    if ((i+i+OFFSET)<n) {
      if ((i+i+OFFSET+1)>=n){
	j=i+i+OFFSET;
      } else{
	if (arr[i+i+OFFSET].key>arr[i+i+OFFSET+1].key){ 
	  j=i+i+OFFSET;
	} else{
	  j=i+i+OFFSET+1;
	}
      }
      if(arr[i].key<arr[j].key){
	change=arr[i];
	arr[i]=arr[j];
	arr[j]=change;
	reheap2(arr,j,n);
      }
    }  /* end if i+i+OFFSET < n */
  }  /* end for */
/*ende des heapaufbaus */
  for (i=0;i<n-OFFSET;i++){
    if (arr[n-i-OFFSET].key<arr[0].key){  
      change=arr[n-i-OFFSET];
      arr[n-i-OFFSET]=arr[0];
      arr[0]=change;
      reheap2(arr,0,n-i-OFFSET);
    }
  }
return(0);
}

/************************************************************************/
/* Function(s)	: heapsort1, uses reheap1				*/
/* Purpose	: heapsort building a sorted array MAXIMUM at 		*/
/*		  arr[0].key						*/
/* Parameters	: pointer on an array of type ARRTYPE (in test.h)	*/
/* Method	: building a heap, change the top-element to the end    */
/*		  and call the reheap on that				*/
/* Dates	: 25.10.95, 19.3.96					*/
/* Status	: tested 						*/
/* Specials	: if you call the reheap only k-times, you have the	*/
/*		  k-smallest elements of the array			*/
/*		 -sorts the .key of the array, while ptr can be a 	*/
/*		  pointer to the sorted structure, now it is int, for	*/
/*		  to represent the array-fieldnumber... 		*/
/*		  changes may be made in typedef of KEY in heap.h	*/
/* author	: Joerg Ziegenhirt					*/
/*									*/
/*									*/
/************************************************************************/
int reheap1(ARRTYPE *arr,int i, int p)
{
  int j;
  ARRTYPE change;
  while (i+i+OFFSET<p)
  {
    if ((i+i+OFFSET+1)>=p){       /* untersuchter Knoten hat nur einen Nachfolger*/
        j=i+i+OFFSET;
    }else{
      if (arr[i+i+OFFSET].key<arr[i+i+OFFSET+1].key){     
        j=i+i+OFFSET;
      } else {
        j=i+i+OFFSET+1;
      }
    }
    if (arr[i].key<arr[j].key){break;}
    else{
      change=arr[i];
      arr[i]=arr[j];
      arr[j]=change;
      i=j;
    }
  }
return(0);
}

int heapsort1(ARRTYPE *arr,long int n)
{
  int i,j;
  ARRTYPE change;
/* heapaufbau */
 for (i=n/2;i>=0;i--){
    if ((i+i+OFFSET)<n) {
      if ((i+i+OFFSET+1)>=n){
	j=i+i+OFFSET;
      } else{
	if (arr[i+i+OFFSET].key<arr[i+i+OFFSET+1].key){ 
	  j=i+i+OFFSET;
	} else{
	  j=i+i+OFFSET+1;
	}
      }
      if(arr[i].key>arr[j].key){    
	change=arr[i];
	arr[i]=arr[j];
	arr[j]=change;
	reheap1(arr,j,n);
      }
    }  /* end if i+i+OFFSET < n */
  }  /* end for */
/*ende des heapaufbaus */

  for (i=0;i<n-OFFSET;i++){
    if (arr[n-i-OFFSET].key>arr[0].key){
      change=arr[n-i-OFFSET];
      arr[n-i-OFFSET]=arr[0];
      arr[0]=change;
      reheap1(arr,0,n-i-OFFSET);
    }
  }
return(0);
}
