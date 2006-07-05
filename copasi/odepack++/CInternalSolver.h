/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/odepack++/CInternalSolver.h,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/07/05 19:38:32 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.
//
// This C++ code is based on an f2c conversion of the Fortran
// library ODEPACK available at: http://www.netlib.org/odepack/

#ifndef ODEPACK_CInternalSolver
#define ODEPACK_CInternalSolver

#include "common.h"
#include "Cxerrwd.h"

class CInternalSolver
  {
  private:

  protected:
    CInternalSolver():
        mxerrwd(),
        mpdls001_(NULL),
        mpdlsa01_(NULL),
        mpdlsr01_(NULL)
    {}

  public:
    ~CInternalSolver()
    {
      if (mpdls001_ != NULL) {delete mpdls001_; mpdls001_ = NULL;}
      if (mpdlsa01_ != NULL) {delete mpdlsa01_; mpdlsa01_ = NULL;}
      if (mpdlsr01_ != NULL) {delete mpdlsr01_; mpdlsr01_ = NULL;}
    }

    void setOstream(std::ostream & os)
    {mxerrwd.setOstream(os);}

    void enablePrint(const bool & print = true)
    {mxerrwd.enablePrint(print);}

  protected:
    C_INT dintdy_(double *t, const C_INT *k, double *yh,
                  C_INT *nyh, double *dky, C_INT *iflag);

    C_INT dprja_(C_INT *neq, double *y, double *yh,
                 C_INT *nyh, double *ewt, double *ftem, double *savf,
                 double *wm, C_INT *iwm, evalF f, evalJ jac);

    C_INT drchek_(const C_INT * job, evalG g, C_INT *neq, double *
                  y, double *yh, C_INT *nyh, double *g0, double *g1,
                  double *gx, C_INT *jroot, C_INT *irt);

    C_INT droots_(C_INT *ng, double *hmin, C_INT *jflag,
                  double *x0, double *x1, double *g0, double *g1,
                  double *gx, double *x, C_INT *jroot);

    C_INT dsolsy_(double *wm, C_INT *iwm, double *x,
                  double *tem);

    C_INT dstoda_(C_INT *neq, double *y, double *yh,
                  C_INT *nyh, double *yh1, double *ewt, double *savf,
                  double *acor, double *wm, C_INT *iwm, evalF f, evalJ jac,
                  PJAC * pjac, SLVS * slvs);

  protected:
    Cxerrwd mxerrwd;
    dls001 * mpdls001_;
    dlsa01 * mpdlsa01_;
    dlsr01 * mpdlsr01_;
  };

#endif // ODEPACK_CInternalSolver
