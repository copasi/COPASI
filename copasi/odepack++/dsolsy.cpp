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

static C_INT c__0 = 0;

#include "dgbsl.h"
#include "dgesl.h"

#include "copasi/lapack/lapackwrap.h"

/* DECK DSOLSY */
/* Subroutine */
C_INT CInternalSolver::dsolsy_(double *wm, C_INT *iwm, double *x,
                               double *tem)
{
  /* System generated locals */
  C_INT i__1;

  /* Local variables */
  C_INT i__;
  double r__, di;
  C_INT ml, mu;
  double hl0, phl0;
  C_INT meband;

  /* ***BEGIN PROLOGUE  DSOLSY */
  /* ***SUBSIDIARY */
  /* ***PURPOSE  ODEPACK linear system solver. */
  /* ***TYPE      DOUBLE PRECISION (SSOLSY-S, DSOLSY-D) */
  /* ***AUTHOR  Hindmarsh, Alan C., (LLNL) */
  /* ***DESCRIPTION */

  /*  This routine manages the solution of the linear system arising from */
  /*  a chord iteration.  It is called if MITER .ne. 0. */
  /*  If MITER is 1 or 2, it calls DGESL to accomplish this. */
  /*  If MITER = 3 it updates the coefficient h*EL0 in the diagonal */
  /*  matrix, and then computes the solution. */
  /*  If MITER is 4 or 5, it calls DGBSL. */
  /*  Communication with DSOLSY uses the following variables: */
  /*  WM    = real work space containing the inverse diagonal matrix if */
  /*          MITER = 3 and the LU decomposition of the matrix otherwise. */
  /*          Storage of matrix elements starts at WM(3). */
  /*          WM also contains the following matrix-related data: */
  /*          WM(1) = SQRT(UROUND) (not used here), */
  /*          WM(2) = HL0, the previous value of h*EL0, used if MITER = 3. */
  /*  IWM   = integer work space containing pivot information, starting at */
  /*          IWM(21), if MITER is 1, 2, 4, or 5.  IWM also contains band */
  /*          parameters ML = IWM(1) and MU = IWM(2) if MITER is 4 or 5. */
  /*  X     = the right-hand side vector on input, and the solution vector */
  /*          on output, of length N. */
  /*  TEM   = vector of work space of length N, not used in this version. */
  /*  IERSL = output flag (in COMMON).  IERSL = 0 if no trouble occurred. */
  /*          IERSL = 1 if a singular matrix arose with MITER = 3. */
  /*  This routine also uses the COMMON variables EL0, H, MITER, and N. */

  /* ***SEE ALSO  DLSODE */
  /* ***ROUTINES CALLED  DGBSL, DGESL */
  /* ***COMMON BLOCKS    DLS001 */
  /* ***REVISION HISTORY  (YYMMDD) */
  /*   791129  DATE WRITTEN */
  /*   890501  Modified prologue to SLATEC/LDOC format.  (FNF) */
  /*   890503  Minor cosmetic changes.  (FNF) */
  /*   930809  Renamed to allow single/double precision versions. (ACH) */
  /*   010418  Reduced size of Common block /DLS001/. (ACH) */
  /*   031105  Restored 'own' variables to Common block /DLS001/, to */
  /*           enable interrupt/restart feature. (ACH) */
  /* ***END PROLOGUE  DSOLSY */
  /* **End */

  /* ***FIRST EXECUTABLE STATEMENT  DSOLSY */
  /* Parameter adjustments */
  --tem;
  --x;
  --iwm;
  --wm;

  /* Function Body */
  dls001_1.iersl = 0;

  switch (dls001_1.miter)
    {
      case 1: goto L100;

      case 2: goto L100;

      case 3: goto L300;

      case 4: goto L400;

      case 5: goto L400;
    }

L100:
  dgesl_(&wm[3], &dls001_1.n, &dls001_1.n, &iwm[21], &x[1], &c__0);
  return 0;

L300:
  phl0 = wm[2];
  hl0 = dls001_1.h__ * dls001_1.el0;
  wm[2] = hl0;

  if (hl0 == phl0)
    {
      goto L330;
    }

  r__ = hl0 / phl0;
  i__1 = dls001_1.n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      di = 1. - r__ * (1. - 1. / wm[i__ + 2]);

      if (fabs(di) == 0.)
        {
          goto L390;
        }

      /* L320: */
      wm[i__ + 2] = 1. / di;
    }

L330:
  i__1 = dls001_1.n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* L340: */
      x[i__] = wm[i__ + 2] * x[i__];
    }

  return 0;
L390:
  dls001_1.iersl = 1;
  return 0;

L400:
  ml = iwm[1];
  mu = iwm[2];
  meband = (ml << 1) + mu + 1;
  dgbsl_(&wm[3], &meband, &dls001_1.n, &ml, &mu, &iwm[21], &x[1], &c__0);
  return 0;
  /* ----------------------- END OF SUBROUTINE DSOLSY ---------------------- */
} /* dsolsy_ */
