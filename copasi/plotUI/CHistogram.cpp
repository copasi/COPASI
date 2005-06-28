/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/Attic/CHistogram.cpp,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/28 17:09:14 $
   End CVS Header */

#include <float.h>

#include "CHistogram.h"

//  public:

CHistogram::CHistogram():
    mIncrement(0.1),
    mUptodate(false),
    mXArray(NULL),
    mYArray(NULL),
    mArraySize(0),
    mCount(0)
{
  mInvIncrement = 1 / mIncrement;
}

CHistogram::CHistogram(C_FLOAT64 incr):
    mIncrement(incr),
    mUptodate(false),
    mXArray(NULL),
    mYArray(NULL),
    mArraySize(0),
    mCount(0)
{
  mInvIncrement = 1 / mIncrement;
}

CHistogram::~CHistogram()
{
  if (mXArray)
    delete[] mXArray;
  if (mYArray)
    delete[] mYArray;
}

void CHistogram::addValue(const C_FLOAT64 & val)
{
  //just ignore breaks. Later we perhaps want to start a new histogram...
  if (isnan(val)) //NaN
    return;

  mUptodate = false;
  //std::cout << val<< "  " << (C_INT32)(val/mIncrement)<< std::endl;
  mMap[(C_INT32)(val * mInvIncrement)]++;
  mMap[(((C_INT32)(val * mInvIncrement))) + 1];
  ++mCount;
}

const double* CHistogram::getXArray()
{
  if (!mUptodate)
    updateArray();
  return mXArray;
}

const double* CHistogram::getYArray()
{
  if (!mUptodate)
    updateArray();
  return mYArray;
}

int CHistogram::size()
{
  if (!mUptodate)
    updateArray();
  return mArraySize;
}

//private
void CHistogram::updateArray()
{
  if (mUptodate)
    return; //do nothing

  //delete Arrays
  if (mXArray)
    delete[] mXArray;
  if (mYArray)
    delete[] mYArray;

  //construct arrays
  mXArray = new double[mMap.size()];
  mYArray = new double[mMap.size()];
  mArraySize = mMap.size();

  C_FLOAT64 tmpFactor = 1 / (mCount * mIncrement);

  C_INT32 i;
  std::map<C_INT32, C_INT32>::const_iterator it, itEnd = mMap.end();
  for (it = mMap.begin(), i = 0; it != itEnd; ++it, ++i)
    {//TODO use pointer increments instead of [...]
      mXArray[i] = it->first * mIncrement;
      mYArray[i] = (double)it->second * tmpFactor;
      //std::cout <<it->first <<" " <<it->second << std::endl;
    }

  mUptodate = true;
}
