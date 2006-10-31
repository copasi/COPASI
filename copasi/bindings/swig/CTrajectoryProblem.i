%{

#include "trajectory/CTrajectoryProblem.h"

%}


class CTrajectoryProblem : public CCopasiProblem
{
  public:
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
     * This methods must be called to elevate subgroups to
     * derived objects. The default implementation does nothing.
     * @return bool success
     */
    virtual bool elevateChildren();

    /**
     * Set the number of time steps the trajectory method should integrate.
     * @param "const unsigned C_INT32 &" stepNumber
     * @parem bool success
     */
    void setStepNumber(const unsigned C_INT32 & stepNumber);

    /**
     * Retrieve the number of time steps the trajectory method should integrate.
     * @return "const unsigned C_INT32 &" stepNumber
     */
    const unsigned C_INT32 & getStepNumber() const;

    /**
     * Set the size a integration step the trajectory method should do.
     * @param "const C_FLOAT64 &" stepSize
     * @parem bool success
     */
    void setStepSize(const C_FLOAT64 & stepSize);

    /**
     * Retrieve the size a integration step the trajectory method should do.
     * @return "const C_FLOAT64 &" stepSize
     */
    const C_FLOAT64 & getStepSize() const;

    /**
     * Set the end time.
     * @param "const C_FLOAT64 &" duration
     * @parem bool success
     */
    void setDuration(const C_FLOAT64 & duration);

    /**
     * Retrieve the end time.
     * @return "const C_FLOAT64 &" duration
     */
    const C_FLOAT64 & getDuration() const;

    /**
     * Set the end time.
     * @param "const C_FLOAT64 &" endTime
     */
    void setOutputStartTime(const C_FLOAT64 & endTime);

    /**
     * Retrieve the end time.
     * @return "const C_FLOAT64 &" endTime
     */
    const C_FLOAT64 & getOutputStartTime() const;

    /**
     *.
     */
    void setTimeSeriesRequested(bool flag);

    /**
     *
     */
    bool timeSeriesRequested() const;

};


