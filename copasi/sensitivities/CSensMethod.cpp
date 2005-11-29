/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sensitivities/CSensMethod.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/11/29 17:28:14 $
   End CVS Header */

/**
 *  CSensMethod class.
 *  This class describes the interface to all steady state methods.
 *  The variaous method like Newton have to be derived from
 *  this class.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

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
  mTargetDim = mTargetObjects.size();
  mTargetSizes.clear(); mTargetSizes.resize(mTargetDim);
  mTargetIndex.clear(); mTargetIndex.resize(mTargetDim);

  unsigned C_INT32 i;

  for (i = 0; i < mTargetDim; ++i)
    {
      mTargetSizes[i] = mTargetObjects[i].size();
    }

  mTarget1.resize(mTargetSizes);
  mTarget2.resize(mTargetSizes);

  mVariableDim = mVariableObjects.size();
  mVariableSizes.clear(); mVariableSizes.resize(mVariableDim);
  mVariableIndex.clear(); mVariableIndex.resize(mVariableDim);

  for (i = 0; i < mVariableDim; ++i)
    {
      mVariableSizes[i] = mVariableObjects[i].size();
    }

  //CCopasiArray mResult;
  //mResultDim =
  mIndex.clear(); mIndex.resize(mTargetDim + mVariableDim);
  std::vector<unsigned int>::iterator it =
    std::copy(mTargetSizes.begin(), mTargetSizes.end(), mIndex.begin());
  std::copy(mVariableSizes.begin(), mVariableSizes.end(), it);
  mResult.resize(mIndex);

  return true;
}

bool CSensMethod::processInternal()
{
  //store current state

  //do subtask
  doOneCalculation();

  //store target values to mTarget1
  storeTargetValues(mTarget1);

  //for()
  {
    //if requested restore original state (not for ss, but for all others, basically

    //change one variable

    //do subtask
    doOneCalculation();

    //store target values to mTarget2
    storeTargetValues(mTarget2);

    //calculate actual sensitivities

    //restore variable
  }
  return true;
}

bool CSensMethod::doOneCalculation()
{
  //only explicit
  if (true)
    {
      mpProblem->getModel()->updateRates();
    }

  //subtask
  if (false)
  {}

  return true;
}

bool CSensMethod::storeTargetValues(CCopasiArray & target)
{
  //so far only 1D array of objects are supported
  assert(mTargetDim == 1);

  std::vector<CCopasiObject*>::const_iterator it, itEnd = mTargetObjects[0].end();
  unsigned int i;
  for (it = mTargetObjects[0].begin(), i = 0; it != itEnd; ++it, ++i)
    {
      mVariableIndex[0] = i;
      mResult[mVariableIndex] = *(C_FLOAT64*)((*it)->getReference());
    }
  return true;
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
