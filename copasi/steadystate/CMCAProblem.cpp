/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CMCAProblem.cpp,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/21 20:35:15 $
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

/**
 *  Default constructor.
 *  @param "CModel *" pModel
 */
CMCAProblem::CMCAProblem(const CCopasiContainer * pParent):
    CCopasiProblem(CCopasiTask::steadyState, pParent),
    mInitialState()
{
  addParameter("SteadyStateRequested", CCopasiParameter::BOOL, true);
  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CMCAProblem &" src
 */
CMCAProblem::CMCAProblem(const CMCAProblem & src,
                         const CCopasiContainer * pParent):
    CCopasiProblem(src, pParent)
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
  return true;
}

/**
 * Load a mca problem
 * @param "CReadConfig &" configBuffer
 */
void CMCAProblem::load(CReadConfig & configBuffer,
                       CReadConfig::Mode C_UNUSED(mode))
{
  if (configBuffer.getVersion() < "4.0")
    {
      configBuffer.getVariable("RepxSteadyStateAnalysis", "bool" ,
                               getValue("SteadyStateRequested").pBOOL,
                               CReadConfig::LOOP);
    }
}

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
 * Set whether the steady state analysis is requested.
 * @param bool * steadyStateRequested
 */
void CMCAProblem::setSteadyStateRequested(bool & steadyStateRequested)
{setValue("SteadyStateRequested", steadyStateRequested);}

/**
 * Retrieve whether the steady state analysis is requested.
 * @return bool steadyStateRequested
 */
bool CMCAProblem::isSteadyStateRequested() const
  {return * getValue("SteadyStateRequested").pBOOL;}
