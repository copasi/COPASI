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
template < typename __T >
inline __T __pow2(const __T & base)
{
  return base * base;
}

template < typename __T >
inline doublereal __dabs(const __T & d)
{
  return d < 0 ? -d : d;
}

struct linear_algebra
{
  integer mle = 0;
  integer mue = 0;
  integer mbjac = 0;
  integer mbb = 0;
  integer mdiag = 0;
  integer mdiff = 0;
  integer mbdiag = 0;
};

struct common : linear_algebra
{};

//C ******************************************
//C     VERSION OF March 5, 2024
//C ******************************************
//C
void decomr(const common & cmn,
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
            const CVectorCore< integer > & /* iphes */);

void decomc(const common & cmn,
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
            const integer & ijob);

void solexp(const integer & n,
            const CMatrix< doublereal  > & fjac,
            const integer & ldjac,
            const integer & mujac,
            const integer & nm1,
            const integer & lde1,
            const CMatrix< doublereal  > & e1,
            CVectorCore< doublereal  > & z1,
            const CVectorCore< integer > & ip1,
            const doublereal  & fac1,
            const integer & /* ijob */);

void solexpc(const integer & n,
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
             const integer & /* ijob */);

void slvrad(const common & cmn,
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
            const integer & ijob);
} // namespace dc_sumexpdel
