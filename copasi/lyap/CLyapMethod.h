/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/lyap/CLyapMethod.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/05/04 10:54:43 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CLyapMethod class.
 */

#ifndef COPASI_CLyapMethod
#define COPASI_CLyapMethod

#include <string>

#include "utilities/CCopasiMethod.h"
#include "utilities/CVector.h"

class CLyapProblem;
class CState;

class CLyapValidSubTypes : public std::vector< CCopasiMethod::SubType >
  {
  public:
    /**
     * Default constructor.
     */
    CLyapValidSubTypes();

    /**
     * Destructor.
     */
    ~CLyapValidSubTypes();
  };

class CLyapMethod : public CCopasiMethod
  {
  public:
    /**
     *  A list of valid trajectory method types;
     */
    static const CLyapValidSubTypes ValidSubTypes;

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
     *  to the calling LyapTask
     */
    //CState * mpCurrentState;

    /**
     *  A pointer to the trajectory problem.
     */
    CLyapProblem * mpProblem;

    // Operations
  private:
    /**
     * Default constructor.
     */
    CLyapMethod();

  protected:
    /**
     * Default constructor.
     * @param const CCopasiMethod::SubType & subType
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CLyapMethod(const CCopasiMethod::SubType & subType,
                const CCopasiContainer * pParent = NULL);

  public:

    /**
     * Create a trajectory method for a special problem.
     * Note: the returned object has to be released after use with delete
     * a problem is also passed so that the method has a chance to choose an
     * appropriate simulation method.
     */
    static CLyapMethod *
    createLyapMethod(CCopasiMethod::SubType subType
                     = CCopasiMethod::lyapWolf,
                     CLyapProblem * pProblem = NULL);

    /**
     * Copy constructor.
     * @param "const CLyapMethod &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CLyapMethod(const CLyapMethod & src,
                const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CLyapMethod();

    /**
     *  Set a pointer to the current state.
     *  This method is used by CLyapTask::process()
     *  The results of the simulation are passed via this CState variable
     *  @param "CState *" currentState
     */
    //void setCurrentState(CState * currentState);

    /**
     *  Set a pointer to the problem.
     *  This method is used by CLyap
     *  @param "CLyapProblem *" problem
     */
    void setProblem(CLyapProblem * problem);

    /**
     *  This instructs the method to calculate a time step of deltaT
     *  starting with the current state, i.e., the result of the previous
     *  step.
     *  The new state (after deltaT) is expected in the current state.
     *  The return value is the actual timestep taken.
     *  @param "const double &" deltaT
     */
    virtual void step(const double & deltaT);

    virtual bool calculate() = 0;

    /**
     *  This instructs the method to prepare for integration
     *  starting with the initialState given.
     *  @param "const CState *" initialState
     */
    virtual void start(const CState * initialState);

    /**
     * Check if the method is suitable for this problem
     * @return bool suitability of the method
     */
    virtual bool isValidProblem(const CCopasiProblem * pProblem);
  };

#include "CLyapWolfMethod.h"

#endif // COPASI_CLyapMethod
