// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/* dn2fb.f -- translated by f2c (version 19970805).
   You must link the resulting object file with the libraries:
  -lf2c -lm   (in that order)

           -- fixed manually by Pedro Mendes May 1998
 */

#ifndef COPASI_CNL2SOL
#define COPASI_CNL2SOL

#include "copasi/lapack/lapackwrap.h"
#include "copasi/lapack/blaswrap.h"

class FNL2SOL
{
public:
  virtual ~FNL2SOL() {};

  virtual C_INT operator()(integer * C_UNUSED(n), integer * C_UNUSED(n), doublereal * C_UNUSED(value), integer * C_UNUSED(n), doublereal * C_UNUSED(value1), integer * C_UNUSED(n), doublereal * C_UNUSED(value2), U_fp)
  {return std::numeric_limits<C_INT>::quiet_NaN();}
};

template <class CType> class FNL2SOLTemplate : public FNL2SOL
{
private:
  C_INT(CType::*mMethod)(integer *, integer *, doublereal *, integer *, doublereal *, integer *, doublereal *, U_fp);  // pointer to member function
  CType * mpType;                                            // pointer to object

public:

  // constructor - takes pointer to an object and pointer to a member and stores
  // them in two private variables
  FNL2SOLTemplate(CType * pType,
                  C_INT(CType::*method)(integer *, integer *, doublereal *, integer *, doublereal *, integer *, doublereal *, U_fp))
  {
    mpType = pType;
    mMethod = method;
  };

  virtual ~FNL2SOLTemplate() {};

  // override operator "()"
  virtual C_INT operator()(integer *n, integer *p, doublereal *x, integer *nf, doublereal *resid, integer *uiparm, doublereal *urparm, U_fp ufparm)
  {return (*mpType.*mMethod)(n, p, x, nf, resid, uiparm, urparm, ufparm);}    ; // execute member function
};

class CNL2SOL
{

public:
  CNL2SOL();

  int dn2fb_(integer *n, integer *p, doublereal *x, doublereal *b,
             FNL2SOL *calcr, integer *iv, integer *liv, integer *lv, doublereal *v,
             integer *ui, doublereal *ur, U_fp uf);

  int divset_N(integer *alg, integer *iv, integer *liv, integer
               *lv, doublereal *v);

  ~CNL2SOL();

private:
};

#endif // COPASI_CNL2SOL
