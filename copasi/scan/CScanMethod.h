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

class CScanProblem;
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
    void scan(unsigned C_INT32 i, bool nl);

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
