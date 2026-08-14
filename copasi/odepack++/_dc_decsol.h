// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

//
//  dc_decsol.h
//  Radau5
//
//  Created by Abhishekh Gupta on 1/9/19.
//  Copyright © 2019 Abhishekh Gupta. All rights reserved.
//

#pragma once

#include "copasi/odepack++/_decsol.h"

#include <functional>

namespace _dc_decsol
{
template < typename __T >
inline __T pow2(const __T & base)
{
  return base * base;
}

template < typename __T >
inline __T sign(const __T & a, const __T & b)
{
  __T x;
  x = (a >= 0 ? a : -a);
  return (b >= 0 ? x : -x);
}

// Common block variables
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

struct common : public linear_algebra
{};

//C     evalF       NAME (EXTERNAL) OF SUBROUTINE COMPUTING THE
//C                 VALUE OF F(X,Y):
//C                    SUBROUTINE evalF(N,X,Y,F,RPAR,IPAR)
//C                    DOUBLE PRECISION X,Y(N),F(N)
typedef std::function< void(const integer & i,
                            const doublereal & x,
                            const CVectorCore< doublereal > & y,
                            const CVectorCore< doublereal > & f,
                            const CVectorCore< doublereal > & rpar,
                            const CVectorCore< integer > & ipar) >
  evalF;

void decomr(common & cmn,
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
            CVectorCore< integer > & iphes);

void decomc(common & cmn,
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
            const integer & ijob);

VOID slvrar(common & cmn,
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
            const integer & ijob);

void slvrai(common & cmn,
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
            const integer & ijob);

void slvrad(common & cmn,
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
            const integer & ijob);

void estrad(common & cmn,
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
            const CVectorCore< integer > & ipar);

void estrav(common & cmn,
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
            const CVectorCore< integer > & ipar);

void slvrod(common & cmn,
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
            bool const & stage1);

void slvseu(common & cmn,
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
            const integer & ijob);
}; // namespace _dc_decsol
