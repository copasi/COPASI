/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTrajectoryMethod.cpp,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:18:03 $
   End CVS Header */

/**
 *  CTrajectoryMethod class.
 *  This class describes the interface to all integration methods.
 *  The variaous method like LSODA or Gillespie have to be derived from
 *  this class.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#define COPASI_TRACE_CONSTRUCTION
#include "copasi.h"
#include "CTrajectoryMethod.h"
#include "CTrajectoryProblem.h"
#include "model/CState.h"
#include "model/CCompartment.h"

CTrajectoryValidSubTypes::CTrajectoryValidSubTypes():
    CVector< CCopasiMethod::SubType >(2)
{
  CCopasiMethod::SubType * pSubType = array();

  *pSubType++ = CCopasiMethod::deterministic;
  *pSubType++ = CCopasiMethod::stochastic;
}

/**
 * Destructor.
 */
CTrajectoryValidSubTypes::~CTrajectoryValidSubTypes() {}

const CTrajectoryValidSubTypes CTrajectoryMethod::ValidSubTypes;

#ifdef XXXX
const CVector< CCopasiMethod::SubType >
CTrajectoryMethod::ValidSubTypes(2,
                                 CCopasiMethod::deterministic,
                                 CCopasiMethod::stochastic,
                                 CCopasiMethod::hybrid);
#endif // XXXX

bool CTrajectoryMethod::isValidSubType(const CCopasiMethod::SubType & subType)
{
  unsigned C_INT32 i, imax = CTrajectoryMethod::ValidSubTypes.size();

  for (i = 0; i < imax; i++)
    if (CTrajectoryMethod::ValidSubTypes[i] == subType) return true;

  return false;
}

CTrajectoryMethod *
CTrajectoryMethod::createTrajectoryMethod(CCopasiMethod::SubType subType,
    CTrajectoryProblem * pProblem)
{
  CTrajectoryMethod * pMethod = NULL;

  switch (subType)
    {
    case unset:
    case deterministic:
      pMethod = new CLsodaMethod();
      break;

    case stochastic:
      pMethod = CStochMethod::createStochMethod(pProblem);
      break;

    case hybrid:
      pMethod = CHybridMethod::createHybridMethod(pProblem);
      break;

    default:
      fatalError();
    }
  return pMethod;
}

/**
 *  Default constructor.
 */
CTrajectoryMethod::CTrajectoryMethod(const CCopasiMethod::SubType & subType,
                                     const CCopasiContainer * pParent) :
    CCopasiMethod(CCopasiTask::timeCourse, subType, pParent),
    mpCurrentState(NULL),
    mpProblem(NULL)
{CONSTRUCTOR_TRACE;}

/**
 *  Copy constructor.
 *  @param "const CTrajectoryMethod &" src
 */
CTrajectoryMethod::CTrajectoryMethod(const CTrajectoryMethod & src,
                                     const CCopasiContainer * pParent):
    CCopasiMethod(src, pParent),
    mpCurrentState(src.mpCurrentState),
    mpProblem(src.mpProblem)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CTrajectoryMethod::~CTrajectoryMethod()
{DESTRUCTOR_TRACE;}

void CTrajectoryMethod::setCurrentState(CState * currentState)
{
  mpCurrentState = currentState;
}

/**
 *  Set a pointer to the problem.
 *  This method is used by CTrajectory 
 *  @param "CTrajectoryProblem *" problem
 */
void CTrajectoryMethod::setProblem(CTrajectoryProblem * problem)
{mpProblem = problem;}

/**
 *  This instructs the method to calculate a a time step of deltaT
 *  starting with the current state, i.e., the result of the previous
 *  step.
 *  The new state (after deltaT) is expected in the current state.
 *  The return value is the actual timestep taken.
 *  @param "const double &" deltaT
 *  @return "const double" actualDeltaT
 */
const double CTrajectoryMethod::step(const double & C_UNUSED(deltaT))
{return 0.0;}

/**
 *  This instructs the method to calculate a a time step of deltaT
 *  starting with the initialState given.
 *  The new state (after deltaT) is expected in the current state.
 *  The return value is the actual timestep taken.
 *  @param "double &" deltaT
 *  @param "const CState *" initialState
 *  @return "const double &" actualDeltaT
 */
const double CTrajectoryMethod::step(const double & C_UNUSED(deltaT),
                                     const CState * C_UNUSED(initialState))
{return 0.0;}
