// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

//
// This C++ code is based on an f2c conversion of the Fortran
// library

#ifndef ODEPACK_CRadau5
#define ODEPACK_CRadau5

#include "copasi/odepack++/CInternalSolver.h"
#include "dc_decsol.h"


class CRadau5: public CInternalSolver
{
public:
  CRadau5();
  ~CRadau5();

  integer operator()(integer *n,         //  Number of equations
                     evalF fcn,          //  Evaluate f
                     doublereal *x,     //  Initial X values
                     doublereal *y,    //  Initial Y values
                     doublereal *xend,  //  Final X value
                     doublereal *h__,   //  Initial step size guess
                     doublereal *rtol,  //  Relative error tolerance
                     doublereal *atol,  //  Absolute error tolerance
                     integer *itol,     //  Switch for atol and rtol
                     U_fp jac,          //  External subroutine for partial derivatives
                     integer *ijac,     //  Switch for Jacobian computation
                     integer *mljac,    //  Switch for Jacobian structure
                     integer *mujac,    //  Upper bandwidth of Jacobian
                     U_fp mas,          //  For mass matrix
                     integer *imas,     //  For mass matrix
                     integer *mlmas,    //  For mass matrix
                     integer *mumas,    //  For mass matrix
                     U_fp solout,       //  Subroutine to compute external numerical computation
                     integer *iout,     //  Switch for solout function
                     doublereal *work,  //  Work array
                     integer *lwork,    //  Length of work array
                     integer *iwork,    //  integer working space
                     integer *liwork,   //  Length of iwork
                     doublereal *rpar,  //  Real parameter for working
                     integer *ipar,     //  integer parameter for working
                     integer *idid);    //  Output status

private:

  static const integer mxstp0;
  static const integer mxhnl0;
  static const integer mord[2];
};

#endif // ODEPACK_CRadau5

