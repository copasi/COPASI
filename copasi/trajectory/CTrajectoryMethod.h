/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTrajectoryMethod.h,v $
   $Revision: 1.19 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/02/01 14:58:56 $
   End CVS Header */

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

#include "utilities/CCopasiMethod.h"
#include "utilities/CVector.h"

class CTrajectoryProblem;
class CState;

class CTrajectoryValidSubTypes : public std::vector< CCopasiMethod::SubType >
  {
  public:
    /**
     * Default constructor.
     */
    CTrajectoryValidSubTypes();

    /**
     * Destructor.
     */
    ~CTrajectoryValidSubTypes();
  };

class CTrajectoryMethod : public CCopasiMethod
  {
  public:
    /**
     *  A list of valid trajectory method types;
     */
    static const CTrajectoryValidSubTypes ValidSubTypes;

    /**
     * Checks whether the given sub type is a valid method
     * @param const CCopasiMethod::SubType & subType
     * @return bool isValidSubType
     */
    static bool isValidSubType(const CCopasiMethod::SubType & subType);

  protected:
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
  private:
    /**
     * Default constructor.
     */
    CTrajectoryMethod();

  protected:
    /**
     * Default constructor.
     * @param const CCopasiMethod::SubType & subType 
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CTrajectoryMethod(const CCopasiMethod::SubType & subType,
                      const CCopasiContainer * pParent = NULL);

  public:

    /**
     * Create a trajectory method for a special problem.
     * Note: the returned object has to be released after use with delete
     * a problem is also passed so that the method has a chance to choose an
     * appropriate simulation method.
     */
    static CTrajectoryMethod *
    createTrajectoryMethod(CCopasiMethod::SubType subType
                           = CCopasiMethod::deterministic,
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
#include "CTauLeapMethod.h"

#endif // COPASI_CTrajectoryMethod
