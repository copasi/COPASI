/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CopasiTime.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:18:04 $
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
    C_INT32 mTime;

    static C_INT32 getCurrentTime_msec();
  };

#endif
