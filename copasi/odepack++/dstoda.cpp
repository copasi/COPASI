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

#define dls001_1 (mdls001_._1)
#define dls001_2 (mdls001_._2)
#define dls001_3 (mdls001_._3)

#define dlsa01_1 (mdlsa01_._1)
#define dlsa01_2 (mdlsa01_._2)
#define dlsa01_3 (mdlsa01_._3)

static C_INT c__1 = 1;
static C_INT c__2 = 2;

#define pow_dd(__x, __y) pow(*__x, *__y)

#include "dcfode.h"
#include "dmnorm.h"

/* DECK DSTODA */
/* Subroutine */
C_INT CInternalSolver::dstoda_(C_INT *neq, double *y, double *yh,
                               C_INT *nyh, double *yh1, double *ewt, double *savf,
                               double *acor, double *wm, C_INT *iwm,
                               evalF f, evalJ jac, PJAC * pjac, SLVS * slvs)
{
  /* Initialized data */

  static const double sm1[12] =
  {
    .5, .575, .55, .45, .35, .25, .2, .15, .1, .075, .05,
    .025
  };

  /* System generated locals */
  C_INT yh_dim1, yh_offset, i__1, i__2;
  double d__1, d__2, d__3;

  /* Local variables */
  C_INT i__, j, m;
  double r__;
  C_INT i1, jb;
  double rh = 0.0, rm, dm1, dm2;
  C_INT lm1, lm2;
  double rh1, rh2, del, ddn;
  C_INT ncf;
  double pdh = 0.0, dsm, dup, exm1, exm2;
  C_INT nqm1, nqm2;
  double dcon, delp;
  C_INT lm1p1, lm2p1;
  double exdn, rhdn;
  C_INT iret;
  double told, rhsm;
  C_INT newq;
  double exsm, rhup, rate, exup, rh1it, alpha;
  C_INT iredo = 0;
  double pnorm;

  /* Parameter adjustments */
  --neq;
  --y;
  yh_dim1 = *nyh;
  yh_offset = 1 + yh_dim1;
  yh -= yh_offset;
  --yh1;
  --ewt;
  --savf;
  --acor;
  --wm;
  --iwm;

  /* Function Body */
  /* ----------------------------------------------------------------------- */
  /* DSTODA performs one step of the integration of an initial value */
  /* problem for a system of ordinary differential equations. */
  /* Note: DSTODA is independent of the value of the iteration method */
  /* indicator MITER, when this is .ne. 0, and hence is independent */
  /* of the type of chord method used, or the Jacobian structure. */
  /* Communication with DSTODA is done with the following variables: */

  /* Y      = an array of length .ge. N used as the Y argument in */
  /*          all calls to F and JAC. */
  /* NEQ    = integer array containing problem size in NEQ(1), and */
  /*          passed as the NEQ argument in all calls to F and JAC. */
  /* YH     = an NYH by LMAX array containing the dependent variables */
  /*          and their approximate scaled derivatives, where */
  /*          LMAX = MAXORD + 1.  YH(i,j+1) contains the approximate */
  /*          j-th derivative of y(i), scaled by H**j/factorial(j) */
  /*          (j = 0,1,...,NQ).  On entry for the first step, the first */
  /*          two columns of YH must be set from the initial values. */
  /* NYH    = a constant integer .ge. N, the first dimension of YH. */
  /* YH1    = a one-dimensional array occupying the same space as YH. */
  /* EWT    = an array of length N containing multiplicative weights */
  /*          for local error measurements.  Local errors in y(i) are */
  /*          compared to 1.0/EWT(i) in various error tests. */
  /* SAVF   = an array of working storage, of length N. */
  /* ACOR   = a work array of length N, used for the accumulated */
  /*          corrections.  On a successful return, ACOR(i) contains */
  /*          the estimated one-step local error in y(i). */
  /* WM,IWM = real and integer work arrays associated with matrix */
  /*          operations in chord iteration (MITER .ne. 0). */
  /* PJAC   = name of routine to evaluate and preprocess Jacobian matrix */
  /*          and P = I - H*EL0*Jac, if a chord method is being used. */
  /*          It also returns an estimate of norm(Jac) in PDNORM. */
  /* SLVS   = name of routine to solve linear system in chord iteration. */
  /* CCMAX  = maximum relative change in H*EL0 before PJAC is called. */
  /* H      = the step size to be attempted on the next step. */
  /*          H is altered by the error control algorithm during the */
  /*          problem.  H can be either positive or negative, but its */
  /*          sign must remain constant throughout the problem. */
  /* HMIN   = the minimum absolute value of the step size H to be used. */
  /* HMXI   = inverse of the maximum absolute value of H to be used. */
  /*          HMXI = 0.0 is allowed and corresponds to an infinite HMAX. */
  /*          HMIN and HMXI may be changed at any time, but will not */
  /*          take effect until the next change of H is considered. */
  /* TN     = the independent variable. TN is updated on each step taken. */
  /* JSTART = an integer used for input only, with the following */
  /*          values and meanings: */
  /*               0  perform the first step. */
  /*           .gt.0  take a new step continuing from the last. */
  /*              -1  take the next step with a new value of H, */
  /*                    N, METH, MITER, and/or matrix parameters. */
  /*              -2  take the next step with a new value of H, */
  /*                    but with other inputs unchanged. */
  /*          On return, JSTART is set to 1 to facilitate continuation. */
  /* KFLAG  = a completion code with the following meanings: */
  /*               0  the step was succesful. */
  /*              -1  the requested error could not be achieved. */
  /*              -2  corrector convergence could not be achieved. */
  /*              -3  fatal error in PJAC or SLVS. */
  /*          A return with KFLAG = -1 or -2 means either */
  /*          ABS(H) = HMIN or 10 consecutive failures occurred. */
  /*          On a return with KFLAG negative, the values of TN and */
  /*          the YH array are as of the beginning of the last */
  /*          step, and H is the last step size attempted. */
  /* MAXORD = the maximum order of integration method to be allowed. */
  /* MAXCOR = the maximum number of corrector iterations allowed. */
  /* MSBP   = maximum number of steps between PJAC calls (MITER .gt. 0). */
  /* MXNCF  = maximum number of convergence failures allowed. */
  /* METH   = current method. */
  /*          METH = 1 means Adams method (nonstiff) */
  /*          METH = 2 means BDF method (stiff) */
  /*          METH may be reset by DSTODA. */
  /* MITER  = corrector iteration method. */
  /*          MITER = 0 means functional iteration. */
  /*          MITER = JT .gt. 0 means a chord iteration corresponding */
  /*          to Jacobian type JT.  (The DLSODA/DLSODAR argument JT is */
  /*          communicated here as JTYP, but is not used in DSTODA */
  /*          except to load MITER following a method switch.) */
  /*          MITER may be reset by DSTODA. */
  /* N      = the number of first-order differential equations. */
  /* ----------------------------------------------------------------------- */
  dls001_3.kflag = 0;
  told = dls001_3.tn;
  ncf = 0;
  dls001_3.ierpj = 0;
  dls001_3.iersl = 0;
  dls001_3.jcur = 0;
  dls001_3.icf = 0;
  delp = 0.;

  if (dls001_3.jstart > 0)
    {
      goto L200;
    }

  if (dls001_3.jstart == -1)
    {
      goto L100;
    }

  if (dls001_3.jstart == -2)
    {
      goto L160;
    }

  /* ----------------------------------------------------------------------- */
  /* On the first call, the order is set to 1, and other variables are */
  /* initialized.  RMAX is the maximum ratio by which H can be increased */
  /* in a single step.  It is initially 1.E4 to compensate for the small */
  /* initial H, but then is normally equal to 10.  If a failure */
  /* occurs (in corrector convergence or error test), RMAX is set at 2 */
  /* for the next increase. */
  /* DCFODE is called to get the needed coefficients for both methods. */
  /* ----------------------------------------------------------------------- */
  dls001_3.lmax = dls001_3.maxord + 1;
  dls001_3.nq = 1;
  dls001_3.l = 2;
  dls001_3.ialth = 2;
  dls001_3.rmax = 1e4;
  dls001_3.rc = 0.;
  dls001_3.el0 = 1.;
  dls001_3.crate = .7;
  dls001_3.hold = dls001_3.h__;
  dls001_3.nslp = 0;
  dls001_3.ipup = dls001_3.miter;
  iret = 3;
  /* Initialize switching parameters.  METH = 1 is assumed initially. ----- */
  dlsa01_1.icount = 20;
  dlsa01_1.irflag = 0;
  dlsa01_1.pdest = 0.;
  dlsa01_1.pdlast = 0.;
  dlsa01_1.ratio = 5.;
  dcfode_(&c__2, dls001_3.elco, dls001_3.tesco);

  for (i__ = 1; i__ <= 5; ++i__)
    {
      /* L10: */
      dlsa01_1.cm2[i__ - 1] = dls001_3.tesco[i__ * 3 - 2] * dls001_3.elco[
                                i__ + 1 + i__ * 13 - 14];
    }

  dcfode_(&c__1, dls001_3.elco, dls001_3.tesco);

  for (i__ = 1; i__ <= 12; ++i__)
    {
      /* L20: */
      dlsa01_1.cm1[i__ - 1] = dls001_3.tesco[i__ * 3 - 2] * dls001_3.elco[
                                i__ + 1 + i__ * 13 - 14];
    }

  goto L150;
  /* ----------------------------------------------------------------------- */
  /* The following block handles preliminaries needed when JSTART = -1. */
  /* IPUP is set to MITER to force a matrix update. */
  /* If an order increase is about to be considered (IALTH = 1), */
  /* IALTH is reset to 2 to postpone consideration one more step. */
  /* If the caller has changed METH, DCFODE is called to reset */
  /* the coefficients of the method. */
  /* If H is to be changed, YH must be rescaled. */
  /* If H or METH is being changed, IALTH is reset to L = NQ + 1 */
  /* to prevent further changes in H for that many steps. */
  /* ----------------------------------------------------------------------- */
L100:
  dls001_3.ipup = dls001_3.miter;
  dls001_3.lmax = dls001_3.maxord + 1;

  if (dls001_3.ialth == 1)
    {
      dls001_3.ialth = 2;
    }

  if (dls001_3.meth == dlsa01_1.mused)
    {
      goto L160;
    }

  dcfode_(&dls001_3.meth, dls001_3.elco, dls001_3.tesco);
  dls001_3.ialth = dls001_3.l;
  iret = 1;
  /* ----------------------------------------------------------------------- */
  /* The el vector and related constants are reset */
  /* whenever the order NQ is changed, or at the start of the problem. */
  /* ----------------------------------------------------------------------- */
L150:
  i__1 = dls001_3.l;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L155: */
      dls001_3.el[i__ - 1] = dls001_3.elco[i__ + dls001_3.nq * 13 - 14];
    }

  dls001_3.nqnyh = dls001_3.nq * *nyh;
  dls001_3.rc = dls001_3.rc * dls001_3.el[0] / dls001_3.el0;
  dls001_3.el0 = dls001_3.el[0];
  dls001_3.conit = .5 / (dls001_3.nq + 2);

  switch (iret)
    {
      case 1: goto L160;

      case 2: goto L170;

      case 3: goto L200;
    }

  /* ----------------------------------------------------------------------- */
  /* If H is being changed, the H ratio RH is checked against */
  /* RMAX, HMIN, and HMXI, and the YH array rescaled.  IALTH is set to */
  /* L = NQ + 1 to prevent a change of H for that many steps, unless */
  /* forced by a convergence or error test failure. */
  /* ----------------------------------------------------------------------- */
L160:

  if (dls001_3.h__ == dls001_3.hold)
    {
      goto L200;
    }

  rh = dls001_3.h__ / dls001_3.hold;
  dls001_3.h__ = dls001_3.hold;
  iredo = 3;
  goto L175;
L170:
  /* Computing MAX */
  d__1 = rh, d__2 = dls001_3.hmin / fabs(dls001_3.h__);
  rh = std::max(d__1, d__2);
L175:
  rh = std::min(rh, dls001_3.rmax);
  /* Computing MAX */
  d__1 = 1., d__2 = fabs(dls001_3.h__) * dls001_3.hmxi * rh;
  rh /= std::max(d__1, d__2);

  /* ----------------------------------------------------------------------- */

  /* If METH = 1, also restrict the new step size by the stability region. */

  /* If this reduces H, set IRFLAG to 1 so that if there are roundoff */

  /* problems later, we can assume that is the cause of the trouble. */

  /* ----------------------------------------------------------------------- */
  if (dls001_3.meth == 2)
    {
      goto L178;
    }

  dlsa01_1.irflag = 0;
  /* Computing MAX */
  d__1 = fabs(dls001_3.h__) * dlsa01_1.pdlast;
  pdh = std::max(d__1, 1e-6);

  if (rh * pdh * 1.00001 < sm1[dls001_3.nq - 1])
    {
      goto L178;
    }

  rh = sm1[dls001_3.nq - 1] / pdh;
  dlsa01_1.irflag = 1;
L178:
  r__ = 1.;
  i__1 = dls001_3.l;

  for (j = 2; j <= i__1; ++j)
    {
      r__ *= rh;
      i__2 = dls001_3.n;

      for (i__ = 1; i__ <= i__2; ++i__)
        {
          /* L180: */
          yh[i__ + j * yh_dim1] *= r__;
        }
    }

  dls001_3.h__ *= rh;
  dls001_3.rc *= rh;
  dls001_3.ialth = dls001_3.l;

  if (iredo == 0)
    {
      goto L690;
    }

  /* ----------------------------------------------------------------------- */
  /* This section computes the predicted values by effectively */
  /* multiplying the YH array by the Pascal triangle matrix. */
  /* RC is the ratio of new to old values of the coefficient  H*EL(1). */
  /* When RC differs from 1 by more than CCMAX, IPUP is set to MITER */
  /* to force PJAC to be called, if a Jacobian is involved. */
  /* In any case, PJAC is called at least every MSBP steps. */
  /* ----------------------------------------------------------------------- */
L200:

  if ((d__1 = dls001_3.rc - 1., fabs(d__1)) > dls001_3.ccmax)
    {
      dls001_3.ipup = dls001_3.miter;
    }

  if (dls001_3.nst >= dls001_3.nslp + dls001_3.msbp)
    {
      dls001_3.ipup = dls001_3.miter;
    }

  dls001_3.tn += dls001_3.h__;
  i1 = dls001_3.nqnyh + 1;
  i__2 = dls001_3.nq;

  for (jb = 1; jb <= i__2; ++jb)
    {
      i1 -= *nyh;
      /* DIR$ IVDEP */
      i__1 = dls001_3.nqnyh;

      for (i__ = i1; i__ <= i__1; ++i__)
        {
          /* L210: */
          yh1[i__] += yh1[i__ + *nyh];
        }

      /* L215: */
    }

  pnorm = dmnorm_(&dls001_3.n, &yh1[1], &ewt[1]);
  /* ----------------------------------------------------------------------- */
  /* Up to MAXCOR corrector iterations are taken.  A convergence test is */
  /* made on the RMS-norm of each correction, weighted by the error */
  /* weight vector EWT.  The sum of the corrections is accumulated in the */
  /* vector ACOR(i).  The YH array is not altered in the corrector loop. */
  /* ----------------------------------------------------------------------- */
L220:
  m = 0;
  rate = 0.;
  del = 0.;
  i__2 = dls001_3.n;

  for (i__ = 1; i__ <= i__2; ++i__)
    {
      /* L230: */
      y[i__] = yh[i__ + yh_dim1];
    }

  f(&neq[1], &dls001_3.tn, &y[1], &savf[1]);
  ++dls001_3.nfe;

  if (dls001_3.ipup <= 0)
    {
      goto L250;
    }

  /* ----------------------------------------------------------------------- */
  /* If indicated, the matrix P = I - H*EL(1)*J is reevaluated and */
  /* preprocessed before starting the corrector iteration.  IPUP is set */
  /* to 0 as an indicator that this has been done. */
  /* ----------------------------------------------------------------------- */
  (*pjac)(&neq[1], &y[1], &yh[yh_offset], nyh, &ewt[1], &acor[1], &savf[1],
          &wm[1], &iwm[1], f, jac);
  dls001_3.ipup = 0;
  dls001_3.rc = 1.;
  dls001_3.nslp = dls001_3.nst;
  dls001_3.crate = .7;

  if (dls001_3.ierpj != 0)
    {
      goto L430;
    }

L250:
  i__2 = dls001_3.n;

  for (i__ = 1; i__ <= i__2; ++i__)
    {
      /* L260: */
      acor[i__] = 0.;
    }

L270:

  if (dls001_3.miter != 0)
    {
      goto L350;
    }

  /* ----------------------------------------------------------------------- */
  /* In the case of functional iteration, update Y directly from */
  /* the result of the last function evaluation. */
  /* ----------------------------------------------------------------------- */
  i__2 = dls001_3.n;

  for (i__ = 1; i__ <= i__2; ++i__)
    {
      savf[i__] = dls001_3.h__ * savf[i__] - yh[i__ + (yh_dim1 << 1)];
      /* L290: */
      y[i__] = savf[i__] - acor[i__];
    }

  del = dmnorm_(&dls001_3.n, &y[1], &ewt[1]);
  i__2 = dls001_3.n;

  for (i__ = 1; i__ <= i__2; ++i__)
    {
      y[i__] = yh[i__ + yh_dim1] + dls001_3.el[0] * savf[i__];
      /* L300: */
      acor[i__] = savf[i__];
    }

  goto L400;
  /* ----------------------------------------------------------------------- */
  /* In the case of the chord method, compute the corrector error, */
  /* and solve the linear system with that as right-hand side and */
  /* P as coefficient matrix. */
  /* ----------------------------------------------------------------------- */
L350:
  i__2 = dls001_3.n;

  for (i__ = 1; i__ <= i__2; ++i__)
    {
      /* L360: */
      y[i__] = dls001_3.h__ * savf[i__] - (yh[i__ + (yh_dim1 << 1)] + acor[
                                             i__]);
    }

  (*slvs)(&wm[1], &iwm[1], &y[1], &savf[1]);

  if (dls001_3.iersl < 0)
    {
      goto L430;
    }

  if (dls001_3.iersl > 0)
    {
      goto L410;
    }

  del = dmnorm_(&dls001_3.n, &y[1], &ewt[1]);
  i__2 = dls001_3.n;

  for (i__ = 1; i__ <= i__2; ++i__)
    {
      acor[i__] += y[i__];
      /* L380: */
      y[i__] = yh[i__ + yh_dim1] + dls001_3.el[0] * acor[i__];
    }

  /* ----------------------------------------------------------------------- */
  /* Test for convergence.  If M .gt. 0, an estimate of the convergence */
  /* rate constant is stored in CRATE, and this is used in the test. */

  /* We first check for a change of iterates that is the size of */
  /* roundoff error.  If this occurs, the iteration has converged, and a */
  /* new rate estimate is not formed. */
  /* In all other cases, force at least two iterations to estimate a */
  /* local Lipschitz constant estimate for Adams methods. */
  /* On convergence, form PDEST = local maximum Lipschitz constant */
  /* estimate.  PDLAST is the most recent nonzero estimate. */
  /* ----------------------------------------------------------------------- */
L400:

  if (del <= pnorm * 100. * dls001_3.uround)
    {
      goto L450;
    }

  if (m == 0 && dls001_3.meth == 1)
    {
      goto L405;
    }

  if (m == 0)
    {
      goto L402;
    }

  rm = 1024.;

  if (del <= delp * 1024.)
    {
      rm = del / delp;
    }

  rate = std::max(rate, rm);
  /* Computing MAX */
  d__1 = dls001_3.crate * .2;
  dls001_3.crate = std::max(d__1, rm);
L402:
  /* Computing MIN */
  d__1 = 1., d__2 = dls001_3.crate * 1.5;
  dcon = del * std::min(d__1, d__2) / (dls001_3.tesco[dls001_3.nq * 3 - 2] *
                                       dls001_3.conit);

  if (dcon > 1.)
    {
      goto L405;
    }

  /* Computing MAX */
  d__2 = dlsa01_1.pdest, d__3 = rate / (d__1 = dls001_3.h__ * dls001_3.el[0]
                                        , fabs(d__1));
  dlsa01_1.pdest = std::max(d__2, d__3);

  if (dlsa01_1.pdest != 0.)
    {
      dlsa01_1.pdlast = dlsa01_1.pdest;
    }

  goto L450;
L405:
  ++m;

  if (m == dls001_3.maxcor)
    {
      goto L410;
    }

  if (m >= 2 && del > delp * 2.)
    {
      goto L410;
    }

  delp = del;
  f(&neq[1], &dls001_3.tn, &y[1], &savf[1]);
  ++dls001_3.nfe;
  goto L270;
  /* ----------------------------------------------------------------------- */
  /* The corrector iteration failed to converge. */
  /* If MITER .ne. 0 and the Jacobian is out of date, PJAC is called for */
  /* the next try.  Otherwise the YH array is retracted to its values */
  /* before prediction, and H is reduced, if possible.  If H cannot be */
  /* reduced or MXNCF failures have occurred, exit with KFLAG = -2. */
  /* ----------------------------------------------------------------------- */
L410:

  if (dls001_3.miter == 0 || dls001_3.jcur == 1)
    {
      goto L430;
    }

  dls001_3.icf = 1;
  dls001_3.ipup = dls001_3.miter;
  goto L220;
L430:
  dls001_3.icf = 2;
  ++ncf;
  dls001_3.rmax = 2.;
  dls001_3.tn = told;
  i1 = dls001_3.nqnyh + 1;
  i__2 = dls001_3.nq;

  for (jb = 1; jb <= i__2; ++jb)
    {
      i1 -= *nyh;
      /* DIR$ IVDEP */
      i__1 = dls001_3.nqnyh;

      for (i__ = i1; i__ <= i__1; ++i__)
        {
          /* L440: */
          yh1[i__] -= yh1[i__ + *nyh];
        }

      /* L445: */
    }

  if (dls001_3.ierpj < 0 || dls001_3.iersl < 0)
    {
      goto L680;
    }

  if (fabs(dls001_3.h__) <= dls001_3.hmin * 1.00001)
    {
      goto L670;
    }

  if (ncf == dls001_3.mxncf)
    {
      goto L670;
    }

  rh = .25;
  dls001_3.ipup = dls001_3.miter;
  iredo = 1;
  goto L170;
  /* ----------------------------------------------------------------------- */
  /* The corrector has converged.  JCUR is set to 0 */
  /* to signal that the Jacobian involved may need updating later. */
  /* The local error test is made and control passes to statement 500 */
  /* if it fails. */
  /* ----------------------------------------------------------------------- */
L450:
  dls001_3.jcur = 0;

  if (m == 0)
    {
      dsm = del / dls001_3.tesco[dls001_3.nq * 3 - 2];
    }

  if (m > 0)
    {
      dsm = dmnorm_(&dls001_3.n, &acor[1], &ewt[1]) / dls001_3.tesco[
              dls001_3.nq * 3 - 2];
    }

  if (dsm > 1.)
    {
      goto L500;
    }

  /* ----------------------------------------------------------------------- */
  /* After a successful step, update the YH array. */
  /* Decrease ICOUNT by 1, and if it is -1, consider switching methods. */
  /* If a method switch is made, reset various parameters, */
  /* rescale the YH array, and exit.  If there is no switch, */
  /* consider changing H if IALTH = 1.  Otherwise decrease IALTH by 1. */
  /* If IALTH is then 1 and NQ .lt. MAXORD, then ACOR is saved for */
  /* use in a possible order increase on the next step. */
  /* If a change in H is considered, an increase or decrease in order */
  /* by one is considered also.  A change in H is made only if it is by a */
  /* factor of at least 1.1.  If not, IALTH is set to 3 to prevent */
  /* testing for that many steps. */
  /* ----------------------------------------------------------------------- */
  dls001_3.kflag = 0;
  iredo = 0;
  ++dls001_3.nst;
  dls001_3.hu = dls001_3.h__;
  dls001_3.nqu = dls001_3.nq;
  dlsa01_1.mused = dls001_3.meth;
  i__2 = dls001_3.l;

  for (j = 1; j <= i__2; ++j)
    {
      i__1 = dls001_3.n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          /* L460: */
          yh[i__ + j * yh_dim1] += dls001_3.el[j - 1] * acor[i__];
        }
    }

  --dlsa01_1.icount;

  if (dlsa01_1.icount >= 0)
    {
      goto L488;
    }

  if (dls001_3.meth == 2)
    {
      goto L480;
    }

  /* ----------------------------------------------------------------------- */
  /* We are currently using an Adams method.  Consider switching to BDF. */
  /* If the current order is greater than 5, assume the problem is */
  /* not stiff, and skip this section. */
  /* If the Lipschitz constant and error estimate are not polluted */
  /* by roundoff, go to 470 and perform the usual test. */
  /* Otherwise, switch to the BDF methods if the last step was */
  /* restricted to insure stability (irflag = 1), and stay with Adams */
  /* method if not.  When switching to BDF with polluted error estimates, */
  /* in the absence of other information, double the step size. */

  /* When the estimates are OK, we make the usual test by computing */

  /* the step size we could have (ideally) used on this step, */

  /* with the current (Adams) method, and also that for the BDF. */

  /* If NQ .gt. MXORDS, we consider changing to order MXORDS on switching. */

  /* Compare the two step sizes to decide whether to switch. */

  /* The step size advantage must be at least RATIO = 5 to switch. */

  /* ----------------------------------------------------------------------- */
  if (dls001_3.nq > 5)
    {
      goto L488;
    }

  if (dsm > pnorm * 100. * dls001_3.uround && dlsa01_1.pdest != 0.)
    {
      goto L470;
    }

  if (dlsa01_1.irflag == 0)
    {
      goto L488;
    }

  rh2 = 2.;
  nqm2 = std::min(dls001_3.nq, dlsa01_1.mxords);
  goto L478;
L470:
  exsm = 1. / dls001_3.l;
  rh1 = 1. / (pow_dd(&dsm, &exsm) * 1.2 + 1.2e-6);
  rh1it = rh1 * 2.;
  pdh = dlsa01_1.pdlast * fabs(dls001_3.h__);

  if (pdh * rh1 > 1e-5)
    {
      rh1it = sm1[dls001_3.nq - 1] / pdh;
    }

  rh1 = std::min(rh1, rh1it);

  if (dls001_3.nq <= dlsa01_1.mxords)
    {
      goto L474;
    }

  nqm2 = dlsa01_1.mxords;
  lm2 = dlsa01_1.mxords + 1;
  exm2 = 1. / lm2;
  lm2p1 = lm2 + 1;
  dm2 = dmnorm_(&dls001_3.n, &yh[lm2p1 * yh_dim1 + 1], &ewt[1]) /
        dlsa01_1.cm2[dlsa01_1.mxords - 1];
  rh2 = 1. / (pow_dd(&dm2, &exm2) * 1.2 + 1.2e-6);
  goto L476;
L474:
  dm2 = dsm * (dlsa01_1.cm1[dls001_3.nq - 1] / dlsa01_1.cm2[dls001_3.nq - 1]
              );
  rh2 = 1. / (pow_dd(&dm2, &exsm) * 1.2 + 1.2e-6);
  nqm2 = dls001_3.nq;
L476:

  if (rh2 < dlsa01_1.ratio * rh1)
    {
      goto L488;
    }

  /* THE SWITCH TEST PASSED.  RESET RELEVANT QUANTITIES FOR BDF. ---------- */
L478:
  rh = rh2;
  dlsa01_1.icount = 20;
  dls001_3.meth = 2;
  dls001_3.miter = dlsa01_1.jtyp;
  dlsa01_1.pdlast = 0.;
  dls001_3.nq = nqm2;
  dls001_3.l = dls001_3.nq + 1;
  goto L170;
  /* ----------------------------------------------------------------------- */
  /* We are currently using a BDF method.  Consider switching to Adams. */
  /* Compute the step size we could have (ideally) used on this step, */
  /* with the current (BDF) method, and also that for the Adams. */
  /* If NQ .gt. MXORDN, we consider changing to order MXORDN on switching. */
  /* Compare the two step sizes to decide whether to switch. */
  /* The step size advantage must be at least 5/RATIO = 1 to switch. */
  /* If the step size for Adams would be so small as to cause */
  /* roundoff pollution, we stay with BDF. */
  /* ----------------------------------------------------------------------- */
L480:
  exsm = 1. / dls001_3.l;

  if (dlsa01_1.mxordn >= dls001_3.nq)
    {
      goto L484;
    }

  nqm1 = dlsa01_1.mxordn;
  lm1 = dlsa01_1.mxordn + 1;
  exm1 = 1. / lm1;
  lm1p1 = lm1 + 1;
  dm1 = dmnorm_(&dls001_3.n, &yh[lm1p1 * yh_dim1 + 1], &ewt[1]) /
        dlsa01_1.cm1[dlsa01_1.mxordn - 1];
  rh1 = 1. / (pow_dd(&dm1, &exm1) * 1.2 + 1.2e-6);
  goto L486;
L484:
  dm1 = dsm * (dlsa01_1.cm2[dls001_3.nq - 1] / dlsa01_1.cm1[dls001_3.nq - 1]
              );
  rh1 = 1. / (pow_dd(&dm1, &exsm) * 1.2 + 1.2e-6);
  nqm1 = dls001_3.nq;
  exm1 = exsm;
L486:
  rh1it = rh1 * 2.;
  pdh = dlsa01_1.pdnorm * fabs(dls001_3.h__);

  if (pdh * rh1 > 1e-5)
    {
      rh1it = sm1[nqm1 - 1] / pdh;
    }

  rh1 = std::min(rh1, rh1it);
  rh2 = 1. / (pow_dd(&dsm, &exsm) * 1.2 + 1.2e-6);

  if (rh1 * dlsa01_1.ratio < rh2 * 5.)
    {
      goto L488;
    }

  alpha = std::max(.001, rh1);
  dm1 = pow_dd(&alpha, &exm1) * dm1;

  if (dm1 <= dls001_3.uround * 1e3 * pnorm)
    {
      goto L488;
    }

  /* The switch test passed.  Reset relevant quantities for Adams. -------- */
  rh = rh1;
  dlsa01_1.icount = 20;
  dls001_3.meth = 1;
  dls001_3.miter = 0;
  dlsa01_1.pdlast = 0.;
  dls001_3.nq = nqm1;
  dls001_3.l = dls001_3.nq + 1;
  goto L170;

  /* No method switch is being made.  Do the usual step/order selection. -- */
L488:
  --dls001_3.ialth;

  if (dls001_3.ialth == 0)
    {
      goto L520;
    }

  if (dls001_3.ialth > 1)
    {
      goto L700;
    }

  if (dls001_3.l == dls001_3.lmax)
    {
      goto L700;
    }

  i__1 = dls001_3.n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L490: */
      yh[i__ + dls001_3.lmax * yh_dim1] = acor[i__];
    }

  goto L700;
  /* ----------------------------------------------------------------------- */
  /* The error test failed.  KFLAG keeps track of multiple failures. */
  /* Restore TN and the YH array to their previous values, and prepare */
  /* to try the step again.  Compute the optimum step size for this or */
  /* one lower order.  After 2 or more failures, H is forced to decrease */
  /* by a factor of 0.2 or less. */
  /* ----------------------------------------------------------------------- */
L500:
  --dls001_3.kflag;
  dls001_3.tn = told;
  i1 = dls001_3.nqnyh + 1;
  i__1 = dls001_3.nq;

  for (jb = 1; jb <= i__1; ++jb)
    {
      i1 -= *nyh;
      /* DIR$ IVDEP */
      i__2 = dls001_3.nqnyh;

      for (i__ = i1; i__ <= i__2; ++i__)
        {
          /* L510: */
          yh1[i__] -= yh1[i__ + *nyh];
        }

      /* L515: */
    }

  dls001_3.rmax = 2.;

  if (fabs(dls001_3.h__) <= dls001_3.hmin * 1.00001)
    {
      goto L660;
    }

  if (dls001_3.kflag <= -3)
    {
      goto L640;
    }

  iredo = 2;
  rhup = 0.;
  goto L540;
  /* ----------------------------------------------------------------------- */
  /* Regardless of the success or failure of the step, factors */
  /* RHDN, RHSM, and RHUP are computed, by which H could be multiplied */
  /* at order NQ - 1, order NQ, or order NQ + 1, respectively. */
  /* In the case of failure, RHUP = 0.0 to avoid an order increase. */
  /* The largest of these is determined and the new order chosen */
  /* accordingly.  If the order is to be increased, we compute one */
  /* additional scaled derivative. */
  /* ----------------------------------------------------------------------- */
L520:
  rhup = 0.;

  if (dls001_3.l == dls001_3.lmax)
    {
      goto L540;
    }

  i__1 = dls001_3.n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L530: */
      savf[i__] = acor[i__] - yh[i__ + dls001_3.lmax * yh_dim1];
    }

  dup = dmnorm_(&dls001_3.n, &savf[1], &ewt[1]) / dls001_3.tesco[
          dls001_3.nq * 3 - 1];
  exup = 1. / (dls001_3.l + 1);
  rhup = 1. / (pow_dd(&dup, &exup) * 1.4 + 1.4e-6);
L540:
  exsm = 1. / dls001_3.l;
  rhsm = 1. / (pow_dd(&dsm, &exsm) * 1.2 + 1.2e-6);
  rhdn = 0.;

  if (dls001_3.nq == 1)
    {
      goto L550;
    }

  ddn = dmnorm_(&dls001_3.n, &yh[dls001_3.l * yh_dim1 + 1], &ewt[1]) /
        dls001_3.tesco[dls001_3.nq * 3 - 3];
  exdn = 1. / dls001_3.nq;
  rhdn = 1. / (pow_dd(&ddn, &exdn) * 1.3 + 1.3e-6);
  /* If METH = 1, limit RH according to the stability region also. -------- */
L550:

  if (dls001_3.meth == 2)
    {
      goto L560;
    }

  /* Computing MAX */
  d__1 = fabs(dls001_3.h__) * dlsa01_1.pdlast;
  pdh = std::max(d__1, 1e-6);

  if (dls001_3.l < dls001_3.lmax)
    {
      /* Computing MIN */
      d__1 = rhup, d__2 = sm1[dls001_3.l - 1] / pdh;
      rhup = std::min(d__1, d__2);
    }

  /* Computing MIN */
  d__1 = rhsm, d__2 = sm1[dls001_3.nq - 1] / pdh;
  rhsm = std::min(d__1, d__2);

  if (dls001_3.nq > 1)
    {
      /* Computing MIN */
      d__1 = rhdn, d__2 = sm1[dls001_3.nq - 2] / pdh;
      rhdn = std::min(d__1, d__2);
    }

  dlsa01_1.pdest = 0.;
L560:

  if (rhsm >= rhup)
    {
      goto L570;
    }

  if (rhup > rhdn)
    {
      goto L590;
    }

  goto L580;
L570:

  if (rhsm < rhdn)
    {
      goto L580;
    }

  newq = dls001_3.nq;
  rh = rhsm;
  goto L620;
L580:
  newq = dls001_3.nq - 1;
  rh = rhdn;

  if (dls001_3.kflag < 0 && rh > 1.)
    {
      rh = 1.;
    }

  goto L620;
L590:
  newq = dls001_3.l;
  rh = rhup;

  if (rh < 1.1)
    {
      goto L610;
    }

  r__ = dls001_3.el[dls001_3.l - 1] / dls001_3.l;
  i__1 = dls001_3.n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L600: */
      yh[i__ + (newq + 1) * yh_dim1] = acor[i__] * r__;
    }

  goto L630;
L610:
  dls001_3.ialth = 3;
  goto L700;
  /* If METH = 1 and H is restricted by stability, bypass 10 percent test. */
L620:

  if (dls001_3.meth == 2)
    {
      goto L622;
    }

  if (rh * pdh * 1.00001 >= sm1[newq - 1])
    {
      goto L625;
    }

L622:

  if (dls001_3.kflag == 0 && rh < 1.1)
    {
      goto L610;
    }

L625:

  if (dls001_3.kflag <= -2)
    {
      rh = std::min(rh, .2);
    }

  /* ----------------------------------------------------------------------- */

  /* If there is a change of order, reset NQ, L, and the coefficients. */

  /* In any case H is reset according to RH and the YH array is rescaled. */

  /* Then exit from 690 if the step was OK, or redo the step otherwise. */

  /* ----------------------------------------------------------------------- */
  if (newq == dls001_3.nq)
    {
      goto L170;
    }

L630:
  dls001_3.nq = newq;
  dls001_3.l = dls001_3.nq + 1;
  iret = 2;
  goto L150;
  /* ----------------------------------------------------------------------- */
  /* Control reaches this section if 3 or more failures have occured. */
  /* If 10 failures have occurred, exit with KFLAG = -1. */
  /* It is assumed that the derivatives that have accumulated in the */
  /* YH array have errors of the wrong order.  Hence the first */
  /* derivative is recomputed, and the order is set to 1.  Then */
  /* H is reduced by a factor of 10, and the step is retried, */
  /* until it succeeds or H reaches HMIN. */
  /* ----------------------------------------------------------------------- */
L640:

  if (dls001_3.kflag == -10)
    {
      goto L660;
    }

  rh = .1;
  /* Computing MAX */
  d__1 = dls001_3.hmin / fabs(dls001_3.h__);
  rh = std::max(d__1, rh);
  dls001_3.h__ *= rh;
  i__1 = dls001_3.n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L645: */
      y[i__] = yh[i__ + yh_dim1];
    }

  f(&neq[1], &dls001_3.tn, &y[1], &savf[1]);
  ++dls001_3.nfe;
  i__1 = dls001_3.n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L650: */
      yh[i__ + (yh_dim1 << 1)] = dls001_3.h__ * savf[i__];
    }

  dls001_3.ipup = dls001_3.miter;
  dls001_3.ialth = 5;

  if (dls001_3.nq == 1)
    {
      goto L200;
    }

  dls001_3.nq = 1;
  dls001_3.l = 2;
  iret = 3;
  goto L150;
  /* ----------------------------------------------------------------------- */
  /* All returns are made through this section.  H is saved in HOLD */
  /* to allow the caller to change H on the next step. */
  /* ----------------------------------------------------------------------- */
L660:
  dls001_3.kflag = -1;
  goto L720;
L670:
  dls001_3.kflag = -2;
  goto L720;
L680:
  dls001_3.kflag = -3;
  goto L720;
L690:
  dls001_3.rmax = 10.;
L700:
  r__ = 1. / dls001_3.tesco[dls001_3.nqu * 3 - 2];
  i__1 = dls001_3.n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L710: */
      acor[i__] *= r__;
    }

L720:
  dls001_3.hold = dls001_3.h__;
  dls001_3.jstart = 1;
  return 0;
  /* ----------------------- End of Subroutine DSTODA ---------------------- */
} /* dstoda_ */
