/* 
	MATRIX.H
*/


#define N_MATRIX  30


typedef struct matrix
{
    int zeilen;
    int spalten;
    double a[N_MATRIX][N_MATRIX];
}MATRIX;


void print_matrix() ;
void mov_matrix() ;
int add_matrix() ;
int sub_matrix() ;
int lin_matrix() ;
int mult_matrix() ;
int ein_matrix() ;
int inv_matrix() ;
int exp_matrix() ;
double norm_matrix() ;
double gauss_matrix() ;

