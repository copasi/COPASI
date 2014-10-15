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
 *  This class describes the method for doing the Scan.
 */

#ifndef COPASI_CScanMethod
#define COPASI_CScanMethod

#include <string>

#include "utilities/CCopasiMethod.h"
#include "steadystate/CSteadyStateTask.h"
#include "trajectory/CTrajectoryTask.h"
#include "report/CReport.h"

class CScanProblem;
class CScanTask;
class CSteadyStateTask;
class CTrajectory;
class CRandom;

class CScanItem
{
protected:
  size_t mNumSteps;

  const CCopasiObject * mpObject;

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

  virtual bool isNesting() const {return true;};

  virtual ~CScanItem() {};

  /**
   * perform checks. This is used in the method::isValidProblem() method.
   * It returns false for an invalid ScanItem and generates a CCopasiMessage
   */
  virtual bool isValidScanItem();

  /**
   * Retrieve the initial object which is scanned.
   * @return const CCopasiObject * object
   */
  const CCopasiObject * getObject() const;

protected:

  CScanItem(CCopasiParameterGroup* si);

  //initObject();

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

//***********************************+

class CScanItemLinear: public CScanItem
{
private:
  C_FLOAT64 mMin, mMax, mFaktor;
  bool mLog;
public:
  CScanItemLinear(CCopasiParameterGroup* si);
  virtual void step();

  virtual ~CScanItemLinear() {};

  virtual bool isValidScanItem(const bool & continueFromCurrentState);
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

  CObjectInterface::UpdateSequence mInitialUpdates;

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

  // Operations
private:
  /**
   * Default constructor
   */
  CScanMethod();

public:
  /**
   * Specific constructor
   * @param const CCopasiContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: scanMethod)
   * @param const CTaskEnum::Task & taskType (default: scan)
   */
  CScanMethod(const CCopasiContainer * pParent,
              const CTaskEnum::Method & methodType = CTaskEnum::scanMethod,
              const CTaskEnum::Task & taskType = CTaskEnum::scan);

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
