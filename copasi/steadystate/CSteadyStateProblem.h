/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CSteadyStateProblem.h,v $
   $Revision: 1.11.8.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/12/21 19:53:14 $
   End CVS Header */

/**
 *  CSteadyStateProblem class.
 *  This class describes the steady state problem, i.e., it allows to specify
 *  for example initial conditions.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#ifndef COPASI_CSteadyStateProblem
#define COPASI_CSteadyStateProblem

#include <string>

#include "utilities/CCopasiProblem.h"
#include "utilities/CReadConfig.h"

class CSteadyStateProblem: public CCopasiProblem
  {
    // Attributes
  private:
    /**
     *  The initial state, i.e., the starting conditions of the trajectroy.
     */ 
    //CState mInitialState;

    /**
     *  was a initial state set?
     */ 
    //bool mHasInitialState;

  public:
    // Operations

    /**
     * Default constructor.
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CSteadyStateProblem(const CCopasiContainer * pParent = NULL);

    /**
     *  Copy constructor.
     *  @param "const CSteadyStateProblem &" src
     * @paramconst CCopasiContainer * pParent (default: NULL)
     */
    CSteadyStateProblem(const CSteadyStateProblem & src,
                        const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    virtual ~CSteadyStateProblem();

    /**
     * Do all neccessary initialization so that calls to caluclate will 
     * be successful. This is called once from CCopasiTask::process()
     * @result bool succes
     */
    virtual bool initialize();

    /**
     * Set whether the jacobian is requested.
     * @param bool & jacobianRequested
     */
    void setJacobianRequested(bool & jacobianRequested);

    /**
     * Retrieve whether the jacobian is requested.
     * @return bool jacobianRequested
     */
    bool isJacobianRequested() const;

    /**
     * Set whether stabilty analysis is requested.
     * @param bool & stabilityAnalysisRequested
     */
    void setStabilityAnalysisRequested(bool & stabilityAnalysisRequested);

    /**
     * Retrieve whether the stabilty analysis is requested.
     * @return bool stabilityAnalysisRequested
     */
    bool isStabilityAnalysisRequested() const;

    /**
     * Load a trajectory problem
     * @param "CReadConfig &" configBuffer
     * @param "CReadConfig::Mode mode (Default: CReadConfig::NEXT)
     */
    void load(CReadConfig & configBuffer,
              CReadConfig::Mode mode = CReadConfig::NEXT);
  };

#endif // COPASI_CSteadyStateProblem
