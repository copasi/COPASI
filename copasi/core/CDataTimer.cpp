// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#include "copasi.h"

#include "CDataTimer.h"
#include "copasi/core/CDataContainer.h"
#include "copasi/core/CDataObjectReference.h"

CCopasiTimer::CCopasiTimer(const Type & type,
                           const CDataContainer * pParent):
  CDataObject((type == CCopasiTimer::Type::WALL) ? "Wall Clock Time" : "CPU Time",
              pParent, "Timer", CDataObject::ValueDbl),
  mType(type),
  mStartTime(),
  mElapsedTime(0),
  mElapsedTimeSeconds(0)
{
  switch (mType)
    {
      case Type::WALL:
        mStartTime = CCopasiTimeVariable::getCurrentWallTime();
        break;

      case Type::PROCESS:
        mStartTime = CCopasiTimeVariable::getProcessTime();
        break;

      case Type::THREAD:
        mStartTime = CCopasiTimeVariable::getThreadTime();
        break;
    }
}

CCopasiTimer::CCopasiTimer(const CCopasiTimer & src,
                           const CDataContainer * pParent):
  CDataObject(src, pParent),
  mType(src.mType),
  mStartTime(src.mStartTime),
  mElapsedTime(src.mElapsedTime),
  mElapsedTimeSeconds(src.mElapsedTimeSeconds)
{}

CCopasiTimer::~CCopasiTimer()
{}

bool CCopasiTimer::start()
{
  switch (mType)
    {
      case Type::WALL:
        mStartTime = CCopasiTimeVariable::getCurrentWallTime();
        break;

      case Type::PROCESS:
        mStartTime = CCopasiTimeVariable::getProcessTime();
        break;

      case Type::THREAD:
        mStartTime = CCopasiTimeVariable::getThreadTime();
        break;
    }

  mElapsedTime = 0;
  mElapsedTimeSeconds = 0;

  return true;
}

void CCopasiTimer::calculateValue()
{
  switch (mType)
    {
      case Type::WALL:
        mElapsedTime = CCopasiTimeVariable::getCurrentWallTime() - mStartTime;
        break;

      case Type::PROCESS:
        mElapsedTime = CCopasiTimeVariable::getProcessTime() - mStartTime;
        break;

      case Type::THREAD:
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
