/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/blaswrap.h,v $
   $Revision: 1.1.2.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/01/10 22:50:03 $
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
 # ifdef USE_CLAPACK
 #  include "f2c.h"
 #  define dgemm_ f2c_dgemm
 # endif
 # include "blas.h"
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
