
#ifndef INCLUDE_R250_H_FILE
#define INCLUDE_R250_H_FILE

/*** Function prototypes for R250 random number generator, by W. L. Maier  ***/
unsigned int r250( void );
unsigned int r250n(unsigned n);
double dr250( void );
void r250_init(int seed);

double rnormal01( void );
double rnormal( double m, double sd );
double rpnormal( double m, double sd );
double rlognormal( double m, double sd );

#endif

