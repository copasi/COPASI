/**
 * CScanTask class.
 *
 * This class implements a scan task which is comprised of a
 * of a problem and a method.
 *  
 */

#ifndef COPASI_CScanTask
#define COPASI_CScanTask

#include "utilities/CReadConfig.h"
#include "utilities/CWriteConfig.h"
#include "CScanMethod.h"
#include "utilities/CVector.h"
#include "CScanProblem.h"

class CScanMethod;
class COutputEvent;
class CReport;

class CScanTask : public CCopasiContainer
  {
    //Attributes
  private:

    static CReport * mReport;
    /**
     * Flag indicating whether the task shall be executed by CopasiSE
     */
    bool mRequested;

    static void call_back_report();

    /**
     * A pointer to the problem to be integrated.
     */
    CScanProblem *mpProblem;

    /**
     * A pointer to the method choosen for the integration.
     */
    CScanMethod * mpMethod;

    /**
     * Pointer to the output stream for reporting
     */
    std::ostream * mpOut;

    /**
     * End Phase Output Event
     */
    COutputEvent *mpOutEnd;

    /**
        * Unique Key
        */
    std::string mKey;

    /*
     Output value address
    */
    CVector<C_FLOAT64*>* pValueAddrMatrix;
    //Operations

  public:

    inline void setValueMatrixAddr(CVector<C_FLOAT64*>* pInputValueAddrMatrix)
    {
      mpProblem->setValueMatrixAddr(pInputValueAddrMatrix);
      pValueAddrMatrix = pInputValueAddrMatrix;
    }

    inline CReport* getReport() {return mReport;};

    inline std::string getKey() const {return mKey;}
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
    void initializeReporting(std::ostream & out);

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
#endif // COPASI_CScanTask
