/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodSteepestDescent.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2005/07/20 05:10:36 $
   End CVS Header */

#ifndef COPASI_COptMethodSteepestDescent
#define COPASI_COptMethodSteepestDescent

class COptMethodSteepestDescent: public COptMethod
  {
    friend COptMethod * COptMethod::createMethod(CCopasiMethod::SubType subType);

    // Operations
  private:

    /**
     * Default Constructor
     */
    COptMethodSteepestDescent(const CCopasiContainer * pParent = NULL);

    /**
        * Initialize arrays and pointer.
        * @return bool success
        */
    virtual bool initialize();

    /**
        * Cleanup arrays and pointers.
        * @return bool success
        */
    virtual bool cleanup();

  public:
    /**
     * Copy Constructor
     * @param const COptMethodEP2 & src
     */
    COptMethodSteepestDescent(const COptMethodSteepestDescent& src,
                              const CCopasiContainer * pParent = NULL);

    /**
        * Set the call back of the problem
        * @param CProcessReport * pCallBack
        * @result bool succes
        */
    virtual bool setCallBack(CProcessReport * pCallBack);

    /**
     * Destructor
     */
    virtual ~COptMethodSteepestDescent();

    /**
     * Execute the optimization algorithm calling simulation routine 
     * when needed. It is noted that this procedure can give feedback 
     * of its progress by the callback function set with SetCallback.
     */

    virtual bool optimise();

  private :

    // variables
    int debug;     // 1 for output
    int maxiter;    // maximum number of iterations
    double tolerance;   // length of steps taken
    double * candp, candx;
    double * dsd;

    // calculate the gradient of an objective function
    void gradient();

    int FMinBrent(double a,         /* Left border      */
                  double b,                /* Right border      */
                  double *min,             /* Location of minimum    */
                  double *fmin,            /* Value of minimum     */
                  double tol,              /* Acceptable tolerance    */
                  int maxiter);          /* Maximum number of iterations  */

    double DescentLine(double x);
  };

#endif  // COPASI_COptMethodSteepestDescent
