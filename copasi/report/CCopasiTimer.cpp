/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiTimer.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/08/08 17:20:30 $
   End CVS Header */

#include "copasi.h"

#include "CCopasiTimer.h"
#include "CCopasiContainer.h"
#include "CCopasiObjectReference.h"

CCopasiTimer::CCopasiTimer(const Type & type,
                           const CCopasiContainer * pParent):
    CCopasiObject((type == CCopasiTimer::WALL) ? "Wall Clock Time" : "CPU Time",
                  pParent, "Timer"),
    mType(type),
    mStartTime((mType == CCopasiTimer::WALL) ?
               CCopasiTimeVariable::getCurrentWallTime() :
               CCopasiTimeVariable::getCPUTime()),
    mElapsedTime(0),
    mElapsedTimeSeconds(0)
{setActualize(this, &CCopasiTimer::actualize);}

CCopasiTimer::CCopasiTimer(const CCopasiTimer & src,
                           const CCopasiContainer * pParent):
CCopasiObject(src, pParent),
mType(src.mType),
mStartTime(src.mStartTime),
mElapsedTime(src.mElapsedTime),
mElapsedTimeSeconds(src.mElapsedTimeSeconds)
{setActualize(this, &CCopasiTimer::actualize);}

CCopasiTimer::~CCopasiTimer()
{}

bool CCopasiTimer::start()
{
  switch (mType)
    {
    case WALL:
      mStartTime = CCopasiTimeVariable::getCurrentWallTime();
      break;

    case CPU:
      mStartTime = CCopasiTimeVariable::getCPUTime();
      break;
    }

  mElapsedTime = 0;
  mElapsedTimeSeconds = 0;

  return true;
}

bool CCopasiTimer::actualize()
{
  switch (mType)
    {
    case WALL:
      mElapsedTime = CCopasiTimeVariable::getCurrentWallTime() - mStartTime;
      break;

    case CPU:
      mElapsedTime = CCopasiTimeVariable::getCPUTime() - mStartTime;
      break;
    }

  mElapsedTimeSeconds = mElapsedTime.getSeconds();

  return true;
}

const CCopasiTimeVariable & CCopasiTimer::getElapsedTime()
{
  actualize();
  return mElapsedTime;
}

void CCopasiTimer::print(std::ostream * ostream) const
  {(*ostream) << mElapsedTime.isoFormat();}
