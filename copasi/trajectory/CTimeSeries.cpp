/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTimeSeries.cpp,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/09/30 15:49:16 $
   End CVS Header */

#include "CTimeSeries.h"
#include "model/CMetabNameInterface.h"
#include "model/CModel.h"

CTimeSeries::CTimeSeries()
    : mIt(begin()),
    mpState(NULL),
    mDummyString(""),
    mDummyFloat(0)
{}

bool CTimeSeries::init(C_INT32 n, CState * pState)
{
  //std::cout << n << std::endl;
  mpState = pState;

  resize(n + 1);
  mIt = begin();

  mTitles.resize(mpState->getVariableNumberSize() + 1);
  mTitles[0] = "Time";

  C_INT32 i, imax = mpState->getVariableNumberSize();
  for (i = 0; i < imax; ++i)
    mTitles[i + 1] = CMetabNameInterface::getDisplayName(mpState->getModel(),
                     *mpState->getModel()->getMetabolites()[i]);

  mFactors.resize(mpState->getVariableNumberSize() + 1);
  mFactors[0] = 1; //time
  for (i = 0; i < imax; ++i)
    mFactors[i + 1] = mpState->getModel()->getNumber2QuantityFactor()
                      * mpState->getModel()->getMetabolites()[i]->getCompartment()->getVolumeInv();

  return true;
}

bool CTimeSeries::add()
{
  //std::cout << mpState->getTime() << std::endl;;
  if (mIt == end())
    {
      C_INT32 dummy = mIt - begin();
      resize(size() + 256);
      mIt = begin() + dummy;
      //std::cout << " resize " << dummy << std::endl;
    }

  *mIt = *mpState;

  ++mIt;

  return true;
}

bool CTimeSeries::finish()
{
  //std::cout << mCounter << std::endl;
  erase(mIt, end());
  return true;
}

//*** the methods to retrieve data from the CTimeSeries *******

unsigned C_INT32 CTimeSeries::getNumSteps() const
  {return mIt - begin();}

unsigned C_INT32 CTimeSeries::getNumVariables() const
  {
    if (mpState)
      return mpState->getVariableNumberSize() + 1;

    return 0;
  }

const C_FLOAT64 & CTimeSeries::getData(unsigned C_INT32 step, unsigned C_INT32 var) const
  {
    if (step >= getNumSteps()) return mDummyFloat;

    if (var == 0) return (*this)[step].getTime();

    if (var < getNumVariables()) return (*this)[step].getVariableNumber(var - 1);

    return mDummyFloat;
  }

C_FLOAT64 CTimeSeries::getConcentrationData(unsigned C_INT32 step, unsigned C_INT32 var) const
  {
    static C_FLOAT64 tmp;

    if (step >= getNumSteps()) return mDummyFloat;

    if (var == 0) return (*this)[step].getTime();

    if (var < getNumVariables())
      return tmp = (*this)[step].getVariableNumber(var - 1) * mFactors[var];

    return mDummyFloat;
  }

const std::string & CTimeSeries::getTitle(unsigned C_INT32 var) const
  {
    if (var < mTitles.size())
      return mTitles[var];
    else
      return mDummyString;
  }
