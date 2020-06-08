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

#include "copasi/copasi.h"

#include "dcfode.h"

/* DECK DCFODE */
/* Subroutine */
C_INT dcfode_(C_INT *meth, double *elco, double * tesco)
{
  /* System generated locals */
  C_INT i__1;

  /* Local variables */
  C_INT i__, ib;
  double pc[12];
  C_INT nq;
  double fnq;
  C_INT nqm1, nqp1;
  double ragq, pint, xpin, fnqm1, agamq, rqfac, tsign, rq1fac;

  /* ***BEGIN PROLOGUE  DCFODE */
  /* ***SUBSIDIARY */
  /* ***PURPOSE  Set ODE integrator coefficients. */
  /* ***TYPE      DOUBLE PRECISION (SCFODE-S, DCFODE-D) */
  /* ***AUTHOR  Hindmarsh, Alan C., (LLNL) */
  /* ***DESCRIPTION */

  /*  DCFODE is called by the integrator routine to set coefficients */
  /*  needed there.  The coefficients for the current method, as */
  /*  given by the value of METH, are set for all orders and saved. */
  /*  The maximum order assumed here is 12 if METH = 1 and 5 if METH = 2. */
  /*  (A smaller value of the maximum order is also allowed.) */
  /*  DCFODE is called once at the beginning of the problem, */
  /*  and is not called again unless and until METH is changed. */

  /*  The ELCO array contains the basic method coefficients. */
  /*  The coefficients el(i), 1 .le. i .le. nq+1, for the method of */
  /*  order nq are stored in ELCO(i,nq).  They are given by a genetrating */
  /*  polynomial, i.e., */
  /*      l(x) = el(1) + el(2)*x + ... + el(nq+1)*x**nq. */
  /*  For the implicit Adams methods, l(x) is given by */
  /*      dl/dx = (x+1)*(x+2)*...*(x+nq-1)/factorial(nq-1),    l(-1) = 0. */
  /*  For the BDF methods, l(x) is given by */
  /*      l(x) = (x+1)*(x+2)* ... *(x+nq)/K, */
  /*  where         K = factorial(nq)*(1 + 1/2 + ... + 1/nq). */

  /*  The TESCO array contains test constants used for the */
  /*  local error test and the selection of step size and/or order. */
  /*  At order nq, TESCO(k,nq) is used for the selection of step */
  /*  size at order nq - 1 if k = 1, at order nq if k = 2, and at order */
  /*  nq + 1 if k = 3. */

  /* ***SEE ALSO  DLSODE */
  /* ***ROUTINES CALLED  (NONE) */
  /* ***REVISION HISTORY  (YYMMDD) */
  /*   791129  DATE WRITTEN */
  /*   890501  Modified prologue to SLATEC/LDOC format.  (FNF) */
  /*   890503  Minor cosmetic changes.  (FNF) */
  /*   930809  Renamed to allow single/double precision versions. (ACH) */
  /* ***END PROLOGUE  DCFODE */
  /* **End */

  /* ***FIRST EXECUTABLE STATEMENT  DCFODE */
  /* Parameter adjustments */
  tesco -= 4;
  elco -= 14;

  /* Function Body */
  switch (*meth)
    {
      case 1: goto L100;

      case 2: goto L200;
    }

L100:
  elco[14] = 1.;
  elco[15] = 1.;
  tesco[4] = 0.;
  tesco[5] = 2.;
  tesco[7] = 1.;
  tesco[39] = 0.;
  pc[0] = 1.;
  rqfac = 1.;

  for (nq = 2; nq <= 12; ++nq)
    {
      /* ----------------------------------------------------------------------- */
      /* The PC array will contain the coefficients of the polynomial */
      /*     p(x) = (x+1)*(x+2)*...*(x+nq-1). */
      /* Initially, p(x) = 1. */
      /* ----------------------------------------------------------------------- */
      rq1fac = rqfac;
      rqfac /= nq;
      nqm1 = nq - 1;
      fnqm1 = (double) nqm1;
      nqp1 = nq + 1;
      /* Form coefficients of p(x)*(x+nq-1). ---------------------------------- */
      pc[nq - 1] = 0.;
      i__1 = nqm1;

      for (ib = 1; ib <= i__1; ++ib)
        {
          i__ = nqp1 - ib;
          /* L110: */
          pc[i__ - 1] = pc[i__ - 2] + fnqm1 * pc[i__ - 1];
        }

      pc[0] = fnqm1 * pc[0];
      /* Compute integral, -1 to 0, of p(x) and x*p(x). ----------------------- */
      pint = pc[0];
      xpin = pc[0] / 2.;
      tsign = 1.;
      i__1 = nq;

      for (i__ = 2; i__ <= i__1; ++i__)
        {
          tsign = -tsign;
          pint += tsign * pc[i__ - 1] / i__;
          /* L120: */
          xpin += tsign * pc[i__ - 1] / (i__ + 1);
        }

      /* Store coefficients in ELCO and TESCO. -------------------------------- */
      elco[nq * 13 + 1] = pint * rq1fac;
      elco[nq * 13 + 2] = 1.;
      i__1 = nq;

      for (i__ = 2; i__ <= i__1; ++i__)
        {
          /* L130: */
          elco[i__ + 1 + nq * 13] = rq1fac * pc[i__ - 1] / i__;
        }

      agamq = rqfac * xpin;
      ragq = 1. / agamq;
      tesco[nq * 3 + 2] = ragq;

      if (nq < 12)
        {
          tesco[nqp1 * 3 + 1] = ragq * rqfac / nqp1;
        }

      tesco[nqm1 * 3 + 3] = ragq;
      /* L140: */
    }

  return 0;

L200:
  pc[0] = 1.;
  rq1fac = 1.;

  for (nq = 1; nq <= 5; ++nq)
    {
      /* ----------------------------------------------------------------------- */
      /* The PC array will contain the coefficients of the polynomial */
      /*     p(x) = (x+1)*(x+2)*...*(x+nq). */
      /* Initially, p(x) = 1. */
      /* ----------------------------------------------------------------------- */
      fnq = (double) nq;
      nqp1 = nq + 1;
      /* Form coefficients of p(x)*(x+nq). ------------------------------------ */
      pc[nqp1 - 1] = 0.;
      i__1 = nq;

      for (ib = 1; ib <= i__1; ++ib)
        {
          i__ = nq + 2 - ib;
          /* L210: */
          pc[i__ - 1] = pc[i__ - 2] + fnq * pc[i__ - 1];
        }

      pc[0] = fnq * pc[0];
      /* Store coefficients in ELCO and TESCO. -------------------------------- */
      i__1 = nqp1;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          /* L220: */
          elco[i__ + nq * 13] = pc[i__ - 1] / pc[1];
        }

      elco[nq * 13 + 2] = 1.;
      tesco[nq * 3 + 1] = rq1fac;
      tesco[nq * 3 + 2] = nqp1 / elco[nq * 13 + 1];
      tesco[nq * 3 + 3] = (nq + 2) / elco[nq * 13 + 1];
      rq1fac /= fnq;
      /* L230: */
    }

  return 0;
  /* ----------------------- END OF SUBROUTINE DCFODE ---------------------- */
} /* dcfode_ */
