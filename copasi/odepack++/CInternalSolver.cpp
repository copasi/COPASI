// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
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

CInternalSolver::CInternalSolver(CInternalSolver::State & state)
  : Cxerrwd(true)
  , mState(state)
  , mpCheckRoots(&CInternalSolver::drchek_)
{}

CInternalSolver::~CInternalSolver()
{}

void CInternalSolver::saveState(CInternalSolver::State & state) const
{
  state.mdls001_ = mState.mdls001_;
  state.mdlsa01_ = mState.mdlsa01_;
  state.mdlsr01_ = mState.mdlsr01_;
}

void CInternalSolver::resetState(const CInternalSolver::State & state)
{
  mState.mdls001_ = state.mdls001_;
  mState.mdlsa01_ = state.mdlsa01_;
  mState.mdlsr01_ = state.mdlsr01_;
}
