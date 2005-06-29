/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiTimer.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/29 20:24:22 $
   End CVS Header */

#include "copasi.h"

#include "CCopasiTimer.h"
#include "report/CCopasiObjectReference.h"

CCopasiTimer::CCopasiTimer(const Type & type,
                           const CCopasiContainer * pParent):
    CCopasiContainer((type == CCopasiTimer::WALL) ? "Wall Clock Time" : "CPU Time",
                     pParent, "Timer"),
    mType(type),
    mStartTime((mType == CCopasiTimer::WALL) ?
               CCopasiTimeVariable::getCurrentWallTime() :
               CCopasiTimeVariable::getCPUTime()),
    mElapsedTime(0),
    mElapsedTimeSeconds(0)
{initObjects();}

CCopasiTimer::CCopasiTimer(const CCopasiTimer & src,
                           const CCopasiContainer * pParent):
CCopasiContainer(src, pParent),
mType(src.mType),
mStartTime(src.mStartTime),
mElapsedTime(src.mElapsedTime),
mElapsedTimeSeconds(src.mElapsedTimeSeconds)
{initObjects();}

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

void CCopasiTimer::initObjects()
{
  CCopasiObject * pObject;
  pObject = addObjectReference("Elapsed Time", mElapsedTimeSeconds, CCopasiObject::ValueDbl);
  pObject->setActualize(this, &CCopasiTimer::actualize);
}
