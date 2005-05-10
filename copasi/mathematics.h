/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/Attic/mathematics.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/05/10 12:10:40 $
   End CVS Header */

#include <math.h>
#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif
#ifndef M_E
#define M_E            2.7182818284590452354   /* e */
#endif

#ifdef WIN32 // These are not part of ANSI C and Visual C++ 6.0 misses them.
#define asinh(__x) log(__x + sqrt(__x * __x + 1.0))
#define acosh(__x) log(__x + sqrt(__x * __x - 1.0))
#define atanh(__x) log((1.0 + __x)/(1.0 - __x))
#endif // WIN32
