// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <string.h>

#include "copasi.h"

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

void CInternalSolver::saveState()
{
  mState.mdls001 = mdls001_;
  mState.mdlsa01 = mdlsa01_;
  mState.mdlsr01 = mdlsr01_;
}

void CInternalSolver::resetState()
{
  mdls001_ = mState.mdls001;
  mdlsa01_ = mState.mdlsa01;
  mdlsr01_ = mState.mdlsr01;
}
