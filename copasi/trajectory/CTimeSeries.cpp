/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTimeSeries.cpp,v $
   $Revision: 1.10 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/07/19 20:57:04 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CTimeSeries.h"
#include "model/CMetabNameInterface.h"
#include "model/CModel.h"
#include "utilities/CSort.h"

CTimeSeries::CTimeSeries()
    : mIt(begin()),
    mpState(NULL),
    mDummyString(""),
    mDummyFloat(0)
{}

bool CTimeSeries::init(C_INT32 n, CModel * pModel)
{
  //std::cout << n << std::endl;
  mpState = & pModel->getState();

  CStateTemplate & Template = pModel->getStateTemplate();

  CModelEntity **it = Template.getEntities();
  CModelEntity **end = Template.endDependent();

  resize(n + 1);
  mIt = begin();

  mTitles.resize(mpState->getNumVariable() + 1);
  mFactors.resize(mpState->getNumVariable() + 1);

  C_INT32 i;
  C_FLOAT64 Number2QuantityFactor = pModel->getNumber2QuantityFactor();

  CMetab * pMetab;
  for (i = 0; it != end; ++i, ++it)
    {
      if ((pMetab = dynamic_cast<CMetab *>(*it)) != NULL)
        {
          mTitles[i] = CMetabNameInterface::getDisplayName(pModel, *pMetab);
          mFactors[i] =
            Number2QuantityFactor / pMetab->getCompartment()->getValue();
        }
      else
        {
          mTitles[i] = (*it)->getObjectDisplayName();
          mFactors[i] = 1.0;
        }
    }

  mTitles[0] = "Time";

  mPivot.resize(mpState->getNumVariable() + 1);
  memcpy(mPivot.array(), Template.getUserOrder().array(), sizeof(unsigned C_INT32) * mPivot.size());

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
      return mpState->getNumVariable() + 1;

    return 0;
  }

const C_FLOAT64 & CTimeSeries::getData(unsigned C_INT32 step, unsigned C_INT32 var) const
  {
    if (step >= getNumSteps()) return mDummyFloat;

    if (var < mPivot.size()) return *(&(*this)[step].getTime() + mPivot[var]);

    return mDummyFloat;
  }

C_FLOAT64 CTimeSeries::getConcentrationData(unsigned C_INT32 step, unsigned C_INT32 var) const
  {
    static C_FLOAT64 tmp;

    if (step >= getNumSteps()) return mDummyFloat;

    if (var < mPivot.size())
      return tmp = *(&(*this)[step].getTime() + mPivot[var]) * mFactors[mPivot[var]];

    return mDummyFloat;
  }

const std::string & CTimeSeries::getTitle(unsigned C_INT32 var) const
  {
    if (var < mPivot.size())
      return mTitles[mPivot[var]];
    else
      return mDummyString;
  }

int CTimeSeries::save(const std::string& fileName, bool writeParticleNumbers, const std::string& separator) const
  {
    std::ofstream fileStream(utf8ToLocale(fileName).c_str());
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
