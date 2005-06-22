/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tss/Attic/CTSSProblem.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/06/22 12:09:52 $
   End CVS Header */

#ifdef COPASI_TSS

#include <string>

#define COPASI_TRACE_CONSTRUCTION
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

#endif // COPASI_TSS
