/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/clapackwrap.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:16:32 $
   End CVS Header */

#ifdef min
# undef min
#endif // min

#ifdef max
# undef max
#endif // max

extern "C"
  {
#ifdef USE_CLAPACK
# include "f2c.h"
#endif

#include "clapack.h"        //use CLAPACK
  }

#ifdef min
# undef min
#endif // min

#ifdef max
# undef max
#endif // max

#ifdef WIN32
#define min _cpp_min
#define max _cpp_max
#endif // WIN32
