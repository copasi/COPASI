/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiTimer.cpp,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: shoops $
   $Date: 2012/04/04 19:17:43 $
   End CVS Header */

// Copyright (C) 2012 - 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CCopasiTimer.h"
#include "CCopasiContainer.h"
#include "CCopasiObjectReference.h"

CCopasiTimer::CCopasiTimer(const Type & type,
                           const CCopasiContainer * pParent):
    CCopasiObject((type == CCopasiTimer::WALL) ? "Wall Clock Time" : "CPU Time",
                  pParent, "Timer", CCopasiObject::ValueDbl),
    mType(type),
    mStartTime(),
    mElapsedTime(0),
    mElapsedTimeSeconds(0)
{
  switch (mType)
    {
      case WALL:
        mStartTime = CCopasiTimeVariable::getCurrentWallTime();
        break;

      case PROCESS:
        mStartTime = CCopasiTimeVariable::getProcessTime();
        break;

      case THREAD:
        mStartTime = CCopasiTimeVariable::getThreadTime();
        break;

    }

  setRefresh(this, &CCopasiTimer::refresh);
}


CCopasiTimer::CCopasiTimer(const CCopasiTimer & src,
                           const CCopasiContainer * pParent):
    CCopasiObject(src, pParent),
    mType(src.mType),
    mStartTime(src.mStartTime),
    mElapsedTime(src.mElapsedTime),
    mElapsedTimeSeconds(src.mElapsedTimeSeconds)
{setRefresh(this, &CCopasiTimer::refresh);}

CCopasiTimer::~CCopasiTimer()
{}

bool CCopasiTimer::start()
{
  switch (mType)
    {
      case WALL:
        mStartTime = CCopasiTimeVariable::getCurrentWallTime();
        break;

      case PROCESS:
        mStartTime = CCopasiTimeVariable::getProcessTime();
        break;

      case THREAD:
        mStartTime = CCopasiTimeVariable::getThreadTime();
        break;
    }

  mElapsedTime = 0;
  mElapsedTimeSeconds = 0;

  return true;
}

void CCopasiTimer::refresh()
{
  switch (mType)
    {
      case WALL:
        mElapsedTime = CCopasiTimeVariable::getCurrentWallTime() - mStartTime;
        break;

      case PROCESS:
        mElapsedTime = CCopasiTimeVariable::getProcessTime() - mStartTime;
        break;

      case THREAD:
        mElapsedTime = CCopasiTimeVariable::getThreadTime() - mStartTime;
        break;
    }

  mElapsedTimeSeconds =
    (mElapsedTime.getMicroSeconds() * 1e-6);

  return;
}

const CCopasiTimeVariable & CCopasiTimer::getElapsedTime() const
{
  return mElapsedTime;
}

const C_FLOAT64 & CCopasiTimer::getElapsedTimeSeconds() const
{
  return mElapsedTimeSeconds;
}

void CCopasiTimer::print(std::ostream * ostream) const
{(*ostream) << mElapsedTimeSeconds;}

void * CCopasiTimer::getValuePointer() const
{return & const_cast<CCopasiTimer *>(this)->mElapsedTimeSeconds;}
