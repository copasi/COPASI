/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CluX.h,v $
   $Revision: 1.15 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:32:43 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CluX
#define COPASI_CluX

// Solve system of linear equations Ax = b.
//
//  Typical usage:
//
//    Matrix(double) A;
//    Vector(unsigned C_INT32) ipiv;
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
class CProcessReport;
template < typename ValueType > class CMatrix;
template < typename ValueType > class CVector;

bool LUfactor(CMatrix< C_FLOAT64 > & A,
              CVector< unsigned C_INT32 > & row,
              CVector< unsigned C_INT32 > & col,
              CProcessReport * cb = NULL);

#endif // COPASI_CluX
