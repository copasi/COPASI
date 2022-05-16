// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_blaswrap
#define COPASI_blaswrap

#ifdef min
# undef min
#endif // min

#ifdef max
# undef max
#endif // max

extern "C"
{
#ifdef HAVE_BLASWRAP_H
# include <blaswrap.h>
#else
# ifdef USE_MKL
#  include "mkl_blas.h"
#  define daxpy_ daxpy
#  define dcopy_ dcopy
#  define ddot_ ddot
#  define dgemm_ dgemm
#  define dnrm2_ dnrm2
#  define dscal_ dscal
#  define idamax_ idamax
# endif // USE_MKL

# if (defined HAVE_CLAPACK_H || defined HAVE_LAPACK_H)
#  if (defined WIN32 && defined HAVE_LAPACK_H)
#   define daxpy_ DAXPY
#   define dcopy_ DCOPY
#   define ddot_ DDOT
#   define dgemm_ DGEMM
#   define dnrm2_ DNRM2
#   define dscal_ DSCAL
#   define idamax_ IDAMAX
#  endif // (defined WIN32 && defined HAVE_LAPACK_H)

# if (defined HAVE_CLAPACK_H && !defined NO_BLAS_WRAP && !defined HAVE_APPLE)
#  define daxpy_ f2c_daxpy
#  define dcopy_ f2c_dcopy
#  define ddot_ f2c_ddot
#  define dgemm_ f2c_dgemm
#  define dnrm2_ f2c_dnrm2
#  define dscal_ f2c_dscal
#  define idamax_ f2c_idamax
# endif // (defined HAVE_CLAPACK_H && !defined NO_BLAS_WRAP && !defined HAVE_APPLE)

# endif // (defined HAVE_CLAPACK_H || defined HAVE_LAPACK_H)
#endif // HAVE_BLASWRAP_H

# ifdef HAVE_F2C_H
#  include <f2c.h>
# else
#  include "copasi/lapack/f2c.h"
# endif
# undef abs

# ifdef HAVE_BLAS_H
#  include <blas.h>
# elif defined(HAVE_CBLAS_H)
#  include <cblas.h>
# else
#  include "copasi/lapack/blas.h"
# endif

#ifdef USE_SUNPERF
# include "sunperf.h"
#endif // USE_SUNPERF
}

#ifdef HAVE_APPLE
# undef abs
# undef max
# undef min
# include <Accelerate/Accelerate.h>
# define daxpy_(N, ALPHA, X, INCX, Y, INCY) \
  cblas_daxpy(*N, *ALPHA, X, *INCX, Y, *INCY)
# define dcopy_(N, X, INCX, Y, INCY) \
  cblas_dcopy(*N, X, *INCX, Y, *INCY)
# define ddot_(N, X, INCX, Y, INCY) \
  cblas_ddot(*N, X, *INCX, Y, *INCY)
# define dgemm_(TRANSA, TRANSB, M, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC) \
  cblas_dgemm(CblasColMajor, \
              (*TRANSA == 'N' ? CblasNoTrans: CblasTrans), \
              (*TRANSB == 'N' ? CblasNoTrans: CblasTrans), \
              *M, *N, *K, *ALPHA, A, *LDA, B, *LDB, *BETA, C, *LDC)
# define dscal_(N, ALPHA, X, INCX) cblas_dscal(*N, *ALPHA, X *INCX)
# define dnrm2_(N, X, INCX) cblas_dnrm2(*N, X, *INCX)
# define idamax_(N, X, INCX) \
  cblas_idamax(*N, X, *INCX)

#endif // HAVE_APPLE

#ifdef min
# undef min
#endif // min

#ifdef max
# undef max
#endif // max

#ifdef WIN32
# if _MSC_VER < 1600
#  define min _cpp_min
#  define max _cpp_max
# endif
#endif

#endif // COPASI_blaswrap
