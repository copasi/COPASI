/**
 *  CTrajectoryMethod class.
 *  This class describes the interface to all integration methods.
 *  The variaous method like LSODA or Gillespie have to be derived from
 *  this class.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#ifndef COPASI_CTrajectoryMethod
#define COPASI_CTrajectoryMethod

#include <string>

#include "utilities/CMethodParameterList.h"

class CTrajectoryProblem;

class CState;

class CTrajectoryMethod : public CMethodParameterList
  {
  public:
    static const string MethodTypeName[];

    // Attributes

  private:
    enum MethodType
    {
      unspecified = 0,
      deterministic,
      stochastic,
      hybrid
    };

    /**
     *  The name of the method
     */
    string mName;

    /**
     *  The type of the method
     */
    CTrajectoryMethod::MethodType mType;

    /**
     *  A pointer to the current state
     */
    CState * mpCurrentState;

    /**
     *  A pointer to the trajectory problem.
     */
    CTrajectoryProblem * mpProblem;

  public:
    // Operations

    /**
     *  Default constructor.
     *  @param "CState *" currentState (Default = NULL)
     */
    CTrajectoryMethod(CState * currentState = NULL);

    /**
     *  Copy constructor.
     *  @param "const CTrajectoryMethod &" src
     */
    CTrajectoryMethod(const CTrajectoryMethod & src);

    /**
     *  Destructor.
     */
    ~CTrajectoryMethod();

    /**
     *  Set a pointer to the current state.
     *  This method is used by CTrajectory 
     *  @param "CState *" currentState
     */
    void setCurrentState(CState * currentState);

    /**
     *  Set a pointer to the problem.
     *  This method is used by CTrajectory 
     *  @param "CTrajectoryProblem *" problem
     */
    void setProblem(CTrajectoryProblem * problem);

    /**
     *  This instructs the method to calculate a a time step of deltaT
     *  starting with the current state, i.e., the result of the previous
     *  step.
     *  The new state (after deltaT) is expected in the current state.
     *  The return value is the actual timestep taken.
     *  @param "const double &" deltaT
     *  @return "const double" actualDeltaT
     */
    virtual const double step(const double & deltaT);

    /**
     *  This instructs the method to calculate a a time step of deltaT
     *  starting with the initialState given.
     *  The new state (after deltaT) is expected in the current state.
     *  The return value is the actual timestep taken.
     *  @param "double &" deltaT
     *  @param "const CState *" initialState
     *  @return "const double" actualDeltaT
     */
    virtual const double step(const double & deltaT, const CState * initialState);
  };

#endif // COPASI_CTrajectoryMethod
