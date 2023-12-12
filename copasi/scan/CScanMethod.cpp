// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the 
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

#include "copasi/copasi.h"
#include "copasi/model/CModel.h"
#include "copasi/model/CState.h"
#include "copasi/utilities/CReadConfig.h"
#include "copasi/randomGenerator/CRandom.h"
//#include "copasi/utilities/CWriteConfig.h"
#include "CScanProblem.h"
#include "CScanMethod.h"
#include "CScanTask.h"

#include "copasi/math/CMathContainer.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/utilities/CParameterEstimationUtils.h"
#include <copasi/utilities/CCopasiException.h>

// Uncomment this line below to get debug print out.
// #define DEBUG_OUTPUT 1

// this will have to be defined somewhere else with the
// values of other distribution types
//#define SD_UNIFORM 0
//#define SD_GAUSS 1
//#define SD_BOLTZ 2
//#define SD_REGULAR 3

//**************** CScanItem classes ***************************

//static
CScanItem* CScanItem::createScanItemFromParameterGroup(CCopasiParameterGroup* si,
    CRandom* rg)
{
  if (!si) return NULL;

  CScanProblem::Type type = (CScanProblem::Type) si->getValue< unsigned C_INT32 >("Type");

  CScanItem* tmp = NULL;

  if (type == CScanProblem::SCAN_REPEAT)
    tmp = new CScanItemRepeat(si);

  if (type == CScanProblem::SCAN_LINEAR)
    tmp = new CScanItemLinear(si);

  if (type == CScanProblem::SCAN_RANDOM)
    tmp = new CScanItemRandom(si, rg);

  if (type == CScanProblem::SCAN_PARAMETER_SET)
    tmp = new CScanItemParameterSet(si);

  /*  if (type == CScanProblem::SCAN_BREAK)
      tmp = new CScanItemBreak(si, st);*/

  return tmp;
}

CScanItem::CScanItem():
  mNumSteps(0),
  mpObject(NULL),
  mpObjectValue(NULL),
  mStoreValue(0.0),
  mIndex(0),
  mFlagFinished(false)
{}

CScanItem::CScanItem(CCopasiParameterGroup* si):
  mNumSteps(0),
  mpObject(NULL),
  mpObjectValue(NULL),
  mStoreValue(0.0),
  mIndex(0),
  mFlagFinished(false)
{
  assert(si != NULL);
  ensureParameterGroupHasAllElements(si);

  mNumSteps = si->getValue< unsigned C_INT32 >("Number of steps");

  CCopasiProblem * pProblem = dynamic_cast< CCopasiProblem * >(si->getObjectAncestor("Problem"));

  if (pProblem != NULL)
    {
      mpObject = pProblem->getMathContainer()->getObject(si->getValue< CCommonName >("Object"));
    }

  if (mpObject != NULL)
    {
      mpObjectValue = (C_FLOAT64 *) mpObject->getValuePointer();
    }
}

void CScanItem::ensureParameterGroupHasAllElements(CCopasiParameterGroup* pg)
{
  pg->assertParameter("Number of steps", CCopasiParameter::Type::UINT, 0);
  pg->assertParameter("Object", CCopasiParameter::Type::CN, std::string());
}

size_t CScanItem::getNumSteps() const {return mNumSteps;}

void CScanItem::restoreValue() const
{
  if (mpObjectValue != NULL)
    {
      *mpObjectValue = mStoreValue;
    }
}

void CScanItem::storeValue()
{
  if (mpObjectValue != NULL)
    {
      mStoreValue = *mpObjectValue;
    }
}

void CScanItem::reset()
{
  mIndex = 0;
  mFlagFinished = false;
  this->step(); //purely virtual
}

bool CScanItem::isFinished() const {return mFlagFinished;}

bool CScanItem::isNesting() const {return true;}

CScanItem::~CScanItem() {}

bool CScanItem::isValidScanItem(const bool & /* continueFromCurrentState */)
{
  if (mpObject == NULL)
    {
      CCopasiMessage(CCopasiMessage::ERROR, "Invalid or missing scan parameter.");
      return false;
    }

  return true;
}

const CObjectInterface * CScanItem::getObject() const
{
  return mpObject;
}

//*******

CScanItemRepeat::CScanItemRepeat(CCopasiParameterGroup* si):
  CScanItem(si)
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

CScanItemLinear::CScanItemLinear(CCopasiParameterGroup* si):
  CScanItem(si),
  mValues(),
  mLog(false),
  mUseValues(false)
{
  ensureParameterGroupHasAllElements(si);

  mLog = si->getValue< bool >("log");
  mMin = si->getValue< C_FLOAT64 >("Minimum");
  mMax = si->getValue< C_FLOAT64 >("Maximum");

  if (mLog)
    {
      mMin = log(mMin);
      mMax = log(mMax);
    }

  mFaktor = (mMax - mMin) / mNumSteps;

  //TODO: log scanning of negative values?

  if (si->getParameter("Use Values") && si->getParameter("Values"))
    {
      mUseValues = si->getValue<bool>("Use Values");
      std::string values = si->getValue<std::string>("Values");

      if (mUseValues && !values.empty())
        {
          std::vector<std::string> elems;
          ResultParser::split(values, std::string(",; |\n\t\r"), elems);

          for (std::string & number : elems)
            {
              mValues.push_back(ResultParser::saveToDouble(number));
            }

          mNumSteps = 0;

          if (!mValues.empty())
            mNumSteps = mValues.size() - 1;
        }
    }
}

void CScanItemLinear::step()
{
  //do something ...
  C_FLOAT64 Value;

  if (!mUseValues)
    {
      Value = mMin + mIndex * mFaktor;

      if (mLog)
        Value = exp(Value);
    }
  else
    {
      //the index
      if (mIndex >= mValues.size())
        Value = 1.0;
      else
        Value = mValues[mIndex];
    }

  //the index
  if (mIndex > mNumSteps)
    mFlagFinished = true;

  if (mpObjectValue != NULL)
    {
      *mpObjectValue = Value;
    }

  ++mIndex;
}

bool CScanItemLinear::isValidScanItem(const bool & continueFromCurrentState)
{
  if (!CScanItem::isValidScanItem(continueFromCurrentState)) return false;

  if (mLog)
    {
      if (std::isnan(mFaktor) || mFaktor < - std::numeric_limits< C_FLOAT64 >::max() || std::numeric_limits< C_FLOAT64 >::max() < mFaktor)
        {
          //not a valid range for log
          CCopasiMessage(CCopasiMessage::ERROR, "Only positive values for min and max are possible for a logarithmic scan.");
          return false;
        }
    }

  return true;
}

void CScanItemLinear::ensureParameterGroupHasAllElements(CCopasiParameterGroup* pg)
{
  pg->assertParameter("log", CCopasiParameter::Type::BOOL, false);
  pg->assertParameter("Minimum", CCopasiParameter::Type::DOUBLE, 0);
  pg->assertParameter("Maximum", CCopasiParameter::Type::DOUBLE, 0);
  pg->assertParameter("Use Values", CCopasiParameter::Type::BOOL, false);
  pg->assertParameter("Values", CCopasiParameter::Type::STRING, std::string());
}

//*******

CScanItemRandom::CScanItemRandom(CCopasiParameterGroup* si, CRandom* rg):
  CScanItem(si),
  mRg(rg),
  mRandomType(0),
  mLog(false)
{
  ensureParameterGroupHasAllElements(si);

  mRandomType = si->getValue< unsigned C_INT32 >("Distribution type");

  mLog = si->getValue< bool >("log");
  mMin = si->getValue< C_FLOAT64 >("Minimum");
  mMax = si->getValue< C_FLOAT64 >("Maximum");

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

  if (mpObjectValue != NULL && mIndex <= mNumSteps)
    {
      *mpObjectValue = Value;
    }

  ++mIndex;
}

void CScanItemRandom::ensureParameterGroupHasAllElements(CCopasiParameterGroup* pg)
{
  pg->assertParameter("Distribution type", CCopasiParameter::Type::UINT, 0);
  pg->assertParameter("log", CCopasiParameter::Type::BOOL, false);
  pg->assertParameter("Minimum", CCopasiParameter::Type::DOUBLE, 0);
  pg->assertParameter("Maximum", CCopasiParameter::Type::DOUBLE, 0);
}

//**************** CScanMethod class ***************************

CScanMethod::CScanMethod(const CDataContainer * pParent,
                         const CTaskEnum::Method & methodType,
                         const CTaskEnum::Task & taskType)
  : CCopasiMethod(pParent, methodType, taskType)
  , mpProblem(NULL)
  , mpTask(NULL)
  , mpRandomGenerator(NULL)
  , mTotalSteps(1)
  , mLastNestingItem(C_INVALID_INDEX)
  , mContinueFromCurrentState(false)
  , mFailCounter(0)
{
  mpRandomGenerator = CRandom::createGenerator();
}

CScanMethod::CScanMethod(const CScanMethod & src,
                         const CDataContainer * pParent)
  : CCopasiMethod(src, pParent)
  , mpProblem(NULL)
  , mpTask(NULL)
  , mpRandomGenerator(NULL)
  , mTotalSteps(1)
  , mLastNestingItem(C_INVALID_INDEX)
  , mContinueFromCurrentState(false)
  , mFailCounter(0)
{
  mpRandomGenerator = CRandom::createGenerator();
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
  mInitialUpdates.clear();
  //mTransientRefreshes.clear();

  mTotalSteps = 1;
  CObjectInterface::ObjectSet ObjectSet;

  size_t Offset = mpContainer->getState(false).begin() - mpContainer->getInitialState().begin();

  size_t i, imax = mpProblem->getNumberOfScanItems();
  mContinueFromCurrentState = mpProblem->getContinueFromCurrentState();

  for (i = 0; i < imax; ++i)
    {
      CScanItem * pItem = CScanItem::createScanItemFromParameterGroup(mpProblem->getScanItem(i),
                          mpRandomGenerator);

      if (pItem == NULL)
        {
          continue;
        }

      mScanItems.push_back(pItem);
      mTotalSteps *= pItem->getNumSteps() + 1;

      const CObjectInterface * pObject = pItem->getObject();

      if (pObject != NULL)
        {
          if (pObject != pObject->getDataObject())
            {
              // If we continue from the current state we must change the transient values
              // unless we have a local reaction parameter
              if (mContinueFromCurrentState &&
                  static_cast< const CMathObject * >(pObject)->getEntityType() != CMath::EntityType::LocalReactionParameter)
                {
                  pObject += Offset;
                }
            }

          ObjectSet.insert(pObject);
        }
    }

  if (mContinueFromCurrentState)
    {
      mpContainer->getTransientDependencies().getUpdateSequence(mInitialUpdates, CCore::SimulationContext::UpdateMoieties, ObjectSet, mpContainer->getSimulationUpToDateObjects());
    }
  else
    {
      mpContainer->getInitialDependencies().getUpdateSequence(mInitialUpdates, CCore::SimulationContext::UpdateMoieties, ObjectSet, mpContainer->getInitialStateObjects());
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

  mFailCounter = 0;

  //Do the scan...
  if (imax) //there are scan items
    success = loop(0);
  else
    success = calculate(); //nothing to scan, only one call to the subtask

  if (mFailCounter > 0)
    {
      CCopasiMessage(CCopasiMessage::ERROR, "%ld subtask executions failed.", mFailCounter);
    }

  // restore old parameter values
  for (i = 0; i < imax; ++i)
    mScanItems[i]->restoreValue();

  return success;
}

bool CScanMethod::loop(size_t level)
{
  bool isLastMasterItem = (level == (mScanItems.size() - 1)); //TODO

  CScanItem* currentSI = mScanItems[level];
  size_t failCounter = 0;

  mInitialStateChanged = dynamic_cast< CScanItemParameterSet * >(currentSI) != NULL;

  for (currentSI->reset(); !currentSI->isFinished(); currentSI->step())
    {
      //TODO: handle slave SIs

      if (isLastMasterItem)
        {
          if (!calculate())
            return false;
        }
      else
        {
          if (!loop(level + 1))
            return false;
        }

      // separator needs to be handled slightly differently if we are at the last item
      if (currentSI->isNesting())
        static_cast< CScanTask *>(getObjectParent())->outputSeparatorCallback(level == mLastNestingItem);
    }

  return true;
}

bool CScanMethod::calculate()
{
#ifdef DEBUG_OUTPUT
  std::cout << "CScanMethod::calculate State 1: " << mpContainer->getValues() << std::endl;
#endif // DEBUG_OUTPUT

  if (!mInitialStateChanged)
  mpContainer->applyUpdateSequence(mInitialUpdates);

#ifdef DEBUG_OUTPUT
  std::cout << "CScanMethod::calculate State 2: " << mpContainer->getValues() << std::endl;
#endif // DEBUG_OUTPUT

  bool success = true;

  CVector< C_FLOAT64 > InitialState = mpContainer->getInitialState();

  try
    {
      success = mpTask->processCallback();
    }
  catch (const CCopasiException &)
    {
      success = false;
      CCopasiMessage::getLastMessage();
    }

  if (!success)
    {
      ++mFailCounter;
      success = mpProblem->getContinueOnError();
    }

  // Assure that the subtask did not interfere with the scan operation.
  mpContainer->setInitialState(InitialState);

  return success;
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
                       mpRandomGenerator);

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

CScanItemParameterSet::CScanItemParameterSet(CCopasiParameterGroup * si)
  : CScanItem(si)
  , mValues()
  , mSets()
  , mpOldValue(NULL)
{
  ensureParameterGroupHasAllElements(si);

  auto* group = si->getGroup("ParameterSet CNs");
  if (!group)
    return;

  mNumSteps = si->getValue< unsigned C_INT32 >("Number of steps");

  CDataModel* dm = dynamic_cast< CDataModel * >(si->getObjectDataModel());
  
  for (size_t i = 0; i < group->size(); ++i)
    {
      auto* parameter = group->getParameter(i);
      if (!parameter)
        continue;
      auto cn = parameter->getValue<CCommonName>();
      auto* pSet =  dynamic_cast<const CModelParameterSet*>(dm->getObjectFromCN(cn));
      if (!pSet)
        continue;
      mSets.push_back(pSet);
      mValues.push_back(cn);
    }
}

void CScanItemParameterSet::step()
{
  if (mIndex > mNumSteps || mIndex >= mSets.size())
    mFlagFinished = true;
  else    
  {
    auto* pSet = const_cast<CModelParameterSet* >(mSets[mIndex]);
    pSet->updateModel();
  }

  ++mIndex;
}

bool CScanItemParameterSet::isValidScanItem(const bool & continueFromCurrentState)
{
  if (mSets.empty())
    {
      CCopasiMessage(CCopasiMessage::ERROR, "Invalid or missing scan parameter.");
      return false;
    }

  return true;
}

void CScanItemParameterSet::ensureParameterGroupHasAllElements(CCopasiParameterGroup * pg)
{
  pg->assertGroup("ParameterSet CNs");
}
