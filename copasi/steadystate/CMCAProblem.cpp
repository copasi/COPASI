/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CMCAProblem.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/10/21 15:10:49 $
   End CVS Header */

/**
 *  CMCAProblem class.
 *  This class describes the metabolic control analysis problem, i.e., it allows to specify
 *  for example initial conditions.
 *  
 *  Created for Copasi by Ralph Gauges 2004
 */

#include <string>

#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include "CMCAProblem.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "utilities/CGlobals.h"

/**
 *  Default constructor.
 *  @param "CModel *" pModel
 */
CMCAProblem::CMCAProblem(const CCopasiContainer * pParent):
    CCopasiProblem(CCopasiTask::steadyState, pParent),
    mInitialState()
{
  addParameter("JacobianRequested", CCopasiParameter::BOOL, true);
  addParameter("StabilityAnalysisRequested", CCopasiParameter::BOOL, true);
  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CMCAProblem &" src
 */
CMCAProblem::CMCAProblem(const CMCAProblem & src,
                         const CCopasiContainer * pParent):
    CCopasiProblem(src, pParent),
    mInitialState(src.mInitialState)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CMCAProblem::~CMCAProblem()
{DESTRUCTOR_TRACE;}

/**
 * Set the model the problem is dealing with.
 * @param "CModel *" pModel
 */
bool CMCAProblem::setModel(CModel * pModel)
{
  mpModel = pModel;
  mInitialState.setModel(mpModel);

  return true;
}

/**
 * Retrieve the model the problem is dealing with.
 * @return "CModel *" pModel
 */ 
//CModel * CMCAProblem::getModel() const {return mpModel;}

/**
 * Set the initial state of the problem.
 * @param const CState & initialState
 */
void CMCAProblem::setInitialState(const CState & initialState)
{
  mInitialState = initialState;
  mpModel = const_cast<CModel *>(mInitialState.getModel());
}

/**
 * Set the initial state of the problem.
 * @param const CStateX & InitialState
 */
void CMCAProblem::setInitialState(const CStateX & initialState)
{
  mInitialState = initialState;
  mpModel = const_cast<CModel *>(mInitialState.getModel());
}

/**
 * Retrieve the initial state of the problem.
 * @return "const CState &" pInitialState
 */
const CState & CMCAProblem::getInitialState() const
  {return mInitialState;}

/**
 * Set whether the jacobian is requested.
 * @param bool * jacobianRequested
 */
void CMCAProblem::setJacobianRequested(bool & jacobianRequested)
{setValue("JacobianRequested", jacobianRequested);}

/**
 * Retrieve whether the jacobian is requested.
 * @return bool jacobianRequested
 */
bool CMCAProblem::isJacobianRequested() const
  {return * (bool *) getValue("JacobianRequested");}

/**
 * Set whether stabilty analysis is requested.
 * @param bool * stabilityAnalysisRequested
 */
void CMCAProblem::setStabilityAnalysisRequested(bool & stabilityAnalysisRequested)
{setValue("StabilityAnalysisRequested", stabilityAnalysisRequested);}

/**
 * Retrieve whether the stabilty analysis is requested.
 * @return bool stabilityAnalysisRequested
 */
bool CMCAProblem::isStabilityAnalysisRequested() const
  {return * (bool *) getValue("StabilityAnalysisRequested");}

/**
 * Load a steadystate problem
 * @param "CReadConfig &" configBuffer
 */
void CMCAProblem::load(CReadConfig & configBuffer,
                       CReadConfig::Mode C_UNUSED(mode))
{
  if (configBuffer.getVersion() < "4.0")
    {
      mpModel = Copasi->pModel;
      mInitialState = mpModel->getState();
      configBuffer.getVariable("RepSteadyStateAnalysis", "bool" ,
                               getValue("SteadyStateRequested"),
                               CReadConfig::LOOP);
    }
}
