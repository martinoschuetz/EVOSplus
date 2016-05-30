#include "time.h"
#include "stdio.h"
#include "stdlib.h"


struct {
     int lz;
} evz_;

#define evz_1 evz_

double z_(double *s, double (*r)());

int main()
{
	int	MAX = 1000;
	double	rand_val;
	double	streuung = 0.0;
	double	varianz = 0.0;
	int	i;
	double	sigma = 1.0;

	void    srand48();
	double	drand48();
	int	printf();

	srand48((long) time((time_t *) NULL));
	evz_1.lz = 1;

	for(i=1; i<= MAX; i++){
		rand_val = z_(&sigma, drand48);
		streuung += rand_val;
		varianz  += rand_val * rand_val;
	}

	printf("Streuung: %g\n",streuung/(double)MAX);
	printf("Varianz:  %g\n",varianz/(double)MAX);

	return(0);
}

double z_(s, r)
double *s;
double (*r) ();
{
    /* Initialized data */

    static double zp = 6.28318531;

    /* System generated locals */
    double ret_val;

    /* Builtin functions */
    double log(), sqrt(), sin(), cos();

    /* Local variables */
    static double a, b, d;

    switch ((int)evz_1.lz) {
        case 1:  goto L1;
        case 2:  goto L2;
    }
L1:
    a = sqrt(log(((*r)(&d))) * (double)-2.);
    b = zp * (*r)(&d);
    ret_val = *s * a * sin(b);
    evz_1.lz = 2;
    return ret_val;
L2:
    ret_val = *s * a * cos(b);
    evz_1.lz = 1;
    return ret_val;
} /* z_ */
