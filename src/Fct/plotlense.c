#include <stdio.h>
#include <math.h>
#include <values.h>

static double	RefInd[2] = {2.2, 4.2}; /* Refractive indices */

double reflection(long dim, double *x, long *d);

FILE	*SpectralProfil;



int plotlense(long dim, double *x, long *d, double fx,
	      char *wave, char *structure, char *final)

{
	unsigned long   i = 1,
			layers = 1;
	double          thickness = 0.0,
			accuThickness = 0.0,
			epsilon = 0.0001;
	FILE		*FilterStructure,
			*FinalFilter;


	if((SpectralProfil = fopen(wave, "w")) == NULL)
		return(0);
	if((FilterStructure = fopen(structure, "w")) == NULL)
		return(0);
	if((FinalFilter = fopen(final, "w")) == NULL)
		return(0);

	if(fabs(fx - reflection(dim,x,d)) >= epsilon) {
		fprintf(stderr, "\nnon corresponding merit values\n");
		return(0);
	}
	fprintf(SpectralProfil, "# fx = %g", fx);

	fprintf(FinalFilter, 
		"# Layer\tIndex\tGeometrical(nm)\t\tOptical(mikrom)\n");
	fprintf(FinalFilter, "\n%ld\t%.4g\t",
		layers, RefInd[d[0]]);
	thickness = x[0];

	fprintf(FilterStructure, "# thickness (mikrom)\tindex\n\n");
	fprintf(FilterStructure, "%.10e\t%.4g\n", 0.0, RefInd[d[0]]);

	for(i = 1; i < dim; i++) {
		if(d[i-1] != d[i]) {
			fprintf(FinalFilter, "%.10e\t%.10e\n",
				thickness, thickness /1000.0 * RefInd[d[i-1]]);
			accuThickness += thickness;
			fprintf(FilterStructure, "%.10e\t%.4g\n",
				accuThickness/1000.0, RefInd[d[i]]);
			thickness = 0.0;
			layers++;
			fprintf(FinalFilter, "%ld\t%.4g\t",
				layers, RefInd[d[i]]);
		}
		thickness += x[i];
	}

	fprintf(FinalFilter, "%.10e\t%.10e\n\n",
		thickness, thickness /1000.0 *RefInd[d[i-1]]);

	accuThickness += thickness;
	fprintf(FilterStructure, "%.10e\t%.4g\n",
		accuThickness/1000.0, RefInd[d[i-1]]);
	fprintf(FilterStructure, "%.10e\t%.4g\n",
		accuThickness/1000.0, 0.0);

	if(fclose(SpectralProfil) == EOF)
		return(0);
	if(fclose(FilterStructure) == EOF)
		return(0);
	if(fclose(FinalFilter) == EOF)
		return(0);
	
	return(1);
}




double reflection(long dim, double *x, long *d)

{

	unsigned long	m = 47;		/* number of wavelengths. */
	double		XAir = 1.0,	/* refractory index of incident medium.
					   Default medium is air */
			XSub = 4.0,	/* refractory index of substrate.
					   Default medium is germaium.
					   Glass has a refractory index 1.5.*/
			lower = 7.7,	/* Lower wavel. of the band of interest. */
/*			upper = 12.3    Upper wavel. of the band of interest. */
			stepsize = 100.0;

    	unsigned long	i, j;
    	double 		ConsI, Refl, Wale, Delta,
			XMerit = 0.0,
			Y11, Y12, Y21, Y22, X11, X12, X21, X22, 
			Z11, Z12, Z21, Z22, QQ1, QQ2, AA;


	ConsI = XAir * XSub * 4.0;
	for (i = 1; i <= m; i++) {
	    Wale  = lower * 1000.0 + stepsize * ((double) i-1);

	    Delta = 2.0 * M_PI * x[0] * RefInd[d[0]] / Wale;
	    /*  POSIX solution
	     *
	     * Y11   = Y22 = cos(Delta);
	     * AA	   = sin(Delta);
	     *
	     */
	    /* Nonstandard solution: needs 14 % less time! */
	    sincos(Delta, &AA, & Y11); 
	    Y22 = Y11;
	    Y12   = AA / RefInd[d[0]];
	    Y21   = AA * RefInd[d[0]];
	    /* With this precalculation the multiplication with
	       the identity matrix can be omitted. */

	    for (j = 2; j <= (unsigned long) dim; j++) {
	        Delta = 2.0 * M_PI * x[j-1] * RefInd[d[j-1]] / Wale;
		/* POSIX solution
		 *
		 * X11 = cos(Delta);
		 * X22 = X11;
		 * AA  = sin(Delta);
		 */

		/* Nonstandard solution: needs 14 % less time! */
		sincos(Delta, &AA, &X11);
		X22 = X11;
		
		X21 = AA * RefInd[d[j-1]];
		X12 = AA / RefInd[d[j-1]];
		
		Z11 = Y11 * X11 - Y12 * X21;
		Z12 = Y11 * X12 + Y12 * X22;
		Z21 = Y21 * X11 + Y22 * X21;
		Z22 = - Y21 * X12 + Y22 * X22;
		/* Minus results from the complex calculation */
		Y11 = Z11;
		Y12 = Z12;
		Y21 = Z21;
		Y22 = Z22;
	    }/* end calculation of M(lambda_i)	*/

	    QQ1	 = XAir * Y11 + XSub * Y22;
	    QQ2	 = XAir * XSub * Y12 + Y21;
	    Refl = 1.0 - ConsI / (QQ1 * QQ1 + QQ2 * QQ2);

	    fprintf(SpectralProfil, "%.10e\t\t%.10e\n", Wale/1000.0, Refl);
	    
		XMerit = XMerit + Refl * Refl;
	}

	return(100.0 * sqrt(XMerit / (double) m));
}
