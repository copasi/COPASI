/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/scan/CScanMethod.h,v $
   $Revision: 1.16 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:32:26 $
   End CVS Header */

/**
 *  CScanMethod class.
 *  This class describes the method for doing the Scan.
 *
 *  Created for Copasi by Rohan Luktuke 2002
 */

#ifndef COPASI_CScanMethod
#define COPASI_CScanMethod

#include <string>

#include "utilities/CMethodParameterList.h"
#include "steadystate/CSteadyStateTask.h"
#include "trajectory/CTrajectoryTask.h"
#include "report/CReport.h"

class CScanProblem;
class CSteadyStateTask;
class CTrajectory;

class CScanMethod
  {
  protected:
    /**
     *  A pointer to the trajectory problem.
     */
    CScanProblem * scanProblem;
    // Operations
  protected:
    /**
     *  Default constructor.
     */
    CScanMethod();

  public:

    /**
       * calculate function for ScanMethod
       */

    C_FLOAT64 simulate();

    /**
     * Create a trajectory method.
     * Note: the returned object has to be released after use with delete
     */

    static CScanMethod * createMethod();

    /**
     *  Copy constructor.
     *  @param "const CTrajectoryMethod &" src
     */
    CScanMethod(const CScanMethod & src);

    /**
     *  Destructor.
     */
    ~CScanMethod();

    /**
     *  Set a pointer to the problem.
     *  This method is used by CTrajectory
     *  @param "CTrajectoryProblem *" problem
     */
    void setProblem(CScanProblem * problem);

    /**
     *  The main scan method.
     */
    void scan(unsigned C_INT32 s, bool C_UNUSED(nl), void (*pCallback)(CReport *), CReport *pReport);
  };

#endif // COPASI_CTrajectoryMethod
