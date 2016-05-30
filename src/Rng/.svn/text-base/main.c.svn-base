
/* main.c -- implementation of JAZZ-C's RNG device manager

   Copyright (C) 1994 Joerg Heitkoetter

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. */


#include "define.h"
#include "rng.h"

#define MAXIMUM LONG_MAX

char *program_name = "RNG_Test";


int main (argc, argv)
     int argc;
     char **argv;

{
  unsigned long  i;
  double rand_val, streuung = 0.0, varianz = 0.0;

  /*  if (newRNG ("ran3", "seed = 0.123456789") != NULL)
	  if (newRNG ("ran3", "seed = 0.189") != NULL)
      if (newRNG ("ran3", "seed = 0.858") != NULL)
	  if (newRNG ("ran3", "seed = 0.323") != NULL)
	  if (newRNG ("ran3", "seed = 0.444") != NULL)
	  if (newRNG ("ran3", "seed = 0.131") != NULL) 
	  if (newRNG ("ran3", "seed = 0.999999999") != NULL)*/
	  if (newRNG ("ran3", "seed = 0.1500002115") != NULL)
    {
	  for(i=1; i<= MAXIMUM; i++){
		/*		rand_val = normal(1.0);*/
		rand_val = randomperc();
		if(rand_val < 0.0 || rand_val > 1.0)
		  printf("Out of Range : %ld : %g", i, rand_val);
		streuung += rand_val;
		/*		varianz  += rand_val * rand_val;*/
	}

	printf("Erwartungswert: %g\n",streuung/(double)MAXIMUM);
	/*	printf("Varianz:  %g\n",varianz/(double)MAXIMUM);*/
	
	streuung = 0.0, varianz = 0.0;

	deleteRNG ();
    }
  /*
  if (newRNG ("drand", "seed = 0.123456789") != NULL)
    {
      testRNG (60);
	for(i=0;i<=6;i++)
		printf("%g ",randomperc());
	printf("\n");
	for(i=1; i<= MAXIMUM; i++){
		rand_val = normal(1.0);
		streuung += rand_val;
		varianz  += rand_val * rand_val;
	}

	printf("Streuung: %g\n",streuung/(double)MAXIMUM);
	printf("Varianz:  %g\n",varianz/(double)MAXIMUM);
	streuung = 0.0, varianz = 0.0;
	
	deleteRNG ();
    }

  if (newRNG ("plauger", "seed = 0.123456789") != NULL)
    {
	testRNG (60);
	for(i=0;i<=6;i++)
		printf("%g ",randomperc());
	printf("\n");
	for(i=1; i<= MAXIMUM; i++){
		rand_val = normal(1.0);
		streuung += rand_val;
		varianz  += rand_val * rand_val;
	}

	printf("Streuung: %g\n",streuung/(double)MAXIMUM);
	printf("Varianz:  %g\n",varianz/(double)MAXIMUM);
	streuung = 0.0, varianz = 0.0;	
	deleteRNG ();
    }

  if (newRNG ("srand", "seed = 0.123456789") != NULL)
    {
	testRNG (60);
	for(i=0;i<=6;i++)
		printf("%g ",randomperc());
	printf("\n");
	for(i=1; i<= MAXIMUM; i++){
		rand_val = normal(1.0);
		streuung += rand_val;
		varianz  += rand_val * rand_val;
	}

	printf("Streuung: %g\n",streuung/(double)MAXIMUM);
	printf("Varianz:  %g\n",varianz/(double)MAXIMUM);
	streuung = 0.0, varianz = 0.0;
	deleteRNG ();
    }

  if (newRNG ("vlcr", "seed = 0.123456789") != NULL)
    {
	testRNG (60);
	for(i=0;i<=6;i++)
		printf("%g ",randomperc());
	printf("\n");
	for(i=1; i<= MAXIMUM; i++){
		rand_val = normal(1.0);
		streuung += rand_val;
		varianz  += rand_val * rand_val;
	}

	printf("Streuung: %g\n",streuung/(double)MAXIMUM);
	printf("Varianz:  %g\n",varianz/(double)MAXIMUM);
	streuung = 0.0, varianz = 0.0;
	deleteRNG ();
    }

  if (newRNG ("grefenstette", "seed = 0.123456789") != NULL)
    {
	long h0 = 0, h1 = 0, h2 = 0, h3 = 0, h4 = 0;
    
        testRNG (60);
	for(i=0;i<=6;i++)
		printf("%g ",randomperc());
	printf("\n");
	for(i=1; i<= MAXIMUM; i++){
		rand_val = normal(1.0);
		streuung += rand_val;
		varianz  += rand_val * rand_val;
	}

	printf("Streuung: %g\n",streuung/(double)MAXIMUM);
	printf("Varianz:  %g\n",varianz/(double)MAXIMUM);
	streuung = 0.0, varianz = 0.0;
	printf("\n");
	for(i=1; i<= MAXIMUM; i++) {
		switch(centerBinomial(4)) {
			case -2 : h0++; break;
			case -1 : h1++; break;
			case 0 : h2++; break;
			case 1 : h3++; break;
			case 2 : h4++; break;
			default: printf("\nFalsche Zahl\n");
		}
	}
	printf("\nW0 = %g", (double) h0 / (double) MAXIMUM);
	printf("\nW1 = %g", (double) h1 / (double) MAXIMUM);
	printf("\nW2 = %g", (double) h2 / (double) MAXIMUM);
	printf("\nW3 = %g", (double) h3 / (double) MAXIMUM);
	printf("\nW4 = %g", (double) h4 / (double) MAXIMUM);
	printf("\n");

	for(i=1;i<=100;i++) {
		printf("%ld ",rnd(0,1));
		if(i % 5 == 0)
			printf("\n");
	}
	printf("\n");
        deleteRNG ();
    }

    if (newRNG ("ran4", "seed = 0.123456789") != NULL) {

	for(i=1;i<=100;i++) {
		printf("%g ",randomperc());
		if(i % 5 == 0)
			printf("\n");
	}
	deleteRNG ();
    }
	*/	
    return(0);
}
