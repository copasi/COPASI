/**
 *  CTrajectoryProblem class.
 *  This class describes the trajectory problem, i.e., it allows to specify
 *  for example initial conditions and number of steps.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#ifndef COPASI_CScanProblem
#define COPASI_CScanProblem

#include <string>
#include "utilities/CMethodParameterList.h"
#include "utilities/CCopasiVector.h"

class CModel;
class CWriteConfig;
class CReadConfig;
class CTrajectoryTask;
class CSteadyStateTask;
class CRandom;
class Cr250;

class CScanProblem
  {
    // Attributes
  private:
    CRandom * pRandomGenerator;
    Cr250* pCr250Generator;

    /**
     *  The model the problem is working on.
     */
    CModel * mpModel;

    /**
     *
     */
    bool mProcessTrajectory;

    /**
     *
     */
    CTrajectoryTask * mpTrajectory;

    /**
     *
     */
    bool mProcessSteadyState;

    /**
     *
     */
    CSteadyStateTask * mpSteadyState;

    /**
     *
     */
    CCopasiVectorNS < CMethodParameterList > mScanItemList;

    /*
     * 
     */
    CVector<C_FLOAT64*>* pValueAddrMatrix;

  public:
    // Operations
    inline void setValueMatrixAddr(CVector<C_FLOAT64*>* pInputValueAddrMatrix)
    {
      pValueAddrMatrix = pInputValueAddrMatrix;
    }

    inline bool ifSteadyStateTask() {return mProcessSteadyState;}
    inline bool ifTrajectoryTask() {return mProcessTrajectory;}
    inline CSteadyStateTask* getSteadyStateTask() {return mpSteadyState;}
    inline CTrajectoryTask* getTrajectoryTask() {return mpTrajectory;}
    /**
    check if an object already exists in the list
    */
    inline bool bExisted(const std::string & name)
    {
      return (mScanItemList.getIndex(name) != C_INVALID_INDEX);
    }

    /**
      count the size of Parameter List
    */
    unsigned int paraCount()
    {
      return mScanItemList.size();
    }

    /**
     *  Default constructor.
     */
    CScanProblem();

    /**
     *  Copy constructor.
     *  @param "const CScanProblem &" src
     */
    CScanProblem(const CScanProblem & src);

    /**
     *  Destructor.
     */
    ~CScanProblem();

    /**
     * process the trajectory and steadystate task
    */

    void calculate();

    /**
     * Initialize the pointer for steadystate task 
    */
    void setSteadyStateTask(CSteadyStateTask* pSteadyStateTask);

    /**
     * Initialize the pointer to the trajectory task
    */
    void setTrajectoryTask(CTrajectoryTask* pTrajectoryTask);

    /**
     *  Size of the scanItem vector
     * @ return unsigned C_INT32 size
     */
    unsigned C_INT32 getListSize() const;

    /**
     *  Add a Scan Item to the vector ScanItem
     */
    void addScanItem(const CMethodParameterList & Item);

    /**
    * Delete a parameter in the list
    */
    void removeScanItem(const std::string & name);

    /**
    * Delete a parameter in the list
    */
    void swapScanItem(unsigned C_INT32 indexFrom, unsigned C_INT32 indexTo);

    /**
     *  Get a Scan Item from the vector ScanItem
     */
    CMethodParameterList * getScanItem(C_INT32 itemNumber);

    /**
     *  Add a parameter to a scan item
     * @param "const C_INT32" itemNumber
     * @param "const std::string &" name
     * @param "const double &" value
     */
    void addScanItemParameter(const C_INT32 itemNumber,
                              const std::string & name,
                              const double & value);

    /**
     *  Get a parameter from a scan item
     * @param "const C_INT32" itemNumber
     * @param "const std::string &" name
     */
    const double & getScanItemParameter(const C_INT32 itemNumber,
                                        const std::string & name);

    /**
     *  Set the value of a parameter in a scan item
     * @param "const C_INT32" itemNumber
     * @param "const std::string &" name
     * @param "const double &" value
     */
    void setScanItemParameter(const C_INT32 itemNumber,
                              const std::string & name,
                              const double & value);

    /**
     * Set the moddel the problem is dealing with.
     * @param "CModel *" pModel
     */
    void setModel(CModel * pModel);

    /**
     * Retrieve the model the problem is dealing with.
     * @return "CModel *" pModel
     */
    CModel * getModel() const;

    /**
     * Check whether to process a Trajectory task
     * @return bool processTrajectory
     */
    bool processTrajectory() const;

    /**
     * Set whether to process a Trajectory task
     * @param const bool & processTrajectory
     * @return bool success
     */
    bool setProcessTrajectory(const bool & processTrajectory);

    /**
     * Check whether to process a SteadyState task
     * @return bool processSteadyState
     */
    bool processSteadyState() const;

    /**
     * Set whether to process a SteadyState task
     * @param const bool & processSteadyState
     * @return bool success
     */
    bool setProcessSteadyState(const bool & processSteadyState);

    /**
     * Load a trajectory problem
     * @param "CReadConfig &" configBuffer
     * @param "CReadConfig::Mode mode (Default: CReadConfig::NEXT)
     */
    void load(CReadConfig & configBuffer,
              CReadConfig::Mode mode = CReadConfig::NEXT);

    /**
     * Save a trajectory problem
     * @param "CWriteConfig &" configBuffer
     */
    void save(CWriteConfig & configBuffer) const;

    /*
     Intialized all parameters insidethe Scan Parameter Matrix,
    */
    void InitScan(void);

    // this function counts the number of iterations to execute
    unsigned C_INT32 CountScan(void);

    /**
     *  Set the value of the scan parameter based on the distribution
     *  @param unsigned C_INT32 i where to start in the distribution
     *  @param unsigned C_INT32 first first parameter in the set of Master/Slaves
     *  @param unsigned C_INT32 last last parameter in the set of Master/Slaves
     */
    void setScanParameterValue(unsigned C_INT32 i,
                               unsigned C_INT32 first,
                               unsigned C_INT32 last);
  };

#endif // COPASI_CScanProblem
