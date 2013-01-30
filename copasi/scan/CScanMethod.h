// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
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

  CCopasiObject * mpObject;
  CCopasiObject * mpInitialObject;

  C_FLOAT64 mStoreValue;

  size_t mIndex;

  bool mFlagFinished;

  bool mIsStateVariable;

public:
  static
  CScanItem* createScanItemFromParameterGroup(CCopasiParameterGroup* si,
      CRandom* rg,
      const bool & continueFromCurrentState);

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
   * @param const bool & continueFromCurrentState
   */
  virtual bool isValidScanItem(const bool & continueFromCurrentState);

  /**
   * Retrieve the initial object which is scanned.
   * @return const CCopasiObject * object
   */
  const CCopasiObject * getObject() const;

protected:

  CScanItem(CCopasiParameterGroup* si, const bool & continueFromCurrentState);

  //initObject();

private:
  CScanItem();
};

//***********************************+

class CScanItemRepeat: public CScanItem
{
public:
  CScanItemRepeat(CCopasiParameterGroup* si, const bool & continueFromCurrentState);
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
  CScanItemLinear(CCopasiParameterGroup* si, const bool & continueFromCurrentState);
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
  CScanItemRandom(CCopasiParameterGroup* si, CRandom* rg, const bool & continueFromCurrentState);
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

  std::vector< Refresh * > mInitialRefreshes;

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
   * Default constructor.
   */
  CScanMethod();

protected:
  /**
   * Specific constructor.
   * @param CCopasiMethod::SubType subType
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CScanMethod(CCopasiMethod::SubType subType,
              const CCopasiContainer * pParent = NULL);

public:
  /**
   * Create a trajectory method.
   * Note: the returned object has to be released after use with delete
   */
  static CScanMethod * createMethod(CCopasiMethod::SubType subType = CCopasiMethod::scanMethod);

  /**
   *  Copy constructor.
   *  @param "const CTrajectoryMethod &" src
   */
  //CScanMethod(const CScanMethod & src,
  //            const CCopasiContainer * pParent = NULL);

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
