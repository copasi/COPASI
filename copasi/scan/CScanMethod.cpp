// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CScanMethod class.
 *  This class describes the Scan method
 *
 *  Created for COPASI by Rohan Luktuke 2002
 */

#include <string>
#include <cmath>

#include "copasi.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "utilities/CReadConfig.h"
#include "randomGenerator/CRandom.h"
//#include "utilities/CWriteConfig.h"
#include "CScanProblem.h"
#include "CScanMethod.h"
#include "CScanTask.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"
#include <utilities/CCopasiMessage.h>
// this will have to be defined somewhere else with the
// values of other distribution types
//#define SD_UNIFORM 0
//#define SD_GAUSS 1
//#define SD_BOLTZ 2
//#define SD_REGULAR 3

//**************** CScanItem classes ***************************

//static
CScanItem* CScanItem::createScanItemFromParameterGroup(CCopasiParameterGroup* si,
    CRandom* rg,
    const bool & continueFromCurrentState)
{
  if (!si) return NULL;

  CScanProblem::Type type = *(CScanProblem::Type*)(si->getValue("Type").pUINT);

  CScanItem* tmp = NULL;

  if (type == CScanProblem::SCAN_REPEAT)
    tmp = new CScanItemRepeat(si, continueFromCurrentState);

  if (type == CScanProblem::SCAN_LINEAR)
    tmp = new CScanItemLinear(si, continueFromCurrentState);

  if (type == CScanProblem::SCAN_RANDOM)
    tmp = new CScanItemRandom(si, rg, continueFromCurrentState);

  /*  if (type == CScanProblem::SCAN_BREAK)
      tmp = new CScanItemBreak(si, st);*/

  return tmp;
}

CScanItem::CScanItem():
  mNumSteps(0),
  mpObject(NULL),
  mpInitialObject(NULL),
  mStoreValue(0.0),
  mIndex(0),
  mFlagFinished(false),
  mIsStateVariable(false)
{}

CScanItem::CScanItem(CCopasiParameterGroup* si,
                     const bool & continueFromCurrentState):
  mNumSteps(0),
  mpObject(NULL),
  mpInitialObject(NULL),
  mStoreValue(0.0),
  mIndex(0),
  mFlagFinished(false),
  mIsStateVariable(false)
{
  assert(si != NULL);

  mNumSteps = * si->getValue("Number of steps").pUINT;

  std::string tmpString = * si->getValue("Object").pCN;
  CCopasiDataModel* pDataModel = si->getObjectDataModel();
  assert(pDataModel != NULL);
  CCopasiObject * tmpObject = pDataModel->getDataObject(tmpString);

  if (tmpObject == NULL || !tmpObject->isValueDbl())
    {
      return;
    }

  mpInitialObject = tmpObject;

  if (continueFromCurrentState)
    {
      // Determine whether the object is the initial value of a state variable;
      const CModel * pModel = static_cast< CModel * >(mpInitialObject->getObjectAncestor("Model"));

      if (pModel != NULL)
        {
          mIsStateVariable = pModel->isStateVariable(tmpObject);

          if (!mIsStateVariable)
            {
              // We need to find the object for the transient value if it exists so that we can update while continuing.
              mpObject = pModel->getCorrespondingTransientObject(tmpObject);
            }
        }
    }
  else
    {
      mpObject = mpInitialObject;
    }
}

size_t CScanItem::getNumSteps() const {return mNumSteps;};

void CScanItem::restoreValue() const
{
  if (mpObject)
    mpObject->setObjectValue(mStoreValue);
};

void CScanItem::storeValue()
{
  if (mpObject)
    {
      assert(mpObject->isValueDbl());
      mStoreValue = * (C_FLOAT64 *) mpObject->getValuePointer();
    }
};

void CScanItem::reset()
{
  mIndex = 0;
  mFlagFinished = false;
  this->step(); //purely virtual
}

bool CScanItem::isFinished() const {return mFlagFinished;};

bool CScanItem::isValidScanItem(const bool & continueFromCurrentState)
{
  if (continueFromCurrentState &&
      mIsStateVariable &&
      mpObject == NULL)
    {
      CCopasiMessage(CCopasiMessage::WARNING, MCScan + 1, mpInitialObject->getObjectDisplayName().c_str());
      return true;
    }

  if (mpInitialObject == NULL)
    {
      CCopasiMessage(CCopasiMessage::ERROR, "Invalid or missing scan parameter.");
      return false;
    }

  return true;
}

const CCopasiObject * CScanItem::getObject() const
{
  return mpObject;
}

//*******

CScanItemRepeat::CScanItemRepeat(CCopasiParameterGroup* si,
                                 const bool & continueFromCurrentState):
  CScanItem(si, continueFromCurrentState)
{
  if (mNumSteps >= 1)
    --mNumSteps; // for the repeat item mNumSteps is the number of iterations, not of intervals
}

void CScanItemRepeat::step()
{
  //do something ...

  //the index
  if (mIndex > mNumSteps)
    mFlagFinished = true;

  ++mIndex;
}

bool CScanItemRepeat::isValidScanItem(const bool & /* continueFromCurrentState */)
{
  return true;
}

//*******

CScanItemLinear::CScanItemLinear(CCopasiParameterGroup* si,
                                 const bool & continueFromCurrentState):
  CScanItem(si, continueFromCurrentState),
  mLog(false)
{
  mLog = * si->getValue("log").pBOOL;
  mMin = * si->getValue("Minimum").pDOUBLE;
  mMax = * si->getValue("Maximum").pDOUBLE;

  if (mLog)
    {
      mMin = log(mMin);
      mMax = log(mMax);
    }

  mFaktor = (mMax - mMin) / mNumSteps;

  //TODO: log scanning of negative values?
}

void CScanItemLinear::step()
{
  //do something ...
  C_FLOAT64 Value = mMin + mIndex * mFaktor;

  if (mLog)
    Value = exp(Value);

  //the index
  if (mIndex > mNumSteps)
    mFlagFinished = true;

  if (mpObject) mpObject->setObjectValue(Value);

  ++mIndex;
}

bool CScanItemLinear::isValidScanItem(const bool & continueFromCurrentState)
{
  if (!CScanItem::isValidScanItem(continueFromCurrentState)) return false;

  if (mLog)
    {
      if (isnan(mFaktor) || mFaktor < - std::numeric_limits< C_FLOAT64 >::max() || std::numeric_limits< C_FLOAT64 >::max() < mFaktor)
        {
          //not a valid range for log
          CCopasiMessage(CCopasiMessage::ERROR, "Only positive values for min and max are possible for a logarithmic scan.");
          return false;
        }
    }

  return true;
}

//*******

CScanItemRandom::CScanItemRandom(CCopasiParameterGroup* si, CRandom* rg,
                                 const bool & continueFromCurrentState):
  CScanItem(si, continueFromCurrentState),
  mRg(rg),
  mRandomType(0),
  mLog(false)
{
  mRandomType = * si->getValue("Distribution type").pUINT;

  mLog = * si->getValue("log").pBOOL;
  mMin = * si->getValue("Minimum").pDOUBLE;
  mMax = * si->getValue("Maximum").pDOUBLE;

  if (mLog && mRandomType == 0)
    {
      mMin = log(mMin);
      mMax = log(mMax);
    }

  mNumSteps = 0;
  mFaktor = (mMax - mMin);
}

void CScanItemRandom::step()
{
  C_FLOAT64 Value;

  //the index
  if (mIndex > mNumSteps)
    mFlagFinished = true;
  else
    {
      C_FLOAT64 tmpF;

      switch (mRandomType)
        {
          case 0: // uniform
            Value = mMin + mRg->getRandomCC() * mFaktor;

            if (mLog)
              Value = exp(Value);

            break;

          case 1: // normal
            tmpF = mRg->getRandomNormal01();
            Value = mMin + tmpF * mMax;

            if (mLog)
              Value = exp(Value);

            break;

          case 2: // poisson

            if (mMin < 0)
              CCopasiMessage(CCopasiMessage::WARNING, "Invalid ScanItem: Requested Poisson random variable for negative argument: %lf", mMin);

            Value = mRg->getRandomPoisson(mMin);

            break;

          case 3: // gamma
            Value = mRg->getRandomGamma(mMin, mMax);

            if (mLog)
              Value = exp(Value);

            break;
        }
    }

  if (mpObject) mpObject->setObjectValue(Value);

  ++mIndex;
}

//**************** CScanMethod class ***************************

CScanMethod * CScanMethod::createMethod(CCopasiMethod::SubType /* subType */)
{
  return new CScanMethod();
}

CScanMethod::CScanMethod():
  CCopasiMethod(CCopasiTask::scan, CCopasiMethod::scanMethod),
  mpProblem(NULL),
  mpTask(NULL),
  mpRandomGenerator(NULL),
  mTotalSteps(1),
  mLastNestingItem(C_INVALID_INDEX),
  mContinueFromCurrentState(false)
{
  mpRandomGenerator = CRandom::createGenerator(CRandom::r250);
}

CScanMethod::~CScanMethod()
{
  cleanupScanItems();
  delete mpRandomGenerator;
  mpRandomGenerator = NULL;
}

bool CScanMethod::cleanupScanItems()
{
  if (!mpProblem) return false;

  size_t i, imax = mScanItems.size();

  for (i = 0; i < imax; ++i) if (mScanItems[i]) delete mScanItems[i];

  mScanItems.clear();
  return true;
}

bool CScanMethod::init()
{
  if (!mpProblem) return false;

  mpTask = dynamic_cast< CScanTask * >(getObjectParent());

  if (mpTask == NULL) return false;

  cleanupScanItems();
  mInitialRefreshes.clear();
  //mTransientRefreshes.clear();

  mTotalSteps = 1;
  std::set< const CCopasiObject * > InitialObjectSet;
  std::set< const CCopasiObject * > TransientObjectSet;

  size_t i, imax = mpProblem->getNumberOfScanItems();
  mContinueFromCurrentState = mpProblem->getContinueFromCurrentState();

  for (i = 0; i < imax; ++i)
    {
      CScanItem * pItem = CScanItem::createScanItemFromParameterGroup(mpProblem->getScanItem(i),
                          mpRandomGenerator,
                          mContinueFromCurrentState);

      if (pItem == NULL)
        {
          continue;
        }

      mScanItems.push_back(pItem);
      mTotalSteps *= pItem->getNumSteps() + 1;

      if (pItem->getObject() != NULL)
        {
          InitialObjectSet.insert(pItem->getObject());
        }
    }

  if (mContinueFromCurrentState)
    {
      mInitialRefreshes = CCopasiObject::buildUpdateSequence(mpProblem->getModel()->getUptoDateObjects(), InitialObjectSet);
    }
  else
    {
      mInitialRefreshes = mpProblem->getModel()->buildInitialRefreshSequence(InitialObjectSet);
    }

  //set mLastNestingItem
  mLastNestingItem = C_INVALID_INDEX;

  if (imax != 0)
    {
      //search from the end
      size_t j;

      for (j = mScanItems.size() - 1; j != C_INVALID_INDEX; --j)
        {
          if (mScanItems[j]->isNesting())
            {
              mLastNestingItem = j;
              break;
            }
        }
    }

  return true;
}

bool CScanMethod::scan()
{
  if (!mpProblem) return false;

  //a hack to ensure that the first subtask is run with initial conditions
  //pDataModel->getModel()->setState(&mpProblem->getInitialState());

  bool success = true;

  size_t i, imax = mScanItems.size();

  //store old parameter values
  for (i = 0; i < imax; ++i)
    mScanItems[i]->storeValue();

  //Do the scan...
  if (imax) //there are scan items
    success = loop(0);
  else
    success = calculate(); //nothing to scan, only one call to the subtask

  //restore old parameter values
  for (i = 0; i < imax; ++i)
    mScanItems[i]->restoreValue();

  return success;
}

bool CScanMethod::loop(size_t level)
{
  bool isLastMasterItem = (level == (mScanItems.size() - 1)); //TODO

  CScanItem* currentSI = mScanItems[level];

  for (currentSI->reset(); !currentSI->isFinished(); currentSI->step())
    {
      //TODO: handle slave SIs

      if (isLastMasterItem)
        {
          if (!calculate()) return false;
        }
      else
        {
          if (!loop(level + 1)) return false;
        } //TODO

      //separator needs to be handled slightly differently if we are at the last item
      if (currentSI->isNesting())
        ((CScanTask*)(getObjectParent()))->outputSeparatorCallback(level == mLastNestingItem);
    }

  return true;
}

bool CScanMethod::calculate()
{
  std::vector< Refresh * >::iterator it = mInitialRefreshes.begin();
  std::vector< Refresh * >::iterator end = mInitialRefreshes.end();

  while (it != end)
    (**it++)();

  return mpTask->processCallback();
}

void CScanMethod::setProblem(CScanProblem * problem)
{mpProblem = problem;}

//virtual
bool CScanMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CCopasiMethod::isValidProblem(pProblem)) return false;

  const CScanProblem * pP = dynamic_cast<const CScanProblem *>(pProblem);

  if (!pP)
    {
      //not a TrajectoryProblem
      CCopasiMessage(CCopasiMessage::EXCEPTION, "Problem is not a Scan problem.");
      return false;
    }

  mContinueFromCurrentState = pP->getContinueFromCurrentState();

  size_t i, imax = pP->getNumberOfScanItems();

  if (imax <= 0)
    {
      //no scan items
      CCopasiMessage(CCopasiMessage::WARNING, "There is nothing to scan.");
      return false;
    }

  for (i = 0; i < imax; ++i)
    {
      CScanItem * si = CScanItem::createScanItemFromParameterGroup(mpProblem->getScanItem(i),
                       mpRandomGenerator,
                       mContinueFromCurrentState);

      if (!si)
        {
          //parameter group could not be interpreted
          CCopasiMessage(CCopasiMessage::ERROR, "Internal problem with scan definition.");
          return false;
        }

      if (!si->isValidScanItem(mContinueFromCurrentState))
        {
          //the self check of the scan item failed.
          //the message should be generated by the isValidScanItem() method.
          delete si;
          return false;
        }

      delete si;
      //mTotalSteps *= mScanItems[i]->getNumSteps();
    }

  return true;
}
