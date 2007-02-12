// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/lyap/CLyapWolfMethod.h,v $
//   $Revision: 1.7 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/02/12 14:27:06 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CLyapWolfMethod
#define COPASI_CLyapWolfMethod

#include <sstream>
#include "utilities/CVector.h"
#include "utilities/CMatrix.h"

#include "odepack++/CLSODA.h"

class CModel;
class CState;
class CLyapTask;

class CLyapWolfMethod : public CLyapMethod
  {
    friend CLyapMethod *
    CLyapMethod::createMethod(CCopasiMethod::SubType subType);

  public:
    struct Data
      {
        C_INT dim;
        CLyapWolfMethod * pMethod;
      };

  public:
    /**
     *  handles the complete calculation
     */
    bool calculate();

    // Attributes
  private:
    /**
     *  A pointer to the current state in complete model view.
     */
    CState * mpState;

    /**
     * mData.dim is the dimension of the ODE system.
     * mData.pMethod contains CLsodaMethod * this to be used in the static method EvalF
     */
    Data mData;

    /**
     *  Number of variables in the model
     */
    unsigned C_INT32 mSystemSize;

    /**
     *  Number of exponents to calculate
     */
    unsigned C_INT32 mNumExp;

    bool mDoDivergence;

    CMatrix<C_FLOAT64> mJacobian;

    //CVector<C_FLOAT64> mLocalExponents;
    CVector<C_FLOAT64> mSumExponents;
    //CVector<C_FLOAT64> mExponents;
    CVector<C_FLOAT64> mNorms;

    /**
     *  integrated divergence
     */
    C_FLOAT64 mSumDivergence;

    /**
     *  Pointer to the array with left hand side values.
     */
    //C_FLOAT64 * mY;

    /**
     * Vector containig the derivatives after calling eval
     */
    //CVector< C_FLOAT64 > mYdot;

    /**
     *  Current time.
     */
    C_FLOAT64 mTime;
    //C_FLOAT64 * mpCurrentTime;

    /**
     *  Requested end time.
     */
    C_FLOAT64 mEndt;

    /**
     *  LSODA state.
     */
    C_INT mLsodaStatus;

    /**
     *
     */
    bool mReducedModel;

    /**
     *  Relative tolerance.
     */
    C_FLOAT64 mRtol;

    /**
     *
     */
    bool mDefaultAtol;

    /**
     *  Absolute tolerance.
     */
    //C_FLOAT64 mAtol;
    CVector<C_FLOAT64> mAtol;

    /**
     *  Maximum order for BDF method.
     */
    //    C_INT32 mBDF;

    /**
     *  Maximum order for Adams method.
     */
    //    C_INT32 mAdams;

    /**
     *  Maximum number of steps for one call of lsoda.
     */
    //    C_INT32 mMaxSteps;

    /**
     *
     */
    std::ostringstream mErrorMsg;

    CLSODA mLSODA;
    C_INT mState;
    CVector< C_FLOAT64 > mDWork;
    CVector< C_INT > mIWork;

    /**
     * the vector that contains the extended system
     */
    CVector< C_FLOAT64 > mVariables;

    C_INT mJType;

    CLyapTask* mpTask;

    // Operations
  private:
    /**
     * Default constructor.
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CLyapWolfMethod(const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Copy constructor.
     * @param "const CLsodaMethod &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CLyapWolfMethod(const CLyapWolfMethod & src,
                    const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CLyapWolfMethod();

    /**
     *  This instructs the method to calculate a time step of deltaT
     *  starting with the current state, i.e., the result of the previous
     *  step.
     *  The new state (after deltaT) is expected in the current state.
     *  The return value is the actual timestep taken.
     *  @param "const double &" deltaT
     */
    virtual void step(const double & deltaT);

    /**
     *  This instructs the method to prepare for integration
     *  starting with the initialState given.
     *  @param "const CState *" initialState
     */
    virtual void start(/*const CState * initialState*/);

    /**
     * Calculate the default absolute tolerance
     * @param const CModel * pModel
     * @return C_FLOAT64 defaultAtol
     */
    C_FLOAT64 getDefaultAtol(const CModel * pModel) const;

    static void EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);

    /**
     *  This evaluates the derivatives for the complete model
     */
    void evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);

    /**
     * Check if the method is suitable for this problem
     * @return bool suitability of the method
     */
    virtual bool isValidProblem(const CCopasiProblem * pProblem);

  private:
    /**
     * Intialize the method parameter
     */
    void initializeParameter();

    void orthonormalize();

    static C_FLOAT64 norm(const C_FLOAT64* dbl1, const C_FLOAT64 * dbl2);
    static void scalarmult(C_FLOAT64* dbl1, const C_FLOAT64* dbl2, const C_FLOAT64 & f);
    static C_FLOAT64 product(const C_FLOAT64* dbl1, const C_FLOAT64* dbl1End,
                             const C_FLOAT64* dbl2);
    static void add(C_FLOAT64* dbl1, const C_FLOAT64* dbl1End,
                    const C_FLOAT64 & f, const C_FLOAT64* dbl2);
  };
#endif // COPASI_CLsodaMethod
