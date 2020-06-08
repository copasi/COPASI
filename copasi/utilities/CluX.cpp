// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <algorithm>
#include <cmath>
#include <limits>

#include "copasi/copasi.h"

#include "CluX.h"

#include "copasi/core/CMatrix.h"
#include "copasi/core/CVector.h"
#include "CProcessReport.h"

#include "copasi/lapack/lapackwrap.h"

// #define DEBUG_MATRIX

bool LUfactor(CMatrix< C_FLOAT64 > & A,
              CVector< size_t > & row,
              CVector< size_t > & col,
              CProcessReport * cb)
{
  size_t Rows = A.numRows();
  size_t Cols = A.numCols();
  size_t Dim = std::min(Rows, Cols);

  if (row.size() != Rows) row.resize(Rows);

  if (col.size() != Cols) col.resize(Cols);

  size_t i = 0, j = 0, k = 0;
  size_t rowP = 0, colP = Cols - 1;

  for (i = 0; i < Rows; i++)
    row[i] = i;

  for (i = 0; i < Cols; i++)
    col[i] = i;

  C_FLOAT64 Work = .5 * Dim * (Dim - 1);
  C_FLOAT64 Completion = 0;

  size_t hProcess;

  if (cb)
    hProcess = cb->addItem("LU decomposition...",
                           Completion,
                           &Work);

  C_FLOAT64 tmp;
  C_FLOAT64 * pTmp1;
  C_FLOAT64 * pTmp2;
  C_FLOAT64 * pTmp3;

  for (i = 0; i < Dim; i++)
    {
      Completion += Dim - i;

      if (cb && !cb->progressItem(hProcess)) return false;

      // find pivot in column j and  test for singularity.
      while (true)
        {
          rowP = C_INVALID_INDEX;
          tmp = 0.0;

          for (j = i, pTmp1 = &A(i, i); j < Rows; j++, pTmp1 += Cols)
            if (fabs(*pTmp1) > tmp) // (fabs(A(j, i)) > t)
              {
                rowP = j;
                tmp = fabs(*pTmp1); // fabs(A(j, i));
              }

          // rowP now has the index of maximum element
          // of column j, below the diagonal

          if (tmp < std::numeric_limits< C_FLOAT64 >::epsilon()) // now we have to swap colums to find a pivot
            {
              // Instead of blindly swapping with the last available
              // column we first check whether it is suitable. If not
              // we proceed with the lat but one ...
              while (i < colP)
                {
                  rowP = C_INVALID_INDEX;
                  tmp = 0.0;

                  for (j = i, pTmp1 = &A(i, colP); j < Rows; j++, pTmp1 += Cols)
                    if (fabs(*pTmp1) > tmp) // (fabs(A(j, colP)) > t)
                      {
                        rowP = j;
                        tmp = fabs(*pTmp1); // fabs(A(j, colP));
                      }

                  if (tmp >= std::numeric_limits< C_FLOAT64 >::epsilon()) break; // Found a suitable column

                  // and row

                  colP--; // proceed with previous column
                }

              if (i >= colP)
                {
                  if (cb) cb->finishItem(hProcess);

                  return true;
                }

              // Swap columns i and colP
              pTmp1 = &A(0, i);
              pTmp2 = &A(0, colP);

              for (k = 0; k < Rows; k++, pTmp1 += Cols, pTmp2 += Cols)
                {
                  tmp = *pTmp1;
                  *pTmp1 = *pTmp2;
                  *pTmp2 = tmp;
                }

              std::swap(col[i], col[colP]);
              colP--;
            }

          // Swap rows i and rowP
          pTmp1 = &A(i, 0);
          pTmp2 = &A(rowP, 0);

          for (k = 0; k < Cols; k++, pTmp1++, pTmp2++)
            {
              tmp = *pTmp1;
              *pTmp1 = *pTmp2;
              *pTmp2 = tmp;
            }

          std::swap(row[i], row[rowP]);
          break;
        }

      if (i < Rows - 1)    // compute elements i+1 <= k < M of i-th column
        {
          // note A(i,i) is guarranteed not to be zero
          tmp = 1.0 / A(i, i);

          pTmp1 = &A(i + 1, i);

          for (k = i + 1; k < Rows; k++, pTmp1 += Cols)
            * pTmp1 *= tmp;
        }

      if (i < Dim - 1)
        {
          // rank-1 update to trailing submatrix:   E = E - x*y;
          //
          // E is the region A(i+1:M, i+1:N)
          // x is the column vector A(i+1:M,i)
          // y is row vector A(i,i+1:N)

          size_t ii, jj;

          pTmp1 = &A(i + 1, i);
          pTmp3 = &A(i + 1, i + 1);

          for (ii = i + 1; ii < Rows; ii++, pTmp1 += Cols, pTmp3 += i + 1)
            {
              pTmp2 = &A(i, i + 1);

              for (jj = i + 1; jj < Cols; jj++, pTmp2++, pTmp3++)
                {
                  *pTmp3 -= *pTmp1 **pTmp2;
                  //                  if (fabs(*pTmp3) < std::numeric_limits< C_FLOAT64 >::epsilon()) *pTmp3 = 0.0;
                }
            }
        }

#ifdef DEBUG_MATRIX
      DebugFile << rowP << "\tx\t" << colP + 1 << std::endl;
      DebugFile << "Row\t" << row << std::endl;
      DebugFile << "Col\t" << col << std::endl;
      DebugFile << A << std::endl;
#endif
    }

  if (cb) cb->finishItem(hProcess);

  return true;
}

#ifdef XXXX
bool LUfactor(CMatrix< C_FLOAT64 > & A,
              CVector< size_t > & row,
              CVector< size_t > & col,
              CProcessReport * cb)
{
  CVector< size_t > lCol;

  C_INT Rows = A.numRows();
  C_INT Cols = A.numCols();

  if (row.size() != Rows) row.resize(Rows);

  if (col.size() != Cols) col.resize(Cols);

  if (lRow.size() != Rows) lRow.resize(Rows);

  if (lCol.size() != Rows) lCol.resize(Cols);

  size_t i = 0, j = 0, k = 0;
  size_t ip, jp = Cols - 1;

  for (i = 0; i < Rows; i++)
    {
      row[i] = i;
      lRow[i] = i;
    }

  for (i = 0; i < Cols; i++)
    {
      col[i] = i;
      lCol[i] = i;
    }

  if (Rows == 0 || Cols == 0)
    return false;

  CMatrix< C_FLOAT64 > T(Cols, Rows);

  for (i = 0; i < Cols; i++)
    for (j = 0; j < Rows; j++)
      T(i, j) = A(j, i);

  C_INT imax = std::min(Rows, Cols);
  CVector<C_INT> RowPivot(imax);

  C_INT Info;

  bool found;
  C_FLOAT64 tmp;
  C_FLOAT64 * pTmp1;
  C_FLOAT64 * pTmp2;
  size_t Delta;

  C_INT subRows = Rows;
  C_INT subCols = Cols;

  size_t iTop = 0;
  size_t jTop = 0;
  size_t LastCols = Cols;

  while (true)
    {
      /*
       *  -- LAPACK routine (version 3.0) --
       *     Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,
       *     Courant Institute, Argonne National Lab, and Rice University
       *     March 31, 1993
       *
       *  Purpose
       *  =======
       *
       *  DGETRF computes an LU factorization of a general M-by-N matrix A
       *  using partial pivoting with row interchanges.
       *
       *  The factorization has the form
       *     A = P * L * U
       *  where P is a permutation matrix, L is lower triangular with unit
       *  diagonal elements (lower trapezoidal if m > n), and U is upper
       *  triangular (upper trapezoidal if m < n).
       *
       *  This is the right-looking Level 3 BLAS version of the algorithm.
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
       *  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)
       *          On entry, the M-by-N matrix to be factored.
       *          On exit, the factors L and U from the factorization
       *          A = P*L*U; the unit diagonal elements of L are not stored.
       *
       *  LDA     (input) INTEGER
       *          The leading dimension of the array A.  LDA >= max(1,M).
       *
       *  IPIV    (output) INTEGER array, dimension (min(M,N))
       *          The pivot indices; for 1 <= i <= min(M,N), row i of the
       *          matrix was interchanged with row IPIV(i).
       *
       *  INFO    (output) INTEGER
       *          = 0:  successful exit
       *          < 0:  if INFO = -i, the i-th argument had an illegal value
       *          > 0:  if INFO = i, U(i,i) is exactly zero. The factorization
       *                has been completed, but the factor U is exactly
       *                singular, and division by zero will occur if it is used
       *                to solve a system of equations.
       *
       */
      dgetrf_(&subRows, &subCols, &T(lCol[iTop], iTop), &Rows, RowPivot.array(), &Info);

      if (Info < 0) return false;

#ifdef DEBUG_MATRIX
      DebugFile << "After dgetrf_\n";
      DebugFile << CTransposeView< CMatrix< C_FLOAT64 > >(T);
#endif

      for (i = 0; i < RowPivot.size(); i++)
        if (i != RowPivot[i] - 1)
          {
            std::swap(row[i + iTop], row[RowPivot[i] - 1 + iTop]);

            pTmp1 = &T(0, i + iTop);
            pTmp2 = &T(0, RowPivot[i] - 1 + iTop);

            for (k = 0; k < iTop; k++, pTmp1 += Rows, pTmp2 += Rows)
              {
                tmp = *pTmp1;
                *pTmp1 = *pTmp2;
                *pTmp2 = tmp;
              }
          }

#ifdef DEBUG_MATRIX
      DebugFile << row << std::endl;
      DebugFile << "After row swap\n";
      DebugFile << CTransposeView< CMatrix< C_FLOAT64 > >(T);
#endif

      if (Info == 0) break;

      iTop += Info - 1;

      // Search first non zero diagonal
      for (i = iTop + 1, found = false; i < imax; i++)
        if (T(lCol[i], i) != 0.0)
          {
            jTop = i;
            found = true;
            break;
          }

      if (found)
        {
          for (i = Rows - 1; jTop <= i; i--)
            {
              for (j = Cols - 1; lCol[jTop] <= j; j--)
                {
                  tmp = 0.0;

                  pTmp1 = &T(iTop, i);
                  pTmp2 = &T(j, iTop);

                  for (k = iTop; k < i && k < j; k++, pTmp1 += Rows, pTmp2++)
                    tmp += *pTmp1 **pTmp2;

                  if (i <= j) tmp += *pTmp2;

                  T(j, i) = tmp;
                }
            }

          subRows = Rows - iTop;
          subCols = Cols - lCol[iTop];

          pTmp1 = &T(lCol[iTop], 0);
          pTmp2 = &T(lCol[jTop], 0);

          for (k = 0; k < Rows; k++, pTmp1++, pTmp2++)
            {
              tmp = *pTmp1;
              *pTmp1 = *pTmp2;
              *pTmp2 = tmp;
            }

          std::swap(col[iTop], col[jTop]);

#ifdef DEBUG_MATRIX
          DebugFile << "After partial inversion: " << iTop << " , " << jTop << std::endl;
          DebugFile << CTransposeView< CMatrix< C_FLOAT64 > >(T);
          DebugFile << "After column swap\n";
          DebugFile << CTransposeView< CMatrix< C_FLOAT64 > >(T);
#endif
        }
      else
        {
          for (j = iTop + 1, found = false; j < Cols; j++)
            {
              for (i = iTop; i < j && i < Rows; i++)
                if (T(lCol[j], i) != 0)
                  {
                    found = true;
                    break;
                  }

              if (found) break;
            }

          if (!found) break;

          jTop = j;

          subRows = Rows - iTop;
          subCols = Cols - lCol[jTop];

          Delta = jTop - iTop;

          // Record the needed column swaps
          for (j = jTop; j < LastCols; j += Delta)
            for (i = j - Delta; i < j && i + Delta < LastCols; i++)
              {
                std::swap(col[i], col[i + Delta]);
                std::swap(lCol[i], lCol[i + Delta]);
              }

          LastCols -= Delta;
        }

      RowPivot.resize(std::min(subRows, subCols));

#ifdef DEBUG_MATRIX
      DebugFile << lCol << std::endl;
      DebugFile << col << std::endl;
#endif
    }

  for (i = 0; i < Cols; i++)
    for (j = 0; j < Rows; j++)
      A(j, i) = T(lCol[i], j);

#ifdef DEBUG_MATRIX
  DebugFile << A;
#endif

  return true;
}
#endif // XXXX
