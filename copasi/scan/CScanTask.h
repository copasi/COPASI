/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/scan/CScanTask.h,v $
   $Revision: 1.22 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/12/14 17:10:27 $
   End CVS Header */

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
//#include "utilities/CWriteConfig.h"
#include "CScanMethod.h"
#include "utilities/CVector.h"
#include "CScanProblem.h"

class CScanMethod;
class CReport;

//-class CScanTask : public CCopasiContainer
class CScanTask : public CCopasiTask
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

    /*
     Output value address
    */
    CVector<C_FLOAT64*>* pValueAddrMatrix;
    //Operations

  public:

    inline void setValueMatrixAddr(CVector<C_FLOAT64*>* pInputValueAddrMatrix)
    {
      //      mpProblem->setValueMatrixAddr(pInputValueAddrMatrix);
      pValueAddrMatrix = pInputValueAddrMatrix;
    }

    /**
     * default constructor
     */
    CScanTask(const CCopasiContainer * pParent = & RootContainer);

    /**
     * Copy constructor
     * @param const CScanTask & src
     */ 
    //-CScanTask(const CScanTask & src);
    CScanTask(const CScanTask & src, const CCopasiContainer * pParent = NULL);

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
     * Do the integration
     */ 
    //-void process();
    virtual bool process();
  };
#endif // COPASI_CScanTask
