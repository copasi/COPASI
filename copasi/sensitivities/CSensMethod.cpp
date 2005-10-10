/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sensitivities/CSensMethod.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/10/10 16:13:43 $
   End CVS Header */

/**
 *  CSensMethod class.
 *  This class describes the interface to all steady state methods.
 *  The variaous method like Newton have to be derived from
 *  this class.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"

//#include "utilities/CCopasiVector.h"
#include "CSensMethod.h"
#include "CSensProblem.h"

#include "model/CModel.h"
#include "model/CState.h"

CSensMethod *
CSensMethod::createSensMethod(CCopasiMethod::SubType subType)
{
  CSensMethod * pMethod = NULL;

  switch (subType)
    {
    case unset:
    case sensMethod:
      pMethod = new CSensMethod(subType);
      break;

    default:
      fatalError();
    }

  return pMethod;
}

/**
 *  Default constructor.
 */
CSensMethod::CSensMethod(CCopasiMethod::SubType subType,
                         const CCopasiContainer * pParent):
    CCopasiMethod(CCopasiTask::sens, subType, pParent),
    mpProblem(NULL)
{CONSTRUCTOR_TRACE;}

/**
 *  Copy constructor.
 *  @param "const CSensMethod &" src
 */
CSensMethod::CSensMethod(const CSensMethod & src,
                         const CCopasiContainer * pParent):
    CCopasiMethod(src, pParent),
    mpProblem(src.mpProblem)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CSensMethod::~CSensMethod()
{DESTRUCTOR_TRACE;}

/**
 *  Set a pointer to the problem.
 *  This method is used by CSteadyState 
 *  @param "CSteadyStateProblem *" problem
 */ 
//void CSensMethod::setProblem(CSteadyStateProblem * problem)
//{mpProblem = problem;}

/**
 * This instructs the method to calculate a the steady state
 * starting with the initialState given.
 * The steady state is returned in the object pointed to by steadyState.
 * @param CState * steadyState
 * @param const CState * initialState
 * @param C_FLOAT64 * jacobian
 * @param CEigen * eigenValues
 * @return CSensMethod::ReturnCode returnCode
 */
bool CSensMethod::process(CProcessReport * handler)
{
  return false;
}

bool CSensMethod::initialize(CSensProblem* problem)
{
  //do what needs to be done only once even if the task is run several times.

  //initialize the object vectors

  //resize the arrays
  mTargetSizes.clear(); mTargetSizes.resize(mTargetObjects.size());
  //mTarget1.clear(); mTarget1.resize(mTargetObjects.size());
  //mTarget2.clear(); mTarget2.resize(mTargetObjects.size());

  unsigned C_INT32 i, imax;

  for (i = 0; i < mTargetObjects.size(); ++i)
    {
      mTargetSizes[i] = mTargetObjects[i].size();

      //mTarget1[i].resize(mTargetObjects[i].size());
      //mTarget2[i].resize(mTargetObjects[i].size());
    }

  mVariableSizes.clear(); mVariableSizes.resize(mVariableObjects.size());

  for (i = 0; i < mVariableObjects.size(); ++i)
    {
      mVariableSizes[i] = mVariableObjects[i].size();
    }

  //CCopasiArray mResult;
}

bool CSensMethod::processInternal()
{
  //store current state

  //do subtask

  //store target values to mTarget1

  //for()
  {
    //if requested restore original state (not for ss, but for all others, basically

    //change one variable

    //do subtask

    //store target values to mTarget2

    //calculate actual sensitivities

    //restore variable
  }
}

//bool CSensMethod::calculateOneSensitivity()
//{
//}

//virtual
bool CSensMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CCopasiMethod::isValidProblem(pProblem)) return false;

  const CSensProblem * pP = dynamic_cast<const CSensProblem *>(pProblem);
  if (!pP)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, "Problem is not a sensitivities problem.");
      return false;
    }

  return true;
}
