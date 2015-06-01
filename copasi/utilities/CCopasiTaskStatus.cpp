//
//  CCopasiTaskStatus.cpp
//  COPASI
//
//  Created by Sven Sahle on 04.11.14.
//
//

#include "CCopasiTaskStatus.h"

const std::string CCopasiTaskStatus::StateString[] =
{
  "Unknown state",
  "Output data structures initialized",
  "Initialized",
  "Problem not valid for selected method",
  "Initialization failed",
  "Started",
  "Stopped",
  "Success",
  "Failed",
  "Result discarded",
  ""
};


CCopasiTaskStatus::CCopasiTaskStatus():
  mState(NoState)
  {
  };

void CCopasiTaskStatus::set(State state)
{
  mState = state;
}

void CCopasiTaskStatus::setInitialized(bool success)
{
  if (success)
    mState = Initialized;
  else
    mState = InitializeFailed;
}


const CCopasiTaskStatus::State & CCopasiTaskStatus::getState() const
{
  return mState;
}

