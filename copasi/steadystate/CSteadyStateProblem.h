/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CSteadyStateProblem.h,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/10/05 12:31:06 $
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

#include "model/CState.h"
#include "utilities/CCopasiProblem.h"
#include "utilities/CReadConfig.h" 
//#include "utilities/CWriteConfig.h"

class CSteadyStateProblem: public CCopasiProblem
  {
    // Attributes
  private:
    /**
     *  The initial state, i.e., the starting conditions of the trajectroy.
     */
    CState mInitialState;

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
     * Set the model of the problem
     * @param CModel * pModel
     * @result bool succes
     */
    virtual bool setModel(CModel * pModel);

    /**
     * Retrieve the model the problem is dealing with.
     * @return "CModel *" pModel
     */ 
    //CModel * getModel() const;

    /**
     * Set the initial state of the problem.
     * @param const CState & InitialState
     */
    void setInitialState(const CState & initialState);

    /**
     * Set the initial state of the problem.
     * @param const CStateX & InitialState
     */
    void setInitialState(const CStateX & initialState);

    /**
     * Retrieve the initial state of the problem.
     * @return "const CState &" pInitialState
     */
    const CState & getInitialState() const;

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

    /**
     * Save a trajectory problem
     * @param "CWriteConfig &" configBuffer
     */ 
    //    void save(CWriteConfig & configBuffer) const;

  private:
    /**
     * This function synchronizes step size and number
     */
    void sync();
  };

#endif // COPASI_CSteadyStateProblem
