/**
 * CTrajectoryTask class.
 *
 * This class implements a trajectory task which is comprised of a
 * of a problem and a method. Additionally calls to the reporting 
 * methods are done when initialized.
 *  
 * Created for Copasi by Stefan Hoops 2002
 */

#ifndef COPASI_CTrajectoryTask
#define COPASI_CTrajectoryTask

#include "utilities/CReadConfig.h"
#include "utilities/CWriteConfig.h"
#include "CTrajectoryMethod.h"

class CTrajectoryProblem;
//class CTrajectoryMethod;
class CState;
class COutputEvent;

class CTrajectoryTask
  {
    //Attributes
  private:

    /**
     * A pointer to the problem to be integrated.
     */
    CTrajectoryProblem *mpProblem;

    /**
     * A pointer to the method choosen for the integration.
     */
    CTrajectoryMethod * mpMethod;

    /**
     * Flag indicating whether the task shall be executed by CopasiSE
     */
    bool mRequested;

    /**
     * A pointer to the current state of the integration.
     */
    CState * mpState;

    /**
     * Initial Output Event
     */
    COutputEvent *mpOutInit;

    /**
     * Any Point Output Event from beginning to end
     */
    COutputEvent *mpOutPoint;

    /**
     * End Phase Output Event
     */
    COutputEvent *mpOutEnd;

    /**
     * Pointer to the output stream for reporting
     */
    std::ofstream * mpOut;

    /**
     * Produces the output. time=0 for init, time=1 for point, time=2 for end.
     */
    void printOutput(const C_INT32 time);

    friend CStochMethod *
    CStochMethod::createStochMethod(CTrajectoryProblem * pProblem);

  public:
    /**
     * default constructor
     */
    CTrajectoryTask();

    /**
     * Copy constructor
     * @param const CTrajectoryTask & src
     */
    CTrajectoryTask(const CTrajectoryTask & src);

    /**
     * special constructor. Allows definition of a Trajectory task without loading one
     */
    CTrajectoryTask(CTrajectoryProblem * pProblem,
                    CTrajectoryMethod::Type type = CTrajectoryMethod::deterministic);

    /**
     * special constructor. Allows definition of a Trajectory task
     * and a problem without loading one.
     *  @param "CModel *" pmodel
     *  @param "C_FLOAT64" starttime
     *  @param "C_FLOAT64" endtime
     *  @param "unsigned C_INT32" stepnumber : number of steps
     *  @param "CTrajectoryMethod::Type" type : type of the method that will be created
     */
    CTrajectoryTask(CModel * pModel,
                    C_FLOAT64 starttime, C_FLOAT64 endtime,
                    unsigned C_INT32 stepnumber,
                    CTrajectoryMethod::Type type = CTrajectoryMethod::deterministic);

    /**
     * Destructor
     */
    ~CTrajectoryTask();

    /**
     * Initilize the reporting feature
     * @param ofstream & out
     */
    void initializeReporting(std::ofstream & out);

    /**
     * Loads parameters for this solver with data coming from a
     * CReadConfig object. (CReadConfig object reads an input stream)
     * @param configbuffer reference to a CReadConfig object.
     */
    void load(CReadConfig & configBuffer);

    /**
     * Saves the parameters of the solver to a CWriteConfig object.
     * (Which usually has a file attached but may also have socket)
     * @param configbuffer reference to a CWriteConfig object.
     */
    void save(CWriteConfig & configBuffer);

    /**
     * Retrieve the probel to be integrated.
     * @return CTrajectoryProblem * pProblem
     */
    CTrajectoryProblem * getProblem();

    /**
     * Set the problem to be integrated.
     * @param CTrajectoryProblem * pProblem
     */
    void setProblem(CTrajectoryProblem * pProblem);

    /**
     * Retrieve the method choosen for the integration.
     * @return CTrajectoryMethod * pMethod
     */
    CTrajectoryMethod * getMethod();

    /**
     * Set the method to be used for the integration.
     * @param CTrajectoryMethod * pMethod
     */
    void setMethod(CTrajectoryMethod * pMethod);

    /**
     * Set wheter the execution of the task is requested.
     * @param const bool & execute
     */
    void setRequested(const bool & requested);

    /**
     * Retrieve whether the execution of the task is requested
     * @return bool isRequested
     */
    bool isRequested() const;

    /**
     * Retrieves a pointer to current state of the integration.
     * @return CState * pState
     */
    CState * getState();

    /**
     * Do the integration
     */
    void process();

  private:
    /**
     * cleanup()
     */
    void cleanup();
  };
#endif // COPASI_CTrajectoryTask
