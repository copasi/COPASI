// Copyright (C) 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

//
// This C++ code is based on an f2c conversion of the Fortran
// library ODEPACK available at: http://www.netlib.org/odepack/

#include <cmath>
#include <algorithm>

#include "copasi/odepack++/CRootCheck.h"
#include "copasi/lapack/blaswrap.h"
#include "copasi/lapack/lapackwrap.h"
#include "copasi/math/CMathEnum.h"

double d_sign(const double & a, const double & b);

static double c_b3 = 1.0;

static const C_INT c__0 = 0;
static C_INT c__1 = 1;

CRootCheck::CRootCheck(CInternalSolver & solver)
  : CInternalSolver(solver)
  , mRootFinder()
{}

CRootCheck::~CRootCheck()
{}

void CRootCheck::initialize(const C_FLOAT64 & relativeTolerance, const CVectorCore< const RootMask > & rootMask)
{
  mRootFinder.initialize(relativeTolerance, rootMask, std::bind(&CRootCheck::calculateRootValues, this, std::placeholders::_1, std::placeholders::_2));
}

C_INT CRootCheck::operator()(const C_INT *job, evalG g, C_INT *neq, double *
                                y, C_INT *nyh, double *rwork, C_INT *jroot, C_INT *irt)
{
  return check(job, g, neq, y, &rwork[dls001_lsoda.lyh], nyh, &rwork[dlsr01_lsodar.lg0], &rwork[dlsr01_lsodar.lg1],
                               &rwork[dlsr01_lsodar.lgx], jroot, irt);
}

/* DECK DRCHEK */
/* Subroutine */
C_INT CRootCheck::check(const C_INT * job,
                        evalG g,
                        C_INT *neq,
                        double * y,
                        double *yh,
                        C_INT *nyh,
                        double *g0,
                        double *g1,
                        double *gx,
                        C_INT *jroot,
                        C_INT *irt)
{
  // drchek_(job, g, neq, y, &rwork[dls001_lsoda.lyh], nyh, &rwork[dlsr01_lsodar.lg0], &rwork[dlsr01_lsodar.lg0],
  //         &rwork[dlsr01_lsodar.lg0], jroot, irt);

  // Convenience variables for interfacing CRootFinder
  CVectorCore< C_FLOAT64 > LeftRoots(dlsr01_1.ngc, g0);
  CVectorCore< C_FLOAT64 > RightRoots(dlsr01_1.ngc, g1);
  CVectorCore< C_FLOAT64 > CurrentRoots(dlsr01_1.ngc, gx);
  CVectorCore< C_INT > JRoot(dlsr01_1.ngc, jroot);

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

  // &c__0, &yh[yh_offset], nyh, &y[1], &iflag
  mData.g = g;
  mData.neq = &neq[1];
  mData.y = &y[1];
  mData.yh = &yh[yh_offset];
  mData.nyh = nyh;

  /* Function Body */
  *irt = 0;
  JRoot = static_cast< C_INT >(CMath::RootToggleType::NoToggle);

#ifdef XXXX
  i__1 = dlsr01_1.ngc;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L10: */
      jroot[i__] = 0;
    }
#endif // XXXX

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
  dlsr01_1.nge = 0;

  (*g)(&neq[1], &dlsr01_1.t0, &y[1], &dlsr01_1.ngc, &g0[1]);
  ++dlsr01_1.nge;

  if (mRootFinder.checkLeftRoot(dlsr01_1.t0, LeftRoots, RootMask::ALL) == CRootFinder::ReturnStatus::RootFound)
    {
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

      if (mRootFinder.checkLeftRoot(dlsr01_1.t0, LeftRoots, RootMask::ALL) == CRootFinder::ReturnStatus::RootFound)
        {
          *irt = -1;
          JRoot = mRootFinder.getToggledRoots();
        }
      }

  return 0;

#ifdef XXXX
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
#endif // XXXX

L200:
  if (dlsr01_1.irfnd == 0)
    {
      goto L260;
    }

  /* If a root was found on the previous step, evaluate G0 = g(T0). ------- */
  dintdy_(&dlsr01_1.t0, &c__0, &yh[yh_offset], nyh, &y[1], &iflag);
  (*g)(&neq[1], &dlsr01_1.t0, &y[1], &dlsr01_1.ngc, &g0[1]);
  ++dlsr01_1.nge;

  if (mRootFinder.checkLeftRoot(dlsr01_1.t0, LeftRoots, RootMask::ALL) == CRootFinder::ReturnStatus::RootFound)
    {
      /* g has a zero at T0.  Look at g at T + (small increment). ------------- */
      temp1 = d_sign(hming, dls001_1.h__);
      dlsr01_1.t0 += temp1;

      if ((dlsr01_1.t0 - dls001_1.tn) * dls001_1.h__ < 0.)
        {
          // goto L230;
          dintdy_(&dlsr01_1.t0, &c__0, &yh[yh_offset], nyh, &y[1], &iflag);
        }
      else
        {
          temp2 = temp1 / dls001_1.h__;
          i__1 = dls001_1.n;

          for (i__ = 1; i__ <= i__1; ++i__)
            {
              /* L220: */
              y[i__] += temp2 * yh[i__ + (yh_dim1 << 1)];
            }
        }

      (*g)(&neq[1], &dlsr01_1.t0, &y[1], &dlsr01_1.ngc, &g0[1]);
      ++dlsr01_1.nge;

      if (mRootFinder.checkLeftRoot(dlsr01_1.t0, LeftRoots, RootMask::ALL) == CRootFinder::ReturnStatus::RootFound)
        {
          /* g has a zero at T0 and also close to T0.  Return root. --------------- */
          JRoot = mRootFinder.getToggledRoots();
          *irt = 1;
          return 0;
        }
      }

#ifdef XXXX
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
#endif // XXXX

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
  // (*g)(&neq[1], &t1, &y[1], &dlsr01_1.ngc, &g1[1]);
  // ++dlsr01_1.nge;

  switch (mRootFinder.checkRoots(t1, RootMask::ALL))
    {
    case CRootFinder::ReturnStatus::RootFound:
      dlsr01_1.t0 = mRootFinder.getRootTime();
      JRoot = mRootFinder.getToggledRoots();
      CurrentRoots = mRootFinder.getRootValues();
      LeftRoots = CurrentRoots;

      /* Found a root.  Interpolate to X and return. -------------------------- */
      dintdy_(&dlsr01_1.t0, &c__0, &yh[yh_offset], nyh, &y[1], &iflag);
      *irt = 1;

      break;

    case CRootFinder::ReturnStatus::NotFound:
      dlsr01_1.t0 = t1;
      LeftRoots = RightRoots;
      JRoot = mRootFinder.getToggledRoots();

      /* No root found.  Interpolate to t1 and return. -------------------------- */
      dintdy_(&dlsr01_1.t0, &c__0, &yh[yh_offset], nyh, &y[1], &iflag);

      break;

    case CRootFinder::ReturnStatus::NotAdvanced:
      JRoot = mRootFinder.getToggledRoots();

      /* Not advanced. Reset to t0 */
      dintdy_(&dlsr01_1.t0, &c__0, &yh[yh_offset], nyh, &y[1], &iflag);
      *irt = -1;

      break;

    case CRootFinder::ReturnStatus::InvalidInterval:
      fatalError();
      break;
  }

#ifdef XXXX
  /* Call DROOTS to search for root in interval from T0 to T1. ------------ */
  jflag = 0;

L350:
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

#endif // XXXX

L390:
  return 0;
  /* ----------------------- End of Subroutine DRCHEK ---------------------- */
} /* drchek_ */

void CRootCheck::calculateRootValues(const double & time,
                                     CVectorCore< C_FLOAT64 > & rootValues)
{
  C_INT iflag = 0;

  dintdy_(const_cast< double * >(&time), &c__0, mData.yh, mData.nyh, mData.y, &iflag);

  if (iflag == 0)
    {
      (*mData.g)(mData.neq, const_cast< double * >(&time), mData.y, &dlsr01_1.ngc, rootValues.array());
      ++dlsr01_1.nge;
    }
}
