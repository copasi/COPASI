/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/blaswrap.h,v $
   $Revision: 1.1.2.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/01/11 14:45:49 $
   End CVS Header */

#ifndef __BLAS_H
#define __BLAS_H

#ifdef min
# undef min
#endif // min

#ifdef max
# undef max
#endif // max

extern "C"
  {
#ifdef USE_MKL
# include "mkl_lapack.h"
#else
# if (defined USE_CLAPACK || defined USE_LAPACK)
#  include "f2c.h"
#  include "blas.h"
#  ifdef USE_CLAPACK
#   define dgemm_ f2c_dgemm
#  endif // USE_CLAPACK
# endif // USE_CLAPACK || USE_LAPACK
#endif // USE_MKL
  }

#ifdef min
# undef min
#endif // min

#ifdef max
# undef max
#endif // max

#ifdef WIN32
# define min _cpp_min
# define max _cpp_max
#endif // WIN32

#endif // __BLAS_H
