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

COptMethod * COptMethod::createMethod(COptMethod::Type type)
{
  COptMethod * Method = NULL;
  switch (type)
    {
    case RandomSearch:
      Method = new CRandomSearch();
      break;

    case RandomSearchMaster:
      Method = new CRandomSearchMaster();
      break;

    case SimulatedAnnealing:
      Method = new COptMethodSA();
      break;

    default:
      fatalError();
    }
  return Method;
}

// Default constructor
COptMethod::COptMethod(const bool & bounds):
    CMethodParameterList(),
    mTypeEnum(COptMethod::RandomSearch),
    mOptProblem(NULL),
    //    mParameters(NULL),
    //    mParameterMin(NULL),
    //    mParameterMax(NULL),
    mBounds(bounds)
{CONSTRUCTOR_TRACE;}

COptMethod::COptMethod(const COptMethod & src):
    CMethodParameterList(src),
    mTypeEnum(src.mTypeEnum),
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

int COptMethod::GetMethodType(void)
{
  return mTypeEnum;
}
