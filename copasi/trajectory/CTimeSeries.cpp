// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTimeSeries.cpp,v $
//   $Revision: 1.14.6.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/22 14:14:35 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CTimeSeries.h"
#include "model/CMetabNameInterface.h"
#include "model/CModel.h"
#include "utilities/CSort.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CKeyFactory.h"

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
    CMatrix< C_FLOAT64 >(),
    mNumSteps(0),
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
    CMatrix< C_FLOAT64 >(src),
    mNumSteps(src.mNumSteps),
    mpIt(mArray + mNumSteps * mCols),
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

bool CTimeSeries::init(C_INT32 n, CModel * pModel)
{
  //std::cout << n << std::endl;
  mpState = & pModel->getState();

  CStateTemplate & Template = pModel->getStateTemplate();

  // We store all variables of the system.
  // The reason for this is that events will be able to change even fixed values.
  CModelEntity **it = Template.getEntities();
  CModelEntity **end = Template.endFixed();

  C_INT32 i, imax = end - it;

  resize(n + 1, imax);

  mPivot.resize(imax);
  mTitles.resize(imax);
  mCompartment.resize(imax);
  mKeys.resize(imax);

  mNumSteps = 0;
  mpIt = mArray;
  mpEnd = mArray + size();
  mCompartment = C_INVALID_INDEX;

  mNumberToQuantityFactor = pModel->getNumber2QuantityFactor();

  CMetab * pMetab;

  for (i = 0; it != end; ++i, ++it)
    {
      if ((pMetab = dynamic_cast<CMetab *>(*it)) != NULL)
        {
          mTitles[i] = CMetabNameInterface::getDisplayName(pModel, *pMetab);
          mCompartment[i] = Template.getIndex(pMetab->getCompartment());
        }
      else
        {
          mTitles[i] = (*it)->getObjectDisplayName();
        }

      mKeys[i] = (*it)->getKey();
    }

  mTitles[0] = "Time";
  mKeys[0] = pModel->getKey();

  const unsigned C_INT32 * pUserOrder = Template.getUserOrder().array();
  const unsigned C_INT32 * pUserOrderEnd = pUserOrder + Template.getUserOrder().size();
  it = Template.getEntities();

  for (i = 0; pUserOrder != pUserOrderEnd; ++pUserOrder)
    //    if (it[*pUserOrder]->isUsed())
    mPivot[i++] = *pUserOrder;

  return true;
}

bool CTimeSeries::add()
{
  if (mpIt != mpEnd)
    {
      memcpy(mpIt, &mpState->getTime(), mCols * sizeof(C_FLOAT64));
      mpIt += mCols;
      mNumSteps++;

      return true;
    }

  return false;
}

bool CTimeSeries::finish()
{
  return true;
}

//*** the methods to retrieve data from the CTimeSeries *******

unsigned C_INT32 CTimeSeries::getNumSteps() const
  {return mNumSteps;}

unsigned C_INT32 CTimeSeries::getNumVariables() const
  {return mCols;}

const C_FLOAT64 & CTimeSeries::getData(const unsigned C_INT32 & step,
                                       const unsigned C_INT32 & var) const
  {
    if (step < mNumSteps && var < mCols)
      return *(mArray + step * mCols + mPivot[var]);

    return mDummyFloat;
  }

C_FLOAT64 CTimeSeries::getConcentrationData(const unsigned C_INT32 & step,
    const unsigned C_INT32 & var) const
  {
    if (step < mNumSteps && var < mCols)
      {
        const unsigned C_INT32 & Col = mPivot[var];
        if (mCompartment[Col] != C_INVALID_INDEX)
          return *(mArray + step * mCols + Col) * mNumberToQuantityFactor / *(mArray + step * mCols + mCompartment[Col]);
        else
          return *(mArray + step * mCols + Col);
      }

    return mDummyFloat;
  }

const std::string & CTimeSeries::getTitle(const unsigned C_INT32 & var) const
  {
    if (var < mCols)
      return mTitles[mPivot[var]];

    return mDummyString;
  }

const std::string & CTimeSeries::getKey(const unsigned C_INT32 & var) const
  {
    if (var < mCols)
      return mKeys[mPivot[var]];

    return mDummyString;
  }

std::string CTimeSeries::getSBMLId(const unsigned C_INT32 & var) const
  {
    std::string key = getKey(var);
    std::string result("");

    if (key != mDummyString)
      {
        CCopasiObject* pObject = GlobalKeys.get(key);
        if (pObject != NULL)
          {
            std::map<CCopasiObject*, SBase*>::iterator pos = CCopasiDataModel::Global->getCopasi2SBMLMap().find(pObject);
            if (pos != CCopasiDataModel::Global->getCopasi2SBMLMap().end())
              {
                SBase* pSBMLObject = pos->second;
                Compartment* pSBMLCompartment = NULL;
                Species* pSBMLSpecies = NULL;
                Parameter* pSBMLParameter = NULL;
                Model* pSBMLModel = NULL;
                switch (pSBMLObject->getTypeCode())
                  {
                  case SBML_COMPARTMENT:
                    pSBMLCompartment = dynamic_cast<Compartment*>(pSBMLObject);
                    if (pSBMLCompartment && pSBMLCompartment->isSetId())
                      {
                        result = pSBMLCompartment->getId();
                      }
                    break;
                  case SBML_SPECIES:
                    pSBMLSpecies = dynamic_cast<Species*>(pSBMLObject);
                    if (pSBMLSpecies && pSBMLSpecies->isSetId())
                      {
                        result = pSBMLSpecies->getId();
                      }
                    break;
                  case SBML_PARAMETER:
                    pSBMLParameter = dynamic_cast<Parameter*>(pSBMLObject);
                    if (pSBMLParameter && pSBMLParameter->isSetId())
                      {
                        result = pSBMLParameter->getId();
                      }
                    break;
                  case SBML_MODEL:
                    pSBMLModel = dynamic_cast<Model*>(pSBMLObject);
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
    unsigned int maxCount = mNumSteps;
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
