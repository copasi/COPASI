/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CopasiTime.cpp,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/01/28 17:14:53 $
   End CVS Header */

#include <time.h>

#ifdef WIN32
# include <windows.h>
# include <winbase.h>
#else
# include <sys/time.h>
# include <sys/resource.h>
#endif // WIN32

#include <sstream>

#include "copasi.h"
#include "CopasiTime.h"
#include "utility.h"

CCopasiTimeVariable::CCopasiTimeVariable():
    mTime(LLONG_CONST(0))
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

bool CCopasiTimeVariable::operator < (const CCopasiTimeVariable & value)
{return (mTime < value.mTime);}

std::string CCopasiTimeVariable::isoFormat() const
  {
    std::stringstream Iso;
    bool first = true;

    if (mTime < LLONG_CONST(0))
      {
        CCopasiTimeVariable Tmp(-mTime);
        Iso << "-";
        Iso << Tmp.isoFormat();

        return Iso.str();
      }

    if (mTime >= LLONG_CONST(86400000000))
      {
        Iso << LL2String(getDays()) << ":";
        first = false;
      }

    if (mTime >= LLONG_CONST(3600000000))
      Iso << LL2String(getHours(true), first ? 0 : 2) << ":";
    if (mTime >= LLONG_CONST(60000000))
      Iso << LL2String(getMinutes(true), first ? 0 : 2) << ":";
    if (mTime >= LLONG_CONST(1000000))
      Iso << LL2String(getSeconds(true), first ? 0 : 2) << ".";
    else
      Iso << "0.";

    Iso << LL2String(getMilliSeconds(true), 3) << LL2String(getMicroSeconds(true), 3);

    return Iso.str();
  }

C_INT64 CCopasiTimeVariable::getMicroSeconds(const bool & bounded) const
  {
    if (bounded) return mTime % LLONG_CONST(1000);
    else return mTime;
  }

C_INT64 CCopasiTimeVariable::getMilliSeconds(const bool & bounded) const
  {
    C_INT64 MilliSeconds = mTime / LLONG_CONST(1000);

    if (bounded) return MilliSeconds % LLONG_CONST(1000);
    else return MilliSeconds;
  }

C_INT64 CCopasiTimeVariable::getSeconds(const bool & bounded) const
  {
    C_INT64 Seconds = mTime / LLONG_CONST(1000000);

    if (bounded) return Seconds % LLONG_CONST(60);
    else return Seconds;
  }

C_INT64 CCopasiTimeVariable::getMinutes(const bool & bounded) const
  {
    C_INT64 Minutes = mTime / LLONG_CONST(60000000);

    if (bounded) return Minutes % LLONG_CONST(60);
    else return Minutes;
  }

C_INT64 CCopasiTimeVariable::getHours(const bool & bounded) const
  {
    C_INT64 Hours = mTime / LLONG_CONST(3600000000);

    if (bounded) return Hours % LLONG_CONST(24);
    else return Hours;
  }

C_INT64 CCopasiTimeVariable::getDays() const
  {
    C_INT64 Days = mTime / LLONG_CONST(86400000000);

    return Days;
  }

#ifndef WIN32

//static
CCopasiTimeVariable CCopasiTimeVariable::getCurrentWallTime()
{
  timeval ttt;
  gettimeofday(&ttt, 0);
  C_INT64 time;
  time = ((C_INT64) ttt.tv_sec) * LLONG_CONST(1000000) + (C_INT64) ttt.tv_usec;
  return time;
}
#else

//static
CCopasiTimeVariable CCopasiTimeVariable::getCurrentWallTime()
{
  LARGE_INTEGER SystemTime;
  GetSystemTimeAsFileTime((FILETIME *) &SystemTime);

  return SystemTime.QuadPart / LLONG_CONST(10);
}
#endif

CCopasiTimeVariable CCopasiTimeVariable::getCPUTime()
{
#ifdef WIN32
  LARGE_INTEGER CreationTime;
  LARGE_INTEGER ExitTime;
  LARGE_INTEGER KernelTime;
  LARGE_INTEGER UserTime;

  GetProcessTimes(GetCurrentProcess(),
                  (FILETIME *) &CreationTime,
                  (FILETIME *) &ExitTime,
                  (FILETIME *) &KernelTime,
                  (FILETIME *) &UserTime);

  return UserTime.QuadPart / LLONG_CONST(10);

#else
  struct rusage ResourceUsage;

  getrusage(RUSAGE_SELF, &ResourceUsage);

  return ((C_INT64) ResourceUsage.ru_utime.tv_sec) * LLONG_CONST(1000000)
  + (C_INT64) ResourceUsage.ru_utime.tv_usec;
#endif // WIN32
}

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
