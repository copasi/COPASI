/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethod.cpp,v $
   $Revision: 1.23 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/12/06 19:19:28 $
   End CVS Header */

/**
 *  COptMethod class
 *  This class describes the interface to all optimization methods.
 *  The various method like RandomSearch or GA have to be derived from
 *  this class.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#include "copasi.h"

#include "COptTask.h"
#include "COptMethod.h"
#include "COptProblem.h" 
/*
const std::string COptMethod::TypeName[] =
  {
    "EvolutionaryProgram",
    "GeneticAlgorithm",
    "GeneticAlgorithmSR",
//    "HybridGASA",
    "RandomSearch",
//    "RandomSearchMaster",
//    "SimulatedAnnealing",
    "SteepestDescent"
    ""
  };
 */
COptMethod * COptMethod::createMethod(CCopasiMethod::SubType subType)
{
  COptMethod * pMethod = NULL;

  switch (subType)
    {
    case EvolutionaryProgram:
      pMethod = new COptMethodEP();
      break;

    case GeneticAlgorithm:
      pMethod = new COptMethodGA();
      break;

    case GeneticAlgorithmSR:
      pMethod = new COptMethodGASR();
      break;

    case HookeJeeves:
      pMethod = new COptMethodHookeJeeves();
      break;

    case RandomSearch:
      pMethod = new CRandomSearch();
      break;

    case SteepestDescent:
      pMethod = new COptMethodSteepestDescent();
      break;

    default:
      pMethod = new COptMethodGA();
      //fatalError();
    }

  return pMethod;
}

// Default constructor
COptMethod::COptMethod():
    CCopasiMethod(CCopasiTask::optimization, CCopasiMethod::unset),
    mpOptProblem(NULL),
    mpParentTask(NULL),
    mBounds(false)
{CONSTRUCTOR_TRACE;}

COptMethod::COptMethod(const CCopasiTask::Type & taskType,
                       const COptMethod::SubType & subType,
                       const CCopasiContainer * pParent):
    CCopasiMethod(taskType, subType, pParent),
    mpOptProblem(NULL),
    mpParentTask(NULL),
    mBounds(false)
{CONSTRUCTOR_TRACE;}

COptMethod::COptMethod(const COptMethod & src,
                       const CCopasiContainer * pParent):
    CCopasiMethod(src, pParent),
    mpOptProblem(src.mpOptProblem),
    mpParentTask(src.mpParentTask),
    mBounds(src.mBounds)
{CONSTRUCTOR_TRACE;}

//YOHE: seems "virtual" cannot be outside of class declaration
COptMethod::~COptMethod()
{}

void COptMethod::setProblem(COptProblem * problem)
{
  assert(problem);
  mpOptProblem = problem;
}

// Returns True if this method is capable of handling adjustable parameter boundary
// constraints, False otherwise
bool COptMethod::isBounded(void)
{
  return mBounds;
}

//virtual C_INT32 COptMethod::Optimise(C_FLOAT64 (*func) (void))
bool COptMethod::optimise(void)
{
  return false;
}

bool COptMethod::initialize()
{
  if (!mpOptProblem)
    return false;
  if (!(mpOptItem = &mpOptProblem->getOptItemList()))
    return false;
  if (!(mpSetCalculateVariable = &mpOptProblem->getCalculateVariableUpdateMethods()))
    return false;

  mpParentTask = dynamic_cast<COptTask *>(getObjectParent());
  if (!mpParentTask) return false;

  /*if (pTask &&
      (mpReport = &pTask->getReport()) &&
      !mpReport->getStream())
    mpReport = NULL;*/

  return true;
}

bool COptMethod::cleanup()
{return true;}

//virtual
bool COptMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CCopasiMethod::isValidProblem(pProblem)) return false;

  const COptProblem * pTP = dynamic_cast<const COptProblem *>(pProblem);
  if (!pTP)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, "Problem is not an optimization problem.");
      return false;
    }

  return true;
}
