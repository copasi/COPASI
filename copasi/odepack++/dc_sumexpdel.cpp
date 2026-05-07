// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// fingerprinteger 82cacaf2e5c6720236bce779c7c8468f
#include "copasi/odepack++/dc_sumexpdel.h"

//C ******************************************
//C     VERSION OF March 5, 2024
//C ******************************************
//C
void dc_sumexpdel::decomr(const common & cmn,
                          const integer & n,
                          const CMatrix< doublereal  > & fjac,
                          const integer & ldjac,
                          const CMatrix< doublereal  > & fmas,
                          const integer & ldmas,
                          const integer & /* mlmas */,
                          const integer & /* mumas */,
                          const integer & /* m1 */,
                          const integer & /* m2 */,
                          const integer & nm1,
                          const doublereal  & fac1,
                          CMatrix< doublereal  > & e1,
                          const integer & lde1,
                          CVectorCore< integer > & ip1,
                          integer & ier,
                          const integer & ijob,
                          bool const & /* calhes */,
                          const CVectorCore< integer > & /* iphes */)
{
  const integer & mbdiag = cmn.mbdiag;
  //
  integer j = 0;
  integer i = 0;
  integer nd = 0;
  doublereal  term = 0.0;
  doublereal  sum = 0.0;
  integer lexp = 0;
  integer ii = 0;
  doublereal  fact = 0.0;
  doublereal  cc = 0.0;
  doublereal  u1 = 0.0;
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
      goto statement_2;
    case 5:
      goto statement_55;
    case 6:
      goto statement_55;
    case 7:
      goto statement_55;
    case 8:
      goto statement_55;
    case 9:
      goto statement_55;
    case 10:
      goto statement_55;
    case 11:
      goto statement_2;
    case 12:
      goto statement_2;
    case 13:
      goto statement_55;
    case 14:
      goto statement_55;
    case 15:
      goto statement_55;
    default:
      break;
    }
//C
//C -----------------------------------------------------------
//C
statement_1:
  //C ---  B=IDENTITY, JACOBIAN A FULL MATRIX
  for (size_t j =  1; j <=  n; ++j) // FEM_DO_SAFE(j, 1, n)
  {
    for (size_t i =  1; i <=  n; ++i) // FEM_DO_SAFE(i, 1, n)
    {
      e1(i, j) = -fjac(i, j);
    }
    e1(j, j) += fac1;
  }
  dec_(&n, &lde1, e1.array(), ip1.array(), &ier);
  return;
//C
//C -----------------------------------------------------------
//C
statement_3:
  //C ---  B IS A DIAGONAL MATRIX, JACOBIAN A FULL MATRIX
  for (size_t j =  1; j <=  n; ++j) // FEM_DO_SAFE(j, 1, n)
  {
    for (size_t i =  1; i <=  n; ++i) // FEM_DO_SAFE(i, 1, n)
    {
      e1(i, j) = -fjac(i, j);
    }
    e1(j, j) += fac1 * fmas(mbdiag, j);
  }
  dec_(&n, &lde1, e1.array(), ip1.array(), &ier);
  return;
//C
//C -----------------------------------------------------------
//C
statement_2:
  //C ---  B = IDENTITY OR DIAGONAL, SUMEXP LINEAR ALGEBRA
  nd = cmn.mue + 1;
  term = fac1;
  for (size_t j =  1; j <=  nd; ++j) // FEM_DO_SAFE(j, 1, nd)
  {
    for (size_t i =  1; i <=  nd; ++i) // FEM_DO_SAFE(i, 1, nd)
    {
      e1(i, j) = -fjac(i, j);
    }
    if (ijob == 4)
      {
        term = fac1 * fmas(mbdiag, j);
      }
    e1(j, j) += term;
  }
  sum = 0.0;
  lexp = n - nd - 2;
  ii = nd + 2;
  for (size_t i =  1; i <=  lexp; ++i) // FEM_DO_SAFE(i, 1, lexp)
  {
    fact = fjac(3, ii);
    ii++;
    if (i == 1 || fact == 0.0)
      {
        cc = 1.0e0;
      }
    else
      {
        cc = fact * u1;
      }
    u1 = cc / (fac1 - fjac(2, ii));
    sum += fjac(1, ii) * u1;
  }
  for (size_t j =  1; j <=  nd; ++j) // FEM_DO_SAFE(j, 1, nd)
  {
    for (size_t i =  1; i <=  nd; ++i) // FEM_DO_SAFE(i, 1, nd)
    {
      e1(i, j) = e1(i, j) - sum * fjac(i, nd + 1) * fjac(j, nd + 2);
    }
  }
  dec_(&nd, &lde1, e1.array(), ip1.array(), &ier);
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
void dc_sumexpdel::decomc(const common & cmn,
                          const integer & n,
                          const CMatrix< doublereal  > & fjac,
                          const integer & ldjac,
                          const CMatrix< doublereal  > & fmas,
                          const integer & ldmas,
                          const integer & /* mlmas */,
                          const integer & /* mumas */,
                          const integer & /* m1 */,
                          const integer & /* m2 */,
                          const integer & nm1,
                          const doublereal  & alphn,
                          const doublereal  & betan,
                          CMatrix< doublereal  > & e2r,
                          CMatrix< doublereal  > & e2i,
                          const integer & lde1,
                          CVectorCore< integer > & ip2,
                          integer & ier,
                          const integer & ijob)
{
  const integer & mbdiag = cmn.mbdiag;
  //
  integer j = 0;
  integer i = 0;
  doublereal  bb = 0.0;
  integer nd = 0;
  integer lexp = 0;
  doublereal  sumr = 0.0;
  doublereal  sumi = 0.0;
  integer ii = 0;
  doublereal  fact = 0.0;
  doublereal  algam = 0.0;
  doublereal  denom = 0.0;
  doublereal  ur = 0.0;
  doublereal  ui = 0.0;
  doublereal  usave = 0.0;
  doublereal  prod = 0.0;
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
      goto statement_2;
    case 5:
      goto statement_55;
    case 6:
      goto statement_55;
    case 7:
      goto statement_55;
    case 8:
      goto statement_55;
    case 9:
      goto statement_55;
    case 10:
      goto statement_55;
    case 11:
      goto statement_2;
    case 12:
      goto statement_2;
    case 13:
      goto statement_55;
    case 14:
      goto statement_55;
    case 15:
      goto statement_55;
    default:
      break;
    }
//C
//C -----------------------------------------------------------
//C
statement_1:
  //C ---  B=IDENTITY, JACOBIAN A FULL MATRIX
  for (size_t j =  1; j <=  n; ++j) // FEM_DO_SAFE(j, 1, n)
  {
    for (size_t i =  1; i <=  n; ++i) // FEM_DO_SAFE(i, 1, n)
    {
      e2r(i, j) = -fjac(i, j);
      e2i(i, j) = 0.e0;
    }
    e2r(j, j) += alphn;
    e2i(j, j) = betan;
  }
  decc_(&n, &lde1, e2r.array(), e2i.array(), ip2.array(), &ier);
  return;
//C
//C -----------------------------------------------------------
//C
statement_3:
  //C ---  B IS A DIAGONAL MATRIX, JACOBIAN A FULL MATRIX
  for (size_t j =  1; j <=  n; ++j) // FEM_DO_SAFE(j, 1, n)
  {
    for (size_t i =  1; i <=  n; ++i) // FEM_DO_SAFE(i, 1, n)
    {
      e2r(i, j) = -fjac(i, j);
      e2i(i, j) = 0.e0;
    }
    bb = fmas(mbdiag, j);
    e2r(j, j) += alphn * bb;
    e2i(j, j) = betan * bb;
  }
  decc_(&n, &lde1, e2r.array(), e2i.array(), ip2.array(), &ier);
  return;
//C
//C -----------------------------------------------------------
//C
statement_2:
  //C ---  B = IDENTITY OR DIAGONAL, SUMEXP LINEAR ALGEBRA
  nd = cmn.mue + 1;
  bb = 1.0e0;
  for (size_t j =  1; j <=  nd; ++j) // FEM_DO_SAFE(j, 1, nd)
  {
    for (size_t i =  1; i <=  nd; ++i) // FEM_DO_SAFE(i, 1, nd)
    {
      e2r(i, j) = -fjac(i, j);
      e2i(i, j) = 0.e0;
    }
    if (ijob == 4)
      {
        bb = fmas(mbdiag, j);
      }
    e2r(j, j) += alphn * bb;
    e2i(j, j) = betan * bb;
  }
  lexp = n - nd - 2;
  sumr = 0.0;
  sumi = 0.0;
  ii = nd + 2;
  for (size_t i =  1; i <=  lexp; ++i) // FEM_DO_SAFE(i, 1, lexp)
  {
    ii++;
    fact = fjac(3, ii - 1);
    if (i == 1 || fact == 0.0)
      {
        algam = alphn - fjac(2, ii);
        denom = pow2(algam) + pow2(betan);
        ur = algam / denom;
        ui = -betan / denom;
      }
    else
      {
        usave = (ur * algam + ui * betan) / denom;
        ui = fact * (ui * algam - ur * betan) / denom;
        ur = fact * usave;
      }
    sumr += fjac(1, ii) * ur;
    sumi += fjac(1, ii) * ui;
  }
  for (size_t j =  1; j <=  nd; ++j) // FEM_DO_SAFE(j, 1, nd)
  {
    for (size_t i =  1; i <=  nd; ++i) // FEM_DO_SAFE(i, 1, nd)
    {
      prod = fjac(i, nd + 1) * fjac(j, nd + 2);
      e2r(i, j) = e2r(i, j) - sumr * prod;
      e2i(i, j) = e2i(i, j) - sumi * prod;
    }
  }
  decc_(&nd, &lde1, e2r.array(), e2i.array(), ip2.array(), &ier);
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
void dc_sumexpdel::solexp(const integer & n,
                          const CMatrix< doublereal  > & fjac,
                          const integer & ldjac,
                          const integer & mujac,
                          const integer & nm1,
                          const integer & lde1,
                          const CMatrix< doublereal  > & e1,
                          CVectorCore< doublereal  > & z1,
                          const CVectorCore< integer > & ip1,
                          const doublereal  & fac1,
                          const integer & /* ijob */)
{
  integer nd = mujac + 1;
  integer lexp = n - nd - 2;
  doublereal  sum = 0.0;
  integer ii = nd + 1;
  integer i = 0;
  doublereal  fact = 0.0;
  doublereal  fjinv = 0.0;
  doublereal  u1 = 0.0;
  for (size_t i =  1; i <=  lexp; ++i) // FEM_DO_SAFE(i, 1, lexp)
  {
    fact = fjac(3, ii + 1);
    if (i == 1 || fact == 0.0)
      {
        fjinv = 1.0e0 / (fac1 - fjac(2, ii + 2));
        u1 = z1(ii) * fjinv;
      }
    else
      {
        u1 = (z1(ii) + fact * u1) * fjinv;
      }
    sum += fjac(1, ii + 2) * u1;
    ii++;
  }
  integer nd1 = nd + 1;
  for (size_t i =  1; i <=  nd; ++i) // FEM_DO_SAFE(i, 1, nd)
  {
    z1(i) += sum * fjac(i, nd1);
  }
  sol_(&nd, &lde1, e1.array(), z1.array(), ip1.array());
  integer nd2 = nd + 2;
  doublereal  prod = 0.0;
  integer ipro = 0;
  for (size_t ipro =  1; ipro <=  nd; ++ipro) // FEM_DO_SAFE(ipro, 1, nd)
  {
    prod += fjac(ipro, nd2) * z1(ipro);
  }
  ii = nd + 1;
  for (size_t i =  1; i <=  lexp; ++i) // FEM_DO_SAFE(i, 1, lexp)
  {
    fact = fjac(3, ii + 1);
    if (i == 1 || fact == 0.0)
      {
        fjinv = 1.0e0 / (fac1 - fjac(2, ii + 2));
        z1(ii) = (z1(ii) + prod) * fjinv;
      }
    else
      {
        z1(ii) = (z1(ii) + fact * z1(ii - 1)) * fjinv;
      }
    ii++;
  }
  z1(n - 1) = 0.0;
  z1(n) = 0.0;
}

//C
//C     END OF SUBROUTINE SOLEXP
//C
//C ***********************************************************
//C
void dc_sumexpdel::solexpc(const integer & n,
                           const CMatrix< doublereal  > & fjac,
                           const integer & ldjac,
                           const integer & mujac,
                           const integer & nm1,
                           const integer & lde1,
                           const CMatrix< doublereal  > & e2r,
                           const CMatrix< doublereal  > & e2i,
                           CVectorCore< doublereal  > & z2,
                           CVectorCore< doublereal  > & z3,
                           const CVectorCore< integer > & /* ip1 */,
                           const CVectorCore< integer > & ip2,
                           const doublereal  & alphn,
                           const doublereal  & betan,
                           const integer & /* ijob */)
{
  integer nd = mujac + 1;
  integer lexp = n - nd - 2;
  integer ii = nd + 1;
  doublereal  sumr = 0.0;
  doublereal  sumi = 0.0;
  integer i = 0;
  doublereal  fact = 0.0;
  doublereal  algam = 0.0;
  doublereal  denom = 0.0;
  doublereal  ur = 0.0;
  doublereal  ui = 0.0;
  doublereal  usave = 0.0;
  for (size_t i =  1; i <=  lexp; ++i) // FEM_DO_SAFE(i, 1, lexp)
  {
    fact = fjac(3, ii + 1);
    if (i == 1 || fact == 0.0)
      {
        algam = alphn - fjac(2, ii + 2);
        denom = pow2(algam) + pow2(betan);
        ur = (z2(ii) * algam + z3(ii) * betan) / denom;
        ui = (z3(ii) * algam - z2(ii) * betan) / denom;
      }
    else
      {
        ur = fact * ur;
        ui = fact * ui;
        usave = ((z2(ii) + ur) * algam + (z3(ii) + ui) * betan) / denom;
        ui = ((z3(ii) + ui) * algam - (z2(ii) + ur) * betan) / denom;
        ur = usave;
      }
    sumr += fjac(1, ii + 2) * ur;
    sumi += fjac(1, ii + 2) * ui;
    ii++;
  }
  for (size_t i =  1; i <=  nd; ++i) // FEM_DO_SAFE(i, 1, nd)
  {
    z2(i) += sumr * fjac(i, nd + 1);
    z3(i) += sumi * fjac(i, nd + 1);
  }
  solc_(&nd, &lde1, e2r.array(), e2i.array(), z2.array(), z3.array(), ip2.array());
  integer nd2 = nd + 2;
  doublereal  prodr = 0.0;
  doublereal  prodi = 0.0;
  integer ipro = 0;
  for (size_t ipro =  1; ipro <=  nd; ++ipro) // FEM_DO_SAFE(ipro, 1, nd)
  {
    prodr += fjac(ipro, nd2) * z2(ipro);
    prodi += fjac(ipro, nd2) * z3(ipro);
  }
  ii = nd + 1;
  for (size_t i =  1; i <=  lexp; ++i) // FEM_DO_SAFE(i, 1, lexp)
  {
    fact = fjac(3, ii + 1);
    if (i == 1 || fact == 0.0)
      {
        algam = alphn - fjac(2, ii + 2);
        denom = pow2(algam) + pow2(betan);
        ur = ((z2(ii) + prodr) * algam + (z3(ii) + prodi) * betan) / denom;
        ui = ((z3(ii) + prodi) * algam - (z2(ii) + prodr) * betan) / denom;
      }
    else
      {
        ur = fact * ur;
        ui = fact * ui;
        usave = ((z2(ii) + ur) * algam + (z3(ii) + ui) * betan) / denom;
        ui = ((z3(ii) + ui) * algam - (z2(ii) + ur) * betan) / denom;
        ur = usave;
      }
    z2(ii) = ur;
    z3(ii) = ui;
    ii++;
  }
  z2(n - 1) = 0.0;
  z2(n) = 0.0;
  z3(n - 1) = 0.0;
  z3(n) = 0.0;
}

//C
//C     END OF SUBROUTINE DECOMC
//C
//C ***********************************************************
//C
void dc_sumexpdel::slvrad(const common & cmn,
                          const integer & n,
                          const CMatrix< doublereal  > & fjac,
                          const integer & ldjac,
                          const integer & /* mljac */,
                          const integer & /* mujac */,
                          const CMatrix< doublereal  > & fmas,
                          const integer & ldmas,
                          const integer & /* mlmas */,
                          const integer & /* mumas */,
                          const integer & /* m1 */,
                          const integer & /* m2 */,
                          const integer & nm1,
                          const doublereal  & fac1,
                          const doublereal  & alphn,
                          const doublereal  & betan,
                          const CMatrix< doublereal  > & e1,
                          const CMatrix< doublereal  > & e2r,
                          const CMatrix< doublereal  > & e2i,
                          const integer & lde1,
                          CVectorCore< doublereal  > & z1,
                          CVectorCore< doublereal  > & z2,
                          CVectorCore< doublereal  > & z3,
                          const CVectorCore< doublereal  > & f1,
                          const CVectorCore< doublereal  > & f2,
                          const CVectorCore< doublereal  > & f3,
                          const CVectorCore< doublereal  > & /* cont */,
                          const CVectorCore< integer > & ip1,
                          const CVectorCore< integer > & ip2,
                          const CVectorCore< integer > & /* iphes */,
                          const integer & /* ier */,
                          const integer & ijob)
{
  const integer & mue = cmn.mue;
  const integer & mbdiag = cmn.mbdiag;
  //
  integer i = 0;
  doublereal  s2 = 0.0;
  doublereal  s3 = 0.0;
  doublereal  bb = 0.0;
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
      goto statement_2;
    case 5:
      goto statement_55;
    case 6:
      goto statement_55;
    case 7:
      goto statement_55;
    case 8:
      goto statement_55;
    case 9:
      goto statement_55;
    case 10:
      goto statement_55;
    case 11:
      goto statement_2;
    case 12:
      goto statement_2;
    case 13:
      goto statement_55;
    case 14:
      goto statement_55;
    case 15:
      goto statement_55;
    default:
      break;
    }
//C
//C -----------------------------------------------------------
//C
statement_1:
  //C ---  B = IDENTITY, JACOBIAN A FULL MATRIX
  for (size_t i =  1; i <=  n; ++i) // FEM_DO_SAFE(i, 1, n)
  {
    s2 = -f2(i);
    s3 = -f3(i);
    z1(i) = z1(i) - f1(i) * fac1;
    z2(i) += s2 * alphn - s3 * betan;
    z3(i) += s3 * alphn + s2 * betan;
  }
  sol_(&n, &lde1, e1.array(), z1.array(), ip1.array());
  solc_(&n, &lde1, e2r.array(), e2i.array(), z2.array(), z3.array(), ip2.array());
  return;
//C
//C -----------------------------------------------------------
//C
statement_3:
  //C ---  B IS A DIAGONAL MATRIX, JACOBIAN A FULL MATRIX
  for (size_t i =  1; i <=  n; ++i) // FEM_DO_SAFE(i, 1, n)
  {
    bb = fmas(mbdiag, i);
    s2 = -bb * f2(i);
    s3 = -bb * f3(i);
    z1(i) = z1(i) - bb * f1(i) * fac1;
    z2(i) += s2 * alphn - s3 * betan;
    z3(i) += s3 * alphn + s2 * betan;
  }
  sol_(&n, &lde1, e1.array(), z1.array(), ip1.array());
  solc_(&n, &lde1, e2r.array(), e2i.array(), z2.array(), z3.array(), ip2.array());
  return;
//C
//C -----------------------------------------------------------
//C
statement_2:
  //C ---  B = IDENTITY, SUMEXP LINEAR ALGEBRA
  bb = 1.0e0;
  for (size_t i =  1; i <=  n; ++i) // FEM_DO_SAFE(i, 1, n)
  {
    if (ijob == 4)
      {
        bb = fmas(mbdiag, i);
      }
    s2 = -bb * f2(i);
    s3 = -bb * f3(i);
    z1(i) = z1(i) - bb * f1(i) * fac1;
    z2(i) += s2 * alphn - s3 * betan;
    z3(i) += s3 * alphn + s2 * betan;
  }
  solexp(n, fjac, ldjac, mue, nm1, lde1, e1, z1, ip1, fac1, ijob);
  solexpc(n, fjac, ldjac, mue, nm1, lde1, e2r, e2i, z2, z3, ip1, ip2,
          alphn, betan, ijob);
  return;
//C
//C -----------------------------------------------------------
//C
statement_55:;
}
