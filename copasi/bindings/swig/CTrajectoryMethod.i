%{

#include "trajectory/CTrajectoryMethod.h"

%}


class CTrajectoryMethod : public CCopasiMethod
{
  public:
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
     *  This instructs the method to calculate a time step of deltaT
     *  starting with the current state, i.e., the result of the previous
     *  step.
     *  The new state (after deltaT) is expected in the current state.
     *  The return value is the actual timestep taken.
     *  @param "const double &" deltaT
     */
    virtual void step(const double & deltaT);

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


