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
    static const std::string TypeName[];

    // Attributes
  public:
    enum Type
    {
      unspecified = -1,
      deterministic = 0,
      stochastic,
      hybrid
    };

  protected:
    /**
     *  The type of the method
     */
    CTrajectoryMethod::Type mTypeEnum;

    /**
     *  A pointer to the current state. This is set from outside
     *  with the setState() method and never changed anywhere else.
     *  It´s used to report the results
     *  to the calling TrajectoryTask
     */
    CState * mpCurrentState;

    /**
     *  A pointer to the trajectory problem.
     */
    CTrajectoryProblem * mpProblem;

    // Operations
  protected:
    /**
     * Default constructor.
     * @param "const string &" name (Default = "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     * @param const std::string & type (default: "Trajectory Method Parameter List")
     */
    CTrajectoryMethod(const std::string & name = "NoName",
                      const CCopasiContainer * pParent = NULL,
                      const std::string & type = "Trajectory Method Parameter List");

  public:

    /**
     * Create a trajectory method for a special problem.
     * Note: the returned object has to be released after use with delete
     * a problem is also passed so that the method has a chance to choose an
     * appropriate simulation method.
     */
    static CTrajectoryMethod *
    createTrajectoryMethod(CTrajectoryMethod::Type type
                           = CTrajectoryMethod::deterministic,
                           CTrajectoryProblem * pProblem = NULL);

    /**
     * Copy constructor.
     * @param "const CTrajectoryMethod &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CTrajectoryMethod(const CTrajectoryMethod & src,
                      const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CTrajectoryMethod();

    /**
     * Retrieve the type in numeric form
     * @return const CTrajectoryMethod::Type & type 
     */
    const CTrajectoryMethod::Type & getTypeEnum() const;

    /**
     *  Set a pointer to the current state.
     *  This method is used by CTrajectoryTask::process()
     *  The results of the simulation are passed via this CState variable
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

#include "CLsodaMethod.h"
#include "CStochMethod.h"
#include "CHybridMethod.h"

#endif // COPASI_CTrajectoryMethod
