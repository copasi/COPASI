/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CSteadyStateProblem.cpp,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:18:02 $
   End CVS Header */

/**
 *  CSteadyStateProblem class.
 *  This class describes the steady state problem, i.e., it allows to specify
 *  for example initial conditions.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#include <string>

#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include "CSteadyStateProblem.h"
#include "model/CModel.h"
#include "model/CState.h"
#include "utilities/CGlobals.h"

/**
 *  Default constructor.
 *  @param "CModel *" pModel
 */
CSteadyStateProblem::CSteadyStateProblem(const CCopasiContainer * pParent):
    CCopasiProblem(CCopasiTask::steadyState, pParent),
    mInitialState()
{
  addParameter("JacobianRequested", CCopasiParameter::BOOL, true);
  addParameter("StabilityAnalysisRequested", CCopasiParameter::BOOL, true);
  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CSteadyStateProblem &" src
 */
CSteadyStateProblem::CSteadyStateProblem(const CSteadyStateProblem & src,
    const CCopasiContainer * pParent):
    CCopasiProblem(src, pParent),
    mInitialState(src.mInitialState)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CSteadyStateProblem::~CSteadyStateProblem()
{DESTRUCTOR_TRACE;}

/**
 * Set the model the problem is dealing with.
 * @param "CModel *" pModel
 */
bool CSteadyStateProblem::setModel(CModel * pModel)
{
  mpModel = pModel;
  mInitialState.setModel(mpModel);

  return true;
}

/**
 * Retrieve the model the problem is dealing with.
 * @return "CModel *" pModel
 */ 
//CModel * CSteadyStateProblem::getModel() const {return mpModel;}

/**
 * Set the initial state of the problem.
 * @param const CState & initialState
 */
void CSteadyStateProblem::setInitialState(const CState & initialState)
{
  mInitialState = initialState;
  mpModel = const_cast<CModel *>(mInitialState.getModel());
}

/**
 * Set the initial state of the problem.
 * @param const CStateX & InitialState
 */
void CSteadyStateProblem::setInitialState(const CStateX & initialState)
{
  mInitialState = initialState;
  mpModel = const_cast<CModel *>(mInitialState.getModel());
}

/**
 * Retrieve the initial state of the problem.
 * @return "const CState &" pInitialState
 */
const CState & CSteadyStateProblem::getInitialState() const
  {return mInitialState;}

/**
 * Set whether the jacobian is requested.
 * @param bool * jacobianRequested
 */
void CSteadyStateProblem::setJacobianRequested(bool & jacobianRequested)
{setValue("JacobianRequested", jacobianRequested);}

/**
 * Retrieve whether the jacobian is requested.
 * @return bool jacobianRequested
 */
bool CSteadyStateProblem::isJacobianRequested() const
  {return * (bool *) getValue("JacobianRequested");}

/**
 * Set whether stabilty analysis is requested.
 * @param bool * stabilityAnalysisRequested
 */
void CSteadyStateProblem::setStabilityAnalysisRequested(bool & stabilityAnalysisRequested)
{setValue("StabilityAnalysisRequested", stabilityAnalysisRequested);}

/**
 * Retrieve whether the stabilty analysis is requested.
 * @return bool stabilityAnalysisRequested
 */
bool CSteadyStateProblem::isStabilityAnalysisRequested() const
  {return * (bool *) getValue("StabilityAnalysisRequested");}

/**
 * Load a steadystate problem
 * @param "CReadConfig &" configBuffer
 */
void CSteadyStateProblem::load(CReadConfig & configBuffer,
                               CReadConfig::Mode C_UNUSED(mode))
{
  if (configBuffer.getVersion() < "4.0")
    {
      mpModel = Copasi->pModel;
      mInitialState = mpModel->getInitialState();
      configBuffer.getVariable("RepStabilityAnalysis", "bool" ,
                               getValue("StabilityAnalysisRequested"),
                               CReadConfig::LOOP);
      setValue("JacobianRequested",
               * (bool *) getValue("StabilityAnalysisRequested"));
    }
}

/**
 * Save a steady state problem
 * @param "CWriteConfig &" configBuffer
 */ 
/*void CSteadyStateProblem::save(CWriteConfig & C_UNUSED(configBuffer)) const
  {fatalError();}*/
