/*
	Matrix
	4.1.93
*/


#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <memory.h>
#include "rinterface.h" 
#include "rmatrix.h"


void print_matrix(MATRIX *ma)
{
    int z,
        s,
        zmax,
        smax;
    double x;
    zmax = (ma->zeilen < 10) ? ma->zeilen : 10;
    smax = (ma->spalten < 10) ? ma->spalten : 10;
    printf("%d*%d-Matrix", ma->zeilen, ma->spalten);
    for (z = 0; z < zmax; z++)
    {
	printf("\n");
	for (s = 0; s < smax; s++)
	{
	    x = ma->a[z][s];
/*		if (fabs(x) < 1.e-14 ) x = 0. ; */
	    printf("%12.5f ", x);
	}
    }
    printf("\n");
}

void mov_matrix(MATRIX *mc,MATRIX *ma)
{
  int s,z;
  /*  *mc=ma;  */
  /*  memcpy(&mc, &ma, sizeof(ma)); */
    mc->spalten=ma->spalten;
    mc->zeilen=ma->zeilen;
    for (z = 0; z < ma->zeilen; z++)
        for (s = 0; s < ma->spalten; s++) {
            mc->a[z][s] = ma->a[z][s];
        }
}



int add_matrix(MATRIX *mc, MATRIX *ma, MATRIX *mb)
{
    int z,
        s;
    if (ma->zeilen != mb->zeilen)
	return (1);
    if (ma->spalten != mb->spalten)
	return (2);
    mc->zeilen = ma->zeilen;
    mc->spalten = ma->spalten;

    for (z = 0; z < mc->zeilen; z++)
	for (s = 0; s < mc->spalten; s++)
	    mc->a[z][s] = ma->a[z][s] + mb->a[z][s];
    return (0);
}

int sub_matrix(MATRIX *mc, MATRIX *ma, MATRIX *mb)
{
    int z,
        s;
    if (ma->zeilen != mb->zeilen)
	return (1);
    if (ma->spalten != mb->spalten)
	return (2);
    mc->zeilen = ma->zeilen;
    mc->spalten = ma->spalten;

    for (z = 0; z < mc->zeilen; z++)
	for (s = 0; s < mc->spalten; s++)
	    mc->a[z][s] = ma->a[z][s] - mb->a[z][s];

    return (0);
}

int lin_matrix(MATRIX *mc, double a, MATRIX *ma, double b, MATRIX *mb)
{
    int z,
        s;
    if (ma->zeilen != mb->zeilen)
	return (1);
    if (ma->spalten != mb->spalten)
	return (2);
    mc->zeilen = ma->zeilen;
    mc->spalten = ma->spalten;
    for (z = 0; z < mc->zeilen; z++)
	for (s = 0; s < mc->spalten; s++)
	    mc->a[z][s] = a * ma->a[z][s] + b * mb->a[z][s];
    return (0);
}

int mult_matrix(MATRIX *mc, MATRIX *ma, MATRIX *mb)
{
    MATRIX md;
    int i, z,
        s;
    if (ma->spalten != mb->zeilen)
	return (1);
    md.zeilen = ma->zeilen;
    md.spalten = mb->spalten;
    for (z = 0; z < md.zeilen; z++)
	for (s = 0; s < md.spalten; s++)
	{
	    md.a[z][s] = 0;
	    for (i = 0; i < ma->spalten; i++)
		md.a[z][s] += ma->a[z][i] * mb->a[i][s];
	}
    mov_matrix(mc, &md);
    return (0);
}

int ein_matrix(MATRIX *mc, int n)
{
    int z,
        s;
    if (n > N_MATRIX)
	return (n);
    if (n < 0)
	return (-1);
    mc->zeilen = n;
    mc->spalten = n;

    for (z = 0; z < mc->zeilen; z++)
	for (s = 0; s < mc->spalten; s++)
	    mc->a[z][s] = (s == z) ? 1. : 0.;
    return (0);
}

int inv_matrix(MATRIX *mc, MATRIX *ma)
{
    MATRIX mb,
           my,
           me;
    int i, n;
    n = mc->zeilen = mc->spalten = ma->zeilen;
    ein_matrix(&me, n);
    sub_matrix(&mb, &me, ma);
    mov_matrix(mc, &me);
    add_matrix(&my, &me, &mb);
    for (i = 0; i < 8; i++)
    {
	mult_matrix(mc, &my, mc);
	mult_matrix(&mb, &mb, &mb);
	add_matrix(&my, &me, &mb);
    }
    return (0);
}

int exp_matrix(MATRIX *mc, MATRIX *ma)
{
    MATRIX mb,
           me;
    int i, n;
    double fak;
    n = mc->zeilen = mc->spalten = ma->zeilen;
    ein_matrix(&me, n);
    add_matrix(mc, &me, ma);
    mov_matrix(&mb, ma);
    fak = 1;
    for (i = 2; i < 20; i++)
    {
	mult_matrix(&mb, &mb, ma);
	fak /= i;
	lin_matrix(mc, 1., mc, fak, &mb);
    }
    return (0);
}

double norm_matrix(MATRIX *mc, MATRIX *ma)
{
    double fak;
    int z,
        s;
    mc->zeilen = ma->zeilen;
    mc->spalten = ma->spalten;
    fak = 0.;
    for (z = 0; z < mc->zeilen; z++)
	for (s = 0; s < mc->spalten; s++)
	    if (fabs(ma->a[z][s]) > fak)
		fak = fabs(ma->a[z][s]);

    for (z = 0; z < mc->zeilen; z++)
	for (s = 0; s < mc->spalten; s++)
	    mc->a[z][s] = ma->a[z][s] / fak;
    return (fak);
}

double gauss_matrix(MATRIX *mmc, MATRIX *mma, MATRIX *mb)
{
    MATRIX ma,
           mc;
    double det,
           faktor, max;
    int z,
        i,
        pivz = 0, pivot[N_MATRIX],
        permutation, s;


    if (mma->zeilen != mb->zeilen)
    {
	printf("Gauss: Matrizen haben ungleiche Zeilenzahl.\7\n");
	mc.zeilen = mc.zeilen = 0.;
	return (0.);
    }
    mov_matrix(&ma, mma);
    mov_matrix(&mc, mb);
    mc.spalten = mb->spalten;
    memset(pivot, 0, sizeof(pivot));

    det = 1;
    for (s = 0; s < ma.zeilen; s++)
    {
	max = 0.;
	for (z = 0; z < ma.zeilen; z++)
	{
	    if (pivot[z] == 0 && fabs(ma.a[z][s]) > max)
	    {
		max = fabs(ma.a[z][s]);
		pivz = z;
	    }
	}


	if (max == 0.)
	    return (0.);	/* Matrix singulaer */
	pivot[pivz] = s + 1;

	for (z = 0; z < ma.zeilen; z++)
	{
	    if (z != pivz)
	    {
		faktor = ma.a[z][s] / ma.a[pivz][s];
		for (i = s; i < ma.spalten; i++)
		{
		    ma.a[z][i] -= faktor * ma.a[pivz][i];
		}
		for (i = 0; i < mc.spalten; i++)
		{
		    mc.a[z][i] -= faktor * mc.a[pivz][i];
		}
	    }
	    else
	    {
		faktor = ma.a[pivz][s];
		det *= faktor;
		for (i = s; i < ma.spalten; i++)
		{
		    ma.a[z][i] /= faktor;
		}
		for (i = 0; i < mc.spalten; i++)
		{
		    mc.a[z][i] /= faktor;
		}
	    }
	}
    }

    mmc->zeilen = mc.zeilen;
    mmc->spalten = mc.spalten;
    for (z = 0; z < mc.zeilen; z++)
    {
	permutation += z - pivot[z];
	for (s = 0; s < mc.spalten; s++)
	    mmc->a[pivot[z] - 1][s] = mc.a[z][s];
    }
    permutation = 0;
    for (s = 0; s < mc.zeilen - 1; s++)
	for (z = s + 1; z < mc.zeilen; z++)
	    if (pivot[z] < pivot[s])
		permutation = 1 - permutation;

    if (permutation)
	return (-det);
    return (det);
}
