/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CTrajectoryProblem.h,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/06 21:36:50 $
   End CVS Header */

/**
 *  CTrajectoryProblem class.
 *  This class describes the trajectory problem, i.e., it allows to specify
 *  for example initial conditions and number of steps.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */

#ifndef COPASI_CTrajectoryProblem
#define COPASI_CTrajectoryProblem

#include <string>

#include "utilities/CCopasiProblem.h"
#include "utilities/CReadConfig.h"
#include "utilities/CWriteConfig.h"
#include "model/CState.h"

class CModel;

class CTrajectoryProblem : public CCopasiProblem
  {
    // Attributes
  private:
    /**
     *  The number of steps to calculate
     */
    unsigned C_INT32 mStepNumber;

    /**
     *  The size of each step
     */
    double mStepSize;

    /**
     *  Indicate whether the step number or step size was set last.
     */
    bool mStepNumberSetLast;

    /**
     *  The start time of the trajectory
     */
    double mStartTime;

    /**
     *  The end time of the trajectory
     */
    double mEndTime;

    /**
     *  The initial state, i.e., the starting conditions of the trajectroy.
     */
    CState mInitialState;

    /**
     *  The final state of the trajectory at time EndTime
     */
    CState mEndState;

  public:
    // Operations

    /**
     * Default constructor.
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CTrajectoryProblem(const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor.
     * @param const CTrajectoryProblem & src
     * @paramconst CCopasiContainer * pParent (default: NULL)
     */
    CTrajectoryProblem(const CTrajectoryProblem & src,
                       const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CTrajectoryProblem();

    /**
     * Set the moddel the problem is dealing with.
     * @param "CModel *" pModel
     */
    virtual bool setModel(CModel * pModel);

    /**
     * Set the number of time steps the trajectory method should integrate.
     * @param "const unsigned C_INT32 &" stepNumber
     */
    void setStepNumber(const unsigned C_INT32 & stepNumber);

    /**
     * Retrieve the number of time steps the trajectory method should integrate.
     * @return "const unsigned C_INT32 &" stepNumber
     */
    const unsigned C_INT32 & getStepNumber() const;

    /**
     * Set the size a integration step the trajectory method should do.
     * @param "const double &" stepSize
     */
    void setStepSize(const double & stepSize);

    /**
     * Retrieve the size a integration step the trajectory method should do.
     * @return "const double &" stepSize
     */
    const double & getStepSize() const;

    /**
     * Set the start time.
     * @param "const double &" startTime
     */
    void setStartTime(const double & startTime);

    /**
     * Retrieve the start time.
     * @return "const double &" startTime
     */
    const double & getStartTime() const;

    /**
     * Set the end time.
     * @param "const double &" endTime
     */
    void setEndTime(const double & endTime);

    /**
     * Retrieve the end time.
     * @return "const double &" endTime
     */
    const double & getEndTime() const;

    /**
     * Set the initial state of the problem.
     * @param "const CState &" initialState
     */
    void setInitialState(const CState & initialState);

    /**
     * Set the initial state of the problem.
     * @param "const CStateX &" initialState
     */
    void setInitialState(const CStateX & initialState);

    /**
     * Retrieve the initial state of the problem.
     * @return "const CState &" pInitialState
     */
    const CState & getInitialState() const;

    /**
     * Set the end state of the problem.
     * @param "const CState *" pEndState
     */
    void setEndState(const CState * pEndState);

    /**
     * Set the end state of the problem.
     * @param "const CStateX *" pEndState
     */
    void setEndState(const CStateX * pEndState);

    /**
     * Retrieve the end state of the problem.
     * @return "const CState &" pEndState
     */
    const CState & getEndState() const;

    /**
     * Load a trajectory problem
     * @param "CReadConfig &" configBuffer
     * @param "CReadConfig::Mode mode (Default: CReadConfig::NEXT)
     */
    void load(CReadConfig & configBuffer,
              CReadConfig::Mode mode = CReadConfig::NEXT);

    /**
     * Save a trajectory problem
     * @param "CWriteConfig &" configBuffer
     */
    void save(CWriteConfig & configBuffer) const;

  private:
    /**
     * This function synchronizes step size and number
     */
    void sync();
  };

#endif // COPASI_CTrajectoryProblem
