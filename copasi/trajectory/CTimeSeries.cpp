// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTimeSeries.cpp,v $
//   $Revision: 1.21.4.4 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2011/03/30 11:44:46 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <limits>

#include "copasi.h"

#include "CTimeSeries.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include "model/CMetabNameInterface.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"
#include "commandline/CLocaleString.h"

#include "sbml/SBase.h"
#include "sbml/Compartment.h"
#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/Model.h"

// static
std::string CTimeSeries::mDummyString("");

// static
C_FLOAT64 CTimeSeries::mDummyFloat(0.0);

CTimeSeries::CTimeSeries():
    COutputInterface(),
    CMatrix< C_FLOAT64 >(),
    mAllocatedSteps(0),
    mRecordedSteps(0),
    mpIt(mArray),
    mpEnd(mArray + size()),
    mpState(NULL),
    mTitles(),
    mCompartment(),
    mPivot(),
    mKeys(),
    mNumberToQuantityFactor(0.0)
{}

CTimeSeries::CTimeSeries(const CTimeSeries & src):
    COutputInterface(src),
    CMatrix< C_FLOAT64 >(src),
    mAllocatedSteps(src.mAllocatedSteps),
    mRecordedSteps(src.mRecordedSteps),
    mpIt(mArray + mRecordedSteps * mCols),
    mpEnd(mArray + size()),
    mpState(src.mpState),
    mTitles(src.mTitles),
    mCompartment(src.mCompartment),
    mPivot(src.mPivot),
    mKeys(src.mKeys),
    mNumberToQuantityFactor(src.mNumberToQuantityFactor)
{}

CTimeSeries::~CTimeSeries()
{}

void CTimeSeries::allocate(const size_t & steps)
{
  // The actual allocation is deferred to compile
  mAllocatedSteps = steps;
}

void CTimeSeries::clear()
{
  mObjects.clear();
  CMatrix< C_FLOAT64 >::resize(0, 0);
  mAllocatedSteps = mRows;
  mRecordedSteps = 0;
  mpIt = mArray;
  mpEnd = mArray + size();
  mpState = NULL;
  mTitles.clear();
  mCompartment.resize(0);
  mPivot.resize(0);
  mKeys.clear();
  mNumberToQuantityFactor = 0.0;
}

// virtual
bool CTimeSeries::compile(std::vector< CCopasiContainer * > listOfContainer,
                          const CCopasiDataModel* pDataModel)
{
  const CModel * pModel =
    dynamic_cast< const CModel * >(pDataModel->ObjectFromName(listOfContainer, pDataModel->getModel()->getCN()));

  if (pModel == NULL)
    return false;

  mpState = & pModel->getState();

  const CStateTemplate & Template = pModel->getStateTemplate();

  // We store all variables of the system.
  // The reason for this is that events will be able to change even fixed values.
  CModelEntity *const* it = Template.getEntities();
  CModelEntity *const* end = Template.endFixed();

  size_t i, imax = end - it;

  CMatrix< C_FLOAT64 >::resize(mAllocatedSteps + 1, imax);

  mObjects.clear();

  mPivot.resize(imax);
  mTitles.resize(imax);
  mCompartment.resize(imax);
  mKeys.resize(imax);

  mRecordedSteps = 0;
  mpIt = mArray;
  mpEnd = mArray + size();
  mCompartment = C_INVALID_INDEX;

  mNumberToQuantityFactor = pModel->getNumber2QuantityFactor();

  const CMetab * pMetab;

  for (i = 0; it != end; ++i, ++it)
    {
      if ((pMetab = dynamic_cast< const CMetab *>(*it)) != NULL)
        {
          mTitles[i] = CMetabNameInterface::getDisplayName(pModel, *pMetab);
          mCompartment[i] = Template.getIndex(pMetab->getCompartment());
        }
      else
        {
          mTitles[i] = (*it)->getObjectDisplayName();
        }

      mKeys[i] = (*it)->getKey();

      mObjects.insert((*it)->getValueReference());
    }

  mTitles[0] = "Time";
  mKeys[0] = pModel->getKey();

  const size_t * pUserOrder = Template.getUserOrder().array();
  const size_t * pUserOrderEnd = pUserOrder + Template.getUserOrder().size();
  it = Template.getEntities();

  for (i = 0; pUserOrder != pUserOrderEnd; ++pUserOrder)
    mPivot[i++] = *pUserOrder;

  return true;
}

// virtual
void CTimeSeries::output(const COutputInterface::Activity & activity)
{
  if (activity != DURING)
    return;

  // We may have to reallocate due to additional output caused from events
  if (mpIt == mpEnd)
    {
      size_t diff;
      diff = mAllocatedSteps / 4;

      if (diff < 10)
        diff = 10;
      else if (diff > 10000)
        diff = 10000;

      mAllocatedSteps += diff;
      CMatrix< C_FLOAT64 >::resize(mAllocatedSteps, mCols, true);

      mpIt = mArray + mRecordedSteps * mCols;
      mpEnd = mArray + size();
    }

  if (mpIt != mpEnd)
    {
      memcpy(mpIt, &mpState->getTime(), mCols * sizeof(C_FLOAT64));
      mpIt += mCols;
      mRecordedSteps++;
    }
}

// virtual
void CTimeSeries::separate(const COutputInterface::Activity & /* activity */)
{
  if (mpIt != mpEnd)
    {
      C_FLOAT64 * pIt = mpIt;
      mpIt += mCols;
      mRecordedSteps++;

      // We copy NaN to indicate separation, which is similar to plotting.
      for (; pIt != mpIt; ++pIt)
        *pIt = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
    }
}

// virtual
void CTimeSeries::finish()
{}

//*** the methods to retrieve data from the CTimeSeries *******

const size_t & CTimeSeries::getRecordedSteps() const
{return mRecordedSteps;}

const size_t & CTimeSeries::getNumVariables() const
{return mCols;}

const C_FLOAT64 & CTimeSeries::getData(const size_t & step,
                                       const size_t & var) const
{
  if (step < mRecordedSteps && var < mCols)
    return *(mArray + step * mCols + mPivot[var]);

  return mDummyFloat;
}

C_FLOAT64 CTimeSeries::getConcentrationData(const size_t & step,
    const size_t & var) const
{
  if (step < mRecordedSteps && var < mCols)
    {
      const size_t & Col = mPivot[var];

      if (mCompartment[Col] != C_INVALID_INDEX)
        return *(mArray + step * mCols + Col) * mNumberToQuantityFactor / *(mArray + step * mCols + mCompartment[Col]);
      else
        return *(mArray + step * mCols + Col);
    }

  return mDummyFloat;
}

const std::string & CTimeSeries::getTitle(const size_t & var) const
{
  if (var < mCols)
    return mTitles[mPivot[var]];

  return mDummyString;
}

const std::string & CTimeSeries::getKey(const size_t & var) const
{
  if (var < mCols)
    return mKeys[mPivot[var]];

  return mDummyString;
}

std::string CTimeSeries::getSBMLId(const size_t & var, const CCopasiDataModel* pDataModel) const
{
  std::string key = getKey(var);
  std::string result("");

  if (key != mDummyString)
    {
      const CCopasiObject* pObject = CCopasiRootContainer::getKeyFactory()->get(key);

      if (pObject != NULL)
        {
          std::map<CCopasiObject*, SBase*>::const_iterator pos = const_cast<CCopasiDataModel*>(pDataModel)->getCopasi2SBMLMap().find(const_cast<CCopasiObject*>(pObject));

          if (pos != const_cast<CCopasiDataModel*>(pDataModel)->getCopasi2SBMLMap().end())
            {
              const SBase* pSBMLObject = pos->second;
              const Compartment* pSBMLCompartment = NULL;
              const Species* pSBMLSpecies = NULL;
              const Parameter* pSBMLParameter = NULL;
              const Model* pSBMLModel = NULL;

              switch (pSBMLObject->getTypeCode())
                {
                  case SBML_COMPARTMENT:
                    pSBMLCompartment = dynamic_cast<const Compartment*>(pSBMLObject);

                    if (pSBMLCompartment && pSBMLCompartment->isSetId())
                      {
                        result = pSBMLCompartment->getId();
                      }

                    break;
                  case SBML_SPECIES:
                    pSBMLSpecies = dynamic_cast<const Species*>(pSBMLObject);

                    if (pSBMLSpecies && pSBMLSpecies->isSetId())
                      {
                        result = pSBMLSpecies->getId();
                      }

                    break;
                  case SBML_PARAMETER:
                    pSBMLParameter = dynamic_cast<const Parameter*>(pSBMLObject);

                    if (pSBMLParameter && pSBMLParameter->isSetId())
                      {
                        result = pSBMLParameter->getId();
                      }

                    break;
                  case SBML_MODEL:
                    pSBMLModel = dynamic_cast<const Model*>(pSBMLObject);

                    if (pSBMLModel && pSBMLModel->isSetId())
                      {
                        result = pSBMLModel->getId();
                      }

                    break;
                  default:
                    break;
                }
            }
        }
    }

  return result;
}

int CTimeSeries::save(const std::string& fileName, bool writeParticleNumbers, const std::string& separator) const
{
  std::ofstream fileStream(CLocaleString::fromUtf8(fileName).c_str());
  std::ostringstream* stringStream = new std::ostringstream();
  (*stringStream) << "# ";
  size_t counter2;
  size_t maxCount2 = this->getNumVariables();

  for (counter2 = 0; counter2 < maxCount2; ++counter2)
    {
      (*stringStream) << this->getTitle(counter2) << separator;
    }

  (*stringStream) << std::endl;
  fileStream << stringStream->str();

  if (!fileStream.good()) return 1;

  size_t counter;
  size_t maxCount = mRecordedSteps;

  for (counter = 0; counter < maxCount; ++counter)
    {
      delete stringStream;
      stringStream = new std::ostringstream();

      for (counter2 = 0; counter2 < maxCount2; ++counter2)
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
