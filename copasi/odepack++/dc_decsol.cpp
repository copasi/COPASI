// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

/* dc_decsol.f -- translated by f2c (version 20160102).
   You must link the resulting object file with libf2c:
  on Microsoft Windows system, link with libf2c.lib;
  on Linux or Unix systems, link with .../path/to/libf2c.a -lm
  or, if you install libf2c.a in a standard place, with -lf2c -lm
  -- in that order, at the end of the command line, as in
    cc *.o -lf2c -lm
  Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

    http://www.netlib.org/f2c/libf2c.zip
 */

#include "dc_decsol.h"

/* Common Block Declarations */

static struct
{
  integer mle, mue, mbjac, mbb, mdiag, mdiff, mbdiag;
} linal_;

#define linal_1 linal_

/* Table of constant values */

static integer c__1 = 1;

/* ****************************************** */
/*     VERSION OF SEPTEMBER 18, 1995 */
/* ****************************************** */

/* Subroutine */ int decomr_(integer *n, doublereal *fjac, integer *ldjac,
                             doublereal *fmas, integer *ldmas, integer *mlmas, integer *mumas,
                             integer *m1, integer *m2, integer *nm1, doublereal *fac1, doublereal *
                             e1, integer *lde1, integer *ip1, integer *ier, integer *ijob, logical
                             *calhes, integer *iphes)
{
  /* System generated locals */
  integer fjac_dim1, fjac_offset, fmas_dim1, fmas_offset, e1_dim1,
          e1_offset, i__1, i__2, i__3, i__4, i__5, i__6;

  /* Local variables */
  static integer i__, j, k, j1, ib, mm, jm1;
  extern /* Subroutine */ int dec_(integer *, integer *, doublereal *,
                                   integer *, integer *);
  static doublereal sum;
  extern /* Subroutine */ int decb_(integer *, integer *, doublereal *,
                                    integer *, integer *, integer *, integer *), dech_(integer *,
                                        integer *, doublereal *, integer *, integer *, integer *),
                                                elmhes_(integer *, integer *, integer *, integer *, doublereal *,
                                                    integer *);

  /* Parameter adjustments */
  --iphes;
  fjac_dim1 = *ldjac;
  fjac_offset = 1 + fjac_dim1;
  fjac -= fjac_offset;
  --ip1;
  fmas_dim1 = *ldmas;
  fmas_offset = 1 + fmas_dim1;
  fmas -= fmas_offset;
  e1_dim1 = *lde1;
  e1_offset = 1 + e1_dim1;
  e1 -= e1_offset;

  /* Function Body */
  switch (*ijob)
    {
      case 1:  goto L1;

      case 2:  goto L2;

      case 3:  goto L3;

      case 4:  goto L4;

      case 5:  goto L5;

      case 6:  goto L6;

      case 7:  goto L7;

      case 8:  goto L55;

      case 9:  goto L55;

      case 10:  goto L55;

      case 11:  goto L11;

      case 12:  goto L12;

      case 13:  goto L13;

      case 14:  goto L14;

      case 15:  goto L15;
    }

  /* ----------------------------------------------------------- */

L1:
  /* ---  B=IDENTITY, JACOBIAN A FULL MATRIX */
  i__1 = *n;

  for (j = 1; j <= i__1; ++j)
    {
      i__2 = *n;

      for (i__ = 1; i__ <= i__2; ++i__)
        {
          e1[i__ + j * e1_dim1] = -fjac[i__ + j * fjac_dim1];
        }

      e1[j + j * e1_dim1] += *fac1;
    }

  dec_(n, lde1, &e1[e1_offset], &ip1[1], ier);
  return 0;

  /* ----------------------------------------------------------- */

L11:
  /* ---  B=IDENTITY, JACOBIAN A FULL MATRIX, SECOND ORDER */
  i__1 = *nm1;

  for (j = 1; j <= i__1; ++j)
    {
      jm1 = j + *m1;
      i__2 = *nm1;

      for (i__ = 1; i__ <= i__2; ++i__)
        {
          e1[i__ + j * e1_dim1] = -fjac[i__ + jm1 * fjac_dim1];
        }

      e1[j + j * e1_dim1] += *fac1;
    }

L45:
  mm = *m1 / *m2;
  i__1 = *m2;

  for (j = 1; j <= i__1; ++j)
    {
      i__2 = *nm1;

      for (i__ = 1; i__ <= i__2; ++i__)
        {
          sum = 0.;
          i__3 = mm - 1;

          for (k = 0; k <= i__3; ++k)
            {
              sum = (sum + fjac[i__ + (j + k * *m2) * fjac_dim1]) / *fac1;
            }

          e1[i__ + j * e1_dim1] -= sum;
        }
    }

  dec_(nm1, lde1, &e1[e1_offset], &ip1[1], ier);
  return 0;

  /* ----------------------------------------------------------- */

L2:
  /* ---  B=IDENTITY, JACOBIAN A BANDED MATRIX */
  i__1 = *n;

  for (j = 1; j <= i__1; ++j)
    {
      i__2 = linal_1.mbjac;

      for (i__ = 1; i__ <= i__2; ++i__)
        {
          e1[i__ + linal_1.mle + j * e1_dim1] = -fjac[i__ + j * fjac_dim1];
        }

      e1[linal_1.mdiag + j * e1_dim1] += *fac1;
    }

  decb_(n, lde1, &e1[e1_offset], &linal_1.mle, &linal_1.mue, &ip1[1], ier);
  return 0;

  /* ----------------------------------------------------------- */

L12:
  /* ---  B=IDENTITY, JACOBIAN A BANDED MATRIX, SECOND ORDER */
  i__1 = *nm1;

  for (j = 1; j <= i__1; ++j)
    {
      jm1 = j + *m1;
      i__2 = linal_1.mbjac;

      for (i__ = 1; i__ <= i__2; ++i__)
        {
          e1[i__ + linal_1.mle + j * e1_dim1] = -fjac[i__ + jm1 * fjac_dim1]
                                                ;
        }

      e1[linal_1.mdiag + j * e1_dim1] += *fac1;
    }

L46:
  mm = *m1 / *m2;
  i__1 = *m2;

  for (j = 1; j <= i__1; ++j)
    {
      i__2 = linal_1.mbjac;

      for (i__ = 1; i__ <= i__2; ++i__)
        {
          sum = 0.;
          i__3 = mm - 1;

          for (k = 0; k <= i__3; ++k)
            {
              sum = (sum + fjac[i__ + (j + k * *m2) * fjac_dim1]) / *fac1;
            }

          e1[i__ + linal_1.mle + j * e1_dim1] -= sum;
        }
    }

  decb_(nm1, lde1, &e1[e1_offset], &linal_1.mle, &linal_1.mue, &ip1[1], ier)
  ;
  return 0;

  /* ----------------------------------------------------------- */

L3:
  /* ---  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX */
  i__1 = *n;

  for (j = 1; j <= i__1; ++j)
    {
      i__2 = *n;

      for (i__ = 1; i__ <= i__2; ++i__)
        {
          e1[i__ + j * e1_dim1] = -fjac[i__ + j * fjac_dim1];
        }

      /* Computing MAX */
      i__2 = 1, i__3 = j - *mumas;
      /* Computing MIN */
      i__5 = *n, i__6 = j + *mlmas;
      i__4 = min(i__5, i__6);

      for (i__ = max(i__2, i__3); i__ <= i__4; ++i__)
        {
          e1[i__ + j * e1_dim1] += *fac1 * fmas[i__ - j + linal_1.mbdiag +
                                                j * fmas_dim1];
        }
    }

  dec_(n, lde1, &e1[e1_offset], &ip1[1], ier);
  return 0;

  /* ----------------------------------------------------------- */

L13:
  /* ---  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER */
  i__1 = *nm1;

  for (j = 1; j <= i__1; ++j)
    {
      jm1 = j + *m1;
      i__4 = *nm1;

      for (i__ = 1; i__ <= i__4; ++i__)
        {
          e1[i__ + j * e1_dim1] = -fjac[i__ + jm1 * fjac_dim1];
        }

      /* Computing MAX */
      i__4 = 1, i__2 = j - *mumas;
      /* Computing MIN */
      i__5 = *nm1, i__6 = j + *mlmas;
      i__3 = min(i__5, i__6);

      for (i__ = max(i__4, i__2); i__ <= i__3; ++i__)
        {
          e1[i__ + j * e1_dim1] += *fac1 * fmas[i__ - j + linal_1.mbdiag +
                                                j * fmas_dim1];
        }
    }

  goto L45;

  /* ----------------------------------------------------------- */

L4:
  /* ---  B IS A BANDED MATRIX, JACOBIAN A BANDED MATRIX */
  i__1 = *n;

  for (j = 1; j <= i__1; ++j)
    {
      i__3 = linal_1.mbjac;

      for (i__ = 1; i__ <= i__3; ++i__)
        {
          e1[i__ + linal_1.mle + j * e1_dim1] = -fjac[i__ + j * fjac_dim1];
        }

      i__3 = linal_1.mbb;

      for (i__ = 1; i__ <= i__3; ++i__)
        {
          ib = i__ + linal_1.mdiff;
          e1[ib + j * e1_dim1] += *fac1 * fmas[i__ + j * fmas_dim1];
        }
    }

  decb_(n, lde1, &e1[e1_offset], &linal_1.mle, &linal_1.mue, &ip1[1], ier);
  return 0;

  /* ----------------------------------------------------------- */

L14:
  /* ---  B IS A BANDED MATRIX, JACOBIAN A BANDED MATRIX, SECOND ORDER */
  i__1 = *nm1;

  for (j = 1; j <= i__1; ++j)
    {
      jm1 = j + *m1;
      i__3 = linal_1.mbjac;

      for (i__ = 1; i__ <= i__3; ++i__)
        {
          e1[i__ + linal_1.mle + j * e1_dim1] = -fjac[i__ + jm1 * fjac_dim1]
                                                ;
        }

      i__3 = linal_1.mbb;

      for (i__ = 1; i__ <= i__3; ++i__)
        {
          ib = i__ + linal_1.mdiff;
          e1[ib + j * e1_dim1] += *fac1 * fmas[i__ + j * fmas_dim1];
        }
    }

  goto L46;

  /* ----------------------------------------------------------- */

L5:
  /* ---  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX */
  i__1 = *n;

  for (j = 1; j <= i__1; ++j)
    {
      i__3 = *n;

      for (i__ = 1; i__ <= i__3; ++i__)
        {
          e1[i__ + j * e1_dim1] = fmas[i__ + j * fmas_dim1] * *fac1 - fjac[
                                    i__ + j * fjac_dim1];
        }
    }

  dec_(n, lde1, &e1[e1_offset], &ip1[1], ier);
  return 0;

  /* ----------------------------------------------------------- */

L15:
  /* ---  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER */
  i__1 = *nm1;

  for (j = 1; j <= i__1; ++j)
    {
      jm1 = j + *m1;
      i__3 = *nm1;

      for (i__ = 1; i__ <= i__3; ++i__)
        {
          e1[i__ + j * e1_dim1] = fmas[i__ + j * fmas_dim1] * *fac1 - fjac[
                                    i__ + jm1 * fjac_dim1];
        }
    }

  goto L45;

  /* ----------------------------------------------------------- */

L6:
  /* ---  B IS A FULL MATRIX, JACOBIAN A BANDED MATRIX */
  /* ---  THIS OPTION IS NOT PROVIDED */
  return 0;

  /* ----------------------------------------------------------- */

L7:

  /* ---  B=IDENTITY, JACOBIAN A FULL MATRIX, HESSENBERG-OPTION */
  if (*calhes)
    {
      elmhes_(ldjac, n, &c__1, n, &fjac[fjac_offset], &iphes[1]);
    }

  *calhes = FALSE_;
  i__1 = *n - 1;

  for (j = 1; j <= i__1; ++j)
    {
      j1 = j + 1;
      e1[j1 + j * e1_dim1] = -fjac[j1 + j * fjac_dim1];
    }

  i__1 = *n;

  for (j = 1; j <= i__1; ++j)
    {
      i__3 = j;

      for (i__ = 1; i__ <= i__3; ++i__)
        {
          e1[i__ + j * e1_dim1] = -fjac[i__ + j * fjac_dim1];
        }

      e1[j + j * e1_dim1] += *fac1;
    }

  dech_(n, lde1, &e1[e1_offset], &c__1, &ip1[1], ier);
  return 0;

  /* ----------------------------------------------------------- */

L55:
  return 0;
} /* decomr_ */

/*     END OF SUBROUTINE DECOMR */

/* *********************************************************** */

/* Subroutine */ int decomc_(integer *n, doublereal *fjac, integer *ldjac,
                             doublereal *fmas, integer *ldmas, integer *mlmas, integer *mumas,
                             integer *m1, integer *m2, integer *nm1, doublereal *alphn, doublereal
                             *betan, doublereal *e2r, doublereal *e2i, integer *lde1, integer *ip2,
                             integer *ier, integer *ijob)
{
  /* System generated locals */
  integer fjac_dim1, fjac_offset, fmas_dim1, fmas_offset, e2r_dim1,
          e2r_offset, e2i_dim1, e2i_offset, i__1, i__2, i__3, i__4, i__5,
          i__6;
  doublereal d__1, d__2;

  /* Local variables */
  static integer i__, j, k, j1;
  static doublereal bb;
  static integer ib, mm, jm1;
  static doublereal bet, alp;
  extern /* Subroutine */ int decc_(integer *, integer *, doublereal *,
                                    doublereal *, integer *, integer *);
  static doublereal ffma, abno;
  static integer imle;
  static doublereal sumi, sumr, sums;
  extern /* Subroutine */ int decbc_(integer *, integer *, doublereal *,
                                     doublereal *, integer *, integer *, integer *, integer *), dechc_(
                                       integer *, integer *, doublereal *, doublereal *, integer *,
                                       integer *, integer *);

  /* Parameter adjustments */
  fjac_dim1 = *ldjac;
  fjac_offset = 1 + fjac_dim1;
  fjac -= fjac_offset;
  --ip2;
  fmas_dim1 = *ldmas;
  fmas_offset = 1 + fmas_dim1;
  fmas -= fmas_offset;
  e2i_dim1 = *lde1;
  e2i_offset = 1 + e2i_dim1;
  e2i -= e2i_offset;
  e2r_dim1 = *lde1;
  e2r_offset = 1 + e2r_dim1;
  e2r -= e2r_offset;

  /* Function Body */
  switch (*ijob)
    {
      case 1:  goto L1;

      case 2:  goto L2;

      case 3:  goto L3;

      case 4:  goto L4;

      case 5:  goto L5;

      case 6:  goto L6;

      case 7:  goto L7;

      case 8:  goto L55;

      case 9:  goto L55;

      case 10:  goto L55;

      case 11:  goto L11;

      case 12:  goto L12;

      case 13:  goto L13;

      case 14:  goto L14;

      case 15:  goto L15;
    }

  /* ----------------------------------------------------------- */

L1:
  /* ---  B=IDENTITY, JACOBIAN A FULL MATRIX */
  i__1 = *n;

  for (j = 1; j <= i__1; ++j)
    {
      i__2 = *n;

      for (i__ = 1; i__ <= i__2; ++i__)
        {
          e2r[i__ + j * e2r_dim1] = -fjac[i__ + j * fjac_dim1];
          e2i[i__ + j * e2i_dim1] = 0.;
        }

      e2r[j + j * e2r_dim1] += *alphn;
      e2i[j + j * e2i_dim1] = *betan;
    }

  decc_(n, lde1, &e2r[e2r_offset], &e2i[e2i_offset], &ip2[1], ier);
  return 0;

  /* ----------------------------------------------------------- */

L11:
  /* ---  B=IDENTITY, JACOBIAN A FULL MATRIX, SECOND ORDER */
  i__1 = *nm1;

  for (j = 1; j <= i__1; ++j)
    {
      jm1 = j + *m1;
      i__2 = *nm1;

      for (i__ = 1; i__ <= i__2; ++i__)
        {
          e2r[i__ + j * e2r_dim1] = -fjac[i__ + jm1 * fjac_dim1];
          e2i[i__ + j * e2i_dim1] = 0.;
        }

      e2r[j + j * e2r_dim1] += *alphn;
      e2i[j + j * e2i_dim1] = *betan;
    }

L45:
  mm = *m1 / *m2;
  /* Computing 2nd power */
  d__1 = *alphn;
  /* Computing 2nd power */
  d__2 = *betan;
  abno = d__1 * d__1 + d__2 * d__2;
  alp = *alphn / abno;
  bet = *betan / abno;
  i__1 = *m2;

  for (j = 1; j <= i__1; ++j)
    {
      i__2 = *nm1;

      for (i__ = 1; i__ <= i__2; ++i__)
        {
          sumr = 0.;
          sumi = 0.;
          i__3 = mm - 1;

          for (k = 0; k <= i__3; ++k)
            {
              sums = sumr + fjac[i__ + (j + k * *m2) * fjac_dim1];
              sumr = sums * alp + sumi * bet;
              sumi = sumi * alp - sums * bet;
            }

          e2r[i__ + j * e2r_dim1] -= sumr;
          e2i[i__ + j * e2i_dim1] -= sumi;
        }
    }

  decc_(nm1, lde1, &e2r[e2r_offset], &e2i[e2i_offset], &ip2[1], ier);
  return 0;

  /* ----------------------------------------------------------- */

L2:
  /* ---  B=IDENTITY, JACOBIAN A BANDED MATRIX */
  i__1 = *n;

  for (j = 1; j <= i__1; ++j)
    {
      i__2 = linal_1.mbjac;

      for (i__ = 1; i__ <= i__2; ++i__)
        {
          imle = i__ + linal_1.mle;
          e2r[imle + j * e2r_dim1] = -fjac[i__ + j * fjac_dim1];
          e2i[imle + j * e2i_dim1] = 0.;
        }

      e2r[linal_1.mdiag + j * e2r_dim1] += *alphn;
      e2i[linal_1.mdiag + j * e2i_dim1] = *betan;
    }

  decbc_(n, lde1, &e2r[e2r_offset], &e2i[e2i_offset], &linal_1.mle, &
         linal_1.mue, &ip2[1], ier);
  return 0;

  /* ----------------------------------------------------------- */

L12:
  /* ---  B=IDENTITY, JACOBIAN A BANDED MATRIX, SECOND ORDER */
  i__1 = *nm1;

  for (j = 1; j <= i__1; ++j)
    {
      jm1 = j + *m1;
      i__2 = linal_1.mbjac;

      for (i__ = 1; i__ <= i__2; ++i__)
        {
          e2r[i__ + linal_1.mle + j * e2r_dim1] = -fjac[i__ + jm1 *
                                                  fjac_dim1];
          e2i[i__ + linal_1.mle + j * e2i_dim1] = 0.;
        }

      e2r[linal_1.mdiag + j * e2r_dim1] += *alphn;
      e2i[linal_1.mdiag + j * e2i_dim1] += *betan;
    }

L46:
  mm = *m1 / *m2;
  /* Computing 2nd power */
  d__1 = *alphn;
  /* Computing 2nd power */
  d__2 = *betan;
  abno = d__1 * d__1 + d__2 * d__2;
  alp = *alphn / abno;
  bet = *betan / abno;
  i__1 = *m2;

  for (j = 1; j <= i__1; ++j)
    {
      i__2 = linal_1.mbjac;

      for (i__ = 1; i__ <= i__2; ++i__)
        {
          sumr = 0.;
          sumi = 0.;
          i__3 = mm - 1;

          for (k = 0; k <= i__3; ++k)
            {
              sums = sumr + fjac[i__ + (j + k * *m2) * fjac_dim1];
              sumr = sums * alp + sumi * bet;
              sumi = sumi * alp - sums * bet;
            }

          imle = i__ + linal_1.mle;
          e2r[imle + j * e2r_dim1] -= sumr;
          e2i[imle + j * e2i_dim1] -= sumi;
        }
    }

  decbc_(nm1, lde1, &e2r[e2r_offset], &e2i[e2i_offset], &linal_1.mle, &
         linal_1.mue, &ip2[1], ier);
  return 0;

  /* ----------------------------------------------------------- */

L3:
  /* ---  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX */
  i__1 = *n;

  for (j = 1; j <= i__1; ++j)
    {
      i__2 = *n;

      for (i__ = 1; i__ <= i__2; ++i__)
        {
          e2r[i__ + j * e2r_dim1] = -fjac[i__ + j * fjac_dim1];
          e2i[i__ + j * e2i_dim1] = 0.;
        }
    }

  i__1 = *n;

  for (j = 1; j <= i__1; ++j)
    {
      /* Computing MAX */
      i__2 = 1, i__3 = j - *mumas;
      /* Computing MIN */
      i__5 = *n, i__6 = j + *mlmas;
      i__4 = min(i__5, i__6);

      for (i__ = max(i__2, i__3); i__ <= i__4; ++i__)
        {
          bb = fmas[i__ - j + linal_1.mbdiag + j * fmas_dim1];
          e2r[i__ + j * e2r_dim1] += *alphn * bb;
          e2i[i__ + j * e2i_dim1] = *betan * bb;
        }
    }

  decc_(n, lde1, &e2r[e2r_offset], &e2i[e2i_offset], &ip2[1], ier);
  return 0;

  /* ----------------------------------------------------------- */

L13:
  /* ---  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER */
  i__1 = *nm1;

  for (j = 1; j <= i__1; ++j)
    {
      jm1 = j + *m1;
      i__4 = *nm1;

      for (i__ = 1; i__ <= i__4; ++i__)
        {
          e2r[i__ + j * e2r_dim1] = -fjac[i__ + jm1 * fjac_dim1];
          e2i[i__ + j * e2i_dim1] = 0.;
        }

      /* Computing MAX */
      i__4 = 1, i__2 = j - *mumas;
      /* Computing MIN */
      i__5 = *nm1, i__6 = j + *mlmas;
      i__3 = min(i__5, i__6);

      for (i__ = max(i__4, i__2); i__ <= i__3; ++i__)
        {
          ffma = fmas[i__ - j + linal_1.mbdiag + j * fmas_dim1];
          e2r[i__ + j * e2r_dim1] += *alphn * ffma;
          e2i[i__ + j * e2i_dim1] += *betan * ffma;
        }
    }

  goto L45;

  /* ----------------------------------------------------------- */

L4:
  /* ---  B IS A BANDED MATRIX, JACOBIAN A BANDED MATRIX */
  i__1 = *n;

  for (j = 1; j <= i__1; ++j)
    {
      i__3 = linal_1.mbjac;

      for (i__ = 1; i__ <= i__3; ++i__)
        {
          imle = i__ + linal_1.mle;
          e2r[imle + j * e2r_dim1] = -fjac[i__ + j * fjac_dim1];
          e2i[imle + j * e2i_dim1] = 0.;
        }

      /* Computing MAX */
      i__3 = 1, i__4 = *mumas + 2 - j;
      /* Computing MIN */
      i__5 = linal_1.mbb, i__6 = *mumas + 1 - j + *n;
      i__2 = min(i__5, i__6);

      for (i__ = max(i__3, i__4); i__ <= i__2; ++i__)
        {
          ib = i__ + linal_1.mdiff;
          bb = fmas[i__ + j * fmas_dim1];
          e2r[ib + j * e2r_dim1] += *alphn * bb;
          e2i[ib + j * e2i_dim1] = *betan * bb;
        }
    }

  decbc_(n, lde1, &e2r[e2r_offset], &e2i[e2i_offset], &linal_1.mle, &
         linal_1.mue, &ip2[1], ier);
  return 0;

  /* ----------------------------------------------------------- */

L14:
  /* ---  B IS A BANDED MATRIX, JACOBIAN A BANDED MATRIX, SECOND ORDER */
  i__1 = *nm1;

  for (j = 1; j <= i__1; ++j)
    {
      jm1 = j + *m1;
      i__2 = linal_1.mbjac;

      for (i__ = 1; i__ <= i__2; ++i__)
        {
          e2r[i__ + linal_1.mle + j * e2r_dim1] = -fjac[i__ + jm1 *
                                                  fjac_dim1];
          e2i[i__ + linal_1.mle + j * e2i_dim1] = 0.;
        }

      i__2 = linal_1.mbb;

      for (i__ = 1; i__ <= i__2; ++i__)
        {
          ib = i__ + linal_1.mdiff;
          ffma = fmas[i__ + j * fmas_dim1];
          e2r[ib + j * e2r_dim1] += *alphn * ffma;
          e2i[ib + j * e2i_dim1] += *betan * ffma;
        }
    }

  goto L46;

  /* ----------------------------------------------------------- */

L5:
  /* ---  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX */
  i__1 = *n;

  for (j = 1; j <= i__1; ++j)
    {
      i__2 = *n;

      for (i__ = 1; i__ <= i__2; ++i__)
        {
          bb = fmas[i__ + j * fmas_dim1];
          e2r[i__ + j * e2r_dim1] = bb * *alphn - fjac[i__ + j * fjac_dim1];
          e2i[i__ + j * e2i_dim1] = bb * *betan;
        }
    }

  decc_(n, lde1, &e2r[e2r_offset], &e2i[e2i_offset], &ip2[1], ier);
  return 0;

  /* ----------------------------------------------------------- */

L15:
  /* ---  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER */
  i__1 = *nm1;

  for (j = 1; j <= i__1; ++j)
    {
      jm1 = j + *m1;
      i__2 = *nm1;

      for (i__ = 1; i__ <= i__2; ++i__)
        {
          e2r[i__ + j * e2r_dim1] = *alphn * fmas[i__ + j * fmas_dim1] -
                                    fjac[i__ + jm1 * fjac_dim1];
          e2i[i__ + j * e2i_dim1] = *betan * fmas[i__ + j * fmas_dim1];
        }
    }

  goto L45;

  /* ----------------------------------------------------------- */

L6:
  /* ---  B IS A FULL MATRIX, JACOBIAN A BANDED MATRIX */
  /* ---  THIS OPTION IS NOT PROVIDED */
  return 0;

  /* ----------------------------------------------------------- */

L7:
  /* ---  B=IDENTITY, JACOBIAN A FULL MATRIX, HESSENBERG-OPTION */
  i__1 = *n - 1;

  for (j = 1; j <= i__1; ++j)
    {
      j1 = j + 1;
      e2r[j1 + j * e2r_dim1] = -fjac[j1 + j * fjac_dim1];
      e2i[j1 + j * e2i_dim1] = 0.;
    }

  i__1 = *n;

  for (j = 1; j <= i__1; ++j)
    {
      i__2 = j;

      for (i__ = 1; i__ <= i__2; ++i__)
        {
          e2i[i__ + j * e2i_dim1] = 0.;
          e2r[i__ + j * e2r_dim1] = -fjac[i__ + j * fjac_dim1];
        }

      e2r[j + j * e2r_dim1] += *alphn;
      e2i[j + j * e2i_dim1] = *betan;
    }

  dechc_(n, lde1, &e2r[e2r_offset], &e2i[e2i_offset], &c__1, &ip2[1], ier);
  return 0;

  /* ----------------------------------------------------------- */

L55:
  return 0;
} /* decomc_ */

/*     END OF SUBROUTINE DECOMC */

/* *********************************************************** */

/* Subroutine */ int slvrar_(integer *n, doublereal *fjac, integer *ldjac,
                             integer *mljac, integer *mujac, doublereal *fmas, integer *ldmas,
                             integer *mlmas, integer *mumas, integer *m1, integer *m2, integer *
                             nm1, doublereal *fac1, doublereal *e1, integer *lde1, doublereal *z1,
                             doublereal *f1, integer *ip1, integer *iphes, integer *ier, integer *
                             ijob)
{
  /* System generated locals */
  integer fjac_dim1, fjac_offset, fmas_dim1, fmas_offset, e1_dim1,
          e1_offset, i__1, i__2, i__3, i__4, i__5, i__6;

  /* Local variables */
  static integer i__, j, k;
  static doublereal s1;
  static integer mm, mp, im1, mp1, jkm;
  extern /* Subroutine */ int sol_(integer *, integer *, doublereal *,
                                   doublereal *, integer *);
  static doublereal sum1;
  extern /* Subroutine */ int solb_(integer *, integer *, doublereal *,
                                    integer *, integer *, doublereal *, integer *), solh_(integer *,
                                        integer *, doublereal *, integer *, doublereal *, integer *);
  static doublereal zsafe;

  /* Parameter adjustments */
  --iphes;
  --f1;
  --z1;
  fjac_dim1 = *ldjac;
  fjac_offset = 1 + fjac_dim1;
  fjac -= fjac_offset;
  --ip1;
  fmas_dim1 = *ldmas;
  fmas_offset = 1 + fmas_dim1;
  fmas -= fmas_offset;
  e1_dim1 = *lde1;
  e1_offset = 1 + e1_dim1;
  e1 -= e1_offset;

  /* Function Body */
  switch (*ijob)
    {
      case 1:  goto L1;

      case 2:  goto L2;

      case 3:  goto L3;

      case 4:  goto L4;

      case 5:  goto L5;

      case 6:  goto L6;

      case 7:  goto L7;

      case 8:  goto L55;

      case 9:  goto L55;

      case 10:  goto L55;

      case 11:  goto L11;

      case 12:  goto L12;

      case 13:  goto L13;

      case 14:  goto L13;

      case 15:  goto L15;
    }

  /* ----------------------------------------------------------- */

L1:
  /* ---  B=IDENTITY, JACOBIAN A FULL MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      z1[i__] -= f1[i__] * *fac1;
    }

  sol_(n, lde1, &e1[e1_offset], &z1[1], &ip1[1]);
  return 0;

  /* ----------------------------------------------------------- */

L11:
  /* ---  B=IDENTITY, JACOBIAN A FULL MATRIX, SECOND ORDER */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      z1[i__] -= f1[i__] * *fac1;
    }

L48:
  mm = *m1 / *m2;
  i__1 = *m2;

  for (j = 1; j <= i__1; ++j)
    {
      sum1 = 0.;

      for (k = mm - 1; k >= 0; --k)
        {
          jkm = j + k * *m2;
          sum1 = (z1[jkm] + sum1) / *fac1;
          i__2 = *nm1;

          for (i__ = 1; i__ <= i__2; ++i__)
            {
              im1 = i__ + *m1;
              z1[im1] += fjac[i__ + jkm * fjac_dim1] * sum1;
            }
        }
    }

  sol_(nm1, lde1, &e1[e1_offset], &z1[*m1 + 1], &ip1[1]);
L49:

  for (i__ = *m1; i__ >= 1; --i__)
    {
      z1[i__] = (z1[i__] + z1[*m2 + i__]) / *fac1;
    }

  return 0;

  /* ----------------------------------------------------------- */

L2:
  /* ---  B=IDENTITY, JACOBIAN A BANDED MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      z1[i__] -= f1[i__] * *fac1;
    }

  solb_(n, lde1, &e1[e1_offset], &linal_1.mle, &linal_1.mue, &z1[1], &ip1[1]
       );
  return 0;

  /* ----------------------------------------------------------- */

L12:
  /* ---  B=IDENTITY, JACOBIAN A BANDED MATRIX, SECOND ORDER */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      z1[i__] -= f1[i__] * *fac1;
    }

L45:
  mm = *m1 / *m2;
  i__1 = *m2;

  for (j = 1; j <= i__1; ++j)
    {
      sum1 = 0.;

      for (k = mm - 1; k >= 0; --k)
        {
          jkm = j + k * *m2;
          sum1 = (z1[jkm] + sum1) / *fac1;
          /* Computing MAX */
          i__2 = 1, i__3 = j - *mujac;
          /* Computing MIN */
          i__5 = *nm1, i__6 = j + *mljac;
          i__4 = min(i__5, i__6);

          for (i__ = max(i__2, i__3); i__ <= i__4; ++i__)
            {
              im1 = i__ + *m1;
              z1[im1] += fjac[i__ + *mujac + 1 - j + jkm * fjac_dim1] *
                         sum1;
            }
        }
    }

  solb_(nm1, lde1, &e1[e1_offset], &linal_1.mle, &linal_1.mue, &z1[*m1 + 1],
        &ip1[1]);
  goto L49;

  /* ----------------------------------------------------------- */

L3:
  /* ---  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      s1 = 0.;
      /* Computing MAX */
      i__4 = 1, i__2 = i__ - *mlmas;
      /* Computing MIN */
      i__5 = *n, i__6 = i__ + *mumas;
      i__3 = min(i__5, i__6);

      for (j = max(i__4, i__2); j <= i__3; ++j)
        {
          s1 -= fmas[i__ - j + linal_1.mbdiag + j * fmas_dim1] * f1[j];
        }

      z1[i__] += s1 * *fac1;
    }

  sol_(n, lde1, &e1[e1_offset], &z1[1], &ip1[1]);
  return 0;

  /* ----------------------------------------------------------- */

L13:
  /* ---  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER */
  i__1 = *m1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      z1[i__] -= f1[i__] * *fac1;
    }

  i__1 = *nm1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      im1 = i__ + *m1;
      s1 = 0.;
      /* Computing MAX */
      i__3 = 1, i__4 = i__ - *mlmas;
      /* Computing MIN */
      i__5 = *nm1, i__6 = i__ + *mumas;
      i__2 = min(i__5, i__6);

      for (j = max(i__3, i__4); j <= i__2; ++j)
        {
          s1 -= fmas[i__ - j + linal_1.mbdiag + j * fmas_dim1] * f1[j + *m1]
                ;
        }

      z1[im1] += s1 * *fac1;
    }

  if (*ijob == 14)
    {
      goto L45;
    }

  goto L48;

  /* ----------------------------------------------------------- */

L4:
  /* ---  B IS A BANDED MATRIX, JACOBIAN A BANDED MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      s1 = 0.;
      /* Computing MAX */
      i__2 = 1, i__3 = i__ - *mlmas;
      /* Computing MIN */
      i__5 = *n, i__6 = i__ + *mumas;
      i__4 = min(i__5, i__6);

      for (j = max(i__2, i__3); j <= i__4; ++j)
        {
          s1 -= fmas[i__ - j + linal_1.mbdiag + j * fmas_dim1] * f1[j];
        }

      z1[i__] += s1 * *fac1;
    }

  solb_(n, lde1, &e1[e1_offset], &linal_1.mle, &linal_1.mue, &z1[1], &ip1[1]
       );
  return 0;

  /* ----------------------------------------------------------- */

L5:
  /* ---  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      s1 = 0.;
      i__4 = *n;

      for (j = 1; j <= i__4; ++j)
        {
          s1 -= fmas[i__ + j * fmas_dim1] * f1[j];
        }

      z1[i__] += s1 * *fac1;
    }

  sol_(n, lde1, &e1[e1_offset], &z1[1], &ip1[1]);
  return 0;

  /* ----------------------------------------------------------- */

L15:
  /* ---  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER */
  i__1 = *m1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      z1[i__] -= f1[i__] * *fac1;
    }

  i__1 = *nm1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      im1 = i__ + *m1;
      s1 = 0.;
      i__4 = *nm1;

      for (j = 1; j <= i__4; ++j)
        {
          s1 -= fmas[i__ + j * fmas_dim1] * f1[j + *m1];
        }

      z1[im1] += s1 * *fac1;
    }

  goto L48;

  /* ----------------------------------------------------------- */

L6:
  /* ---  B IS A FULL MATRIX, JACOBIAN A BANDED MATRIX */
  /* ---  THIS OPTION IS NOT PROVIDED */
  return 0;

  /* ----------------------------------------------------------- */

L7:
  /* ---  B=IDENTITY, JACOBIAN A FULL MATRIX, HESSENBERG-OPTION */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      z1[i__] -= f1[i__] * *fac1;
    }

  for (mm = *n - 2; mm >= 1; --mm)
    {
      mp = *n - mm;
      mp1 = mp - 1;
      i__ = iphes[mp];

      if (i__ == mp)
        {
          goto L746;
        }

      zsafe = z1[mp];
      z1[mp] = z1[i__];
      z1[i__] = zsafe;
L746:
      i__1 = *n;

      for (i__ = mp + 1; i__ <= i__1; ++i__)
        {
          z1[i__] -= fjac[i__ + mp1 * fjac_dim1] * z1[mp];
        }
    }

  solh_(n, lde1, &e1[e1_offset], &c__1, &z1[1], &ip1[1]);
  i__1 = *n - 2;

  for (mm = 1; mm <= i__1; ++mm)
    {
      mp = *n - mm;
      mp1 = mp - 1;
      i__4 = *n;

      for (i__ = mp + 1; i__ <= i__4; ++i__)
        {
          z1[i__] += fjac[i__ + mp1 * fjac_dim1] * z1[mp];
        }

      i__ = iphes[mp];

      if (i__ == mp)
        {
          goto L750;
        }

      zsafe = z1[mp];
      z1[mp] = z1[i__];
      z1[i__] = zsafe;
L750:
      ;
    }

  return 0;

  /* ----------------------------------------------------------- */

L55:
  return 0;
} /* slvrar_ */

/*     END OF SUBROUTINE SLVRAR */

/* *********************************************************** */

/* Subroutine */ int slvrai_(integer *n, doublereal *fjac, integer *ldjac,
                             integer *mljac, integer *mujac, doublereal *fmas, integer *ldmas,
                             integer *mlmas, integer *mumas, integer *m1, integer *m2, integer *
                             nm1, doublereal *alphn, doublereal *betan, doublereal *e2r,
                             doublereal *e2i, integer *lde1, doublereal *z2, doublereal *z3,
                             doublereal *f2, doublereal *f3, doublereal *cont, integer *ip2,
                             integer *iphes, integer *ier, integer *ijob)
{
  /* System generated locals */
  integer fjac_dim1, fjac_offset, fmas_dim1, fmas_offset, e2r_dim1,
          e2r_offset, e2i_dim1, e2i_offset, i__1, i__2, i__3, i__4, i__5,
          i__6;
  doublereal d__1, d__2;

  /* Local variables */
  static integer i__, j, k;
  static doublereal s2, s3, bb;
  static integer mm, mp, im1, jm1, mp1;
  static doublereal z2i, z3i;
  static integer jkm, mpi;
  static doublereal sum2, sum3, abno;
  extern /* Subroutine */ int solc_(integer *, integer *, doublereal *,
                                    doublereal *, doublereal *, doublereal *, integer *);
  static integer iimu;
  static doublereal sumh, e1imp;
  extern /* Subroutine */ int solbc_(integer *, integer *, doublereal *,
                                     doublereal *, integer *, integer *, doublereal *, doublereal *,
                                     integer *);
  static doublereal zsafe;
  extern /* Subroutine */ int solhc_(integer *, integer *, doublereal *,
                                     doublereal *, integer *, doublereal *, doublereal *, integer *);

  /* Parameter adjustments */
  --iphes;
  --f3;
  --f2;
  --z3;
  --z2;
  fjac_dim1 = *ldjac;
  fjac_offset = 1 + fjac_dim1;
  fjac -= fjac_offset;
  --ip2;
  fmas_dim1 = *ldmas;
  fmas_offset = 1 + fmas_dim1;
  fmas -= fmas_offset;
  e2i_dim1 = *lde1;
  e2i_offset = 1 + e2i_dim1;
  e2i -= e2i_offset;
  e2r_dim1 = *lde1;
  e2r_offset = 1 + e2r_dim1;
  e2r -= e2r_offset;

  /* Function Body */
  switch (*ijob)
    {
      case 1:  goto L1;

      case 2:  goto L2;

      case 3:  goto L3;

      case 4:  goto L4;

      case 5:  goto L5;

      case 6:  goto L6;

      case 7:  goto L7;

      case 8:  goto L55;

      case 9:  goto L55;

      case 10:  goto L55;

      case 11:  goto L11;

      case 12:  goto L12;

      case 13:  goto L13;

      case 14:  goto L13;

      case 15:  goto L15;
    }

  /* ----------------------------------------------------------- */

L1:
  /* ---  B=IDENTITY, JACOBIAN A FULL MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      s2 = -f2[i__];
      s3 = -f3[i__];
      z2[i__] = z2[i__] + s2 * *alphn - s3 * *betan;
      z3[i__] = z3[i__] + s3 * *alphn + s2 * *betan;
    }

  solc_(n, lde1, &e2r[e2r_offset], &e2i[e2i_offset], &z2[1], &z3[1], &ip2[1]
       );
  return 0;

  /* ----------------------------------------------------------- */

L11:
  /* ---  B=IDENTITY, JACOBIAN A FULL MATRIX, SECOND ORDER */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      s2 = -f2[i__];
      s3 = -f3[i__];
      z2[i__] = z2[i__] + s2 * *alphn - s3 * *betan;
      z3[i__] = z3[i__] + s3 * *alphn + s2 * *betan;
    }

L48:
  /* Computing 2nd power */
  d__1 = *alphn;
  /* Computing 2nd power */
  d__2 = *betan;
  abno = d__1 * d__1 + d__2 * d__2;
  mm = *m1 / *m2;
  i__1 = *m2;

  for (j = 1; j <= i__1; ++j)
    {
      sum2 = 0.;
      sum3 = 0.;

      for (k = mm - 1; k >= 0; --k)
        {
          jkm = j + k * *m2;
          sumh = (z2[jkm] + sum2) / abno;
          sum3 = (z3[jkm] + sum3) / abno;
          sum2 = sumh * *alphn + sum3 * *betan;
          sum3 = sum3 * *alphn - sumh * *betan;
          i__2 = *nm1;

          for (i__ = 1; i__ <= i__2; ++i__)
            {
              im1 = i__ + *m1;
              z2[im1] += fjac[i__ + jkm * fjac_dim1] * sum2;
              z3[im1] += fjac[i__ + jkm * fjac_dim1] * sum3;
            }
        }
    }

  solc_(nm1, lde1, &e2r[e2r_offset], &e2i[e2i_offset], &z2[*m1 + 1], &z3[*
        m1 + 1], &ip2[1]);
L49:

  for (i__ = *m1; i__ >= 1; --i__)
    {
      mpi = *m2 + i__;
      z2i = z2[i__] + z2[mpi];
      z3i = z3[i__] + z3[mpi];
      z3[i__] = (z3i * *alphn - z2i * *betan) / abno;
      z2[i__] = (z2i * *alphn + z3i * *betan) / abno;
    }

  return 0;

  /* ----------------------------------------------------------- */

L2:
  /* ---  B=IDENTITY, JACOBIAN A BANDED MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      s2 = -f2[i__];
      s3 = -f3[i__];
      z2[i__] = z2[i__] + s2 * *alphn - s3 * *betan;
      z3[i__] = z3[i__] + s3 * *alphn + s2 * *betan;
    }

  solbc_(n, lde1, &e2r[e2r_offset], &e2i[e2i_offset], &linal_1.mle, &
         linal_1.mue, &z2[1], &z3[1], &ip2[1]);
  return 0;

  /* ----------------------------------------------------------- */

L12:
  /* ---  B=IDENTITY, JACOBIAN A BANDED MATRIX, SECOND ORDER */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      s2 = -f2[i__];
      s3 = -f3[i__];
      z2[i__] = z2[i__] + s2 * *alphn - s3 * *betan;
      z3[i__] = z3[i__] + s3 * *alphn + s2 * *betan;
    }

L45:
  /* Computing 2nd power */
  d__1 = *alphn;
  /* Computing 2nd power */
  d__2 = *betan;
  abno = d__1 * d__1 + d__2 * d__2;
  mm = *m1 / *m2;
  i__1 = *m2;

  for (j = 1; j <= i__1; ++j)
    {
      sum2 = 0.;
      sum3 = 0.;

      for (k = mm - 1; k >= 0; --k)
        {
          jkm = j + k * *m2;
          sumh = (z2[jkm] + sum2) / abno;
          sum3 = (z3[jkm] + sum3) / abno;
          sum2 = sumh * *alphn + sum3 * *betan;
          sum3 = sum3 * *alphn - sumh * *betan;
          /* Computing MAX */
          i__2 = 1, i__3 = j - *mujac;
          /* Computing MIN */
          i__5 = *nm1, i__6 = j + *mljac;
          i__4 = min(i__5, i__6);

          for (i__ = max(i__2, i__3); i__ <= i__4; ++i__)
            {
              im1 = i__ + *m1;
              iimu = i__ + *mujac + 1 - j;
              z2[im1] += fjac[iimu + jkm * fjac_dim1] * sum2;
              z3[im1] += fjac[iimu + jkm * fjac_dim1] * sum3;
            }
        }
    }

  solbc_(nm1, lde1, &e2r[e2r_offset], &e2i[e2i_offset], &linal_1.mle, &
         linal_1.mue, &z2[*m1 + 1], &z3[*m1 + 1], &ip2[1]);
  goto L49;

  /* ----------------------------------------------------------- */

L3:
  /* ---  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      s2 = 0.;
      s3 = 0.;
      /* Computing MAX */
      i__4 = 1, i__2 = i__ - *mlmas;
      /* Computing MIN */
      i__5 = *n, i__6 = i__ + *mumas;
      i__3 = min(i__5, i__6);

      for (j = max(i__4, i__2); j <= i__3; ++j)
        {
          bb = fmas[i__ - j + linal_1.mbdiag + j * fmas_dim1];
          s2 -= bb * f2[j];
          s3 -= bb * f3[j];
        }

      z2[i__] = z2[i__] + s2 * *alphn - s3 * *betan;
      z3[i__] = z3[i__] + s3 * *alphn + s2 * *betan;
    }

  solc_(n, lde1, &e2r[e2r_offset], &e2i[e2i_offset], &z2[1], &z3[1], &ip2[1]
       );
  return 0;

  /* ----------------------------------------------------------- */

L13:
  /* ---  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER */
  i__1 = *m1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      s2 = -f2[i__];
      s3 = -f3[i__];
      z2[i__] = z2[i__] + s2 * *alphn - s3 * *betan;
      z3[i__] = z3[i__] + s3 * *alphn + s2 * *betan;
    }

  i__1 = *nm1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      im1 = i__ + *m1;
      s2 = 0.;
      s3 = 0.;
      /* Computing MAX */
      i__3 = 1, i__4 = i__ - *mlmas;
      /* Computing MIN */
      i__5 = *nm1, i__6 = i__ + *mumas;
      i__2 = min(i__5, i__6);

      for (j = max(i__3, i__4); j <= i__2; ++j)
        {
          jm1 = j + *m1;
          bb = fmas[i__ - j + linal_1.mbdiag + j * fmas_dim1];
          s2 -= bb * f2[jm1];
          s3 -= bb * f3[jm1];
        }

      z2[im1] = z2[im1] + s2 * *alphn - s3 * *betan;
      z3[im1] = z3[im1] + s3 * *alphn + s2 * *betan;
    }

  if (*ijob == 14)
    {
      goto L45;
    }

  goto L48;

  /* ----------------------------------------------------------- */

L4:
  /* ---  B IS A BANDED MATRIX, JACOBIAN A BANDED MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      s2 = 0.;
      s3 = 0.;
      /* Computing MAX */
      i__2 = 1, i__3 = i__ - *mlmas;
      /* Computing MIN */
      i__5 = *n, i__6 = i__ + *mumas;
      i__4 = min(i__5, i__6);

      for (j = max(i__2, i__3); j <= i__4; ++j)
        {
          bb = fmas[i__ - j + linal_1.mbdiag + j * fmas_dim1];
          s2 -= bb * f2[j];
          s3 -= bb * f3[j];
        }

      z2[i__] = z2[i__] + s2 * *alphn - s3 * *betan;
      z3[i__] = z3[i__] + s3 * *alphn + s2 * *betan;
    }

  solbc_(n, lde1, &e2r[e2r_offset], &e2i[e2i_offset], &linal_1.mle, &
         linal_1.mue, &z2[1], &z3[1], &ip2[1]);
  return 0;

  /* ----------------------------------------------------------- */

L5:
  /* ---  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      s2 = 0.;
      s3 = 0.;
      i__4 = *n;

      for (j = 1; j <= i__4; ++j)
        {
          bb = fmas[i__ + j * fmas_dim1];
          s2 -= bb * f2[j];
          s3 -= bb * f3[j];
        }

      z2[i__] = z2[i__] + s2 * *alphn - s3 * *betan;
      z3[i__] = z3[i__] + s3 * *alphn + s2 * *betan;
    }

  solc_(n, lde1, &e2r[e2r_offset], &e2i[e2i_offset], &z2[1], &z3[1], &ip2[1]
       );
  return 0;

  /* ----------------------------------------------------------- */

L15:
  /* ---  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER */
  i__1 = *m1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      s2 = -f2[i__];
      s3 = -f3[i__];
      z2[i__] = z2[i__] + s2 * *alphn - s3 * *betan;
      z3[i__] = z3[i__] + s3 * *alphn + s2 * *betan;
    }

  i__1 = *nm1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      im1 = i__ + *m1;
      s2 = 0.;
      s3 = 0.;
      i__4 = *nm1;

      for (j = 1; j <= i__4; ++j)
        {
          jm1 = j + *m1;
          bb = fmas[i__ + j * fmas_dim1];
          s2 -= bb * f2[jm1];
          s3 -= bb * f3[jm1];
        }

      z2[im1] = z2[im1] + s2 * *alphn - s3 * *betan;
      z3[im1] = z3[im1] + s3 * *alphn + s2 * *betan;
    }

  goto L48;

  /* ----------------------------------------------------------- */

L6:
  /* ---  B IS A FULL MATRIX, JACOBIAN A BANDED MATRIX */
  /* ---  THIS OPTION IS NOT PROVIDED */
  return 0;

  /* ----------------------------------------------------------- */

L7:
  /* ---  B=IDENTITY, JACOBIAN A FULL MATRIX, HESSENBERG-OPTION */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      s2 = -f2[i__];
      s3 = -f3[i__];
      z2[i__] = z2[i__] + s2 * *alphn - s3 * *betan;
      z3[i__] = z3[i__] + s3 * *alphn + s2 * *betan;
    }

  for (mm = *n - 2; mm >= 1; --mm)
    {
      mp = *n - mm;
      mp1 = mp - 1;
      i__ = iphes[mp];

      if (i__ == mp)
        {
          goto L746;
        }

      zsafe = z2[mp];
      z2[mp] = z2[i__];
      z2[i__] = zsafe;
      zsafe = z3[mp];
      z3[mp] = z3[i__];
      z3[i__] = zsafe;
L746:
      i__1 = *n;

      for (i__ = mp + 1; i__ <= i__1; ++i__)
        {
          e1imp = fjac[i__ + mp1 * fjac_dim1];
          z2[i__] -= e1imp * z2[mp];
          z3[i__] -= e1imp * z3[mp];
        }
    }

  solhc_(n, lde1, &e2r[e2r_offset], &e2i[e2i_offset], &c__1, &z2[1], &z3[1],
         &ip2[1]);
  i__1 = *n - 2;

  for (mm = 1; mm <= i__1; ++mm)
    {
      mp = *n - mm;
      mp1 = mp - 1;
      i__4 = *n;

      for (i__ = mp + 1; i__ <= i__4; ++i__)
        {
          e1imp = fjac[i__ + mp1 * fjac_dim1];
          z2[i__] += e1imp * z2[mp];
          z3[i__] += e1imp * z3[mp];
        }

      i__ = iphes[mp];

      if (i__ == mp)
        {
          goto L750;
        }

      zsafe = z2[mp];
      z2[mp] = z2[i__];
      z2[i__] = zsafe;
      zsafe = z3[mp];
      z3[mp] = z3[i__];
      z3[i__] = zsafe;
L750:
      ;
    }

  return 0;

  /* ----------------------------------------------------------- */

L55:
  return 0;
} /* slvrai_ */

/*     END OF SUBROUTINE SLVRAI */

/* *********************************************************** */

/* Subroutine */ int slvrad_(integer *n, doublereal *fjac, integer *ldjac,
                             integer *mljac, integer *mujac, doublereal *fmas, integer *ldmas,
                             integer *mlmas, integer *mumas, integer *m1, integer *m2, integer *
                             nm1, doublereal *fac1, doublereal *alphn, doublereal *betan,
                             doublereal *e1, doublereal *e2r, doublereal *e2i, integer *lde1,
                             doublereal *z1, doublereal *z2, doublereal *z3, doublereal *f1,
                             doublereal *f2, doublereal *f3, doublereal *cont, integer *ip1,
                             integer *ip2, integer *iphes, integer *ier, integer *ijob)
{
  /* System generated locals */
  integer fjac_dim1, fjac_offset, fmas_dim1, fmas_offset, e1_dim1,
          e1_offset, e2r_dim1, e2r_offset, e2i_dim1, e2i_offset, i__1, i__2,
          i__3, i__4, i__5, i__6;
  doublereal d__1, d__2;

  /* Local variables */
  static integer i__, j, k;
  static doublereal s1, s2, s3, bb;
  static integer mm, mp, j1b, j2b, im1, jm1, mp1;
  static doublereal z2i, z3i;
  static integer jkm, mpi;
  extern /* Subroutine */ int sol_(integer *, integer *, doublereal *,
                                   doublereal *, integer *);
  static doublereal sum1, sum2, sum3, ffja, abno;
  extern /* Subroutine */ int solb_(integer *, integer *, doublereal *,
                                    integer *, integer *, doublereal *, integer *), solc_(integer *,
                                        integer *, doublereal *, doublereal *, doublereal *, doublereal *,
                                        integer *), solh_(integer *, integer *, doublereal *, integer *,
                                            doublereal *, integer *);
  static doublereal sumh, e1imp;
  extern /* Subroutine */ int solbc_(integer *, integer *, doublereal *,
                                     doublereal *, integer *, integer *, doublereal *, doublereal *,
                                     integer *);
  static doublereal zsafe;
  extern /* Subroutine */ int solhc_(integer *, integer *, doublereal *,
                                     doublereal *, integer *, doublereal *, doublereal *, integer *);

  /* Parameter adjustments */
  --iphes;
  --f3;
  --f2;
  --f1;
  --z3;
  --z2;
  --z1;
  fjac_dim1 = *ldjac;
  fjac_offset = 1 + fjac_dim1;
  fjac -= fjac_offset;
  --ip2;
  --ip1;
  fmas_dim1 = *ldmas;
  fmas_offset = 1 + fmas_dim1;
  fmas -= fmas_offset;
  e2i_dim1 = *lde1;
  e2i_offset = 1 + e2i_dim1;
  e2i -= e2i_offset;
  e2r_dim1 = *lde1;
  e2r_offset = 1 + e2r_dim1;
  e2r -= e2r_offset;
  e1_dim1 = *lde1;
  e1_offset = 1 + e1_dim1;
  e1 -= e1_offset;

  /* Function Body */
  switch (*ijob)
    {
      case 1:  goto L1;

      case 2:  goto L2;

      case 3:  goto L3;

      case 4:  goto L4;

      case 5:  goto L5;

      case 6:  goto L6;

      case 7:  goto L7;

      case 8:  goto L55;

      case 9:  goto L55;

      case 10:  goto L55;

      case 11:  goto L11;

      case 12:  goto L12;

      case 13:  goto L13;

      case 14:  goto L13;

      case 15:  goto L15;
    }

  /* ----------------------------------------------------------- */

L1:
  /* ---  B=IDENTITY, JACOBIAN A FULL MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      s2 = -f2[i__];
      s3 = -f3[i__];
      z1[i__] -= f1[i__] * *fac1;
      z2[i__] = z2[i__] + s2 * *alphn - s3 * *betan;
      z3[i__] = z3[i__] + s3 * *alphn + s2 * *betan;
    }

  sol_(n, lde1, &e1[e1_offset], &z1[1], &ip1[1]);
  solc_(n, lde1, &e2r[e2r_offset], &e2i[e2i_offset], &z2[1], &z3[1], &ip2[1]
       );
  return 0;

  /* ----------------------------------------------------------- */

L11:
  /* ---  B=IDENTITY, JACOBIAN A FULL MATRIX, SECOND ORDER */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      s2 = -f2[i__];
      s3 = -f3[i__];
      z1[i__] -= f1[i__] * *fac1;
      z2[i__] = z2[i__] + s2 * *alphn - s3 * *betan;
      z3[i__] = z3[i__] + s3 * *alphn + s2 * *betan;
    }

L48:
  /* Computing 2nd power */
  d__1 = *alphn;
  /* Computing 2nd power */
  d__2 = *betan;
  abno = d__1 * d__1 + d__2 * d__2;
  mm = *m1 / *m2;
  i__1 = *m2;

  for (j = 1; j <= i__1; ++j)
    {
      sum1 = 0.;
      sum2 = 0.;
      sum3 = 0.;

      for (k = mm - 1; k >= 0; --k)
        {
          jkm = j + k * *m2;
          sum1 = (z1[jkm] + sum1) / *fac1;
          sumh = (z2[jkm] + sum2) / abno;
          sum3 = (z3[jkm] + sum3) / abno;
          sum2 = sumh * *alphn + sum3 * *betan;
          sum3 = sum3 * *alphn - sumh * *betan;
          i__2 = *nm1;

          for (i__ = 1; i__ <= i__2; ++i__)
            {
              im1 = i__ + *m1;
              z1[im1] += fjac[i__ + jkm * fjac_dim1] * sum1;
              z2[im1] += fjac[i__ + jkm * fjac_dim1] * sum2;
              z3[im1] += fjac[i__ + jkm * fjac_dim1] * sum3;
            }
        }
    }

  sol_(nm1, lde1, &e1[e1_offset], &z1[*m1 + 1], &ip1[1]);
  solc_(nm1, lde1, &e2r[e2r_offset], &e2i[e2i_offset], &z2[*m1 + 1], &z3[*
        m1 + 1], &ip2[1]);
L49:

  for (i__ = *m1; i__ >= 1; --i__)
    {
      mpi = *m2 + i__;
      z1[i__] = (z1[i__] + z1[mpi]) / *fac1;
      z2i = z2[i__] + z2[mpi];
      z3i = z3[i__] + z3[mpi];
      z3[i__] = (z3i * *alphn - z2i * *betan) / abno;
      z2[i__] = (z2i * *alphn + z3i * *betan) / abno;
    }

  return 0;

  /* ----------------------------------------------------------- */

L2:
  /* ---  B=IDENTITY, JACOBIAN A BANDED MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      s2 = -f2[i__];
      s3 = -f3[i__];
      z1[i__] -= f1[i__] * *fac1;
      z2[i__] = z2[i__] + s2 * *alphn - s3 * *betan;
      z3[i__] = z3[i__] + s3 * *alphn + s2 * *betan;
    }

  solb_(n, lde1, &e1[e1_offset], &linal_1.mle, &linal_1.mue, &z1[1], &ip1[1]
       );
  solbc_(n, lde1, &e2r[e2r_offset], &e2i[e2i_offset], &linal_1.mle, &
         linal_1.mue, &z2[1], &z3[1], &ip2[1]);
  return 0;

  /* ----------------------------------------------------------- */

L12:
  /* ---  B=IDENTITY, JACOBIAN A BANDED MATRIX, SECOND ORDER */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      s2 = -f2[i__];
      s3 = -f3[i__];
      z1[i__] -= f1[i__] * *fac1;
      z2[i__] = z2[i__] + s2 * *alphn - s3 * *betan;
      z3[i__] = z3[i__] + s3 * *alphn + s2 * *betan;
    }

L45:
  /* Computing 2nd power */
  d__1 = *alphn;
  /* Computing 2nd power */
  d__2 = *betan;
  abno = d__1 * d__1 + d__2 * d__2;
  mm = *m1 / *m2;
  i__1 = *m2;

  for (j = 1; j <= i__1; ++j)
    {
      sum1 = 0.;
      sum2 = 0.;
      sum3 = 0.;

      for (k = mm - 1; k >= 0; --k)
        {
          jkm = j + k * *m2;
          sum1 = (z1[jkm] + sum1) / *fac1;
          sumh = (z2[jkm] + sum2) / abno;
          sum3 = (z3[jkm] + sum3) / abno;
          sum2 = sumh * *alphn + sum3 * *betan;
          sum3 = sum3 * *alphn - sumh * *betan;
          /* Computing MAX */
          i__2 = 1, i__3 = j - *mujac;
          /* Computing MIN */
          i__5 = *nm1, i__6 = j + *mljac;
          i__4 = min(i__5, i__6);

          for (i__ = max(i__2, i__3); i__ <= i__4; ++i__)
            {
              im1 = i__ + *m1;
              ffja = fjac[i__ + *mujac + 1 - j + jkm * fjac_dim1];
              z1[im1] += ffja * sum1;
              z2[im1] += ffja * sum2;
              z3[im1] += ffja * sum3;
            }
        }
    }

  solb_(nm1, lde1, &e1[e1_offset], &linal_1.mle, &linal_1.mue, &z1[*m1 + 1],
        &ip1[1]);
  solbc_(nm1, lde1, &e2r[e2r_offset], &e2i[e2i_offset], &linal_1.mle, &
         linal_1.mue, &z2[*m1 + 1], &z3[*m1 + 1], &ip2[1]);
  goto L49;

  /* ----------------------------------------------------------- */

L3:
  /* ---  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      s1 = 0.;
      s2 = 0.;
      s3 = 0.;
      /* Computing MAX */
      i__4 = 1, i__2 = i__ - *mlmas;
      /* Computing MIN */
      i__5 = *n, i__6 = i__ + *mumas;
      i__3 = min(i__5, i__6);

      for (j = max(i__4, i__2); j <= i__3; ++j)
        {
          bb = fmas[i__ - j + linal_1.mbdiag + j * fmas_dim1];
          s1 -= bb * f1[j];
          s2 -= bb * f2[j];
          s3 -= bb * f3[j];
        }

      z1[i__] += s1 * *fac1;
      z2[i__] = z2[i__] + s2 * *alphn - s3 * *betan;
      z3[i__] = z3[i__] + s3 * *alphn + s2 * *betan;
    }

  sol_(n, lde1, &e1[e1_offset], &z1[1], &ip1[1]);
  solc_(n, lde1, &e2r[e2r_offset], &e2i[e2i_offset], &z2[1], &z3[1], &ip2[1]
       );
  return 0;

  /* ----------------------------------------------------------- */

L13:
  /* ---  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER */
  i__1 = *m1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      s2 = -f2[i__];
      s3 = -f3[i__];
      z1[i__] -= f1[i__] * *fac1;
      z2[i__] = z2[i__] + s2 * *alphn - s3 * *betan;
      z3[i__] = z3[i__] + s3 * *alphn + s2 * *betan;
    }

  i__1 = *nm1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      im1 = i__ + *m1;
      s1 = 0.;
      s2 = 0.;
      s3 = 0.;
      /* Computing MAX */
      i__3 = 1, i__4 = i__ - *mlmas;
      j1b = max(i__3, i__4);
      /* Computing MIN */
      i__3 = *nm1, i__4 = i__ + *mumas;
      j2b = min(i__3, i__4);
      i__3 = j2b;

      for (j = j1b; j <= i__3; ++j)
        {
          jm1 = j + *m1;
          bb = fmas[i__ - j + linal_1.mbdiag + j * fmas_dim1];
          s1 -= bb * f1[jm1];
          s2 -= bb * f2[jm1];
          s3 -= bb * f3[jm1];
        }

      z1[im1] += s1 * *fac1;
      z2[im1] = z2[im1] + s2 * *alphn - s3 * *betan;
      z3[im1] = z3[im1] + s3 * *alphn + s2 * *betan;
    }

  if (*ijob == 14)
    {
      goto L45;
    }

  goto L48;

  /* ----------------------------------------------------------- */

L4:
  /* ---  B IS A BANDED MATRIX, JACOBIAN A BANDED MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      s1 = 0.;
      s2 = 0.;
      s3 = 0.;
      /* Computing MAX */
      i__3 = 1, i__4 = i__ - *mlmas;
      /* Computing MIN */
      i__5 = *n, i__6 = i__ + *mumas;
      i__2 = min(i__5, i__6);

      for (j = max(i__3, i__4); j <= i__2; ++j)
        {
          bb = fmas[i__ - j + linal_1.mbdiag + j * fmas_dim1];
          s1 -= bb * f1[j];
          s2 -= bb * f2[j];
          s3 -= bb * f3[j];
        }

      z1[i__] += s1 * *fac1;
      z2[i__] = z2[i__] + s2 * *alphn - s3 * *betan;
      z3[i__] = z3[i__] + s3 * *alphn + s2 * *betan;
    }

  solb_(n, lde1, &e1[e1_offset], &linal_1.mle, &linal_1.mue, &z1[1], &ip1[1]
       );
  solbc_(n, lde1, &e2r[e2r_offset], &e2i[e2i_offset], &linal_1.mle, &
         linal_1.mue, &z2[1], &z3[1], &ip2[1]);
  return 0;

  /* ----------------------------------------------------------- */

L5:
  /* ---  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      s1 = 0.;
      s2 = 0.;
      s3 = 0.;
      i__2 = *n;

      for (j = 1; j <= i__2; ++j)
        {
          bb = fmas[i__ + j * fmas_dim1];
          s1 -= bb * f1[j];
          s2 -= bb * f2[j];
          s3 -= bb * f3[j];
        }

      z1[i__] += s1 * *fac1;
      z2[i__] = z2[i__] + s2 * *alphn - s3 * *betan;
      z3[i__] = z3[i__] + s3 * *alphn + s2 * *betan;
    }

  sol_(n, lde1, &e1[e1_offset], &z1[1], &ip1[1]);
  solc_(n, lde1, &e2r[e2r_offset], &e2i[e2i_offset], &z2[1], &z3[1], &ip2[1]
       );
  return 0;

  /* ----------------------------------------------------------- */

L15:
  /* ---  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER */
  i__1 = *m1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      s2 = -f2[i__];
      s3 = -f3[i__];
      z1[i__] -= f1[i__] * *fac1;
      z2[i__] = z2[i__] + s2 * *alphn - s3 * *betan;
      z3[i__] = z3[i__] + s3 * *alphn + s2 * *betan;
    }

  i__1 = *nm1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      im1 = i__ + *m1;
      s1 = 0.;
      s2 = 0.;
      s3 = 0.;
      i__2 = *nm1;

      for (j = 1; j <= i__2; ++j)
        {
          jm1 = j + *m1;
          bb = fmas[i__ + j * fmas_dim1];
          s1 -= bb * f1[jm1];
          s2 -= bb * f2[jm1];
          s3 -= bb * f3[jm1];
        }

      z1[im1] += s1 * *fac1;
      z2[im1] = z2[im1] + s2 * *alphn - s3 * *betan;
      z3[im1] = z3[im1] + s3 * *alphn + s2 * *betan;
    }

  goto L48;

  /* ----------------------------------------------------------- */

L6:
  /* ---  B IS A FULL MATRIX, JACOBIAN A BANDED MATRIX */
  /* ---  THIS OPTION IS NOT PROVIDED */
  return 0;

  /* ----------------------------------------------------------- */

L7:
  /* ---  B=IDENTITY, JACOBIAN A FULL MATRIX, HESSENBERG-OPTION */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      s2 = -f2[i__];
      s3 = -f3[i__];
      z1[i__] -= f1[i__] * *fac1;
      z2[i__] = z2[i__] + s2 * *alphn - s3 * *betan;
      z3[i__] = z3[i__] + s3 * *alphn + s2 * *betan;
    }

  for (mm = *n - 2; mm >= 1; --mm)
    {
      mp = *n - mm;
      mp1 = mp - 1;
      i__ = iphes[mp];

      if (i__ == mp)
        {
          goto L746;
        }

      zsafe = z1[mp];
      z1[mp] = z1[i__];
      z1[i__] = zsafe;
      zsafe = z2[mp];
      z2[mp] = z2[i__];
      z2[i__] = zsafe;
      zsafe = z3[mp];
      z3[mp] = z3[i__];
      z3[i__] = zsafe;
L746:
      i__1 = *n;

      for (i__ = mp + 1; i__ <= i__1; ++i__)
        {
          e1imp = fjac[i__ + mp1 * fjac_dim1];
          z1[i__] -= e1imp * z1[mp];
          z2[i__] -= e1imp * z2[mp];
          z3[i__] -= e1imp * z3[mp];
        }
    }

  solh_(n, lde1, &e1[e1_offset], &c__1, &z1[1], &ip1[1]);
  solhc_(n, lde1, &e2r[e2r_offset], &e2i[e2i_offset], &c__1, &z2[1], &z3[1],
         &ip2[1]);
  i__1 = *n - 2;

  for (mm = 1; mm <= i__1; ++mm)
    {
      mp = *n - mm;
      mp1 = mp - 1;
      i__2 = *n;

      for (i__ = mp + 1; i__ <= i__2; ++i__)
        {
          e1imp = fjac[i__ + mp1 * fjac_dim1];
          z1[i__] += e1imp * z1[mp];
          z2[i__] += e1imp * z2[mp];
          z3[i__] += e1imp * z3[mp];
        }

      i__ = iphes[mp];

      if (i__ == mp)
        {
          goto L750;
        }

      zsafe = z1[mp];
      z1[mp] = z1[i__];
      z1[i__] = zsafe;
      zsafe = z2[mp];
      z2[mp] = z2[i__];
      z2[i__] = zsafe;
      zsafe = z3[mp];
      z3[mp] = z3[i__];
      z3[i__] = zsafe;
L750:
      ;
    }

  return 0;

  /* ----------------------------------------------------------- */

L55:
  return 0;
} /* slvrad_ */

/*     END OF SUBROUTINE SLVRAD */

/* *********************************************************** */

/* Subroutine */ int estrad_(integer *n, doublereal *fjac, integer *ldjac,
                             integer *mljac, integer *mujac, doublereal *fmas, integer *ldmas,
                             integer *mlmas, integer *mumas, doublereal *h__, doublereal *dd1,
                             doublereal *dd2, doublereal *dd3, CRadau5::evalF fcn, integer *nfcn, doublereal
                             *y0, doublereal *y, integer *ijob, doublereal *x, integer *m1,
                             integer *m2, integer *nm1, doublereal *e1, integer *lde1, doublereal *
                             z1, doublereal *z2, doublereal *z3, doublereal *cont, doublereal *f1,
                             doublereal *f2, integer *ip1, integer *iphes, doublereal *scal,
                             doublereal *err, logical *first, logical *reject, doublereal *fac1,
                             doublereal *rpar, integer *ipar)
{
  /* System generated locals */
  integer fjac_dim1, fjac_offset, fmas_dim1, fmas_offset, e1_dim1,
          e1_offset, i__1, i__2, i__3, i__4, i__5, i__6;
  doublereal d__1;

  /* Local variables */
  static integer i__, j, k, mm, mp, im1;
  extern /* Subroutine */ int sol_(integer *, integer *, doublereal *,
                                   doublereal *, integer *);
  static doublereal sum, hee1, hee2, hee3, sum1;
  extern /* Subroutine */ int solb_(integer *, integer *, doublereal *,
                                    integer *, integer *, doublereal *, integer *), solh_(integer *,
                                        integer *, doublereal *, integer *, doublereal *, integer *);
  static doublereal zsafe;

  /* Parameter adjustments */
  --scal;
  --iphes;
  --f2;
  --f1;
  --cont;
  --z3;
  --z2;
  --z1;
  --y;
  --y0;
  fjac_dim1 = *ldjac;
  fjac_offset = 1 + fjac_dim1;
  fjac -= fjac_offset;
  --ip1;
  fmas_dim1 = *ldmas;
  fmas_offset = 1 + fmas_dim1;
  fmas -= fmas_offset;
  e1_dim1 = *lde1;
  e1_offset = 1 + e1_dim1;
  e1 -= e1_offset;
  --rpar;
  --ipar;

  /* Function Body */
  hee1 = *dd1 / *h__;
  hee2 = *dd2 / *h__;
  hee3 = *dd3 / *h__;

  switch (*ijob)
    {
      case 1:  goto L1;

      case 2:  goto L2;

      case 3:  goto L3;

      case 4:  goto L4;

      case 5:  goto L5;

      case 6:  goto L6;

      case 7:  goto L7;

      case 8:  goto L55;

      case 9:  goto L55;

      case 10:  goto L55;

      case 11:  goto L11;

      case 12:  goto L12;

      case 13:  goto L13;

      case 14:  goto L14;

      case 15:  goto L15;
    }

L1:
  /* ------  B=IDENTITY, JACOBIAN A FULL MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      f2[i__] = hee1 * z1[i__] + hee2 * z2[i__] + hee3 * z3[i__];
      cont[i__] = f2[i__] + y0[i__];
    }

  sol_(n, lde1, &e1[e1_offset], &cont[1], &ip1[1]);
  goto L77;

L11:
  /* ------  B=IDENTITY, JACOBIAN A FULL MATRIX, SECOND ORDER */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      f2[i__] = hee1 * z1[i__] + hee2 * z2[i__] + hee3 * z3[i__];
      cont[i__] = f2[i__] + y0[i__];
    }

L48:
  mm = *m1 / *m2;
  i__1 = *m2;

  for (j = 1; j <= i__1; ++j)
    {
      sum1 = 0.;

      for (k = mm - 1; k >= 0; --k)
        {
          sum1 = (cont[j + k * *m2] + sum1) / *fac1;
          i__2 = *nm1;

          for (i__ = 1; i__ <= i__2; ++i__)
            {
              im1 = i__ + *m1;
              cont[im1] += fjac[i__ + (j + k * *m2) * fjac_dim1] * sum1;
            }
        }
    }

  sol_(nm1, lde1, &e1[e1_offset], &cont[*m1 + 1], &ip1[1]);

  for (i__ = *m1; i__ >= 1; --i__)
    {
      cont[i__] = (cont[i__] + cont[*m2 + i__]) / *fac1;
    }

  goto L77;

L2:
  /* ------  B=IDENTITY, JACOBIAN A BANDED MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      f2[i__] = hee1 * z1[i__] + hee2 * z2[i__] + hee3 * z3[i__];
      cont[i__] = f2[i__] + y0[i__];
    }

  solb_(n, lde1, &e1[e1_offset], &linal_1.mle, &linal_1.mue, &cont[1], &ip1[
          1]);
  goto L77;

L12:
  /* ------  B=IDENTITY, JACOBIAN A BANDED MATRIX, SECOND ORDER */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      f2[i__] = hee1 * z1[i__] + hee2 * z2[i__] + hee3 * z3[i__];
      cont[i__] = f2[i__] + y0[i__];
    }

L45:
  mm = *m1 / *m2;
  i__1 = *m2;

  for (j = 1; j <= i__1; ++j)
    {
      sum1 = 0.;

      for (k = mm - 1; k >= 0; --k)
        {
          sum1 = (cont[j + k * *m2] + sum1) / *fac1;
          /* Computing MAX */
          i__2 = 1, i__3 = j - *mujac;
          /* Computing MIN */
          i__5 = *nm1, i__6 = j + *mljac;
          i__4 = min(i__5, i__6);

          for (i__ = max(i__2, i__3); i__ <= i__4; ++i__)
            {
              im1 = i__ + *m1;
              cont[im1] += fjac[i__ + *mujac + 1 - j + (j + k * *m2) *
                                fjac_dim1] * sum1;
            }
        }
    }

  solb_(nm1, lde1, &e1[e1_offset], &linal_1.mle, &linal_1.mue, &cont[*m1 +
        1], &ip1[1]);

  for (i__ = *m1; i__ >= 1; --i__)
    {
      cont[i__] = (cont[i__] + cont[*m2 + i__]) / *fac1;
    }

  goto L77;

L3:
  /* ------  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      f1[i__] = hee1 * z1[i__] + hee2 * z2[i__] + hee3 * z3[i__];
    }

  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      /* Computing MAX */
      i__4 = 1, i__2 = i__ - *mlmas;
      /* Computing MIN */
      i__5 = *n, i__6 = i__ + *mumas;
      i__3 = min(i__5, i__6);

      for (j = max(i__4, i__2); j <= i__3; ++j)
        {
          sum += fmas[i__ - j + linal_1.mbdiag + j * fmas_dim1] * f1[j];
        }

      f2[i__] = sum;
      cont[i__] = sum + y0[i__];
    }

  sol_(n, lde1, &e1[e1_offset], &cont[1], &ip1[1]);
  goto L77;

L13:
  /* ------  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER */
  i__1 = *m1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      f2[i__] = hee1 * z1[i__] + hee2 * z2[i__] + hee3 * z3[i__];
      cont[i__] = f2[i__] + y0[i__];
    }

  i__1 = *n;

  for (i__ = *m1 + 1; i__ <= i__1; ++i__)
    {
      f1[i__] = hee1 * z1[i__] + hee2 * z2[i__] + hee3 * z3[i__];
    }

  i__1 = *nm1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      /* Computing MAX */
      i__3 = 1, i__4 = i__ - *mlmas;
      /* Computing MIN */
      i__5 = *nm1, i__6 = i__ + *mumas;
      i__2 = min(i__5, i__6);

      for (j = max(i__3, i__4); j <= i__2; ++j)
        {
          sum += fmas[i__ - j + linal_1.mbdiag + j * fmas_dim1] * f1[j + *
                 m1];
        }

      im1 = i__ + *m1;
      f2[im1] = sum;
      cont[im1] = sum + y0[im1];
    }

  goto L48;

L4:
  /* ------  B IS A BANDED MATRIX, JACOBIAN A BANDED MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      f1[i__] = hee1 * z1[i__] + hee2 * z2[i__] + hee3 * z3[i__];
    }

  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      /* Computing MAX */
      i__2 = 1, i__3 = i__ - *mlmas;
      /* Computing MIN */
      i__5 = *n, i__6 = i__ + *mumas;
      i__4 = min(i__5, i__6);

      for (j = max(i__2, i__3); j <= i__4; ++j)
        {
          sum += fmas[i__ - j + linal_1.mbdiag + j * fmas_dim1] * f1[j];
        }

      f2[i__] = sum;
      cont[i__] = sum + y0[i__];
    }

  solb_(n, lde1, &e1[e1_offset], &linal_1.mle, &linal_1.mue, &cont[1], &ip1[
          1]);
  goto L77;

L14:
  /* ------  B IS A BANDED MATRIX, JACOBIAN A BANDED MATRIX, SECOND ORDER */
  i__1 = *m1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      f2[i__] = hee1 * z1[i__] + hee2 * z2[i__] + hee3 * z3[i__];
      cont[i__] = f2[i__] + y0[i__];
    }

  i__1 = *n;

  for (i__ = *m1 + 1; i__ <= i__1; ++i__)
    {
      f1[i__] = hee1 * z1[i__] + hee2 * z2[i__] + hee3 * z3[i__];
    }

  i__1 = *nm1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      /* Computing MAX */
      i__4 = 1, i__2 = i__ - *mlmas;
      /* Computing MIN */
      i__5 = *nm1, i__6 = i__ + *mumas;
      i__3 = min(i__5, i__6);

      for (j = max(i__4, i__2); j <= i__3; ++j)
        {
          sum += fmas[i__ - j + linal_1.mbdiag + j * fmas_dim1] * f1[j + *
                 m1];
        }

      im1 = i__ + *m1;
      f2[im1] = sum;
      cont[im1] = sum + y0[im1];
    }

  goto L45;

L5:
  /* ------  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      f1[i__] = hee1 * z1[i__] + hee2 * z2[i__] + hee3 * z3[i__];
    }

  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      i__3 = *n;

      for (j = 1; j <= i__3; ++j)
        {
          sum += fmas[i__ + j * fmas_dim1] * f1[j];
        }

      f2[i__] = sum;
      cont[i__] = sum + y0[i__];
    }

  sol_(n, lde1, &e1[e1_offset], &cont[1], &ip1[1]);
  goto L77;

L15:
  /* ------  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER */
  i__1 = *m1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      f2[i__] = hee1 * z1[i__] + hee2 * z2[i__] + hee3 * z3[i__];
      cont[i__] = f2[i__] + y0[i__];
    }

  i__1 = *n;

  for (i__ = *m1 + 1; i__ <= i__1; ++i__)
    {
      f1[i__] = hee1 * z1[i__] + hee2 * z2[i__] + hee3 * z3[i__];
    }

  i__1 = *nm1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      i__3 = *nm1;

      for (j = 1; j <= i__3; ++j)
        {
          sum += fmas[i__ + j * fmas_dim1] * f1[j + *m1];
        }

      im1 = i__ + *m1;
      f2[im1] = sum;
      cont[im1] = sum + y0[im1];
    }

  goto L48;

L6:
  /* ------  B IS A FULL MATRIX, JACOBIAN A BANDED MATRIX */
  /* ------  THIS OPTION IS NOT PROVIDED */
  return 0;

L7:
  /* ------  B=IDENTITY, JACOBIAN A FULL MATRIX, HESSENBERG-OPTION */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      f2[i__] = hee1 * z1[i__] + hee2 * z2[i__] + hee3 * z3[i__];
      cont[i__] = f2[i__] + y0[i__];
    }

  for (mm = *n - 2; mm >= 1; --mm)
    {
      mp = *n - mm;
      i__ = iphes[mp];

      if (i__ == mp)
        {
          goto L310;
        }

      zsafe = cont[mp];
      cont[mp] = cont[i__];
      cont[i__] = zsafe;
L310:
      i__1 = *n;

      for (i__ = mp + 1; i__ <= i__1; ++i__)
        {
          cont[i__] -= fjac[i__ + (mp - 1) * fjac_dim1] * cont[mp];
        }
    }

  solh_(n, lde1, &e1[e1_offset], &c__1, &cont[1], &ip1[1]);
  i__1 = *n - 2;

  for (mm = 1; mm <= i__1; ++mm)
    {
      mp = *n - mm;
      i__3 = *n;

      for (i__ = mp + 1; i__ <= i__3; ++i__)
        {
          cont[i__] += fjac[i__ + (mp - 1) * fjac_dim1] * cont[mp];
        }

      i__ = iphes[mp];

      if (i__ == mp)
        {
          goto L440;
        }

      zsafe = cont[mp];
      cont[mp] = cont[i__];
      cont[i__] = zsafe;
L440:
      ;
    }

  /* -------------------------------------- */

L77:
  *err = 0.;
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* Computing 2nd power */
      d__1 = cont[i__] / scal[i__];
      *err += d__1 * d__1;
    }

  /* Computing MAX */
  d__1 = sqrt(*err / *n);
  *err = max(d__1, 1e-10);

  if (*err < 1.)
    {
      return 0;
    }

  if (*first || *reject)
    {
      i__1 = *n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          cont[i__] = y[i__] + cont[i__];
        }

      (*fcn)(n, x, &cont[1], &f1[1], &rpar[1], &ipar[1]);
      ++(*nfcn);
      i__1 = *n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          cont[i__] = f1[i__] + f2[i__];
        }

      switch (*ijob)
        {
          case 1:  goto L31;

          case 2:  goto L32;

          case 3:  goto L31;

          case 4:  goto L32;

          case 5:  goto L31;

          case 6:  goto L32;

          case 7:  goto L33;

          case 8:  goto L55;

          case 9:  goto L55;

          case 10:  goto L55;

          case 11:  goto L41;

          case 12:  goto L42;

          case 13:  goto L41;

          case 14:  goto L42;

          case 15:  goto L41;
        }

      /* ------ FULL MATRIX OPTION */
L31:
      sol_(n, lde1, &e1[e1_offset], &cont[1], &ip1[1]);
      goto L88;
      /* ------ FULL MATRIX OPTION, SECOND ORDER */
L41:
      i__1 = *m2;

      for (j = 1; j <= i__1; ++j)
        {
          sum1 = 0.;

          for (k = mm - 1; k >= 0; --k)
            {
              sum1 = (cont[j + k * *m2] + sum1) / *fac1;
              i__3 = *nm1;

              for (i__ = 1; i__ <= i__3; ++i__)
                {
                  im1 = i__ + *m1;
                  cont[im1] += fjac[i__ + (j + k * *m2) * fjac_dim1] * sum1;
                }
            }
        }

      sol_(nm1, lde1, &e1[e1_offset], &cont[*m1 + 1], &ip1[1]);

      for (i__ = *m1; i__ >= 1; --i__)
        {
          cont[i__] = (cont[i__] + cont[*m2 + i__]) / *fac1;
        }

      goto L88;
      /* ------ BANDED MATRIX OPTION */
L32:
      solb_(n, lde1, &e1[e1_offset], &linal_1.mle, &linal_1.mue, &cont[1], &
            ip1[1]);
      goto L88;
      /* ------ BANDED MATRIX OPTION, SECOND ORDER */
L42:
      i__1 = *m2;

      for (j = 1; j <= i__1; ++j)
        {
          sum1 = 0.;

          for (k = mm - 1; k >= 0; --k)
            {
              sum1 = (cont[j + k * *m2] + sum1) / *fac1;
              /* Computing MAX */
              i__3 = 1, i__4 = j - *mujac;
              /* Computing MIN */
              i__5 = *nm1, i__6 = j + *mljac;
              i__2 = min(i__5, i__6);

              for (i__ = max(i__3, i__4); i__ <= i__2; ++i__)
                {
                  im1 = i__ + *m1;
                  cont[im1] += fjac[i__ + *mujac + 1 - j + (j + k * *m2) *
                                    fjac_dim1] * sum1;
                }
            }
        }

      solb_(nm1, lde1, &e1[e1_offset], &linal_1.mle, &linal_1.mue, &cont[*
            m1 + 1], &ip1[1]);

      for (i__ = *m1; i__ >= 1; --i__)
        {
          cont[i__] = (cont[i__] + cont[*m2 + i__]) / *fac1;
        }

      goto L88;
      /* ------ HESSENBERG MATRIX OPTION */
L33:

      for (mm = *n - 2; mm >= 1; --mm)
        {
          mp = *n - mm;
          i__ = iphes[mp];

          if (i__ == mp)
            {
              goto L510;
            }

          zsafe = cont[mp];
          cont[mp] = cont[i__];
          cont[i__] = zsafe;
L510:
          i__1 = *n;

          for (i__ = mp + 1; i__ <= i__1; ++i__)
            {
              cont[i__] -= fjac[i__ + (mp - 1) * fjac_dim1] * cont[mp];
            }
        }

      solh_(n, lde1, &e1[e1_offset], &c__1, &cont[1], &ip1[1]);
      i__1 = *n - 2;

      for (mm = 1; mm <= i__1; ++mm)
        {
          mp = *n - mm;
          i__2 = *n;

          for (i__ = mp + 1; i__ <= i__2; ++i__)
            {
              cont[i__] += fjac[i__ + (mp - 1) * fjac_dim1] * cont[mp];
            }

          i__ = iphes[mp];

          if (i__ == mp)
            {
              goto L640;
            }

          zsafe = cont[mp];
          cont[mp] = cont[i__];
          cont[i__] = zsafe;
L640:
          ;
        }

      /* ----------------------------------- */
L88:
      *err = 0.;
      i__1 = *n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          /* Computing 2nd power */
          d__1 = cont[i__] / scal[i__];
          *err += d__1 * d__1;
        }

      /* Computing MAX */
      d__1 = sqrt(*err / *n);
      *err = max(d__1, 1e-10);
    }

  return 0;
  /* ----------------------------------------------------------- */
L55:
  return 0;
} /* estrad_ */

/*     END OF SUBROUTINE ESTRAD */

/* *********************************************************** */

/* Subroutine */ int estrav_(integer *n, doublereal *fjac, integer *ldjac,
                             integer *mljac, integer *mujac, doublereal *fmas, integer *ldmas,
                             integer *mlmas, integer *mumas, doublereal *h__, doublereal *dd, S_fp
                             fcn, integer *nfcn, doublereal *y0, doublereal *y, integer *ijob,
                             doublereal *x, integer *m1, integer *m2, integer *nm1, integer *ns,
                             integer *nns, doublereal *e1, integer *lde1, doublereal *zz,
                             doublereal *cont, doublereal *ff, integer *ip1, integer *iphes,
                             doublereal *scal, doublereal *err, logical *first, logical *reject,
                             doublereal *fac1, doublereal *rpar, integer *ipar)
{
  /* System generated locals */
  integer fjac_dim1, fjac_offset, fmas_dim1, fmas_offset, e1_dim1,
          e1_offset, i__1, i__2, i__3, i__4, i__5, i__6;
  doublereal d__1;

  /* Local variables */
  static integer i__, j, k, mm, mp, im1;
  extern /* Subroutine */ int sol_(integer *, integer *, doublereal *,
                                   doublereal *, integer *);
  static doublereal sum, sum1;
  extern /* Subroutine */ int solb_(integer *, integer *, doublereal *,
                                    integer *, integer *, doublereal *, integer *), solh_(integer *,
                                        integer *, doublereal *, integer *, doublereal *, integer *);
  static doublereal zsafe;

  /* Parameter adjustments */
  --scal;
  --iphes;
  --cont;
  --y;
  --y0;
  fjac_dim1 = *ldjac;
  fjac_offset = 1 + fjac_dim1;
  fjac -= fjac_offset;
  --ip1;
  fmas_dim1 = *ldmas;
  fmas_offset = 1 + fmas_dim1;
  fmas -= fmas_offset;
  --dd;
  --ff;
  --zz;
  e1_dim1 = *lde1;
  e1_offset = 1 + e1_dim1;
  e1 -= e1_offset;
  --rpar;
  --ipar;

  /* Function Body */
  switch (*ijob)
    {
      case 1:  goto L1;

      case 2:  goto L2;

      case 3:  goto L3;

      case 4:  goto L4;

      case 5:  goto L5;

      case 6:  goto L6;

      case 7:  goto L7;

      case 8:  goto L55;

      case 9:  goto L55;

      case 10:  goto L55;

      case 11:  goto L11;

      case 12:  goto L12;

      case 13:  goto L13;

      case 14:  goto L14;

      case 15:  goto L15;
    }

L1:
  /* ------  B=IDENTITY, JACOBIAN A FULL MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      i__2 = *ns;

      for (k = 1; k <= i__2; ++k)
        {
          sum += dd[k] * zz[i__ + (k - 1) * *n];
        }

      ff[i__ + *n] = sum / *h__;
      cont[i__] = ff[i__ + *n] + y0[i__];
    }

  sol_(n, lde1, &e1[e1_offset], &cont[1], &ip1[1]);
  goto L77;

L11:
  /* ------  B=IDENTITY, JACOBIAN A FULL MATRIX, SECOND ORDER */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      i__2 = *ns;

      for (k = 1; k <= i__2; ++k)
        {
          sum += dd[k] * zz[i__ + (k - 1) * *n];
        }

      ff[i__ + *n] = sum / *h__;
      cont[i__] = ff[i__ + *n] + y0[i__];
    }

L48:
  mm = *m1 / *m2;
  i__1 = *m2;

  for (j = 1; j <= i__1; ++j)
    {
      sum1 = 0.;

      for (k = mm - 1; k >= 0; --k)
        {
          sum1 = (cont[j + k * *m2] + sum1) / *fac1;
          i__2 = *nm1;

          for (i__ = 1; i__ <= i__2; ++i__)
            {
              im1 = i__ + *m1;
              cont[im1] += fjac[i__ + (j + k * *m2) * fjac_dim1] * sum1;
            }
        }
    }

  sol_(nm1, lde1, &e1[e1_offset], &cont[*m1 + 1], &ip1[1]);

  for (i__ = *m1; i__ >= 1; --i__)
    {
      cont[i__] = (cont[i__] + cont[*m2 + i__]) / *fac1;
    }

  goto L77;

L2:
  /* ------  B=IDENTITY, JACOBIAN A BANDED MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      i__2 = *ns;

      for (k = 1; k <= i__2; ++k)
        {
          sum += dd[k] * zz[i__ + (k - 1) * *n];
        }

      ff[i__ + *n] = sum / *h__;
      cont[i__] = ff[i__ + *n] + y0[i__];
    }

  solb_(n, lde1, &e1[e1_offset], &linal_1.mle, &linal_1.mue, &cont[1], &ip1[
          1]);
  goto L77;

L12:
  /* ------  B=IDENTITY, JACOBIAN A BANDED MATRIX, SECOND ORDER */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      i__2 = *ns;

      for (k = 1; k <= i__2; ++k)
        {
          sum += dd[k] * zz[i__ + (k - 1) * *n];
        }

      ff[i__ + *n] = sum / *h__;
      cont[i__] = ff[i__ + *n] + y0[i__];
    }

L45:
  mm = *m1 / *m2;
  i__1 = *m2;

  for (j = 1; j <= i__1; ++j)
    {
      sum1 = 0.;

      for (k = mm - 1; k >= 0; --k)
        {
          sum1 = (cont[j + k * *m2] + sum1) / *fac1;
          /* Computing MAX */
          i__2 = 1, i__3 = j - *mujac;
          /* Computing MIN */
          i__5 = *nm1, i__6 = j + *mljac;
          i__4 = min(i__5, i__6);

          for (i__ = max(i__2, i__3); i__ <= i__4; ++i__)
            {
              im1 = i__ + *m1;
              cont[im1] += fjac[i__ + *mujac + 1 - j + (j + k * *m2) *
                                fjac_dim1] * sum1;
            }
        }
    }

  solb_(nm1, lde1, &e1[e1_offset], &linal_1.mle, &linal_1.mue, &cont[*m1 +
        1], &ip1[1]);

  for (i__ = *m1; i__ >= 1; --i__)
    {
      cont[i__] = (cont[i__] + cont[*m2 + i__]) / *fac1;
    }

  goto L77;

L3:
  /* ------  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      i__4 = *ns;

      for (k = 1; k <= i__4; ++k)
        {
          sum += dd[k] * zz[i__ + (k - 1) * *n];
        }

      ff[i__] = sum / *h__;
    }

  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      /* Computing MAX */
      i__4 = 1, i__2 = i__ - *mlmas;
      /* Computing MIN */
      i__5 = *n, i__6 = i__ + *mumas;
      i__3 = min(i__5, i__6);

      for (j = max(i__4, i__2); j <= i__3; ++j)
        {
          sum += fmas[i__ - j + linal_1.mbdiag + j * fmas_dim1] * ff[j];
        }

      ff[i__ + *n] = sum;
      cont[i__] = sum + y0[i__];
    }

  sol_(n, lde1, &e1[e1_offset], &cont[1], &ip1[1]);
  goto L77;

L13:
  /* ------  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER */
  i__1 = *m1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      i__3 = *ns;

      for (k = 1; k <= i__3; ++k)
        {
          sum += dd[k] * zz[i__ + (k - 1) * *n];
        }

      ff[i__ + *n] = sum / *h__;
      cont[i__] = ff[i__ + *n] + y0[i__];
    }

  i__1 = *n;

  for (i__ = *m1 + 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      i__3 = *ns;

      for (k = 1; k <= i__3; ++k)
        {
          sum += dd[k] * zz[i__ + (k - 1) * *n];
        }

      ff[i__] = sum / *h__;
    }

  i__1 = *nm1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      /* Computing MAX */
      i__3 = 1, i__4 = i__ - *mlmas;
      /* Computing MIN */
      i__5 = *nm1, i__6 = i__ + *mumas;
      i__2 = min(i__5, i__6);

      for (j = max(i__3, i__4); j <= i__2; ++j)
        {
          sum += fmas[i__ - j + linal_1.mbdiag + j * fmas_dim1] * ff[j + *
                 m1];
        }

      im1 = i__ + *m1;
      ff[im1 + *n] = sum;
      cont[im1] = sum + y0[im1];
    }

  goto L48;

L4:
  /* ------  B IS A BANDED MATRIX, JACOBIAN A BANDED MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      i__2 = *ns;

      for (k = 1; k <= i__2; ++k)
        {
          sum += dd[k] * zz[i__ + (k - 1) * *n];
        }

      ff[i__] = sum / *h__;
    }

  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      /* Computing MAX */
      i__2 = 1, i__3 = i__ - *mlmas;
      /* Computing MIN */
      i__5 = *n, i__6 = i__ + *mumas;
      i__4 = min(i__5, i__6);

      for (j = max(i__2, i__3); j <= i__4; ++j)
        {
          sum += fmas[i__ - j + linal_1.mbdiag + j * fmas_dim1] * ff[j];
        }

      ff[i__ + *n] = sum;
      cont[i__] = sum + y0[i__];
    }

  solb_(n, lde1, &e1[e1_offset], &linal_1.mle, &linal_1.mue, &cont[1], &ip1[
          1]);
  goto L77;

L14:
  /* ------  B IS A BANDED MATRIX, JACOBIAN A BANDED MATRIX, SECOND ORDER */
  i__1 = *m1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      i__4 = *ns;

      for (k = 1; k <= i__4; ++k)
        {
          sum += dd[k] * zz[i__ + (k - 1) * *n];
        }

      ff[i__ + *n] = sum / *h__;
      cont[i__] = ff[i__ + *n] + y0[i__];
    }

  i__1 = *n;

  for (i__ = *m1 + 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      i__4 = *ns;

      for (k = 1; k <= i__4; ++k)
        {
          sum += dd[k] * zz[i__ + (k - 1) * *n];
        }

      ff[i__] = sum / *h__;
    }

  i__1 = *nm1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      /* Computing MAX */
      i__4 = 1, i__2 = i__ - *mlmas;
      /* Computing MIN */
      i__5 = *nm1, i__6 = i__ + *mumas;
      i__3 = min(i__5, i__6);

      for (j = max(i__4, i__2); j <= i__3; ++j)
        {
          sum += fmas[i__ - j + linal_1.mbdiag + j * fmas_dim1] * ff[j + *
                 m1];
        }

      im1 = i__ + *m1;
      ff[im1 + *n] = sum;
      cont[im1] = sum + y0[im1];
    }

  goto L45;

L5:
  /* ------  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      i__3 = *ns;

      for (k = 1; k <= i__3; ++k)
        {
          sum += dd[k] * zz[i__ + (k - 1) * *n];
        }

      ff[i__] = sum / *h__;
    }

  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      i__3 = *n;

      for (j = 1; j <= i__3; ++j)
        {
          sum += fmas[i__ + j * fmas_dim1] * ff[j];
        }

      ff[i__ + *n] = sum;
      cont[i__] = sum + y0[i__];
    }

  sol_(n, lde1, &e1[e1_offset], &cont[1], &ip1[1]);
  goto L77;

L15:
  /* ------  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER */
  i__1 = *m1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      i__3 = *ns;

      for (k = 1; k <= i__3; ++k)
        {
          sum += dd[k] * zz[i__ + (k - 1) * *n];
        }

      ff[i__ + *n] = sum / *h__;
      cont[i__] = ff[i__ + *n] + y0[i__];
    }

  i__1 = *n;

  for (i__ = *m1 + 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      i__3 = *ns;

      for (k = 1; k <= i__3; ++k)
        {
          sum += dd[k] * zz[i__ + (k - 1) * *n];
        }

      ff[i__] = sum / *h__;
    }

  i__1 = *nm1;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      i__3 = *nm1;

      for (j = 1; j <= i__3; ++j)
        {
          sum += fmas[i__ + j * fmas_dim1] * ff[j + *m1];
        }

      im1 = i__ + *m1;
      ff[im1 + *n] = sum;
      cont[im1] = sum + y0[im1];
    }

  goto L48;

L6:
  /* ------  B IS A FULL MATRIX, JACOBIAN A BANDED MATRIX */
  /* ------  THIS OPTION IS NOT PROVIDED */
  return 0;

L7:
  /* ------  B=IDENTITY, JACOBIAN A FULL MATRIX, HESSENBERG-OPTION */
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      sum = 0.;
      i__3 = *ns;

      for (k = 1; k <= i__3; ++k)
        {
          sum += dd[k] * zz[i__ + (k - 1) * *n];
        }

      ff[i__ + *n] = sum / *h__;
      cont[i__] = ff[i__ + *n] + y0[i__];
    }

  for (mm = *n - 2; mm >= 1; --mm)
    {
      mp = *n - mm;
      i__ = iphes[mp];

      if (i__ == mp)
        {
          goto L310;
        }

      zsafe = cont[mp];
      cont[mp] = cont[i__];
      cont[i__] = zsafe;
L310:
      i__1 = *n;

      for (i__ = mp + 1; i__ <= i__1; ++i__)
        {
          cont[i__] -= fjac[i__ + (mp - 1) * fjac_dim1] * cont[mp];
        }
    }

  solh_(n, lde1, &e1[e1_offset], &c__1, &cont[1], &ip1[1]);
  i__1 = *n - 2;

  for (mm = 1; mm <= i__1; ++mm)
    {
      mp = *n - mm;
      i__3 = *n;

      for (i__ = mp + 1; i__ <= i__3; ++i__)
        {
          cont[i__] += fjac[i__ + (mp - 1) * fjac_dim1] * cont[mp];
        }

      i__ = iphes[mp];

      if (i__ == mp)
        {
          goto L440;
        }

      zsafe = cont[mp];
      cont[mp] = cont[i__];
      cont[i__] = zsafe;
L440:
      ;
    }

  /* -------------------------------------- */

L77:
  *err = 0.;
  i__1 = *n;

  for (i__ = 1; i__ <= i__1; ++i__)
    {
      /* Computing 2nd power */
      d__1 = cont[i__] / scal[i__];
      *err += d__1 * d__1;
    }

  /* Computing MAX */
  d__1 = sqrt(*err / *n);
  *err = max(d__1, 1e-10);

  if (*err < 1.)
    {
      return 0;
    }

  if (*first || *reject)
    {
      i__1 = *n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          cont[i__] = y[i__] + cont[i__];
        }

      (*fcn)(n, x, &cont[1], &ff[1], &rpar[1], &ipar[1]);
      ++(*nfcn);
      i__1 = *n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          cont[i__] = ff[i__] + ff[i__ + *n];
        }

      switch (*ijob)
        {
          case 1:  goto L31;

          case 2:  goto L32;

          case 3:  goto L31;

          case 4:  goto L32;

          case 5:  goto L31;

          case 6:  goto L32;

          case 7:  goto L33;

          case 8:  goto L55;

          case 9:  goto L55;

          case 10:  goto L55;

          case 11:  goto L41;

          case 12:  goto L42;

          case 13:  goto L41;

          case 14:  goto L42;

          case 15:  goto L41;
        }

      /* ------ FULL MATRIX OPTION */
L31:
      sol_(n, lde1, &e1[e1_offset], &cont[1], &ip1[1]);
      goto L88;
      /* ------ FULL MATRIX OPTION, SECOND ORDER */
L41:
      i__1 = *m2;

      for (j = 1; j <= i__1; ++j)
        {
          sum1 = 0.;

          for (k = mm - 1; k >= 0; --k)
            {
              sum1 = (cont[j + k * *m2] + sum1) / *fac1;
              i__3 = *nm1;

              for (i__ = 1; i__ <= i__3; ++i__)
                {
                  im1 = i__ + *m1;
                  cont[im1] += fjac[i__ + (j + k * *m2) * fjac_dim1] * sum1;
                }
            }
        }

      sol_(nm1, lde1, &e1[e1_offset], &cont[*m1 + 1], &ip1[1]);

      for (i__ = *m1; i__ >= 1; --i__)
        {
          cont[i__] = (cont[i__] + cont[*m2 + i__]) / *fac1;
        }

      goto L88;
      /* ------ BANDED MATRIX OPTION */
L32:
      solb_(n, lde1, &e1[e1_offset], &linal_1.mle, &linal_1.mue, &cont[1], &
            ip1[1]);
      goto L88;
      /* ------ BANDED MATRIX OPTION, SECOND ORDER */
L42:
      i__1 = *m2;

      for (j = 1; j <= i__1; ++j)
        {
          sum1 = 0.;

          for (k = mm - 1; k >= 0; --k)
            {
              sum1 = (cont[j + k * *m2] + sum1) / *fac1;
              /* Computing MAX */
              i__3 = 1, i__4 = j - *mujac;
              /* Computing MIN */
              i__5 = *nm1, i__6 = j + *mljac;
              i__2 = min(i__5, i__6);

              for (i__ = max(i__3, i__4); i__ <= i__2; ++i__)
                {
                  im1 = i__ + *m1;
                  cont[im1] += fjac[i__ + *mujac + 1 - j + (j + k * *m2) *
                                    fjac_dim1] * sum1;
                }
            }
        }

      solb_(nm1, lde1, &e1[e1_offset], &linal_1.mle, &linal_1.mue, &cont[*
            m1 + 1], &ip1[1]);

      for (i__ = *m1; i__ >= 1; --i__)
        {
          cont[i__] = (cont[i__] + cont[*m2 + i__]) / *fac1;
        }

      goto L88;
      /* ------ HESSENBERG MATRIX OPTION */
L33:

      for (mm = *n - 2; mm >= 1; --mm)
        {
          mp = *n - mm;
          i__ = iphes[mp];

          if (i__ == mp)
            {
              goto L510;
            }

          zsafe = cont[mp];
          cont[mp] = cont[i__];
          cont[i__] = zsafe;
L510:
          i__1 = *n;

          for (i__ = mp + 1; i__ <= i__1; ++i__)
            {
              cont[i__] -= fjac[i__ + (mp - 1) * fjac_dim1] * cont[mp];
            }
        }

      solh_(n, lde1, &e1[e1_offset], &c__1, &cont[1], &ip1[1]);
      i__1 = *n - 2;

      for (mm = 1; mm <= i__1; ++mm)
        {
          mp = *n - mm;
          i__2 = *n;

          for (i__ = mp + 1; i__ <= i__2; ++i__)
            {
              cont[i__] += fjac[i__ + (mp - 1) * fjac_dim1] * cont[mp];
            }

          i__ = iphes[mp];

          if (i__ == mp)
            {
              goto L640;
            }

          zsafe = cont[mp];
          cont[mp] = cont[i__];
          cont[i__] = zsafe;
L640:
          ;
        }

      /* ----------------------------------- */
L88:
      *err = 0.;
      i__1 = *n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          /* Computing 2nd power */
          d__1 = cont[i__] / scal[i__];
          *err += d__1 * d__1;
        }

      /* Computing MAX */
      d__1 = sqrt(*err / *n);
      *err = max(d__1, 1e-10);
    }

  return 0;

  /* ----------------------------------------------------------- */

L55:
  return 0;
} /* estrav_ */

/*     END OF SUBROUTINE ESTRAV */

/* *********************************************************** */

/* Subroutine */ int slvrod_(integer *n, doublereal *fjac, integer *ldjac,
                             integer *mljac, integer *mujac, doublereal *fmas, integer *ldmas,
                             integer *mlmas, integer *mumas, integer *m1, integer *m2, integer *
                             nm1, doublereal *fac1, doublereal *e, integer *lde, integer *ip,
                             doublereal *dy, doublereal *ak, doublereal *fx, doublereal *ynew,
                             doublereal *hd, integer *ijob, logical *stage1)
{
  /* System generated locals */
  integer fjac_dim1, fjac_offset, fmas_dim1, fmas_offset, e_dim1, e_offset,
          i__1, i__2, i__3, i__4, i__5, i__6;

  /* Local variables */
  static integer i__, j, k, mm, im1, jkm;
  extern /* Subroutine */ int sol_(integer *, integer *, doublereal *,
                                   doublereal *, integer *);
  static doublereal sum;
  extern /* Subroutine */ int solb_(integer *, integer *, doublereal *,
                                    integer *, integer *, doublereal *, integer *);

  /* Parameter adjustments */
  --ynew;
  --fx;
  --ak;
  --dy;
  fjac_dim1 = *ldjac;
  fjac_offset = 1 + fjac_dim1;
  fjac -= fjac_offset;
  --ip;
  fmas_dim1 = *ldmas;
  fmas_offset = 1 + fmas_dim1;
  fmas -= fmas_offset;
  e_dim1 = *lde;
  e_offset = 1 + e_dim1;
  e -= e_offset;

  /* Function Body */
  if (*hd == 0.)
    {
      i__1 = *n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          ak[i__] = dy[i__];
        }
    }
  else
    {
      i__1 = *n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          ak[i__] = dy[i__] + *hd * fx[i__];
        }
    }

  switch (*ijob)
    {
      case 1:  goto L1;

      case 2:  goto L2;

      case 3:  goto L3;

      case 4:  goto L4;

      case 5:  goto L5;

      case 6:  goto L6;

      case 7:  goto L55;

      case 8:  goto L55;

      case 9:  goto L55;

      case 10:  goto L55;

      case 11:  goto L11;

      case 12:  goto L12;

      case 13:  goto L13;

      case 14:  goto L13;

      case 15:  goto L15;
    }

  /* ----------------------------------------------------------- */

L1:

  /* ---  B=IDENTITY, JACOBIAN A FULL MATRIX */
  if (*stage1)
    {
      i__1 = *n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          ak[i__] += ynew[i__];
        }
    }

  sol_(n, lde, &e[e_offset], &ak[1], &ip[1]);
  return 0;

  /* ----------------------------------------------------------- */

L11:

  /* ---  B=IDENTITY, JACOBIAN A FULL MATRIX, SECOND ORDER */
  if (*stage1)
    {
      i__1 = *n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          ak[i__] += ynew[i__];
        }
    }

L48:
  mm = *m1 / *m2;
  i__1 = *m2;

  for (j = 1; j <= i__1; ++j)
    {
      sum = 0.;

      for (k = mm - 1; k >= 0; --k)
        {
          jkm = j + k * *m2;
          sum = (ak[jkm] + sum) / *fac1;
          i__2 = *nm1;

          for (i__ = 1; i__ <= i__2; ++i__)
            {
              im1 = i__ + *m1;
              ak[im1] += fjac[i__ + jkm * fjac_dim1] * sum;
            }
        }
    }

  sol_(nm1, lde, &e[e_offset], &ak[*m1 + 1], &ip[1]);

  for (i__ = *m1; i__ >= 1; --i__)
    {
      ak[i__] = (ak[i__] + ak[*m2 + i__]) / *fac1;
    }

  return 0;

  /* ----------------------------------------------------------- */

L2:

  /* ---  B=IDENTITY, JACOBIAN A BANDED MATRIX */
  if (*stage1)
    {
      i__1 = *n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          ak[i__] += ynew[i__];
        }
    }

  solb_(n, lde, &e[e_offset], &linal_1.mle, &linal_1.mue, &ak[1], &ip[1]);
  return 0;

  /* ----------------------------------------------------------- */

L12:

  /* ---  B=IDENTITY, JACOBIAN A BANDED MATRIX, SECOND ORDER */
  if (*stage1)
    {
      i__1 = *n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          ak[i__] += ynew[i__];
        }
    }

L45:
  mm = *m1 / *m2;
  i__1 = *m2;

  for (j = 1; j <= i__1; ++j)
    {
      sum = 0.;

      for (k = mm - 1; k >= 0; --k)
        {
          jkm = j + k * *m2;
          sum = (ak[jkm] + sum) / *fac1;
          /* Computing MAX */
          i__2 = 1, i__3 = j - *mujac;
          /* Computing MIN */
          i__5 = *nm1, i__6 = j + *mljac;
          i__4 = min(i__5, i__6);

          for (i__ = max(i__2, i__3); i__ <= i__4; ++i__)
            {
              im1 = i__ + *m1;
              ak[im1] += fjac[i__ + *mujac + 1 - j + jkm * fjac_dim1] * sum;
            }
        }
    }

  solb_(nm1, lde, &e[e_offset], &linal_1.mle, &linal_1.mue, &ak[*m1 + 1], &
        ip[1]);

  for (i__ = *m1; i__ >= 1; --i__)
    {
      ak[i__] = (ak[i__] + ak[*m2 + i__]) / *fac1;
    }

  return 0;

  /* ----------------------------------------------------------- */

L3:

  /* ---  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX */
  if (*stage1)
    {
      i__1 = *n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          sum = 0.;
          /* Computing MAX */
          i__4 = 1, i__2 = i__ - *mlmas;
          /* Computing MIN */
          i__5 = *n, i__6 = i__ + *mumas;
          i__3 = min(i__5, i__6);

          for (j = max(i__4, i__2); j <= i__3; ++j)
            {
              sum += fmas[i__ - j + linal_1.mbdiag + j * fmas_dim1] * ynew[
                       j];
            }

          ak[i__] += sum;
        }
    }

  sol_(n, lde, &e[e_offset], &ak[1], &ip[1]);
  return 0;

  /* ----------------------------------------------------------- */

L13:

  /* ---  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER */
  if (*stage1)
    {
      i__1 = *m1;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          ak[i__] += ynew[i__];
        }

      i__1 = *nm1;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          sum = 0.;
          /* Computing MAX */
          i__3 = 1, i__4 = i__ - *mlmas;
          /* Computing MIN */
          i__5 = *nm1, i__6 = i__ + *mumas;
          i__2 = min(i__5, i__6);

          for (j = max(i__3, i__4); j <= i__2; ++j)
            {
              sum += fmas[i__ - j + linal_1.mbdiag + j * fmas_dim1] * ynew[
                       j + *m1];
            }

          im1 = i__ + *m1;
          ak[im1] += sum;
        }
    }

  if (*ijob == 14)
    {
      goto L45;
    }

  goto L48;

  /* ----------------------------------------------------------- */

L4:

  /* ---  B IS A BANDED MATRIX, JACOBIAN A BANDED MATRIX */
  if (*stage1)
    {
      i__1 = *n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          sum = 0.;
          /* Computing MAX */
          i__2 = 1, i__3 = i__ - *mlmas;
          /* Computing MIN */
          i__5 = *n, i__6 = i__ + *mumas;
          i__4 = min(i__5, i__6);

          for (j = max(i__2, i__3); j <= i__4; ++j)
            {
              sum += fmas[i__ - j + linal_1.mbdiag + j * fmas_dim1] * ynew[
                       j];
            }

          ak[i__] += sum;
        }
    }

  solb_(n, lde, &e[e_offset], &linal_1.mle, &linal_1.mue, &ak[1], &ip[1]);
  return 0;

  /* ----------------------------------------------------------- */

L5:

  /* ---  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX */
  if (*stage1)
    {
      i__1 = *n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          sum = 0.;
          i__4 = *n;

          for (j = 1; j <= i__4; ++j)
            {
              sum += fmas[i__ + j * fmas_dim1] * ynew[j];
            }

          ak[i__] += sum;
        }
    }

  sol_(n, lde, &e[e_offset], &ak[1], &ip[1]);
  return 0;

  /* ----------------------------------------------------------- */

L15:

  /* ---  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER */
  if (*stage1)
    {
      i__1 = *m1;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          ak[i__] += ynew[i__];
        }

      i__1 = *nm1;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          sum = 0.;
          i__4 = *nm1;

          for (j = 1; j <= i__4; ++j)
            {
              sum += fmas[i__ + j * fmas_dim1] * ynew[j + *m1];
            }

          im1 = i__ + *m1;
          ak[im1] += sum;
        }
    }

  goto L48;

  /* ----------------------------------------------------------- */

L6:

  /* ---  B IS A FULL MATRIX, JACOBIAN A BANDED MATRIX */
  /* ---  THIS OPTION IS NOT PROVIDED */
  if (*stage1)
    {
      i__1 = *n;

      for (i__ = 1; i__ <= i__1; ++i__)
        {
          sum = 0.;
          i__4 = *n;

          for (j = 1; j <= i__4; ++j)
            {
              /* L623: */
              sum += fmas[i__ + j * fmas_dim1] * ynew[j];
            }

          /* L624: */
          ak[i__] += sum;
        }

      solb_(n, lde, &e[e_offset], &linal_1.mle, &linal_1.mue, &ak[1], &ip[1]
           );
    }

  return 0;

  /* ----------------------------------------------------------- */

L55:
  return 0;
} /* slvrod_ */

/*     END OF SUBROUTINE SLVROD */

/* *********************************************************** */

/* Subroutine */ int slvseu_(integer *n, doublereal *fjac, integer *ldjac,
                             integer *mljac, integer *mujac, doublereal *fmas, integer *ldmas,
                             integer *mlmas, integer *mumas, integer *m1, integer *m2, integer *
                             nm1, doublereal *fac1, doublereal *e, integer *lde, integer *ip,
                             integer *iphes, doublereal *del, integer *ijob)
{
  /* System generated locals */
  integer fjac_dim1, fjac_offset, fmas_dim1, fmas_offset, e_dim1, e_offset,
          i__1, i__2, i__3, i__4, i__5, i__6;

  /* Local variables */
  static integer i__, j, k, mm, mp, im1, mp1, jkm, mmm;
  extern /* Subroutine */ int sol_(integer *, integer *, doublereal *,
                                   doublereal *, integer *);
  static doublereal sum;
  extern /* Subroutine */ int solb_(integer *, integer *, doublereal *,
                                    integer *, integer *, doublereal *, integer *), solh_(integer *,
                                        integer *, doublereal *, integer *, doublereal *, integer *);
  static doublereal zsafe;

  /* Parameter adjustments */
  --del;
  --iphes;
  fjac_dim1 = *ldjac;
  fjac_offset = 1 + fjac_dim1;
  fjac -= fjac_offset;
  --ip;
  fmas_dim1 = *ldmas;
  fmas_offset = 1 + fmas_dim1;
  fmas -= fmas_offset;
  e_dim1 = *lde;
  e_offset = 1 + e_dim1;
  e -= e_offset;

  /* Function Body */
  switch (*ijob)
    {
      case 1:  goto L1;

      case 2:  goto L2;

      case 3:  goto L1;

      case 4:  goto L2;

      case 5:  goto L1;

      case 6:  goto L55;

      case 7:  goto L7;

      case 8:  goto L55;

      case 9:  goto L55;

      case 10:  goto L55;

      case 11:  goto L11;

      case 12:  goto L12;

      case 13:  goto L11;

      case 14:  goto L12;

      case 15:  goto L11;
    }

  /* ----------------------------------------------------------- */

L1:
  /* ---  B=IDENTITY, JACOBIAN A FULL MATRIX */
  sol_(n, lde, &e[e_offset], &del[1], &ip[1]);
  return 0;

  /* ----------------------------------------------------------- */

L11:
  /* ---  B=IDENTITY, JACOBIAN A FULL MATRIX, SECOND ORDER */
  mm = *m1 / *m2;
  i__1 = *m2;

  for (j = 1; j <= i__1; ++j)
    {
      sum = 0.;

      for (k = mm - 1; k >= 0; --k)
        {
          jkm = j + k * *m2;
          sum = (del[jkm] + sum) / *fac1;
          i__2 = *nm1;

          for (i__ = 1; i__ <= i__2; ++i__)
            {
              im1 = i__ + *m1;
              del[im1] += fjac[i__ + jkm * fjac_dim1] * sum;
            }
        }
    }

  sol_(nm1, lde, &e[e_offset], &del[*m1 + 1], &ip[1]);

  for (i__ = *m1; i__ >= 1; --i__)
    {
      del[i__] = (del[i__] + del[*m2 + i__]) / *fac1;
    }

  return 0;

  /* ----------------------------------------------------------- */

L2:
  /* ---  B=IDENTITY, JACOBIAN A BANDED MATRIX */
  solb_(n, lde, &e[e_offset], &linal_1.mle, &linal_1.mue, &del[1], &ip[1]);
  return 0;

  /* ----------------------------------------------------------- */

L12:
  /* ---  B=IDENTITY, JACOBIAN A BANDED MATRIX, SECOND ORDER */
  mm = *m1 / *m2;
  i__1 = *m2;

  for (j = 1; j <= i__1; ++j)
    {
      sum = 0.;

      for (k = mm - 1; k >= 0; --k)
        {
          jkm = j + k * *m2;
          sum = (del[jkm] + sum) / *fac1;
          /* Computing MAX */
          i__2 = 1, i__3 = j - *mujac;
          /* Computing MIN */
          i__5 = *nm1, i__6 = j + *mljac;
          i__4 = min(i__5, i__6);

          for (i__ = max(i__2, i__3); i__ <= i__4; ++i__)
            {
              im1 = i__ + *m1;
              del[im1] += fjac[i__ + *mujac + 1 - j + jkm * fjac_dim1] *
                          sum;
            }
        }
    }

  solb_(nm1, lde, &e[e_offset], &linal_1.mle, &linal_1.mue, &del[*m1 + 1], &
        ip[1]);

  for (i__ = *m1; i__ >= 1; --i__)
    {
      del[i__] = (del[i__] + del[*m2 + i__]) / *fac1;
    }

  return 0;

  /* ----------------------------------------------------------- */

L7:

  /* ---  HESSENBERG OPTION */
  for (mmm = *n - 2; mmm >= 1; --mmm)
    {
      mp = *n - mmm;
      mp1 = mp - 1;
      i__ = iphes[mp];

      if (i__ == mp)
        {
          goto L110;
        }

      zsafe = del[mp];
      del[mp] = del[i__];
      del[i__] = zsafe;
L110:
      i__1 = *n;

      for (i__ = mp + 1; i__ <= i__1; ++i__)
        {
          del[i__] -= fjac[i__ + mp1 * fjac_dim1] * del[mp];
        }
    }

  solh_(n, lde, &e[e_offset], &c__1, &del[1], &ip[1]);
  i__1 = *n - 2;

  for (mmm = 1; mmm <= i__1; ++mmm)
    {
      mp = *n - mmm;
      mp1 = mp - 1;
      i__4 = *n;

      for (i__ = mp + 1; i__ <= i__4; ++i__)
        {
          del[i__] += fjac[i__ + mp1 * fjac_dim1] * del[mp];
        }

      i__ = iphes[mp];

      if (i__ == mp)
        {
          goto L240;
        }

      zsafe = del[mp];
      del[mp] = del[i__];
      del[i__] = zsafe;
L240:
      ;
    }

  return 0;

  /* ----------------------------------------------------------- */

L55:
  return 0;
} /* slvseu_ */
