/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethod.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/30 17:58:52 $
   End CVS Header */

/**
 *  COptMethod class
 *  This class describes the interface to all optimization methods.
 *  The various method like RandomSearch or GA have to be derived from
 *  this class.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include "COptMethod.h"
#include "COptProblem.h"

const std::string COptMethod::TypeName[] =
  {
    "RandomSearch",
    "RandomSearchMaster",
    "SimulatedAnnealing"
  };

COptMethod * COptMethod::createMethod(CCopasiMethod::SubType subType)
{
  COptMethod * pMethod = NULL;
  switch (subType)
    {
    case RandomSearch:
      pMethod = new CRandomSearch();
      break;

    case RandomSearchMaster:
      pMethod = new CRandomSearchMaster();
      break;

    case SimulatedAnnealing:
      pMethod = new COptMethodSA();
      break;

    default:
      fatalError();
    }

  return pMethod;
}

// Default constructor
COptMethod::COptMethod():
    CCopasiMethod(CCopasiTask::optimization, CCopasiMethod::unset),
    mOptProblem(NULL),
    //    mParameters(NULL),
    //    mParameterMin(NULL),
    //    mParameterMax(NULL),
    mBounds(false)
{CONSTRUCTOR_TRACE;}

COptMethod::COptMethod(CCopasiMethod::SubType subType,
                       const CCopasiContainer * pParent):
    CCopasiMethod(CCopasiTask::optimization, subType, pParent),
    mOptProblem(NULL),
    //    mParameters(NULL),
    //    mParameterMin(NULL),
    //    mParameterMax(NULL),
    mBounds(false)
{CONSTRUCTOR_TRACE;}

COptMethod::COptMethod(const COptMethod & src,
                       const CCopasiContainer * pParent):
    CCopasiMethod(src, pParent),
    mOptProblem(src.mOptProblem),
    //    mParameters(src.mParameters),
    //    mParameterMin(src.mParameterMin),
    //    mParameterMax(src.mParameterMax),
    mBounds(src.mBounds)
{CONSTRUCTOR_TRACE;}

//YOHE: seems "virtual" cannot be outside of class declaration
COptMethod::~COptMethod()
{}

void COptMethod::setProblem(COptProblem * problem)
{
  assert(problem);
  mOptProblem = problem;
}

// Returns True if this method is capable of handling adjustable parameter boundary
// constraints, False otherwise
bool COptMethod::isBounded(void)
{
  return mBounds;
}

//virtual C_INT32 COptMethod::Optimise(C_FLOAT64 (*func) (void))
C_INT32 COptMethod::optimise(void)
{
  return 0;
}
