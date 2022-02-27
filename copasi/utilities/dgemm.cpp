// Copyright (C) 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/utilities/dgemm.h"

#include "copasi/lapack/lapackwrap.h"
#include "copasi/lapack/blaswrap.h"

// static
bool dgemm::eval(const C_FLOAT64 & alpha, const dgemm::Matrix & A, const dgemm::Matrix & B, const C_FLOAT64 & beta, dgemm::Matrix & C)
{
  if (A.numCols() != B.numRows())
    return false;

  if (beta == 0.0)
    C.resize(A.numRows(), B.numCols());
  else if (A.numRows() != C.numRows() || B.numCols() != C.numCols())
    return false;

  //  DGEMM
  //
  //  =========== DOCUMENTATION ===========
  //
  //  Online html documentation available at
  //            http://www.netlib.org/lapack/explore-html/
  //
  //  Definition:
  //  ===========
  //
  //       SUBROUTINE DGEMM(TRANSA,TRANSB,M,N,K,ALPHA,A,LDA,B,LDB,BETA,C,LDC)
  //
  //       .. Scalar Arguments ..
  //       DOUBLE PRECISION ALPHA,BETA
  //       INTEGER K,LDA,LDB,LDC,M,N
  //       CHARACTER TRANSA,TRANSB
  //       ..
  //       .. Array Arguments ..
  //       DOUBLE PRECISION A(LDA,*),B(LDB,*),C(LDC,*)
  //       ..
  //
  //  Purpose:
  //  ========
  //
  //  DGEMM  performs one of the matrix-matrix operations
  //
  //    C := alpha*op(A )*op(B ) + beta*C,
  //
  //  where  op(X ) is one of
  //
  //    op(X ) = X   or   op(X ) = X**T,
  //
  //  alpha and beta are scalars, and A, B and C are matrices, with op(A)
  //  an m by k matrix,  op(B )  a  k by n matrix and  C an m by n matrix.
  //
  //  Arguments:
  //  ==========
  //
  //  TRANSA   TRANSA is CHARACTER*1
  //           On entry, TRANSA specifies the form of op(A ) to be used in
  //           the matrix multiplication as follows:
  //
  //              TRANSA = 'N' or 'n',  op(A ) = A.
  //
  //              TRANSA = 'T' or 't',  op(A ) = A**T.
  //
  //              TRANSA = 'C' or 'c',  op(A ) = A**T.
  //
  //  TRANSB   TRANSB is CHARACTER*1
  //           On entry, TRANSB specifies the form of op(B ) to be used in
  //           the matrix multiplication as follows:
  //
  //              TRANSB = 'N' or 'n',  op(B ) = B.
  //
  //              TRANSB = 'T' or 't',  op(B ) = B**T.
  //
  //              TRANSB = 'C' or 'c',  op(B ) = B**T.
  //
  //  M        M is INTEGER
  //           On entry,  M  specifies  the number  of rows  of the  matrix
  //           op(A )  and of the  matrix  C.  M  must  be at least  zero.
  //
  //  N        N is INTEGER
  //           On entry,  N  specifies the number  of columns of the matrix
  //           op(B ) and the number of columns of the matrix C. N must be
  //           at least zero.
  //
  //  K        K is INTEGER
  //           On entry,  K  specifies  the number of columns of the matrix
  //           op(A ) and the number of rows of the matrix op(B ). K must
  //           be at least  zero.
  //
  //  ALPHA    ALPHA is DOUBLE PRECISION.
  //           On entry, ALPHA specifies the scalar alpha.
  //
  //  A        A is DOUBLE PRECISION array, dimension (LDA, ka ), where ka is
  //           k  when  TRANSA = 'N' or 'n',  and is  m  otherwise.
  //           Before entry with  TRANSA = 'N' or 'n',  the leading  m by k
  //           part of the array  A  must contain the matrix  A,  otherwise
  //           the leading  k by m  part of the array  A  must contain  the
  //           matrix A.
  //
  //  LDA      LDA is INTEGER
  //           On entry, LDA specifies the first dimension of A as declared
  //           in the calling (sub) program. When  TRANSA = 'N' or 'n' then
  //           LDA must be at least  max(1, m ), otherwise  LDA must be at
  //           least  max(1, k ).
  //
  //  B        B is DOUBLE PRECISION array, dimension (LDB, kb ), where kb is
  //           n  when  TRANSB = 'N' or 'n',  and is  k  otherwise.
  //           Before entry with  TRANSB = 'N' or 'n',  the leading  k by n
  //           part of the array  B  must contain the matrix  B,  otherwise
  //           the leading  n by k  part of the array  B  must contain  the
  //           matrix B.
  //
  //  LDB      LDB is INTEGER
  //           On entry, LDB specifies the first dimension of B as declared
  //           in the calling (sub) program. When  TRANSB = 'N' or 'n' then
  //           LDB must be at least  max(1, k ), otherwise  LDB must be at
  //           least  max(1, n ).
  //
  //  BETA     BETA is DOUBLE PRECISION.
  //           On entry,  BETA  specifies the scalar  beta.  When  BETA  is
  //           supplied as zero then C need not be set on input.
  //
  //  C        C is DOUBLE PRECISION array, dimension (LDC, N)
  //           Before entry, the leading  m by n  part of the array  C must
  //           contain the matrix  C,  except when  beta  is zero, in which
  //           case C need not be set on entry.
  //           On exit, the array  C  is overwritten by the  m by n  matrix
  //           (alpha*op(A )*op(B ) + beta*C ).
  //
  //  LDC      LDC is INTEGER
  //           On entry, LDC specifies the first dimension of C as declared
  //           in  the  calling  (sub)  program.   LDC  must  be  at  least
  //           max(1, m ).
  //
  //  Authors:
  //  ========
  //
  //  Univ. of Tennessee
  //  Univ. of California Berkeley
  //  Univ. of Colorado Denver
  //  NAG Ltd.
  //
  //  double_blas_level3
  //
  //  Further Details:
  //  =====================
  //
  //
  //  Level 3 Blas routine.
  //
  //  -- Written on 8-February-1989.
  //     Jack Dongarra, Argonne National Laboratory.
  //     Iain Duff, AERE Harwell.
  //     Jeremy Du Croz, Numerical Algorithms Group Ltd.
  //     Sven Hammarling, Numerical Algorithms Group Ltd.
  //
  //  =====================================================================

  // Note: dgemm uses Fortran style matrices, i.e., column and rows are reversed
  //   (A * B)^T = B^T * A^T

  char TRANS = 'N';
  C_INT M = (C_INT) B.numCols();
  C_INT N = (C_INT) A.numRows();
  C_INT K = (C_INT) A.numCols();
  C_INT LDA = std::max< C_INT >(1, M);
  C_INT LDB = std::max< C_INT >(1, K);
  C_INT LDC = std::max< C_INT >(1, M);

  dgemm_(&TRANS, &TRANS, &M, &N, &K,
         const_cast< C_FLOAT64 * >(&alpha),
         const_cast< C_FLOAT64 * >(B.array()), &LDA,
         const_cast< C_FLOAT64 * >(A.array()), &LDB,
         const_cast< C_FLOAT64 * >(&beta), C.array(), &LDC);

  return true;
}

// static
bool dgemm::eval(const C_FLOAT64 & alpha, const dgemm::Matrix & A, const dgemm::Vector & B, const C_FLOAT64 & beta, dgemm::Vector & C)
{
  if (A.numCols() != B.size())
    return false;

  if (beta == 0.0
      && dynamic_cast< CVector< C_FLOAT64 > * >(&C) != NULL)
    static_cast< CVector< C_FLOAT64 > * >(&C)->resize(A.numRows());
  else if (A.numRows() != C.size())
    return false;

  char TRANS = 'N';
  C_INT M = 1;
  C_INT N = (C_INT) A.numRows();
  C_INT K = (C_INT) A.numCols();
  C_INT LDA = std::max< C_INT >(1, M);
  C_INT LDB = std::max< C_INT >(1, K);
  C_INT LDC = std::max< C_INT >(1, M);

  dgemm_(&TRANS, &TRANS, &M, &N, &K,
         const_cast< C_FLOAT64 * >(&alpha),
         const_cast< C_FLOAT64 * >(B.array()), &LDA,
         const_cast< C_FLOAT64 * >(A.array()), &LDB,
         const_cast< C_FLOAT64 * >(&beta), C.array(), &LDC);

  return true;
}

// static
bool dgemm::eval(const C_FLOAT64 & alpha, const dgemm::Vector & A, const dgemm::Matrix & B, const C_FLOAT64 & beta, dgemm::Vector & C)
{
  if (A.size() != B.numRows())
    return false;

  if (beta == 0.0
      && dynamic_cast< CVector< C_FLOAT64 > * >(&C) != NULL)
    static_cast< CVector< C_FLOAT64 > * >(&C)->resize(B.numCols());
  else if (B.numCols() != C.size())
    return false;

  char TRANS = 'N';
  C_INT M = (C_INT) B.numCols();
  C_INT N = 1;
  C_INT K = (C_INT) A.size();
  C_INT LDA = std::max< C_INT >(1, M);
  C_INT LDB = std::max< C_INT >(1, K);
  C_INT LDC = std::max< C_INT >(1, M);

  dgemm_(&TRANS, &TRANS, &M, &N, &K,
         const_cast< C_FLOAT64 * >(&alpha),
         const_cast< C_FLOAT64 * >(B.array()), &LDA,
         const_cast< C_FLOAT64 * >(A.array()), &LDB,
         const_cast< C_FLOAT64 * >(&beta), C.array(), &LDC);

  return true;
}

// static
bool dgemm::eval(const C_FLOAT64 & alpha, const dgemm::Vector & A, const dgemm::Vector & B, const C_FLOAT64 & beta, C_FLOAT64 & C)
{
  if (A.size() != B.size())
    return false;

  char TRANS = 'N';
  C_INT M = 1;
  C_INT N = 1;
  C_INT K = (C_INT) A.size();
  C_INT LDA = std::max< C_INT >(1, M);
  C_INT LDB = std::max< C_INT >(1, K);
  C_INT LDC = std::max< C_INT >(1, M);

  dgemm_(&TRANS, &TRANS, &M, &N, &K,
         const_cast< C_FLOAT64 * >(&alpha),
         const_cast< C_FLOAT64 * >(B.array()), &LDA,
         const_cast< C_FLOAT64 * >(A.array()), &LDB,
         const_cast< C_FLOAT64 * >(&beta), &C, &LDC);

  return true;
}
