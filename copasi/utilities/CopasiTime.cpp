/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CopasiTime.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/08/31 12:21:14 $
   End CVS Header */

#include "CopasiTime.h"

CopasiTimePoint::CopasiTimePoint():
    mTime(getCurrentTime_msec())
{}

C_INT32 CopasiTimePoint::init()
{mTime = getCurrentTime_msec();}

C_INT32 CopasiTimePoint::get() const
  {return mTime;}

C_INT32 CopasiTimePoint::getTimeDiff() const
  {
    C_INT32 diff = getCurrentTime_msec() - mTime;
    if (diff >= 0) return diff;
    else return diff + (1 << 30);
  }

//the following is linux (posix? unix?) specific and might not work under windows
//from the web I guess that windows needs something with
// #include <time.h>
// ...
// return timeGetTime()
// ...
// but I cannot test that

#include <sys/time.h>

//static
C_INT32 CopasiTimePoint::getCurrentTime_msec()
{
  timeval ttt;
  gettimeofday(&ttt, 0);
  long long int time;
  time = ttt.tv_sec * 1000 + ttt.tv_usec / 1000;
  return time % (1 << 30);
}
