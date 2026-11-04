// Copyright (C) 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

//
//  decsol.h
//  Radau5
//
//  Created by Abhishekh Gupta on 1/9/19.
//  Copyright © 2019 Abhishekh Gupta. All rights reserved.
//

#pragma once

#include <cmath>
#include "copasi/core/CCore.h"

#ifdef HAVE_F2C_H
#  include <f2c.h>
#else
#  include "copasi/lapack/f2c.h"
#endif

#ifdef min
#  undef min
#endif // min

#ifdef max
#  undef max
#endif // max

#ifdef abs
#  undef abs
#endif // abs

#include "copasi/core/CVector.h"
#include "copasi/core/CMatrix.h"

namespace decsol
{
// Matrix Triangularization by Gaussian Elimination
void dec(const integer & n,
         const integer & ndim,
         CFortranAccess< CMatrix< doublereal > > & a,
         CVectorCore< integer > & ip,
         integer & ier);

// Solution of linear system A*x = b
void sol(const integer & n,
         const integer & ndim,
         const CFortranAccess< CMatrix< doublereal > > & a,
         CVectorCore< doublereal > & b,
         const CVectorCore< integer > & ip);

void sol(const integer & n,
         const integer & ndim,
         const CFortranAccess< CMatrix< doublereal > > & a,
         doublereal & b,
         const CVectorCore< integer > & ip);

// Matrix Triangularization by Gaussian Elimination of a Hessenberg
// matrix with lower bandwidth lb
void dech(const integer & n,
          const integer & ndim,
          CFortranAccess< CMatrix< doublereal > > & a,
          const integer & lb,
          CVectorCore< integer > & ip,
          integer & ier);

void solh(const integer & n,
          const integer & ndim,
          const CFortranAccess< CMatrix< doublereal > > & a,
          const integer & lb,
          CVectorCore< doublereal > & b,
          const CVectorCore< integer > & ip);

void decc(const integer & n,
          const integer & ndim,
          CFortranAccess< CMatrix< doublereal > > & ar,
          CFortranAccess< CMatrix< doublereal > > & ai,
          CVectorCore< integer > & ip,
          integer & ier);

void solc(const integer & n,
          const integer & ndim,
          const CFortranAccess< CMatrix< doublereal > > & ar,
          const CFortranAccess< CMatrix< doublereal > > & ai,
          CVectorCore< doublereal > & br,
          CVectorCore< doublereal > & bi,
          const CVectorCore< integer > & ip);

void solc(const integer & n,
          const integer & ndim,
          const CFortranAccess< CMatrix< doublereal > > & ar,
          const CFortranAccess< CMatrix< doublereal > > & ai,
          doublereal & br,
          doublereal & bi,
          const CVectorCore< integer > & ip);

void dechc(const integer & n,
           const integer & ndim,
           CFortranAccess< CMatrix< doublereal > > & ar,
           CFortranAccess< CMatrix< doublereal > > & ai,
           const integer & lb,
           CVectorCore< integer > & ip,
           integer & ier);

void solhc(const integer & n,
           const integer & ndim,
           const CFortranAccess< CMatrix< doublereal > > & ar,
           const CFortranAccess< CMatrix< doublereal > > & ai,
           const integer & lb,
           CVectorCore< doublereal > & br,
           CVectorCore< doublereal > & bi,
           const CVectorCore< integer > & ip);

void decb(const integer & n,
          const integer & ndim,
          CFortranAccess< CMatrix< doublereal > > & a,
          const integer & ml,
          const integer & mu,
          CVectorCore< integer > & ip,
          integer & ier);

void solb(const integer & n,
          const integer & ndim,
          const CFortranAccess< CMatrix< doublereal > > & a,
          const integer & ml,
          const integer & mu,
          CVectorCore< doublereal > & b,
          const CVectorCore< integer > & ip);

void solb(const integer & n,
          const integer & ndim,
          const CFortranAccess< CMatrix< doublereal > > & a,
          const integer & ml,
          const integer & mu,
          doublereal & b,
          const CVectorCore< integer > & ip);

void decbc(const integer & n,
           const integer & ndim,
           CFortranAccess< CMatrix< doublereal > > & ar,
           CFortranAccess< CMatrix< doublereal > > & ai,
           const integer & ml,
           const integer & mu,
           CVectorCore< integer > & ip,
           integer & ier);

void solbc(const integer & n,
           const integer & ndim,
           const CFortranAccess< CMatrix< doublereal > > & ar,
           const CFortranAccess< CMatrix< doublereal > > & ai,
           const integer & ml,
           const integer & mu,
           CVectorCore< doublereal > & br,
           CVectorCore< doublereal > & bi,
           const CVectorCore< integer > & ip);

void solbc(const integer & n,
           const integer & ndim,
           const CFortranAccess< CMatrix< doublereal > > & ar,
           const CFortranAccess< CMatrix< doublereal > > & ai,
           const integer & ml,
           const integer & mu,
           doublereal & br,
           doublereal & bi,
           const CVectorCore< integer > & ip);

void elmhes(const integer & nm,
            const integer & n,
            const integer & low,
            const integer & igh,
            CFortranAccess< CMatrix< doublereal > > & a,
            CVectorCore< integer > & identifier_int);
} // namespace decsol
