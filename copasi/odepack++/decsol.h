// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the
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

#ifndef decsol_h
#define decsol_h

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

// Matrix Triangularization by Gaussian Elimination
int dec_(const integer * n,
         const integer * ndim,
         doublereal * a,
         integer * ip,
         integer * ier);

// Solution of linear system A*x = b
int sol_(const integer * n,
         const integer * ndim,
         const doublereal * a,
         doublereal * b,
         const integer * ip);

// Matrix Triangularization by Gaussian Elimination of a Hessenberg
// matrix with lower bandwidth lb
int dech_(const integer * n,
          const integer * ndim,
          doublereal * a,
          const integer * lb,
          integer * ip,
          integer * ier);

// Solution of linear system A*x = b -- Hessenberg matrix
int solh_(const integer * n,
          const integer * ndim,
          const doublereal * a,
          const integer * lb,
          doublereal * b,
          const integer * ip);

// Matrix Triangularization by Gaussian Elimination for complex matrices
int decc_(const integer * n,
          const integer * ndim,
          doublereal * ar,
          doublereal * ai,
          integer * ip,
          integer * ier);

// Solution of linear system A*x = b -- complex matrices
int solc_(const integer * n,
          const integer * ndim,
          const doublereal * ar,
          const doublereal * ai,
          doublereal * br,
          doublereal * bi,
          const integer * ip);

// Matrix Triangularization by Gaussian Elimination -- Hessenberg, complex
// matrices
int dechc_(const integer * n,
           const integer * ndim,
           doublereal * ar,
           doublereal * ai,
           const integer * lb,
           integer * ip,
           integer * ie);

// Solution of linear system A*x = b -- Hessenberg, complex matrices
int solhc_(const integer * n,
           const integer * ndim,
           const doublereal * ar,
           const doublereal * ai,
           const integer * lb,
           doublereal * br,
           doublereal * bi,
           const integer * ip);

//Matrix Triangularization by Gaussian Elimination -- banded matrix
int decb_(const integer * n,
          const integer * ndim,
          doublereal * a,
          const integer * ml,
          const integer * mu,
          integer * ip,
          integer * ier);

// Solution of linear system A*x = b -- banded matrix
int solb_(const integer * n,
          const integer * ndim,
          const doublereal * a,
          const integer * ml,
          const integer * mu,
          doublereal * b,
          const integer * ip);

//Matrix Triangularization by Gaussian Elimination -- banded, complex matrices
int decbc_(const integer * n,
           const integer * ndim,
           doublereal * ar,
           doublereal * ai,
           const integer * ml,
           const integer * mu,
           integer * ip,
           integer * ier);

// Solution of linear system A*x = b -- banded, complex matrices
int solbc_(const integer * n,
           const integer * ndim,
           const doublereal * ar,
           const doublereal * ai,
           const integer * ml,
           const integer * mu,
           doublereal * br,
           doublereal * bi,
           const integer * ip);

// reduces a submatrix to upper Hessenberg form
int elmhes_(const integer * nm,
            const integer * n,
            const integer * low,
            const integer * igh,
            doublereal * a,
            integer * int__);

#endif /* decsol_h */
