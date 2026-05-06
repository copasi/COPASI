// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// fingerprinteger 82cacaf2e5c6720236bce779c7c8468f
#pragma once

#include "copasi/odepack++/decsol.h"

#include "copasi/core/CVector.h"
#include "copasi/core/CMatrix.h"

namespace dc_sumexpdel
{
template < typename T >
inline T pow2(T const & base)
{
  return base * base;
}

template < typename T >
inline double dabs(T const & d)
{
  return d < 0 ? -d : d;
}

struct linear_algebra
{
  integer mle;
  integer mue;
  integer mbjac;
  integer mbb;
  integer mdiag;
  integer mdiff;
  integer mbdiag;

  linear_algebra()
    : mle(0)
    , mue(0)
    , mbjac(0)
    , mbb(0)
    , mdiag(0)
    , mdiff(0)
    , mbdiag(0){};
};

struct common : linear_algebra
{
  common()
    : linear_algebra(){};
};

//C ******************************************
//C     VERSION OF March 5, 2024
//C ******************************************
//C
void decomr(const common & cmn,
            const integer & n,
            const CMatrix< double > & fjac,
            const integer & ldjac,
            const CMatrix< double > & fmas,
            const integer & ldmas,
            const integer & /* mlmas */,
            const integer & /* mumas */,
            const integer & /* m1 */,
            const integer & /* m2 */,
            const integer & nm1,
            const double & fac1,
            CMatrix< double > & e1,
            const integer & lde1,
            CVectorCore< integer > & ip1,
            integer & ier,
            const integer & ijob,
            bool const & /* calhes */,
            const CVectorCore< integer > & /* iphes */);

void decomc(const common & cmn,
            const integer & n,
            const CMatrix< double > & fjac,
            const integer & ldjac,
            const CMatrix< double > & fmas,
            const integer & ldmas,
            const integer & /* mlmas */,
            const integer & /* mumas */,
            const integer & /* m1 */,
            const integer & /* m2 */,
            const integer & nm1,
            const double & alphn,
            const double & betan,
            CMatrix< double > & e2r,
            CMatrix< double > & e2i,
            const integer & lde1,
            CVectorCore< integer > & ip2,
            integer & ier,
            const integer & ijob);

void solexp(const integer & n,
            const CMatrix< double > & fjac,
            const integer & ldjac,
            const integer & mujac,
            const integer & nm1,
            const integer & lde1,
            const CMatrix< double > & e1,
            CVectorCore< double > & z1,
            const CVectorCore< integer > & ip1,
            const double & fac1,
            const integer & /* ijob */);

void solexpc(const integer & n,
             const CMatrix< double > & fjac,
             const integer & ldjac,
             const integer & mujac,
             const integer & nm1,
             const integer & lde1,
             const CMatrix< double > & e2r,
             const CMatrix< double > & e2i,
             CVectorCore< double > & z2,
             CVectorCore< double > & z3,
             const CVectorCore< integer > & /* ip1 */,
             const CVectorCore< integer > & ip2,
             const double & alphn,
             const double & betan,
             const integer & /* ijob */);

void slvrad(const common & cmn,
            const integer & n,
            const CMatrix< double > & fjac,
            const integer & ldjac,
            const integer & /* mljac */,
            const integer & /* mujac */,
            const CMatrix< double > & fmas,
            const integer & ldmas,
            const integer & /* mlmas */,
            const integer & /* mumas */,
            const integer & /* m1 */,
            const integer & /* m2 */,
            const integer & nm1,
            const double & fac1,
            const double & alphn,
            const double & betan,
            const CMatrix< double > & e1,
            const CMatrix< double > & e2r,
            const CMatrix< double > & e2i,
            const integer & lde1,
            CVectorCore< double > & z1,
            CVectorCore< double > & z2,
            CVectorCore< double > & z3,
            const CVectorCore< double > & f1,
            const CVectorCore< double > & f2,
            const CVectorCore< double > & f3,
            const CVectorCore< double > & /* cont */,
            const CVectorCore< integer > & ip1,
            const CVectorCore< integer > & ip2,
            const CVectorCore< integer > & /* iphes */,
            const integer & /* ier */,
            const integer & ijob);
} // namespace dc_sumexpdel
