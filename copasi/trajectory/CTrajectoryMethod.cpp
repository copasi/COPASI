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

const std::string CTrajectoryMethod::TypeName[] =
  {
    "deterministic",
    "stochastic",
    "hybrid",
    ""
  };

CTrajectoryMethod *
CTrajectoryMethod::createTrajectoryMethod(CTrajectoryMethod::Type type,
    CTrajectoryProblem * pProblem)
{
  CTrajectoryMethod * Method = NULL;

  switch (type)
    {
    case unspecified:
    case deterministic:
      Method = new CLsodaMethod();
      break;

    case stochastic:
      Method = CStochMethod::createStochMethod(pProblem);
      break;

    case hybrid:
      Method = CHybridMethod::createHybridMethod(pProblem);
      break;

    default:
      fatalError();
    }
  return Method;
}

/**
 *  Default constructor.
 */
CTrajectoryMethod::CTrajectoryMethod(const std::string & name,
                                     const CCopasiContainer * pParent,
                                     const std::string & type) :
    CMethodParameterList(name, pParent, type),
    mTypeEnum(CTrajectoryMethod::unspecified),
    mpCurrentState(NULL),
    mpProblem(NULL)
{CONSTRUCTOR_TRACE;}

/**
 *  Copy constructor.
 *  @param "const CTrajectoryMethod &" src
 */
CTrajectoryMethod::CTrajectoryMethod(const CTrajectoryMethod & src,
                                     const CCopasiContainer * pParent):
    CMethodParameterList(src, pParent),
    mTypeEnum(src.mTypeEnum),
    mpCurrentState(src.mpCurrentState),
    mpProblem(src.mpProblem)
{CONSTRUCTOR_TRACE;}

/**
 *  Destructor.
 */
CTrajectoryMethod::~CTrajectoryMethod()
{DESTRUCTOR_TRACE;}

const CTrajectoryMethod::Type & CTrajectoryMethod::getTypeEnum() const
  {return mTypeEnum;}

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
