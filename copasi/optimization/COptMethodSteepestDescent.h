/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodSteepestDescent.h,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:29:53 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_COptMethodSteepestDescent
#define COPASI_COptMethodSteepestDescent

class FDescent;

class COptMethodSteepestDescent: public COptMethod
  {
    friend COptMethod * COptMethod::createMethod(CCopasiMethod::SubType subType);

    // Operations
  private:

    /**
     * Default Constructor
     */
    COptMethodSteepestDescent(const CCopasiContainer * pParent = NULL);

    /**
     * Initialize arrays and pointer.
     * @return bool success
     */
    virtual bool initialize();

    /**
     * Cleanup arrays and pointers.
     * @return bool success
     */
    virtual bool cleanup();

    /**
     * Evaluate the objective function for the current parameters
     * @return const C_FLOAT64 & objectiveValue
     */
    const C_FLOAT64 & evaluate();

    /**
     * Calculate the gradient of the objective at the current parameters
     */
    void gradient();

    /**
     * Descent int the direction of the gradient with step x
     * and evaluate the objective function
     * @param const C_FLOAT64 & x
     * @return const C_FLOAT64 objectiveValue
     */
    const C_FLOAT64 descentLine(const C_FLOAT64 & x);

    /**
        * Initialize contained objects.
        */
    void initObjects();

  public:
    /**
     * Copy Constructor
     * @param const COptMethodSteepestDescent & src
     */
    COptMethodSteepestDescent(const COptMethodSteepestDescent& src,
                              const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~COptMethodSteepestDescent();

    /**
     * Execute the optimization algorithm calling simulation routine
     * when needed. It is noted that this procedure can give feedback
     * of its progress by the callback function set with SetCallback.
     */

    virtual bool optimise();

  private :

    // variables

    /**
     * The maximum number of iterations.
     */
    unsigned C_INT32 mIterations;

    /**
     * The tolerance
     */
    C_FLOAT64 mTolerance;   // length of steps taken

    /**
     * Indicates whether there the executions shall continue
     */
    bool mContinue;

    /**
     * The best value found so far.
     */
    C_FLOAT64 mBestValue;

    /**
        * array of values of objective function f/ individuals
        */
    C_FLOAT64 mValue;

    /**
     * number of parameters
     */
    unsigned C_INT32 mVariableSize;

    /**
     * A vector of parameters of the current individual
     */
    CVector < C_FLOAT64 > mIndividual;

    /**
     * The gradient vector for the objective function
     */
    CVector < C_FLOAT64 > mGradient;

    /**
     * Functor pointing to the descent method.
     */
    FDescent * mpDescent;

    /**
        * The current iteration
        */
    unsigned C_INT32 mCurrentIteration;
  };

#endif  // COPASI_COptMethodSteepestDescent
