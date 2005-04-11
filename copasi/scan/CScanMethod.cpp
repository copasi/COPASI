/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/scan/CScanMethod.cpp,v $
   $Revision: 1.39 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/04/11 21:19:24 $
   End CVS Header */

/**
 *  CScanMethod class.
 *  This class describes the Scan method
 *
 *  Created for Copasi by Rohan Luktuke 2002
 */

#include <string>

//#define COPASI_TRACE_CONSTRUCTION
#include "mathematics.h"
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

// this will have to be defined somewhere else with the
// values of other distribution types
//#define SD_UNIFORM 0
//#define SD_GAUSS 1
//#define SD_BOLTZ 2
//#define SD_REGULAR 3

//**************** CScanItem classes ***************************

//static
CScanItem* CScanItem::createScanItemFromParameterGroup(const CCopasiParameterGroup* si,
    CRandom* rg,
    CScanTask* st)
{
  if (!si) return NULL;

  CScanProblem::Type type = *(CScanProblem::Type*)(si->getValue("Type"));

  CScanItem* tmp;

  if (type == CScanProblem::SCAN_REPEAT)
    tmp = new CScanItemRepeat(si);

  if (type == CScanProblem::SCAN_LINEAR)
    tmp = new CScanItemLinear(si);

  if (type == CScanProblem::SCAN_RANDOM)
    tmp = new CScanItemRandom(si, rg);

  /*  if (type == CScanProblem::SCAN_BREAK)
      tmp = new CScanItemBreak(si, st);*/

  return tmp;
}

CScanItem::CScanItem(const CCopasiParameterGroup* si)
    : mNumSteps(0),
    mpValue(NULL),
    mStoreValue(0.0),
    mIndex(0),
    mFlagFinished(false)
{
  mNumSteps = *(unsigned C_INT32*)(si->getValue("Number of steps"));

  std::string tmpString = *(std::string*)(si->getValue("Object"));
  CCopasiObject* tmpObject = CCopasiContainer::ObjectFromName(tmpString);
  if (!tmpObject) {mpValue = NULL; return;}
  if (!tmpObject->isValueDbl()) {mpValue = NULL; return;}
  mpValue = tmpObject;
}

unsigned C_INT32 CScanItem::getNumSteps() const {return mNumSteps;};

void CScanItem::restoreValue() const
  {
    if (mpValue)
      mpValue->setObjectValue(mStoreValue);
  };

void CScanItem::storeValue()
{if (mpValue) mStoreValue = * (C_FLOAT64 *) mpValue->getReference();};

void CScanItem::reset()
{
  mIndex = 0;
  mFlagFinished = false;
  this->step(); //purely virtual
}

bool CScanItem::isFinished() const {return mFlagFinished;};

//*******

CScanItemRepeat::CScanItemRepeat(const CCopasiParameterGroup* si)
    : CScanItem(si)
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

  //  std::cout << "SIRepeat " << mIndex-1<< std::endl;
}

//*******

CScanItemLinear::CScanItemLinear(const CCopasiParameterGroup* si)
    : CScanItem(si),
    mLog(false)
{
  mLog = *(bool*)(si->getValue("log"));
  mMin = *(C_FLOAT64*)(si->getValue("Minimum"));
  mMax = *(C_FLOAT64*)(si->getValue("Maximum"));
  if (mLog)
    {
      mMin = log(mMin);
      mMax = log(mMax);
    }
  mFaktor = (mMax - mMin) / mNumSteps;
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

  mpValue->setObjectValue(Value);
  ++mIndex;

  //std::cout << "SILinear " << mMin + (mIndex-1)*mFaktor<< std::endl;
}

//*******

CScanItemRandom::CScanItemRandom(const CCopasiParameterGroup* si, CRandom* rg)
    : CScanItem(si),
    mRg(rg),
    mRandomType(0),
    mLog(false)
{
  mRandomType = *(unsigned C_INT32*)(si->getValue("Distribution type"));
  std::cout << " ****** " << mRandomType << std::endl;
  mLog = *(bool*)(si->getValue("log"));
  mMin = *(C_FLOAT64*)(si->getValue("Minimum"));
  mMax = *(C_FLOAT64*)(si->getValue("Maximum"));
  if (mLog)
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
        case 0:        //uniform
          Value = mMin + mRg->getRandomCC() * mFaktor;
          if (mLog)
            Value = exp(Value);
          break;

        case 1:        //normal
          tmpF = mRg->getRandomNormal01();
          Value = mMin + tmpF * mMax;
          if (mLog)
            Value = exp(Value);
          break;

        case 2:        //poisson
          Value = mRg->getRandomPoisson(mMin);
          //if (mLog)
          //  *mpValue = exp(*mpValue);
          break;
        }
    }

  mpValue->setObjectValue(Value);
  ++mIndex;
}

//*******

/*CScanItemBreak::CScanItemBreak(const CCopasiParameterGroup* si, CScanTask* st)
    : CScanItem(si),
    mPlotB(0),
    mReportB(0),
    mST(NULL)
{
  mReportB = *(unsigned C_INT32*)(si->getValue("Report break"));
  mPlotB = *(unsigned C_INT32*)(si->getValue("Plot break"));
  mST = st;
  mNumSteps = 0;
}
 
void CScanItemBreak::step()
{
  //the index
  if (mIndex > mNumSteps)
    mFlagFinished = true;
  else
    {
      //TODO: tell the task what exactly to do...
      mST->outputSeparatorCallback();
    }
 
  ++mIndex;
}*/

//**************** CScanMethod class ***************************

CScanMethod * CScanMethod::createMethod() {return new CScanMethod;}

CScanMethod::CScanMethod():
    CCopasiMethod(CCopasiTask::scan, CCopasiMethod::scanMethod),
    mpProblem(NULL),
    mpRandomGenerator(NULL),
    mTotalSteps(1)
    //    mVariableSize(0),
    //    mpVariables(NULL)
{
  //  addParameter("Random Number Generator", CCopasiParameter::STRING,
  //               CRandom::TypeName[1]);
  //  addParameter("Random Number Seed", CCopasiParameter::INT, (C_INT32) 0);
  mpRandomGenerator = CRandom::createGenerator(CRandom::r250);
}

/*CScanMethod::CScanMethod(const CScanMethod & src,
                         const CCopasiContainer * pParent):
    CCopasiMethod(src, pParent),
    mpProblem(NULL),
    mpRandomGenerator(NULL)
    //    mVariableSize(0),
    //    mpVariables(NULL)
{}*/

CScanMethod::~CScanMethod()
{
  cleanupScanItems();
  delete mpRandomGenerator;
  mpRandomGenerator = NULL;
}

bool CScanMethod::cleanupScanItems()
{
  if (!mpProblem) return false;
  unsigned C_INT32 i, imax = mScanItems.size();
  for (i = 0; i < imax; ++i) if (mScanItems[i]) delete mScanItems[i];

  mScanItems.clear();
  return true;
}

bool CScanMethod::init()
{
  if (!mpProblem) return false;

  cleanupScanItems();

  mTotalSteps = 1;

  unsigned C_INT32 i, imax = mpProblem->getNumberOfScanItems();
  for (i = 0; i < imax; ++i)
    {
      mScanItems.push_back(CScanItem::createScanItemFromParameterGroup(mpProblem->getScanItem(i),
                           mpRandomGenerator,
                           (CScanTask*)(getObjectParent())));
      mTotalSteps *= mScanItems[i]->getNumSteps();
    }

  //set mLastNestingItem
  mLastNestingItem = -1;
  if (imax != 0)
    {
      //search from the end
      C_INT32 j;
      for (j = mScanItems.size() - 1; j >= 0; --j)
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
  CCopasiDataModel::Global->getModel()->setState(&mpProblem->getInitialState());

  bool success = true;

  unsigned C_INT32 i, imax = mScanItems.size();

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

bool CScanMethod::loop(unsigned C_INT32 level)
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

bool CScanMethod::calculate() const
  {
    //std::cout << "*********** Scan: calculate... ************" << std::endl;
    return ((CScanTask*)(getObjectParent()))->processCallback();
  }

void CScanMethod::setProblem(const CScanProblem * problem)
{mpProblem = problem;}
