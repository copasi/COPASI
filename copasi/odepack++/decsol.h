// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

# ifdef HAVE_F2C_H
#  include <f2c.h>
# else
#  include "copasi/lapack/f2c.h"
# endif

//template<class T>
//inline const T& max(const T& a, const T& b)
//{ return a > b ? a : b; }
//
//template<class T>
//inline const T& min(const T& a, const T& b)
//{ return a < b ? a : b; }

// Matrix Triangularization by Gaussian Elimination
int dec_(integer n, double **A, int *ip);

// Solution of linear system A*x = b
void sol_(integer n, double **A, double *b, int *ip);

// Matrix Triangularization by Gaussian Elimination of a Hessenberg
// matrix with lower bandwidth lb
int dech_(integer n, double **A, int lb, int *ip);

// Solution of linear system A*x = b -- Hessenberg matrix
void solh_(integer n, double **A, int lb, double *b, int *ip);

// Matrix Triangularization by Gaussian Elimination for complex matrices
int decc_(integer n, double **AR, double **AI, int *ip);

// Solution of linear system A*x = b -- complex matrices
void solc_(integer n, double **AR, double **AI, double *br,
           double *bi, int *ip);

// Matrix Triangularization by Gaussian Elimination -- Hessenberg, complex
// matrices
int dechc_(integer n, double **AR, double **AI, int lb, int *ip);

// Solution of linear system A*x = b -- Hessenberg, complex matrices
void solhc_(integer n, double **AR, double **AI, int lb,
            double *br, double *bi, int *ip);

//Matrix Triangularization by Gaussian Elimination -- banded matrix
int decb_(integer n, double **A, int ml, int mu, int *ip);

// Solution of linear system A*x = b -- banded matrix
void solb_(integer n, double **A, int ml, int mu, double *b, int *ip);

//Matrix Triangularization by Gaussian Elimination -- banded, complex matrices
int decbc_(integer n, double **AR, double **AI, int ml, int mu, int *ip);

// Solution of linear system A*x = b -- banded, complex matrices
void solbc_(integer n, double **AR, double **AI, int ml, int mu,
            double *br, double *bi, int *ip);

// reduces a submatrix to upper Hessenberg form
void elmhes_(integer n, int low, int igh, double **A, int *inter);


#endif /* decsol_h */
