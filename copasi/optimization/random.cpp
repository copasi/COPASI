/* random.c
 *
 * contains non-uniform random number generators
 */

#include <math.h>
#include "r250.h"

/* a normal distribution with mean 0 and S.D. 1 */

double rnormal01( void )
{
 static char f = 1;
 static double y;
 double a, b, s;
 double mean = 0;
 double sd = 1;

 /* negate the flag */
 f = -f;
 /* return the stored number (if one is there) */
 if( f>0 ) return y;
 for(;;)
 {
  a = 2.0 * dr250() - 1.0;
  b = 2.0 * dr250() - 1.0;
  s = a*a + b*b;
  if( ( s < 1.0 ) && ( s != 0 ) ) break;
 }
 s = sqrt( -2.0*log(s)/s );
 // save one of the numbers for the next time
 y = sd * s*a + mean;
 // and return the other
 return sd * s*b + mean;
}


/* a normal distribution with mean m and S.D. sd */

double rnormal( double m, double sd )
{
 double psd;
 /* force the std.dev. to be positive */
 /* WE REALLY SHOULD THROW AN EXCEPTION... */
 psd = fabs( sd );
 return rnormal01() * psd + m;
}


/* a strictly positive normal distribution with mean m and S.D. sd */

double rpnormal( double m, double sd )
{
 double x, pm, psd;
 /* force the mean and std.dev. to be positive */
 /* WE REALLY SHOULD THROW AN EXCEPTION... */
 pm = fabs( m );
 psd = fabs( sd );
 for(;;)
  if( ( x = rnormal( pm, psd ) ) > 0.0 ) return x;
}


/* a tentative normal distribution in logarithmic space */

double rlognormal( double m, double sd )
{
 double psd;
 /* force the std.dev. to be positive */
 /* WE REALLY SHOULD THROW AN EXCEPTION... */
 psd = fabs( sd );
 return m * pow( 10, rnormal01() * psd );
}
