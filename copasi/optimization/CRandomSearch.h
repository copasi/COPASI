/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/CRandomSearch.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: chlee $ 
   $Date: 2005/06/14 18:17:00 $
   End CVS Header */

/**
 * CRandomSearch class
 */

#ifndef COPASI_CRandomSearch
#define COPASI_CRandomSearch

class CRandom;
//*** need to be added for definition
class COptProblem;
class COptMethod;

#include "utilities/CVector.h"

// YOHE: this is an abstract class that contains many virtual functions
// without definitions
//
/** @dia:pos 48.05,34.05 */
/** @dia:route COptMethod; v,46.9608,16.35,33,59.1652,34.05 */
class CRandomSearch : public COptMethod
  {
    friend COptMethod * COptMethod::createMethod(CCopasiMethod::SubType subType);

    // Operations
  private:
    /**
     * Default Constructor
     */
    CRandomSearch();

    /**
        * Initialize arrays and pointer.
        * @return bool success
        */
    virtual bool initialize();

    /**
        * Evaluate the fitness of one individual
        * @param const CVector< C_FLOAT64 > & individual
        * @return C_FLOAT64 fitness
        */
    C_FLOAT64 evaluate(const CVector< C_FLOAT64 > & individual);

    /**
        * Find the best individual at this generation
        * @return unsigned C_INT32 fittest
        */
    unsigned C_INT32 fittest();

    /**
        * number of iterations
        */
    unsigned C_INT32 mIterations;

    /**
        * a vector of the number of individuals.
        */ 
    //C_FLOAT64 mIndividual;
    CVector<C_FLOAT64> mIndividual;

    /**
        * array of values of objective function f/ individuals
        */ 
    //CVector< C_FLOAT64 > mValue;
    C_FLOAT64 mValue;

    /**
     * a pointer to the randomnumber generator.
     */
    CRandom * mpRandom;

    /**
     * *** Perhaps this is actually not needed ****number of parameters
     */
    unsigned C_INT32 mVariableSize;

    /**
        * type of random number generator
        */
    CRandom::Type Type;

    /**
        * Random Generator Seed
        */
    unsigned C_INT32 Seed;

    C_FLOAT64 mBestValue;
    //unsigned C_INT32 mBestValue
    unsigned C_INT32 mBestIndex;

  public:
    /**
     * Copy Constructor
     * @param const CRandomSearch & src
     */
    CRandomSearch(const CRandomSearch & src);

    /**
     * Destructor
     */
    virtual ~CRandomSearch();

    /**
     * Execute the optimization algorithm calling simulation routine 
     * when needed. It is noted that this procedure can give feedback 
     * of its progress by the callback function set with SetCallback.
     */
    virtual bool optimise();
  };

#endif  // COPASI_CRandomSearch
