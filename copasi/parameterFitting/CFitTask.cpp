/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CFitTask.cpp,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/02/14 14:35:28 $
   End CVS Header */

/**
  * CFitTask class.
  *
  * This class implements a parameter estimation task which is comprised of a
  * of a problem and a method.
  *  
  */
#include "copasi.h"

#include "CFitTask.h"
 #include "CFitProblem.h"
 #include "CFitMethod.h"

#include "utilities/CCopasiMethod.h"

unsigned C_INT32 CFitTask::validMethods[] =
  {
    CCopasiMethod::GeneticAlgorithm,
    CCopasiMethod::GeneticAlgorithmSR,
    CCopasiMethod::EvolutionaryProgram,
    CCopasiMethod::RandomSearch,
    CCopasiMethod::SteepestDescent,
    CCopasiMethod::unset
  };

CFitTask::CFitTask(const CCopasiTask::Type & type,
                   const CCopasiContainer * pParent):
    COptTask(type, pParent)
{
  pdelete(mpProblem);
  mpProblem = new CFitProblem(type, this);
  pdelete(mpMethod);
  mpMethod = CFitMethod::createMethod();
  this->add(mpMethod, true);

  ((COptMethod *) mpMethod)->setProblem((COptProblem *) mpProblem);
}

CFitTask::CFitTask(const CFitTask & src,
                   const CCopasiContainer * pParent):
    COptTask(src, pParent)
{
  pdelete(mpProblem);
  mpProblem = new CFitProblem(* (CFitProblem *) src.mpProblem, this);
  pdelete(mpMethod);
  mpMethod = CFitMethod::createMethod(src.mpMethod->getSubType());
  this->add(mpMethod, true);

  ((COptMethod *) mpMethod)->setProblem((COptProblem *) mpProblem);
}

CFitTask::~CFitTask()
{cleanup();}

void CFitTask::cleanup(){}

bool CFitTask::setCallBack(CProcessReport * pCallBack)
{
  bool success = CCopasiTask::setCallBack(pCallBack);

  if (!mpProblem->setCallBack(pCallBack)) success = false;
  if (!mpMethod->setCallBack(pCallBack)) success = false;

  return success;
}

bool CFitTask::initialize(const OutputFlag & of,
                          std::ostream * pOstream)
{
  return COptTask::initialize(of, pOstream);
}

bool CFitTask::process(const bool & /* useInitialValues */)
{
  CFitProblem * pProblem = dynamic_cast<CFitProblem *>(mpProblem);
  COptMethod * pMethod = dynamic_cast<COptMethod *>(mpMethod);

  if (!pProblem || !pMethod) return false;

  mpMethod->isValidProblem(mpProblem);

  initOutput();

  bool success = pMethod->optimise();

  pProblem->calculateStatistics();

  finishOutput();

  return success;
}

bool CFitTask::restore()
{
  // The subtasks must be completely restored.
  dynamic_cast<CFitProblem *>(mpProblem)->restoreTrajectoryProblem();

  return CCopasiTask::restore();
}

bool CFitTask::setMethodType(const int & type)
{
  CCopasiMethod::SubType Type = (CCopasiMethod::SubType) type;

  if (mpMethod->getSubType() == Type) return true;

  pdelete (mpMethod);

  mpMethod = CFitMethod::createMethod(Type);
  this->add(mpMethod, true);

  return true;
}
