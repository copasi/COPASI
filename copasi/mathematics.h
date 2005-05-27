/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/Attic/mathematics.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/27 21:12:10 $
   End CVS Header */

#ifndef COPASI_mathematics
#define COPASI_mathematics

#include <math.h>
#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif
#ifndef M_E
#define M_E            2.7182818284590452354   /* e */
#endif

#ifdef WIN32 // These are not part of ANSI C and Visual C++ 6.0 misses them.
static inline double asinh(double value)
{return log(value + sqrt(value * value + 1.0));}

static inline double acosh(double value)
{return log(value + sqrt(value * value - 1.0));}

static inline double atanh(double value)
{return (.5 * log((1.0 + value) / (1.0 - value)));}
#endif // WIN32

#endif // COPASI_mathematics
