/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CluX.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/12/02 19:08:09 $
   End CVS Header */

#include <algorithm>

#include "copasi.h"

#include "CluX.h"
#include "CMatrix.h"
#include "CVector.h"

#include "clapackwrap.h"

// #define DEBUG_MATRIX

bool LUfactor(CMatrix< C_FLOAT64 > & A,
              CVector< unsigned C_INT32 > & row,
              CVector< unsigned C_INT32 > & col,
              CVector< unsigned C_INT32 > & lRow)
{
  CVector< unsigned C_INT32 > lCol;

  C_INT Rows = A.numRows();
  C_INT Cols = A.numCols();

  if (row.size() != Rows) row.resize(Rows);
  if (col.size() != Cols) col.resize(Cols);
  if (lRow.size() != Rows) lRow.resize(Rows);
  if (lCol.size() != Rows) lCol.resize(Cols);

  unsigned C_INT32 i = 0, j = 0, k = 0;
  unsigned C_INT32 ip, jp = Cols - 1;

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
      T(i, j) = A (j, i);

  C_INT imax = std::min(Rows, Cols);
  CVector<C_INT> RowPivot(imax);

  C_INT Info;

  bool found;
  C_FLOAT64 tmp;
  C_FLOAT64 * pTmp1;
  C_FLOAT64 * pTmp2;
  unsigned C_INT32 Delta;

  C_INT subRows = Rows;
  C_INT subCols = Cols;

  unsigned C_INT32 iTop = 0;
  unsigned C_INT32 jTop = 0;
  unsigned C_INT32 LastCols = Cols;

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
;
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
                    tmp += *pTmp1 * *pTmp2;

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
