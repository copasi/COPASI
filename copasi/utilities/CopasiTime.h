/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CopasiTime.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/01/24 18:39:27 $
   End CVS Header */

#ifndef COPASI_time
#define COPASI_time

#include "copasi.h"

class CopasiTimePoint
  {
  public:
    CopasiTimePoint();

    C_INT32 init();

    C_INT32 get() const;

    C_INT32 getTimeDiff() const;

  private:
    C_INT64 mTime;

    static C_INT64 getCurrentTime_msec();
  };

class CCopasiTimeVariable
  {
  public:
    CCopasiTimeVariable();

    CCopasiTimeVariable(const CCopasiTimeVariable & src);

    CCopasiTimeVariable(const C_INT64 & value);

    ~CCopasiTimeVariable();

    CCopasiTimeVariable operator + (const CCopasiTimeVariable & value);

    CCopasiTimeVariable operator - (const CCopasiTimeVariable & value);

    CCopasiTimeVariable & operator = (const CCopasiTimeVariable & rhs);

    CCopasiTimeVariable & operator = (const C_INT64 & value);

    std::string isoFormat() const;

    C_INT64 getMicroSeconds(const bool & bounded = false) const;

    C_INT64 getMilliSeconds(const bool & bounded = false) const;

    C_INT64 getSeconds(const bool & bounded = false) const;

    C_INT64 getMinutes(const bool & bounded = false) const;

    C_INT64 getHours(const bool & bounded = false) const;

    C_INT64 getDays() const;

    static CCopasiTimeVariable getCurrentWallTime();

  private:
    static std::string LL2String(const C_INT64 & value,
                                 const C_INT32 & digits = 0);

  private:
    C_INT64 mTime;
  };

#endif
