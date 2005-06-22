/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tss/Attic/CTSSMethod.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/22 15:54:21 $
   End CVS Header */

/**
 *  CTSSMethod class.
 *  This class describes the interface to all steady state methods.
 *  The variaous method like Newton have to be derived from
 *  this class.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"

//#include "utilities/CCopasiVector.h"
#include "CTSSMethod.h"
#include "CTSSProblem.h"

#include "model/CModel.h"
#include "model/CState.h"

CTSSMethod *
CTSSMethod::createTSSMethod(CCopasiMethod::SubType subType)
{
  CTSSMethod * pMethod = NULL;

  switch (subType)
    {
    case unset:
    case tssMethod:
      pMethod = new CTSSMethod(subType);
      break;

    default:
      fatalError();
    }

  return pMethod;
}

/**
 *  Default constructor.
 */
CTSSMethod::CTSSMethod(CCopasiMethod::SubType subType,
                       const CCopasiContainer * pParent):
    CCopasiMethod(CCopasiTask::tss, subType, pParent),
    mpProblem(NULL)
{CONSTRUCTOR_TRACE;}

/**
 *  Copy constructor.
 *  @param "const CTSSMethod &" src
 */
CTSSMethod::CTSSMethod(const CTSSMethod & src,
                       const CCopasiContainer * pParent):
    CCopasiMethod(src, pParent),
    mpProblem(src.mpProblem)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CTSSMethod::~CTSSMethod()
{DESTRUCTOR_TRACE;}

/**
 *  Set a pointer to the problem.
 *  This method is used by CSteadyState 
 *  @param "CSteadyStateProblem *" problem
 */ 
//void CTSSMethod::setProblem(CSteadyStateProblem * problem)
//{mpProblem = problem;}

/**
 * This instructs the method to calculate a the steady state
 * starting with the initialState given.
 * The steady state is returned in the object pointed to by steadyState.
 * @param CState * steadyState
 * @param const CState * initialState
 * @param C_FLOAT64 * jacobian
 * @param CEigen * eigenValues
 * @return CTSSMethod::ReturnCode returnCode
 */
bool CTSSMethod::process(CProcessReport * handler)
{
  return false;
}

//virtual
bool CTSSMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!pProblem)
    {
      //no problem
      CCopasiMessage(CCopasiMessage::EXCEPTION, "pProblem == NULL");
      return false;
    }

  const CTSSProblem * pP = dynamic_cast<const CTSSProblem *>(pProblem);
  if (!pP)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, "Problem is not a time scale separation problem.");
      return false;
    }

  return true;
}
