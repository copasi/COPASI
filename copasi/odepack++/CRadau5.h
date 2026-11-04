// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

//
// This C++ code is based on an f2c conversion of the Fortran
// library

#ifndef ODEPACK_CRadau5
#define ODEPACK_CRadau5

#include "copasi/odepack++/Cxerrwd.h"
#include "copasi/odepack++/dc_decsol.h"

class CRadau5 : public Cxerrwd
{
public:
  struct Sconra5
  {
    C_INT nn;
    C_INT nn2;
    C_INT nn3;
    C_INT nn4;
    double xsol;
    double hsol;
    double c2m1;
    double c1m1;

    Sconra5()
      : nn(0)
      , nn2(0)
      , nn3(0)
      , nn4(0)
      , xsol(0.0)
      , hsol(0.0)
      , c2m1(0.0)
      , c1m1(0.0){};
  };

  struct common : dc_decsol::common
  {
    Sconra5 conra5;

    common()
      : dc_decsol::common()
      , conra5(){};
  };

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
  int radcor_(C_INT * n,
              CRadau5::evalF fcn,
              double * x,
              double * y,
              double * xend,
              double * hmax,
              double * h__,
              double * rtol,
              double * atol,
              C_INT * itol,
              CRadau5::evalJ jac,
              C_INT * ijac,
              C_INT * mljac,
              C_INT * mujac,
              CRadau5::evalM mas,
              C_INT * mlmas,
              C_INT * mumas,
              CRadau5::evalO solout,
              C_INT * iout,
              C_INT * idid,
              C_INT * nmax,
              double * uround,
              double * safe,
              double * thet,
              double * fnewt,
              double * quot1,
              double * quot2,
              C_INT * nit,
              C_INT * ijob,
              C_LOGICAL * startn,
              C_INT * nind1,
              C_INT * nind2,
              C_INT * nind3,
              C_LOGICAL * pred,
              double * facl,
              double * facr,
              C_INT * m1,
              C_INT * m2,
              C_INT * nm1,
              C_LOGICAL * implct,
              C_LOGICAL * banded,
              C_INT * ldjac,
              C_INT * lde1,
              C_INT * ldmas,
              double * z1,
              double * z2,
              double * z3,
              double * y0,
              double * scal,
              double * f1,
              double * f2,
              double * f3,
              double * fjac,
              double * e1,
              double * e2r,
              double * e2i,
              double * fmas,
              C_INT * ip1,
              C_INT * ip2,
              C_INT * iphes,
              double * cont,
              C_INT * nfcn,
              C_INT * njac,
              C_INT * nstep,
              C_INT * naccpt,
              C_INT * nrejct,
              C_INT * ndec,
              C_INT * nsol,
              double * rpar,
              C_INT * ipar);

  double contr5_(C_INT * i__,
                 double * x,
                 double * cont,
                 C_INT * lrc);

  int estrad_(C_INT * n,
              double * fjac,
              C_INT * ldjac,
              C_INT * mljac,
              C_INT * mujac,
              double * fmas,
              C_INT * ldmas,
              C_INT * mlmas,
              C_INT * mumas,
              double * h__,
              double * dd1,
              double * dd2,
              double * dd3,
              CRadau5::evalF fcn,
              C_INT * nfcn,
              double * y0,
              double * y,
              C_INT * ijob,
              double * x,
              C_INT * m1,
              C_INT * m2,
              C_INT * nm1,
              double * e1,
              C_INT * lde1,
              double * z1,
              double * z2,
              double * z3,
              double * cont,
              double * f1,
              double * f2,
              C_INT * ip1,
              C_INT * iphes,
              double * scal,
              double * err,
              C_LOGICAL * first,
              C_LOGICAL * reject,
              double * fac1,
              double * rpar,
              C_INT * ipar);

  common mCommon;
};

#endif // ODEPACK_CRadau5
