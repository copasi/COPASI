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
 *  This class describes the method for doing the Scan.
 */

#ifndef COPASI_CScanMethod
#define COPASI_CScanMethod

#include <string>

#include "copasi/utilities/CCopasiMethod.h"
#include "copasi/steadystate/CSteadyStateTask.h"
#include "copasi/trajectory/CTrajectoryTask.h"
#include "copasi/report/CReport.h"

class CScanProblem;
class CScanTask;
class CSteadyStateTask;
class CTrajectory;
class CRandom;
class CModelParameterSet;

class CScanItem
{
protected:
  size_t mNumSteps;

  const CObjectInterface * mpObject;

  C_FLOAT64 * mpObjectValue;

  C_FLOAT64 mStoreValue;

  size_t mIndex;

  bool mFlagFinished;

public:
  static
  CScanItem* createScanItemFromParameterGroup(CCopasiParameterGroup* si,
      CRandom* rg);

  size_t getNumSteps() const;

  void restoreValue() const;

  void storeValue();

  void reset();

  bool isFinished() const;

  virtual void step() = 0;

  virtual bool isNesting() const;

  virtual ~CScanItem();

  /**
   * perform checks. This is used in the method::isValidProblem() method.
   * It returns false for an invalid ScanItem and generates a CCopasiMessage
   */
  virtual bool isValidScanItem(const bool & continueFromCurrentState);

  /**
   * Retrieve the initial object which is scanned.
   * @return const CObjectInterface * object
   */
  const CObjectInterface * getObject() const;

protected:

  CScanItem(CCopasiParameterGroup* si);

  //initObject();
  virtual void ensureParameterGroupHasAllElements(CCopasiParameterGroup* pg);

private:
  CScanItem();
};

//***********************************+

class CScanItemRepeat: public CScanItem
{
public:
  CScanItemRepeat(CCopasiParameterGroup* si);

  virtual void step();

  virtual ~CScanItemRepeat() {};

  virtual bool isValidScanItem(const bool & continueFromCurrentState);
};


class CScanItemParameterSet : public CScanItem
{
private:
  std::vector< std::string > mValues;
  std::vector< const CModelParameterSet* > mSets;

  CModelParameterSet * mpOldValue;

public:
  CScanItemParameterSet(CCopasiParameterGroup * si);
  virtual void step();

  virtual ~CScanItemParameterSet(){};

  virtual bool isValidScanItem(const bool & continueFromCurrentState);

protected:
  virtual void ensureParameterGroupHasAllElements(CCopasiParameterGroup * pg);
};

//***********************************+

class CScanItemLinear: public CScanItem
{
private:
  std::vector<C_FLOAT64> mValues;
  C_FLOAT64 mMin, mMax, mFaktor;
  bool mLog;
  bool mUseValues;
public:
  CScanItemLinear(CCopasiParameterGroup* si);
  virtual void step();

  virtual ~CScanItemLinear() {};

  virtual bool isValidScanItem(const bool & continueFromCurrentState);
protected:
  virtual void ensureParameterGroupHasAllElements(CCopasiParameterGroup* pg);
};

//***********************************+

class CScanItemRandom: public CScanItem
{
private:
  C_FLOAT64 mMin, mMax, mFaktor;
  CRandom* mRg;
  unsigned C_INT32 mRandomType;
  bool mLog;
public:
  CScanItemRandom(CCopasiParameterGroup* si, CRandom* rg);
  virtual ~CScanItemRandom() {};

  virtual void step();
  virtual bool isNesting() const {return false;};
protected:
  virtual void ensureParameterGroupHasAllElements(CCopasiParameterGroup* pg);
};

//***********************************+

/*class CScanItemBreak: public CScanItem
  {
  private:
    size_t mPlotB, mReportB;
    CScanTask* mST;
  public:
    CScanItemBreak(const CCopasiParameterGroup* si, CScanTask* st);
    void step();
    virtual bool isNesting() const {return false;};
  };*/

//*******************************************+
//*******************************************+

class CScanMethod : public CCopasiMethod
{
protected:
  /**
   *  A pointer to the trajectory problem.
   */
  CScanProblem * mpProblem;

  /**
   *  A pointer to the scan Task.
   */
  CScanTask * mpTask;

  /**
   * A pointer to the random number generator
   */
  CRandom * mpRandomGenerator;

  std::vector<CScanItem*> mScanItems;

  CCore::CUpdateSequence mInitialUpdates;

  //std::vector< Refresh * > mTransientRefreshes;

  size_t mTotalSteps;

  /**
   * the index of the last item that has several subitems,
   * also the last item that need to generate output separators
   */
  size_t mLastNestingItem;

  /**
   * Variable indicating whether the subtask shall continue from the current state
   * or the initial state
   */
  bool mContinueFromCurrentState;

  /**
   * Count exceptions thrown by subtask
   */
  size_t mFailCounter;

  /**
   * Indicate, that the initial state was changed by a scan item directly 
   * and shouldn't be overwritten in calculate.
   */
  bool mInitialStateChanged;

  // Operations
private:
  /**
   * Default constructor
   */
  CScanMethod();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: scanMethod)
   * @param const CTaskEnum::Task & taskType (default: scan)
   */
  CScanMethod(const CDataContainer * pParent,
              const CTaskEnum::Method & methodType = CTaskEnum::Method::scanMethod,
              const CTaskEnum::Task & taskType = CTaskEnum::Task::scan);

  /**
   * Copy constructor
   * @param const CScanMethod & src
   * @param const CDataContainer * pParent
   */
  CScanMethod(const CScanMethod & src,
              const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  ~CScanMethod();

  /**
   *  Set a pointer to the problem.
   *  This method is used by CTrajectory
   *  @param "CTrajectoryProblem *" problem
   */
  void setProblem(CScanProblem * problem);

  bool init();

  bool scan();

  size_t getTotalNumberOfSteps() const {return mTotalSteps;};

  /**
   *  The main scan method.
   */
  //void scan(size_t s, bool C_UNUSED(nl), void (*pCallback)(CReport *), CReport *pReport);

  /**
   * Check if the method is suitable for this problem
   * @return bool suitability of the method
   */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);

private:

  bool cleanupScanItems();

  bool loop(size_t level);

  bool calculate();

  /**
   *  Set the value of the scan parameter based on the distribution
   *  @param size_t i where to start in the distribution
   *  @param size_t first first parameter in the set of Master/Slaves
   *  @param size_t last last parameter in the set of Master/Slaves
   */
  //void setScanParameterValue(size_t i,
  //                           size_t first,
  //                           size_t last);
};

#endif // COPASI_CTrajectoryMethod
