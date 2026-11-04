// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// fingerprint 51b57d0ecdefa9751f678984a0863a96
#include "copasi/odepack++/_dc_decsol.h"

static const integer c__1 = 1;

//C ******************************************
//C     VERSION OF SEPTEMBER 18, 1995
//C ******************************************
//C
void _dc_decsol::decomr(common & cmn,
                        const integer & n,
                        CFortranAccess< CMatrix< doublereal > > & fjac,
                        const integer & ldjac,
                        const CFortranAccess< CMatrix< doublereal > > & fmas,
                        const integer & ldmas,
                        const integer & mlmas,
                        const integer & mumas,
                        const integer & m1,
                        const integer & m2,
                        const integer & nm1,
                        const doublereal & fac1,
                        CFortranAccess< CMatrix< doublereal > > & e1,
                        const integer & lde1,
                        CVectorCore< integer > & ip1,
                        integer & ier,
                        const integer & ijob,
                        bool & calhes,
                        CVectorCore< integer > & iphes)
{
  integer & mle = cmn.mle;
  integer & mue = cmn.mue;
  integer & mbjac = cmn.mbjac;
  integer & mbb = cmn.mbb;
  integer & mdiag = cmn.mdiag;
  integer & mdiff = cmn.mdiff;
  integer & mbdiag = cmn.mbdiag;
  //
  integer j = 0;
  integer i = 0;
  integer jm1 = 0;
  integer mm = 0;
  doublereal sum = 0.0;
  integer k = 0;
  integer ib = 0;
  integer j1 = 0;
  //C
  switch (ijob)
    {
    case 1:
      goto statement_1;
    case 2:
      goto statement_2;
    case 3:
      goto statement_3;
    case 4:
      goto statement_4;
    case 5:
      goto statement_5;
    case 6:
      goto statement_6;
    case 7:
      goto statement_7;
    case 8:
      goto statement_55;
    case 9:
      goto statement_55;
    case 10:
      goto statement_55;
    case 11:
      goto statement_11;
    case 12:
      goto statement_12;
    case 13:
      goto statement_13;
    case 14:
      goto statement_14;
    case 15:
      goto statement_15;
    default:
      break;
    }
//C
//C -----------------------------------------------------------
//C
statement_1:
  //C ---  B=IDENTITY, JACOBIAN A FULL MATRIX
  // FEM_DO_SAFE(j, 1, n)
  for (integer j = 1; j <= n; ++j)
    {
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          e1(i, j) = -fjac(i, j);
        }
      e1(j, j) += fac1;
    }
  decsol::dec(n, lde1, e1, ip1, ier);
  return;
//C
//C -----------------------------------------------------------
//C
statement_11:
  //C ---  B=IDENTITY, JACOBIAN A FULL MATRIX, SECOND ORDER
  // FEM_DO_SAFE(j, 1, nm1)
  for (integer j = 1; j <= nm1; ++j)
    {
      jm1 = j + m1;
      // FEM_DO_SAFE(i, 1, nm1)
      for (integer i = 1; i <= nm1; ++i)
        {
          e1(i, j) = -fjac(i, jm1);
        }
      e1(j, j) += fac1;
    }
statement_45:
  mm = m1 / m2;
  // FEM_DO_SAFE(j, 1, m2)
  for (integer j = 1; j <= m2; ++j)
    {
      // FEM_DO_SAFE(i, 1, nm1)
      for (integer i = 1; i <= nm1; ++i)
        {
          sum = 0.e0;
          // FEM_DO_SAFE(k, 0, mm - 1)
          for (integer k = 0; k <= mm - 1; ++k)
            {
              sum = (sum + fjac(i, j + k * m2)) / fac1;
            }
          e1(i, j) = e1(i, j) - sum;
        }
    }
  decsol::dec(nm1, lde1, e1, ip1, ier);
  return;
//C
//C -----------------------------------------------------------
//C
statement_2:
  //C ---  B=IDENTITY, JACOBIAN A BANDED MATRIX
  // FEM_DO_SAFE(j, 1, n)
  for (integer j = 1; j <= n; ++j)
    {
      // FEM_DO_SAFE(i, 1, mbjac)
      for (integer i = 1; i <= mbjac; ++i)
        {
          e1(i + mle, j) = -fjac(i, j);
        }
      e1(mdiag, j) += fac1;
    }
  decsol::decb(n, lde1, e1, mle, mue, ip1, ier);
  return;
//C
//C -----------------------------------------------------------
//C
statement_12:
  //C ---  B=IDENTITY, JACOBIAN A BANDED MATRIX, SECOND ORDER
  // FEM_DO_SAFE(j, 1, nm1)
  for (integer j = 1; j <= nm1; ++j)
    {
      jm1 = j + m1;
      // FEM_DO_SAFE(i, 1, mbjac)
      for (integer i = 1; i <= mbjac; ++i)
        {
          e1(i + mle, j) = -fjac(i, jm1);
        }
      e1(mdiag, j) += fac1;
    }
statement_46:
  mm = m1 / m2;
  // FEM_DO_SAFE(j, 1, m2)
  for (integer j = 1; j <= m2; ++j)
    {
      // FEM_DO_SAFE(i, 1, mbjac)
      for (integer i = 1; i <= mbjac; ++i)
        {
          sum = 0.e0;
          // FEM_DO_SAFE(k, 0, mm - 1)
          for (integer k = 0; k <= mm - 1; ++k)
            {
              sum = (sum + fjac(i, j + k * m2)) / fac1;
            }
          e1(i + mle, j) = e1(i + mle, j) - sum;
        }
    }
  decsol::decb(nm1, lde1, e1, mle, mue, ip1, ier);
  return;
//C
//C -----------------------------------------------------------
//C
statement_3:
  //C ---  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX
  // FEM_DO_SAFE(j, 1, n)
  for (integer j = 1; j <= n; ++j)
    {
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          e1(i, j) = -fjac(i, j);
        }
      // FEM_DO_SAFE(i, std::max(c__1, j - mumas), std::min(n, j + mlmas))
      for (integer i = std::max(c__1, j - mumas); i <= std::min(n, j + mlmas); ++i)
        {
          e1(i, j) += fac1 * fmas(i - j + mbdiag, j);
        }
    }
  decsol::dec(n, lde1, e1, ip1, ier);
  return;
//C
//C -----------------------------------------------------------
//C
statement_13:
  //C ---  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER
  // FEM_DO_SAFE(j, 1, nm1)
  for (integer j = 1; j <= nm1; ++j)
    {
      jm1 = j + m1;
      // FEM_DO_SAFE(i, 1, nm1)
      for (integer i = 1; i <= nm1; ++i)
        {
          e1(i, j) = -fjac(i, jm1);
        }
      // FEM_DO_SAFE(i, std::max(c__1, j - mumas), std::min(nm1, j + mlmas))
      for (integer i = std::max(c__1, j - mumas); i <= std::min(nm1, j + mlmas); ++i)
        {
          e1(i, j) += fac1 * fmas(i - j + mbdiag, j);
        }
    }
  goto statement_45;
//C
//C -----------------------------------------------------------
//C
statement_4:
  //C ---  B IS A BANDED MATRIX, JACOBIAN A BANDED MATRIX
  // FEM_DO_SAFE(j, 1, n)
  for (integer j = 1; j <= n; ++j)
    {
      // FEM_DO_SAFE(i, 1, mbjac)
      for (integer i = 1; i <= mbjac; ++i)
        {
          e1(i + mle, j) = -fjac(i, j);
        }
      // FEM_DO_SAFE(i, 1, mbb)
      for (integer i = 1; i <= mbb; ++i)
        {
          ib = i + mdiff;
          e1(ib, j) += fac1 * fmas(i, j);
        }
    }
  decsol::decb(n, lde1, e1, mle, mue, ip1, ier);
  return;
//C
//C -----------------------------------------------------------
//C
statement_14:
  //C ---  B IS A BANDED MATRIX, JACOBIAN A BANDED MATRIX, SECOND ORDER
  // FEM_DO_SAFE(j, 1, nm1)
  for (integer j = 1; j <= nm1; ++j)
    {
      jm1 = j + m1;
      // FEM_DO_SAFE(i, 1, mbjac)
      for (integer i = 1; i <= mbjac; ++i)
        {
          e1(i + mle, j) = -fjac(i, jm1);
        }
      // FEM_DO_SAFE(i, 1, mbb)
      for (integer i = 1; i <= mbb; ++i)
        {
          ib = i + mdiff;
          e1(ib, j) += fac1 * fmas(i, j);
        }
    }
  goto statement_46;
//C
//C -----------------------------------------------------------
//C
statement_5:
  //C ---  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX
  // FEM_DO_SAFE(j, 1, n)
  for (integer j = 1; j <= n; ++j)
    {
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          e1(i, j) = fmas(i, j) * fac1 - fjac(i, j);
        }
    }
  decsol::dec(n, lde1, e1, ip1, ier);
  return;
//C
//C -----------------------------------------------------------
//C
statement_15:
  //C ---  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER
  // FEM_DO_SAFE(j, 1, nm1)
  for (integer j = 1; j <= nm1; ++j)
    {
      jm1 = j + m1;
      // FEM_DO_SAFE(i, 1, nm1)
      for (integer i = 1; i <= nm1; ++i)
        {
          e1(i, j) = fmas(i, j) * fac1 - fjac(i, jm1);
        }
    }
  goto statement_45;
//C
//C -----------------------------------------------------------
//C
statement_6:
  //C ---  B IS A FULL MATRIX, JACOBIAN A BANDED MATRIX
  //C ---  THIS OPTION IS NOT PROVIDED
  return;
//C
//C -----------------------------------------------------------
//C
statement_7:
  //C ---  B=IDENTITY, JACOBIAN A FULL MATRIX, HESSENBERG-OPTION
  if (calhes)
    {
      decsol::elmhes(ldjac, n, 1, n, fjac, iphes);
    }
  calhes = false;
  // FEM_DO_SAFE(j, 1, n - 1)
  for (integer j = 1; j <= n - 1; ++j)
    {
      j1 = j + 1;
      e1(j1, j) = -fjac(j1, j);
    }
  // FEM_DO_SAFE(j, 1, n)
  for (integer j = 1; j <= n; ++j)
    {
      // FEM_DO_SAFE(i, 1, j)
      for (integer i = 1; i <= j; ++i)
        {
          e1(i, j) = -fjac(i, j);
        }
      e1(j, j) += fac1;
    }
  decsol::dech(n, lde1, e1, 1, ip1, ier);
  return;
//C
//C -----------------------------------------------------------
//C
statement_55:;
}

//C
//C     END OF SUBROUTINE DECOMR
//C
//C ***********************************************************
//C
void _dc_decsol::decomc(common & cmn,
                        const integer & n,
                        const CFortranAccess< CMatrix< doublereal > > & fjac,
                        const integer & ldjac,
                        const CFortranAccess< CMatrix< doublereal > > & fmas,
                        const integer & ldmas,
                        const integer & mlmas,
                        const integer & mumas,
                        const integer & m1,
                        const integer & m2,
                        const integer & nm1,
                        const doublereal & alphn,
                        const doublereal & betan,
                        CFortranAccess< CMatrix< doublereal > > & e2r,
                        CFortranAccess< CMatrix< doublereal > > & e2i,
                        const integer & lde1,
                        CVectorCore< integer > & ip2,
                        integer & ier,
                        const integer & ijob)
{
  integer & mle = cmn.mle;
  integer & mue = cmn.mue;
  integer & mbjac = cmn.mbjac;
  integer & mbb = cmn.mbb;
  integer & mdiag = cmn.mdiag;
  integer & mdiff = cmn.mdiff;
  integer & mbdiag = cmn.mbdiag;
  //
  integer j = 0;
  integer i = 0;
  integer jm1 = 0;
  integer mm = 0;
  doublereal abno = 0.0;
  doublereal alp = 0.0;
  doublereal bet = 0.0;
  doublereal sumr = 0.0;
  doublereal sumi = 0.0;
  integer k = 0;
  doublereal sums = 0.0;
  integer imle = 0;
  doublereal bb = 0.0;
  doublereal ffma = 0.0;
  integer ib = 0;
  integer j1 = 0;
  //C
  switch (ijob)
    {
    case 1:
      goto statement_1;
    case 2:
      goto statement_2;
    case 3:
      goto statement_3;
    case 4:
      goto statement_4;
    case 5:
      goto statement_5;
    case 6:
      goto statement_6;
    case 7:
      goto statement_7;
    case 8:
      goto statement_55;
    case 9:
      goto statement_55;
    case 10:
      goto statement_55;
    case 11:
      goto statement_11;
    case 12:
      goto statement_12;
    case 13:
      goto statement_13;
    case 14:
      goto statement_14;
    case 15:
      goto statement_15;
    default:
      break;
    }
//C
//C -----------------------------------------------------------
//C
statement_1:
  //C ---  B=IDENTITY, JACOBIAN A FULL MATRIX
  // FEM_DO_SAFE(j, 1, n)
  for (integer j = 1; j <= n; ++j)
    {
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          e2r(i, j) = -fjac(i, j);
          e2i(i, j) = 0.e0;
        }
      e2r(j, j) += alphn;
      e2i(j, j) = betan;
    }
  decsol::decc(n, lde1, e2r, e2i, ip2, ier);
  return;
//C
//C -----------------------------------------------------------
//C
statement_11:
  //C ---  B=IDENTITY, JACOBIAN A FULL MATRIX, SECOND ORDER
  // FEM_DO_SAFE(j, 1, nm1)
  for (integer j = 1; j <= nm1; ++j)
    {
      jm1 = j + m1;
      // FEM_DO_SAFE(i, 1, nm1)
      for (integer i = 1; i <= nm1; ++i)
        {
          e2r(i, j) = -fjac(i, jm1);
          e2i(i, j) = 0.e0;
        }
      e2r(j, j) += alphn;
      e2i(j, j) = betan;
    }
statement_45:
  mm = m1 / m2;
  abno = pow2(alphn) + pow2(betan);
  alp = alphn / abno;
  bet = betan / abno;
  // FEM_DO_SAFE(j, 1, m2)
  for (integer j = 1; j <= m2; ++j)
    {
      // FEM_DO_SAFE(i, 1, nm1)
      for (integer i = 1; i <= nm1; ++i)
        {
          sumr = 0.e0;
          sumi = 0.e0;
          // FEM_DO_SAFE(k, 0, mm - 1)
          for (integer k = 0; k <= mm - 1; ++k)
            {
              sums = sumr + fjac(i, j + k * m2);
              sumr = sums * alp + sumi * bet;
              sumi = sumi * alp - sums * bet;
            }
          e2r(i, j) = e2r(i, j) - sumr;
          e2i(i, j) = e2i(i, j) - sumi;
        }
    }
  decsol::decc(nm1, lde1, e2r, e2i, ip2, ier);
  return;
//C
//C -----------------------------------------------------------
//C
statement_2:
  //C ---  B=IDENTITY, JACOBIAN A BANDED MATRIX
  // FEM_DO_SAFE(j, 1, n)
  for (integer j = 1; j <= n; ++j)
    {
      // FEM_DO_SAFE(i, 1, mbjac)
      for (integer i = 1; i <= mbjac; ++i)
        {
          imle = i + mle;
          e2r(imle, j) = -fjac(i, j);
          e2i(imle, j) = 0.e0;
        }
      e2r(mdiag, j) += alphn;
      e2i(mdiag, j) = betan;
    }
  decsol::decbc(n, lde1, e2r, e2i, mle, mue, ip2, ier);
  return;
//C
//C -----------------------------------------------------------
//C
statement_12:
  //C ---  B=IDENTITY, JACOBIAN A BANDED MATRIX, SECOND ORDER
  // FEM_DO_SAFE(j, 1, nm1)
  for (integer j = 1; j <= nm1; ++j)
    {
      jm1 = j + m1;
      // FEM_DO_SAFE(i, 1, mbjac)
      for (integer i = 1; i <= mbjac; ++i)
        {
          e2r(i + mle, j) = -fjac(i, jm1);
          e2i(i + mle, j) = 0.e0;
        }
      e2r(mdiag, j) += alphn;
      e2i(mdiag, j) += betan;
    }
statement_46:
  mm = m1 / m2;
  abno = pow2(alphn) + pow2(betan);
  alp = alphn / abno;
  bet = betan / abno;
  // FEM_DO_SAFE(j, 1, m2)
  for (integer j = 1; j <= m2; ++j)
    {
      // FEM_DO_SAFE(i, 1, mbjac)
      for (integer i = 1; i <= mbjac; ++i)
        {
          sumr = 0.e0;
          sumi = 0.e0;
          // FEM_DO_SAFE(k, 0, mm - 1)
          for (integer k = 0; k <= mm - 1; ++k)
            {
              sums = sumr + fjac(i, j + k * m2);
              sumr = sums * alp + sumi * bet;
              sumi = sumi * alp - sums * bet;
            }
          imle = i + mle;
          e2r(imle, j) = e2r(imle, j) - sumr;
          e2i(imle, j) = e2i(imle, j) - sumi;
        }
    }
  decsol::decbc(nm1, lde1, e2r, e2i, mle, mue, ip2, ier);
  return;
//C
//C -----------------------------------------------------------
//C
statement_3:
  //C ---  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX
  // FEM_DO_SAFE(j, 1, n)
  for (integer j = 1; j <= n; ++j)
    {
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          e2r(i, j) = -fjac(i, j);
          e2i(i, j) = 0.e0;
        }
    }
  // FEM_DO_SAFE(j, 1, n)
  for (integer j = 1; j <= n; ++j)
    {
      // FEM_DO_SAFE(i, std::max(c__1, j - mumas), std::min(n, j + mlmas))
      for (integer i = std::max(c__1, j - mumas); i <= std::min(n, j + mlmas); ++i)
        {
          bb = fmas(i - j + mbdiag, j);
          e2r(i, j) += alphn * bb;
          e2i(i, j) = betan * bb;
        }
    }
  decsol::decc(n, lde1, e2r, e2i, ip2, ier);
  return;
//C
//C -----------------------------------------------------------
//C
statement_13:
  //C ---  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER
  // FEM_DO_SAFE(j, 1, nm1)
  for (integer j = 1; j <= nm1; ++j)
    {
      jm1 = j + m1;
      // FEM_DO_SAFE(i, 1, nm1)
      for (integer i = 1; i <= nm1; ++i)
        {
          e2r(i, j) = -fjac(i, jm1);
          e2i(i, j) = 0.e0;
        }
      // FEM_DO_SAFE(i, std::max(c__1, j - mumas), std::min(nm1, j + mlmas))
      for (integer i = std::max(c__1, j - mumas); i <= std::min(nm1, j + mlmas); ++i)
        {
          ffma = fmas(i - j + mbdiag, j);
          e2r(i, j) += alphn * ffma;
          e2i(i, j) += betan * ffma;
        }
    }
  goto statement_45;
//C
//C -----------------------------------------------------------
//C
statement_4:
  //C ---  B IS A BANDED MATRIX, JACOBIAN A BANDED MATRIX
  // FEM_DO_SAFE(j, 1, n)
  for (integer j = 1; j <= n; ++j)
    {
      // FEM_DO_SAFE(i, 1, mbjac)
      for (integer i = 1; i <= mbjac; ++i)
        {
          imle = i + mle;
          e2r(imle, j) = -fjac(i, j);
          e2i(imle, j) = 0.e0;
        }
      // FEM_DO_SAFE(i, std::max(c__1, mumas + 2 - j), std::min(mbb, mumas + 1 - j + n))
      for (integer i = std::max(c__1, mumas + 2 - j); i <= std::min(mbb, mumas + 1 - j + n); ++i)
        {
          ib = i + mdiff;
          bb = fmas(i, j);
          e2r(ib, j) += alphn * bb;
          e2i(ib, j) = betan * bb;
        }
    }
  decsol::decbc(n, lde1, e2r, e2i, mle, mue, ip2, ier);
  return;
//C
//C -----------------------------------------------------------
//C
statement_14:
  //C ---  B IS A BANDED MATRIX, JACOBIAN A BANDED MATRIX, SECOND ORDER
  // FEM_DO_SAFE(j, 1, nm1)
  for (integer j = 1; j <= nm1; ++j)
    {
      jm1 = j + m1;
      // FEM_DO_SAFE(i, 1, mbjac)
      for (integer i = 1; i <= mbjac; ++i)
        {
          e2r(i + mle, j) = -fjac(i, jm1);
          e2i(i + mle, j) = 0.e0;
        }
      // FEM_DO_SAFE(i, 1, mbb)
      for (integer i = 1; i <= mbb; ++i)
        {
          ib = i + mdiff;
          ffma = fmas(i, j);
          e2r(ib, j) += alphn * ffma;
          e2i(ib, j) += betan * ffma;
        }
    }
  goto statement_46;
//C
//C -----------------------------------------------------------
//C
statement_5:
  //C ---  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX
  // FEM_DO_SAFE(j, 1, n)
  for (integer j = 1; j <= n; ++j)
    {
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          bb = fmas(i, j);
          e2r(i, j) = bb * alphn - fjac(i, j);
          e2i(i, j) = bb * betan;
        }
    }
  decsol::decc(n, lde1, e2r, e2i, ip2, ier);
  return;
//C
//C -----------------------------------------------------------
//C
statement_15:
  //C ---  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER
  // FEM_DO_SAFE(j, 1, nm1)
  for (integer j = 1; j <= nm1; ++j)
    {
      jm1 = j + m1;
      // FEM_DO_SAFE(i, 1, nm1)
      for (integer i = 1; i <= nm1; ++i)
        {
          e2r(i, j) = alphn * fmas(i, j) - fjac(i, jm1);
          e2i(i, j) = betan * fmas(i, j);
        }
    }
  goto statement_45;
//C
//C -----------------------------------------------------------
//C
statement_6:
  //C ---  B IS A FULL MATRIX, JACOBIAN A BANDED MATRIX
  //C ---  THIS OPTION IS NOT PROVIDED
  return;
//C
//C -----------------------------------------------------------
//C
statement_7:
  //C ---  B=IDENTITY, JACOBIAN A FULL MATRIX, HESSENBERG-OPTION
  // FEM_DO_SAFE(j, 1, n - 1)
  for (integer j = 1; j <= n - 1; ++j)
    {
      j1 = j + 1;
      e2r(j1, j) = -fjac(j1, j);
      e2i(j1, j) = 0.e0;
    }
  // FEM_DO_SAFE(j, 1, n)
  for (integer j = 1; j <= n; ++j)
    {
      // FEM_DO_SAFE(i, 1, j)
      for (integer i = 1; i <= j; ++i)
        {
          e2i(i, j) = 0.e0;
          e2r(i, j) = -fjac(i, j);
        }
      e2r(j, j) += alphn;
      e2i(j, j) = betan;
    }
  decsol::dechc(n, lde1, e2r, e2i, 1, ip2, ier);
  return;
//C
//C -----------------------------------------------------------
//C
statement_55:;
}

//C
//C     END OF SUBROUTINE DECOMC
//C
//C ***********************************************************
//C
void _dc_decsol::slvrar(common & cmn,
                        const integer & n,
                        const CFortranAccess< CMatrix< doublereal > > & fjac,
                        const integer & ldjac,
                        const integer & mljac,
                        const integer & mujac,
                        const CFortranAccess< CMatrix< doublereal > > & fmas,
                        const integer & ldmas,
                        const integer & mlmas,
                        const integer & mumas,
                        const integer & m1,
                        const integer & m2,
                        const integer & nm1,
                        const doublereal & fac1,
                        const CFortranAccess< CMatrix< doublereal > > & e1,
                        const integer & lde1,
                        CVectorCore< doublereal > & z1,
                        const CVectorCore< doublereal > & f1,
                        const CVectorCore< integer > & ip1,
                        const CVectorCore< integer > & iphes,
                        const integer & /* ier */,
                        const integer & ijob)
{
  integer & mle = cmn.mle;
  integer & mue = cmn.mue;
  integer & mbdiag = cmn.mbdiag;
  //
  integer i = 0;
  integer mm = 0;
  integer j = 0;
  doublereal sum1 = 0.0;
  integer k = 0;
  integer jkm = 0;
  integer im1 = 0;
  doublereal s1 = 0.0;
  integer mp = 0;
  integer mp1 = 0;
  doublereal zsafe = 0.0;
  //C
  switch (ijob)
    {
    case 1:
      goto statement_1;
    case 2:
      goto statement_2;
    case 3:
      goto statement_3;
    case 4:
      goto statement_4;
    case 5:
      goto statement_5;
    case 6:
      goto statement_6;
    case 7:
      goto statement_7;
    case 8:
      goto statement_55;
    case 9:
      goto statement_55;
    case 10:
      goto statement_55;
    case 11:
      goto statement_11;
    case 12:
      goto statement_12;
    case 13:
      goto statement_13;
    case 14:
      goto statement_13;
    case 15:
      goto statement_15;
    default:
      break;
    }
//C
//C -----------------------------------------------------------
//C
statement_1:
  //C ---  B=IDENTITY, JACOBIAN A FULL MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      z1(i) = z1(i) - f1(i) * fac1;
    }
  decsol::sol(n, lde1, e1, z1, ip1);
  return;
//C
//C -----------------------------------------------------------
//C
statement_11:
  //C ---  B=IDENTITY, JACOBIAN A FULL MATRIX, SECOND ORDER
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      z1(i) = z1(i) - f1(i) * fac1;
    }
statement_48:
  mm = m1 / m2;
  // FEM_DO_SAFE(j, 1, m2)
  for (integer j = 1; j <= m2; ++j)
    {
      sum1 = 0.e0;
      // FEM_DOSTEP(k, mm - 1, 0, -1)
      for (integer k = mm - 1; k >= 0; --k)
        {
          jkm = j + k * m2;
          sum1 = (z1(jkm) + sum1) / fac1;
          // FEM_DO_SAFE(i, 1, nm1)
          for (integer i = 1; i <= nm1; ++i)
            {
              im1 = i + m1;
              z1(im1) += fjac(i, jkm) * sum1;
            }
        }
    }
  decsol::sol(nm1, lde1, e1, z1(m1 + 1), ip1);
statement_49:
  // FEM_DOSTEP(i, m1, 1, -1)
  for (integer i = m1; i >= 1; --i)
    {
      z1(i) = (z1(i) + z1(m2 + i)) / fac1;
    }
  return;
//C
//C -----------------------------------------------------------
//C
statement_2:
  //C ---  B=IDENTITY, JACOBIAN A BANDED MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      z1(i) = z1(i) - f1(i) * fac1;
    }
  decsol::solb(n, lde1, e1, mle, mue, z1, ip1);
  return;
//C
//C -----------------------------------------------------------
//C
statement_12:
  //C ---  B=IDENTITY, JACOBIAN A BANDED MATRIX, SECOND ORDER
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      z1(i) = z1(i) - f1(i) * fac1;
    }
statement_45:
  mm = m1 / m2;
  // FEM_DO_SAFE(j, 1, m2)
  for (integer j = 1; j <= m2; ++j)
    {
      sum1 = 0.e0;
      // FEM_DOSTEP(k, mm - 1, 0, -1)
      for (integer k = mm - 1; k >= 0; --k)
        {
          jkm = j + k * m2;
          sum1 = (z1(jkm) + sum1) / fac1;
          // FEM_DO_SAFE(i, std::max(c__1, j - mujac), std::min(nm1, j + mljac))
          for (integer i = std::max(c__1, j - mujac); i <= std::min(nm1, j + mljac); ++i)
            {
              im1 = i + m1;
              z1(im1) += fjac(i + mujac + 1 - j, jkm) * sum1;
            }
        }
    }
  decsol::solb(nm1, lde1, e1, mle, mue, z1(m1 + 1), ip1);
  goto statement_49;
//C
//C -----------------------------------------------------------
//C
statement_3:
  //C ---  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      s1 = 0.0e0;
      // FEM_DO_SAFE(j, std::max(c__1, i - mlmas), std::min(n, i + mumas))
      for (integer j = std::max(c__1, i - mlmas); j <= std::min(n, i + mumas); ++j)

        {
          s1 = s1 - fmas(i - j + mbdiag, j) * f1(j);
        }
      z1(i) += s1 * fac1;
    }
  decsol::sol(n, lde1, e1, z1, ip1);
  return;
//C
//C -----------------------------------------------------------
//C
statement_13:
  //C ---  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER
  // FEM_DO_SAFE(i, 1, m1)
  for (integer i = 1; i <= m1; ++i)
    {
      z1(i) = z1(i) - f1(i) * fac1;
    }
  // FEM_DO_SAFE(i, 1, nm1)
  for (integer i = 1; i <= nm1; ++i)
    {
      im1 = i + m1;
      s1 = 0.0e0;
      // FEM_DO_SAFE(j, std::max(c__1, i - mlmas), std::min(nm1, i + mumas))
      for (integer j = std::max(c__1, i - mlmas); j <= std::min(nm1, i + mumas); ++j)
        {
          s1 = s1 - fmas(i - j + mbdiag, j) * f1(j + m1);
        }
      z1(im1) += s1 * fac1;
    }
  if (ijob == 14)
    {
      goto statement_45;
    }
  goto statement_48;
//C
//C -----------------------------------------------------------
//C
statement_4:
  //C ---  B IS A BANDED MATRIX, JACOBIAN A BANDED MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      s1 = 0.0e0;
      // FEM_DO_SAFE(j, std::max(c__1, i - mlmas), std::min(n, i + mumas))
      for (integer j = std::max(c__1, i - mlmas); j <= std::min(n, i + mumas); ++j)
        {
          s1 = s1 - fmas(i - j + mbdiag, j) * f1(j);
        }
      z1(i) += s1 * fac1;
    }
  decsol::solb(n, lde1, e1, mle, mue, z1, ip1);
  return;
//C
//C -----------------------------------------------------------
//C
statement_5:
  //C ---  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      s1 = 0.0e0;
      // FEM_DO_SAFE(j, 1, n)
      for (integer j = 1; j <= n; ++j)
        {
          s1 = s1 - fmas(i, j) * f1(j);
        }
      z1(i) += s1 * fac1;
    }
  decsol::sol(n, lde1, e1, z1, ip1);
  return;
//C
//C -----------------------------------------------------------
//C
statement_15:
  //C ---  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER
  // FEM_DO_SAFE(i, 1, m1)
  for (integer i = 1; i <= m1; ++i)
    {
      z1(i) = z1(i) - f1(i) * fac1;
    }
  // FEM_DO_SAFE(i, 1, nm1)
  for (integer i = 1; i <= nm1; ++i)
    {
      im1 = i + m1;
      s1 = 0.0e0;
      // FEM_DO_SAFE(j, 1, nm1)
      for (integer j = 1; j <= nm1; ++j)
        {
          s1 = s1 - fmas(i, j) * f1(j + m1);
        }
      z1(im1) += s1 * fac1;
    }
  goto statement_48;
//C
//C -----------------------------------------------------------
//C
statement_6:
  //C ---  B IS A FULL MATRIX, JACOBIAN A BANDED MATRIX
  //C ---  THIS OPTION IS NOT PROVIDED
  return;
//C
//C -----------------------------------------------------------
//C
statement_7:
  //C ---  B=IDENTITY, JACOBIAN A FULL MATRIX, HESSENBERG-OPTION
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      z1(i) = z1(i) - f1(i) * fac1;
    }
  // FEM_DOSTEP(mm, n - 2, 1, -1)
  for (integer mm = n - 2; mm >= 1; --mm)
    {
      mp = n - mm;
      mp1 = mp - 1;
      i = iphes(mp);
      if (i == mp)
        {
          goto statement_746;
        }
      zsafe = z1(mp);
      z1(mp) = z1(i);
      z1(i) = zsafe;
    statement_746:
      // FEM_DO_SAFE(i, mp + 1, n)
      for (integer i = mp + 1; i <= n; ++i)
        {
          z1(i) = z1(i) - fjac(i, mp1) * z1(mp);
        }
    }
  decsol::solh(n, lde1, e1, 1, z1, ip1);
  // FEM_DO_SAFE(mm, 1, n - 2)
  for (integer mm = 1; mm <= n - 2; ++mm)
    {
      mp = n - mm;
      mp1 = mp - 1;
      // FEM_DO_SAFE(i, mp + 1, n)
      for (integer i = mp + 1; i <= n; ++i)
        {
          z1(i) += fjac(i, mp1) * z1(mp);
        }
      i = iphes(mp);
      if (i == mp)
        {
          goto statement_750;
        }
      zsafe = z1(mp);
      z1(mp) = z1(i);
      z1(i) = zsafe;
    statement_750:;
    }
  return;
//C
//C -----------------------------------------------------------
//C
statement_55:;
}

//C
//C     END OF SUBROUTINE SLVRAR
//C
//C ***********************************************************
//C
void _dc_decsol::slvrai(common & cmn,
                        const integer & n,
                        const CFortranAccess< CMatrix< doublereal > > & fjac,
                        const integer & ldjac,
                        const integer & mljac,
                        const integer & mujac,
                        const CFortranAccess< CMatrix< doublereal > > & fmas,
                        const integer & ldmas,
                        const integer & mlmas,
                        const integer & mumas,
                        const integer & m1,
                        const integer & m2,
                        const integer & nm1,
                        const doublereal & alphn,
                        const doublereal & betan,
                        const CFortranAccess< CMatrix< doublereal > > & e2r,
                        const CFortranAccess< CMatrix< doublereal > > & e2i,
                        const integer & lde1,
                        CVectorCore< doublereal > & z2,
                        CVectorCore< doublereal > & z3,
                        const CVectorCore< doublereal > & f2,
                        const CVectorCore< doublereal > & f3,
                        const doublereal & /* cont */,
                        const CVectorCore< integer > & ip2,
                        const CVectorCore< integer > & iphes,
                        const integer & /* ier */,
                        const integer & ijob)
{
  integer & mle = cmn.mle;
  integer & mue = cmn.mue;
  integer & mbdiag = cmn.mbdiag;
  //
  integer i = 0;
  doublereal s2 = 0.0;
  doublereal s3 = 0.0;
  doublereal abno = 0.0;
  integer mm = 0;
  integer j = 0;
  doublereal sum2 = 0.0;
  doublereal sum3 = 0.0;
  integer k = 0;
  integer jkm = 0;
  doublereal sumh = 0.0;
  integer im1 = 0;
  integer mpi = 0;
  doublereal z2i = 0.0;
  doublereal z3i = 0.0;
  integer iimu = 0;
  doublereal bb = 0.0;
  integer jm1 = 0;
  integer mp = 0;
  integer mp1 = 0;
  doublereal zsafe = 0.0;
  doublereal e1imp = 0.0;
  //C
  switch (ijob)
    {
    case 1:
      goto statement_1;
    case 2:
      goto statement_2;
    case 3:
      goto statement_3;
    case 4:
      goto statement_4;
    case 5:
      goto statement_5;
    case 6:
      goto statement_6;
    case 7:
      goto statement_7;
    case 8:
      goto statement_55;
    case 9:
      goto statement_55;
    case 10:
      goto statement_55;
    case 11:
      goto statement_11;
    case 12:
      goto statement_12;
    case 13:
      goto statement_13;
    case 14:
      goto statement_13;
    case 15:
      goto statement_15;
    default:
      break;
    }
//C
//C -----------------------------------------------------------
//C
statement_1:
  //C ---  B=IDENTITY, JACOBIAN A FULL MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      s2 = -f2(i);
      s3 = -f3(i);
      z2(i) += s2 * alphn - s3 * betan;
      z3(i) += s3 * alphn + s2 * betan;
    }
  decsol::solc(n, lde1, e2r, e2i, z2, z3, ip2);
  return;
//C
//C -----------------------------------------------------------
//C
statement_11:
  //C ---  B=IDENTITY, JACOBIAN A FULL MATRIX, SECOND ORDER
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      s2 = -f2(i);
      s3 = -f3(i);
      z2(i) += s2 * alphn - s3 * betan;
      z3(i) += s3 * alphn + s2 * betan;
    }
statement_48:
  abno = pow2(alphn) + pow2(betan);
  mm = m1 / m2;
  // FEM_DO_SAFE(j, 1, m2)
  for (integer j = 1; j <= m2; ++j)
    {
      sum2 = 0.e0;
      sum3 = 0.e0;
      // FEM_DOSTEP(k, mm - 1, 0, -1)
      for (integer k = mm - 1; k >= 0; --k)
        {
          jkm = j + k * m2;
          sumh = (z2(jkm) + sum2) / abno;
          sum3 = (z3(jkm) + sum3) / abno;
          sum2 = sumh * alphn + sum3 * betan;
          sum3 = sum3 * alphn - sumh * betan;
          // FEM_DO_SAFE(i, 1, nm1)
          for (integer i = 1; i <= nm1; ++i)
            {
              im1 = i + m1;
              z2(im1) += fjac(i, jkm) * sum2;
              z3(im1) += fjac(i, jkm) * sum3;
            }
        }
    }
  decsol::solc(nm1, lde1, e2r, e2i, z2(m1 + 1), z3(m1 + 1), ip2);
statement_49:
  // FEM_DOSTEP(i, m1, 1, -1)
  for (integer i = m1; i >= 1; --i)
    {
      mpi = m2 + i;
      z2i = z2(i) + z2(mpi);
      z3i = z3(i) + z3(mpi);
      z3(i) = (z3i * alphn - z2i * betan) / abno;
      z2(i) = (z2i * alphn + z3i * betan) / abno;
    }
  return;
//C
//C -----------------------------------------------------------
//C
statement_2:
  //C ---  B=IDENTITY, JACOBIAN A BANDED MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      s2 = -f2(i);
      s3 = -f3(i);
      z2(i) += s2 * alphn - s3 * betan;
      z3(i) += s3 * alphn + s2 * betan;
    }
  decsol::solbc(n, lde1, e2r, e2i, mle, mue, z2, z3, ip2);
  return;
//C
//C -----------------------------------------------------------
//C
statement_12:
  //C ---  B=IDENTITY, JACOBIAN A BANDED MATRIX, SECOND ORDER
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      s2 = -f2(i);
      s3 = -f3(i);
      z2(i) += s2 * alphn - s3 * betan;
      z3(i) += s3 * alphn + s2 * betan;
    }
statement_45:
  abno = pow2(alphn) + pow2(betan);
  mm = m1 / m2;
  // FEM_DO_SAFE(j, 1, m2)
  for (integer j = 1; j <= m2; ++j)
    {
      sum2 = 0.e0;
      sum3 = 0.e0;
      // FEM_DOSTEP(k, mm - 1, 0, -1)
      for (integer k = mm - 1; k >= 0; --k)
        {
          jkm = j + k * m2;
          sumh = (z2(jkm) + sum2) / abno;
          sum3 = (z3(jkm) + sum3) / abno;
          sum2 = sumh * alphn + sum3 * betan;
          sum3 = sum3 * alphn - sumh * betan;
          // FEM_DO_SAFE(i, std::max(c__1, j - mujac), std::min(nm1, j + mljac))
          for (integer i = std::max(c__1, j - mujac); i <= std::min(nm1, j + mljac); ++i)
            {
              im1 = i + m1;
              iimu = i + mujac + 1 - j;
              z2(im1) += fjac(iimu, jkm) * sum2;
              z3(im1) += fjac(iimu, jkm) * sum3;
            }
        }
    }
  decsol::solbc(nm1, lde1, e2r, e2i, mle, mue, z2(m1 + 1), z3(m1 + 1), ip2);
  goto statement_49;
//C
//C -----------------------------------------------------------
//C
statement_3:
  //C ---  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      s2 = 0.0e0;
      s3 = 0.0e0;
      // FEM_DO_SAFE(j, std::max(c__1, i - mlmas), std::min(n, i + mumas))
      for (integer j = std::max(c__1, i - mlmas); j <= std::min(n, i + mumas); ++j)
        {
          bb = fmas(i - j + mbdiag, j);
          s2 = s2 - bb * f2(j);
          s3 = s3 - bb * f3(j);
        }
      z2(i) += s2 * alphn - s3 * betan;
      z3(i) += s3 * alphn + s2 * betan;
    }
  decsol::solc(n, lde1, e2r, e2i, z2, z3, ip2);
  return;
//C
//C -----------------------------------------------------------
//C
statement_13:
  //C ---  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER
  // FEM_DO_SAFE(i, 1, m1)
  for (integer i = 1; i <= m1; ++i)
    {
      s2 = -f2(i);
      s3 = -f3(i);
      z2(i) += s2 * alphn - s3 * betan;
      z3(i) += s3 * alphn + s2 * betan;
    }
  // FEM_DO_SAFE(i, 1, nm1)
  for (integer i = 1; i <= nm1; ++i)
    {
      im1 = i + m1;
      s2 = 0.0e0;
      s3 = 0.0e0;
      // FEM_DO_SAFE(j, std::max(c__1, i - mlmas), std::min(nm1, i + mumas))
      for (integer j = std::max(c__1, i - mlmas); j <= std::min(nm1, i + mumas); ++j)
        {
          jm1 = j + m1;
          bb = fmas(i - j + mbdiag, j);
          s2 = s2 - bb * f2(jm1);
          s3 = s3 - bb * f3(jm1);
        }
      z2(im1) += s2 * alphn - s3 * betan;
      z3(im1) += s3 * alphn + s2 * betan;
    }
  if (ijob == 14)
    {
      goto statement_45;
    }
  goto statement_48;
//C
//C -----------------------------------------------------------
//C
statement_4:
  //C ---  B IS A BANDED MATRIX, JACOBIAN A BANDED MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      s2 = 0.0e0;
      s3 = 0.0e0;
      // FEM_DO_SAFE(j, std::max(c__1, i - mlmas), std::min(n, i + mumas))
      for (integer j = std::max(c__1, i - mlmas); j <= std::min(n, i + mumas); ++j)
        {
          bb = fmas(i - j + mbdiag, j);
          s2 = s2 - bb * f2(j);
          s3 = s3 - bb * f3(j);
        }
      z2(i) += s2 * alphn - s3 * betan;
      z3(i) += s3 * alphn + s2 * betan;
    }
  decsol::solbc(n, lde1, e2r, e2i, mle, mue, z2, z3, ip2);
  return;
//C
//C -----------------------------------------------------------
//C
statement_5:
  //C ---  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      s2 = 0.0e0;
      s3 = 0.0e0;
      // FEM_DO_SAFE(j, 1, n)
      for (integer j = 1; j <= n; ++j)
        {
          bb = fmas(i, j);
          s2 = s2 - bb * f2(j);
          s3 = s3 - bb * f3(j);
        }
      z2(i) += s2 * alphn - s3 * betan;
      z3(i) += s3 * alphn + s2 * betan;
    }
  decsol::solc(n, lde1, e2r, e2i, z2, z3, ip2);
  return;
//C
//C -----------------------------------------------------------
//C
statement_15:
  //C ---  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER
  // FEM_DO_SAFE(i, 1, m1)
  for (integer i = 1; i <= m1; ++i)
    {
      s2 = -f2(i);
      s3 = -f3(i);
      z2(i) += s2 * alphn - s3 * betan;
      z3(i) += s3 * alphn + s2 * betan;
    }
  // FEM_DO_SAFE(i, 1, nm1)
  for (integer i = 1; i <= nm1; ++i)
    {
      im1 = i + m1;
      s2 = 0.0e0;
      s3 = 0.0e0;
      // FEM_DO_SAFE(j, 1, nm1)
      for (integer j = 1; j <= nm1; ++j)
        {
          jm1 = j + m1;
          bb = fmas(i, j);
          s2 = s2 - bb * f2(jm1);
          s3 = s3 - bb * f3(jm1);
        }
      z2(im1) += s2 * alphn - s3 * betan;
      z3(im1) += s3 * alphn + s2 * betan;
    }
  goto statement_48;
//C
//C -----------------------------------------------------------
//C
statement_6:
  //C ---  B IS A FULL MATRIX, JACOBIAN A BANDED MATRIX
  //C ---  THIS OPTION IS NOT PROVIDED
  return;
//C
//C -----------------------------------------------------------
//C
statement_7:
  //C ---  B=IDENTITY, JACOBIAN A FULL MATRIX, HESSENBERG-OPTION
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      s2 = -f2(i);
      s3 = -f3(i);
      z2(i) += s2 * alphn - s3 * betan;
      z3(i) += s3 * alphn + s2 * betan;
    }
  // FEM_DOSTEP(mm, n - 2, 1, -1)
  for (integer mm = n - 2; mm >= 1; --mm)
    {
      mp = n - mm;
      mp1 = mp - 1;
      i = iphes(mp);
      if (i == mp)
        {
          goto statement_746;
        }
      zsafe = z2(mp);
      z2(mp) = z2(i);
      z2(i) = zsafe;
      zsafe = z3(mp);
      z3(mp) = z3(i);
      z3(i) = zsafe;
    statement_746:
      // FEM_DO_SAFE(i, mp + 1, n)
      for (integer i = mp + 1; i <= n; ++i)
        {
          e1imp = fjac(i, mp1);
          z2(i) = z2(i) - e1imp * z2(mp);
          z3(i) = z3(i) - e1imp * z3(mp);
        }
    }
  decsol::solhc(n, lde1, e2r, e2i, 1, z2, z3, ip2);
  // FEM_DO_SAFE(mm, 1, n - 2)
  for (integer mm = 1; mm <= n - 2; ++mm)
    {
      mp = n - mm;
      mp1 = mp - 1;
      // FEM_DO_SAFE(i, mp + 1, n)
      for (integer i = mp + 1; i <= n; ++i)
        {
          e1imp = fjac(i, mp1);
          z2(i) += e1imp * z2(mp);
          z3(i) += e1imp * z3(mp);
        }
      i = iphes(mp);
      if (i == mp)
        {
          goto statement_750;
        }
      zsafe = z2(mp);
      z2(mp) = z2(i);
      z2(i) = zsafe;
      zsafe = z3(mp);
      z3(mp) = z3(i);
      z3(i) = zsafe;
    statement_750:;
    }
  return;
//C
//C -----------------------------------------------------------
//C
statement_55:;
}

//C
//C     END OF SUBROUTINE SLVRAI
//C
//C ***********************************************************
//C
void _dc_decsol::slvrad(common & cmn,
                        const integer & n,
                        const CFortranAccess< CMatrix< doublereal > > & fjac,
                        const integer & ldjac,
                        const integer & mljac,
                        const integer & mujac,
                        const CFortranAccess< CMatrix< doublereal > > & fmas,
                        const integer & ldmas,
                        const integer & mlmas,
                        const integer & mumas,
                        const integer & m1,
                        const integer & m2,
                        const integer & nm1,
                        const doublereal & fac1,
                        const doublereal & alphn,
                        const doublereal & betan,
                        const CFortranAccess< CMatrix< doublereal > > & e1,
                        const CFortranAccess< CMatrix< doublereal > > & e2r,
                        const CFortranAccess< CMatrix< doublereal > > & e2i,
                        const integer & lde1,
                        CVectorCore< doublereal > & z1,
                        CVectorCore< doublereal > & z2,
                        CVectorCore< doublereal > & z3,
                        const CVectorCore< doublereal > & f1,
                        const CVectorCore< doublereal > & f2,
                        const CVectorCore< doublereal > & f3,
                        const CVectorCore< doublereal > & /* cont */,
                        const CVectorCore< integer > & ip1,
                        const CVectorCore< integer > & ip2,
                        const CVectorCore< integer > & iphes,
                        const integer & /* ier */,
                        const integer & ijob)
{
  integer & mle = cmn.mle;
  integer & mue = cmn.mue;
  integer & mbdiag = cmn.mbdiag;
  //
  integer i = 0;
  doublereal s2 = 0.0;
  doublereal s3 = 0.0;
  doublereal abno = 0.0;
  integer mm = 0;
  integer j = 0;
  doublereal sum1 = 0.0;
  doublereal sum2 = 0.0;
  doublereal sum3 = 0.0;
  integer k = 0;
  integer jkm = 0;
  doublereal sumh = 0.0;
  integer im1 = 0;
  integer mpi = 0;
  doublereal z2i = 0.0;
  doublereal z3i = 0.0;
  doublereal ffja = 0.0;
  doublereal s1 = 0.0;
  doublereal bb = 0.0;
  integer j1b = 0;
  integer j2b = 0;
  integer jm1 = 0;
  integer mp = 0;
  integer mp1 = 0;
  doublereal zsafe = 0.0;
  doublereal e1imp = 0.0;
  //C
  switch (ijob)
    {
    case 1:
      goto statement_1;
    case 2:
      goto statement_2;
    case 3:
      goto statement_3;
    case 4:
      goto statement_4;
    case 5:
      goto statement_5;
    case 6:
      goto statement_6;
    case 7:
      goto statement_7;
    case 8:
      goto statement_55;
    case 9:
      goto statement_55;
    case 10:
      goto statement_55;
    case 11:
      goto statement_11;
    case 12:
      goto statement_12;
    case 13:
      goto statement_13;
    case 14:
      goto statement_13;
    case 15:
      goto statement_15;
    default:
      break;
    }
//C
//C -----------------------------------------------------------
//C
statement_1:
  //C ---  B=IDENTITY, JACOBIAN A FULL MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      s2 = -f2(i);
      s3 = -f3(i);
      z1(i) = z1(i) - f1(i) * fac1;
      z2(i) += s2 * alphn - s3 * betan;
      z3(i) += s3 * alphn + s2 * betan;
    }
  decsol::sol(n, lde1, e1, z1, ip1);
  decsol::solc(n, lde1, e2r, e2i, z2, z3, ip2);
  return;
//C
//C -----------------------------------------------------------
//C
statement_11:
  //C ---  B=IDENTITY, JACOBIAN A FULL MATRIX, SECOND ORDER
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      s2 = -f2(i);
      s3 = -f3(i);
      z1(i) = z1(i) - f1(i) * fac1;
      z2(i) += s2 * alphn - s3 * betan;
      z3(i) += s3 * alphn + s2 * betan;
    }
statement_48:
  abno = pow2(alphn) + pow2(betan);
  mm = m1 / m2;
  // FEM_DO_SAFE(j, 1, m2)
  for (integer j = 1; j <= m2; ++j)
    {
      sum1 = 0.e0;
      sum2 = 0.e0;
      sum3 = 0.e0;
      // FEM_DOSTEP(k, mm - 1, 0, -1)
      for (integer k = mm - 1; k >= 0; --k)
        {
          jkm = j + k * m2;
          sum1 = (z1(jkm) + sum1) / fac1;
          sumh = (z2(jkm) + sum2) / abno;
          sum3 = (z3(jkm) + sum3) / abno;
          sum2 = sumh * alphn + sum3 * betan;
          sum3 = sum3 * alphn - sumh * betan;
          // FEM_DO_SAFE(i, 1, nm1)
          for (integer i = 1; i <= nm1; ++i)
            {
              im1 = i + m1;
              z1(im1) += fjac(i, jkm) * sum1;
              z2(im1) += fjac(i, jkm) * sum2;
              z3(im1) += fjac(i, jkm) * sum3;
            }
        }
    }
  decsol::sol(nm1, lde1, e1, z1(m1 + 1), ip1);
  decsol::solc(nm1, lde1, e2r, e2i, z2(m1 + 1), z3(m1 + 1), ip2);
statement_49:
  // FEM_DOSTEP(i, m1, 1, -1)
  for (integer i = m1; i >= 1; --i)
    {
      mpi = m2 + i;
      z1(i) = (z1(i) + z1(mpi)) / fac1;
      z2i = z2(i) + z2(mpi);
      z3i = z3(i) + z3(mpi);
      z3(i) = (z3i * alphn - z2i * betan) / abno;
      z2(i) = (z2i * alphn + z3i * betan) / abno;
    }
  return;
//C
//C -----------------------------------------------------------
//C
statement_2:
  //C ---  B=IDENTITY, JACOBIAN A BANDED MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      s2 = -f2(i);
      s3 = -f3(i);
      z1(i) = z1(i) - f1(i) * fac1;
      z2(i) += s2 * alphn - s3 * betan;
      z3(i) += s3 * alphn + s2 * betan;
    }
  decsol::solb(n, lde1, e1, mle, mue, z1, ip1);
  decsol::solbc(n, lde1, e2r, e2i, mle, mue, z2, z3, ip2);
  return;
//C
//C -----------------------------------------------------------
//C
statement_12:
  //C ---  B=IDENTITY, JACOBIAN A BANDED MATRIX, SECOND ORDER
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      s2 = -f2(i);
      s3 = -f3(i);
      z1(i) = z1(i) - f1(i) * fac1;
      z2(i) += s2 * alphn - s3 * betan;
      z3(i) += s3 * alphn + s2 * betan;
    }
statement_45:
  abno = pow2(alphn) + pow2(betan);
  mm = m1 / m2;
  // FEM_DO_SAFE(j, 1, m2)
  for (integer j = 1; j <= m2; ++j)
    {
      sum1 = 0.e0;
      sum2 = 0.e0;
      sum3 = 0.e0;
      // FEM_DOSTEP(k, mm - 1, 0, -1)
      for (integer k = mm - 1; k >= 0; --k)
        {
          jkm = j + k * m2;
          sum1 = (z1(jkm) + sum1) / fac1;
          sumh = (z2(jkm) + sum2) / abno;
          sum3 = (z3(jkm) + sum3) / abno;
          sum2 = sumh * alphn + sum3 * betan;
          sum3 = sum3 * alphn - sumh * betan;
          // FEM_DO_SAFE(i, std::max(c__1, j - mujac), std::min(nm1, j + mljac))
          for (integer i = std::max(c__1, j - mujac); i <= std::min(nm1, j + mljac); ++i)
            {
              /* code */
            }

          {
            im1 = i + m1;
            ffja = fjac(i + mujac + 1 - j, jkm);
            z1(im1) += ffja * sum1;
            z2(im1) += ffja * sum2;
            z3(im1) += ffja * sum3;
          }
        }
    }
  decsol::solb(nm1, lde1, e1, mle, mue, z1(m1 + 1), ip1);
  decsol::solbc(nm1, lde1, e2r, e2i, mle, mue, z2(m1 + 1), z3(m1 + 1), ip2);
  goto statement_49;
//C
//C -----------------------------------------------------------
//C
statement_3:
  //C ---  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      s1 = 0.0e0;
      s2 = 0.0e0;
      s3 = 0.0e0;
      // FEM_DO_SAFE(j, std::max(c__1, i - mlmas), std::min(n, i + mumas))
      for (integer j = std::max(c__1, i - mlmas); j <= std::min(n, i + mumas); ++j)
        {
          bb = fmas(i - j + mbdiag, j);
          s1 = s1 - bb * f1(j);
          s2 = s2 - bb * f2(j);
          s3 = s3 - bb * f3(j);
        }
      z1(i) += s1 * fac1;
      z2(i) += s2 * alphn - s3 * betan;
      z3(i) += s3 * alphn + s2 * betan;
    }
  decsol::sol(n, lde1, e1, z1, ip1);
  decsol::solc(n, lde1, e2r, e2i, z2, z3, ip2);
  return;
//C
//C -----------------------------------------------------------
//C
statement_13:
  //C ---  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER
  // FEM_DO_SAFE(i, 1, m1)
  for (integer i = 1; i <= m1; ++i)
    {
      s2 = -f2(i);
      s3 = -f3(i);
      z1(i) = z1(i) - f1(i) * fac1;
      z2(i) += s2 * alphn - s3 * betan;
      z3(i) += s3 * alphn + s2 * betan;
    }
  // FEM_DO_SAFE(i, 1, nm1)
  for (integer i = 1; i <= nm1; ++i)
    {
      im1 = i + m1;
      s1 = 0.0e0;
      s2 = 0.0e0;
      s3 = 0.0e0;
      j1b = std::max(c__1, i - mlmas);
      j2b = std::min(nm1, i + mumas);
      // FEM_DO_SAFE(j, j1b, j2b)
      for (integer j = j1b; j <= j2b; ++j)
        {
          jm1 = j + m1;
          bb = fmas(i - j + mbdiag, j);
          s1 = s1 - bb * f1(jm1);
          s2 = s2 - bb * f2(jm1);
          s3 = s3 - bb * f3(jm1);
        }
      z1(im1) += s1 * fac1;
      z2(im1) += s2 * alphn - s3 * betan;
      z3(im1) += s3 * alphn + s2 * betan;
    }
  if (ijob == 14)
    {
      goto statement_45;
    }
  goto statement_48;
//C
//C -----------------------------------------------------------
//C
statement_4:
  //C ---  B IS A BANDED MATRIX, JACOBIAN A BANDED MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      s1 = 0.0e0;
      s2 = 0.0e0;
      s3 = 0.0e0;
      // FEM_DO_SAFE(j, std::max(c__1, i - mlmas), std::min(n, i + mumas))
      for (integer j = std::max(c__1, i - mlmas); j <= std::min(n, i + mumas); ++j)
        {
          bb = fmas(i - j + mbdiag, j);
          s1 = s1 - bb * f1(j);
          s2 = s2 - bb * f2(j);
          s3 = s3 - bb * f3(j);
        }
      z1(i) += s1 * fac1;
      z2(i) += s2 * alphn - s3 * betan;
      z3(i) += s3 * alphn + s2 * betan;
    }
  decsol::solb(n, lde1, e1, mle, mue, z1, ip1);
  decsol::solbc(n, lde1, e2r, e2i, mle, mue, z2, z3, ip2);
  return;
//C
//C -----------------------------------------------------------
//C
statement_5:
  //C ---  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      s1 = 0.0e0;
      s2 = 0.0e0;
      s3 = 0.0e0;
      // FEM_DO_SAFE(j, 1, n)
      for (integer j = 1; j <= n; ++j)
        {
          bb = fmas(i, j);
          s1 = s1 - bb * f1(j);
          s2 = s2 - bb * f2(j);
          s3 = s3 - bb * f3(j);
        }
      z1(i) += s1 * fac1;
      z2(i) += s2 * alphn - s3 * betan;
      z3(i) += s3 * alphn + s2 * betan;
    }
  decsol::sol(n, lde1, e1, z1, ip1);
  decsol::solc(n, lde1, e2r, e2i, z2, z3, ip2);
  return;
//C
//C -----------------------------------------------------------
//C
statement_15:
  //C ---  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER
  // FEM_DO_SAFE(i, 1, m1)
  for (integer i = 1; i <= m1; ++i)
    {
      s2 = -f2(i);
      s3 = -f3(i);
      z1(i) = z1(i) - f1(i) * fac1;
      z2(i) += s2 * alphn - s3 * betan;
      z3(i) += s3 * alphn + s2 * betan;
    }
  // FEM_DO_SAFE(i, 1, nm1)
  for (integer i = 1; i <= nm1; ++i)
    {
      im1 = i + m1;
      s1 = 0.0e0;
      s2 = 0.0e0;
      s3 = 0.0e0;
      // FEM_DO_SAFE(j, 1, nm1)
      for (integer j = 1; j <= nm1; ++j)
        {
          jm1 = j + m1;
          bb = fmas(i, j);
          s1 = s1 - bb * f1(jm1);
          s2 = s2 - bb * f2(jm1);
          s3 = s3 - bb * f3(jm1);
        }
      z1(im1) += s1 * fac1;
      z2(im1) += s2 * alphn - s3 * betan;
      z3(im1) += s3 * alphn + s2 * betan;
    }
  goto statement_48;
//C
//C -----------------------------------------------------------
//C
statement_6:
  //C ---  B IS A FULL MATRIX, JACOBIAN A BANDED MATRIX
  //C ---  THIS OPTION IS NOT PROVIDED
  return;
//C
//C -----------------------------------------------------------
//C
statement_7:
  //C ---  B=IDENTITY, JACOBIAN A FULL MATRIX, HESSENBERG-OPTION
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      s2 = -f2(i);
      s3 = -f3(i);
      z1(i) = z1(i) - f1(i) * fac1;
      z2(i) += s2 * alphn - s3 * betan;
      z3(i) += s3 * alphn + s2 * betan;
    }
  // FEM_DOSTEP(mm, n - 2, 1, -1)
  for (integer mm = n - 2; mm >= 1; --mm)
    {
      mp = n - mm;
      mp1 = mp - 1;
      i = iphes(mp);
      if (i == mp)
        {
          goto statement_746;
        }
      zsafe = z1(mp);
      z1(mp) = z1(i);
      z1(i) = zsafe;
      zsafe = z2(mp);
      z2(mp) = z2(i);
      z2(i) = zsafe;
      zsafe = z3(mp);
      z3(mp) = z3(i);
      z3(i) = zsafe;
    statement_746:
      // FEM_DO_SAFE(i, mp + 1, n)
      for (integer i = mp + 1; i <= n; ++i)
        {
          e1imp = fjac(i, mp1);
          z1(i) = z1(i) - e1imp * z1(mp);
          z2(i) = z2(i) - e1imp * z2(mp);
          z3(i) = z3(i) - e1imp * z3(mp);
        }
    }
  decsol::solh(n, lde1, e1, 1, z1, ip1);
  decsol::solhc(n, lde1, e2r, e2i, 1, z2, z3, ip2);
  // FEM_DO_SAFE(mm, 1, n - 2)
  for (integer mm = 1; mm <= n - 2; ++mm)
    {
      mp = n - mm;
      mp1 = mp - 1;
      // FEM_DO_SAFE(i, mp + 1, n)
      for (integer i = mp + 1; i <= n; ++i)
        {
          e1imp = fjac(i, mp1);
          z1(i) += e1imp * z1(mp);
          z2(i) += e1imp * z2(mp);
          z3(i) += e1imp * z3(mp);
        }
      i = iphes(mp);
      if (i == mp)
        {
          goto statement_750;
        }
      zsafe = z1(mp);
      z1(mp) = z1(i);
      z1(i) = zsafe;
      zsafe = z2(mp);
      z2(mp) = z2(i);
      z2(i) = zsafe;
      zsafe = z3(mp);
      z3(mp) = z3(i);
      z3(i) = zsafe;
    statement_750:;
    }
  return;
//C
//C -----------------------------------------------------------
//C
statement_55:;
}

//C
//C     END OF SUBROUTINE SLVRAD
//C
//C ***********************************************************
//C
void _dc_decsol::estrad(common & cmn,
                        const integer & n,
                        const CFortranAccess< CMatrix< doublereal > > & fjac,
                        const integer & ldjac,
                        const integer & mljac,
                        const integer & mujac,
                        const CFortranAccess< CMatrix< doublereal > > & fmas,
                        const integer & ldmas,
                        const integer & mlmas,
                        const integer & mumas,
                        const doublereal & h,
                        const doublereal & dd1,
                        const doublereal & dd2,
                        const doublereal & dd3,
                        evalF & fcn,
                        integer & nfcn,
                        const CVectorCore< doublereal > & y0,
                        const CVectorCore< doublereal > & y,
                        const integer & ijob,
                        const doublereal & x,
                        const integer & m1,
                        const integer & m2,
                        const integer & nm1,
                        const CFortranAccess< CMatrix< doublereal > > & e1,
                        const integer & lde1,
                        const CVectorCore< doublereal > & z1,
                        const CVectorCore< doublereal > & z2,
                        const CVectorCore< doublereal > & z3,
                        CVectorCore< doublereal > & cont,
                        CVectorCore< doublereal > & f1,
                        CVectorCore< doublereal > & f2,
                        const CVectorCore< integer > & ip1,
                        const CVectorCore< integer > & iphes,
                        const CVectorCore< doublereal > & scal,
                        doublereal & err,
                        bool const & first,
                        bool const & reject,
                        const doublereal & fac1,
                        const CVectorCore< doublereal > & rpar,
                        const CVectorCore< integer > & ipar)
{
  integer & mle = cmn.mle;
  integer & mue = cmn.mue;
  integer & mbdiag = cmn.mbdiag;
  //
  doublereal hee1 = 0.0;
  doublereal hee2 = 0.0;
  doublereal hee3 = 0.0;
  integer i = 0;
  integer mm = 0;
  integer j = 0;
  doublereal sum1 = 0.0;
  integer k = 0;
  integer im1 = 0;
  doublereal sum = 0.0;
  integer mp = 0;
  doublereal zsafe = 0.0;
  hee1 = dd1 / h;
  hee2 = dd2 / h;
  hee3 = dd3 / h;
  switch (ijob)
    {
    case 1:
      goto statement_1;
    case 2:
      goto statement_2;
    case 3:
      goto statement_3;
    case 4:
      goto statement_4;
    case 5:
      goto statement_5;
    case 6:
      goto statement_6;
    case 7:
      goto statement_7;
    case 8:
      goto statement_55;
    case 9:
      goto statement_55;
    case 10:
      goto statement_55;
    case 11:
      goto statement_11;
    case 12:
      goto statement_12;
    case 13:
      goto statement_13;
    case 14:
      goto statement_14;
    case 15:
      goto statement_15;
    default:
      break;
    }
//C
statement_1:
  //C ------  B=IDENTITY, JACOBIAN A FULL MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      f2(i) = hee1 * z1(i) + hee2 * z2(i) + hee3 * z3(i);
      cont(i) = f2(i) + y0(i);
    }
  decsol::sol(n, lde1, e1, cont, ip1);
  goto statement_77;
//C
statement_11:
  //C ------  B=IDENTITY, JACOBIAN A FULL MATRIX, SECOND ORDER
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      f2(i) = hee1 * z1(i) + hee2 * z2(i) + hee3 * z3(i);
      cont(i) = f2(i) + y0(i);
    }
statement_48:
  mm = m1 / m2;
  // FEM_DO_SAFE(j, 1, m2)
  for (integer j = 1; j <= m2; ++j)
    {
      sum1 = 0.e0;
      // FEM_DOSTEP(k, mm - 1, 0, -1)
      for (integer k = mm - 1; k >= 0; --k)
        {
          sum1 = (cont(j + k * m2) + sum1) / fac1;
          // FEM_DO_SAFE(i, 1, nm1)
          for (integer i = 1; i <= nm1; ++i)
            {
              im1 = i + m1;
              cont(im1) += fjac(i, j + k * m2) * sum1;
            }
        }
    }
  decsol::sol(nm1, lde1, e1, cont(m1 + 1), ip1);
  // FEM_DOSTEP(i, m1, 1, -1)
  for (integer i = m1; i >= 1; --i)
    {
      cont(i) = (cont(i) + cont(m2 + i)) / fac1;
    }
  goto statement_77;
//C
statement_2:
  //C ------  B=IDENTITY, JACOBIAN A BANDED MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      f2(i) = hee1 * z1(i) + hee2 * z2(i) + hee3 * z3(i);
      cont(i) = f2(i) + y0(i);
    }
  decsol::solb(n, lde1, e1, mle, mue, cont, ip1);
  goto statement_77;
//C
statement_12:
  //C ------  B=IDENTITY, JACOBIAN A BANDED MATRIX, SECOND ORDER
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      f2(i) = hee1 * z1(i) + hee2 * z2(i) + hee3 * z3(i);
      cont(i) = f2(i) + y0(i);
    }
statement_45:
  mm = m1 / m2;
  // FEM_DO_SAFE(j, 1, m2)
  for (integer j = 1; j <= m2; ++j)
    {
      sum1 = 0.e0;
      // FEM_DOSTEP(k, mm - 1, 0, -1)
      for (integer k = mm - 1; k >= 0; --k)
        {
          sum1 = (cont(j + k * m2) + sum1) / fac1;
          // FEM_DO_SAFE(i, std::max(c__1, j - mujac), std::min(nm1, j + mljac))
          for (integer i = std::max(c__1, j - mujac); i <= std::min(nm1, j + mljac); ++i)
            {
              im1 = i + m1;
              cont(im1) += fjac(i + mujac + 1 - j, j + k * m2) * sum1;
            }
        }
    }
  decsol::solb(nm1, lde1, e1, mle, mue, cont(m1 + 1), ip1);
  // FEM_DOSTEP(i, m1, 1, -1)
  for (integer i = m1; i >= 1; --i)
    {
      cont(i) = (cont(i) + cont(m2 + i)) / fac1;
    }
  goto statement_77;
//C
statement_3:
  //C ------  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      f1(i) = hee1 * z1(i) + hee2 * z2(i) + hee3 * z3(i);
    }
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(j, std::max(c__1, i - mlmas), std::min(n, i + mumas))
      for (integer j = std::max(c__1, i - mlmas); j <= std::min(n, i + mumas); ++j)
        {
          sum += fmas(i - j + mbdiag, j) * f1(j);
        }
      f2(i) = sum;
      cont(i) = sum + y0(i);
    }
  decsol::sol(n, lde1, e1, cont, ip1);
  goto statement_77;
//C
statement_13:
  //C ------  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER
  // FEM_DO_SAFE(i, 1, m1)
  for (integer i = 1; i <= m1; ++i)
    {
      f2(i) = hee1 * z1(i) + hee2 * z2(i) + hee3 * z3(i);
      cont(i) = f2(i) + y0(i);
    }
  // FEM_DO_SAFE(i, m1 + 1, n)
  for (integer i = m1 + 1; i <= n; ++i)
    {
      f1(i) = hee1 * z1(i) + hee2 * z2(i) + hee3 * z3(i);
    }
  // FEM_DO_SAFE(i, 1, nm1)
  for (integer i = 1; i <= nm1; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(j, std::max(c__1, i - mlmas), std::min(nm1, i + mumas))
      for (integer j = std::max(c__1, i - mlmas); j <= std::min(nm1, i + mumas); ++j)
        {
          sum += fmas(i - j + mbdiag, j) * f1(j + m1);
        }
      im1 = i + m1;
      f2(im1) = sum;
      cont(im1) = sum + y0(im1);
    }
  goto statement_48;
//C
statement_4:
  //C ------  B IS A BANDED MATRIX, JACOBIAN A BANDED MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      f1(i) = hee1 * z1(i) + hee2 * z2(i) + hee3 * z3(i);
    }
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(j, std::max(c__1, i - mlmas), std::min(n, i + mumas))
      for (integer j = std::max(c__1, i - mlmas); j <= std::min(n, i + mumas); ++j)
        {
          sum += fmas(i - j + mbdiag, j) * f1(j);
        }
      f2(i) = sum;
      cont(i) = sum + y0(i);
    }
  decsol::solb(n, lde1, e1, mle, mue, cont, ip1);
  goto statement_77;
//C
statement_14:
  //C ------  B IS A BANDED MATRIX, JACOBIAN A BANDED MATRIX, SECOND ORDER
  // FEM_DO_SAFE(i, 1, m1)
  for (integer i = 1; i <= m1; ++i)
    {
      f2(i) = hee1 * z1(i) + hee2 * z2(i) + hee3 * z3(i);
      cont(i) = f2(i) + y0(i);
    }
  // FEM_DO_SAFE(i, m1 + 1, n)
  for (integer i = m1 + 1; i <= n; ++i)
    {
      f1(i) = hee1 * z1(i) + hee2 * z2(i) + hee3 * z3(i);
    }
  // FEM_DO_SAFE(i, 1, nm1)
  for (integer i = 1; i <= nm1; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(j, std::max(c__1, i - mlmas), std::min(nm1, i + mumas))
      for (integer j = std::max(c__1, i - mlmas); j <= std::min(nm1, i + mumas); ++j)
        {
          sum += fmas(i - j + mbdiag, j) * f1(j + m1);
        }
      im1 = i + m1;
      f2(im1) = sum;
      cont(im1) = sum + y0(im1);
    }
  goto statement_45;
//C
statement_5:
  //C ------  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      f1(i) = hee1 * z1(i) + hee2 * z2(i) + hee3 * z3(i);
    }
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(j, 1, n)
      for (integer j = 1; j <= n; ++j)
        {
          sum += fmas(i, j) * f1(j);
        }
      f2(i) = sum;
      cont(i) = sum + y0(i);
    }
  decsol::sol(n, lde1, e1, cont, ip1);
  goto statement_77;
//C
statement_15:
  //C ------  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER
  // FEM_DO_SAFE(i, 1, m1)
  for (integer i = 1; i <= m1; ++i)
    {
      f2(i) = hee1 * z1(i) + hee2 * z2(i) + hee3 * z3(i);
      cont(i) = f2(i) + y0(i);
    }
  // FEM_DO_SAFE(i, m1 + 1, n)
  for (integer i = m1 + 1; i <= n; ++i)
    {
      f1(i) = hee1 * z1(i) + hee2 * z2(i) + hee3 * z3(i);
    }
  // FEM_DO_SAFE(i, 1, nm1)
  for (integer i = 1; i <= nm1; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(j, 1, nm1)
      for (integer j = 1; j <= nm1; ++j)
        {
          sum += fmas(i, j) * f1(j + m1);
        }
      im1 = i + m1;
      f2(im1) = sum;
      cont(im1) = sum + y0(im1);
    }
  goto statement_48;
//C
statement_6:
  //C ------  B IS A FULL MATRIX, JACOBIAN A BANDED MATRIX
  //C ------  THIS OPTION IS NOT PROVIDED
  return;
//C
statement_7:
  //C ------  B=IDENTITY, JACOBIAN A FULL MATRIX, HESSENBERG-OPTION
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      f2(i) = hee1 * z1(i) + hee2 * z2(i) + hee3 * z3(i);
      cont(i) = f2(i) + y0(i);
    }
  // FEM_DOSTEP(mm, n - 2, 1, -1)
  for (integer mm = n - 2; mm >= 1; --mm)
    {
      mp = n - mm;
      i = iphes(mp);
      if (i == mp)
        {
          goto statement_310;
        }
      zsafe = cont(mp);
      cont(mp) = cont(i);
      cont(i) = zsafe;
    statement_310:
      // FEM_DO_SAFE(i, mp + 1, n)
      for (integer i = mp + 1; i <= n; ++i)
        {
          cont(i) = cont(i) - fjac(i, mp - 1) * cont(mp);
        }
    }
  decsol::solh(n, lde1, e1, 1, cont, ip1);
  // FEM_DO_SAFE(mm, 1, n - 2)
  for (integer mm = 1; mm <= n - 2; ++mm)
    {
      mp = n - mm;
      // FEM_DO_SAFE(i, mp + 1, n)
      for (integer i = mp + 1; i <= n; ++i)
        {
          cont(i) += fjac(i, mp - 1) * cont(mp);
        }
      i = iphes(mp);
      if (i == mp)
        {
          goto statement_440;
        }
      zsafe = cont(mp);
      cont(mp) = cont(i);
      cont(i) = zsafe;
    statement_440:;
    }
//C
//C --------------------------------------
//C
statement_77:
  err = 0.e0;
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      err += pow2((cont(i) / scal(i)));
    }
  err = std::max(std::sqrt(err / n), 1.e-10);
  //C
  if (err < 1.e0)
    {
      return;
    }
  if (first || reject)
    {
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          cont(i) += y(i);
        }
      fcn(n, x, cont, f1, rpar, ipar);
      nfcn++;
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          cont(i) = f1(i) + f2(i);
        }
      switch (ijob)
        {
        case 1:
          goto statement_31;
        case 2:
          goto statement_32;
        case 3:
          goto statement_31;
        case 4:
          goto statement_32;
        case 5:
          goto statement_31;
        case 6:
          goto statement_32;
        case 7:
          goto statement_33;
        case 8:
          goto statement_55;
        case 9:
          goto statement_55;
        case 10:
          goto statement_55;
        case 11:
          goto statement_41;
        case 12:
          goto statement_42;
        case 13:
          goto statement_41;
        case 14:
          goto statement_42;
        case 15:
          goto statement_41;
        default:
          break;
        }
    //C ------ FULL MATRIX OPTION
    statement_31:
      decsol::sol(n, lde1, e1, cont, ip1);
      goto statement_88;
    //C ------ FULL MATRIX OPTION, SECOND ORDER
    statement_41:
      // FEM_DO_SAFE(j, 1, m2)
      for (integer j = 1; j <= m2; ++j)
        {
          sum1 = 0.e0;
          // FEM_DOSTEP(k, mm - 1, 0, -1)
          for (integer k = mm - 1; k >= 0; --k)
            {
              sum1 = (cont(j + k * m2) + sum1) / fac1;
              // FEM_DO_SAFE(i, 1, nm1)
              for (integer i = 1; i <= nm1; ++i)
                {
                  im1 = i + m1;
                  cont(im1) += fjac(i, j + k * m2) * sum1;
                }
            }
        }
      decsol::sol(nm1, lde1, e1, cont(m1 + 1), ip1);
      // FEM_DOSTEP(i, m1, 1, -1)
      for (integer i = m1; i >= 1; --i)
        {
          cont(i) = (cont(i) + cont(m2 + i)) / fac1;
        }
      goto statement_88;
    //C ------ BANDED MATRIX OPTION
    statement_32:
      decsol::solb(n, lde1, e1, mle, mue, cont, ip1);
      goto statement_88;
    //C ------ BANDED MATRIX OPTION, SECOND ORDER
    statement_42:
      // FEM_DO_SAFE(j, 1, m2)
      for (integer j = 1; j <= m2; ++j)
        {
          sum1 = 0.e0;
          // FEM_DOSTEP(k, mm - 1, 0, -1)
          for (integer k = mm - 1; k >= 0; --k)
            {
              sum1 = (cont(j + k * m2) + sum1) / fac1;
              // FEM_DO_SAFE(i, std::max(c__1, j - mujac), std::min(nm1, j + mljac))
              for (integer i = std::max(c__1, j - mujac); i <= std::min(nm1, j + mljac); ++i)
                {
                  im1 = i + m1;
                  cont(im1) += fjac(i + mujac + 1 - j, j + k * m2) * sum1;
                }
            }
        }
      decsol::solb(nm1, lde1, e1, mle, mue, cont(m1 + 1), ip1);
      // FEM_DOSTEP(i, m1, 1, -1)
      for (integer i = m1; i >= 1; --i)
        {
          cont(i) = (cont(i) + cont(m2 + i)) / fac1;
        }
      goto statement_88;
    //C ------ HESSENBERG MATRIX OPTION
    statement_33:
      // FEM_DOSTEP(mm, n - 2, 1, -1)
      for (integer mm = n - 2; mm >= 1; --mm)
        {
          mp = n - mm;
          i = iphes(mp);
          if (i == mp)
            {
              goto statement_510;
            }
          zsafe = cont(mp);
          cont(mp) = cont(i);
          cont(i) = zsafe;
        statement_510:
          // FEM_DO_SAFE(i, mp + 1, n)
          for (integer i = mp + 1; i <= n; ++i)
            {
              cont(i) = cont(i) - fjac(i, mp - 1) * cont(mp);
            }
        }
      decsol::solh(n, lde1, e1, 1, cont, ip1);
      // FEM_DO_SAFE(mm, 1, n - 2)
      for (integer mm = 1; mm <= n - 2; ++mm)
        {
          mp = n - mm;
          // FEM_DO_SAFE(i, mp + 1, n)
          for (integer i = mp + 1; i <= n; ++i)
            {
              cont(i) += fjac(i, mp - 1) * cont(mp);
            }
          i = iphes(mp);
          if (i == mp)
            {
              goto statement_640;
            }
          zsafe = cont(mp);
          cont(mp) = cont(i);
          cont(i) = zsafe;
        statement_640:;
        }
    //C -----------------------------------
    statement_88:
      err = 0.e0;
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          err += pow2((cont(i) / scal(i)));
        }
      err = std::max(std::sqrt(err / n), 1.e-10);
    }
  return;
//C -----------------------------------------------------------
statement_55:;
}

//C
//C     END OF SUBROUTINE ESTRAD
//C
//C ***********************************************************
//C
void _dc_decsol::estrav(common & cmn,
                        const integer & n,
                        const CFortranAccess< CMatrix< doublereal > > & fjac,
                        const integer & ldjac,
                        const integer & mljac,
                        const integer & mujac,
                        const CFortranAccess< CMatrix< doublereal > > & fmas,
                        const integer & ldmas,
                        const integer & mlmas,
                        const integer & mumas,
                        const doublereal & h,
                        const CVectorCore< doublereal > & dd,
                        evalF & fcn,
                        integer & nfcn,
                        const CVectorCore< doublereal > & y0,
                        const CVectorCore< doublereal > & y,
                        const integer & ijob,
                        const doublereal & x,
                        const integer & m1,
                        const integer & m2,
                        const integer & nm1,
                        const integer & ns,
                        const integer & nns,
                        const CFortranAccess< CMatrix< doublereal > > & e1,
                        const integer & lde1,
                        const CVectorCore< doublereal > & zz,
                        CVectorCore< doublereal > & cont,
                        CVectorCore< doublereal > & ff,
                        const CVectorCore< integer > & ip1,
                        const CVectorCore< integer > & iphes,
                        const CVectorCore< doublereal > & scal,
                        doublereal & err,
                        bool const & first,
                        bool const & reject,
                        const doublereal & fac1,
                        const CVectorCore< doublereal > & rpar,
                        const CVectorCore< integer > & ipar)
{
  integer & mle = cmn.mle;
  integer & mue = cmn.mue;
  integer & mbdiag = cmn.mbdiag;
  //
  integer i = 0;
  doublereal sum = 0.0;
  integer k = 0;
  integer mm = 0;
  integer j = 0;
  doublereal sum1 = 0.0;
  integer im1 = 0;
  integer mp = 0;
  doublereal zsafe = 0.0;
  switch (ijob)
    {
    case 1:
      goto statement_1;
    case 2:
      goto statement_2;
    case 3:
      goto statement_3;
    case 4:
      goto statement_4;
    case 5:
      goto statement_5;
    case 6:
      goto statement_6;
    case 7:
      goto statement_7;
    case 8:
      goto statement_55;
    case 9:
      goto statement_55;
    case 10:
      goto statement_55;
    case 11:
      goto statement_11;
    case 12:
      goto statement_12;
    case 13:
      goto statement_13;
    case 14:
      goto statement_14;
    case 15:
      goto statement_15;
    default:
      break;
    }
//C
statement_1:
  //C ------  B=IDENTITY, JACOBIAN A FULL MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(k, 1, ns)
      for (integer k = 1; k <= ns; ++k)
        {
          sum += dd(k) * zz(i + (k - 1) * n);
        }
      ff(i + n) = sum / h;
      cont(i) = ff(i + n) + y0(i);
    }
  decsol::sol(n, lde1, e1, cont, ip1);
  goto statement_77;
//C
statement_11:
  //C ------  B=IDENTITY, JACOBIAN A FULL MATRIX, SECOND ORDER
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(k, 1, ns)
      for (integer k = 1; k <= ns; ++k)
        {
          sum += dd(k) * zz(i + (k - 1) * n);
        }
      ff(i + n) = sum / h;
      cont(i) = ff(i + n) + y0(i);
    }
statement_48:
  mm = m1 / m2;
  // FEM_DO_SAFE(j, 1, m2)
  for (integer j = 1; j <= m2; ++j)
    {
      sum1 = 0.e0;
      // FEM_DOSTEP(k, mm - 1, 0, -1)
      for (integer k = mm - 1; k >= 0; --k)
        {
          sum1 = (cont(j + k * m2) + sum1) / fac1;
          // FEM_DO_SAFE(i, 1, nm1)
          for (integer i = 1; i <= nm1; ++i)
            {
              im1 = i + m1;
              cont(im1) += fjac(i, j + k * m2) * sum1;
            }
        }
    }
  decsol::sol(nm1, lde1, e1, cont(m1 + 1), ip1);
  // FEM_DOSTEP(i, m1, 1, -1)
  for (integer i = m1; i >= 1; --i)
    {
      cont(i) = (cont(i) + cont(m2 + i)) / fac1;
    }
  goto statement_77;
//C
statement_2:
  //C ------  B=IDENTITY, JACOBIAN A BANDED MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(k, 1, ns)
      for (integer k = 1; k <= ns; ++k)
        {
          sum += dd(k) * zz(i + (k - 1) * n);
        }
      ff(i + n) = sum / h;
      cont(i) = ff(i + n) + y0(i);
    }
  decsol::solb(n, lde1, e1, mle, mue, cont, ip1);
  goto statement_77;
//C
statement_12:
  //C ------  B=IDENTITY, JACOBIAN A BANDED MATRIX, SECOND ORDER
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(k, 1, ns)
      for (integer k = 1; k <= ns; ++k)
        {
          sum += dd(k) * zz(i + (k - 1) * n);
        }
      ff(i + n) = sum / h;
      cont(i) = ff(i + n) + y0(i);
    }
statement_45:
  mm = m1 / m2;
  // FEM_DO_SAFE(j, 1, m2)
  for (integer j = 1; j <= m2; ++j)
    {
      sum1 = 0.e0;
      // FEM_DOSTEP(k, mm - 1, 0, -1)
      for (integer k = mm - 1; k >= 0; --k)
        {
          sum1 = (cont(j + k * m2) + sum1) / fac1;
          // FEM_DO_SAFE(i, std::max(c__1, j - mujac), std::min(nm1, j + mljac))
          for (integer i = std::max(c__1, j - mujac); i <= std::min(nm1, j + mljac); ++i)
            {
              im1 = i + m1;
              cont(im1) += fjac(i + mujac + 1 - j, j + k * m2) * sum1;
            }
        }
    }
  decsol::solb(nm1, lde1, e1, mle, mue, cont(m1 + 1), ip1);
  // FEM_DOSTEP(i, m1, 1, -1)
  for (integer i = m1; i >= 1; --i)
    {
      cont(i) = (cont(i) + cont(m2 + i)) / fac1;
    }
  goto statement_77;
//C
statement_3:
  //C ------  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(k, 1, ns)
      for (integer k = 1; k <= ns; ++k)
        {
          sum += dd(k) * zz(i + (k - 1) * n);
        }
      ff(i) = sum / h;
    }
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(j, std::max(c__1, i - mlmas), std::min(n, i + mumas))
      for (integer j = std::max(c__1, i - mlmas); j <= std::min(n, i + mumas); ++j)
        {
          sum += fmas(i - j + mbdiag, j) * ff(j);
        }
      ff(i + n) = sum;
      cont(i) = sum + y0(i);
    }
  decsol::sol(n, lde1, e1, cont, ip1);
  goto statement_77;
//C
statement_13:
  //C ------  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER
  // FEM_DO_SAFE(i, 1, m1)
  for (integer i = 1; i <= m1; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(k, 1, ns)
      for (integer k = 1; k <= ns; ++k)
        {
          sum += dd(k) * zz(i + (k - 1) * n);
        }
      ff(i + n) = sum / h;
      cont(i) = ff(i + n) + y0(i);
    }
  // FEM_DO_SAFE(i, m1 + 1, n)
  for (integer i = m1 + 1; i <= n; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(k, 1, ns)
      for (integer k = 1; k <= ns; ++k)
        {
          sum += dd(k) * zz(i + (k - 1) * n);
        }
      ff(i) = sum / h;
    }
  // FEM_DO_SAFE(i, 1, nm1)
  for (integer i = 1; i <= nm1; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(j, std::max(c__1, i - mlmas), std::min(nm1, i + mumas))
      for (integer j = std::max(c__1, i - mlmas); j <= std::min(nm1, i + mumas); ++j)
        {
          sum += fmas(i - j + mbdiag, j) * ff(j + m1);
        }
      im1 = i + m1;
      ff(im1 + n) = sum;
      cont(im1) = sum + y0(im1);
    }
  goto statement_48;
//C
statement_4:
  //C ------  B IS A BANDED MATRIX, JACOBIAN A BANDED MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(k, 1, ns)
      for (integer k = 1; k <= ns; ++k)
        {
          sum += dd(k) * zz(i + (k - 1) * n);
        }
      ff(i) = sum / h;
    }
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(j, std::max(c__1, i - mlmas), std::min(n, i + mumas))
      for (integer j = std::max(c__1, i - mlmas); j <= std::min(n, i + mumas); ++j)
        {
          sum += fmas(i - j + mbdiag, j) * ff(j);
        }
      ff(i + n) = sum;
      cont(i) = sum + y0(i);
    }
  decsol::solb(n, lde1, e1, mle, mue, cont, ip1);
  goto statement_77;
//C
statement_14:
  //C ------  B IS A BANDED MATRIX, JACOBIAN A BANDED MATRIX, SECOND ORDER
  // FEM_DO_SAFE(i, 1, m1)
  for (integer i = 1; i <= m1; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(k, 1, ns)
      for (integer k = 1; k <= ns; ++k)
        {
          sum += dd(k) * zz(i + (k - 1) * n);
        }
      ff(i + n) = sum / h;
      cont(i) = ff(i + n) + y0(i);
    }
  // FEM_DO_SAFE(i, m1 + 1, n)
  for (integer i = m1 + 1; i <= n; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(k, 1, ns)
      for (integer k = 1; k <= ns; ++k)
        {
          sum += dd(k) * zz(i + (k - 1) * n);
        }
      ff(i) = sum / h;
    }
  // FEM_DO_SAFE(i, 1, nm1)
  for (integer i = 1; i <= nm1; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(j, std::max(c__1, i - mlmas), std::min(nm1, i + mumas))
      for (integer j = std::max(c__1, i - mlmas); j <= std::min(nm1, i + mumas); ++j)
        {
          sum += fmas(i - j + mbdiag, j) * ff(j + m1);
        }
      im1 = i + m1;
      ff(im1 + n) = sum;
      cont(im1) = sum + y0(im1);
    }
  goto statement_45;
//C
statement_5:
  //C ------  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(k, 1, ns)
      for (integer k = 1; k <= ns; ++k)
        {
          sum += dd(k) * zz(i + (k - 1) * n);
        }
      ff(i) = sum / h;
    }
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(j, 1, n)
      for (integer j = 1; j <= n; ++j)
        {
          sum += fmas(i, j) * ff(j);
        }
      ff(i + n) = sum;
      cont(i) = sum + y0(i);
    }
  decsol::sol(n, lde1, e1, cont, ip1);
  goto statement_77;
//C
statement_15:
  //C ------  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER
  // FEM_DO_SAFE(i, 1, m1)
  for (integer i = 1; i <= m1; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(k, 1, ns)
      for (integer k = 1; k <= ns; ++k)
        {
          sum += dd(k) * zz(i + (k - 1) * n);
        }
      ff(i + n) = sum / h;
      cont(i) = ff(i + n) + y0(i);
    }
  // FEM_DO_SAFE(i, m1 + 1, n)
  for (integer i = m1 + 1; i <= n; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(k, 1, ns)
      for (integer k = 1; k <= ns; ++k)
        {
          sum += dd(k) * zz(i + (k - 1) * n);
        }
      ff(i) = sum / h;
    }
  // FEM_DO_SAFE(i, 1, nm1)
  for (integer i = 1; i <= nm1; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(j, 1, nm1)
      for (integer j = 1; j <= nm1; ++j)
        {
          sum += fmas(i, j) * ff(j + m1);
        }
      im1 = i + m1;
      ff(im1 + n) = sum;
      cont(im1) = sum + y0(im1);
    }
  goto statement_48;
//C
statement_6:
  //C ------  B IS A FULL MATRIX, JACOBIAN A BANDED MATRIX
  //C ------  THIS OPTION IS NOT PROVIDED
  return;
//C
statement_7:
  //C ------  B=IDENTITY, JACOBIAN A FULL MATRIX, HESSENBERG-OPTION
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      sum = 0.e0;
      // FEM_DO_SAFE(k, 1, ns)
      for (integer k = 1; k <= ns; ++k)
        {
          sum += dd(k) * zz(i + (k - 1) * n);
        }
      ff(i + n) = sum / h;
      cont(i) = ff(i + n) + y0(i);
    }
  // FEM_DOSTEP(mm, n - 2, 1, -1)
  for (integer mm = n - 2; mm >= 1; --mm)
    {
      mp = n - mm;
      i = iphes(mp);
      if (i == mp)
        {
          goto statement_310;
        }
      zsafe = cont(mp);
      cont(mp) = cont(i);
      cont(i) = zsafe;
    statement_310:
      // FEM_DO_SAFE(i, mp + 1, n)
      for (integer i = mp + 1; i <= n; ++i)
        {
          cont(i) = cont(i) - fjac(i, mp - 1) * cont(mp);
        }
    }
  decsol::solh(n, lde1, e1, 1, cont, ip1);
  // FEM_DO_SAFE(mm, 1, n - 2)
  for (integer mm = 1; mm <= n - 2; ++mm)
    {
      mp = n - mm;
      // FEM_DO_SAFE(i, mp + 1, n)
      for (integer i = mp + 1; i <= n; ++i)
        {
          cont(i) += fjac(i, mp - 1) * cont(mp);
        }
      i = iphes(mp);
      if (i == mp)
        {
          goto statement_440;
        }
      zsafe = cont(mp);
      cont(mp) = cont(i);
      cont(i) = zsafe;
    statement_440:;
    }
//C
//C --------------------------------------
//C
statement_77:
  err = 0.e0;
  // FEM_DO_SAFE(i, 1, n)
  for (integer i = 1; i <= n; ++i)
    {
      err += pow2((cont(i) / scal(i)));
    }
  err = std::max(std::sqrt(err / n), 1.e-10);
  //C
  if (err < 1.e0)
    {
      return;
    }
  if (first || reject)
    {
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          cont(i) += y(i);
        }
      fcn(n, x, cont, ff, rpar, ipar);
      nfcn++;
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          cont(i) = ff(i) + ff(i + n);
        }
      switch (ijob)
        {
        case 1:
          goto statement_31;
        case 2:
          goto statement_32;
        case 3:
          goto statement_31;
        case 4:
          goto statement_32;
        case 5:
          goto statement_31;
        case 6:
          goto statement_32;
        case 7:
          goto statement_33;
        case 8:
          goto statement_55;
        case 9:
          goto statement_55;
        case 10:
          goto statement_55;
        case 11:
          goto statement_41;
        case 12:
          goto statement_42;
        case 13:
          goto statement_41;
        case 14:
          goto statement_42;
        case 15:
          goto statement_41;
        default:
          break;
        }
    //C ------ FULL MATRIX OPTION
    statement_31:
      decsol::sol(n, lde1, e1, cont, ip1);
      goto statement_88;
    //C ------ FULL MATRIX OPTION, SECOND ORDER
    statement_41:
      // FEM_DO_SAFE(j, 1, m2)
      for (integer j = 1; j <= m2; ++j)
        {
          sum1 = 0.e0;
          // FEM_DOSTEP(k, mm - 1, 0, -1)
          for (integer k = mm - 1; k >= 0; --k)
            {
              sum1 = (cont(j + k * m2) + sum1) / fac1;
              // FEM_DO_SAFE(i, 1, nm1)
              for (integer i = 1; i <= nm1; ++i)
                {
                  im1 = i + m1;
                  cont(im1) += fjac(i, j + k * m2) * sum1;
                }
            }
        }
      decsol::sol(nm1, lde1, e1, cont(m1 + 1), ip1);
      // FEM_DOSTEP(i, m1, 1, -1)
      for (integer i = m1; i >= 1; --i)
        {
          cont(i) = (cont(i) + cont(m2 + i)) / fac1;
        }
      goto statement_88;
    //C ------ BANDED MATRIX OPTION
    statement_32:
      decsol::solb(n, lde1, e1, mle, mue, cont, ip1);
      goto statement_88;
    //C ------ BANDED MATRIX OPTION, SECOND ORDER
    statement_42:
      // FEM_DO_SAFE(j, 1, m2)
      for (integer j = 1; j <= m2; ++j)
        {
          sum1 = 0.e0;
          // FEM_DOSTEP(k, mm - 1, 0, -1)
          for (integer k = mm - 1; k >= 0; --k)
            {
              sum1 = (cont(j + k * m2) + sum1) / fac1;
              //FEM_DO_SAFE(i, std::max(c__1, j - mujac), std::min(nm1, j + mljac))
              for (integer i = std::max(c__1, j - mujac); i <= std::min(nm1, j + mljac); ++i)
                {
                  im1 = i + m1;
                  cont(im1) += fjac(i + mujac + 1 - j, j + k * m2) * sum1;
                }
            }
        }
      decsol::solb(nm1, lde1, e1, mle, mue, cont(m1 + 1), ip1);
      // FEM_DOSTEP(i, m1, 1, -1)
      for (integer i = m1; i >= 1; --i)
        {
          cont(i) = (cont(i) + cont(m2 + i)) / fac1;
        }
      goto statement_88;
    //C ------ HESSENBERG MATRIX OPTION
    statement_33:
      // FEM_DOSTEP(mm, n - 2, 1, -1)
      for (integer mm = n - 2; mm >= 1; --mm)
        {
          mp = n - mm;
          i = iphes(mp);
          if (i == mp)
            {
              goto statement_510;
            }
          zsafe = cont(mp);
          cont(mp) = cont(i);
          cont(i) = zsafe;
        statement_510:
          // FEM_DO_SAFE(i, mp + 1, n)
          for (integer i = mp + 1; i <= n; ++i)
            {
              cont(i) = cont(i) - fjac(i, mp - 1) * cont(mp);
            }
        }
      decsol::solh(n, lde1, e1, 1, cont, ip1);
      // FEM_DO_SAFE(mm, 1, n - 2)
      for (integer mm = 1; mm <= n - 2; ++mm)
        {
          mp = n - mm;
          // FEM_DO_SAFE(i, mp + 1, n)
          for (integer i = mp + 1; i <= n; ++i)
            {
              cont(i) += fjac(i, mp - 1) * cont(mp);
            }
          i = iphes(mp);
          if (i == mp)
            {
              goto statement_640;
            }
          zsafe = cont(mp);
          cont(mp) = cont(i);
          cont(i) = zsafe;
        statement_640:;
        }
    //C -----------------------------------
    statement_88:
      err = 0.e0;
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          err += pow2((cont(i) / scal(i)));
        }
      err = std::max(std::sqrt(err / n), 1.e-10);
    }
  return;
//C
//C -----------------------------------------------------------
//C
statement_55:;
}

//C
//C     END OF SUBROUTINE ESTRAV
//C
//C ***********************************************************
//C
void _dc_decsol::slvrod(common & cmn,
                        const integer & n,
                        const CFortranAccess< CMatrix< doublereal > > & fjac,
                        const integer & ldjac,
                        const integer & mljac,
                        const integer & mujac,
                        const CFortranAccess< CMatrix< doublereal > > & fmas,
                        const integer & ldmas,
                        const integer & mlmas,
                        const integer & mumas,
                        const integer & m1,
                        const integer & m2,
                        const integer & nm1,
                        const doublereal & fac1,
                        const CFortranAccess< CMatrix< doublereal > > & e,
                        const integer & lde,
                        const CVectorCore< integer > & ip,
                        const CVectorCore< doublereal > & dy,
                        CVectorCore< doublereal > & ak,
                        const CVectorCore< doublereal > & fx,
                        const CVectorCore< doublereal > & ynew,
                        const doublereal & hd,
                        const integer & ijob,
                        bool const & stage1)
{
  integer & mle = cmn.mle;
  integer & mue = cmn.mue;
  integer & mbdiag = cmn.mbdiag;
  //
  integer i = 0;
  integer mm = 0;
  integer j = 0;
  doublereal sum = 0.0;
  integer k = 0;
  integer jkm = 0;
  integer im1 = 0;
  //C
  if (hd == 0.e0)
    {
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          ak(i) = dy(i);
        }
    }
  else
    {
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          ak(i) = dy(i) + hd * fx(i);
        }
    }
  //C
  switch (ijob)
    {
    case 1:
      goto statement_1;
    case 2:
      goto statement_2;
    case 3:
      goto statement_3;
    case 4:
      goto statement_4;
    case 5:
      goto statement_5;
    case 6:
      goto statement_6;
    case 7:
      goto statement_55;
    case 8:
      goto statement_55;
    case 9:
      goto statement_55;
    case 10:
      goto statement_55;
    case 11:
      goto statement_11;
    case 12:
      goto statement_12;
    case 13:
      goto statement_13;
    case 14:
      goto statement_13;
    case 15:
      goto statement_15;
    default:
      break;
    }
//C
//C -----------------------------------------------------------
//C
statement_1:
  //C ---  B=IDENTITY, JACOBIAN A FULL MATRIX
  if (stage1)
    {
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          ak(i) += ynew(i);
        }
    }
  decsol::sol(n, lde, e, ak, ip);
  return;
//C
//C -----------------------------------------------------------
//C
statement_11:
  //C ---  B=IDENTITY, JACOBIAN A FULL MATRIX, SECOND ORDER
  if (stage1)
    {
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          ak(i) += ynew(i);
        }
    }
statement_48:
  mm = m1 / m2;
  // FEM_DO_SAFE(j, 1, m2)
  for (integer j = 1; j <= m2; ++j)
    {
      sum = 0.e0;
      // FEM_DOSTEP(k, mm - 1, 0, -1)
      for (integer k = mm - 1; k >= 0; --k)
        {
          jkm = j + k * m2;
          sum = (ak(jkm) + sum) / fac1;
          // FEM_DO_SAFE(i, 1, nm1)
          for (integer i = 1; i <= nm1; ++i)
            {
              im1 = i + m1;
              ak(im1) += fjac(i, jkm) * sum;
            }
        }
    }
  decsol::sol(nm1, lde, e, ak(m1 + 1), ip);
  // FEM_DOSTEP(i, m1, 1, -1)
  for (integer i = m1; i >= 1; --i)
    {
      ak(i) = (ak(i) + ak(m2 + i)) / fac1;
    }
  return;
//C
//C -----------------------------------------------------------
//C
statement_2:
  //C ---  B=IDENTITY, JACOBIAN A BANDED MATRIX
  if (stage1)
    {
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          ak(i) += ynew(i);
        }
    }
  decsol::solb(n, lde, e, mle, mue, ak, ip);
  return;
//C
//C -----------------------------------------------------------
//C
statement_12:
  //C ---  B=IDENTITY, JACOBIAN A BANDED MATRIX, SECOND ORDER
  if (stage1)
    {
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          ak(i) += ynew(i);
        }
    }
statement_45:
  mm = m1 / m2;
  // FEM_DO_SAFE(j, 1, m2)
  for (integer j = 1; j <= m2; ++j)
    {
      sum = 0.e0;
      // FEM_DOSTEP(k, mm - 1, 0, -1)
      for (integer k = mm - 1; k >= 0; --k)
        {
          jkm = j + k * m2;
          sum = (ak(jkm) + sum) / fac1;
          // FEM_DO_SAFE(i, std::max(c__1, j - mujac), std::min(nm1, j + mljac))
          for (integer i = std::max(c__1, j - mujac); i <= std::min(nm1, j + mljac); ++i)
            {
              im1 = i + m1;
              ak(im1) += fjac(i + mujac + 1 - j, jkm) * sum;
            }
        }
    }
  decsol::solb(nm1, lde, e, mle, mue, ak(m1 + 1), ip);
  // FEM_DOSTEP(i, m1, 1, -1)
  for (integer i = m1; i >= 1; --i)
    {
      ak(i) = (ak(i) + ak(m2 + i)) / fac1;
    }
  return;
//C
//C -----------------------------------------------------------
//C
statement_3:
  //C ---  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX
  if (stage1)
    {
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          sum = 0.e0;
          // FEM_DO_SAFE(j, std::max(c__1, i - mlmas), std::min(n, i + mumas))
          for (integer j = std::max(c__1, i - mlmas); j <= std::min(n, i + mumas); ++j)
            {
              sum += fmas(i - j + mbdiag, j) * ynew(j);
            }
          ak(i) += sum;
        }
    }
  decsol::sol(n, lde, e, ak, ip);
  return;
//C
//C -----------------------------------------------------------
//C
statement_13:
  //C ---  B IS A BANDED MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER
  if (stage1)
    {
      // FEM_DO_SAFE(i, 1, m1)
      for (integer i = 1; i <= m1; ++i)
        {
          ak(i) += ynew(i);
        }
      // FEM_DO_SAFE(i, 1, nm1)
      for (integer i = 1; i <= nm1; ++i)
        {
          sum = 0.e0;
          // FEM_DO_SAFE(j, std::max(c__1, i - mlmas), std::min(nm1, i + mumas))
          for (integer j = std::max(c__1, i - mlmas); j <= std::min(nm1, i + mumas); ++j)
            {
              sum += fmas(i - j + mbdiag, j) * ynew(j + m1);
            }
          im1 = i + m1;
          ak(im1) += sum;
        }
    }
  if (ijob == 14)
    {
      goto statement_45;
    }
  goto statement_48;
//C
//C -----------------------------------------------------------
//C
statement_4:
  //C ---  B IS A BANDED MATRIX, JACOBIAN A BANDED MATRIX
  if (stage1)
    {
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          sum = 0.e0;
          // FEM_DO_SAFE(j, std::max(c__1, i - mlmas), std::min(n, i + mumas))
          for (integer j = std::max(c__1, i - mlmas); j <= std::min(n, i + mumas); ++j)
            {
              sum += fmas(i - j + mbdiag, j) * ynew(j);
            }
          ak(i) += sum;
        }
    }
  decsol::solb(n, lde, e, mle, mue, ak, ip);
  return;
//C
//C -----------------------------------------------------------
//C
statement_5:
  //C ---  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX
  if (stage1)
    {
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          sum = 0.e0;
          // FEM_DO_SAFE(j, 1, n)
          for (integer j = 1; j <= n; ++j)
            {
              sum += fmas(i, j) * ynew(j);
            }
          ak(i) += sum;
        }
    }
  decsol::sol(n, lde, e, ak, ip);
  return;
//C
//C -----------------------------------------------------------
//C
statement_15:
  //C ---  B IS A FULL MATRIX, JACOBIAN A FULL MATRIX, SECOND ORDER
  if (stage1)
    {
      // FEM_DO_SAFE(i, 1, m1)
      for (integer i = 1; i <= m1; ++i)
        {
          ak(i) += ynew(i);
        }
      // FEM_DO_SAFE(i, 1, nm1)
      for (integer i = 1; i <= nm1; ++i)
        {
          sum = 0.e0;
          // FEM_DO_SAFE(j, 1, nm1)
          for (integer j = 1; j <= nm1; ++j)
            {
              sum += fmas(i, j) * ynew(j + m1);
            }
          im1 = i + m1;
          ak(im1) += sum;
        }
    }
  goto statement_48;
//C
//C -----------------------------------------------------------
//C
statement_6:
  //C ---  B IS A FULL MATRIX, JACOBIAN A BANDED MATRIX
  //C ---  THIS OPTION IS NOT PROVIDED
  if (stage1)
    {
      // FEM_DO_SAFE(i, 1, n)
      for (integer i = 1; i <= n; ++i)
        {
          sum = 0.e0;
          // FEM_DO_SAFE(j, 1, n)
          for (integer j = 1; j <= n; ++j)
            {
              sum += fmas(i, j) * ynew(j);
            }
          ak(i) += sum;
        }
      decsol::solb(n, lde, e, mle, mue, ak, ip);
    }
  return;
//C
//C -----------------------------------------------------------
//C
statement_55:;
}

//C
//C     END OF SUBROUTINE SLVROD
//C
//C ***********************************************************
//C
void _dc_decsol::slvseu(common & cmn,
                        const integer & n,
                        const CFortranAccess< CMatrix< doublereal > > & fjac,
                        const integer & ldjac,
                        const integer & mljac,
                        const integer & mujac,
                        const CFortranAccess< CMatrix< doublereal > > & /* fmas */,
                        const integer & ldmas,
                        const integer & /* mlmas */,
                        const integer & /* mumas */,
                        const integer & m1,
                        const integer & m2,
                        const integer & nm1,
                        const doublereal & fac1,
                        const CFortranAccess< CMatrix< doublereal > > & e,
                        const integer & lde,
                        const CVectorCore< integer > & ip,
                        const CVectorCore< integer > & iphes,
                        CVectorCore< doublereal > & del,
                        const integer & ijob)
{
  integer & mle = cmn.mle;
  integer & mue = cmn.mue;
  //
  integer mm = 0;
  integer j = 0;
  doublereal sum = 0.0;
  integer k = 0;
  integer jkm = 0;
  integer i = 0;
  integer im1 = 0;
  integer mmm = 0;
  integer mp = 0;
  integer mp1 = 0;
  doublereal zsafe = 0.0;
  //C
  switch (ijob)
    {
    case 1:
      goto statement_1;
    case 2:
      goto statement_2;
    case 3:
      goto statement_1;
    case 4:
      goto statement_2;
    case 5:
      goto statement_1;
    case 6:
      goto statement_55;
    case 7:
      goto statement_7;
    case 8:
      goto statement_55;
    case 9:
      goto statement_55;
    case 10:
      goto statement_55;
    case 11:
      goto statement_11;
    case 12:
      goto statement_12;
    case 13:
      goto statement_11;
    case 14:
      goto statement_12;
    case 15:
      goto statement_11;
    default:
      break;
    }
//C
//C -----------------------------------------------------------
//C
statement_1:
  //C ---  B=IDENTITY, JACOBIAN A FULL MATRIX
  decsol::sol(n, lde, e, del, ip);
  return;
//C
//C -----------------------------------------------------------
//C
statement_11:
  //C ---  B=IDENTITY, JACOBIAN A FULL MATRIX, SECOND ORDER
  mm = m1 / m2;
  // FEM_DO_SAFE(j, 1, m2)
  for (integer j = 1; j <= m2; ++j)
    {
      sum = 0.e0;
      // FEM_DOSTEP(k, mm - 1, 0, -1)
      for (integer k = mm - 1; k >= 0; --k)
        {
          jkm = j + k * m2;
          sum = (del(jkm) + sum) / fac1;
          // FEM_DO_SAFE(i, 1, nm1)
          for (integer i = 1; i <= nm1; ++i)
            {
              im1 = i + m1;
              del(im1) += fjac(i, jkm) * sum;
            }
        }
    }
  decsol::sol(nm1, lde, e, del(m1 + 1), ip);
  // FEM_DOSTEP(i, m1, 1, -1)
  for (integer i = m1; i >= 1; --i)
    {
      del(i) = (del(i) + del(m2 + i)) / fac1;
    }
  return;
//C
//C -----------------------------------------------------------
//C
statement_2:
  //C ---  B=IDENTITY, JACOBIAN A BANDED MATRIX
  decsol::solb(n, lde, e, mle, mue, del, ip);
  return;
//C
//C -----------------------------------------------------------
//C
statement_12:
  //C ---  B=IDENTITY, JACOBIAN A BANDED MATRIX, SECOND ORDER
  mm = m1 / m2;
  // FEM_DO_SAFE(j, 1, m2)
  for (integer j = 1; j <= m2; ++j)
    {
      sum = 0.e0;
      // FEM_DOSTEP(k, mm - 1, 0, -1)
      for (integer k = mm - 1; k >= 0; --k)
        {
          jkm = j + k * m2;
          sum = (del(jkm) + sum) / fac1;
          // FEM_DO_SAFE(i, std::max(c__1, j - mujac), std::min(nm1, j + mljac))
          for (integer i = std::max(c__1, j - mujac); i <= std::min(nm1, j + mljac); ++i)
            {
              im1 = i + m1;
              del(im1) += fjac(i + mujac + 1 - j, jkm) * sum;
            }
        }
    }
  decsol::solb(nm1, lde, e, mle, mue, del(m1 + 1), ip);
  // FEM_DOSTEP(i, m1, 1, -1)
  for (integer i = m1; i >= 1; --i)
    {
      del(i) = (del(i) + del(m2 + i)) / fac1;
    }
  return;
//C
//C -----------------------------------------------------------
//C
statement_7:
  //C ---  HESSENBERG OPTION
  // FEM_DOSTEP(mmm, n - 2, 1, -1)
  for (integer mmm = n - 2; mmm >= 1; --mmm)
    {
      mp = n - mmm;
      mp1 = mp - 1;
      i = iphes(mp);
      if (i == mp)
        {
          goto statement_110;
        }
      zsafe = del(mp);
      del(mp) = del(i);
      del(i) = zsafe;
    statement_110:
      // FEM_DO_SAFE(i, mp + 1, n)
      for (integer i = mp + 1; i <= n; ++i)
        {
          del(i) = del(i) - fjac(i, mp1) * del(mp);
        }
    }
  decsol::solh(n, lde, e, 1, del, ip);
  // FEM_DO_SAFE(mmm, 1, n - 2)
  for (integer mmm = 1; mmm <= n - 2; ++mmm)
    {
      mp = n - mmm;
      mp1 = mp - 1;
      // FEM_DO_SAFE(i, mp + 1, n)
      for (integer i = mp + 1; i <= n; ++i)
        {
          del(i) += fjac(i, mp1) * del(mp);
        }
      i = iphes(mp);
      if (i == mp)
        {
          goto statement_240;
        }
      zsafe = del(mp);
      del(mp) = del(i);
      del(i) = zsafe;
    statement_240:;
    }
  return;
//C
//C -----------------------------------------------------------
//C
statement_55:;
}
//C
//C     END OF SUBROUTINE SLVSEU
//C
