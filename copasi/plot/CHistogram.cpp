/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/CHistogram.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/02/14 13:41:47 $
   End CVS Header */

#include "CHistogram.h"

//  public:

CHistogram::CHistogram():
    mIncrement(0.1),
    mUptodate(false),
    mXArray(NULL),
    mYArray(NULL),
    mArraySize(0),
    mCount(0)
{}

CHistogram::CHistogram(C_FLOAT64 incr):
    mIncrement(incr),
    mUptodate(false),
    mXArray(NULL),
    mYArray(NULL),
    mArraySize(0),
    mCount(0)
{}

CHistogram::~CHistogram()
{
  if (mXArray)
    delete[] mXArray;
  if (mYArray)
    delete[] mYArray;
}

void CHistogram::addValue(const C_FLOAT64 & val)
{
  mUptodate = false;
  //std::cout << val<< "  " << (C_INT32)(val/mIncrement)<< std::endl;
  mMap[(C_INT32)(val / mIncrement)]++;
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

  //construct arrays
  mXArray = new double[mMap.size()];
  mYArray = new double[mMap.size()];
  mArraySize = mMap.size();

  C_INT32 i;
  std::map<C_INT32, C_INT32>::const_iterator it, itEnd = mMap.end();
  for (it = mMap.begin(), i = 0; it != itEnd; ++it, ++i)
    {//TODO use pointer increments instead of [...]
      mXArray[i] = it->first * mIncrement;
      mYArray[i] = (double)it->second / mCount / mIncrement;
      //std::cout <<it->first <<" " <<it->second << std::endl;
    }

  mUptodate = true;
}
