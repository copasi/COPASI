/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/steadystate/CMCAProblem.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/10/21 15:29:57 $
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
                               getValue("SteadyStateRequested"),
                               CReadConfig::LOOP);
    }
}
