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
CSteadyStateProblem::CSteadyStateProblem():
    mpModel(NULL),
    mpInitialState(NULL)
{
  CONSTRUCTOR_TRACE;
  if (mpModel)
    mpInitialState = mpModel->getInitialState();
}

/**
 *  Copy constructor.
 *  @param "const CSteadyStateProblem &" src
 */
CSteadyStateProblem::CSteadyStateProblem(const CSteadyStateProblem & src):
    mpModel(src.mpModel),
    mpInitialState(src.mpInitialState)
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
void CSteadyStateProblem::setModel(CModel * pModel) {mpModel = pModel;}

/**
 * Retrieve the model the problem is dealing with.
 * @return "CModel *" pModel
 */
CModel * CSteadyStateProblem::getModel() const {return mpModel;}

/**
 * Set the initial state of the problem.
 * @param "const CState *" pInitialState
 */
void CSteadyStateProblem::setInitialState(CState * pInitialState)
{mpInitialState = pInitialState;}

/**
 * Retrieve the initial state of the problem.
 * @return "const CState *" pInitialState
 */
const CState * CSteadyStateProblem::getInitialState() const
  {return mpInitialState;}

/**
 * Set whether the jacobian is requested.
 * @param bool * jacobianRequested
 */
void CSteadyStateProblem::setJacobianRequested(bool * jacobianRequested)
{mJacobianRequested = jacobianRequested;}

/**
 * Retrieve whether the jacobian is requested.
 * @return bool jacobianRequested
 */
bool CSteadyStateProblem::isJacobianRequested() const
  {return mJacobianRequested;}

/**
 * Set whether stabilty analysis is requested.
 * @param bool * stabilityAnalysisRequested
 */
void CSteadyStateProblem::setStabilityAnalysisRequested(bool * stabilityAnalysisRequested)
{mStabilityAnalysisRequested = stabilityAnalysisRequested;}

/**
 * Retrieve whether the stabilty analysis is requested.
 * @return bool stabilityAnalysisRequested
 */
bool CSteadyStateProblem::isStabilityAnalysisRequested() const
  {return mStabilityAnalysisRequested;}

/**
 * Load a steadystate problem
 * @param "CReadConfig &" configBuffer
 */
void CSteadyStateProblem::load(CReadConfig & configBuffer,
                               CReadConfig::Mode mode)
{
  if (configBuffer.getVersion() < "4.0")
    {
      mpModel = Copasi->Model;
      mpInitialState = mpModel->getInitialState();
      configBuffer.getVariable("RepStabilityAnalysis", "bool" ,
                               &mStabilityAnalysisRequested,
                               CReadConfig::LOOP);
      mJacobianRequested = mStabilityAnalysisRequested;
    }
  else
    {
      string Tmp;

      configBuffer.getVariable("SteadyStateProblemModel", "string", &Tmp, mode);
      if (Tmp == Copasi->Model->getTitle())
        mpModel = Copasi->Model;
      else
        fatalError();

      mpInitialState = new CState;
      mpInitialState->load(configBuffer);

      configBuffer.getVariable("JacobianRequested", "bool" ,
                               &mJacobianRequested);
      configBuffer.getVariable("StabilityAnalysisRequested", "bool" ,
                               &mStabilityAnalysisRequested);
    }
}

/**
 * Save a steady state problem
 * @param "CWriteConfig &" configBuffer
 */
void CSteadyStateProblem::save(CWriteConfig & configBuffer) const
  {
    string Tmp = mpModel->getTitle();
    configBuffer.setVariable("SteadyStateProblemModel", "string", &Tmp);

    mpInitialState->save(configBuffer);

    configBuffer.setVariable("JacobianRequested", "bool" ,
                             &mJacobianRequested);
    configBuffer.setVariable("StabilityAnalysisRequested", "bool" ,
                             &mStabilityAnalysisRequested);
  }
