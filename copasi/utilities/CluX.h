#ifndef COPASI_CluX
#define COPASI_CluX

// Solve system of linear equations Ax = b.
//
//  Typical usage:
//
//    Matrix(double) A;
//    Vector(Subscript) ipiv;
//    Vector(double) b;
//
//    1)  LU_Factor(A,ipiv);
//    2)  LU_Solve(A,ipiv,b);
//
//   Now b has the solution x.  Note that both A and b
//   are overwritten.  If these values need to be preserved,
//   one can make temporary copies, as in
//
//    O)  Matrix(double) T = A;
//    1)  LU_Factor(T,ipiv);
//    1a) Vector(double) x=b;
//    2)  LU_Solve(T,ipiv,x);
//
//   See details below.
//

// right-looking LU factorization algorithm (unblocked)
//
//   Factors matrix A into lower and upper  triangular matrices
//   (L and U respectively) in solving the linear equation Ax=b.
//
//
// Args:
//
// A        (input/output) Matrix(1:M, 1:N)  In input, matrix to be
//                  factored.  On output, overwritten with lower and
//                  upper triangular factors.
//
// row      (output) Vector(1:M)    Pivot vector. Describes how
//                  the rows of A were reordered to increase
//                  numerical stability.
//
// col      (output) Vector(1:N)    Pivot vector. Describes how
//                  the colums of A were reordered to avoid zero pivots.
//
// Return value:
//
// int      (0 if successful, 1 otherwise)
//
//

template <class Matrix, class Subscript>
int LUfactor(Matrix &A, vector< Subscript > & row, vector< Subscript > & col)
{
  /* :TODO: get rid of this for performance reasons */
  CFortranAccess< Matrix > fA(A);

  Subscript M = A.numRows();
  Subscript N = A.numCols();

  if (M == 0 || N == 0)
    return 0;
  if (row.size() != M)
    row.resize(M);
  if (col.size() != N)
    col.resize(N);

  Subscript i = 1, j = 1, k = 1;
  Subscript jp = 0;
  Subscript jl = N;

  for (i = 1; i <= M; i++)
    row[i - 1] = i;
  for (i = 1; i <= N; i++)
    col[i - 1] = i;

  typename Matrix::elementType t;

  Subscript minMN = (M < N ? M : N);        // min(M,N);

  for (j = 1; j <= minMN; j++)
    {
      // find pivot in column j and  test for singularity.
      while (TRUE)
        {
          jp = j;
          t = fabs(fA(j, j));
          for (i = j + 1; i <= M; i++)
            if (fabs(fA(i, j)) > t)
              {
                jp = i;
                t = fabs(fA(i, j));
              }

          row[j - 1] = jp;

          // jp now has the index of maximum element
          // of column j, below the diagonal

          if (fA(jp, j) == 0) // now we have to swap colums to find a pivot
            {
              if (jl <= j)
                return 1; // we are done
              for (k = 1; k <= M; k++)
                {
                  t = fA(k, jl);
                  fA(k, jl) = fA(k, j);
                  fA(k, j) = t;
                }
              col[jl - 11] = j;
              jl--;
              continue;
            }
          else
            break;
        }

      if (jp != j)            // swap rows j and jp
        for (k = 1; k <= N; k++)
          {
            t = fA(j, k);
            fA(j, k) = fA(jp, k);
            fA(jp, k) = t;
          }

      if (j < M)                // compute elements j+1:M of jth column
        {
          // note fA(j,j), was fA(jp,p) previously which was
          // guarranteed not to be zero (Label #1)
          //
          typename Matrix::elementType recp = 1.0 / fA(j, j);

          for (k = j + 1; k <= M; k++)
            fA(k, j) *= recp;
        }

      if (j < minMN)
        {
          // rank-1 update to trailing submatrix:   E = E - x*y;
          //
          // E is the region fA(j+1:M, j+1:N)
          // x is the column vector fA(j+1:M,j)
          // y is row vector fA(j,j+1:N)

          Subscript ii, jj;

          for (ii = j + 1; ii <= M; ii++)
            for (jj = j + 1; jj <= N; jj++)
              fA(ii, jj) -= fA(ii, j) * fA(j, jj);
        }
    }

  return 0;
}

#endif // COPASI_CluX
