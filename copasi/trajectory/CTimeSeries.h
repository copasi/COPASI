/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTimeSeries.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/09/24 13:57:30 $
   End CVS Header */

#ifndef TIMESERIES_H
#define TIMESERIES_H

#include <vector>
#include "model/CState.h"

class CTimeSeries : public std::vector<CState>
  {
  };

#endif
