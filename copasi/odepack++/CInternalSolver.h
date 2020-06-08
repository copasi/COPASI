// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#ifndef ODEPACK_CInternalSolver
#define ODEPACK_CInternalSolver

#include "copasi/odepack++/common.h"
#include "copasi/odepack++/Cxerrwd.h"

class CInternalSolver
{
public:
  struct State
  {
    dls001 mdls001;
    dlsa01 mdlsa01;
    dlsr01 mdlsr01;
  };

protected:
  CInternalSolver();

public:
  ~CInternalSolver();

  void setOstream(std::ostream & os);

  void enablePrint(const bool & print = true);

  void saveState(State & state) const;
  void resetState(const State & state);

  C_INT dintdy_(double *t, const C_INT *k, double *yh,
                C_INT *nyh, double *dky, C_INT *iflag);

protected:
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
  dls001 mdls001_;
  dlsa01 mdlsa01_;
  dlsr01 mdlsr01_;
};

#endif // ODEPACK_CInternalSolver
