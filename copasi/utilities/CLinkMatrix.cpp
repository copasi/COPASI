// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

#include <cmath>

#include "copasi/copasi.h"

#include "CLinkMatrix.h"

#include "copasi/core/CDataVector.h"

#include "copasi/lapack/blaswrap.h"
#include "copasi/lapack/lapackwrap.h"

// Define to output debugging information
// #define DEBUG_MATRIX

CLinkMatrix::CLinkMatrix():
  CMatrix< C_FLOAT64 >(),
  mRowPivots(),
  mPivotInverse(),
  mSwapVector(),
  mIndependent(0)
{}

CLinkMatrix::CLinkMatrix(const CLinkMatrix & src):
  CMatrix< C_FLOAT64 >(src),
  mRowPivots(src.mRowPivots),
  mPivotInverse(src.mPivotInverse),
  mSwapVector(src.mSwapVector),
  mIndependent(src.mIndependent)
{}

CLinkMatrix::~CLinkMatrix()
{}

const CVector< size_t > & CLinkMatrix::getRowPivots() const
{
  return mRowPivots;
}

bool CLinkMatrix::build(const CMatrix< C_FLOAT64 > & matrix, size_t maxRank)
{
  bool success = true;

  CMatrix< C_FLOAT64 > M(matrix);

  C_INT NumCols = (C_INT) M.numCols();
  C_INT NumRows = (C_INT) M.numRows();
  C_INT LDA = std::max<C_INT>(1, NumCols);

  CVector< C_INT > JPVT(NumRows);
  JPVT = 0;

  C_INT32 Dim = std::min(NumCols, NumRows);

  if (Dim == 0)
    {
      resize(NumRows, 0);

      mIndependent = 0;

      C_INT32 i;
      mRowPivots.resize(NumRows);

      for (i = 0; i < NumRows; i++)
        mRowPivots[i] = i;
    }
  else if (maxRank == 0)
    {
      C_INT32 i;
      mRowPivots.resize(NumRows);

      for (i = 0; i < NumRows; i++)
        mRowPivots[i] = i;

      mIndependent = 0;

      // Resize mL
      resize(NumRows - mIndependent, mIndependent);
    }
  else
    {
      CVector< C_FLOAT64 > TAU(Dim);

      CVector< C_FLOAT64 > WORK(1);
      C_INT LWORK = -1;
      C_INT INFO = 0;

      // QR factorization of the stoichiometry matrix
      /*
       *  -- LAPACK routine (version 3.0) --
       *     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
       *     Courant Institute, Argonne National Lab, and Rice University
       *     June 30, 1999
       *
       *  Purpose
       *  =======
       *
       *  DGEQP3 computes a QR factorization with column pivoting of a
       *  matrix A:  A*P = Q*R  using Level 3 BLAS.
       *
       *  Arguments
       *  =========
       *
       *  M       (input) INTEGER
       *          The number of rows of the matrix A. M >= 0.
       *
       *  N       (input) INTEGER
       *          The number of columns of the matrix A.  N >= 0.
       *
       *  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
       *          On entry, the M-by-N matrix A.
       *          On exit, the upper triangle of the array contains the
       *          min(M,N)-by-N upper trapezoidal matrix R; the elements below
       *          the diagonal, together with the array TAU, represent the
       *          orthogonal matrix Q as a product of min(M,N) elementary
       *          reflectors.
       *
       *  LDA     (input) INTEGER
       *          The leading dimension of the array A. LDA >= max(1,M).
       *
       *  JPVT    (input/output) INTEGER array, dimension (N)
       *          On entry, if JPVT(J).ne.0, the J-th column of A is permuted
       *          to the front of A*P (a leading column); if JPVT(J)=0,
       *          the J-th column of A is a free column.
       *          On exit, if JPVT(J)=K, then the J-th column of A*P was the
       *          the K-th column of A.
       *
       *  TAU     (output) DOUBLE PRECISION array, dimension (min(M,N))
       *          The scalar factors of the elementary reflectors.
       *
       *  WORK    (workspace/output) DOUBLE PRECISION array, dimension (LWORK)
       *          On exit, if INFO=0, WORK(1) returns the optimal LWORK.
       *
       *  LWORK   (input) INTEGER
       *          The dimension of the array WORK. LWORK >= 3*N+1.
       *          For optimal performance LWORK >= 2*N+(N+1)*NB, where NB
       *          is the optimal blocksize.
       *
       *          If LWORK = -1, then a workspace query is assumed; the routine
       *          only calculates the optimal size of the WORK array, returns
       *          this value as the first entry of the WORK array, and no error
       *          message related to LWORK is issued by XERBLA.
       *
       *  INFO    (output) INTEGER
       *          = 0: successful exit.
       *          < 0: if INFO = -i, the i-th argument had an illegal value.
       *
       *  Further Details
       *  ===============
       *
       *  The matrix Q is represented as a product of elementary reflectors
       *
       *     Q = H(1) H(2) . . . H(k), where k = min(m,n).
       *
       *  Each H(i) has the form
       *
       *     H(i) = I - tau * v * v'
       *
       *  where tau is a real/complex scalar, and v is a real/complex vector
       *  with v(1:i-1) = 0 and v(i) = 1; v(i+1:m) is stored on exit in
       *  A(i+1:m,i), and tau in TAU(i).
       *
       *  Based on contributions by
       *    G. Quintana-Orti, Depto. de Informatica, Universidad Jaime I, Spain
       *    X. Sun, Computer Science Dept., Duke University, USA
       *
       */

      dgeqp3_(&NumCols, &NumRows, M.array(), &LDA,
              JPVT.array(), TAU.array(), WORK.array(), &LWORK, &INFO);

      if (INFO < 0) fatalError();

      LWORK = (C_INT) WORK[0];
      WORK.resize(LWORK);

      dgeqp3_(&NumCols, &NumRows, M.array(), &LDA,
              JPVT.array(), TAU.array(), WORK.array(), &LWORK, &INFO);

      if (INFO < 0) fatalError();

      C_INT32 i;
      mRowPivots.resize(NumRows);

      for (i = 0; i < NumRows; i++)
        mRowPivots[i] = JPVT[i] - 1;

      /**
       * Determine the rank of the matrix
       * This code is copied from dgelsy.f
       */

      C_INT independent = 0;

      if (fabs(M(0, 0)) != 0.0)
        {
          ++independent;

          C_INT imax = 1;
          C_INT imin = 2;
          C_INT mn = Dim;

          C_FLOAT64 * pIsmin = WORK.array();
          C_FLOAT64 * pIsmax = pIsmin + Dim;

          *pIsmin = 1.0;
          *pIsmax = 1.0;

          C_FLOAT64 smax = fabs(M(0, 0));
          C_FLOAT64 smin = smax;
          C_FLOAT64 RCOND = std::max(NumRows, NumCols) * smax * std::numeric_limits< C_FLOAT64 >::epsilon();

          C_FLOAT64 sminpr, s1, c1, smaxpr, s2, c2;

          while (independent < mn && (size_t) independent < maxRank)
            {
              dlaic1_(&imin, &independent, pIsmin, &smin, &M(independent, 0), &M(independent, independent), &sminpr, &s1, &c1);
              dlaic1_(&imax, &independent, pIsmax, &smax, &M(independent, 0), &M(independent, independent), &smaxpr, &s2, &c2);

              if (smaxpr * RCOND > sminpr)
                {
                  break;
                }

              for (C_INT i = 0; i < independent - 1; ++i)
                {
                  *(pIsmin + i) *= s1;
                  *(pIsmax + i) *= s2;
                }

              *(pIsmin + independent) = c1;
              *(pIsmax + independent) = c2;

              smin = sminpr;
              smax = smaxpr;

              ++independent;
            }
        }

      mIndependent = independent;

      // Resize mL
      resize(NumRows - independent, independent);

      if (NumRows != independent && independent != 0)
        {
          /* to take care of differences between fortran's and c's memory  access,
               we need to take the transpose, i.e.,the upper triangular */
          char cL = 'U';
          char cU = 'N'; /* values in the diagonal of R */

          // Calculate Row Echelon form of R.
          // First invert R_1,1
          /* int dtrtri_(char *uplo,
           *             char *diag,
           *             integer *n,
           *             doublereal * A,
           *             integer *lda,
           *             integer *info);
           *  -- LAPACK routine (version 3.0) --
           *     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
           *     Courant Institute, Argonne National Lab, and Rice University
           *     March 31, 1993
           *
           *  Purpose
           *  =======
           *
           *  DTRTRI computes the inverse of a real upper or lower triangular
           *  matrix A.
           *
           *  This is the Level 3 BLAS version of the algorithm.
           *
           *  Arguments
           *  =========
           *
           *  uplo    (input) CHARACTER*1
           *          = 'U':  A is upper triangular;
           *          = 'L':  A is lower triangular.
           *
           *  diag    (input) CHARACTER*1
           *          = 'N':  A is non-unit triangular;
           *          = 'U':  A is unit triangular.
           *
           *  n       (input) INTEGER
           *          The order of the matrix A.  n >= 0.
           *
           *  A       (input/output) DOUBLE PRECISION array, dimension (lda,n)
           *          On entry, the triangular matrix A.  If uplo = 'U', the
           *          leading n-by-n upper triangular part of the array A contains
           *          the upper triangular matrix, and the strictly lower
           *          triangular part of A is not referenced.  If uplo = 'L', the
           *          leading n-by-n lower triangular part of the array A contains
           *          the lower triangular matrix, and the strictly upper
           *          triangular part of A is not referenced.  If diag = 'U', the
           *          diagonal elements of A are also not referenced and are
           *          assumed to be 1.
           *          On exit, the (triangular) inverse of the original matrix, in
           *          the same storage format.
           *
           *  lda     (input) INTEGER
           *          The leading dimension of the array A.  lda >= max(1,n).
           *
           *  info    (output) INTEGER
           *          = 0: successful exit
           *          < 0: if info = -i, the i-th argument had an illegal value
           *          > 0: if info = i, A(i,i) is exactly zero.  The triangular
           *               matrix is singular and its inverse can not be computed.
           */
          dtrtri_(&cL, &cU, &independent, M.array(), &LDA, &INFO);

          if (INFO < 0) fatalError();

          C_INT32 j, k;

          // Compute Link_0 = inverse(R_1,1) * R_1,2
          // :TODO: Use dgemm
          C_FLOAT64 * pTmp1 = array();
          C_FLOAT64 * pTmp2;
          C_FLOAT64 * pTmp3;

          for (j = 0; j < NumRows - independent; j++)
            for (i = 0; i < independent; i++, pTmp1++)
              {
                pTmp2 = &M(j + independent, i);
                pTmp3 = &M(i, i);

                // assert(&mL(j, i) == pTmp3);
                *pTmp1 = 0.0;

                for (k = i; k < independent; k++, pTmp2++, pTmp3 += NumCols)
                  {
                    // assert(&M(j + independent, k) == pTmp2);
                    // assert(&M(k, i) == pTmp3);

                    *pTmp1 += *pTmp3 **pTmp2;
                  }

                if (fabs(*pTmp1) < 100.0 * std::numeric_limits< C_FLOAT64 >::epsilon()) *pTmp1 = 0.0;
              }
        }
    }

  completePivotInformation();

  return success;
}

void CLinkMatrix::completePivotInformation()
{
  // We need to convert the pivot vector into a swap vector.
  mPivotInverse.resize(mRowPivots.size());

  size_t * pCurrentIndex = mPivotInverse.array();
  size_t * pEnd  = pCurrentIndex + mRowPivots.size();

  for (size_t i = 0; pCurrentIndex != pEnd; ++pCurrentIndex, ++i)
    {
      *pCurrentIndex = i;
    }

  CVector< size_t > CurrentColumn(mPivotInverse);
  size_t * pCurrentColumn = CurrentColumn.array();

  mSwapVector.resize(mRowPivots.size());
  C_INT * pJPVT = mSwapVector.array();
  pCurrentIndex = mPivotInverse.array();
  const size_t * pPivot = mRowPivots.array();

  for (; pCurrentIndex != pEnd; ++pPivot, ++pJPVT, ++pCurrentIndex, ++pCurrentColumn)
    {
      // Swap Index
      size_t * pToIndex = & mPivotInverse[*pPivot];
      size_t * pFromIndex = & mPivotInverse[*pCurrentColumn];

      // Swap Column
      size_t * pToColumn = & CurrentColumn[*pToIndex];
      size_t * pFromColumn = pCurrentColumn;

      // Swap
      *pJPVT =  *pToIndex + 1;

      size_t tmp = *pFromIndex;
      *pFromIndex = *pToIndex;
      *pToIndex = tmp;

      tmp = *pFromColumn;
      *pFromColumn = *pToColumn;
      *pToColumn = tmp;
    }
}

void CLinkMatrix::clearPivoting()
{
  size_t * pPivot = mRowPivots.array();
  size_t * pPivotEnd = pPivot + mRowPivots.size();
  size_t Index = 0;

  for (; pPivot != pPivotEnd; ++pPivot, ++Index)
    {
      *pPivot = Index;
    }

  completePivotInformation();
}

bool CLinkMatrix::rightMultiply(const C_FLOAT64 & alpha,
                                const CMatrix< C_FLOAT64> & m,
                                CMatrix< C_FLOAT64> & p) const
{
  bool success = true;

  if (m.numCols() != mRowPivots.size())
    {
      return false;
    }

  // p := alpha * (m1, m2) * (I, L0')' = alpha * m1 + alpha * m2 * L0

  p.resize(m.numRows(), getNumIndependent());

  char T = 'N';
  C_INT M = (C_INT) p.numCols();
  C_INT N = (C_INT) p.numRows();
  C_INT K = (C_INT) numRows();

  C_INT LDA = (C_INT) std::max< size_t >(1, numCols());
  C_INT LDB = (C_INT) std::max< size_t >(1, m.numCols());
  C_INT LDC = (C_INT) std::max< size_t >(1, p.numCols());

  // p := m1

  C_FLOAT64 *pRowP = p.array();
  const C_FLOAT64 *pRowM = m.array();
  C_FLOAT64 *pEnd = p.array() + p.size();

  for (; pRowP < pEnd; pRowP += LDC, pRowM += LDB)
    {
      memcpy(pRowP, pRowM, sizeof(C_FLOAT64) * LDC);
    }

  // DGEMM (TRANSA, TRANSB, M, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC)
  // C := alpha A B + beta C

  dgemm_(&T, &T, &M, &N, &K,
         const_cast< C_FLOAT64 * >(&alpha),
         const_cast< C_FLOAT64 * >(array()), &LDA,
         const_cast< C_FLOAT64 * >(m.array()) + LDA, &LDB,
         const_cast< C_FLOAT64 * >(&alpha), p.array(), &LDC);

  return success;
}

bool CLinkMatrix::leftMultiply(const CMatrix< C_FLOAT64> & m,
                               CMatrix< C_FLOAT64> & p) const
{
  bool success = true;

  if (m.numRows() != numCols())
    {
      return false;
    }

  // p := L * m = (I, L0) * m = (m, L0 * m) = (p1, p2)
  p.resize(mRowPivots.size(), m.numCols());
  p = 0.0;

  // p1 := m
  memcpy(p.array(), m.array(), sizeof(C_FLOAT64) * m.size());

  // p2 := L0 * m
  // p2 (numDependent x m.numCols())
  char T = 'N';
  C_INT M = (C_INT) m.numCols(); /* LDA, LDC */
  C_INT N = (C_INT) getNumDependent();
  C_INT K = (C_INT) numCols();

  C_INT LDA = (C_INT) std::max< size_t >(1, m.numCols());
  C_INT LDB = (C_INT) std::max< size_t >(1, numCols());
  C_INT LDC = (C_INT) std::max< size_t >(1, p.numCols());

  C_FLOAT64 Alpha = 1.0;
  C_FLOAT64 Zero = 0.0;

  // DGEMM (TRANSA, TRANSB, M, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC)
  // C := alpha A B + beta C
  dgemm_(&T, &T, &M, &N, &K, &Alpha,
         const_cast< C_FLOAT64 * >(m.array()), &LDA,
         const_cast< C_FLOAT64 * >(array()), &LDB,
         &Zero, p.array() + m.size(), &LDC);

  return success;
}

const size_t & CLinkMatrix::getNumIndependent() const
{
  return mIndependent;
}

size_t CLinkMatrix::getNumDependent() const
{
  return numRows();
}

bool CLinkMatrix::doRowPivot(CMatrix< C_FLOAT64 > & matrix) const
{
  return applyRowPivot(matrix, mRowPivots);
}

bool CLinkMatrix::undoRowPivot(CMatrix< C_FLOAT64 > & matrix) const
{
  return applyRowPivot(matrix, mPivotInverse);
}

bool CLinkMatrix::applyRowPivot(CMatrix< C_FLOAT64 > & matrix,
                                const CVector< size_t > & pivots) const
{
  if (matrix.numRows() < pivots.size())
    {
      return false;
    }

  CVector< bool > Applied(pivots.size());
  Applied = false;

  CVector< C_FLOAT64 > Tmp(matrix.numCols());

  size_t i, imax = pivots.size();
  size_t to;
  size_t from;
  size_t numCols = matrix.numCols();

  for (i = 0; i < imax; i++)
    if (!Applied[i])
      {
        to = i;
        from = pivots[to];

        if (from != i)
          {
            memcpy(Tmp.array(), matrix[to], sizeof(C_FLOAT64) * numCols);

            while (from != i)
              {
                memcpy(matrix[to], matrix[from], sizeof(C_FLOAT64) * numCols);
                Applied[to] = true;

                to = from;
                from = pivots[to];
              }

            memcpy(matrix[to], Tmp.array(), sizeof(C_FLOAT64) * numCols);
          }

        Applied[to] = true;
      }

  return true;
}

bool CLinkMatrix::doColumnPivot(CMatrix< C_FLOAT64 > & matrix) const
{
  return applyColumnPivot(matrix, 1);
}

bool CLinkMatrix::undoColumnPivot(CMatrix< C_FLOAT64 > & matrix) const
{
  return applyColumnPivot(matrix, -1);
}

bool CLinkMatrix::applyColumnPivot(CMatrix< C_FLOAT64 > & matrix,
                                   const C_INT & incr) const
{
  if (matrix.numCols() < mRowPivots.size())
    {
      return false;
    }

  C_INT N = matrix.numRows();
  C_INT LDA = matrix.numCols();
  C_INT K1 = 1;
  C_INT K2 = mRowPivots.size();

  dlaswp_(&N, matrix.array(), &LDA, &K1, &K2,
          const_cast< C_INT * >(mSwapVector.array()),
          const_cast< C_INT * >(&incr));

  return true;
}

//**********************************************************************
//                   CLinkMatrixView
//**********************************************************************

const C_FLOAT64 CLinkMatrixView::mZero = 0.0;
const C_FLOAT64 CLinkMatrixView::mUnit = 1.0;

CLinkMatrixView::CLinkMatrixView(const CLinkMatrix & A):
  mpA(&A),
  mpNumIndependent(&A.getNumIndependent())
{CONSTRUCTOR_TRACE;}

CLinkMatrixView::~CLinkMatrixView()
{DESTRUCTOR_TRACE;}

CLinkMatrixView &
CLinkMatrixView::operator = (const CLinkMatrixView & rhs)
{
  if (this == &rhs)
    return *this;

  mpA = rhs.mpA;
  mpNumIndependent = rhs.mpNumIndependent;

  return *this;
}

size_t CLinkMatrixView::numRows() const
{
  return *mpNumIndependent + mpA->numRows();
}

size_t CLinkMatrixView::numCols() const
{
  return mpA->numCols();
}

std::ostream &operator<<(std::ostream &os,
                         const CLinkMatrixView & A)
{
  size_t i, imax = A.numRows();
  size_t j, jmax = A.numCols();
  os << "Matrix(" << imax << "x" << jmax << ")" << std::endl;

  for (i = 0; i < imax; i++)
    {
      for (j = 0; j < jmax; j++)
        os << "\t" << A(i, j);

      os << std::endl;
    }

  return os;
}
