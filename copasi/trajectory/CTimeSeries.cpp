// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <limits>

#include "copasi/copasi.h"

#include "CTimeSeries.h"

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/math/CMathContainer.h"
#include "copasi/model/CMetabNameInterface.h"
#include "copasi/model/CModel.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/commandline/CLocaleString.h"

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
  mNumVariables(0),
  mpIt(mpBuffer),
  mpEnd(mpBuffer + size()),
  mContainerValues(),
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
  mNumVariables(src.mNumVariables),
  mpIt(mpBuffer + mRecordedSteps * mCols),
  mpEnd(mpBuffer + size()),
  mContainerValues(),
  mTitles(src.mTitles),
  mCompartment(src.mCompartment),
  mPivot(src.mPivot),
  mKeys(src.mKeys),
  mNumberToQuantityFactor(src.mNumberToQuantityFactor)
{
  mContainerValues.initialize(src.mContainerValues);
}

CTimeSeries::~CTimeSeries()
{}

void CTimeSeries::allocate(const size_t & steps)
{
  // The actual allocation is deferred to compile
  mAllocatedSteps = steps;
}

void CTimeSeries::increaseAllocation()
{
  size_t diff;
  diff = mAllocatedSteps / 4;

  if (diff < 10)
    diff = 10;
  else if (diff > 10000)
    diff = 10000;

  mAllocatedSteps += diff;
  CMatrix< C_FLOAT64 >::resize(mAllocatedSteps, mCols, true);

  mpIt = mpBuffer + mRecordedSteps * mCols;
  mpEnd = mpBuffer + size();
}

void CTimeSeries::clear()
{
  mObjects.clear();
  CMatrix< C_FLOAT64 >::resize(0, 0);
  mAllocatedSteps = mRows;
  mRecordedSteps = 0;
  mNumVariables = 0;
  mpIt = mpBuffer;
  mpEnd = mpBuffer + size();
  mTitles.clear();
  mCompartment.resize(0);
  mPivot.resize(0);
  mKeys.clear();
  mNumberToQuantityFactor = 0.0;
}

// virtual
bool CTimeSeries::compile(CObjectInterface::ContainerList listOfContainer)
{
  CObjectInterface::ContainerList::const_iterator itContainer = listOfContainer.begin();
  CObjectInterface::ContainerList::const_iterator endContainer = listOfContainer.end();
  const CMathContainer * pContainer = NULL;

  for (; itContainer != endContainer && pContainer == NULL; ++itContainer)
    {
      pContainer = dynamic_cast< const CMathContainer * >(*itContainer);
    }

  if (pContainer == NULL)
    return false;

  assert(pContainer != NULL);

  // We store all extensive values of the system.
  size_t Time = 0;
  size_t Reaction = Time + 1;
  size_t ODE = Reaction + pContainer->getCountIndependentSpecies() + pContainer->getCountDependentSpecies();
  size_t EventTarget = ODE + pContainer->getCountODEs();
  size_t Assignment = EventTarget + pContainer->getCountFixedEventTargets();
  size_t Fixed = Assignment + pContainer->getCountAssignments();
  size_t i, imax = Fixed + pContainer->getCountFixed();
  size_t EventTargetCount = 0;

  mContainerValues.initialize(imax, const_cast< C_FLOAT64 * >(pContainer->getState(false).array()) - pContainer->getCountFixed());

  const CMathObject * pFirstObject = pContainer->getMathObject(mContainerValues.array());
  const CMathObject * pObject = pFirstObject;
  const CMathObject * pObjectEnd = pObject + imax;

  mObjects.clear();

  CMatrix< C_FLOAT64 >::resize(mAllocatedSteps + 1, imax);

  mPivot.resize(imax);
  mTitles.resize(imax);
  mCompartment.resize(imax);
  mKeys.resize(imax);
  mCompartment = C_INVALID_INDEX;

  mRecordedSteps = 0;
  mNumVariables = Fixed;
  mpIt = mpBuffer;
  mpEnd = mpBuffer + size();

  mNumberToQuantityFactor = pContainer->getModel().getNumber2QuantityFactor();

  const CMetab * pMetab;

  for (i = 0; pObject != pObjectEnd; ++i, ++pObject)
    {
      switch (pObject->getSimulationType())
        {
          case CMath::SimulationType::Fixed:
            mPivot[Fixed++] = i;

            // We do not expose Fixed values we keep them for internal calculations.
            continue;
            break;

          case CMath::SimulationType::EventTarget:
            EventTargetCount++;
            mPivot[EventTarget++] = i;
            break;

          case CMath::SimulationType::Time:
            mPivot[Time++] = i;
            break;

          case CMath::SimulationType::ODE:
            mPivot[ODE++] = i;
            break;

          case CMath::SimulationType::Independent:
          case CMath::SimulationType::Dependent:
            mPivot[Reaction++] = i;
            break;

          case CMath::SimulationType::Assignment:
            mPivot[Assignment++] = i;
            break;

          case CMath::SimulationType::Conversion:

            if (EventTargetCount < pContainer->getCountFixedEventTargets())
              {
                EventTargetCount++;
                mPivot[EventTarget++] = i;
              }
            else
              {
                mPivot[Assignment++] = i;
              }

            break;

          case CMath::SimulationType::__SIZE:
            break;
        }

      const CDataObject * pDataObject = CObjectInterface::DataObject(pObject);

      if ((pMetab = dynamic_cast< const CMetab *>(pDataObject->getObjectParent())) != NULL)
        {
          mTitles[i] = CMetabNameInterface::getDisplayName(&pContainer->getModel(), *pMetab, false);
          mCompartment[i] = pContainer->getMathObject(pMetab->getCompartment()->getValueReference()) - pFirstObject;
        }
      else if (dynamic_cast< const CModel *>(pDataObject->getObjectParent()) != NULL)
        {
          mTitles[i] = "Time";
        }
      else
        {
          mTitles[i] = pDataObject->getObjectParent()->getObjectDisplayName();
        }

      mKeys[i] = pDataObject->getObjectParent()->getKey();
      mObjects.insert(pObject);
    }

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
      increaseAllocation();
    }

  if (mpIt != mpEnd)
    {
      memcpy(mpIt, mContainerValues.array(), mCols * sizeof(C_FLOAT64));
      mpIt += mCols;
      mRecordedSteps++;
    }
}

// virtual
void CTimeSeries::separate(const COutputInterface::Activity & /* activity */)
{
  // We may have to reallocate due to additional output caused from events
  if (mpIt == mpEnd)
    {
      increaseAllocation();
    }

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
{return mNumVariables;}

const C_FLOAT64 & CTimeSeries::getData(const size_t & step,
                                       const size_t & var) const
{
  if (step < mRecordedSteps && var < mNumVariables)
    return *(mpBuffer + step * mCols + mPivot[var]);

  return mDummyFloat;
}

C_FLOAT64 CTimeSeries::getConcentrationData(const size_t & step,
    const size_t & var) const
{
  if (step < mRecordedSteps && var < mNumVariables)
    {
      const size_t & Col = mPivot[var];

      if (mCompartment[Col] != C_INVALID_INDEX)
        return *(mpBuffer + step * mCols + Col) * mNumberToQuantityFactor / *(mpBuffer + step * mCols + mCompartment[Col]);
      else
        return *(mpBuffer + step * mCols + Col);
    }

  return mDummyFloat;
}

const std::string & CTimeSeries::getTitle(const size_t & var) const
{
  if (var < mNumVariables)
    return mTitles[mPivot[var]];

  return mDummyString;
}

const std::string & CTimeSeries::getKey(const size_t & var) const
{
  if (var < mNumVariables)
    return mKeys[mPivot[var]];

  return mDummyString;
}

std::string CTimeSeries::getSBMLId(const size_t & var, const CDataModel* pDataModel) const
{
  std::string key = getKey(var);
  std::string result("");

  if (key != mDummyString)
    {
      const CDataObject* pObject = CRootContainer::getKeyFactory()->get(key);

      if (pObject != NULL)
        {
          std::map<const CDataObject*, SBase*>::const_iterator pos = const_cast<CDataModel*>(pDataModel)->getCopasi2SBMLMap().find(const_cast<CDataObject*>(pObject));

          if (pos != const_cast<CDataModel*>(pDataModel)->getCopasi2SBMLMap().end())
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


int
CTimeSeries::save(std::ostream& str, bool writeParticleNumbers,
                  const std::string& separator) const
{
  std::ostringstream stringStream;
  stringStream << "# ";
  size_t counter2;
  size_t maxCount2 = this->getNumVariables();

  for (counter2 = 0; counter2 < maxCount2; ++counter2)
    {
      stringStream << this->getTitle(counter2) << separator;
    }

  stringStream << std::endl;
  str << stringStream.str();

  if (!str.good()) return 1;

  size_t counter;
  size_t maxCount = mRecordedSteps;

  for (counter = 0; counter < maxCount; ++counter)
    {
      stringStream.str("");
      stringStream.clear();

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

          stringStream << value << separator;
        }

      stringStream << std::endl;
      str << stringStream.str();

      if (!str.good()) return 1;
    }

  return 0;
}

int CTimeSeries::save(const std::string& fileName, bool writeParticleNumbers, const std::string& separator) const
{
  std::ofstream fileStream(CLocaleString::fromUtf8(fileName).c_str());
  int result = save(fileStream, writeParticleNumbers, separator);
  fileStream.close();
  return result;
}
