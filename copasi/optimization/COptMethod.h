/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethod.h,v $
   $Revision: 1.16 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/07/06 20:10:48 $
   End CVS Header */

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
 
 ****** Modified by Liang Xu
 */

#ifndef COPASI_COptMethod
#define COPASI_COptMethod

#include <string>

#include "utilities/CCopasiMethod.h"

class COptProblem;
class COptItem;
template < class CType > class CVector;

// YOHE: this is an abstract class that contains many virtual functions
// without definitions
//
/** @dia:pos 36.4,4.15 */
class COptMethod : public CCopasiMethod
  {
  public:
    static const std::string TypeName[];

    // Attributes
  public:

    //data member
  protected:
    /** @dia:route 0,2; h,36.4,4.15,33.95,4.15,23.0576 */
    COptProblem * mpOptProblem;        // pointer to remote problem

    const bool mBounds;            // True if method accepts bounds on the parameters

    /**
     * A vector of pointers to the update methods for the optimization parameters
     */
    const std::vector< UpdateMethod * > * mpSetCalculateVariable;

    /**
     * A vector of pointers to the optimization parameter
     */
    const std::vector< COptItem * > * mpOptItem;

    // Operations
  private:
    /**
     * Default constructor.
     */
    COptMethod();

  protected:
    /**
     *
     * @param CCopasiMethod::SubType subType
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COptMethod(CCopasiMethod::SubType subType,
               const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Create a optimization method.
     * Note: the returned object has to be released after use with delete
     */
    static COptMethod * createMethod(CCopasiMethod::SubType subType
                                     = CCopasiMethod::RandomSearch);

    /**
     * Copy constructor
     * @param const COptMethod & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COptMethod(const COptMethod & src,
               const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~COptMethod();

    /**
     * Execute the optimization algorithm calling simulation routine 
     * when needed. It is noted that this procedure can give feedback 
     * of its progress by the callback function set with SetCallback.
     * @ return success;
     */
    virtual bool optimise();

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

    /**
     * Initialize arrays and pointer.
     * @return bool success
     */
    virtual bool initialize();

  protected:
    /**
     * Cleanup arrays and pointers.
     * @return bool success
     */
    virtual bool cleanup();
  };

#include "CRandomSearch.h" 
// #include "CRandomSearchMaster.h"
// #include "COptMethodSA.h"
#include "COptMethodGA.h"
#include "COptMethodGASR.h" 
// #include "COptMethodEP2.h"
// #include "COptMethodHGASA.h"

#endif  // COPASI_COptMethod
