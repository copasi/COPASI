/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodStatistics.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/08/25 22:19:26 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * COptMethodStatistics class
 */

#ifndef COPASI_COptMethodStatistics
#define COPASI_COptMethodStatistics

//class CRandom;
//*** need to be added for definition
class COptProblem;
class COptMethod;

#include "randomGenerator/CRandom.h"
#include "utilities/CVector.h"

// YOHE: this is an abstract class that contains many virtual functions
// without definitions
//
/** @dia:pos 48.05,34.05 */
/** @dia:route COptMethod; v,46.9608,16.35,33,59.1652,34.05 */
class COptMethodStatistics : public COptMethod
  {
    friend COptMethod * COptMethod::createMethod(CCopasiMethod::SubType subType);

    // Operations
  private:
    /**
     * Default Constructor
     */
    COptMethodStatistics();

    /**
        * Initialize arrays and pointer.
        * @return bool success
        */
    virtual bool initialize();

    /**
     * Evaluate the fitness of one individual
     * @param const CVector< C_FLOAT64 > & individual
     * @return bool continue
     */
    bool evaluate(const CVector< C_FLOAT64 > & individual);

    /**
     * a vector of the number of individuals.
     */
    CVector<C_FLOAT64> mIndividual;

    /**
     * array of values of objective function f/ individuals
     */
    C_FLOAT64 mValue;

    /**
     * *** Perhaps this is actually not needed ****number of parameters
     */
    unsigned C_INT32 mVariableSize;

    /**
     * The best value found so far.
     */
    C_FLOAT64 mBestValue;

  public:
    /**
     * Copy Constructor
     * @param const COptMethodStatistics & src
     */
    COptMethodStatistics(const COptMethodStatistics & src);

    /**
     * Destructor
     */
    virtual ~COptMethodStatistics();

    /**
     * Execute the optimization algorithm calling simulation routine
     * when needed. It is noted that this procedure can give feedback
     * of its progress by the callback function set with SetCallback.
     */
    virtual bool optimise();
  };

#endif  // COPASI_COptMethodStatistics
