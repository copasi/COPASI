/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CMCAProblem.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/10/21 15:10:50 $
   End CVS Header */

/**
 *  CMCAProblem class.
 *  This class describes the metabolic control analysis problem, i.e., it allows to specify
 *  for example initial conditions.
 *  
 *  Created for Copasi by Ralph Gauges 2004
 */

#ifndef COPASI_CMCAProblem
#define COPASI_CMCAProblem

#include <string>

#include "model/CState.h"
#include "utilities/CCopasiProblem.h"
#include "utilities/CReadConfig.h"

class CMCAProblem: public CCopasiProblem
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
    CMCAProblem(const CCopasiContainer * pParent = NULL);

    /**
     *  Copy constructor.
     *  @param "const CMCAProblem &" src
     * @paramconst CCopasiContainer * pParent (default: NULL)
     */
    CMCAProblem(const CMCAProblem & src,
                const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    virtual ~CMCAProblem();

    /**
     * Set the model of the problem
     * @param CModel * pModel
     * @result bool succes
     */
    virtual bool setModel(CModel * pModel);

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
     * Set whether the steady state analysis is requested.
     * @param bool & steadyStateRequested
     */
    void setSteadyStateRequested(bool & steadyStateRequested);

    /**
     * Retrieve whether a steady state analysis is requested.
     * @return bool steadyStateRequested
     */
    bool isSteadyStateRequested() const;

    /**
     * Load a trajectory problem
     * @param "CReadConfig &" configBuffer
     * @param "CReadConfig::Mode mode (Default: CReadConfig::NEXT)
     */
    void load(CReadConfig & configBuffer,
              CReadConfig::Mode mode = CReadConfig::NEXT);

  private:
  };
