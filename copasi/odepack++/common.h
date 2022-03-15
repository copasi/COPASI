// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

//
// This C++ code is based on an f2c conversion of the Fortran
// library ODEPACK available at: http://www.netlib.org/odepack/

#ifndef ODEPACK_common
#define ODEPACK_common

#include "copasi/core/CCore.h"

typedef void (*evalF)(const C_INT*, const double*, const double*, double*);
typedef void (*evalJ)(const C_INT*, const double*, const double*, const C_INT*,
                      const C_INT*, double*, const C_INT*);
typedef void (*evalG)(const C_INT*, const double*, const double*,
                      const C_INT*, double*);

union dls001
{
  struct
  {
    double rowns[209], ccmax, el0, h__, hmin, hmxi, hu, rc, tn,
           uround;
    C_INT iownd[6], iowns[6], icf, ierpj, iersl, jcur, jstart, kflag, l,
          lyh, lewt, lacor, lsavf, lwm, liwm, meth, miter, maxord,
          maxcor, msbp, mxncf, n, nq, nst, nfe, nje, nqu;
  }
  _1;
  struct
  {
    double rls[218];
    C_INT ils[37];
  }
  _2;
  struct
  {
    double conit, crate, el[13], elco[156] /* was [13][12] */,
           hold, rmax, tesco[36] /* was [3][12] */, ccmax, el0, h__,
           hmin, hmxi, hu, rc, tn, uround;
    C_INT iownd[6], ialth, ipup, lmax, meo, nqnyh, nslp, icf, ierpj,
          iersl, jcur, jstart, kflag, l, lyh, lewt, lacor, lsavf, lwm,
          liwm, meth, miter, maxord, maxcor, msbp, mxncf, n, nq, nst,
          nfe, nje, nqu;
  }
  _3;
  struct
  {
    double rowns[209], ccmax, el0, h__, hmin, hmxi, hu, rc, tn, uround;
    C_INT init, mxstep, mxhnil, nhnil, nslast, nyh, iowns[6], icf, ierpj,
          iersl, jcur, jstart, kflag, l, lyh, lewt, lacor, lsavf, lwm, liwm,
          meth, miter, maxord, maxcor, msbp, mxncf, n, nq, nst, nfe, nje,
          nqu;
  }
  lsoda;
};

union dlsa01
{
  struct
  {
    double rownd2, cm1[12], cm2[5], pdest, pdlast, ratio, pdnorm;
    C_INT iownd2[3], icount, irflag, jtyp, mused, mxordn, mxords;
  }
  _1;
  struct
  {
    double rownd2, rowns2[20], pdnorm;
    C_INT iownd2[3], iowns2[2], jtyp, mused, mxordn, mxords;
  }
  _2;
  struct
  {
    double rlsa[22];
    C_INT ilsa[9];
  }
  _3;
  struct
  {
    double tsw, rowns2[20], pdnorm;
    C_INT insufr, insufi, ixpr, iowns2[2], jtyp, mused, mxordn, mxords;
  }
  lsoda;
};

union dlsr01
{
  struct
  {
    double rownr3[2], t0, tlast, toutc;
    C_INT iownd3[3], iownr3[2], irfnd, itaskc, ngc, nge;
  }
  _1;
  struct
  {
    double alpha, x2, rdum3[3];
    C_INT iownd3[3], imax, last, idum3[4];
  }
  _2;
  struct
  {
    double rlsr[5];
    C_INT ilsr[9];
  }
  _3;
  struct
  {
    double rownr3[2], t0, tlast, toutc;
    C_INT lg0, lg1, lgx, iownr3[2], irfnd, itaskc, ngc, nge;
  }
  lsodar;
};

class PJAC
{
public:
  PJAC(C_INT(*pMethod)(C_INT *neq, double *y, double *yh,
                       C_INT *nyh, double *ewt, double *ftem,
                       double *savf, double *wm, C_INT *iwm,
                       evalF f, evalJ jac));

  virtual ~PJAC();

  virtual C_INT operator()(C_INT *neq, double *y, double *yh,
                           C_INT *nyh, double *ewt, double *ftem,
                           double *savf, double *wm, C_INT *iwm,
                           evalF f, evalJ jac);

protected:
  PJAC();

private:
  C_INT(*mpMethod)(C_INT *neq, double *y, double *yh,
                   C_INT *nyh, double *ewt, double *ftem,
                   double *savf, double *wm, C_INT *iwm,
                   evalF f, evalJ jac);
};

template <typename CType> class PJACFunctor : public PJAC
{
public:
  PJACFunctor(CType * pType,
              C_INT(CType::*pMethod)(C_INT *neq, double *y, double *yh,
                                     C_INT *nyh, double *ewt, double *ftem,
                                     double *savf, double *wm, C_INT *iwm,
                                     evalF f, evalJ jac)):
    PJAC(),
    mpType(pType),
    mpMethod(pMethod)
  {}

  virtual ~PJACFunctor() {}

  virtual C_INT operator()(C_INT *neq, double *y, double *yh,
                           C_INT *nyh, double *ewt, double *ftem,
                           double *savf, double *wm, C_INT *iwm,
                           evalF f, evalJ jac)
  {
    return (*mpType.*mpMethod)(neq, y, yh, nyh, ewt, ftem, savf, wm,
                               iwm, f, jac);
  }

protected:
  PJACFunctor() : PJAC(), mpType(NULL), mpMethod(NULL) {}

private:
  CType * mpType;
  C_INT(CType::*mpMethod)(C_INT *neq, double *y, double *yh,
                          C_INT *nyh, double *ewt, double *ftem,
                          double *savf, double *wm, C_INT *iwm,
                          evalF f, evalJ jac);
};

class SLVS
{
public:
  SLVS(C_INT(*pMethod)(double *wm, C_INT *iwm, double *x, double *tem));

  virtual ~SLVS();

  virtual C_INT operator()(double *wm, C_INT *iwm, double *x, double *tem);

protected:
  SLVS();

private:
  C_INT(*mpMethod)(double *wm, C_INT *iwm, double *x, double *tem);
};

template <typename CType> class SLVSFunctor : public SLVS
{
public:
  SLVSFunctor(CType * pType,
              C_INT(CType::*pMethod)(double *wm, C_INT *iwm, double *x,
                                     double *tem)):
    SLVS(),
    mpType(pType),
    mpMethod(pMethod)
  {}

  virtual ~SLVSFunctor() {}

  virtual C_INT operator()(double *wm, C_INT *iwm, double *x,
                           double *tem)
  {return (*mpType.*mpMethod)(wm, iwm, x, tem);}

protected:
  SLVSFunctor() : SLVS(), mpType(NULL), mpMethod(NULL) {}

private:
  CType * mpType;
  C_INT(CType::*mpMethod)(double *wm, C_INT *iwm, double *x,
                          double *tem);
};

#endif // ODEPACK_common
