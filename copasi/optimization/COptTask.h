/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptTask.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/04/19 11:43:41 $
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
#include "utilities/CCopasiTask.h"
#include "utilities/CProcessReport.h"

class COptProblem;
class COptMethod;
class CReport;

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

  class CallBack: public CProcessReport
      {
        // Attributes
      private:
        CProcessReport & mParentCallBack;

        // Operations
      public:
        CallBack(CProcessReport & parentCallBack);

        virtual ~CallBack();

        virtual unsigned C_INT32 addItem(const std::string & name,
                                         const CCopasiParameter::Type & type,
                                         const void * pValue,
                                         const void * pEndValue = NULL);

        virtual bool progress(const unsigned C_INT32 & index = C_INVALID_INDEX);

        virtual bool reset(const unsigned C_INT32 & index = C_INVALID_INDEX);

        virtual bool finish(const unsigned C_INT32 & index = C_INVALID_INDEX);

        bool setParentCallBack(CProcessReport * pCallBack);
      };

    /**
     * problem callback
     */
    CallBack *mpProblemCallBack;

    /**
     * method callback
     */
    CallBack * mpMethodCallBack;

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
     * Set the call back of the task
     * @param CProcessReport * pCallBack
     * @result bool succes
     */
    virtual bool setCallBack(CProcessReport * pCallBack);

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
