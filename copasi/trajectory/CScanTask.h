/**
 * CScanTask class.
 *
 * This class implements a scan task which is comprised of a
 * of a problem and a method.
 *  
 */

#include "utilities/CReadConfig.h"
#include "utilities/CWriteConfig.h"

class CScanProblem;
class CScanMethod;

class CScanTask
  {
    //Attributes
  private:

    /**
     * A pointer to the problem to be integrated.
     */
    CScanProblem *scanProblem;

    /**
     * A pointer to the method choosen for the integration.
     */
    CScanMethod * scanMethod;

    /**
     * Pointer to the output stream for reporting
     */
    std::ofstream * mpOut;

    //Operations
  public:
    /**
     * default constructor
     */
    CScanTask();

    /**
     * Copy constructor
     * @param const CScanTask & src
     */
    CScanTask(const CScanTask & src);

    /**
     * Destructor
     */
    ~CScanTask();

    /**
     * cleanup()
     */
    void cleanup();

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
    CScanProblem * getProblem();

    /**
     * Set the problem to be integrated.
     * @param CTrajectoryProblem * pProblem
     */
    void setProblem(CScanProblem * pProblem);

    /**
     * Retrieve the method choosen for the integration.
     * @return CTrajectoryMethod * pMethod
     */
    CScanMethod * getMethod();

    /**
     * Set the method to be used for the integration.
     * @param CTrajectoryMethod * pMethod
     */
    void setMethod(CScanMethod * pMethod);

    /**
     * Do the integration
     */
    void process();
  };
#endif // COPASI_CTrajectoryTask
