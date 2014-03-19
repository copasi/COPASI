// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include <string.h>

#include "copasi.h"

#include "CInternalSolver.h"

CInternalSolver::CInternalSolver():
  mxerrwd(true),
  mpdls001_(NULL),
  mpdlsa01_(NULL),
  mpdlsr01_(NULL)
{}

CInternalSolver::~CInternalSolver()
{
  if (mpdls001_ != NULL) {delete mpdls001_; mpdls001_ = NULL;}

  if (mpdlsa01_ != NULL) {delete mpdlsa01_; mpdlsa01_ = NULL;}

  if (mpdlsr01_ != NULL) {delete mpdlsr01_; mpdlsr01_ = NULL;}
}

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
  if (mpdls001_ != NULL) {memcpy(&mState.mdls001, mpdls001_, sizeof(dls001));}

  if (mpdlsa01_ != NULL) {memcpy(&mState.mdlsa01, mpdlsa01_, sizeof(dlsa01));}

  if (mpdlsr01_ != NULL) {memcpy(&mState.mdlsr01, mpdlsr01_, sizeof(dlsr01));}
}

void CInternalSolver::resetState()
{
  if (mpdls001_ != NULL) {memcpy(mpdls001_, &mState.mdls001, sizeof(dls001));}

  if (mpdlsa01_ != NULL) {memcpy(mpdlsa01_, &mState.mdlsa01, sizeof(dlsa01));}

  if (mpdlsr01_ != NULL) {memcpy(mpdlsr01_, &mState.mdlsr01, sizeof(dlsr01));}
}
