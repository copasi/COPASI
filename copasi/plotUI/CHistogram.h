/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/Attic/CHistogram.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/02/14 13:41:47 $
   End CVS Header */

#ifndef CHISTOGRAM
#define CHISTOGRAM

//#include <string>
#include <vector>
#include <map>
#include "copasi.h"

// "int" and "double" are use in this class because of the qwt interface

class CHistogram
  {
  private:
    CHistogram();
  public:
    CHistogram(C_FLOAT64 incr);

    ~CHistogram();

    void addValue(const C_FLOAT64 & val);

    const double* getXArray();
    const double* getYArray();
    int size();

  private:
    C_FLOAT64 mIncrement;
    bool mUptodate;
    double* mXArray;
    double* mYArray;
    int mArraySize;

    void updateArray();

    //for the histogram
    std::map<C_INT32, C_INT32> mMap;
    C_INT32 mCount;
  };

#endif
