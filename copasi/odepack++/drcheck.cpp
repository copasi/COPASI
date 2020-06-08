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

#include "copasi/lapack/blaswrap.h"
#include "copasi/lapack/lapackwrap.h"

#define dls001_1 (mdls001_._1)
#define dls001_2 (mdls001_._2)
#define dls001_3 (mdls001_._3)

#define dlsr01_1 (mdlsr01_._1)
#define dlsr01_2 (mdlsr01_._2)
#define dlsr01_3 (mdlsr01_._3)

double d_sign(const double & a, const double & b);

static double c_b3 = 1.0;

static const C_INT c__0 = 0;
static C_INT c__1 = 1;

/* DECK DRCHEK */
/* Subroutine */
C_INT CInternalSolver::drchek_(const C_INT *job, evalG g, C_INT *neq, double *
                               y, double *yh, C_INT *nyh, double *g0, double *g1,
                               double *gx, C_INT *jroot, C_INT *irt)
{
  /* System generated locals */
  C_INT yh_dim1, yh_offset, i__1;
  double d__1;

  /* Local variables */
  C_INT i__;
  double x, t1, temp1, temp2;
  C_INT iflag, jflag;
  double hming;
  bool zroot;

  /* ----------------------------------------------------------------------- */
  /* This routine checks for the presence of a root in the vicinity of */
  /* the current T, in a manner depending on the input flag JOB.  It calls */
  /* Subroutine DROOTS to locate the root as precisely as possible. */

  /* In addition to variables described previously, DRCHEK */
  /* uses the following for communication: */
  /* JOB    = integer flag indicating type of call: */
  /*          JOB = 1 means the problem is being initialized, and DRCHEK */
  /*                  is to look for a root at or very near the initial T. */
  /*          JOB = 2 means a continuation call to the solver was just */
  /*                  made, and DRCHEK is to check for a root in the */
  /*                  relevant part of the step last taken. */
  /*          JOB = 3 means a successful step was just taken, and DRCHEK */
  /*                  is to look for a root in the interval of the step. */
  /* G0     = array of length NG, containing the value of g at T = T0. */
  /*          G0 is input for JOB .ge. 2, and output in all cases. */
  /* G1,GX  = arrays of length NG for work space. */
  /* IRT    = completion flag: */
  /*          IRT = 0  means no root was found. */
  /*          IRT = -1 means JOB = 1 and a root was found too near to T. */
  /*          IRT = 1  means a legitimate root was found (JOB = 2 or 3). */
  /*                   On return, T0 is the root location, and Y is the */
  /*                   corresponding solution vector. */
  /* T0     = value of T at one endpoint of interval of interest.  Only */
  /*          roots beyond T0 in the direction of integration are sought. */
  /*          T0 is input if JOB .ge. 2, and output in all cases. */
  /*          T0 is updated by DRCHEK, whether a root is found or not. */
  /* TLAST  = last value of T returned by the solver (input only). */
  /* TOUTC  = copy of TOUT (input only). */
  /* IRFND  = input flag showing whether the last step taken had a root. */
  /*          IRFND = 1 if it did, = 0 if not. */
  /* ITASKC = copy of ITASK (input only). */
  /* NGC    = copy of NG (input only). */
  /* ----------------------------------------------------------------------- */
  /* Parameter adjustments */
  --neq;
  --y;
  yh_dim1 = *nyh;
  yh_offset = 1 + yh_dim1;
  yh -= yh_offset;
  --g0;
  --g1;
  --gx;
  --jroot;

  /* Function Body */
  *irt = 0;
  i__1 = dlsr01_1.ngc;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L10: */
      jroot[i__] = 0;
    }

  hming = (fabs(dls001_1.tn) + fabs(dls001_1.h__)) * dls001_1.uround * 100.;

  switch (*job)
    {
      case 1: goto L100;

      case 2: goto L200;

      case 3: goto L300;
    }

  /* Evaluate g at initial T, and check for zero values. ------------------ */
L100:
  dlsr01_1.t0 = dls001_1.tn;
  (*g)(&neq[1], &dlsr01_1.t0, &y[1], &dlsr01_1.ngc, &g0[1]);
  dlsr01_1.nge = 1;
  zroot = false;
  i__1 = dlsr01_1.ngc;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L110: */
      if ((d__1 = g0[i__], fabs(d__1)) <= 0.)
        {
          zroot = true;
        }
    }

  if (! zroot)
    {
      goto L190;
    }

  /* g has a zero at T.  Look at g at T + (small increment). -------------- */
  /* Computing MAX */
  d__1 = hming / fabs(dls001_1.h__);
  temp2 = std::max(d__1, .1);
  temp1 = temp2 * dls001_1.h__;
  dlsr01_1.t0 += temp1;
  i__1 = dls001_1.n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L120: */
      y[i__] += temp2 * yh[i__ + (yh_dim1 << 1)];
    }

  (*g)(&neq[1], &dlsr01_1.t0, &y[1], &dlsr01_1.ngc, &g0[1]);
  ++dlsr01_1.nge;
  zroot = false;
  i__1 = dlsr01_1.ngc;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L130: */
      if ((d__1 = g0[i__], fabs(d__1)) <= 0.)
        {
          zroot = true;
        }
    }

  if (! zroot)
    {
      goto L190;
    }

  /* g has a zero at T and also close to T.  Take error return. ----------- */
  *irt = -1;
  return 0;

L190:
  return 0;

L200:

  if (dlsr01_1.irfnd == 0)
    {
      goto L260;
    }

  /* If a root was found on the previous step, evaluate G0 = g(T0). ------- */
  dintdy_(&dlsr01_1.t0, &c__0, &yh[yh_offset], nyh, &y[1], &iflag);
  (*g)(&neq[1], &dlsr01_1.t0, &y[1], &dlsr01_1.ngc, &g0[1]);
  ++dlsr01_1.nge;
  zroot = false;
  i__1 = dlsr01_1.ngc;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L210: */
      if ((d__1 = g0[i__], fabs(d__1)) <= 0.)
        {
          zroot = true;
        }
    }

  if (! zroot)
    {
      goto L260;
    }

  /* g has a zero at T0.  Look at g at T + (small increment). ------------- */
  temp1 = d_sign(hming, dls001_1.h__);
  dlsr01_1.t0 += temp1;

  if ((dlsr01_1.t0 - dls001_1.tn) * dls001_1.h__ < 0.)
    {
      goto L230;
    }

  temp2 = temp1 / dls001_1.h__;
  i__1 = dls001_1.n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L220: */
      y[i__] += temp2 * yh[i__ + (yh_dim1 << 1)];
    }

  goto L240;
L230:
  dintdy_(&dlsr01_1.t0, &c__0, &yh[yh_offset], nyh, &y[1], &iflag);
L240:
  (*g)(&neq[1], &dlsr01_1.t0, &y[1], &dlsr01_1.ngc, &g0[1]);
  ++dlsr01_1.nge;
  zroot = false;
  i__1 = dlsr01_1.ngc;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      if ((d__1 = g0[i__], fabs(d__1)) > 0.)
        {
          goto L250;
        }

      jroot[i__] = 1;
      zroot = true;
L250:
      ;
    }

  if (! zroot)
    {
      goto L260;
    }

  /* g has a zero at T0 and also close to T0.  Return root. --------------- */
  *irt = 1;
  return 0;
  /* G0 has no zero components.  Proceed to check relevant interval. ------ */
L260:

  if (dls001_1.tn == dlsr01_1.tlast)
    {
      goto L390;
    }

L300:

  /* Set T1 to TN or TOUTC, whichever comes first, and get g at T1. ------- */
  if (dlsr01_1.itaskc == 2 || dlsr01_1.itaskc == 3 || dlsr01_1.itaskc == 5)
    {
      goto L310;
    }

  if ((dlsr01_1.toutc - dls001_1.tn) * dls001_1.h__ >= 0.)
    {
      goto L310;
    }

  t1 = dlsr01_1.toutc;

  if ((t1 - dlsr01_1.t0) * dls001_1.h__ <= 0.)
    {
      goto L390;
    }

  dintdy_(&t1, &c__0, &yh[yh_offset], nyh, &y[1], &iflag);
  goto L330;
L310:
  t1 = dls001_1.tn;
  i__1 = dls001_1.n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L320: */
      y[i__] = yh[i__ + yh_dim1];
    }

L330:
  (*g)(&neq[1], &t1, &y[1], &dlsr01_1.ngc, &g1[1]);
  ++dlsr01_1.nge;
  /* Call DROOTS to search for root in interval from T0 to T1. ------------ */
  jflag = 0;
L350:
  droots_(&dlsr01_1.ngc, &hming, &jflag, &dlsr01_1.t0, &t1, &g0[1], &g1[1],
          &gx[1], &x, &jroot[1]);

  if (jflag > 1)
    {
      goto L360;
    }

  dintdy_(&x, &c__0, &yh[yh_offset], nyh, &y[1], &iflag);
  (*g)(&neq[1], &x, &y[1], &dlsr01_1.ngc, &gx[1]);
  ++dlsr01_1.nge;
  goto L350;
L360:
  dlsr01_1.t0 = x;
  dcopy_(&dlsr01_1.ngc, &gx[1], &c__1, &g0[1], &c__1);

  if (jflag == 4)
    {
      goto L390;
    }

  /* Found a root.  Interpolate to X and return. -------------------------- */
  dintdy_(&x, &c__0, &yh[yh_offset], nyh, &y[1], &iflag);
  *irt = 1;
  return 0;

L390:
  return 0;
  /* ----------------------- End of Subroutine DRCHEK ---------------------- */
} /* drchek_ */

/* DECK DROOTS */
/* Subroutine */
C_INT CInternalSolver::droots_(C_INT *ng, double *hmin, C_INT *jflag,
                               double *x0, double *x1, double *g0, double *g1,
                               double *gx, double *x, C_INT *jroot)
{
  /* Initialized data */

  static double zero = 0.;
  static double half = .5;
  static double tenth = .1;
  static double five = 5.;

  /* System generated locals */
  C_INT i__1;
  double d__1;

  /* Local variables */
  C_INT i__;
  double t2, tmax;
  bool xroot, zroot, sgnchg;
  C_INT imxold, nxlast;
  double fracsub, fracint;

  /* ----------------------------------------------------------------------- */
  /* This subroutine finds the leftmost root of a set of arbitrary */
  /* functions gi(x) (i = 1,...,NG) in an interval (X0,X1).  Only roots */
  /* of odd multiplicity (i.e. changes of sign of the gi) are found. */
  /* Here the sign of X1 - X0 is arbitrary, but is constant for a given */
  /* problem, and -leftmost- means nearest to X0. */
  /* The values of the vector-valued function g(x) = (gi, i=1...NG) */
  /* are communicated through the call sequence of DROOTS. */
  /* The method used is the Illinois algorithm. */

  /* Reference: */
  /* Kathie L. Hiebert and Lawrence F. Shampine, Implicitly Defined */
  /* Output Points for Solutions of ODEs, Sandia Report SAND80-0180, */
  /* February 1980. */

  /* Description of parameters. */

  /* NG     = number of functions gi, or the number of components of */
  /*          the vector valued function g(x).  Input only. */

  /* HMIN   = resolution parameter in X.  Input only.  When a root is */
  /*          found, it is located only to within an error of HMIN in X. */
  /*          Typically, HMIN should be set to something on the order of */
  /*               100 * UROUND * MAX(ABS(X0),ABS(X1)), */
  /*          where UROUND is the unit roundoff of the machine. */

  /* JFLAG  = integer flag for input and output communication. */

  /*          On input, set JFLAG = 0 on the first call for the problem, */
  /*          and leave it unchanged until the problem is completed. */
  /*          (The problem is completed when JFLAG .ge. 2 on return.) */

  /*          On output, JFLAG has the following values and meanings: */
  /*          JFLAG = 1 means DROOTS needs a value of g(x).  Set GX = g(X) */
  /*                    and call DROOTS again. */
  /*          JFLAG = 2 means a root has been found.  The root is */
  /*                    at X, and GX contains g(X).  (Actually, X is the */
  /*                    rightmost approximation to the root on an interval */
  /*                    (X0,X1) of size HMIN or less.) */
  /*          JFLAG = 3 means X = X1 is a root, with one or more of the gi */
  /*                    being zero at X1 and no sign changes in (X0,X1). */
  /*                    GX contains g(X) on output. */
  /*          JFLAG = 4 means no roots (of odd multiplicity) were */
  /*                    found in (X0,X1) (no sign changes). */

  /* X0,X1  = endpoints of the interval where roots are sought. */
  /*          X1 and X0 are input when JFLAG = 0 (first call), and */
  /*          must be left unchanged between calls until the problem is */
  /*          completed.  X0 and X1 must be distinct, but X1 - X0 may be */
  /*          of either sign.  However, the notion of -left- and -right- */
  /*          will be used to mean nearer to X0 or X1, respectively. */
  /*          When JFLAG .ge. 2 on return, X0 and X1 are output, and */
  /*          are the endpoints of the relevant interval. */

  /* G0,G1  = arrays of length NG containing the vectors g(X0) and g(X1), */
  /*          respectively.  When JFLAG = 0, G0 and G1 are input and */
  /*          none of the G0(i) should be zero. */
  /*          When JFLAG .ge. 2 on return, G0 and G1 are output. */

  /* GX     = array of length NG containing g(X).  GX is input */
  /*          when JFLAG = 1, and output when JFLAG .ge. 2. */

  /* X      = independent variable value.  Output only. */
  /*          When JFLAG = 1 on output, X is the point at which g(x) */
  /*          is to be evaluated and loaded into GX. */
  /*          When JFLAG = 2 or 3, X is the root. */
  /*          When JFLAG = 4, X is the right endpoint of the interval, X1. */

  /* JROOT  = integer array of length NG.  Output only. */
  /*          When JFLAG = 2 or 3, JROOT indicates which components */
  /*          of g(x) have a root at X.  JROOT(i) is 1 if the i-th */
  /*          component has a root, and JROOT(i) = 0 otherwise. */
  /* ----------------------------------------------------------------------- */
  /* Parameter adjustments */
  --jroot;
  --gx;
  --g1;
  --g0;

  /* Function Body */

  if (*jflag == 1)
    {
      goto L200;
    }

  /* JFLAG .ne. 1.  Check for change in sign of g or zero at X1. ---------- */
  dlsr01_2.imax = 0;
  tmax = zero;
  zroot = false;
  i__1 = *ng;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      if ((d__1 = g1[i__], fabs(d__1)) > zero)
        {
          goto L110;
        }

      zroot = true;
      goto L120;
      /* At this point, G0(i) has been checked and cannot be zero. ------------ */
L110:

      if (d_sign(c_b3, g0[i__]) == d_sign(c_b3, g1[i__]))
        {
          goto L120;
        }

      t2 = (d__1 = g1[i__] / (g1[i__] - g0[i__]), fabs(d__1));

      if (t2 <= tmax)
        {
          goto L120;
        }

      tmax = t2;
      dlsr01_2.imax = i__;
L120:
      ;
    }

  if (dlsr01_2.imax > 0)
    {
      goto L130;
    }

  sgnchg = false;
  goto L140;
L130:
  sgnchg = true;
L140:

  if (! sgnchg)
    {
      goto L400;
    }

  /* There is a sign change.  Find the first root in the interval. -------- */
  xroot = false;
  nxlast = 0;
  dlsr01_2.last = 1;

  /* Repeat until the first root in the interval is found.  Loop point. --- */
L150:

  if (xroot)
    {
      goto L300;
    }

  if (nxlast == dlsr01_2.last)
    {
      goto L160;
    }

  dlsr01_2.alpha = 1.;
  goto L180;
L160:

  if (dlsr01_2.last == 0)
    {
      goto L170;
    }

  dlsr01_2.alpha *= .5;
  goto L180;
L170:
  dlsr01_2.alpha *= 2.;
L180:
  dlsr01_2.x2 = *x1 - (*x1 - *x0) * g1[dlsr01_2.imax] / (g1[dlsr01_2.imax]
                - dlsr01_2.alpha * g0[dlsr01_2.imax]);

  /* If X2 is too close to X0 or X1, adjust it inward, by a fractional ---- */

  /* distance that is between 0.1 and 0.5. -------------------------------- */
  if ((d__1 = dlsr01_2.x2 - *x0, fabs(d__1)) < half * *hmin)
    {
      fracint = (d__1 = *x1 - *x0, fabs(d__1)) / *hmin;
      fracsub = tenth;

      if (fracint <= five)
        {
          fracsub = half / fracint;
        }

      dlsr01_2.x2 = *x0 + fracsub * (*x1 - *x0);
    }

  if ((d__1 = *x1 - dlsr01_2.x2, fabs(d__1)) < half * *hmin)
    {
      fracint = (d__1 = *x1 - *x0, fabs(d__1)) / *hmin;
      fracsub = tenth;

      if (fracint <= five)
        {
          fracsub = half / fracint;
        }

      dlsr01_2.x2 = *x1 - fracsub * (*x1 - *x0);
    }

  *jflag = 1;
  *x = dlsr01_2.x2;
  /* Return to the calling routine to get a value of GX = g(X). ----------- */
  return 0;
  /* Check to see in which interval g changes sign. ----------------------- */
L200:
  imxold = dlsr01_2.imax;
  dlsr01_2.imax = 0;
  tmax = zero;
  zroot = false;
  i__1 = *ng;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      if ((d__1 = gx[i__], fabs(d__1)) > zero)
        {
          goto L210;
        }

      zroot = true;
      goto L220;
      /* Neither G0(i) nor GX(i) can be zero at this point. ------------------- */
L210:

      if (d_sign(c_b3, g0[i__]) == d_sign(c_b3, gx[i__]))
        {
          goto L220;
        }

      t2 = (d__1 = gx[i__] / (gx[i__] - g0[i__]), fabs(d__1));

      if (t2 <= tmax)
        {
          goto L220;
        }

      tmax = t2;
      dlsr01_2.imax = i__;
L220:
      ;
    }

  if (dlsr01_2.imax > 0)
    {
      goto L230;
    }

  sgnchg = false;
  dlsr01_2.imax = imxold;
  goto L240;
L230:
  sgnchg = true;
L240:
  nxlast = dlsr01_2.last;

  if (! sgnchg)
    {
      goto L250;
    }

  /* Sign change between X0 and X2, so replace X1 with X2. ---------------- */
  *x1 = dlsr01_2.x2;
  dcopy_(ng, &gx[1], &c__1, &g1[1], &c__1);
  dlsr01_2.last = 1;
  xroot = false;
  goto L270;
L250:

  if (! zroot)
    {
      goto L260;
    }

  /* Zero value at X2 and no sign change in (X0,X2), so X2 is a root. ----- */
  *x1 = dlsr01_2.x2;
  dcopy_(ng, &gx[1], &c__1, &g1[1], &c__1);
  xroot = true;
  goto L270;
  /* No sign change between X0 and X2.  Replace X0 with X2. --------------- */
L260:
  dcopy_(ng, &gx[1], &c__1, &g0[1], &c__1);
  *x0 = dlsr01_2.x2;
  dlsr01_2.last = 0;
  xroot = false;
L270:

  if ((d__1 = *x1 - *x0, fabs(d__1)) <= *hmin)
    {
      xroot = true;
    }

  goto L150;

  /* Return with X1 as the root.  Set JROOT.  Set X = X1 and GX = G1. ----- */
L300:
  *jflag = 2;
  *x = *x1;
  dcopy_(ng, &g1[1], &c__1, &gx[1], &c__1);
  i__1 = *ng;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      jroot[i__] = 0;

      if ((d__1 = g1[i__], fabs(d__1)) > zero)
        {
          goto L310;
        }

      jroot[i__] = 1;
      goto L320;
L310:

      if (d_sign(c_b3, g0[i__]) != d_sign(c_b3, g1[i__]))
        {
          jroot[i__] = 1;
        }

L320:
      ;
    }

  return 0;

  /* No sign change in the interval.  Check for zero at right endpoint. --- */
L400:

  if (! zroot)
    {
      goto L420;
    }

  /* Zero value at X1 and no sign change in (X0,X1).  Return JFLAG = 3. --- */
  *x = *x1;
  dcopy_(ng, &g1[1], &c__1, &gx[1], &c__1);
  i__1 = *ng;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      jroot[i__] = 0;

      if ((d__1 = g1[i__], fabs(d__1)) <= zero)
        {
          jroot[i__] = 1;
        }

      /* L410: */
    }

  *jflag = 3;
  return 0;

  /* No sign changes in this interval.  Set X = X1, return JFLAG = 4. ----- */
L420:
  dcopy_(ng, &g1[1], &c__1, &gx[1], &c__1);
  *x = *x1;
  *jflag = 4;
  return 0;
  /* ----------------------- End of Subroutine DROOTS ---------------------- */
} /* droots_ */
