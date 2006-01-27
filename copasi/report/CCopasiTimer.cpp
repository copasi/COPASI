/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/report/CCopasiTimer.cpp,v $
   $Revision: 1.5.2.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/01/27 13:49:55 $
   End CVS Header */

#include "copasi.h"

#include "CCopasiTimer.h"
#include "CCopasiContainer.h"
#include "CCopasiObjectReference.h"

CCopasiTimer::CCopasiTimer(const Type & type,
                           const CCopasiContainer * pParent):
    CCopasiObject((type == CCopasiTimer::WALL) ? "Wall Clock Time" : "CPU Time",
                  pParent, "Timer", CCopasiObject::ValueDbl),
    mType(type),
    mStartTime((mType == CCopasiTimer::WALL) ?
               CCopasiTimeVariable::getCurrentWallTime() :
               CCopasiTimeVariable::getCPUTime()),
    mElapsedTime(0),
    mElapsedTimeSeconds(0)
{setRefresh(this, &CCopasiTimer::refresh);}

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

    case CPU:
      mStartTime = CCopasiTimeVariable::getCPUTime();
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

    case CPU:
      mElapsedTime = CCopasiTimeVariable::getCPUTime() - mStartTime;
      break;
    }

  mElapsedTimeSeconds =
    (mElapsedTime.getMicroSeconds() * 1e-6);

  return;
}

const CCopasiTimeVariable & CCopasiTimer::getElapsedTime()
{
  refresh();
  return mElapsedTime;
}

void CCopasiTimer::print(std::ostream * ostream) const
  {(*ostream) << mElapsedTimeSeconds;}

void * CCopasiTimer::getReference() const
  {return & const_cast<CCopasiTimer *>(this)->mElapsedTimeSeconds;}
