/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CSteadyStateProblem.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:33:15 $
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
#include "utilities/CReadConfig.h"
#include "utilities/CWriteConfig.h"

class CSteadyStateProblem
  {
    // Attributes
  private:
    /**
     *  The model the problem is working on.
     */
    CModel * mpModel;

    /**
     *  The resolution of the steadystate.
     */
    unsigned C_INT32 mResolution;

    /**
     *  The factor used for finite difference methods.
     */
    unsigned C_INT32 mFactor;

    /**
     *  The initial state, i.e., the starting conditions of the trajectroy.
     */
    CState mInitialState;

    /**
     *  Whether the jacobian is requested for the steady state
     */
    bool mJacobianRequested;

    /**
     *  Whether the stabilty analysis is requested for the the steady state
     */
    bool mStabilityAnalysisRequested;

  public:
    // Operations

    /**
     *  Default constructor.
     */
    CSteadyStateProblem();

    /**
     *  Copy constructor.
     *  @param "const CSteadyStateProblem &" src
     */
    CSteadyStateProblem(const CSteadyStateProblem & src);

    /**
     *  Destructor.
     */
    ~CSteadyStateProblem();

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
    void save(CWriteConfig & configBuffer) const;

  private:
    /**
     * This function synchronizes step size and number
     */
    void sync();
  };

#endif // COPASI_CSteadyStateProblem
