/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTimeSeries.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/09/30 15:49:16 $
   End CVS Header */

#ifndef TIMESERIES_H
#define TIMESERIES_H

#include <vector>
#include "model/CState.h"

class CTimeSeries : private std::vector<CState>
  {
  public:

    CTimeSeries();

    //**** put data into time series ***

    /**
     * initialization
     * @param n prospective number of steps
     * @param pState the CState from which the date should be taken
     * @return success 
     */
    bool init(C_INT32 n, CState * pState);

    bool add();

    bool finish();

    //**** get data from time series ***

    unsigned C_INT32 getNumSteps() const;
    unsigned C_INT32 getNumVariables() const;
    const C_FLOAT64 & getData(unsigned C_INT32 step, unsigned C_INT32 var) const;
    C_FLOAT64 getConcentrationData(unsigned C_INT32 step, unsigned C_INT32 var) const;
    const std::string & getTitle(unsigned C_INT32 var) const;

  private:
    //C_INT32 mN;
    //C_INT32 mCounter;
    std::vector<CState>::iterator mIt;
    CState * mpState;
    std::vector<std::string> mTitles;
    std::vector<C_FLOAT64> mFactors;
    std::string mDummyString;
    C_FLOAT64 mDummyFloat;
  };

#endif
