// Copyright (C) 2020 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include <cmath>
#include "copasi/utilities/CLeastSquareSolution.h"

#include "copasi/lapack/lapackwrap.h"
#include "copasi/lapack/blaswrap.h"
#include "copasi/utilities/dgemm.h"

// static
size_t CLeastSquareSolution::solve(const CMatrix< C_FLOAT64 > & aMatrix,
                                   const CVectorCore< C_FLOAT64 > & bVector,
                                   CVector< C_FLOAT64 > & xVector)
{
  xVector.resize(aMatrix.numCols());
  xVector = std::numeric_limits< C_FLOAT64 >::quiet_NaN();

  if (bVector.size() != aMatrix.numRows())
    return 0;

  /*
      SUBROUTINE DGELSY(M, N, NRHS, A, LDA, B, LDB, JPVT, RCOND, RANK,
     $                   WORK, LWORK, INFO)
   *
   *  -- LAPACK driver routine (version 3.2) --
   *  -- LAPACK is a software package provided by Univ. of Tennessee,    --
   *  -- Univ. of California Berkeley, Univ. of Colorado Denver and NAG Ltd..--
   *     November 2006
   *
   *     .. Scalar Arguments ..
      INTEGER            INFO, LDA, LDB, LWORK, M, N, NRHS, RANK
      DOUBLE PRECISION   RCOND
   *     ..
   *     .. Array Arguments ..
      INTEGER            JPVT(*)
      DOUBLE PRECISION   A(LDA, * ), B(LDB, * ), WORK(*)
   *     ..
   *
   *  Purpose
   *  =======
   *
   *  DGELSY computes the minimum-norm solution to a real linear least
   *  squares problem:
   *      minimize || A * X - B ||
   *  using a complete orthogonal factorization of A.  A is an M-by-N
   *  matrix which may be rank-deficient.
   *
   *  Several right hand side vectors b and solution vectors x can be
   *  handled in a single call; they are stored as the columns of the
   *  M-by-NRHS right hand side matrix B and the N-by-NRHS solution
   *  matrix X.
   *
   *  The routine first computes a QR factorization with column pivoting:
   *      A * P = Q * [ R11 R12 ]
   *                  [  0  R22 ]
   *  with R11 defined as the largest leading submatrix whose estimated
   *  condition number is less than 1/RCOND.  The order of R11, RANK,
   *  is the effective rank of A.
   *
   *  Then, R22 is considered to be negligible, and R12 is annihilated
   *  by orthogonal transformations from the right, arriving at the
   *  complete orthogonal factorization:
   *     A * P = Q * [ T11 0 ] * Z
   *                 [  0  0 ]
   *  The minimum-norm solution is then
   *     X = P * Z' [ inv(T11)*Q1'*B ]
   *                [        0       ]
   *  where Q1 consists of the first RANK columns of Q.
   *
   *  This routine is basically identical to the original xGELSX except
   *  three differences:
   *    o The call to the subroutine xGEQPF has been substituted by the
   *      the call to the subroutine xGEQP3. This subroutine is a Blas-3
   *      version of the QR factorization with column pivoting.
   *    o Matrix B (the right hand side) is updated with Blas-3.
   *    o The permutation of matrix B (the right hand side) is faster and
   *      more simple.
   *
   *  Arguments
   *  =========
   *
   *  M       (input) INTEGER
   *          The number of rows of the matrix A.  M >= 0.
   *
   *  N       (input) INTEGER
   *          The number of columns of the matrix A.  N >= 0.
   *
   *  NRHS    (input) INTEGER
   *          The number of right hand sides, i.e., the number of
   *          columns of matrices B and X. NRHS >= 0.
   *
   *  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
   *          On entry, the M-by-N matrix A.
   *          On exit, A has been overwritten by details of its
   *          complete orthogonal factorization.
   *
   *  LDA     (input) INTEGER
   *          The leading dimension of the array A.  LDA >= max(1,M).
   *
   *  B       (input/output) DOUBLE PRECISION array, dimension (LDB,NRHS)
   *          On entry, the M-by-NRHS right hand side matrix B.
   *          On exit, the N-by-NRHS solution matrix X.
   *
   *  LDB     (input) INTEGER
   *          The leading dimension of the array B. LDB >= max(1,M,N).
   *
   *  JPVT    (input/output) INTEGER array, dimension (N)
   *          On entry, if JPVT(i) .ne. 0, the i-th column of A is permuted
   *          to the front of AP, otherwise column i is a free column.
   *          On exit, if JPVT(i) = k, then the i-th column of AP
   *          was the k-th column of A.
   *
   *  RCOND   (input) DOUBLE PRECISION
   *          RCOND is used to determine the effective rank of A, which
   *          is defined as the order of the largest leading triangular
   *          submatrix R11 in the QR factorization with pivoting of A,
   *          whose estimated condition number < 1/RCOND.
   *
   *  RANK    (output) INTEGER
   *          The effective rank of A, i.e., the order of the submatrix
   *          R11.  This is the same as the order of the submatrix T11
   *          in the complete orthogonal factorization of A.
   *
   *  WORK    (workspace/output) DOUBLE PRECISION array, dimension (MAX(1,LWORK))
   *          On exit, if INFO = 0, WORK(1) returns the optimal LWORK.
   *
   *  LWORK   (input) INTEGER
   *          The dimension of the array WORK.
   *          The unblocked strategy requires that:
   *             LWORK >= MAX(MN+3*N+1, 2*MN+NRHS ),
   *          where MN = min(M, N ).
   *          The block algorithm requires that:
   *             LWORK >= MAX(MN+2*N+N*(N+1), 2*MN+NB*NRHS ),
   *          where NB is an upper bound on the blocksize returned
   *          by ILAENV for the routines DGEQP3, DTZRZF, STZRQF, DORMQR,
   *          and DORMRZ.
   *
   *          If LWORK = -1, then a workspace query is assumed; the routine
   *          only calculates the optimal size of the WORK array, returns
   *          this value as the first entry of the WORK array, and no error
   *          message related to LWORK is issued by XERBLA.
   *
   *  INFO    (output) INTEGER
   *          = 0: successful exit
   *          < 0: If INFO = -i, the i-th argument had an illegal value.
   *
   *  Further Details
   *  ===============
   *
   *  Based on contributions by
   *    A. Petitet, Computer Science Dept., Univ. of Tenn., Knoxville, USA
   *    E. Quintana-Orti, Depto. de Informatica, Universidad Jaime I, Spain
   *    G. Quintana-Orti, Depto. de Informatica, Universidad Jaime I, Spain
   *
   *  =====================================================================
   */

  C_INT M = (C_INT) aMatrix.numRows();
  C_INT N = (C_INT) aMatrix.numCols();
  C_INT NRHS = 1;
  C_INT LDA = std::max< C_INT >(1, M);
  C_INT LDB = std::max(LDA, N);
  CVector< C_INT > JPVT(LDB);
  JPVT = 0;
  C_FLOAT64 RCOND = 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon();
  C_INT RANK = 0;
  CVector< C_FLOAT64 > WORK(1);
  C_INT LWORK = -1;
  C_INT INFO;

  // We need the transpose of the aMatrix;
  CMatrix< C_FLOAT64 > AT(aMatrix.numCols(), aMatrix.numRows());
  const C_FLOAT64 * mpJ = aMatrix.array();
  C_FLOAT64 * mpJTcolumn = AT.array();
  C_FLOAT64 * mpJTcolumnEnd = mpJTcolumn + AT.numCols();
  C_FLOAT64 * mpJT = AT.array();
  C_FLOAT64 * mpJTEnd = mpJT + AT.size();

  for (; mpJTcolumn != mpJTcolumnEnd; ++mpJTcolumn)
    {
      mpJT = mpJTcolumn;

      for (; mpJT < mpJTEnd; mpJT += AT.numCols(), ++mpJ)
        {
          if (std::isnan(*mpJ))
            return 0;

          *mpJT = *mpJ;
        }
    }

  CVector< C_FLOAT64 > B(LDB);
  B = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  memcpy(B.begin(), bVector.begin(), bVector.size() * sizeof(C_FLOAT64));

  dgelsy_(&M, &N, &NRHS, AT.array(), &LDA, B.array(), &LDB, JPVT.array(), &RCOND, &RANK,
          WORK.array(), &LWORK, &INFO);

  if (INFO < 0)
    return 0;

  LWORK = (C_INT) WORK[0];
  WORK.resize(LWORK);

  dgelsy_(&M, &N, &NRHS, AT.array(), &LDA, B.array(), &LDB, JPVT.array(), &RCOND, &RANK,
          WORK.array(), &LWORK, &INFO);

  if (INFO < 0)
    return 0;

  memcpy(xVector.begin(), B.begin(), xVector.size() * sizeof(C_FLOAT64));

  return RANK;
}

// static
CLeastSquareSolution::ResultInfo CLeastSquareSolution::solve(const CMatrix< C_FLOAT64 > & aMatrix,
    const CVectorCore< C_FLOAT64 > & bVector,
    const CVectorCore< C_FLOAT64 > & absoluteTolerances,
    const CVector< C_FLOAT64 * > & compartmentVolumes,
    const C_FLOAT64 & quantity2NumberFactor,
    CVector< C_FLOAT64 > & xVector)
{
  ResultInfo Info;

  Info.rank = solve(aMatrix, bVector, xVector);

  if (Info.rank == 0)
    {
      Info.relativeError = std::numeric_limits< C_FLOAT64 >::infinity();
      Info.absoluteError = std::numeric_limits< C_FLOAT64 >::infinity();

      return Info;
    }

  Info.absoluteError = 0.0; // Largest relative distance
  Info.relativeError = 0.0; // Total relative distance

  // We need to check whether the || Ax - bVector || is sufficiently small.
  // Calculate Ax
  CVector< C_FLOAT64 > Ax;
  dgemm::eval(1.0, aMatrix, xVector, 0.0, Ax);

  // Calculate absolute and relative error
  C_FLOAT64 *pAx = Ax.begin();
  C_FLOAT64 *pAxEnd = Ax.end();
  const C_FLOAT64 *pB = bVector.begin();
  const C_FLOAT64 * pAtol = absoluteTolerances.begin();

  C_FLOAT64 * const * ppCompartmentVolume = compartmentVolumes.array();

  C_FLOAT64 tmp;

  for (; pAx != pAxEnd; ++pAx, ++pB, ++pAtol, ++ppCompartmentVolume)
    {
      // Prevent division by 0
      tmp = fabs(*pAx - *pB) / std::max((fabs(*pAx) + fabs(*pB)) / 2.0, *pAtol);
      Info.relativeError += tmp * tmp;

      tmp = fabs(*pAx - *pB);

      if (*ppCompartmentVolume != NULL)
        {
          tmp /= quantity2NumberFactor * **ppCompartmentVolume;
        }

      Info.absoluteError += tmp * tmp;
    }

  Info.relativeError =
    std::isnan(Info.relativeError) ? std::numeric_limits< C_FLOAT64 >::infinity() : sqrt(Info.relativeError);
  Info.absoluteError =
    std::isnan(Info.absoluteError) ? std::numeric_limits< C_FLOAT64 >::infinity() : sqrt(Info.absoluteError);

  return Info;
}
