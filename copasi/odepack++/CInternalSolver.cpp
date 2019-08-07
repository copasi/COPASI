// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <string.h>

#include "copasi/copasi.h"

#include "CInternalSolver.h"

CInternalSolver::CInternalSolver():
  mxerrwd(true),
  mdls001_(),
  mdlsa01_(),
  mdlsr01_()
{}

CInternalSolver::~CInternalSolver()
{}

void CInternalSolver::setOstream(std::ostream & os)
{
  mxerrwd.setOstream(os);
}

void CInternalSolver::enablePrint(const bool & print)
{
  mxerrwd.enablePrint(print);
}

void CInternalSolver::saveState(CInternalSolver::State & state) const
{
  state.mdls001 = mdls001_;
  state.mdlsa01 = mdlsa01_;
  state.mdlsr01 = mdlsr01_;
}

void CInternalSolver::resetState(const CInternalSolver::State & state)
{
  mdls001_ = state.mdls001;
  mdlsa01_ = state.mdlsa01;
  mdlsr01_ = state.mdlsr01;
}
