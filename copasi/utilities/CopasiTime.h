/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CopasiTime.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/08/31 12:21:14 $
   End CVS Header */

#ifndef COPASI_time
#define COPASI_time

#include <sys/time.h>
#include "copasi.h"

class CopasiTimePoint
  {
  public:
    CopasiTimePoint();

    C_INT32 init();

    C_INT32 get() const;

    C_INT32 getTimeDiff() const;

  private:
    C_INT32 mTime;

    static C_INT32 getCurrentTime_msec();
  };

#endif
