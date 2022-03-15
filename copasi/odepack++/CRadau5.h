// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

//
// This C++ code is based on an f2c conversion of the Fortran
// library

#ifndef ODEPACK_CRadau5
#define ODEPACK_CRadau5

#include "copasi/odepack++/CInternalSolver.h"

class CRadau5: public CInternalSolver
{
public:
  CRadau5();
  ~CRadau5();

  typedef void (*evalF)(const C_INT *, const double *, const double *, double *, double *, C_INT *);
  typedef void (*evalJ)(const C_INT *, const double *, const double *, double *, const C_INT *, double *, const C_INT *);
  // typedef void (*evalG)(const C_INT *, const double *, const double *, const C_INT *, double *);
  typedef void (*evalM)(C_INT *, double *, C_INT *, double *, C_INT *);
  typedef void (*evalO)(C_INT *, double *, double *, double *, double *, C_INT *, C_INT *, double *, C_INT *, C_INT *);

  C_INT operator()(C_INT * n,      //  Number of equations
                   evalF fcn,      //  Evaluate f
                   double * x,     //  Initial X values
                   double * y,     //  Initial Y values
                   double * xend,  //  Final X value
                   double * h__,   //  Initial step size guess
                   double * rtol,  //  Relative error tolerance
                   double * atol,  //  Absolute error tolerance
                   C_INT * itol,   //  Switch for atol and rtol
                   evalJ jac,      //  External subroutine for partial derivatives
                   C_INT * ijac,   //  Switch for Jacobian computation
                   C_INT * mljac,  //  Switch for Jacobian structure
                   C_INT * mujac,  //  Upper bandwidth of Jacobian
                   evalM mas,      //  For mass matrix
                   C_INT * imas,   //  For mass matrix
                   C_INT * mlmas,  //  For mass matrix
                   C_INT * mumas,  //  For mass matrix
                   evalO solout,   //  Subroutine to compute external numerical computation
                   C_INT * iout,   //  Switch for solout function
                   double * work,  //  Work array
                   C_INT * lwork,  //  Length of work array
                   C_INT * iwork,  //  C_INT working space
                   C_INT * liwork, //  Length of iwork
                   double * rpar,  //  Real parameter for working
                   C_INT * ipar,   //  C_INT parameter for working
                   C_INT * idid);  //  Output status

private:

  static const C_INT mxstp0;
  static const C_INT mxhnl0;
  static const C_INT mord[2];
};

#include "dc_decsol.h"

#endif // ODEPACK_CRadau5
