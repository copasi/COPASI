// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the
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

#ifndef dc_decsol_h
#define dc_decsol_h

#include "decsol.h"

namespace dc_decsol
{
// Common block variables
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

struct common
{
  linear_algebra linal;

  common()
    : linal(){};
};

int decomr_(const common & cmn,
            const integer * n,
            doublereal * fjac,
            const integer * ldjac,
            const doublereal * fmas,
            const integer * ldmas,
            const integer * mlmas,
            const integer * mumas,
            const integer * m1,
            const integer * m2,
            const integer * nm1,
            const doublereal * fac1,
            doublereal * e1,
            const integer * lde1,
            integer * ip1,
            integer * ier,
            const integer * ijob,
            logical * calhes,
            integer * iphes);

int decomc_(const common & cmn,
            const integer * n,
            const doublereal * fjac,
            const integer * ldjac,
            const doublereal * fmas,
            const integer * ldmas,
            const integer * mlmas,
            const integer * mumas,
            const integer * m1,
            const integer * m2,
            const integer * nm1,
            const doublereal * alphn,
            const doublereal * betan,
            doublereal * e2r,
            doublereal * e2i,
            const integer * lde1,
            integer * ip2,
            integer * ier,
            const integer * ijob);

int slvrar_(const common & cmn,
            const integer * n,
            const doublereal * fjac,
            const integer * ldjac,
            const integer * mljac,
            const integer * mujac,
            const doublereal * fmas,
            const integer * ldmas,
            const integer * mlmas,
            const integer * mumas,
            const integer * m1,
            const integer * m2,
            const integer * nm1,
            const doublereal * fac1,
            const doublereal * e1,
            const integer * lde1,
            doublereal * z1,
            const doublereal * f1,
            const integer * ip1,
            const integer * iphes,
            const integer * /* ier */,
            const integer * ijob);

int slvrai_(const common & cmn,
            const integer * n,
            const doublereal * fjac,
            const integer * ldjac,
            const integer * mljac,
            const integer * mujac,
            const doublereal * fmas,
            const integer * ldmas,
            const integer * mlmas,
            const integer * mumas,
            const integer * m1,
            const integer * m2,
            const integer * nm1,
            const doublereal * alphn,
            const doublereal * betan,
            const doublereal * e2r,
            const doublereal * e2i,
            const integer * lde1,
            doublereal * z2,
            doublereal * z3,
            const doublereal * f2,
            const doublereal * f3,
            const doublereal * /* cont */,
            const integer * ip2,
            const integer * iphes,
            const integer * /* ier */,
            const integer * ijob);

int slvrad_(const common & cmn,
            const integer * n,
            const doublereal * fjac,
            const integer * ldjac,
            const integer * mljac,
            const integer * mujac,
            const doublereal * fmas,
            const integer * ldmas,
            const integer * mlmas,
            const integer * mumas,
            const integer * m1,
            const integer * m2,
            const integer * nm1,
            const doublereal * fac1,
            const doublereal * alphn,
            const doublereal * betan,
            const doublereal * e1,
            const doublereal * e2r,
            const doublereal * e2i,
            const integer * lde1,
            doublereal * z1,
            doublereal * z2,
            doublereal * z3,
            const doublereal * f1,
            const doublereal * f2,
            const doublereal * f3,
            const doublereal * /* cont */,
            const integer * ip1,
            const integer * ip2,
            const integer * iphes,
            const integer * /* ier */,
            const integer * ijob);

int estrav_(const common & cmn,
            integer * n,
            doublereal * fjac,
            integer * ldjac,
            integer * mljac,
            integer * mujac,
            doublereal * fmas,
            integer * ldmas,
            integer * mlmas,
            integer * mumas,
            doublereal * h__,
            doublereal * dd,
            S_fp fcn,
            integer * nfcn,
            doublereal * y0,
            doublereal * y,
            integer * ijob,
            doublereal * x,
            integer * m1,
            integer * m2,
            integer * nm1,
            integer * ns,
            integer * nns,
            doublereal * e1,
            integer * lde1,
            doublereal * zz,
            doublereal * cont,
            doublereal * ff,
            integer * ip1,
            integer * iphes,
            doublereal * scal,
            doublereal * err,
            logical * first,
            logical * reject,
            doublereal * fac1,
            doublereal * rpar,
            integer * ipar);

int slvrod_(const common & cmn,
            const integer * n,
            const doublereal * fjac,
            const integer * ldjac,
            const integer * mljac,
            const integer * mujac,
            const doublereal * fmas,
            const integer * ldmas,
            const integer * mlmas,
            const integer * mumas,
            const integer * m1,
            const integer * m2,
            const integer * nm1,
            const doublereal * fac1,
            const doublereal * e,
            const integer * lde,
            const integer * ip,
            const doublereal * dy,
            doublereal * ak,
            const doublereal * fx,
            const doublereal * ynew,
            const doublereal * hd,
            const integer * ijob,
            const logical * stage1);

int slvseu_(const common & cmn,
            const integer * n,
            const doublereal * fjac,
            const integer * ldjac,
            const integer * mljac,
            const integer * mujac,
            const doublereal * fmas,
            const integer * ldmas,
            const integer * /* mlmas */,
            const integer * /* mumas */,
            const integer * m1,
            const integer * m2,
            const integer * nm1,
            const doublereal * fac1,
            const doublereal * e,
            const integer * lde,
            const integer * ip,
            const integer * iphes,
            doublereal * del,
            const integer * ijob);
}; // namespace dc_decsol

#endif /* dc_decsol_h */
