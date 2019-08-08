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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

//
// This C++ code is based on an f2c conversion of the Fortran
// library ODEPACK available at: http://www.netlib.org/odepack/

#include <cmath>

#include <algorithm>

#include "copasi/copasi.h"

#include "CInternalSolver.h"

#include "copasi/lapack/lapackwrap.h"

#define dls001_1 (mdls001_._1)
#define dls001_2 (mdls001_._2)
#define dls001_3 (mdls001_._3)

#define dlsa01_1 (mdlsa01_._1)
#define dlsa01_2 (mdlsa01_._2)
#define dlsa01_3 (mdlsa01_._3)

static C_INT c__0 = 0;

#include "dgbfa.h"
#include "dgefa.h"
#include "dbnorm.h"
#include "dfnorm.h"
#include "dmnorm.h"

/* DECK DPRJA */
/* Subroutine */
C_INT CInternalSolver::dprja_(C_INT *neq, double *y, double *yh,
                              C_INT *nyh, double *ewt, double *ftem, double *savf,
                              double *wm, C_INT *iwm, evalF f, evalJ jac)
{
  /* System generated locals */
  C_INT yh_dim1, yh_offset, i__1, i__2, i__3, i__4;
  double d__1, d__2;

  /* Local variables */
  C_INT i__, j;
  double r__;
  C_INT i1, i2, j1;
  double r0;
  C_INT ii, jj, ml, mu;
  double yi, yj, hl0;
  C_INT ml3, np1;
  double fac;
  C_INT mba, ier;
  double con, yjj;
  C_INT meb1, lenp;
  double srur;
  C_INT mband, meband;

  /* ----------------------------------------------------------------------- */
  /* DPRJA is called by DSTODA to compute and process the matrix */
  /* P = I - H*EL(1)*J , where J is an approximation to the Jacobian. */
  /* Here J is computed by the user-supplied routine JAC if */
  /* MITER = 1 or 4 or by finite differencing if MITER = 2 or 5. */
  /* J, scaled by -H*EL(1), is stored in WM.  Then the norm of J (the */
  /* matrix norm consistent with the weighted max-norm on vectors given */
  /* by DMNORM) is computed, and J is overwritten by P.  P is then */
  /* subjected to LU decomposition in preparation for later solution */
  /* of linear systems with P as coefficient matrix.  This is done */
  /* by DGEFA if MITER = 1 or 2, and by DGBFA if MITER = 4 or 5. */

  /* In addition to variables described previously, communication */
  /* with DPRJA uses the following: */
  /* Y     = array containing predicted values on entry. */
  /* FTEM  = work array of length N (ACOR in DSTODA). */
  /* SAVF  = array containing f evaluated at predicted y. */
  /* WM    = real work space for matrices.  On output it contains the */
  /*         LU decomposition of P. */
  /*         Storage of matrix elements starts at WM(3). */
  /*         WM also contains the following matrix-related data: */
  /*         WM(1) = SQRT(UROUND), used in numerical Jacobian increments. */
  /* IWM   = integer work space containing pivot information, starting at */
  /*         IWM(21).   IWM also contains the band parameters */
  /*         ML = IWM(1) and MU = IWM(2) if MITER is 4 or 5. */
  /* EL0   = EL(1) (input). */
  /* PDNORM= norm of Jacobian matrix. (Output). */
  /* IERPJ = output error flag,  = 0 if no trouble, .gt. 0 if */
  /*         P matrix found to be singular. */
  /* JCUR  = output flag = 1 to indicate that the Jacobian matrix */
  /*         (or approximation) is now current. */
  /* This routine also uses the Common variables EL0, H, TN, UROUND, */
  /* MITER, N, NFE, and NJE. */
  /* ----------------------------------------------------------------------- */
  /* Parameter adjustments */
  --neq;
  --y;
  yh_dim1 = *nyh;
  yh_offset = 1 + yh_dim1;
  yh -= yh_offset;
  --ewt;
  --ftem;
  --savf;
  --wm;
  --iwm;

  /* Function Body */
  ++dls001_1.nje;
  dls001_1.ierpj = 0;
  dls001_1.jcur = 1;
  hl0 = dls001_1.h__ * dls001_1.el0;

  switch (dls001_1.miter)
    {
      case 1: goto L100;

      case 2: goto L200;

      case 3: goto L300;

      case 4: goto L400;

      case 5: goto L500;
    }

  /* If MITER = 1, call JAC and multiply by scalar. ----------------------- */
L100:
  lenp = dls001_1.n * dls001_1.n;
  i__1 = lenp;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L110: */
      wm[i__ + 2] = 0.;
    }

  jac(&neq[1], &dls001_1.tn, &y[1], &c__0, &c__0, &wm[3], &dls001_1.n);
  con = -hl0;
  i__1 = lenp;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L120: */
      wm[i__ + 2] *= con;
    }

  goto L240;
  /* If MITER = 2, make N calls to F to approximate J. -------------------- */
L200:
  fac = dmnorm_(&dls001_1.n, &savf[1], &ewt[1]);
  r0 = fabs(dls001_1.h__) * 1e3 * dls001_1.uround * dls001_1.n * fac;

  if (r0 == 0.)
    {
      r0 = 1.;
    }

  srur = wm[1];
  j1 = 2;
  i__1 = dls001_1.n;

  for (j = 1; j <= i__1; ++j)
    {
      yj = y[j];
      /* Computing MAX */
      d__1 = srur * fabs(yj), d__2 = r0 / ewt[j];
      r__ = std::max(d__1, d__2);
      y[j] += r__;
      fac = -hl0 / r__;
      f(&neq[1], &dls001_1.tn, &y[1], &ftem[1]);
      i__2 = dls001_1.n;

      for (i__ = 1; i__ <= i__2; ++i__)
        {
          /* L220: */
          wm[i__ + j1] = (ftem[i__] - savf[i__]) * fac;
        }

      y[j] = yj;
      j1 += dls001_1.n;
      /* L230: */
    }

  dls001_1.nfe += dls001_1.n;
L240:
  /* Compute norm of Jacobian. -------------------------------------------- */
  dlsa01_2.pdnorm = dfnorm_(&dls001_1.n, &wm[3], &ewt[1]) / fabs(hl0);
  /* Add identity matrix. ------------------------------------------------- */
  j = 3;
  np1 = dls001_1.n + 1;
  i__1 = dls001_1.n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      wm[j] += 1.;
      /* L250: */
      j += np1;
    }

  /* Do LU decomposition on P. -------------------------------------------- */
  dgefa_(&wm[3], &dls001_1.n, &dls001_1.n, &iwm[21], &ier);

  if (ier != 0)
    {
      dls001_1.ierpj = 1;
    }

  return 0;
  /* Dummy block only, since MITER is never 3 in this routine. ------------ */
L300:
  return 0;
  /* If MITER = 4, call JAC and multiply by scalar. ----------------------- */
L400:
  ml = iwm[1];
  mu = iwm[2];
  ml3 = ml + 3;
  mband = ml + mu + 1;
  meband = mband + ml;
  lenp = meband * dls001_1.n;
  i__1 = lenp;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L410: */
      wm[i__ + 2] = 0.;
    }

  jac(&neq[1], &dls001_1.tn, &y[1], &ml, &mu, &wm[ml3], &meband);
  con = -hl0;
  i__1 = lenp;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L420: */
      wm[i__ + 2] *= con;
    }

  goto L570;
  /* If MITER = 5, make MBAND calls to F to approximate J. ---------------- */
L500:
  ml = iwm[1];
  mu = iwm[2];
  mband = ml + mu + 1;
  mba = std::min(mband, dls001_1.n);
  meband = mband + ml;
  meb1 = meband - 1;
  srur = wm[1];
  fac = dmnorm_(&dls001_1.n, &savf[1], &ewt[1]);
  r0 = fabs(dls001_1.h__) * 1e3 * dls001_1.uround * dls001_1.n * fac;

  if (r0 == 0.)
    {
      r0 = 1.;
    }

  i__1 = mba;

  for (j = 1; j <= i__1; ++j)
    {
      i__2 = dls001_1.n;
      i__3 = mband;

      for (i__ = j; i__3 < 0 ? i__ >= i__2 : i__ <= i__2; i__ += i__3)
        {
          yi = y[i__];
          /* Computing MAX */
          d__1 = srur * fabs(yi), d__2 = r0 / ewt[i__];
          r__ = std::max(d__1, d__2);
          /* L530: */
          y[i__] += r__;
        }

      f(&neq[1], &dls001_1.tn, &y[1], &ftem[1]);
      i__3 = dls001_1.n;
      i__2 = mband;

      for (jj = j; i__2 < 0 ? jj >= i__3 : jj <= i__3; jj += i__2)
        {
          y[jj] = yh[jj + yh_dim1];
          yjj = y[jj];
          /* Computing MAX */
          d__1 = srur * fabs(yjj), d__2 = r0 / ewt[jj];
          r__ = std::max(d__1, d__2);
          fac = -hl0 / r__;
          /* Computing MAX */
          i__4 = jj - mu;
          i1 = std::max(i__4, (C_INT)1);
          /* Computing MIN */
          i__4 = jj + ml;
          i2 = std::min(i__4, dls001_1.n);
          ii = jj * meb1 - ml + 2;
          i__4 = i2;

          for (i__ = i1; i__ <= i__4; ++i__)
            {
              /* L540: */
              wm[ii + i__] = (ftem[i__] - savf[i__]) * fac;
            }

          /* L550: */
        }

      /* L560: */
    }

  dls001_1.nfe += mba;
L570:
  /* Compute norm of Jacobian. -------------------------------------------- */
  dlsa01_2.pdnorm = dbnorm_(&dls001_1.n, &wm[ml + 3], &meband, &ml, &mu, &
                            ewt[1]) / fabs(hl0);
  /* Add identity matrix. ------------------------------------------------- */
  ii = mband + 2;
  i__1 = dls001_1.n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      wm[ii] += 1.;
      /* L580: */
      ii += meband;
    }

  /* Do LU decomposition of P. -------------------------------------------- */
  dgbfa_(&wm[3], &meband, &dls001_1.n, &ml, &mu, &iwm[21], &ier);

  if (ier != 0)
    {
      dls001_1.ierpj = 1;
    }

  return 0;
  /* ----------------------- End of Subroutine DPRJA ----------------------- */
} /* dprja_ */
