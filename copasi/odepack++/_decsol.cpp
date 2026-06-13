// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi/odepack++/_decsol.h"

void decsol::dec(const integer & n,
                 const integer & ndim,
                 CFortranAccess< CMatrix< doublereal > > & a,
                 CVectorCore< integer > & ip,
                 integer & ier)
{
  integer nm1 = 0;
  integer k = 0;
  integer kp1 = 0;
  integer m = 0;
  integer i = 0;
  doublereal t = 0.0;
  integer j = 0;
  //C VERSION REAL DOUBLE PRECISION
  //C-----------------------------------------------------------------------
  //C  MATRIX TRIANGULARIZATION BY GAUSSIAN ELIMINATION.
  //C  INPUT..
  //C     N = ORDER OF MATRIX.
  //C     NDIM = DECLARED DIMENSION OF ARRAY  A .
  //C     A = MATRIX TO BE TRIANGULARIZED.
  //C  OUTPUT..
  //C     A(I,J), I.LE.J = UPPER TRIANGULAR FACTOR, U .
  //C     A(I,J), I.GT.J = MULTIPLIERS = LOWER TRIANGULAR FACTOR, I - L.
  //C     IP(K), K.LT.N = INDEX OF K-TH PIVOT ROW.
  //C     IP(N) = (-1)**(NUMBER OF INTERCHANGES) OR O .
  //C     IER = 0 IF MATRIX A IS NONSINGULAR, OR K IF FOUND TO BE
  //C           SINGULAR AT STAGE K.
  //C  USE  SOL  TO OBTAIN SOLUTION OF LINEAR SYSTEM.
  //C  DETERM(A) = IP(N)*A(1,1)*A(2,2)*...*A(N,N).
  //C  IF IP(N)=O, A IS SINGULAR, SOL WILL DIVIDE BY ZERO.
  //C
  //C  REFERENCE..
  //C     C. B. MOLER, ALGORITHM 423, LINEAR EQUATION SOLVER,
  //C     C.A.C.M. 15 (1972), P. 274.
  //C-----------------------------------------------------------------------
  ier = 0;
  ip(n) = 1;
  if (n == 1)
    {
      goto statement_70;
    }
  nm1 = n - 1;
  // FEM_DO_SAFE(k, 1, nm1)
  for (integer k = 1; k <= nm1; ++k)
    {
      kp1 = k + 1;
      m = k;
      // FEM_DO_SAFE(i, kp1, n)
      for (integer i = kp1; i <= n; ++i)
        {
          if (std::abs(a(i, k)) > std::abs(a(m, k)))
            {
              m = i;
            }
        }
      ip(k) = m;
      t = a(m, k);
      if (m == k)
        {
          goto statement_20;
        }
      ip(n) = -ip(n);
      a(m, k) = a(k, k);
      a(k, k) = t;
    statement_20:
      if (t == 0.e0)
        {
          goto statement_80;
        }
      t = 1.e0 / t;
      // FEM_DO_SAFE(i, kp1, n)
      for (integer i = kp1; i <= n; ++i)
        {
          a(i, k) = -a(i, k) * t;
        }
      // FEM_DO_SAFE(j, kp1, n)
      for (integer j = kp1; j <= n; ++j)
        {
          t = a(m, j);
          a(m, j) = a(k, j);
          a(k, j) = t;
          if (t == 0.e0)
            {
              goto statement_45;
            }
          // FEM_DO_SAFE(i, kp1, n)
          for (integer i = kp1; i <= n; ++i)
            {
              a(i, j) += a(i, k) * t;
            }
        statement_45:;
        }
    }
statement_70:
  k = n;
  if (a(n, n) == 0.e0)
    {
      goto statement_80;
    }
  return;
statement_80:
  ier = k;
  ip(n) = 0;
  //C----------------------- END OF SUBROUTINE DEC -------------------------
}

void decsol::sol(const integer & n,
                 const integer & ndim,
                 const CFortranAccess< CMatrix< doublereal > > & a,
                 CVectorCore< doublereal > & b,
                 const CVectorCore< integer > & ip)
{
  integer nm1 = 0;
  integer k = 0;
  integer kp1 = 0;
  integer m = 0;
  doublereal t = 0.0;
  integer i = 0;
  integer kb = 0;
  integer km1 = 0;
  //C VERSION REAL DOUBLE PRECISION
  //C-----------------------------------------------------------------------
  //C  SOLUTION OF LINEAR SYSTEM, A*X = B .
  //C  INPUT..
  //C    N = ORDER OF MATRIX.
  //C    NDIM = DECLARED DIMENSION OF ARRAY  A .
  //C    A = TRIANGULARIZED MATRIX OBTAINED FROM DEC.
  //C    B = RIGHT HAND SIDE VECTOR.
  //C    IP = PIVOT VECTOR OBTAINED FROM DEC.
  //C  DO NOT USE IF DEC HAS SET IER .NE. 0.
  //C  OUTPUT..
  //C    B = SOLUTION VECTOR, X .
  //C-----------------------------------------------------------------------
  if (n == 1)
    {
      goto statement_50;
    }
  nm1 = n - 1;
  // FEM_DO_SAFE(k, 1, nm1)
  for (integer k = 1; k <= nm1; ++k)
    {
      kp1 = k + 1;
      m = ip(k);
      t = b(m);
      b(m) = b(k);
      b(k) = t;
      // FEM_DO_SAFE(i, kp1, n)
      for (integer i = kp1; i <= n; ++i)
        {
          b(i) += a(i, k) * t;
        }
    }
  // FEM_DO_SAFE(kb, 1, nm1)
  for (integer kb = 1; kb <= nm1; ++kb)
    {
      km1 = n - kb;
      k = km1 + 1;
      b(k) = b(k) / a(k, k);
      t = -b(k);
      // FEM_DO_SAFE(i, 1, km1)
      for (integer i = 1; i <= km1; ++i)
        {
          b(i) += a(i, k) * t;
        }
    }
statement_50:
  b(1) = b(1) / a(1, 1);
  //C----------------------- END OF SUBROUTINE SOL -------------------------
}

void decsol::sol(const integer & n,
                 const integer & ndim,
                 const CFortranAccess< CMatrix< doublereal > > & a,
                 doublereal & b,
                 const CVectorCore< integer > & ip)
{
  CVectorCore< doublereal > B(n, &b);
  sol(n, ndim, a, B, ip);
}

void decsol::dech(const integer & n,
                  const integer & ndim,
                  CFortranAccess< CMatrix< doublereal > > & a,
                  const integer & lb,
                  CVectorCore< integer > & ip,
                  int & ier)
{
  integer nm1 = 0;
  integer k = 0;
  integer kp1 = 0;
  integer m = 0;
  integer na = 0;
  integer i = 0;
  doublereal t = 0.0;
  integer j = 0;
  //C VERSION REAL DOUBLE PRECISION
  //C-----------------------------------------------------------------------
  //C  MATRIX TRIANGULARIZATION BY GAUSSIAN ELIMINATION OF A HESSENBERG
  //C  MATRIX WITH LOWER BANDWIDTH LB
  //C  INPUT..
  //C     N = ORDER OF MATRIX A.
  //C     NDIM = DECLARED DIMENSION OF ARRAY  A .
  //C     A = MATRIX TO BE TRIANGULARIZED.
  //C     LB = LOWER BANDWIDTH OF A (DIAGONAL IS NOT COUNTED, LB.GE.1).
  //C  OUTPUT..
  //C     A(I,J), I.LE.J = UPPER TRIANGULAR FACTOR, U .
  //C     A(I,J), I.GT.J = MULTIPLIERS = LOWER TRIANGULAR FACTOR, I - L.
  //C     IP(K), K.LT.N = INDEX OF K-TH PIVOT ROW.
  //C     IP(N) = (-1)**(NUMBER OF INTERCHANGES) OR O .
  //C     IER = 0 IF MATRIX A IS NONSINGULAR, OR K IF FOUND TO BE
  //C           SINGULAR AT STAGE K.
  //C  USE  SOLH  TO OBTAIN SOLUTION OF LINEAR SYSTEM.
  //C  DETERM(A) = IP(N)*A(1,1)*A(2,2)*...*A(N,N).
  //C  IF IP(N)=O, A IS SINGULAR, SOL WILL DIVIDE BY ZERO.
  //C
  //C  REFERENCE..
  //C     THIS IS A SLIGHT MODIFICATION OF
  //C     C. B. MOLER, ALGORITHM 423, LINEAR EQUATION SOLVER,
  //C     C.A.C.M. 15 (1972), P. 274.
  //C-----------------------------------------------------------------------
  ier = 0;
  ip(n) = 1;
  if (n == 1)
    {
      goto statement_70;
    }
  nm1 = n - 1;
  // FEM_DO_SAFE(k, 1, nm1)
  for (integer k = 1; k <= nm1; ++k)
    {
      kp1 = k + 1;
      m = k;
      na = std::min(n, lb + k);
      // FEM_DO_SAFE(i, kp1, na)
      for (integer i = kp1; i <= na; ++i)
        {
          if (std::abs(a(i, k)) > std::abs(a(m, k)))
            {
              m = i;
            }
        }
      ip(k) = m;
      t = a(m, k);
      if (m == k)
        {
          goto statement_20;
        }
      ip(n) = -ip(n);
      a(m, k) = a(k, k);
      a(k, k) = t;
    statement_20:
      if (t == 0.e0)
        {
          goto statement_80;
        }
      t = 1.e0 / t;
      // FEM_DO_SAFE(i, kp1, na)
      for (integer i = kp1; i <= na; ++i)
        {
          a(i, k) = -a(i, k) * t;
        }
      // FEM_DO_SAFE(j, kp1, n)
      for (integer j = kp1; j <= n; ++j)
        {
          t = a(m, j);
          a(m, j) = a(k, j);
          a(k, j) = t;
          if (t == 0.e0)
            {
              goto statement_45;
            }
          // FEM_DO_SAFE(i, kp1, na)
          for (integer i = kp1; i <= na; ++i)
            {
              a(i, j) += a(i, k) * t;
            }
        statement_45:;
        }
    }
statement_70:
  k = n;
  if (a(n, n) == 0.e0)
    {
      goto statement_80;
    }
  return;
statement_80:
  ier = k;
  ip(n) = 0;
  //C----------------------- END OF SUBROUTINE DECH ------------------------
}

void decsol::solh(const integer & n,
                  const integer & ndim,
                  const CFortranAccess< CMatrix< doublereal > > & a,
                  const integer & lb,
                  CVectorCore< doublereal > & b,
                  const CVectorCore< integer > & ip)
{
  integer nm1 = 0;
  integer k = 0;
  integer kp1 = 0;
  integer m = 0;
  doublereal t = 0.0;
  integer na = 0;
  integer i = 0;
  integer kb = 0;
  integer km1 = 0;
  //C VERSION REAL DOUBLE PRECISION
  //C-----------------------------------------------------------------------
  //C  SOLUTION OF LINEAR SYSTEM, A*X = B .
  //C  INPUT..
  //C    N = ORDER OF MATRIX A.
  //C    NDIM = DECLARED DIMENSION OF ARRAY  A .
  //C    A = TRIANGULARIZED MATRIX OBTAINED FROM DECH.
  //C    LB = LOWER BANDWIDTH OF A.
  //C    B = RIGHT HAND SIDE VECTOR.
  //C    IP = PIVOT VECTOR OBTAINED FROM DEC.
  //C  DO NOT USE IF DECH HAS SET IER .NE. 0.
  //C  OUTPUT..
  //C    B = SOLUTION VECTOR, X .
  //C-----------------------------------------------------------------------
  if (n == 1)
    {
      goto statement_50;
    }
  nm1 = n - 1;
  // FEM_DO_SAFE(k, 1, nm1)
  for (integer k = 1; k <= nm1; ++k)
    {
      kp1 = k + 1;
      m = ip(k);
      t = b(m);
      b(m) = b(k);
      b(k) = t;
      na = std::min(n, lb + k);
      // FEM_DO_SAFE(i, kp1, na)
      for (integer i = kp1; i <= na; ++i)
        {
          b(i) += a(i, k) * t;
        }
    }
  // FEM_DO_SAFE(kb, 1, nm1)
  for (integer kb = 1; kb <= nm1; ++kb)
    {
      km1 = n - kb;
      k = km1 + 1;
      b(k) = b(k) / a(k, k);
      t = -b(k);
      // FEM_DO_SAFE(i, 1, km1)
      for (integer i = 1; i <= km1; ++i)
        {
          b(i) += a(i, k) * t;
        }
    }
statement_50:
  b(1) = b(1) / a(1, 1);
  //C----------------------- END OF SUBROUTINE SOLH ------------------------
}

void decsol::decc(const integer & n,
                  const integer & ndim,
                  CFortranAccess< CMatrix< doublereal > > & ar,
                  CFortranAccess< CMatrix< doublereal > > & ai,
                  CVectorCore< integer > & ip,
                  int & ier)
{
  integer nm1 = 0;
  integer k = 0;
  integer kp1 = 0;
  integer m = 0;
  integer i = 0;
  doublereal tr = 0.0;
  doublereal ti = 0.0;
  doublereal den = 0.0;
  doublereal prodr = 0.0;
  doublereal prodi = 0.0;
  integer j = 0;
  //C VERSION COMPLEX DOUBLE PRECISION
  //C-----------------------------------------------------------------------
  //C  MATRIX TRIANGULARIZATION BY GAUSSIAN ELIMINATION
  //C  ------ MODIFICATION FOR COMPLEX MATRICES --------
  //C  INPUT..
  //C     N = ORDER OF MATRIX.
  //C     NDIM = DECLARED DIMENSION OF ARRAYS  AR AND AI .
  //C     (AR, AI) = MATRIX TO BE TRIANGULARIZED.
  //C  OUTPUT..
  //C     AR(I,J), I.LE.J = UPPER TRIANGULAR FACTOR, U ; REAL PART.
  //C     AI(I,J), I.LE.J = UPPER TRIANGULAR FACTOR, U ; IMAGINARY PART.
  //C     AR(I,J), I.GT.J = MULTIPLIERS = LOWER TRIANGULAR FACTOR, I - L.
  //C                                                    REAL PART.
  //C     AI(I,J), I.GT.J = MULTIPLIERS = LOWER TRIANGULAR FACTOR, I - L.
  //C                                                    IMAGINARY PART.
  //C     IP(K), K.LT.N = INDEX OF K-TH PIVOT ROW.
  //C     IP(N) = (-1)**(NUMBER OF INTERCHANGES) OR O .
  //C     IER = 0 IF MATRIX A IS NONSINGULAR, OR K IF FOUND TO BE
  //C           SINGULAR AT STAGE K.
  //C  USE  SOL  TO OBTAIN SOLUTION OF LINEAR SYSTEM.
  //C  IF IP(N)=O, A IS SINGULAR, SOL WILL DIVIDE BY ZERO.
  //C
  //C  REFERENCE..
  //C     C. B. MOLER, ALGORITHM 423, LINEAR EQUATION SOLVER,
  //C     C.A.C.M. 15 (1972), P. 274.
  //C-----------------------------------------------------------------------
  ier = 0;
  ip(n) = 1;
  if (n == 1)
    {
      goto statement_70;
    }
  nm1 = n - 1;
  // FEM_DO_SAFE(k, 1, nm1)
  for (integer k = 1; k <= nm1; ++k)
    {
      kp1 = k + 1;
      m = k;
      // FEM_DO_SAFE(i, kp1, n)
      for (integer i = kp1; i <= n; ++i)
        {
          if (std::abs(ar(i, k)) + std::abs(ai(i, k)) > std::abs(ar(m,
                                                                    k))
                                                          + std::abs(ai(m, k)))
            {
              m = i;
            }
        }
      ip(k) = m;
      tr = ar(m, k);
      ti = ai(m, k);
      if (m == k)
        {
          goto statement_20;
        }
      ip(n) = -ip(n);
      ar(m, k) = ar(k, k);
      ai(m, k) = ai(k, k);
      ar(k, k) = tr;
      ai(k, k) = ti;
    statement_20:
      if (std::abs(tr) + std::abs(ti) == 0.e0)
        {
          goto statement_80;
        }
      den = tr * tr + ti * ti;
      tr = tr / den;
      ti = -ti / den;
      // FEM_DO_SAFE(i, kp1, n)
      for (integer i = kp1; i <= n; ++i)
        {
          prodr = ar(i, k) * tr - ai(i, k) * ti;
          prodi = ai(i, k) * tr + ar(i, k) * ti;
          ar(i, k) = -prodr;
          ai(i, k) = -prodi;
        }
      // FEM_DO_SAFE(j, kp1, n)
      for (integer j = kp1; j <= n; ++j)
        {
          tr = ar(m, j);
          ti = ai(m, j);
          ar(m, j) = ar(k, j);
          ai(m, j) = ai(k, j);
          ar(k, j) = tr;
          ai(k, j) = ti;
          if (std::abs(tr) + std::abs(ti) == 0.e0)
            {
              goto statement_48;
            }
          if (ti == 0.e0)
            {
              // FEM_DO_SAFE(i, kp1, n)
              for (integer i = kp1; i <= n; ++i)
                {
                  prodr = ar(i, k) * tr;
                  prodi = ai(i, k) * tr;
                  ar(i, j) += prodr;
                  ai(i, j) += prodi;
                }
              goto statement_48;
            }
          if (tr == 0.e0)
            {
              // FEM_DO_SAFE(i, kp1, n)
              for (integer i = kp1; i <= n; ++i)
                {
                  prodr = -ai(i, k) * ti;
                  prodi = ar(i, k) * ti;
                  ar(i, j) += prodr;
                  ai(i, j) += prodi;
                }
              goto statement_48;
            }
          // FEM_DO_SAFE(i, kp1, n)
          for (integer i = kp1; i <= n; ++i)
            {
              prodr = ar(i, k) * tr - ai(i, k) * ti;
              prodi = ai(i, k) * tr + ar(i, k) * ti;
              ar(i, j) += prodr;
              ai(i, j) += prodi;
            }
        statement_48:;
        }
    }
statement_70:
  k = n;
  if (std::abs(ar(n, n)) + std::abs(ai(n, n)) == 0.e0)
    {
      goto statement_80;
    }
  return;
statement_80:
  ier = k;
  ip(n) = 0;
  //C----------------------- END OF SUBROUTINE DECC ------------------------
}

void decsol::solc(const integer & n,
                  const integer & ndim,
                  const CFortranAccess< CMatrix< doublereal > > & ar,
                  const CFortranAccess< CMatrix< doublereal > > & ai,
                  CVectorCore< doublereal > & br,
                  CVectorCore< doublereal > & bi,
                  const CVectorCore< integer > & ip)
{
  integer nm1 = 0;
  integer k = 0;
  integer kp1 = 0;
  integer m = 0;
  doublereal tr = 0.0;
  doublereal ti = 0.0;
  integer i = 0;
  doublereal prodr = 0.0;
  doublereal prodi = 0.0;
  integer kb = 0;
  integer km1 = 0;
  doublereal den = 0.0;
  //C VERSION COMPLEX DOUBLE PRECISION
  //C-----------------------------------------------------------------------
  //C  SOLUTION OF LINEAR SYSTEM, A*X = B .
  //C  INPUT..
  //C    N = ORDER OF MATRIX.
  //C    NDIM = DECLARED DIMENSION OF ARRAYS  AR AND AI.
  //C    (AR,AI) = TRIANGULARIZED MATRIX OBTAINED FROM DEC.
  //C    (BR,BI) = RIGHT HAND SIDE VECTOR.
  //C    IP = PIVOT VECTOR OBTAINED FROM DEC.
  //C  DO NOT USE IF DEC HAS SET IER .NE. 0.
  //C  OUTPUT..
  //C    (BR,BI) = SOLUTION VECTOR, X .
  //C-----------------------------------------------------------------------
  if (n == 1)
    {
      goto statement_50;
    }
  nm1 = n - 1;
  // FEM_DO_SAFE(k, 1, nm1)
  for (integer k = 1; k <= nm1; ++k)
    {
      kp1 = k + 1;
      m = ip(k);
      tr = br(m);
      ti = bi(m);
      br(m) = br(k);
      bi(m) = bi(k);
      br(k) = tr;
      bi(k) = ti;
      // FEM_DO_SAFE(i, kp1, n)
      for (integer i = kp1; i <= n; ++i)
        {
          prodr = ar(i, k) * tr - ai(i, k) * ti;
          prodi = ai(i, k) * tr + ar(i, k) * ti;
          br(i) += prodr;
          bi(i) += prodi;
        }
    }
  // FEM_DO_SAFE(kb, 1, nm1)
  for (integer kb = 1; kb <= nm1; ++kb)
    {
      km1 = n - kb;
      k = km1 + 1;
      den = ar(k, k) * ar(k, k) + ai(k, k) * ai(k, k);
      prodr = br(k) * ar(k, k) + bi(k) * ai(k, k);
      prodi = bi(k) * ar(k, k) - br(k) * ai(k, k);
      br(k) = prodr / den;
      bi(k) = prodi / den;
      tr = -br(k);
      ti = -bi(k);
      // FEM_DO_SAFE(i, 1, km1)
      for (integer i = 1; i <= km1; ++i)
        {
          prodr = ar(i, k) * tr - ai(i, k) * ti;
          prodi = ai(i, k) * tr + ar(i, k) * ti;
          br(i) += prodr;
          bi(i) += prodi;
        }
    }
statement_50:
  den = ar(1, 1) * ar(1, 1) + ai(1, 1) * ai(1, 1);
  prodr = br(1) * ar(1, 1) + bi(1) * ai(1, 1);
  prodi = bi(1) * ar(1, 1) - br(1) * ai(1, 1);
  br(1) = prodr / den;
  bi(1) = prodi / den;
  //C----------------------- END OF SUBROUTINE SOLC ------------------------
}

void decsol::solc(const integer & n,
                  const integer & ndim,
                  const CFortranAccess< CMatrix< doublereal > > & ar,
                  const CFortranAccess< CMatrix< doublereal > > & ai,
                  doublereal & br,
                  doublereal & bi,
                  const CVectorCore< integer > & ip)
{
  CVectorCore< doublereal > Br(1, &br);
  CVectorCore< doublereal > Bi(1, &bi);
  solc(n, ndim, ar, ai, Br, Bi, ip);
}

void decsol::dechc(const integer & n,
                   const integer & ndim,
                   CFortranAccess< CMatrix< doublereal > > & ar,
                   CFortranAccess< CMatrix< doublereal > > & ai,
                   const integer & lb,
                   CVectorCore< integer > & ip,
                   int & ier)
{
  integer nm1 = 0;
  integer k = 0;
  integer kp1 = 0;
  integer m = 0;
  integer na = 0;
  integer i = 0;
  doublereal tr = 0.0;
  doublereal ti = 0.0;
  doublereal den = 0.0;
  doublereal prodr = 0.0;
  doublereal prodi = 0.0;
  integer j = 0;
  //C VERSION COMPLEX DOUBLE PRECISION
  //C-----------------------------------------------------------------------
  //C  MATRIX TRIANGULARIZATION BY GAUSSIAN ELIMINATION
  //C  ------ MODIFICATION FOR COMPLEX MATRICES --------
  //C  INPUT..
  //C     N = ORDER OF MATRIX.
  //C     NDIM = DECLARED DIMENSION OF ARRAYS  AR AND AI .
  //C     (AR, AI) = MATRIX TO BE TRIANGULARIZED.
  //C  OUTPUT..
  //C     AR(I,J), I.LE.J = UPPER TRIANGULAR FACTOR, U ; REAL PART.
  //C     AI(I,J), I.LE.J = UPPER TRIANGULAR FACTOR, U ; IMAGINARY PART.
  //C     AR(I,J), I.GT.J = MULTIPLIERS = LOWER TRIANGULAR FACTOR, I - L.
  //C                                                    REAL PART.
  //C     AI(I,J), I.GT.J = MULTIPLIERS = LOWER TRIANGULAR FACTOR, I - L.
  //C                                                    IMAGINARY PART.
  //C     LB = LOWER BANDWIDTH OF A (DIAGONAL NOT COUNTED), LB.GE.1.
  //C     IP(K), K.LT.N = INDEX OF K-TH PIVOT ROW.
  //C     IP(N) = (-1)**(NUMBER OF INTERCHANGES) OR O .
  //C     IER = 0 IF MATRIX A IS NONSINGULAR, OR K IF FOUND TO BE
  //C           SINGULAR AT STAGE K.
  //C  USE  SOL  TO OBTAIN SOLUTION OF LINEAR SYSTEM.
  //C  IF IP(N)=O, A IS SINGULAR, SOL WILL DIVIDE BY ZERO.
  //C
  //C  REFERENCE..
  //C     C. B. MOLER, ALGORITHM 423, LINEAR EQUATION SOLVER,
  //C     C.A.C.M. 15 (1972), P. 274.
  //C-----------------------------------------------------------------------
  ier = 0;
  ip(n) = 1;
  if (lb == 0)
    {
      goto statement_70;
    }
  if (n == 1)
    {
      goto statement_70;
    }
  nm1 = n - 1;
  // FEM_DO_SAFE(k, 1, nm1)
  for (integer k = 1; k <= nm1; ++k)
    {
      kp1 = k + 1;
      m = k;
      na = std::min(n, lb + k);
      // FEM_DO_SAFE(i, kp1, na)
      for (integer i = kp1; i <= na; ++i)
        {
          if (std::abs(ar(i, k)) + std::abs(ai(i, k)) > std::abs(ar(m,
                                                                    k))
                                                          + std::abs(ai(m, k)))
            {
              m = i;
            }
        }
      ip(k) = m;
      tr = ar(m, k);
      ti = ai(m, k);
      if (m == k)
        {
          goto statement_20;
        }
      ip(n) = -ip(n);
      ar(m, k) = ar(k, k);
      ai(m, k) = ai(k, k);
      ar(k, k) = tr;
      ai(k, k) = ti;
    statement_20:
      if (std::abs(tr) + std::abs(ti) == 0.e0)
        {
          goto statement_80;
        }
      den = tr * tr + ti * ti;
      tr = tr / den;
      ti = -ti / den;
      // FEM_DO_SAFE(i, kp1, na)
      for (integer i = kp1; i <= na; ++i)
        {
          prodr = ar(i, k) * tr - ai(i, k) * ti;
          prodi = ai(i, k) * tr + ar(i, k) * ti;
          ar(i, k) = -prodr;
          ai(i, k) = -prodi;
        }
      // FEM_DO_SAFE(j, kp1, n)
      for (integer j = kp1; j <= n; ++j)
        {
          tr = ar(m, j);
          ti = ai(m, j);
          ar(m, j) = ar(k, j);
          ai(m, j) = ai(k, j);
          ar(k, j) = tr;
          ai(k, j) = ti;
          if (std::abs(tr) + std::abs(ti) == 0.e0)
            {
              goto statement_48;
            }
          if (ti == 0.e0)
            {
              // FEM_DO_SAFE(i, kp1, na)
              for (integer i = kp1; i <= na; ++i)
                {
                  prodr = ar(i, k) * tr;
                  prodi = ai(i, k) * tr;
                  ar(i, j) += prodr;
                  ai(i, j) += prodi;
                }
              goto statement_48;
            }
          if (tr == 0.e0)
            {
              // FEM_DO_SAFE(i, kp1, na)
              for (integer i = kp1; i <= na; ++i)
                {
                  prodr = -ai(i, k) * ti;
                  prodi = ar(i, k) * ti;
                  ar(i, j) += prodr;
                  ai(i, j) += prodi;
                }
              goto statement_48;
            }
          // FEM_DO_SAFE(i, kp1, na)
          for (integer i = kp1; i <= na; ++i)
            {
              prodr = ar(i, k) * tr - ai(i, k) * ti;
              prodi = ai(i, k) * tr + ar(i, k) * ti;
              ar(i, j) += prodr;
              ai(i, j) += prodi;
            }
        statement_48:;
        }
    }
statement_70:
  k = n;
  if (std::abs(ar(n, n)) + std::abs(ai(n, n)) == 0.e0)
    {
      goto statement_80;
    }
  return;
statement_80:
  ier = k;
  ip(n) = 0;
  //C----------------------- END OF SUBROUTINE DECHC -----------------------
}

void decsol::solhc(const integer & n,
                   const integer & ndim,
                   const CFortranAccess< CMatrix< doublereal > > & ar,
                   const CFortranAccess< CMatrix< doublereal > > & ai,
                   const integer & lb,
                   CVectorCore< doublereal > & br,
                   CVectorCore< doublereal > & bi,
                   const CVectorCore< integer > & ip)
{
  integer nm1 = 0;
  integer k = 0;
  integer kp1 = 0;
  integer m = 0;
  doublereal tr = 0.0;
  doublereal ti = 0.0;
  integer i = 0;
  doublereal prodr = 0.0;
  doublereal prodi = 0.0;
  integer kb = 0;
  integer km1 = 0;
  doublereal den = 0.0;
  //C VERSION COMPLEX DOUBLE PRECISION
  //C-----------------------------------------------------------------------
  //C  SOLUTION OF LINEAR SYSTEM, A*X = B .
  //C  INPUT..
  //C    N = ORDER OF MATRIX.
  //C    NDIM = DECLARED DIMENSION OF ARRAYS  AR AND AI.
  //C    (AR,AI) = TRIANGULARIZED MATRIX OBTAINED FROM DEC.
  //C    (BR,BI) = RIGHT HAND SIDE VECTOR.
  //C    LB = LOWER BANDWIDTH OF A.
  //C    IP = PIVOT VECTOR OBTAINED FROM DEC.
  //C  DO NOT USE IF DEC HAS SET IER .NE. 0.
  //C  OUTPUT..
  //C    (BR,BI) = SOLUTION VECTOR, X .
  //C-----------------------------------------------------------------------
  if (n == 1)
    {
      goto statement_50;
    }
  nm1 = n - 1;
  if (lb == 0)
    {
      goto statement_25;
    }
  // FEM_DO_SAFE(k, 1, nm1)
  for (integer k = 1; k <= nm1; ++k)
    {
      kp1 = k + 1;
      m = ip(k);
      tr = br(m);
      ti = bi(m);
      br(m) = br(k);
      bi(m) = bi(k);
      br(k) = tr;
      bi(k) = ti;
      // FEM_DO_SAFE(i, kp1, std::min(n, lb + k))
      for (integer i = kp1; i <= std::min(n, lb + k); ++i)
        {
          prodr = ar(i, k) * tr - ai(i, k) * ti;
          prodi = ai(i, k) * tr + ar(i, k) * ti;
          br(i) += prodr;
          bi(i) += prodi;
        }
    }
statement_25:
  // FEM_DO_SAFE(kb, 1, nm1)
  for (integer kb = 1; kb <= nm1; ++kb)
    {
      km1 = n - kb;
      k = km1 + 1;
      den = ar(k, k) * ar(k, k) + ai(k, k) * ai(k, k);
      prodr = br(k) * ar(k, k) + bi(k) * ai(k, k);
      prodi = bi(k) * ar(k, k) - br(k) * ai(k, k);
      br(k) = prodr / den;
      bi(k) = prodi / den;
      tr = -br(k);
      ti = -bi(k);
      // FEM_DO_SAFE(i, 1, km1)
      for (integer i = 1; i <= km1; ++i)
        {
          prodr = ar(i, k) * tr - ai(i, k) * ti;
          prodi = ai(i, k) * tr + ar(i, k) * ti;
          br(i) += prodr;
          bi(i) += prodi;
        }
    }
statement_50:
  den = ar(1, 1) * ar(1, 1) + ai(1, 1) * ai(1, 1);
  prodr = br(1) * ar(1, 1) + bi(1) * ai(1, 1);
  prodi = bi(1) * ar(1, 1) - br(1) * ai(1, 1);
  br(1) = prodr / den;
  bi(1) = prodi / den;
  //C----------------------- END OF SUBROUTINE SOLHC -----------------------
}

void decsol::decb(const integer & n,
                  const integer & ndim,
                  CFortranAccess< CMatrix< doublereal > > & a,
                  const integer & ml,
                  const integer & mu,
                  CVectorCore< integer > & ip,
                  int & ier)
{
  integer md = 0;
  integer md1 = 0;
  integer ju = 0;
  integer j = 0;
  integer i = 0;
  integer nm1 = 0;
  integer k = 0;
  integer kp1 = 0;
  integer m = 0;
  integer mdl = 0;
  doublereal t = 0.0;
  integer mm = 0;
  integer jk = 0;
  integer ijk = 0;
  //C-----------------------------------------------------------------------
  //C  MATRIX TRIANGULARIZATION BY GAUSSIAN ELIMINATION OF A BANDED
  //C  MATRIX WITH LOWER BANDWIDTH ML AND UPPER BANDWIDTH MU
  //C  INPUT..
  //C     N       ORDER OF THE ORIGINAL MATRIX A.
  //C     NDIM    DECLARED DIMENSION OF ARRAY  A.
  //C     A       CONTAINS THE MATRIX IN BAND STORAGE.   THE COLUMNS
  //C                OF THE MATRIX ARE STORED IN THE COLUMNS OF  A  AND
  //C                THE DIAGONALS OF THE MATRIX ARE STORED IN ROWS
  //C                ML+1 THROUGH 2*ML+MU+1 OF  A.
  //C     ML      LOWER BANDWIDTH OF A (DIAGONAL IS NOT COUNTED).
  //C     MU      UPPER BANDWIDTH OF A (DIAGONAL IS NOT COUNTED).
  //C  OUTPUT..
  //C     A       AN UPPER TRIANGULAR MATRIX IN BAND STORAGE AND
  //C                THE MULTIPLIERS WHICH WERE USED TO OBTAIN IT.
  //C     IP      INDEX VECTOR OF PIVOT INDICES.
  //C     IP(N)   (-1)**(NUMBER OF INTERCHANGES) OR O .
  //C     IER     = 0 IF MATRIX A IS NONSINGULAR, OR  = K IF FOUND TO BE
  //C                SINGULAR AT STAGE K.
  //C  USE  SOLB  TO OBTAIN SOLUTION OF LINEAR SYSTEM.
  //C  DETERM(A) = IP(N)*A(MD,1)*A(MD,2)*...*A(MD,N)  WITH MD=ML+MU+1.
  //C  IF IP(N)=O, A IS SINGULAR, SOLB WILL DIVIDE BY ZERO.
  //C
  //C  REFERENCE..
  //C     THIS IS A MODIFICATION OF
  //C     C. B. MOLER, ALGORITHM 423, LINEAR EQUATION SOLVER,
  //C     C.A.C.M. 15 (1972), P. 274.
  //C-----------------------------------------------------------------------
  ier = 0;
  ip(n) = 1;
  md = ml + mu + 1;
  md1 = md + 1;
  ju = 0;
  if (ml == 0)
    {
      goto statement_70;
    }
  if (n == 1)
    {
      goto statement_70;
    }
  if (n < mu + 2)
    {
      goto statement_7;
    }
  // FEM_DO_SAFE(j, mu + 2, n)
  for (integer j = mu + 2; j <= n; ++j)
    {
      // FEM_DO_SAFE(i, 1, ml)
      for (integer i = 1; i <= ml; ++i)
        {
          a(i, j) = 0.e0;
        }
    }
statement_7:
  nm1 = n - 1;
  // FEM_DO_SAFE(k, 1, nm1)
  for (integer k = 1; k <= nm1; ++k)
    {
      kp1 = k + 1;
      m = md;
      mdl = std::min(ml, n - k) + md;
      // FEM_DO_SAFE(i, md1, mdl)
      for (integer i = md1; i <= mdl; ++i)
        {
          if (std::abs(a(i, k)) > std::abs(a(m, k)))
            {
              m = i;
            }
        }
      ip(k) = m + k - md;
      t = a(m, k);
      if (m == md)
        {
          goto statement_20;
        }
      ip(n) = -ip(n);
      a(m, k) = a(md, k);
      a(md, k) = t;
    statement_20:
      if (t == 0.e0)
        {
          goto statement_80;
        }
      t = 1.e0 / t;
      // FEM_DO_SAFE(i, md1, mdl)
      for (integer i = md1; i <= mdl; ++i)
        {
          a(i, k) = -a(i, k) * t;
        }
      ju = std::min(std::max(ju, mu + ip(k)), n);
      mm = md;
      if (ju < kp1)
        {
          goto statement_55;
        }
      // FEM_DO_SAFE(j, kp1, ju)
      for (integer j = kp1; j <= ju; ++j)
        {
          m = m - 1;
          mm = mm - 1;
          t = a(m, j);
          if (m == mm)
            {
              goto statement_35;
            }
          a(m, j) = a(mm, j);
          a(mm, j) = t;
        statement_35:
          if (t == 0.e0)
            {
              goto statement_45;
            }
          jk = j - k;
          // FEM_DO_SAFE(i, md1, mdl)
          for (integer i = md1; i <= mdl; ++i)
            {
              ijk = i - jk;
              a(ijk, j) += a(i, k) * t;
            }
        statement_45:;
        }
    statement_55:;
    }
statement_70:
  k = n;
  if (a(md, n) == 0.e0)
    {
      goto statement_80;
    }
  return;
statement_80:
  ier = k;
  ip(n) = 0;
  //C----------------------- END OF SUBROUTINE DECB ------------------------
}

void decsol::solb(const integer & n,
                  const integer & ndim,
                  const CFortranAccess< CMatrix< doublereal > > & a,
                  const integer & ml,
                  const integer & mu,
                  CVectorCore< doublereal > & b,
                  const CVectorCore< integer > & ip)
{
  integer md = 0;
  integer md1 = 0;
  integer mdm = 0;
  integer nm1 = 0;
  integer k = 0;
  integer m = 0;
  doublereal t = 0.0;
  integer mdl = 0;
  integer i = 0;
  integer imd = 0;
  integer kb = 0;
  integer kmd = 0;
  integer lm = 0;
  //C-----------------------------------------------------------------------
  //C  SOLUTION OF LINEAR SYSTEM, A*X = B .
  //C  INPUT..
  //C    N      ORDER OF MATRIX A.
  //C    NDIM   DECLARED DIMENSION OF ARRAY  A .
  //C    A      TRIANGULARIZED MATRIX OBTAINED FROM DECB.
  //C    ML     LOWER BANDWIDTH OF A (DIAGONAL IS NOT COUNTED).
  //C    MU     UPPER BANDWIDTH OF A (DIAGONAL IS NOT COUNTED).
  //C    B      RIGHT HAND SIDE VECTOR.
  //C    IP     PIVOT VECTOR OBTAINED FROM DECB.
  //C  DO NOT USE IF DECB HAS SET IER .NE. 0.
  //C  OUTPUT..
  //C    B      SOLUTION VECTOR, X .
  //C-----------------------------------------------------------------------
  md = ml + mu + 1;
  md1 = md + 1;
  mdm = md - 1;
  nm1 = n - 1;
  if (ml == 0)
    {
      goto statement_25;
    }
  if (n == 1)
    {
      goto statement_50;
    }
  // FEM_DO_SAFE(k, 1, nm1)
  for (integer k = 1; k <= nm1; ++k)
    {
      m = ip(k);
      t = b(m);
      b(m) = b(k);
      b(k) = t;
      mdl = std::min(ml, n - k) + md;
      // FEM_DO_SAFE(i, md1, mdl)
      for (integer i = md1; i <= mdl; ++i)
        {
          imd = i + k - md;
          b(imd) += a(i, k) * t;
        }
    }
statement_25:
  // FEM_DO_SAFE(kb, 1, nm1)
  for (integer kb = 1; kb <= nm1; ++kb)
    {
      k = n + 1 - kb;
      b(k) = b(k) / a(md, k);
      t = -b(k);
      kmd = md - k;
      lm = std::max(1, kmd + 1);
      // FEM_DO_SAFE(i, lm, mdm)
      for (integer i = lm; i <= mdm; ++i)
        {
          imd = i - kmd;
          b(imd) += a(i, k) * t;
        }
    }
statement_50:
  b(1) = b(1) / a(md, 1);
  //C----------------------- END OF SUBROUTINE SOLB ------------------------
}

void decsol::solb(const integer & n,
                  const integer & ndim,
                  const CFortranAccess< CMatrix< doublereal > > & a,
                  const integer & ml,
                  const integer & mu,
                  doublereal & b,
                  const CVectorCore< integer > & ip)
{
  CVectorCore< doublereal > B(n, &b);
  solb(n, ndim, a, ml, mu, B, ip);
}

void decsol::decbc(const integer & n,
                   const integer & ndim,
                   CFortranAccess< CMatrix< doublereal > > & ar,
                   CFortranAccess< CMatrix< doublereal > > & ai,
                   const integer & ml,
                   const integer & mu,
                   CVectorCore< integer > & ip,
                   int & ier)
{
  integer md = 0;
  integer md1 = 0;
  integer ju = 0;
  integer j = 0;
  integer i = 0;
  integer nm1 = 0;
  integer k = 0;
  integer kp1 = 0;
  integer m = 0;
  integer mdl = 0;
  doublereal tr = 0.0;
  doublereal ti = 0.0;
  doublereal den = 0.0;
  doublereal prodr = 0.0;
  doublereal prodi = 0.0;
  integer mm = 0;
  integer jk = 0;
  integer ijk = 0;
  //C-----------------------------------------------------------------------
  //C  MATRIX TRIANGULARIZATION BY GAUSSIAN ELIMINATION OF A BANDED COMPLEX
  //C  MATRIX WITH LOWER BANDWIDTH ML AND UPPER BANDWIDTH MU
  //C  INPUT..
  //C     N       ORDER OF THE ORIGINAL MATRIX A.
  //C     NDIM    DECLARED DIMENSION OF ARRAY  A.
  //C     AR, AI     CONTAINS THE MATRIX IN BAND STORAGE.   THE COLUMNS
  //C                OF THE MATRIX ARE STORED IN THE COLUMNS OF  AR (REAL
  //C                PART) AND AI (IMAGINARY PART)  AND
  //C                THE DIAGONALS OF THE MATRIX ARE STORED IN ROWS
  //C                ML+1 THROUGH 2*ML+MU+1 OF  AR AND AI.
  //C     ML      LOWER BANDWIDTH OF A (DIAGONAL IS NOT COUNTED).
  //C     MU      UPPER BANDWIDTH OF A (DIAGONAL IS NOT COUNTED).
  //C  OUTPUT..
  //C     AR, AI  AN UPPER TRIANGULAR MATRIX IN BAND STORAGE AND
  //C                THE MULTIPLIERS WHICH WERE USED TO OBTAIN IT.
  //C     IP      INDEX VECTOR OF PIVOT INDICES.
  //C     IP(N)   (-1)**(NUMBER OF INTERCHANGES) OR O .
  //C     IER     = 0 IF MATRIX A IS NONSINGULAR, OR  = K IF FOUND TO BE
  //C                SINGULAR AT STAGE K.
  //C  USE  SOLBC  TO OBTAIN SOLUTION OF LINEAR SYSTEM.
  //C  DETERM(A) = IP(N)*A(MD,1)*A(MD,2)*...*A(MD,N)  WITH MD=ML+MU+1.
  //C  IF IP(N)=O, A IS SINGULAR, SOLBC WILL DIVIDE BY ZERO.
  //C
  //C  REFERENCE..
  //C     THIS IS A MODIFICATION OF
  //C     C. B. MOLER, ALGORITHM 423, LINEAR EQUATION SOLVER,
  //C     C.A.C.M. 15 (1972), P. 274.
  //C-----------------------------------------------------------------------
  ier = 0;
  ip(n) = 1;
  md = ml + mu + 1;
  md1 = md + 1;
  ju = 0;
  if (ml == 0)
    {
      goto statement_70;
    }
  if (n == 1)
    {
      goto statement_70;
    }
  if (n < mu + 2)
    {
      goto statement_7;
    }
  // FEM_DO_SAFE(j, mu + 2, n)
  for (integer j = mu + 2; j <= n; ++j)
    {
      // FEM_DO_SAFE(i, 1, ml)
      for (integer i = 1; i <= ml; ++i)
        {
          ar(i, j) = 0.e0;
          ai(i, j) = 0.e0;
        }
    }
statement_7:
  nm1 = n - 1;
  // FEM_DO_SAFE(k, 1, nm1)
  for (integer k = 1; k <= nm1; ++k)
    {
      kp1 = k + 1;
      m = md;
      mdl = std::min(ml, n - k) + md;
      // FEM_DO_SAFE(i, md1, mdl)
      for (integer i = md1; i <= mdl; ++i)
        {
          if (std::abs(ar(i, k)) + std::abs(ai(i, k)) > std::abs(ar(m,
                                                                    k))
                                                          + std::abs(ai(m, k)))
            {
              m = i;
            }
        }
      ip(k) = m + k - md;
      tr = ar(m, k);
      ti = ai(m, k);
      if (m == md)
        {
          goto statement_20;
        }
      ip(n) = -ip(n);
      ar(m, k) = ar(md, k);
      ai(m, k) = ai(md, k);
      ar(md, k) = tr;
      ai(md, k) = ti;
    statement_20:
      if (std::abs(tr) + std::abs(ti) == 0.e0)
        {
          goto statement_80;
        }
      den = tr * tr + ti * ti;
      tr = tr / den;
      ti = -ti / den;
      // FEM_DO_SAFE(i, md1, mdl)
      for (integer i = md1; i <= mdl; ++i)
        {
          prodr = ar(i, k) * tr - ai(i, k) * ti;
          prodi = ai(i, k) * tr + ar(i, k) * ti;
          ar(i, k) = -prodr;
          ai(i, k) = -prodi;
        }
      ju = std::min(std::max(ju, mu + ip(k)), n);
      mm = md;
      if (ju < kp1)
        {
          goto statement_55;
        }
      // FEM_DO_SAFE(j, kp1, ju)
      for (integer j = kp1; j <= ju; ++j)
        {
          m = m - 1;
          mm = mm - 1;
          tr = ar(m, j);
          ti = ai(m, j);
          if (m == mm)
            {
              goto statement_35;
            }
          ar(m, j) = ar(mm, j);
          ai(m, j) = ai(mm, j);
          ar(mm, j) = tr;
          ai(mm, j) = ti;
        statement_35:
          if (std::abs(tr) + std::abs(ti) == 0.e0)
            {
              goto statement_48;
            }
          jk = j - k;
          if (ti == 0.e0)
            {
              // FEM_DO_SAFE(i, md1, mdl)
              for (integer i = md1; i <= mdl; ++i)
                {
                  ijk = i - jk;
                  prodr = ar(i, k) * tr;
                  prodi = ai(i, k) * tr;
                  ar(ijk, j) += prodr;
                  ai(ijk, j) += prodi;
                }
              goto statement_48;
            }
          if (tr == 0.e0)
            {
              // FEM_DO_SAFE(i, md1, mdl)
              for (integer i = md1; i <= mdl; ++i)
                {
                  ijk = i - jk;
                  prodr = -ai(i, k) * ti;
                  prodi = ar(i, k) * ti;
                  ar(ijk, j) += prodr;
                  ai(ijk, j) += prodi;
                }
              goto statement_48;
            }
          // FEM_DO_SAFE(i, md1, mdl)
          for (integer i = md1; i <= mdl; ++i)
            {
              ijk = i - jk;
              prodr = ar(i, k) * tr - ai(i, k) * ti;
              prodi = ai(i, k) * tr + ar(i, k) * ti;
              ar(ijk, j) += prodr;
              ai(ijk, j) += prodi;
            }
        statement_48:;
        }
    statement_55:;
    }
statement_70:
  k = n;
  if (std::abs(ar(md, n)) + std::abs(ai(md, n)) == 0.e0)
    {
      goto statement_80;
    }
  return;
statement_80:
  ier = k;
  ip(n) = 0;
  //C----------------------- END OF SUBROUTINE DECBC ------------------------
}

void decsol::solbc(const integer & n,
                   const integer & ndim,
                   const CFortranAccess< CMatrix< doublereal > > & ar,
                   const CFortranAccess< CMatrix< doublereal > > & ai,
                   const integer & ml,
                   const integer & mu,
                   CVectorCore< doublereal > & br,
                   CVectorCore< doublereal > & bi,
                   const CVectorCore< integer > & ip)
{
  integer md = 0;
  integer md1 = 0;
  integer mdm = 0;
  integer nm1 = 0;
  integer k = 0;
  integer m = 0;
  doublereal tr = 0.0;
  doublereal ti = 0.0;
  integer mdl = 0;
  integer i = 0;
  integer imd = 0;
  doublereal prodr = 0.0;
  doublereal prodi = 0.0;
  integer kb = 0;
  doublereal den = 0.0;
  integer kmd = 0;
  integer lm = 0;
  //C-----------------------------------------------------------------------
  //C  SOLUTION OF LINEAR SYSTEM, A*X = B ,
  //C                  VERSION BANDED AND COMPLEX-DOUBLE PRECISION.
  //C  INPUT..
  //C    N      ORDER OF MATRIX A.
  //C    NDIM   DECLARED DIMENSION OF ARRAY  A .
  //C    AR, AI TRIANGULARIZED MATRIX OBTAINED FROM DECB (REAL AND IMAG. PART).
  //C    ML     LOWER BANDWIDTH OF A (DIAGONAL IS NOT COUNTED).
  //C    MU     UPPER BANDWIDTH OF A (DIAGONAL IS NOT COUNTED).
  //C    BR, BI RIGHT HAND SIDE VECTOR (REAL AND IMAG. PART).
  //C    IP     PIVOT VECTOR OBTAINED FROM DECBC.
  //C  DO NOT USE IF DECB HAS SET IER .NE. 0.
  //C  OUTPUT..
  //C    BR, BI SOLUTION VECTOR, X (REAL AND IMAG. PART).
  //C-----------------------------------------------------------------------
  md = ml + mu + 1;
  md1 = md + 1;
  mdm = md - 1;
  nm1 = n - 1;
  if (ml == 0)
    {
      goto statement_25;
    }
  if (n == 1)
    {
      goto statement_50;
    }
  // FEM_DO_SAFE(k, 1, nm1)
  for (integer k = 1; k <= nm1; ++k)
    {
      m = ip(k);
      tr = br(m);
      ti = bi(m);
      br(m) = br(k);
      bi(m) = bi(k);
      br(k) = tr;
      bi(k) = ti;
      mdl = std::min(ml, n - k) + md;
      // FEM_DO_SAFE(i, md1, mdl)
      for (integer i = md1; i <= mdl; ++i)
        {
          imd = i + k - md;
          prodr = ar(i, k) * tr - ai(i, k) * ti;
          prodi = ai(i, k) * tr + ar(i, k) * ti;
          br(imd) += prodr;
          bi(imd) += prodi;
        }
    }
statement_25:
  // FEM_DO_SAFE(kb, 1, nm1)
  for (integer kb = 1; kb <= nm1; ++kb)
    {
      k = n + 1 - kb;
      den = ar(md, k) * ar(md, k) + ai(md, k) * ai(md, k);
      prodr = br(k) * ar(md, k) + bi(k) * ai(md, k);
      prodi = bi(k) * ar(md, k) - br(k) * ai(md, k);
      br(k) = prodr / den;
      bi(k) = prodi / den;
      tr = -br(k);
      ti = -bi(k);
      kmd = md - k;
      lm = std::max(1, kmd + 1);
      // FEM_DO_SAFE(i, lm, mdm)
      for (integer i = lm; i <= mdm; ++i)
        {
          imd = i - kmd;
          prodr = ar(i, k) * tr - ai(i, k) * ti;
          prodi = ai(i, k) * tr + ar(i, k) * ti;
          br(imd) += prodr;
          bi(imd) += prodi;
        }
    }
  den = ar(md, 1) * ar(md, 1) + ai(md, 1) * ai(md, 1);
  prodr = br(1) * ar(md, 1) + bi(1) * ai(md, 1);
  prodi = bi(1) * ar(md, 1) - br(1) * ai(md, 1);
  br(1) = prodr / den;
  bi(1) = prodi / den;
statement_50:;
  //C----------------------- END OF SUBROUTINE SOLBC ------------------------
}

void decsol::solbc(const integer & n,
                   const integer & ndim,
                   const CFortranAccess< CMatrix< doublereal > > & ar,
                   const CFortranAccess< CMatrix< doublereal > > & ai,
                   const integer & ml,
                   const integer & mu,
                   doublereal & br,
                   doublereal & bi,
                   const CVectorCore< integer > & ip)
{
  CVectorCore< doublereal > Br(n, &br);
  CVectorCore< doublereal > Bi(n, &bi);
  solbc(n, ndim, ar, ai, ml, mu, Br, Bi, ip);
}

void decsol::elmhes(const integer & nm,
                    const integer & n,
                    const integer & low,
                    const integer & igh,
                    CFortranAccess< CMatrix< doublereal > > & a,
                    CVectorCore< integer > & identifier_int)
{
  integer la = 0;
  integer kp1 = 0;
  integer m = 0;
  integer mm1 = 0;
  doublereal x = 0.0;
  integer i = 0;
  integer j = 0;
  doublereal y = 0.0;
  integer mp1 = 0;
  //C
  //C     this subroutine is a translation of the algol procedure elmhes,
  //C     num. math. 12, 349-368(1968) by martin and wilkinson.
  //C     handbook for auto. comp., vol.ii-linear algebra, 339-358(1971).
  //C
  //C     given a real general matrix, this subroutine
  //C     reduces a submatrix situated in rows and columns
  //C     low through igh to upper hessenberg form by
  //C     stabilized elementary similarity transformations.
  //C
  //C     on input:
  //C
  //C      nm must be set to the row dimension of two-dimensional
  //C        array parameters as declared in the calling program
  //C        dimension statement;
  //C
  //C      n is the order of the matrix;
  //C
  //C      low and igh are integers determined by the balancing
  //C        subroutine  balanc.      if  balanc  has not been used,
  //C        set low=1, igh=n;
  //C
  //C      a contains the input matrix.
  //C
  //C     on output:
  //C
  //C      a contains the hessenberg matrix.  the multipliers
  //C        which were used in the reduction are stored in the
  //C        remaining triangle under the hessenberg matrix;
  //C
  //C      int contains information on the rows and columns
  //C        interchanged in the reduction.
  //C        only elements low through igh are used.
  //C
  //C     questions and comments should be directed to b. s. garbow,
  //C     applied mathematics division, argonne national laboratory
  //C
  //C     ------------------------------------------------------------------
  //C
  la = igh - 1;
  kp1 = low + 1;
  if (la < kp1)
    {
      goto statement_200;
    }
  //C
  // FEM_DO_SAFE(m, kp1, la)
  for (integer m = kp1; m <= la; ++m)
    {
      mm1 = m - 1;
      x = 0.0e0;
      i = m;
      //C
      // FEM_DO_SAFE(j, m, igh)
      for (integer j = m; j <= igh; ++j)
        {
          if (std::abs(a(j, mm1)) <= std::abs(x))
            {
              goto statement_100;
            }
          x = a(j, mm1);
          i = j;
        statement_100:;
        }
      //C
      identifier_int(m) = i;
      if (i == m)
        {
          goto statement_130;
        }
      //C    :::::::::: interchange rows and columns of a ::::::::::
      // FEM_DO_SAFE(j, mm1, n)
      for (integer j = mm1; j <= n; ++j)
        {
          y = a(i, j);
          a(i, j) = a(m, j);
          a(m, j) = y;
        }
      //C
      // FEM_DO_SAFE(j, 1, igh)
      for (integer j = 1; j <= igh; ++j)
        {
          y = a(j, i);
          a(j, i) = a(j, m);
          a(j, m) = y;
        }
    //C    :::::::::: end interchange ::::::::::
    statement_130:
      if (x == 0.0e0)
        {
          goto statement_180;
        }
      mp1 = m + 1;
      //C
      // FEM_DO_SAFE(i, mp1, igh)
      for (integer i = mp1; i <= igh; ++i)
        {
          y = a(i, mm1);
          if (y == 0.0e0)
            {
              goto statement_160;
            }
          y = y / x;
          a(i, mm1) = y;
          //C
          // FEM_DO_SAFE(j, m, n)
          for (integer j = m; j <= n; ++j)
            {
              a(i, j) = a(i, j) - y * a(m, j);
            }
          //C
          // FEM_DO_SAFE(j, 1, igh)
          for (integer j = 1; j <= igh; ++j)
            {
              a(j, m) += y * a(j, i);
            }
        //C
        statement_160:;
        }
    //C
    statement_180:;
    }
//C
statement_200:;
  //C    :::::::::: last card of elmhes ::::::::::
}
