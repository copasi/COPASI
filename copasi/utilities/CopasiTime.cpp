/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CopasiTime.cpp,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/01/24 18:39:26 $
   End CVS Header */

#include <sstream>

#include "CopasiTime.h"
#include "utility.h"

CopasiTimePoint::CopasiTimePoint():
    mTime(getCurrentTime_msec())
{}

C_INT32 CopasiTimePoint::init()
{return mTime = getCurrentTime_msec();}

C_INT32 CopasiTimePoint::get() const
  {return mTime;}

C_INT32 CopasiTimePoint::getTimeDiff() const
  {
    C_INT32 diff = getCurrentTime_msec() - mTime;
    return diff & 0x7fffffff;
  }

//the following is linux (posix? unix?) specific and might not work under windows
//from the web I guess that windows needs something with
// #include <time.h>
// ...
// return timeGetTime()
// ...
// but I cannot test that

#ifndef WIN32

#include <sys/time.h>

//static
C_INT64 CopasiTimePoint::getCurrentTime_msec()
{
  timeval ttt;
  gettimeofday(&ttt, 0);
  long long int time;
  time = ttt.tv_sec * 1000 + ttt.tv_usec / 1000;
  return time & 0x7fffffffffffffff;
}
#else

#include <windows.h>
#include <winbase.h>

//static
C_INT64 CopasiTimePoint::getCurrentTime_msec()
{
  LARGE_INTEGER SystemTime;
  GetSystemTimeAsFileTime((FILETIME *) &SystemTime);

  return (SystemTime.QuadPart / 10000) & MAXLONGLONG;
}
#endif

CCopasiTimeVariable::CCopasiTimeVariable():
    mTime(0)
{}

CCopasiTimeVariable::CCopasiTimeVariable(const CCopasiTimeVariable & src):
    mTime(src.mTime)
{}

CCopasiTimeVariable::CCopasiTimeVariable(const C_INT64 & value):
    mTime(value)
{}

CCopasiTimeVariable::~CCopasiTimeVariable() {}

CCopasiTimeVariable CCopasiTimeVariable::operator + (const CCopasiTimeVariable & value)
{return mTime + value.mTime;}

CCopasiTimeVariable CCopasiTimeVariable::operator - (const CCopasiTimeVariable & value)
{return mTime - value.mTime;}

CCopasiTimeVariable & CCopasiTimeVariable::operator = (const CCopasiTimeVariable & rhs)
{
  mTime = rhs.mTime;
  return *this;
}

CCopasiTimeVariable & CCopasiTimeVariable::operator = (const C_INT64 & value)
{
  mTime = value;
  return *this;
}

std::string CCopasiTimeVariable::isoFormat() const
  {
    std::stringstream Iso;
    bool first = true;

    if (mTime < 0)
      {
        CCopasiTimeVariable Tmp(-mTime);
        Iso << "-";
        Iso << Tmp.isoFormat();

        return Iso.str();
      }

    if (mTime >= 86400000000)
      {
        Iso << LL2String(getDays()) << ":";
        first = false;
      }

    if (mTime >= 3600000000)
      Iso << LL2String(getHours(true), first ? 0 : 2) << ":";
    if (mTime >= 60000000)
      Iso << LL2String(getMinutes(true), first ? 0 : 2) << ":";
    if (mTime >= 1000000)
      Iso << LL2String(getSeconds(true), first ? 0 : 2) << ".";
    else
      Iso << "0.";

    Iso << LL2String(getMilliSeconds(true), 3) << LL2String(getMicroSeconds(true), 3);

    return Iso.str();
  }

C_INT64 CCopasiTimeVariable::getMicroSeconds(const bool & bounded) const
  {
    if (bounded) return mTime % 1000;
    else return mTime;
  }

C_INT64 CCopasiTimeVariable::getMilliSeconds(const bool & bounded) const
  {
    C_INT64 MilliSeconds =
      (mTime - (mTime % 1000)) / 1000;

    if (bounded) return MilliSeconds % 1000;
    else return MilliSeconds;
  }

C_INT64 CCopasiTimeVariable::getSeconds(const bool & bounded) const
  {
    C_INT64 Seconds =
      (mTime - (mTime % 1000000)) / 1000000;

    if (bounded) return Seconds % 60;
    else return Seconds;
  }

C_INT64 CCopasiTimeVariable::getMinutes(const bool & bounded) const
  {
    C_INT64 Minutes =
      (mTime - (mTime % 60000000)) / 60000000;

    if (bounded) return Minutes % 60;
    else return Minutes;
  }

C_INT64 CCopasiTimeVariable::getHours(const bool & bounded) const
  {
    C_INT64 Hours =
      (mTime - (mTime % 3600000000)) / 3600000000;

    if (bounded) return Hours % 24;
    else return Hours;
  }

C_INT64 CCopasiTimeVariable::getDays() const
  {
    C_INT64 Days =
      (mTime - (mTime % 86400000000)) / 86400000000;

    return Days;
  }

#ifndef WIN32

#include <sys/time.h>

//static
CCopasiTimeVariable CCopasiTimeVariable::getCurrentWallTime()
{
  timeval ttt;
  gettimeofday(&ttt, 0);
  C_INT64 time;
  time = ((C_INT64) ttt.tv_sec) * 1000000 + (C_INT64) ttt.tv_usec;
  return time;
}
#else

#include <windows.h>
#include <winbase.h>

//static
CCopasiTimeVariable CCopasiTimeVariable::getCurrentWallTime()
{
  LARGE_INTEGER SystemTime;
  GetSystemTimeAsFileTime((FILETIME *) &SystemTime);

  return SystemTime.QuadPart / 10;
}
#endif

std::string CCopasiTimeVariable::LL2String(const C_INT64 & value,
    const C_INT32 & digits)
{
  std::string format;

  if (digits > 0)
    format = "%0" + StringPrint("d", digits);
  else
    format = "%";

#ifdef WIN32
  format += "I64d";
#else
  format += "lld";
#endif

  return StringPrint(format.c_str(), value);
}
