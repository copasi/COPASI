/**
 *  File name: COptMethod.h
 *
 *  Programmer: Yongqun He 
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the interface (.h file) of the COptMethod class. 
 *           It contains the designed abstract interaction between a simulation
 *           subsystem and optimization algorithms. This base class defines
 *           methods by which the simulation subsystem accesses several 
 *           optimization algorithms.
 *  Note: This is an abstract class
 */

#ifndef COPASI_COptMethod
#define COPASI_COptMethod

#include <string>
#include <vector>

#include "utilities/CMethodParameterList.h"

class COptProblem;
template < class CType > class CVector;

// YOHE: this is an abstract class that contains many virtual functions
// without definitions
//
/** @dia:pos 36.4,4.15 */
class COptMethod : public CMethodParameterList
  {
  public:
    static const std::string TypeName[];

    // Attributes
  public:
    enum Type
    {
      RandomSearch = 0,
      RandomSearchMaster
    };

    //data member
  protected:
    /**
     *  The type of the method
     */
    COptMethod::Type mTypeEnum;

    /** @dia:route 0,2; h,36.4,4.15,33.95,4.15,23.0576 */
    COptProblem * mOptProblem;        // pointer to remote problem

    //These parameters are optimization parameters, not method (algm) parameters
    //they are for the model or calculation function.
    //Their memories are stored in COptProblem. Here are only pointers.
    CVector< C_FLOAT64 > * mParameters;    // pointer to parameters
    CVector< C_FLOAT64 > * mParameterMin;  // the minimum values of parameters
    CVector< C_FLOAT64 > * mParameterMax;  // the maximum values of parameters

    const bool mBounds;            // True if method accepts bounds on the parameters

    //rohan: modified 7/26

    // Implementation
  protected:

  public:
    /**
     * Create a optimization method.
     * Note: the returned object has to be released after use with delete
     */
    static COptMethod * createMethod(COptMethod::Type type
                                     = COptMethod::RandomSearch);

    /**
     * Default constructor
     * @param const bool & bounds (Default: false)
     */
    COptMethod(const bool & bounds = false);

    /**
     * Destructor
     */
    virtual ~COptMethod();

    /**
     * Copy constructor
     * @param const COptMethod & src
     */
    COptMethod(const COptMethod & src);

    /**
     * Execute the optimization algorithm calling simulation routine 
     * when needed. It is noted that this procedure can give feedback 
     * of its progress by the callback function set with SetCallback.
     */
    virtual C_INT32 optimise();

    /**
     * Returns True if this method is capable of handling adjustable parameter 
     * boundary constraints, False otherwise
     */
    bool isBounded(void);

    /**
     * Set the problem to be optmised
     * @param "COptProblem *" problem
     */
    void setProblem(COptProblem * problem);
  };

#include "CRandomSearch.h"
#include "CRandomSearchMaster.h"

#endif  // COPASI_COptMethod
