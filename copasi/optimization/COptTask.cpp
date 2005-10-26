/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptTask.cpp,v $
   $Revision: 1.21 $
   $Name:  $
   $Author: stupe $ 
   $Date: 2005/10/26 15:43:19 $
   End CVS Header */

/**
 * COptTask class.
 *
 * This class implements a optimization task which is comprised of a
 * of a problem and a method.
 *  
 */
#include "copasi.h"

#include "COptTask.h"
#include "COptProblem.h"
#include "COptMethod.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"

#include "model/CModel.h"
#include "model/CState.h"

//#include "trajectory/CTrajectoryTask.h"
//#include "trajectory/CTrajectoryProblem.h"
//#include "steadystate/CSteadyStateTask.h"
//#include "steadystate/CSteadyStateProblem.h"
//#include "utilities/COutputHandler.h"

unsigned C_INT32 COptTask::ValidMethods[] =
  {
    CCopasiMethod::GeneticAlgorithm,
    CCopasiMethod::GeneticAlgorithmSR,
    CCopasiMethod::EvolutionaryProgram,
    CCopasiMethod::RandomSearch,
    CCopasiMethod::SteepestDescent,
    CCopasiMethod::unset
  };

COptTask::COptTask(const CCopasiTask::Type & type,
                   const CCopasiContainer * pParent):
    CCopasiTask(type, pParent)
{
  mpProblem = new COptProblem(type, this);
  mpMethod = COptMethod::createMethod();
  this->add(mpMethod, true);
  //  mpMethod->setObjectParent(this);
  ((COptMethod *) mpMethod)->setProblem((COptProblem *) mpProblem);
}

COptTask::COptTask(const COptTask & src,
                   const CCopasiContainer * pParent):
    CCopasiTask(src, pParent)
{
  mpProblem = new COptProblem(* (COptProblem *) src.mpProblem, this);
  mpMethod = COptMethod::createMethod();
  this->add(mpMethod, true);
  //  mpMethod->setObjectParent(this);
  ((COptMethod *) mpMethod)->setProblem((COptProblem *) mpProblem);
}

COptTask::~COptTask()
{cleanup();}

void COptTask::cleanup(){}

bool COptTask::setCallBack(CProcessReport * pCallBack)
{
  bool success = CCopasiTask::setCallBack(pCallBack);

  if (!mpProblem->setCallBack(pCallBack)) success = false;
  if (!mpMethod->setCallBack(pCallBack)) success = false;

  return success;
}

bool COptTask::initialize(const OutputFlag & of,
                          std::ostream * pOstream)
{
  COptProblem * pProblem = dynamic_cast<COptProblem *>(mpProblem);
  COptMethod * pMethod = dynamic_cast<COptMethod *>(mpMethod);

  if (!pProblem || !pMethod) return false;

  //initialize reporting
  bool success = true;

  if (!CCopasiTask::initialize(of, pOstream)) success = false;
  //if (!mReport.open(pOstream)) success = false;
  //if (!mReport.compile()) success = false;

  if (!pProblem->initialize()) success = false;

  pMethod->setProblem(pProblem);
  //  if (!pMethod->initialize()) return false;

  return success;
}

bool COptTask::process(const bool & /* useInitialValues */)
{
  std::vector< UpdateMethod * > mUpdateMethods;
  CVector< C_FLOAT64 > mSolutionVariables;

  COptProblem * pProblem = dynamic_cast<COptProblem *>(mpProblem);
  COptMethod * pMethod = dynamic_cast<COptMethod *>(mpMethod);

  if (!pProblem || !pMethod) return false;

  mpMethod->isValidProblem(mpProblem);

  //bool Report = (mReport.getStream() != NULL);

  //if (Report) mReport.printHeader();
  initOutput();

  bool success = pMethod->optimise();

  //if (Report) mReport.printFooter();
  finishOutput();

  //should be renamed?
  // Optimization is done and we have best values for the parameters.
  mSolutionVariables = pProblem->getSolutionVariables();
  // From those values we need to update the model as while simulation the current state of the model might
  // not be the same as the state when best values are reached.
  // Hence get the pointers to UpdateMethods, get best parameter values and update the state.
  mUpdateMethods = pProblem->getCalculateVariableUpdateMethods();
  std::vector< UpdateMethod * >::iterator it = mUpdateMethods.begin();
  std::vector< UpdateMethod * >::iterator end = mUpdateMethods.end();
  // set the best paramter values
  // parameterCount = mSolutionVariables
  for (int i = 0; it != end; ++it, i++)
    (*mUpdateMethods[i])(mSolutionVariables[i]);

  // pProblem->calculate();
  // Now as state is updated we need to perform steady state analysis from this optimized state.

  // call restore at the last -- or u might want to check with Stefan if this restore is reqd or not... - Sameer
  // pProblem->restore();

  return success;
}

bool COptTask::setMethodType(const int & type)
{
  CCopasiMethod::SubType Type = (CCopasiMethod::SubType) type;

  //*************************** bellow commented *****
  // To get the following portions to work COptMethod needs to implement
  // isValidSubType method
  /*if (!COptMethod::isValidSubType(Type)) return false;*/
  if (mpMethod->getSubType() == Type) return true;

  pdelete (mpMethod);
  //****Current COptMethod only takes type parameter, modify as needed later on if
  //    want to add COptProblem parameter ***/
  /*mpMethod =
    COptMethod::createMethod(Type,(COptProblem *) mpProblem);*/
  mpMethod = COptMethod::createMethod(Type);
  this->add(mpMethod, true);
  //mpMethod->setObjectParent(this);

  return true;
}
