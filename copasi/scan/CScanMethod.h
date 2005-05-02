/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/scan/CScanMethod.h,v $
   $Revision: 1.27 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2005/05/02 09:17:33 $
   End CVS Header */

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

class CScanItem
  {
  protected:
    unsigned C_INT32 mNumSteps;

    // C_FLOAT64 * mpValue;
    CCopasiObject * mpValue;

    C_FLOAT64 mStoreValue;

    unsigned C_INT32 mIndex;

    bool mFlagFinished;

  public:
    static
    CScanItem* createScanItemFromParameterGroup(const CCopasiParameterGroup* si,
        CRandom* rg,
        CScanTask* st);

    unsigned C_INT32 getNumSteps() const;

    void restoreValue() const;

    void storeValue();

    virtual void reset();

    virtual void step() = 0;

    virtual bool isFinished() const;

    virtual bool isNesting() const {return true;};

    virtual ~CScanItem(){};

  protected:

    CScanItem(const CCopasiParameterGroup* si);

    //initObject();

  private:
    CScanItem() {};
  };

//***********************************+

class CScanItemRepeat: public CScanItem
  {
  public:
    CScanItemRepeat(const CCopasiParameterGroup* si);
    void step();

    virtual ~CScanItemRepeat(){};
  };

//***********************************+

class CScanItemLinear: public CScanItem
  {
  private:
    C_FLOAT64 mMin, mMax, mFaktor;
    bool mLog;
  public:
    CScanItemLinear(const CCopasiParameterGroup* si);
    void step();

    virtual ~CScanItemLinear(){};
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
    CScanItemRandom(const CCopasiParameterGroup* si, CRandom* rg);
    virtual ~CScanItemRandom(){};

    void step();
    virtual bool isNesting() const {return false;};
  };

//***********************************+

/*class CScanItemBreak: public CScanItem
  {
  private:
    unsigned C_INT32 mPlotB, mReportB;
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
    const CScanProblem * mpProblem;

    /**
     * A pointer to the random number generator
     */
    CRandom * mpRandomGenerator;

    std::vector<CScanItem*> mScanItems;

    unsigned C_INT32 mTotalSteps;

    /**
     * the index of the last item that has several subitems,
     * also the last item that need to generate output separators
     */
    C_INT32 mLastNestingItem;

    /**
     *
     */ 
    //unsigned C_INT32 mVariableSize;

    /**
     *
     */ 
    //C_FLOAT64 * mpVariables;

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

    static CScanMethod * createMethod();

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
    void setProblem(const CScanProblem * problem);

    bool init();

    bool scan();

    unsigned C_INT32 getTotalNumberOfSteps() const {return mTotalSteps;};

    /**
     *  The main scan method.
     */ 
    //void scan(unsigned C_INT32 s, bool C_UNUSED(nl), void (*pCallback)(CReport *), CReport *pReport);

  private:

    bool cleanupScanItems();

    bool loop(unsigned C_INT32 level);

    bool calculate() const;

    /**
     *  Set the value of the scan parameter based on the distribution
     *  @param unsigned C_INT32 i where to start in the distribution
     *  @param unsigned C_INT32 first first parameter in the set of Master/Slaves
     *  @param unsigned C_INT32 last last parameter in the set of Master/Slaves
     */ 
    //void setScanParameterValue(unsigned C_INT32 i,
    //                           unsigned C_INT32 first,
    //                           unsigned C_INT32 last);
  };

#endif // COPASI_CTrajectoryMethod
