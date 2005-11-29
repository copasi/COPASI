/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CluX.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/11/29 17:19:22 $
   End CVS Header */

#include <algorithm>

#include "copasi.h"

#include "CluX.h"
 #include "CMatrix.h"
 #include "CVector.h"

#include "clapackwrap.h"

bool LUfactor(CMatrix< C_FLOAT64 > & A,
              CVector< unsigned C_INT32 > & row,
              CVector< unsigned C_INT32 > & col,
              CVector< unsigned C_INT32 > & lRow)
{
  C_INT Rows = A.numRows();
  C_INT Cols = A.numCols();

  if (row.size() != Rows) row.resize(Rows);
  if (col.size() != Cols) col.resize(Cols);
  if (lRow.size() != Rows) lRow.resize(Rows);

  unsigned C_INT32 i = 0, j = 0, k = 0;
  unsigned C_INT32 ip, jp = Cols - 1;

  for (i = 0; i < Rows; i++)
    {
      row[i] = i;
      lRow[i] = i;
    }

  for (i = 0; i < Cols; i++)
    col[i] = i;

  if (Rows == 0 || Cols == 0)
    return false;

  // :TODO: we must avoid the need of this copy
  CMatrix< C_FLOAT64 > T(Cols, Rows);

  for (i = 0; i < Cols; i++)
    for (j = 0; j < Rows; j++)
      T(i, j) = A (j, i);

  C_INT imax = std::min(Rows, Cols);
  CVector<C_INT> RowPivot(imax);

  C_INT Info;

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

  dgetrf_(&Rows, &Cols, T.array(), &Rows, RowPivot.array(), &Info);
  if (Info < 0) return false;

  for (i = 0; i < Cols; i++)
    for (j = 0; j < Rows; j++)
      A(j, i) = T(i, j);

  for (i = 0; i < RowPivot.size(); i++)
    std::swap(row[i], row[RowPivot[i] - 1]);

  // We need to assure that the lower right block of LU is zero.
  // We achieve this through row and column swapping however there is
  // no need to do the physical swapping :)
  // We just need to record the pivot vectors.

  // Allowed operations which do not corrupt the triangular properties
  // of L and U (k < l):
  // 1) swap(row[k], row[l]), swap(col[k], col[l]) when U(k, k) = 0
  // 2) swap(col[k], col[l]), only when:
  //    L(n, k) = 0 for n > k,
  //    L(n, l) = 0 for n > k,
  //    U(n, k) = 0 for n >= k,
  //    U(n, l) = 0 for n > k

  // First zero diagonal element is Info - 1 if Info > 0.
  if (Info != 0)
    i = Info - 1;
  else
    i = imax - 1;

  // Move zeros in the diagonal to be at the end (rule 1)
  for (j = imax - 1; i < j; i++)
    if (A(lRow[i], col[i]) == 0.0)
      {
        for (; i < j; j--)
          if (A(lRow[j], col[j]) != 0.0)
            {
              std::swap(row[i], row[j]);
              std::swap(lRow[i], lRow[j]);
              std::swap(col[i], col[j]);

              j--;
              break;
            }

        if (A(lRow[i], col[i]) == 0.0) break; // We did not find a non zero diagonal element
      }

  if (A(lRow[i], col[i]) != 0.0) i++;

  jp = Cols - 1;

  while (i < imax)
    {
      // Find last non zero element in last column
      for (; i < jp; jp--)
        {
          for (ip = std::min((unsigned C_INT32) Rows, jp) - 1; i <= ip; ip--)
            if (A(lRow[ip], col[jp]) != 0.0)
              {
                // rule 2
                std::swap(col[ip], col[jp]);

                // now A(lRow[ip], col[ip]) is non zero

                // rule 1
                std::swap(row[i], row[ip]);
                std::swap(lRow[i], lRow[ip]);
                std::swap(col[i], col[ip]);

                break;
              }

          if (A(lRow[i], col[i]) != 0.0) break;
        }

      i++;
    }

  return true;
}
