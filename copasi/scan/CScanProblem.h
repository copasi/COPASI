/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/scan/CScanProblem.h,v $
   $Revision: 1.17 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/12 16:51:08 $
   End CVS Header */

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
#include "utilities/CCopasiMethod.h"
#include "utilities/CCopasiProblem.h"
#include "utilities/CCopasiVector.h"

class CModel;
class CWriteConfig;
class CReadConfig;
class CTrajectoryTask;
class CSteadyStateTask;
class CRandom;
class Cr250;

class CScanProblem : public CCopasiProblem
  {
  public:
    enum Type
    {
      SD_UNIFORM = 0,
      SD_GAUSS,
      SD_BOLTZ,
      SD_REGULAR
    };

    // Attributes
  private:
    /**
     *
     */
    CCopasiParameterGroup * mpScanParameterList;

    /**
     *
     */
    CTrajectoryTask * mpTrajectory;

    /**
     *
     */
    CSteadyStateTask * mpSteadyState;

    /**
     * 
     */
    CVector< C_FLOAT64 * > mMapping;

  public:
    /**
     * Default constructor.
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CScanProblem(const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor.
     * @param const CScanProblem & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CScanProblem(const CScanProblem & src,
                 const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    virtual ~CScanProblem();

    /**
     * Set the model of the problem
     * @param CModel * pModel
     * @result bool succes
     */
    virtual bool setModel(CModel * pModel);

    /**
     * Do all neccessary initialization so that calls to caluclate will 
     * be successful. This is called once from CScanTask::process()
     * @result bool succes
     */
    virtual bool initialize();

    /**
     * Do the calculattin based on CalculateVariables and fill
     * CalculateResults with the results. 
     * @result bool succes
     */
    virtual bool calculate();

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
     * @param const std::string & name
     * @return bool success
     */
    bool addScanItem(const std::string & name);

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
    CCopasiParameterGroup * getScanItem(C_INT32 itemNumber);

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
     * Get a parameter from a scan item
     * @param "const C_INT32" itemNumber
     * @param "const std::string &" name
     * @return void *;
     */
    void * getScanItemParameter(const C_INT32 itemNumber,
                                const std::string & name);

    /**
     * Set the value of a parameter in a scan item
     * @param const C_INT32 itemNumber
     * @param const std::string & name
     * @param const CType & value
     * @return bool success
     */
    template< class CType >
          bool setScanItemParameter(const C_INT32 itemNumber,
                                    const std::string & name,
                                    const CType & value)
      {
        return
        ((CCopasiParameterGroup *)
         mpScanParameterList->getParameter(itemNumber))
        ->setValue(name, value);
      }

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

    // this function counts the number of iterations to execute
    unsigned C_INT32 CountScan(void);

    CSteadyStateTask* getSteadyStateTask();
    CTrajectoryTask* getTrajectoryTask();

    /**
     * check if an object already exists in the list
     */
    bool bExisted(const std::string & name);

  private:
    /**
     * Intialized all parameters insidethe Scan Parameter Matrix,
     */
    void InitScan(void);
  };

#endif // COPASI_CScanProblem
