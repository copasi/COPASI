/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptTask.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: chlee $ 
   $Date: 2005/01/24 16:11:29 $
   End CVS Header */

/**
 * COptTask class.
 *
 * This class implements a optimization task which is comprised of a
 * of a problem and a method.
 *  
 */

#ifndef COPASI_COptTask
#define COPASI_COptTask

#include "utilities/CVector.h"

class COptProblem;
class COptMethod;
class CReport;
#include "utilities/CCopasiTask.h"

class COptTask : public CCopasiTask
  {
    //Attributes
  private:

    /**
     * Pointer to the output stream for reporting
     */
    std::ostream * mpOut;

    /**
     * Unique Key
     */
    std::string mKey;

    /**
     * for progress bar
     */ 
    //unsigned C_INT32 mProgress;

    /*
     Output value address
    */ 
    //   CVector<C_FLOAT64*>* pValueAddrMatrix;
    //Operations

  public:

    //    inline void setValueMatrixAddr(CVector<C_FLOAT64*>* pInputValueAddrMatrix)
    //    {
    //      mpProblem->setValueMatrixAddr(pInputValueAddrMatrix);
    //      pValueAddrMatrix = pInputValueAddrMatrix;
    //}

    /**
     * default constructor
     */
    COptTask(const CCopasiContainer * pParent = & RootContainer);

    /**
     * Copy constructor
     * @param const COptTask & src
     */ 
    //-COptTask(const COptTask & src);
    COptTask(const COptTask & src, const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    ~COptTask();

    /**
     * cleanup()
     */
    void cleanup();

    /**
     * Initilize 
     * @param ofstream & out
     */
    bool initialize(std::ostream * out);

    /**
        * Set the method type applied to solve the task
        * @param const CCopasiMethod::SubType & type
        * @return bool success
        */
    virtual bool setMethodType(const int & type);

    /**
     * Do the integration
     */
    virtual bool process();

    /**
     * Do the single tasks and the output
     */ 
    //bool processCallback();
  };
#endif // COPASI_COptTask
