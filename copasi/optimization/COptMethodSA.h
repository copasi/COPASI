/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodSA.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/16 16:25:25 $
   End CVS Header */

/**
 * COptMethodSA class
 */

#ifndef COPASI_COptMethodSA
#define COPASI_COptMethodSA
#include "utilities/CVector.h"

class CRandom;

// this is an abstract class that contains many virtual functions
// without definitions
//
/** @dia:pos 48.05,34.05 */
/** @dia:route COptMethod; v,46.9608,16.35,33,59.1652,34.05 */

class COptMethodSA : public COptMethod
  {
    friend COptMethod * COptMethod::createMethod(COptMethod::Type type);

    // Operations
  private:
    /**
     * Default Constructor
     */
    COptMethodSA();

  public:
    /**
     * Copy Constructor
     * @param const COptMethodSA & src
     */
    COptMethodSA(const COptMethodSA & src);

    /**
     * Destructor
     */
    virtual ~COptMethodSA();

    /**
     * Execute the optimization algorithm calling simulation routine 
     * when needed. It is noted that this procedure can give feedback 
     * of its progress by the callback function set with SetCallback.
     */
    virtual C_INT32 optimise();
  };

#endif  // COPASI_COptMethodSA
