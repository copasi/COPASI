/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTimeSeries.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:18:03 $
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

    int save(const std::string& fileName, bool writeConcentrations = false, const std::string& separator = "\t") const;

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
