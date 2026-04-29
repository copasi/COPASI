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
#include "copasi/copasi.h"

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

//template<class T>
//inline const T& max(const T& a, const T& b)
//{return a > b ? a : b;}
//
//template<class T>
//inline const T& min(const T& a, const T& b)
//{return a < b ? a : b;}

// Matrix Triangularization by Gaussian Elimination
int dec_(const integer * n, const integer * ndim, doublereal * a, integer * ip, integer * ier);

// Solution of linear system A*x = b
int sol_(const integer * n, const integer * ndim, const doublereal * a, doublereal * b, const integer * ip);

// Matrix Triangularization by Gaussian Elimination of a Hessenberg
// matrix with lower bandwidth lb
int dech_(const integer * n, const integer * ndim, doublereal * a, integer * lb, integer * ip, integer * ier);

// Solution of linear system A*x = b -- Hessenberg matrix
int solh_(integer * n, integer * ndim, doublereal * a, integer * lb, doublereal * b, integer * ip);

// Matrix Triangularization by Gaussian Elimination for complex matrices
int decc_(integer * n, integer * ndim, doublereal * ar, doublereal * ai, integer * ip, integer * ier);

// Solution of linear system A*x = b -- complex matrices
int solc_(integer * n, integer * ndim, doublereal * ar, doublereal * ai, doublereal * br, doublereal * bi, integer * ip);

// Matrix Triangularization by Gaussian Elimination -- Hessenberg, complex
// matrices
int dechc_(integer * n, integer * ndim, doublereal * ar, doublereal * ai, integer * lb, integer * ip, integer * ier);

// Solution of linear system A*x = b -- Hessenberg, complex matrices
int solhc_(integer * n, integer * ndim, doublereal * ar, doublereal * ai, integer * lb, doublereal * br, doublereal * bi, integer * ip);

//Matrix Triangularization by Gaussian Elimination -- banded matrix
int decb_(integer * n, integer * ndim, doublereal * a, integer * ml, integer * mu, integer * ip, integer * ier);

// Solution of linear system A*x = b -- banded matrix
int solb_(integer * n, integer * ndim, doublereal * a, integer * ml, integer * mu, doublereal * b, integer * ip);

//Matrix Triangularization by Gaussian Elimination -- banded, complex matrices
int decbc_(integer * n, integer * ndim, doublereal * ar, doublereal * ai, integer * ml, integer * mu, integer * ip, integer * ier);

// Solution of linear system A*x = b -- banded, complex matrices
int solbc_(integer * n, integer * ndim, doublereal * ar, doublereal * ai, integer * ml, integer * mu, doublereal * br, doublereal * bi, integer * ip);

// reduces a submatrix to upper Hessenberg form
int elmhes_(integer * nm, integer * n, integer * low, integer * igh, doublereal * a, integer * int__);

#endif /* decsol_h */
