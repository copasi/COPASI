// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <cfloat>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>

#include "copasi/optimization/CPraxis.h"

#include "copasi/randomGenerator/CRandom.h"

CPraxis::CPraxis():
  mpRandom(NULL)
{
  mpRandom = CRandom::createGenerator();
}

CPraxis::~CPraxis()
{
  if (mpRandom != NULL)
    delete mpRandom;
}

//****************************************************************************80

C_FLOAT64 CPraxis::flin(C_INT32 n, C_INT32 jsearch, C_FLOAT64 l, FPraxis * f, C_FLOAT64 x[], C_INT32 & nf, C_FLOAT64 v[], C_FLOAT64 q0[], C_FLOAT64 q1[], C_FLOAT64 & qd0, C_FLOAT64 & qd1, C_FLOAT64 & qa, C_FLOAT64 & qb, C_FLOAT64 & qc)

//****************************************************************************80
//
//  Purpose:
//
//    FLIN is the function of one variable to be minimized by MINNY.
//
//  Discussion:
//
//    F(X) is a scalar function of a vector argument X.
//
//    A minimizer of F(X) is sought along a line or parabola.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    04 August 2016
//
//  Author:
//
//    Original FORTRAN77 version by Richard Brent.
//    C++ version by John Burkardt.
//
//  Reference:
//
//    Richard Brent,
//    Algorithms for Minimization with Derivatives,
//    Prentice Hall, 1973,
//    ReprC_INT32ed by Dover, 2002.
//
//  Parameters:
//
//    Input, C_INT32 N, the number of variables.
//
//    Input, C_INT32 JSEARCH, indicates the kind of search.
//    If JSEARCH is a legal column index, linear search along V(*,JSEARCH).
//    If JSEARCH is -1, then the search is parabolic, based on X, Q0 and Q1.
//
//    Input, C_FLOAT64 L, is the parameter determining the particular
//    poC_INT32 at which F is to be evaluated.
//    For a linear search, L is the step size.
//    For a quadratic search, L is a parameter which specifies
//    a poC_INT32 in the plane of X, Q0 and Q1.
//
//    Input, C_FLOAT64 F (C_FLOAT64 X[], C_INT32 N ), the function to be minimized.
//
//    Input, C_FLOAT64 X[N], the base poC_INT32 of the search.
//
//    Input/output, C_INT32 &NF, the function evaluation counter.
//
//    Input, C_FLOAT64 V[N,N], a matrix whose columns constitute
//    search directions.
//
//    Input, C_FLOAT64 Q0[N], Q1[N], two auxiliary poC_INT32s used to
//    determine the plane when a quadratic search is performed.
//
//    Input, C_FLOAT64 &QD0, &QD1, values needed to compute the
//    coefficients QA, QB, QC.
//
//    Output, C_FLOAT64 &QA, &QB, &QC, coefficients used to combine
//    Q0, X, and A1 if a quadratic search is used.
//
//    Output, C_FLOAT64 FLIN, the value of the function at the
//    minimizing poC_INT32.
//
{
  C_INT32 i;
  C_FLOAT64 * t;
  C_FLOAT64 value;

  t = new C_FLOAT64[n];

  //
  //  The search is linear.
  //
  if (0 <= jsearch)
    {
      for (i = 0; i < n; i++)
        {
          t[i] = x[i] + l * v[i + jsearch * n];
        }
    }
  //
  //  The search is along a parabolic space curve.
  //
  else
    {
      qa = l * (l - qd1) / (qd0 + qd1) / qd0;
      qb = -(l + qd0) * (l - qd1) / qd1 / qd0;
      qc = (l + qd0) * l / qd1 / (qd0 + qd1);

      for (i = 0; i < n; i++)
        {
          t[i] = qa * q0[i] + qb * x[i] + qc * q1[i];
        }
    }

  //
  //  The function evaluation counter NF is incremented.
  //
  nf = nf + 1;
  //
  //  Evaluate the function.
  //
  value = (*f)(t, n);

  delete[] t;

  return value;
}

//****************************************************************************80

void CPraxis::minfit(C_INT32 n, C_FLOAT64 tol, C_FLOAT64 a[], C_FLOAT64 q[])

//****************************************************************************80
//
//  Purpose:
//
//    MINFIT computes the singular value decomposition of an N by N array.
//
//  Discussion:
//
//    This is an improved version of the EISPACK routine MINFIT
//    restricted to the case M = N and P = 0.
//
//    The singular values of the array A are returned in Q.  A is
//    overwritten with the orthogonal matrix V such that U * diag(Q) = A * V,
//    where U is another orthogonal matrix.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    04 August 2016
//
//  Author:
//
//    Original FORTRAN77 version by Richard Brent.
//    C++ version by John Burkardt.
//
//  Reference:
//
//    Richard Brent,
//    Algorithms for Minimization with Derivatives,
//    Prentice Hall, 1973,
//    ReprC_INT32ed by Dover, 2002.
//
//    James Wilkinson, Christian Reinsch,
//    Handbook for Automatic Computation,
//    Volume II, Linear Algebra, Part 2,
//    Springer Verlag, 1971.
//
//    Brian Smith, James Boyle, Jack Dongarra, Burton Garbow, Yasuhiko Ikebe,
//    Virginia Klema, Cleve Moler,
//    Matrix Eigensystem Routines, EISPACK Guide,
//    Lecture Notes in Computer Science, Volume 6,
//    Springer Verlag, 1976,
//    ISBN13: 978-3540075462,
//    LC: QA193.M37.
//
//  Parameters:
//
//    Input, C_INT32 N, the order of the matrix A.
//
//    Input, C_FLOAT64 TOL, a tolerance which determines when a vector
//    (a column or part of a column of the matrix) may be considered
//    "essentially" equal to zero.
//
//    Input/output, C_FLOAT64 A[N,N].  On input, an N by N array whose
//    singular value decomposition is desired.  On output, the
//    SVD orthogonal matrix factor V.
//
//    Input/output, C_FLOAT64 Q[N], the singular values.
//
{
  C_FLOAT64 c;
  C_FLOAT64 * e;
  C_FLOAT64 eps;
  C_FLOAT64 f;
  C_FLOAT64 g;
  C_FLOAT64 h;
  C_INT32 i;
  C_INT32 ii;
  C_INT32 j;
  C_INT32 jj;
  C_INT32 k;
  C_INT32 kt;
  const C_INT32 kt_max = 30;
  C_INT32 l;
  C_INT32 l2;
  C_FLOAT64 s;
  C_INT32 skip;
  C_FLOAT64 temp;
  C_FLOAT64 x;
  C_FLOAT64 y;
  C_FLOAT64 z;

  //
  //  Householder's reduction to bidiagonal form.
  //
  if (n == 1)
    {
      q[0] = a[0 + 0 * n];
      a[0 + 0 * n] = 1.0;
      return;
    }

  e = new C_FLOAT64[n];

  eps = DBL_EPSILON;
  g = 0.0;
  x = 0.0;

  for (i = 1; i <= n; i++)
    {
      e[i - 1] = g;
      l = i + 1;

      s = 0.0;

      for (ii = i; ii <= n; ii++)
        {
          s = s + a[ii - 1 + (i - 1) * n] * a[ii - 1 + (i - 1) * n];
        }

      g = 0.0;

      if (tol <= s)
        {
          f = a[i - 1 + (i - 1) * n];

          g = sqrt(s);

          if (0.0 <= f)
            {
              g = -g;
            }

          h = f * g - s;
          a[i - 1 + (i - 1) * n] = f - g;

          for (j = l; j <= n; j++)
            {
              f = 0.0;

              for (ii = i; ii <= n; ii++)
                {
                  f = f + a[ii - 1 + (i - 1) * n] * a[ii - 1 + (j - 1) * n];
                }

              f = f / h;

              for (ii = i; ii <= n; ii++)
                {
                  a[ii - 1 + (j - 1) * n] = a[ii - 1 + (j - 1) * n] + f * a[ii - 1 + (i - 1) * n];
                }
            }
        }

      q[i - 1] = g;

      s = 0.0;

      for (j = l; j <= n; j++)
        {
          s = s + a[i - 1 + (j - 1) * n] * a[i - 1 + (j - 1) * n];
        }

      g = 0.0;

      if (tol <= s)
        {
          if (i < n)
            {
              f = a[i - 1 + i * n];
            }

          g = sqrt(s);

          if (0.0 <= f)
            {
              g = -g;
            }

          h = f * g - s;

          if (i < n)
            {
              a[i - 1 + i * n] = f - g;

              for (jj = l; jj <= n; jj++)
                {
                  e[jj - 1] = a[i - 1 + (jj - 1) * n] / h;
                }

              for (j = l; j <= n; j++)
                {
                  s = 0.0;

                  for (jj = l; jj <= n; jj++)
                    {
                      s = s + a[j - 1 + (jj - 1) * n] * a[i - 1 + (jj - 1) * n];
                    }

                  for (jj = l; jj <= n; jj++)
                    {
                      a[j - 1 + (jj - 1) * n] = a[j - 1 + (jj - 1) * n] + s * e[jj - 1];
                    }
                }
            }
        }

      y = fabs(q[i - 1]) + fabs(e[i - 1]);

      x = fmax(x, y);
    }

  //
  //  Accumulation of right-hand transformations.
  //
  a[n - 1 + (n - 1) * n] = 1.0;
  g = e[n - 1];
  l = n;

  for (i = n - 1; 1 <= i; i--)
    {
      if (g != 0.0)
        {
          h = a[i - 1 + i * n] * g;

          for (ii = l; ii <= n; ii++)
            {
              a[ii - 1 + (i - 1) * n] = a[i - 1 + (ii - 1) * n] / h;
            }

          for (j = l; j <= n; j++)
            {
              s = 0.0;

              for (jj = l; jj <= n; jj++)
                {
                  s = s + a[i - 1 + (jj - 1) * n] * a[jj - 1 + (j - 1) * n];
                }

              for (ii = l; ii <= n; ii++)
                {
                  a[ii - 1 + (j - 1) * n] = a[ii - 1 + (j - 1) * n] + s * a[ii - 1 + (i - 1) * n];
                }
            }
        }

      for (jj = l; jj <= n; jj++)
        {
          a[i - 1 + (jj - 1) * n] = 0.0;
        }

      for (ii = l; ii <= n; ii++)
        {
          a[ii - 1 + (i - 1) * n] = 0.0;
        }

      a[i - 1 + (i - 1) * n] = 1.0;

      g = e[i - 1];

      l = i;
    }

  //
  //  Diagonalization of the bidiagonal form.
  //
  eps = eps * x;

  for (k = n; 1 <= k; k--)
    {
      kt = 0;

      for (;;)
        {
          kt = kt + 1;

          if (kt_max < kt)
            {
              e[k - 1] = 0.0;
              std::cerr << "\n";
              std::cerr << "MINFIT - Fatal error!\n";
              std::cerr << "  The QR algorithm failed to converge.\n";
              exit(1);
            }

          skip = 0;

          for (l2 = k; 1 <= l2; l2--)
            {
              l = l2;

              if (fabs(e[l - 1]) <= eps)
                {
                  skip = 1;
                  break;
                }

              if (1 < l)
                {
                  if (fabs(q[l - 2]) <= eps)
                    {
                      break;
                    }
                }
            }

          //
          //  Cancellation of E(L) if 1 < L.
          //
          if (!skip)
            {
              c = 0.0;
              s = 1.0;

              for (i = l; i <= k; i++)
                {
                  f = s * e[i - 1];
                  e[i - 1] = c * e[i - 1];

                  if (fabs(f) <= eps)
                    {
                      break;
                    }

                  g = q[i - 1];
                  //
                  //  q(i) = h = sqrt(g*g + f*f).
                  //
                  h = r8_hypot(f, g);

                  q[i - 1] = h;

                  if (h == 0.0)
                    {
                      g = 1.0;
                      h = 1.0;
                    }

                  c = g / h;
                  s = -f / h;
                }
            }

          //
          //  Test for convergence for this index K.
          //
          z = q[k - 1];

          if (l == k)
            {
              if (z < 0.0)
                {
                  q[k - 1] = -z;

                  for (i = 1; i <= n; i++)
                    {
                      a[i - 1 + (k - 1) * n] = -a[i - 1 + (k - 1) * n];
                    }
                }

              break;
            }

          //
          //  Shift from bottom 2*2 minor.
          //
          x = q[l - 1];
          y = q[k - 2];
          g = e[k - 2];
          h = e[k - 1];
          f = ((y - z) * (y + z) + (g - h) * (g + h)) / (2.0 * h * y);

          g = r8_hypot(f, 1.0);

          if (f < 0.0)
            {
              temp = f - g;
            }
          else
            {
              temp = f + g;
            }

          f = ((x - z) * (x + z) + h * (y / temp - h)) / x;
          //
          //  Next QR transformation.
          //
          c = 1.0;
          s = 1.0;

          for (i = l + 1; i <= k; i++)
            {
              g = e[i - 1];
              y = q[i - 1];
              h = s * g;
              g = g * c;

              z = r8_hypot(f, h);

              e[i - 2] = z;

              if (z == 0.0)
                {
                  f = 1.0;
                  z = 1.0;
                }

              c = f / z;
              s = h / z;
              f = x * c + g * s;
              g = -x * s + g * c;
              h = y * s;
              y = y * c;

              for (j = 1; j <= n; j++)
                {
                  x = a[j - 1 + (i - 2) * n];
                  z = a[j - 1 + (i - 1) * n];
                  a[j - 1 + (i - 2) * n] = x * c + z * s;
                  a[j - 1 + (i - 1) * n] = -x * s + z * c;
                }

              z = r8_hypot(f, h);

              q[i - 2] = z;

              if (z == 0.0)
                {
                  f = 1.0;
                  z = 1.0;
                }

              c = f / z;
              s = h / z;
              f = c * g + s * y;
              x = -s * g + c * y;
            }

          e[l - 1] = 0.0;
          e[k - 1] = f;
          q[k - 1] = x;
        }
    }

  delete[] e;

  return;
}
//****************************************************************************80

void CPraxis::minny(C_INT32 n,
                    C_INT32 jsearch,
                    C_INT32 nits,
                    C_FLOAT64 & d2,
                    C_FLOAT64 & x1,
                    C_FLOAT64 & f1,
                    bool fk,
                    FPraxis * f,
                    C_FLOAT64 x[],
                    C_FLOAT64 t,
                    C_FLOAT64 h,
                    C_FLOAT64 v[],
                    C_FLOAT64 q0[],
                    C_FLOAT64 q1[],
                    C_INT32 & nl,
                    C_INT32 & nf,
                    C_FLOAT64 dmin,
                    C_FLOAT64 ldt,
                    C_FLOAT64 & fx,
                    C_FLOAT64 & qa,
                    C_FLOAT64 & qb,
                    C_FLOAT64 & qc,
                    C_FLOAT64 & qd0,
                    C_FLOAT64 & qd1)

//****************************************************************************80
//
//  Purpose:
//
//    MINNY minimizes a scalar function of N variables along a line.
//
//  Discussion:
//
//    MINNY minimizes F along the line from X in the direction V(*,JSEARCH)
//    or else using a quadratic search in the plane defined by Q0, Q1 and X.
//
//    If FK = true, then F1 is FLIN(X1).  Otherwise X1 and F1 are ignored
//    on entry unless final FX is greater than F1.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    04 August 2016
//
//  Author:
//
//    Original FORTRAN77 version by Richard Brent.
//    C++ version by John Burkardt.
//
//  Reference:
//
//    Richard Brent,
//    Algorithms for Minimization with Derivatives,
//    Prentice Hall, 1973,
//    ReprC_INT32ed by Dover, 2002.
//
//  Parameters:
//
//    Input, C_INT32 N, the number of variables.
//
//    Input, C_INT32 JSEARCH, indicates the kind of search.
//    If J is a legal columnindex, linear search in the direction of V(*,JSEARCH).
//    Otherwise, the search is parabolic, based on X, Q0 and Q1.
//
//    Input, C_INT32 NITS, the maximum number of times the C_INT32erval
//    may be halved to retry the calculation.
//
//    Input/output, C_FLOAT64 &D2, is either zero, or an approximation to
//    the value of (1/2) times the second derivative of F.
//
//    Input/output, C_FLOAT64 &X1, on entry, an estimate of the
//    distance from X to the minimum along V(*,JSEARCH), or a curve.
//    On output, the distance between X and the minimizer that was found.
//
//    Input/output, C_FLOAT64 &F1, ?
//
//    Input, bool FK; if FK is TRUE, then on input F1 contains
//    the value FLIN(X1).
//
//    Input, C_FLOAT64 F (C_FLOAT64 X[], C_INT32 N ), is the name of the function to
//    be minimized.
//
//    Input/output, C_FLOAT64 X[N], ?
//
//    Input, C_FLOAT64 T, ?
//
//    Input, C_FLOAT64 H, ?
//
//    Input, C_FLOAT64 V[N,N], a matrix whose columns are direction
//    vectors along which the function may be minimized.
//
//    ?, C_FLOAT64 Q0[N], ?
//
//    ?, C_FLOAT64 Q1[N], ?
//
//    Input/output, C_INT32 &NL, the number of linear searches.
//
//    Input/output, C_INT32 &NF, the number of function evaluations.
//
//    Input, C_FLOAT64 DMIN, an estimate for the smallest eigenvalue.
//
//    Input, C_FLOAT64 LDT, the length of the step.
//
//    Input/output, C_FLOAT64 &FX, the value of F(X,N).
//
//    Input/output, C_FLOAT64 &QA, &QB, &QC;
//
//    Input/output, C_FLOAT64 &QD0, &QD1, ?.
//
{
  C_FLOAT64 d1;
  C_INT32 dz;
  C_FLOAT64 f0;
  C_FLOAT64 f2;
  C_FLOAT64 fm;
  C_INT32 i;
  C_INT32 k;
  C_FLOAT64 m2;
  C_FLOAT64 m4;
  C_FLOAT64 machep;
  C_INT32 ok;
  C_FLOAT64 s;
  C_FLOAT64 sf1;
  C_FLOAT64 small;
  C_FLOAT64 sx1;
  C_FLOAT64 t2;
  C_FLOAT64 temp;
  C_FLOAT64 x2;
  C_FLOAT64 xm;

  machep = DBL_EPSILON;
  small = machep * machep;
  m2 = sqrt(machep);
  m4 = sqrt(m2);
  sf1 = f1;
  sx1 = x1;
  k = 0;
  xm = 0.0;
  fm = fx;
  f0 = fx;
  dz = (d2 < machep);
  //
  //  Find the step size.
  //
  s = r8vec_norm(n, x);

  if (dz)
    {
      temp = dmin;
    }
  else
    {
      temp = d2;
    }

  t2 = m4 * sqrt(fabs(fx) / temp + s * ldt) + m2 * ldt;
  s = m4 * s + t;

  if (dz && s < t2)
    {
      t2 = s;
    }

  t2 = fmax(t2, small);
  t2 = fmin(t2, 0.01 * h);

  if (fk && f1 <= fm)
    {
      xm = x1;
      fm = f1;
    }

  if ((!fk) || fabs(x1) < t2)
    {
      if (0.0 <= x1)
        {
          temp = 1.0;
        }
      else
        {
          temp = -1.0;
        }

      x1 = temp * t2;
      f1 = flin(n, jsearch, x1, f, x, nf, v, q0, q1, qd0, qd1, qa, qb, qc);
    }

  if (f1 <= fm)
    {
      xm = x1;
      fm = f1;
    }

  //
  //  Evaluate FLIN at another poC_INT32 and estimate the second derivative.
  //
  for (;;)
    {
      if (dz)
        {
          if (f1 <= f0)
            {
              x2 = 2.0 * x1;
            }
          else
            {
              x2 = -x1;
            }

          f2 = flin(n, jsearch, x2, f, x, nf, v, q0, q1, qd0, qd1, qa, qb, qc);

          if (f2 <= fm)
            {
              xm = x2;
              fm = f2;
            }

          d2 = (x2 * (f1 - f0) - x1 * (f2 - f0))
               / ((x1 * x2) * (x1 - x2));
        }

      //
      //  Estimate the first derivative at 0.
      //
      d1 = (f1 - f0) / x1 - x1 * d2;
      dz = 1;

      //
      //  Predict the minimum.
      //
      if (d2 <= small)
        {
          if (0.0 <= d1)
            {
              x2 = -h;
            }
          else
            {
              x2 = h;
            }
        }
      else
        {
          x2 = (-0.5 * d1) / d2;
        }

      if (h < fabs(x2))
        {
          if (x2 <= 0.0)
            {
              x2 = -h;
            }
          else
            {
              x2 = h;
            }
        }

      //
      //  Evaluate F at the predicted minimum.
      //
      ok = 1;

      for (;;)
        {
          f2 = flin(n, jsearch, x2, f, x, nf, v, q0, q1, qd0, qd1, qa, qb, qc);

          if (nits <= k || f2 <= f0)
            {
              break;
            }

          k = k + 1;

          if (f0 < f1 && 0.0 < x1 * x2)
            {
              ok = 0;
              break;
            }

          x2 = 0.5 * x2;
        }

      if (ok)
        {
          break;
        }
    }

  //
  //  Increment the one-dimensional search counter.
  //
  nl = nl + 1;

  if (fm < f2)
    {
      x2 = xm;
    }
  else
    {
      fm = f2;
    }

  //
  //  Get a new estimate of the second derivative.
  //
  if (small < fabs(x2 * (x2 - x1)))
    {
      d2 = (x2 * (f1 - f0) - x1 * (fm - f0))
           / ((x1 * x2) * (x1 - x2));
    }
  else
    {
      if (0 < k)
        {
          d2 = 0.0;
        }
    }

  d2 = fmax(d2, small);

  x1 = x2;
  fx = fm;

  if (sf1 < fx)
    {
      fx = sf1;
      x1 = sx1;
    }

  //
  //  Update X for linear search.
  //
  if (0 <= jsearch)
    {
      for (i = 0; i < n; i++)
        {
          x[i] = x[i] + x1 * v[i + jsearch * n];
        }
    }

  return;
}
//****************************************************************************80

C_FLOAT64 CPraxis::operator()(C_FLOAT64 t0, C_FLOAT64 h0, C_INT32 n, C_INT32 prin, C_FLOAT64 x[], FPraxis * f)

//****************************************************************************80
//
//  Purpose:
//
//    PRAXIS seeks an N-dimensional minimizer X of a scalar function F(X).
//
//  Discussion:
//
//    PRAXIS returns the minimum of the function F(X,N) of N variables
//    using the principal axis method.  The gradient of the function is
//    not required.
//
//    The approximating quadratic form is
//
//      Q(x") = F(x,n) + (1/2) * (x"-x)" * A * (x"-x)
//
//    where X is the best estimate of the minimum and
//
//      A = inverse(V") * D * inverse(V)
//
//    V(*,*) is the matrix of search directions;
//    D(*) is the array of second differences.
//
//    If F(X) has continuous second derivatives near X0, then A will tend
//    to the hessian of F at X0 as X approaches X0.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    04 August 2016
//
//  Author:
//
//    Original FORTRAN77 version by Richard Brent.
//    C++ version by John Burkardt.
//
//  Reference:
//
//    Richard Brent,
//    Algorithms for Minimization with Derivatives,
//    Prentice Hall, 1973,
//    ReprC_INT32ed by Dover, 2002.
//
//  Parameters:
//
//    Input, C_FLOAT64 T0, is a tolerance.  PRAXIS attempts to return
//    praxis = (*f)(x) such that if X0 is the true local minimum near X, then
//    norm (x - x0 ) < T0 + sqrt (EPSILON ) * norm (X ),
//    where EPSILON is the machine precision for X.
//
//    Input, C_FLOAT64 H0, is the maximum step size.  H0 should be
//    set to about the maximum distance from the initial guess to the minimum.
//    If H0 is set too large or too small, the initial rate of
//    convergence may be slow.
//
//    Input, C_INT32 N, the number of variables.
//
//    Input, C_INT32 PRIN, controls prC_INT32ing C_INT32ermediate results.
//    0, nothing is prC_INT32ed.
//    1, F is prC_INT32ed after every n+1 or n+2 linear minimizations.
//       final X is prC_INT32ed, but C_INT32ermediate X is prC_INT32ed only
//       if N is at most 4.
//    2, the scale factors and the principal values of the approximating
//       quadratic form are also prC_INT32ed.
//    3, X is also prC_INT32ed after every few linear minimizations.
//    4, the principal vectors of the approximating quadratic form are
//       also prC_INT32ed.
//
//    Input/output, C_FLOAT64 X[N], is an array containing on entry a
//    guess of the poC_INT32 of minimum, on return the estimated poC_INT32 of minimum.
//
//    Input, C_FLOAT64 F (C_FLOAT64 X[], C_INT32 N ), is the name of the function to be
//    minimized.
//
//    Output, C_FLOAT64 PRAXIS, the function value at the minimizer.
//
//  Local parameters:
//
//    Local, C_FLOAT64 DMIN, an estimate for the smallest eigenvalue.
//
//    Local, C_FLOAT64 FX, the value of F(X,N).
//
//    Local, bool ILLC, is TRUE if the system is ill-conditioned.
//
//    Local, C_FLOAT64 LDT, the length of the step.
//
//    Local, C_INT32 NF, the number of function evaluations.
//
//    Local, C_INT32 NL, the number of linear searches.
//
{
  C_FLOAT64 * d;
  C_FLOAT64 d2;
  C_FLOAT64 df;
  C_FLOAT64 dmin;
  C_FLOAT64 dn;
  C_FLOAT64 dni;
  C_FLOAT64 f1;
  bool fk;
  C_FLOAT64 fx;
  C_FLOAT64 h;
  C_INT32 i;
  bool illc;
  C_INT32 j;
  C_INT32 jsearch;
  C_INT32 k;
  C_INT32 k2;
  C_INT32 kl;
  C_INT32 kt;
  C_INT32 ktm;
  C_FLOAT64 large;
  C_FLOAT64 ldfac;
  C_FLOAT64 lds;
  C_FLOAT64 ldt;
  C_FLOAT64 m2;
  C_FLOAT64 m4;
  C_FLOAT64 machep;
  C_INT32 nits;
  C_INT32 nl;
  C_INT32 nf;
  C_FLOAT64 * q0;
  C_FLOAT64 * q1;
  C_FLOAT64 qa;
  C_FLOAT64 qb;
  C_FLOAT64 qc;
  C_FLOAT64 qd0;
  C_FLOAT64 qd1;
  C_FLOAT64 qf1;
  C_FLOAT64 r;
  C_FLOAT64 s;
  C_FLOAT64 scbd;
  C_INT32 seed;
  C_FLOAT64 sf;
  C_FLOAT64 sl;
  C_FLOAT64 small;
  C_FLOAT64 t;
  C_FLOAT64 temp;
  C_FLOAT64 t2;
  C_FLOAT64 * v;
  C_FLOAT64 value;
  C_FLOAT64 vlarge;
  C_FLOAT64 vsmall;
  C_FLOAT64 * y;
  C_FLOAT64 * z;
  //
  //  Allocation.
  //
  d = new C_FLOAT64[n];
  q0 = new C_FLOAT64[n];
  q1 = new C_FLOAT64[n];
  v = new C_FLOAT64[n * n];
  y = new C_FLOAT64[n];
  z = new C_FLOAT64[n];
  //
  //  Initialization.
  //
  machep = DBL_EPSILON;
  small = machep * machep;
  vsmall = small * small;
  large = 1.0 / small;
  vlarge = 1.0 / vsmall;
  m2 = sqrt(machep);
  m4 = sqrt(m2);
  seed = 123456789;
  //
  //  Heuristic numbers:
  //
  //  If the axes may be badly scaled (which is to be avoided if
  //  possible), then set SCBD = 10.  Otherwise set SCBD = 1.
  //
  //  If the problem is known to be ill-conditioned, initialize ILLC = true.
  //
  //  KTM is the number of iterations without improvement before the
  //  algorithm terminates.  KTM = 4 is very cautious; usually KTM = 1
  //  is satisfactory.
  //
  scbd = 1.0;
  illc = false;
  ktm = 1;

  if (illc)
    {
      ldfac = 0.1;
    }
  else
    {
      ldfac = 0.01;
    }

  kt = 0;
  nl = 0;
  nf = 1;
  fx = (*f)(x, n);
  qf1 = fx;
  t = small + fabs(t0);
  t2 = t;
  dmin = small;
  h = h0;
  h = fmax(h, 100.0 * t);
  ldt = h;

  //
  //  The initial set of search directions V is the identity matrix.
  //
  for (j = 0; j < n; j++)
    {
      for (i = 0; i < n; i++)
        {
          v[i + j * n] = 0.0;
        }

      v[j + j * n] = 1.0;
    }

  for (i = 0; i < n; i++)
    {
      d[i] = 0.0;
    }

  qa = 0.0;
  qb = 0.0;
  qc = 0.0;
  qd0 = 0.0;
  qd1 = 0.0;
  r8vec_copy(n, x, q0);
  r8vec_copy(n, x, q1);

  if (0 < prin)
    {
      prC_INT322(n, x, prin, fx, nf, nl);
    }

  //
  //  The main loop starts here.
  //
  for (;;)
    {
      sf = d[0];
      d[0] = 0.0;
      //
      //  Minimize along the first direction V(*,1).
      //
      jsearch = 0;
      nits = 2;
      d2 = d[0];
      s = 0.0;
      value = fx;
      fk = false;

      minny(n, jsearch, nits, d2, s, value, fk, f, x, t,
            h, v, q0, q1, nl, nf, dmin, ldt, fx, qa, qb, qc, qd0, qd1);

      d[0] = d2;

      if (s <= 0.0)
        {
          for (i = 0; i < n; i++)
            {
              v[i + 0 * n] = -v[i + 0 * n];
            }
        }

      if (sf <= 0.9 * d[0] || d[0] <= 0.9 * sf)
        {
          for (i = 1; i < n; i++)
            {
              d[i] = 0.0;
            }
        }

      //
      //  The inner loop starts here.
      //
      for (k = 2; k <= n; k++)
        {
          r8vec_copy(n, x, y);

          sf = fx;

          if (0 < kt)
            {
              illc = true;
            }

          for (;;)
            {
              kl = k;
              df = 0.0;

              //
              //  A random step follows, to avoid resolution valleys.
              //
              if (illc)
                {
                  for (j = 0; j < n; j++)
                    {
                      r = mpRandom->getRandomCC();
                      s = (0.1 * ldt + t2 * pow(10.0, kt)) * (r - 0.5);
                      z[j] = s;

                      for (i = 0; i < n; i++)
                        {
                          x[i] = x[i] + s * v[i + j * n];
                        }
                    }

                  fx = (*f)(x, n);
                  nf = nf + 1;
                }

              //
              //  Minimize along the "non-conjugate" directions V(*,K),...,V(*,N).
              //
              for (k2 = k; k2 <= n; k2++)
                {
                  sl = fx;

                  jsearch = k2 - 1;
                  nits = 2;
                  d2 = d[k2 - 1];
                  s = 0.0;
                  value = fx;
                  fk = false;

                  minny(n, jsearch, nits, d2, s, value, fk, f, x, t,
                        h, v, q0, q1, nl, nf, dmin, ldt, fx, qa, qb, qc, qd0, qd1);

                  d[k2 - 1] = d2;

                  if (illc)
                    {
                      s = d[k2 - 1] * pow(s + z[k2 - 1], 2);
                    }
                  else
                    {
                      s = sl - fx;
                    }

                  if (df <= s)
                    {
                      df = s;
                      kl = k2;
                    }
                }

              //
              //  If there was not much improvement on the first try, set
              //  ILLC = true and start the inner loop again.
              //
              if (illc)
                {
                  break;
                }

              if (fabs(100.0 * machep * fx) <= df)
                {
                  break;
                }

              illc = true;
            }

          if (k == 2 && 1 < prin)
            {
              r8vec_prC_INT32(n, d, "  The second difference array:");
            }

          //
          //  Minimize along the "conjugate" directions V(*,1),...,V(*,K-1).
          //
          for (k2 = 1; k2 < k; k2++)
            {
              jsearch = k2 - 1;
              nits = 2;
              d2 = d[k2 - 1];
              s = 0.0;
              value = fx;
              fk = false;

              minny(n, jsearch, nits, d2, s, value, fk, f, x, t,
                    h, v, q0, q1, nl, nf, dmin, ldt, fx, qa, qb, qc, qd0, qd1);

              d[k2 - 1] = d2;
            }

          f1 = fx;
          fx = sf;

          for (i = 0; i < n; i++)
            {
              temp = x[i];
              x[i] = y[i];
              y[i] = temp - y[i];
            }

          lds = r8vec_norm(n, y);

          //
          //  Discard direction V(*,kl).
          //
          //  If no random step was taken, V(*,KL) is the "non-conjugate"
          //  direction along which the greatest improvement was made.
          //
          if (small < lds)
            {
              for (j = kl - 1; k <= j; j--)
                {
                  for (i = 1; i <= n; i++)
                    {
                      v[i - 1 + j * n] = v[i - 1 + (j - 1) * n];
                    }

                  d[j] = d[j - 1];
                }

              d[k - 1] = 0.0;

              for (i = 1; i <= n; i++)
                {
                  v[i - 1 + (k - 1) * n] = y[i - 1] / lds;
                }

              //
              //  Minimize along the new "conjugate" direction V(*,k), which is
              //  the normalized vector:  (new x) - (old x).
              //
              jsearch = k - 1;
              nits = 4;
              d2 = d[k - 1];
              value = f1;
              fk = true;

              minny(n, jsearch, nits, d2, lds, value, fk, f, x, t,
                    h, v, q0, q1, nl, nf, dmin, ldt, fx, qa, qb, qc, qd0, qd1);

              d[k - 1] = d2;

              if (lds <= 0.0)
                {
                  lds = -lds;

                  for (i = 1; i <= n; i++)
                    {
                      v[i - 1 + (k - 1) * n] = -v[i - 1 + (k - 1) * n];
                    }
                }
            }

          ldt = ldfac * ldt;
          ldt = fmax(ldt, lds);

          if (0 < prin)
            {
              prC_INT322(n, x, prin, fx, nf, nl);
            }

          t2 = r8vec_norm(n, x);

          t2 = m2 * t2 + t;

          //
          //  See whether the length of the step taken since starting the
          //  inner loop exceeds half the tolerance.
          //
          if (0.5 * t2 < ldt)
            {
              kt = -1;
            }

          kt = kt + 1;

          if (ktm < kt)
            {
              if (0 < prin)
                {
                  r8vec_prC_INT32(n, x, "  X:");
                }

              delete[] d;
              delete[] q0;
              delete[] q1;
              delete[] v;
              delete[] y;
              delete[] z;

              return fx;
            }
        }

      //
      //  The inner loop ends here.
      //
      //  Try quadratic extrapolation in case we are in a curved valley.
      //
      quad(n, f, x, t, h, v, q0, q1, nl, nf, dmin, ldt, fx, qf1,
           qa, qb, qc, qd0, qd1);

      for (j = 0; j < n; j++)
        {
          d[j] = 1.0 / sqrt(d[j]);
        }

      dn = r8vec_max(n, d);

      if (3 < prin)
        {
          r8mat_prC_INT32(n, n, v, "  The new direction vectors:");
        }

      for (j = 0; j < n; j++)
        {
          for (i = 0; i < n; i++)
            {
              v[i + j * n] = (d[j] / dn) * v[i + j * n];
            }
        }

      //
      //  Scale the axes to try to reduce the condition number.
      //
      if (1.0 < scbd)
        {
          for (i = 0; i < n; i++)
            {
              s = 0.0;

              for (j = 0; j < n; j++)
                {
                  s = s + v[i + j * n] * v[i + j * n];
                }

              s = sqrt(s);
              z[i] = fmax(m4, s);
            }

          s = r8vec_min(n, z);

          for (i = 0; i < n; i++)
            {
              sl = s / z[i];
              z[i] = 1.0 / sl;

              if (scbd < z[i])
                {
                  sl = 1.0 / scbd;
                  z[i] = scbd;
                }

              for (j = 0; j < n; j++)
                {
                  v[i + j * n] = sl * v[i + j * n];
                }
            }
        }

      //
      //  Calculate a new set of orthogonal directions before repeating
      //  the main loop.
      //
      //  Transpose V for MINFIT:
      //
      r8mat_transpose_in_place(n, v);
      //
      //  MINFIT finds the singular value decomposition of V.
      //
      //  This gives the principal values and principal directions of the
      //  approximating quadratic form without squaring the condition number.
      //
      minfit(n, vsmall, v, d);

      //
      //  Unscale the axes.
      //
      if (1.0 < scbd)
        {
          for (i = 0; i < n; i++)
            {
              for (j = 0; j < n; j++)
                {
                  v[i + j * n] = z[i] * v[i + j * n];
                }
            }

          for (j = 0; j < n; j++)
            {
              s = 0.0;

              for (i = 0; i < n; i++)
                {
                  s = s + v[i + j * n] * v[i + j * n];
                }

              s = sqrt(s);

              d[j] = s * d[j];

              for (i = 0; i < n; i++)
                {
                  v[i + j * n] = v[i + j * n] / s;
                }
            }
        }

      for (i = 0; i < n; i++)
        {
          dni = dn * d[i];

          if (large < dni)
            {
              d[i] = vsmall;
            }
          else if (dni < small)
            {
              d[i] = vlarge;
            }
          else
            {
              d[i] = 1.0 / dni / dni;
            }
        }

      //
      //  Sort the eigenvalues and eigenvectors.
      //
      svsort(n, d, v);
      //
      //  Determine the smallest eigenvalue.
      //
      dmin = fmax(d[n - 1], small);

      //
      //  The ratio of the smallest to largest eigenvalue determines whether
      //  the system is ill conditioned.
      //
      if (dmin < m2 * d[0])
        {
          illc = true;
        }
      else
        {
          illc = false;
        }

      if (1 < prin)
        {
          if (1.0 < scbd)
            {
              r8vec_prC_INT32(n, z, "  The scale factors:");
            }

          r8vec_prC_INT32(n, d, "  Principal values of the quadratic form:");
        }

      if (3 < prin)
        {
          r8mat_prC_INT32(n, n, v, "  The principal axes:");
        }

      //
      //  The main loop ends here.
      //
    }

  if (0 < prin)
    {
      r8vec_prC_INT32(n, x, "  X:");
    }

  //
  //  Free memory.
  //
  delete[] d;
  delete[] q0;
  delete[] q1;
  delete[] v;
  delete[] y;
  delete[] z;

  return fx;
}
//****************************************************************************80

void CPraxis::prC_INT322(C_INT32 n, C_FLOAT64 x[], C_INT32 prin, C_FLOAT64 fx, C_INT32 nf, C_INT32 nl)

//****************************************************************************80
//
//  Purpose:
//
//    PRINT2 prC_INT32s certain data about the progress of the iteration.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    04 August 2016
//
//  Author:
//
//    Original FORTRAN77 version by Richard Brent.
//    C++ version by John Burkardt.
//
//  Reference:
//
//    Richard Brent,
//    Algorithms for Minimization with Derivatives,
//    Prentice Hall, 1973,
//    ReprC_INT32ed by Dover, 2002.
//
//  Parameters:
//
//    Input, C_INT32 N, the number of variables.
//
//    Input, C_FLOAT64 X[N], the current estimate of the minimizer.
//
//    Input, C_INT32 PRIN, the user-specifed prC_INT32 level.
//    0, nothing is prC_INT32ed.
//    1, F is prC_INT32ed after every n+1 or n+2 linear minimizations.
//       final X is prC_INT32ed, but C_INT32ermediate X is prC_INT32ed only
//       if N is at most 4.
//    2, the scale factors and the principal values of the approximating
//       quadratic form are also prC_INT32ed.
//    3, X is also prC_INT32ed after every few linear minimizations.
//    4, the principal vectors of the approximating quadratic form are
//       also prC_INT32ed.
//
//    Input, C_FLOAT64 FX, the smallest value of F(X) found so far.
//
//    Input, C_INT32 NF, the number of function evaluations.
//
//    Input, C_INT32 NL, the number of linear searches.
//
{
  std::cout << "\n";
  std::cout << "  Linear searches = " << nl << "\n";
  std::cout << "  Function evaluations " << nf << "\n";
  std::cout << "  Function value FX = " << fx << "\n";

  if (n <= 4 || 2 < prin)
    {
      r8vec_prC_INT32(n, x, "  X:");
    }

  return;
}
//****************************************************************************80

void CPraxis::quad(C_INT32 n, FPraxis * f, C_FLOAT64 x[], C_FLOAT64 t, C_FLOAT64 h, C_FLOAT64 v[], C_FLOAT64 q0[], C_FLOAT64 q1[], C_INT32 & nl, C_INT32 & nf, C_FLOAT64 dmin, C_FLOAT64 ldt, C_FLOAT64 & fx, C_FLOAT64 & qf1, C_FLOAT64 & qa, C_FLOAT64 & qb, C_FLOAT64 & qc, C_FLOAT64 & qd0, C_FLOAT64 & qd1)

//****************************************************************************80
//
//  Purpose:
//
//    QUAD seeks to minimize the scalar function F along a particular curve.
//
//  Discussion:
//
//    The minimizer to be sought is required to lie on a curve defined
//    by Q0, Q1 and X.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    04 August 2016
//
//  Author:
//
//    Original FORTRAN77 version by Richard Brent.
//    C++ version by John Burkardt.
//
//  Reference:
//
//    Richard Brent,
//    Algorithms for Minimization with Derivatives,
//    Prentice Hall, 1973,
//    ReprC_INT32ed by Dover, 2002.
//
//  Parameters:
//
//    Input, C_INT32 N, the number of variables.
//
//    Input, C_FLOAT64 F (C_FLOAT64 X[], C_INT32 N ), the name of the function to
//    be minimized.
//
//    Input/output, C_FLOAT64 X[N], ?
//
//    Input, C_FLOAT64 T, ?
//
//    Input, C_FLOAT64 H, ?
//
//    Input, C_FLOAT64 V[N,N], the matrix of search directions.
//
//    Input/output, C_FLOAT64 Q0[N], Q1[N], two auxiliary poC_INT32s used to define
//    a curve through X.
//
//    Input/output, C_INT32 &NL, the number of linear searches.
//
//    Input/output, C_INT32 &NF, the number of function evaluations.
//
//    Input, C_FLOAT64 DMIN, an estimate for the smallest eigenvalue.
//
//    Input, C_FLOAT64 LDT, the length of the step.
//
//    Input/output, C_FLOAT64 &FX, the value of F(X,N).
//
//    Input/output, C_FLOAT64 &QF1, &QA, &QB, &QC, &QD0, &QD1 ?
//
{
  bool fk;
  C_INT32 i;
  C_INT32 jsearch;
  C_FLOAT64 l;
  C_INT32 nits;
  C_FLOAT64 s;
  C_FLOAT64 temp;
  C_FLOAT64 value;

  temp = fx;
  fx = qf1;
  qf1 = temp;

  for (i = 0; i < n; i++)
    {
      temp = x[i];
      x[i] = q1[i];
      q1[i] = temp;
    }

  qd1 = 0.0;

  for (i = 0; i < n; i++)
    {
      qd1 = qd1 + (x[i] - q1[i]) * (x[i] - q1[i]);
    }

  qd1 = sqrt(qd1);

  if (qd0 <= 0.0 || qd1 <= 0.0 || nl < 3 * n * n)
    {
      fx = qf1;
      qa = 0.0;
      qb = 0.0;
      qc = 1.0;
      s = 0.0;
    }
  else
    {
      jsearch = -1;
      nits = 2;
      s = 0.0;
      l = qd1;
      value = qf1;
      fk = true;

      minny(n, jsearch, nits, s, l, value, fk, f, x, t,
            h, v, q0, q1, nl, nf, dmin, ldt, fx, qa, qb, qc, qd0, qd1);

      qa = l * (l - qd1) / (qd0 + qd1) / qd0;
      qb = -(l + qd0) * (l - qd1) / qd1 / qd0;
      qc = (l + qd0) * l / qd1 / (qd0 + qd1);
    }

  qd0 = qd1;

  for (i = 0; i < n; i++)
    {
      s = q0[i];
      q0[i] = x[i];
      x[i] = qa * s + qb * x[i] + qc * q1[i];
    }

  return;
}
//****************************************************************************80

C_FLOAT64 CPraxis::r8_hypot(C_FLOAT64 x, C_FLOAT64 y)

//****************************************************************************80
//
//  Purpose:
//
//    R8_HYPOT returns the value of sqrt (X^2 + Y^2 ).
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    26 March 2012
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, C_FLOAT64 X, Y, the arguments.
//
//    Output, C_FLOAT64 R8_HYPOT, the value of sqrt (X^2 + Y^2 ).
//
{
  C_FLOAT64 a;
  C_FLOAT64 b;
  C_FLOAT64 value;

  if (fabs(x) < fabs(y))
    {
      a = fabs(y);
      b = fabs(x);
    }
  else
    {
      a = fabs(x);
      b = fabs(y);
    }

  //
  //  A contains the larger value.
  //
  if (a == 0.0)
    {
      value = 0.0;
    }
  else
    {
      value = a * sqrt(1.0 + (b / a) * (b / a));
    }

  return value;
}
//****************************************************************************80

C_FLOAT64 CPraxis::r8_uniform_01(C_INT32 & seed)

//****************************************************************************80
//
//  Purpose:
//
//    R8_UNIFORM_01 returns a unit pseudorandom R8.
//
//  Discussion:
//
//    This routine implements the recursion
//
//      seed = (16807 * seed ) mod (2^31 - 1)
//      u = seed / (2^31 - 1)
//
//    The C_INT32eger arithmetic never requires more than 32 bits,
//    including a sign bit.
//
//    If the initial seed is 12345, then the first three computations are
//
//      Input     Output      R8_UNIFORM_01
//      SEED      SEED
//
//         12345   207482415  0.096616
//     207482415  1790989824  0.833995
//    1790989824  2035175616  0.947702
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    09 April 2012
//
//  Author:
//
//    John Burkardt
//
//  Reference:
//
//    Paul Bratley, Bennett Fox, Linus Schrage,
//    A Guide to Simulation,
//    Second Edition,
//    Springer, 1987,
//    ISBN: 0387964673,
//    LC: QA76.9.C65.B73.
//
//    Bennett Fox,
//    Algorithm 647:
//    Implementation and Relative Efficiency of Quasirandom
//    Sequence Generators,
//    ACM Transactions on Mathematical Software,
//    Volume 12, Number 4, December 1986, pages 362-376.
//
//    Pierre L'Ecuyer,
//    Random Number Generation,
//    in Handbook of Simulation,
//    edited by Jerry Banks,
//    Wiley, 1998,
//    ISBN: 0471134031,
//    LC: T57.62.H37.
//
//    Peter Lewis, Allen Goodman, James Miller,
//    A Pseudo-Random Number Generator for the System/360,
//    IBM Systems Journal,
//    Volume 8, Number 2, 1969, pages 136-143.
//
//  Parameters:
//
//    Input/output, C_INT32 &SEED, the "seed" value.  Normally, this
//    value should not be 0.  On output, SEED has been updated.
//
//    Output, C_FLOAT64 R8_UNIFORM_01, a new pseudorandom variate,
//    strictly between 0 and 1.
//
{
  const C_INT32 i4_huge = 2147483647;
  C_INT32 k;
  C_FLOAT64 r;

  if (seed == 0)
    {
      std::cerr << "\n";
      std::cerr << "R8_UNIFORM_01 - Fatal error!\n";
      std::cerr << "  Input value of SEED = 0.\n";
      exit(1);
    }

  k = seed / 127773;

  seed = 16807 * (seed - k * 127773) - k * 2836;

  if (seed < 0)
    {
      seed = seed + i4_huge;
    }

  r = (C_FLOAT64)(seed) * 4.656612875E-10;

  return r;
}
//****************************************************************************80

void CPraxis::r8mat_prC_INT32(C_INT32 m, C_INT32 n, C_FLOAT64 a[], std::string title)

//****************************************************************************80
//
//  Purpose:
//
//    R8MAT_PRINT prC_INT32s an R8MAT.
//
//  Discussion:
//
//    An R8MAT is a doubly dimensioned array of R8 values, stored as a vector
//    in column-major order.
//
//    Entry A(I,J) is stored as A[I+J*M]
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    10 September 2009
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, C_INT32 M, the number of rows in A.
//
//    Input, C_INT32 N, the number of columns in A.
//
//    Input, C_FLOAT64 A[M*N], the M by N matrix.
//
//    Input, std::string TITLE, a title.
//
{
  r8mat_prC_INT32_some(m, n, a, 1, 1, m, n, title);

  return;
}
//****************************************************************************80

void CPraxis::r8mat_prC_INT32_some(C_INT32 m, C_INT32 n, C_FLOAT64 a[], C_INT32 ilo, C_INT32 jlo, C_INT32 ihi, C_INT32 jhi, std::string title)

//****************************************************************************80
//
//  Purpose:
//
//    R8MAT_PRINT_SOME prC_INT32s some of an R8MAT.
//
//  Discussion:
//
//    An R8MAT is a doubly dimensioned array of R8 values, stored as a vector
//    in column-major order.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    26 June 2013
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, C_INT32 M, the number of rows of the matrix.
//    M must be positive.
//
//    Input, C_INT32 N, the number of columns of the matrix.
//    N must be positive.
//
//    Input, C_FLOAT64 A[M*N], the matrix.
//
//    Input, C_INT32 ILO, JLO, IHI, JHI, designate the first row and
//    column, and the last row and column to be prC_INT32ed.
//
//    Input, std::string TITLE, a title.
//
{
#define INCX 5

  C_INT32 i;
  C_INT32 i2hi;
  C_INT32 i2lo;
  C_INT32 j;
  C_INT32 j2hi;
  C_INT32 j2lo;

  std::cout << "\n";
  std::cout << title << "\n";

  if (m <= 0 || n <= 0)
    {
      std::cout << "\n";
      std::cout << "  (None)\n";
      return;
    }

  //
  //  PrC_INT32 the columns of the matrix, in strips of 5.
  //
  for (j2lo = jlo; j2lo <= jhi; j2lo = j2lo + INCX)
    {
      j2hi = j2lo + INCX - 1;

      if (n < j2hi)
        {
          j2hi = n;
        }

      if (jhi < j2hi)
        {
          j2hi = jhi;
        }

      std::cout << "\n";
      //
      //  For each column J in the current range...
      //
      //  Write the header.
      //
      std::cout << "  Col:    ";

      for (j = j2lo; j <= j2hi; j++)
        {
          std::cout << std::setw(7) << j - 1 << "       ";
        }

      std::cout << "\n";
      std::cout << "  Row\n";
      std::cout << "\n";

      //
      //  Determine the range of the rows in this strip.
      //
      if (1 < ilo)
        {
          i2lo = ilo;
        }
      else
        {
          i2lo = 1;
        }

      if (ihi < m)
        {
          i2hi = ihi;
        }
      else
        {
          i2hi = m;
        }

      for (i = i2lo; i <= i2hi; i++)
        {
          //
          //  PrC_INT32 out (up to) 5 entries in row I, that lie in the current strip.
          //
          std::cout << std::setw(5) << i - 1 << ": ";

          for (j = j2lo; j <= j2hi; j++)
            {
              std::cout << std::setw(12) << a[i - 1 + (j - 1) * m] << "  ";
            }

          std::cout << "\n";
        }
    }

  return;
#undef INCX
}
//****************************************************************************80

void CPraxis::r8mat_transpose_in_place(C_INT32 n, C_FLOAT64 a[])

//****************************************************************************80
//
//  Purpose:
//
//    R8MAT_TRANSPOSE_IN_PLACE transposes a square R8MAT in place.
//
//  Discussion:
//
//    An R8MAT is a doubly dimensioned array of R8 values, stored as a vector
//    in column-major order.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    26 June 2008
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, C_INT32 N, the number of rows and columns of the matrix A.
//
//    Input/output, C_FLOAT64 A[N*N], the matrix to be transposed.
//
{
  C_INT32 i;
  C_INT32 j;
  C_FLOAT64 t;

  for (j = 0; j < n; j++)
    {
      for (i = 0; i < j; i++)
        {
          t = a[i + j * n];
          a[i + j * n] = a[j + i * n];
          a[j + i * n] = t;
        }
    }

  return;
}
//****************************************************************************80

void CPraxis::r8vec_copy(C_INT32 n, C_FLOAT64 a1[], C_FLOAT64 a2[])

//****************************************************************************80
//
//  Purpose:
//
//    R8VEC_COPY copies an R8VEC.
//
//  Discussion:
//
//    An R8VEC is a vector of R8's.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    03 July 2005
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, C_INT32 N, the number of entries in the vectors.
//
//    Input, C_FLOAT64 A1[N], the vector to be copied.
//
//    Output, C_FLOAT64 A2[N], the copy of A1.
//
{
  C_INT32 i;

  for (i = 0; i < n; i++)
    {
      a2[i] = a1[i];
    }

  return;
}
//****************************************************************************80

C_FLOAT64 CPraxis::r8vec_max(C_INT32 n, C_FLOAT64 r8vec[])

//****************************************************************************80
//
//  Purpose:
//
//    R8VEC_MAX returns the value of the maximum element in an R8VEC.
//
//  Discussion:
//
//    An R8VEC is a vector of R8's.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    22 August 2010
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, C_INT32 N, the number of entries in the array.
//
//    Input, C_FLOAT64 R8VEC[N], a poC_INT32er to the first entry of the array.
//
//    Output, C_FLOAT64 R8VEC_MAX, the value of the maximum element.  This
//    is set to 0.0 if N <= 0.
//
{
  C_INT32 i;
  C_FLOAT64 value;

  value = r8vec[0];

  for (i = 1; i < n; i++)
    {
      if (value < r8vec[i])
        {
          value = r8vec[i];
        }
    }

  return value;
}
//****************************************************************************80

C_FLOAT64 CPraxis::r8vec_min(C_INT32 n, C_FLOAT64 r8vec[])

//****************************************************************************80
//
//  Purpose:
//
//    R8VEC_MIN returns the value of the minimum element in an R8VEC.
//
//  Discussion:
//
//    An R8VEC is a vector of R8's.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    02 July 2005
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, C_INT32 N, the number of entries in the array.
//
//    Input, C_FLOAT64 R8VEC[N], the array to be checked.
//
//    Output, C_FLOAT64 R8VEC_MIN, the value of the minimum element.
//
{
  C_INT32 i;
  C_FLOAT64 value;

  value = r8vec[0];

  for (i = 1; i < n; i++)
    {
      if (r8vec[i] < value)
        {
          value = r8vec[i];
        }
    }

  return value;
}
//****************************************************************************80

C_FLOAT64 CPraxis::r8vec_norm(C_INT32 n, C_FLOAT64 a[])

//****************************************************************************80
//
//  Purpose:
//
//    R8VEC_NORM returns the L2 norm of an R8VEC.
//
//  Discussion:
//
//    An R8VEC is a vector of R8's.
//
//    The vector L2 norm is defined as:
//
//      R8VEC_NORM = sqrt (sum (1 <= I <= N ) A(I)^2 ).
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    01 March 2003
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, C_INT32 N, the number of entries in A.
//
//    Input, C_FLOAT64 A[N], the vector whose L2 norm is desired.
//
//    Output, C_FLOAT64 R8VEC_NORM, the L2 norm of A.
//
{
  C_INT32 i;
  C_FLOAT64 v;

  v = 0.0;

  for (i = 0; i < n; i++)
    {
      v = v + a[i] * a[i];
    }

  v = sqrt(v);

  return v;
}
//****************************************************************************80

void CPraxis::r8vec_prC_INT32(C_INT32 n, C_FLOAT64 a[], std::string title)

//****************************************************************************80
//
//  Purpose:
//
//    R8VEC_PRINT prC_INT32s an R8VEC.
//
//  Discussion:
//
//    An R8VEC is a vector of R8's.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    16 August 2004
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, C_INT32 N, the number of components of the vector.
//
//    Input, C_FLOAT64 A[N], the vector to be prC_INT32ed.
//
//    Input, std::string TITLE, a title.
//
{
  C_INT32 i;

  std::cout << "\n";
  std::cout << title << "\n";
  std::cout << "\n";

  for (i = 0; i < n; i++)
    {
      std::cout << "  " << std::setw(8) << i
                << ": " << std::setw(14) << a[i] << "\n";
    }

  return;
}
//****************************************************************************80

void CPraxis::svsort(C_INT32 n, C_FLOAT64 d[], C_FLOAT64 v[])

//****************************************************************************80
//
//  Purpose:
//
//    SVSORT descending sorts D and adjusts the corresponding columns of V.
//
//  Discussion:
//
//    A simple bubble sort is used on D.
//
//    In our application, D contains singular values, and the columns of V are
//    the corresponding right singular vectors.
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    04 August 2016
//
//  Author:
//
//    Original FORTRAN77 version by Richard Brent.
//    C++ version by John Burkardt.
//
//  Reference:
//
//    Richard Brent,
//    Algorithms for Minimization with Derivatives,
//    Prentice Hall, 1973,
//    ReprC_INT32ed by Dover, 2002.
//
//  Parameters:
//
//    Input, C_INT32 N, the length of D, and the order of V.
//
//    Input/output, C_FLOAT64 D[N], the vector to be sorted.
//    On output, the entries of D are in descending order.
//
//    Input/output, C_FLOAT64 V[N,N], an N by N array to be adjusted
//    as D is sorted.  In particular, if the value that was in D(I) on input is
//    moved to D(J) on output, then the input column V(*,I) is moved to
//    the output column V(*,J).
//
{
  C_INT32 i;
  C_INT32 j1;
  C_INT32 j2;
  C_INT32 j3;
  C_FLOAT64 t;

  for (j1 = 0; j1 < n - 1; j1++)
    {
      //
      //  Find J3, the index of the largest entry in D[J1:N-1].
      //  MAXLOC apparently requires its output to be an array.
      //
      j3 = j1;

      for (j2 = j1 + 1; j2 < n; j2++)
        {
          if (d[j3] < d[j2])
            {
              j3 = j2;
            }
        }

      //
      //  If J1 != J3, swap D[J1] and D[J3], and columns J1 and J3 of V.
      //
      if (j1 != j3)
        {
          t = d[j1];
          d[j1] = d[j3];
          d[j3] = t;

          for (i = 0; i < n; i++)
            {
              t = v[i + j1 * n];
              v[i + j1 * n] = v[i + j3 * n];
              v[i + j3 * n] = t;
            }
        }
    }

  return;
}
//****************************************************************************80

void timestamp()

//****************************************************************************80
//
//  Purpose:
//
//    TIMESTAMP prC_INT32s the current YMDHMS date as a time stamp.
//
//  Example:
//
//    31 May 2001 09:45:54 AM
//
//  Licensing:
//
//    This code is distributed under the GNU LGPL license.
//
//  Modified:
//
//    08 July 2009
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    None
//
{
#define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct std::tm * tm_ptr;
  std::time_t now;

  now = std::time(NULL);
  tm_ptr = std::localtime(&now);

  std::strftime(time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm_ptr);

  std::cout << time_buffer << "\n";

  return;
#undef TIME_SIZE
}
