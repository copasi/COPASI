/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/odepack++/CInternalSolver.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:29:35 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef ODEPACK_CInternalSolver
#define ODEPACK_CInternalSolver

#include "common.h"

class Cxerrwd;

class CInternalSolver
  {
  public:

  public:

    CInternalSolver(Cxerrwd * pxerrwd,
                    dls001 & dls001_,
                    dlsa01 & dlsa01_):
        mpxerrwd(pxerrwd),
        mdls001_(dls001_),
        mdlsa01_(dlsa01_)
    {}

    C_INT dintdy_(double *t, const C_INT *k, double *yh,
                  C_INT *nyh, double *dky, C_INT *iflag);

    C_INT dprja_(C_INT *neq, double *y, double *yh,
                 C_INT *nyh, double *ewt, double *ftem, double *savf,
                 double *wm, C_INT *iwm, evalF f, evalJ jac);

    C_INT dsolsy_(double *wm, C_INT *iwm, double *x,
                  double *tem);

    C_INT dstoda_(C_INT *neq, double *y, double *yh,
                  C_INT *nyh, double *yh1, double *ewt, double *savf,
                  double *acor, double *wm, C_INT *iwm, evalF f, evalJ jac,
                  PJAC * pjac, SLVS * slvs);

  private:
    Cxerrwd * mpxerrwd;
    dls001 & mdls001_;
    dlsa01 & mdlsa01_;
  };

#endif // ODEPACK_CInternalSolver
