/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tss/Attic/CTSSProblem.cpp,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/11/29 17:28:22 $
   End CVS Header */

#include <string>

#include "copasi.h"
#include "CTSSProblem.h" 
//#include "model/CModel.h"
//#include "model/CState.h"
#include "CopasiDataModel/CCopasiDataModel.h"

/**
 *  Default constructor.
 *  @param "CModel *" pModel
 */
CTSSProblem::CTSSProblem(const CCopasiContainer * pParent):
    CCopasiProblem(CCopasiTask::steadyState, pParent)
{
  //addParameter("JacobianRequested", CCopasiParameter::BOOL, true);
  //addParameter("StabilityAnalysisRequested", CCopasiParameter::BOOL, true);
  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CTSSProblem &" src
 */
CTSSProblem::CTSSProblem(const CTSSProblem & src,
                         const CCopasiContainer * pParent):
    CCopasiProblem(src, pParent)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CTSSProblem::~CTSSProblem()
{DESTRUCTOR_TRACE;}
