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

const string CTrajectoryMethod::MethodTypeName[] =
  {
    "unspecified",
    "deterministic",
    "stochastic",
    "hybrid"
  };

/**
 *  Default constructor.
 *  @param "CState *" currentState (Default = NULL)
 */
CTrajectoryMethod::CTrajectoryMethod(CState * currentState) :
    CMethodParameterList(),
    mName("No Name"),
    mType(CTrajectoryMethod::unspecified),
    mpCurrentState(currentState),
    mpProblem(NULL)
{CONSTRUCTOR_TRACE; }

/**
 *  Copy constructor.
 *  @param "const CTrajectoryMethod &" src
 */
CTrajectoryMethod::CTrajectoryMethod(const CTrajectoryMethod & src):
    CMethodParameterList(src),
    mName(src.mName),
    mType(src.mType),
    mpCurrentState(src.mpCurrentState),
    mpProblem(src.mpProblem)
{CONSTRUCTOR_TRACE; }

/**
 *  Destructor.
 */
CTrajectoryMethod::~CTrajectoryMethod()
{DESTRUCTOR_TRACE; }

/**
 *  Set a pointer to the current state.
 *  This method is used by CTrajectory 
 *  @param "CState *" currentState
 */
void CTrajectoryMethod::setCurrentState(CState * currentState)
{mpCurrentState = currentState; }

/**
 *  Set a pointer to the problem.
 *  This method is used by CTrajectory 
 *  @param "CTrajectoryProblem *" problem
 */
void CTrajectoryMethod::setProblem(CTrajectoryProblem * problem)
{mpProblem = problem; }

/**
 *  This instructs the method to calculate a a time step of deltaT
 *  starting with the current state, i.e., the result of the previous
 *  step.
 *  The new state (after deltaT) is expected in the current state.
 *  The return value is the actual timestep taken.
 *  @param "const double &" deltaT
 *  @return "const double" actualDeltaT
 */
const double CTrajectoryMethod::step(const double & deltaT) { return 0.0; }

/**
 *  This instructs the method to calculate a a time step of deltaT
 *  starting with the initialState given.
 *  The new state (after deltaT) is expected in the current state.
 *  The return value is the actual timestep taken.
 *  @param "double &" deltaT
 *  @param "const CState *" initialState
 *  @return "const double &" actualDeltaT
 */
const double CTrajectoryMethod::step(const double & deltaT,
                                     const CState * initialState)
{ return 0.0; }
