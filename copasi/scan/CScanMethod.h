/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/scan/CScanMethod.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:18:02 $
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

#include "utilities/CCopasiMethod.h"
#include "steadystate/CSteadyStateTask.h"
#include "trajectory/CTrajectoryTask.h"
#include "report/CReport.h"

class CScanProblem;
class CSteadyStateTask;
class CTrajectory;

class CScanMethod : public CCopasiMethod
  {
  protected:
    /**
     *  A pointer to the trajectory problem.
     */
    CScanProblem * scanProblem;

    /**
     * A pointer to the random number generator
     */
    CRandom * mpRandomGenerator;

    /**
     *
     */
    unsigned C_INT32 mVariableSize;

    /**
     *
     */
    C_FLOAT64 * mpVariables;

    // Operations
  private:
    /**
     * Default constructor.
     */
    CScanMethod();

  protected:
    /**
     * Specific constructor.
     * @param CCopasiMethod::SubType subType 
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CScanMethod(CCopasiMethod::SubType subType,
                const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Create a trajectory method.
     * Note: the returned object has to be released after use with delete
     */

    static CScanMethod * createMethod();

    /**
     *  Copy constructor.
     *  @param "const CTrajectoryMethod &" src
     */
    CScanMethod(const CScanMethod & src,
                const CCopasiContainer * pParent = NULL);

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

  private:
    /**
     *  Set the value of the scan parameter based on the distribution
     *  @param unsigned C_INT32 i where to start in the distribution
     *  @param unsigned C_INT32 first first parameter in the set of Master/Slaves
     *  @param unsigned C_INT32 last last parameter in the set of Master/Slaves
     */
    void setScanParameterValue(unsigned C_INT32 i,
                               unsigned C_INT32 first,
                               unsigned C_INT32 last);
  };

#endif // COPASI_CTrajectoryMethod
