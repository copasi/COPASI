/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CopasiTime.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/09/15 20:47:52 $
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
