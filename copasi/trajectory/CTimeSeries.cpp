/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTimeSeries.cpp,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:18:03 $
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

int CTimeSeries::save(const std::string& fileName, bool writeParticleNumbers, const std::string& separator) const
  {
    std::ofstream fileStream(fileName.c_str());
    std::ostringstream* stringStream = new std::ostringstream();
    (*stringStream) << "# ";
    unsigned int counter2;
    unsigned int maxCount2 = this->getNumVariables();
    for (counter2 = 0; counter2 < maxCount2;++counter2)
      {
        (*stringStream) << this->getTitle(counter2) << separator;
      }
    (*stringStream) << std::endl;
    fileStream << stringStream->str();
    if (!fileStream.good()) return 1;
    unsigned int counter;
    unsigned int maxCount = this->getNumSteps();
    for (counter = 0; counter < maxCount;++counter)
      {
        delete stringStream;
        stringStream = new std::ostringstream();
        for (counter2 = 0; counter2 < maxCount2;++counter2)
          {
            C_FLOAT64 value;
            if (writeParticleNumbers)
              {
                value = this->getData(counter, counter2);
              }
            else
              {
                value = this->getConcentrationData(counter, counter2);
              }
            (*stringStream) << value << separator;
          }
        (*stringStream) << std::endl;
        fileStream << stringStream->str();
        if (!fileStream.good()) return 1;
      }
    fileStream.close();
    delete stringStream;
    return 0;
  }
