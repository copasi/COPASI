// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tssanalysis/CTSSAMethod.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: isurovts $
//   $Date: 2007/12/21 11:43:59 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CTSSAMethod class.
 *  This class describes the interface to all time scale separation analysis methods.
 *  The variaous method like ILDM or CSP have to be derived from
 *  this class.
 *
 */

#ifndef COPASI_CTSSAMethod
#define COPASI_CTSSAMethod

#include <string>

#include "utilities/CCopasiMethod.h"
#include "utilities/CVector.h"
#include "odepack++/CLSODA.h"
#include "utilities/CMatrix.h"

#include "utilities/CAnnotatedMatrix.h"
#include "report/CCopasiObjectReference.h"

class CTSSAProblem;
class CModel;
class CState;

class CTSSAMethod : public CCopasiMethod
  {
  protected:
    /**
     *  A pointer to the current state. This is set from outside
     *  with the setState() method and never changed anywhere else.
     *  It´s used to report the results
     *  to the calling TSSATask
     */
    CState * mpCurrentState;

    /**
     *  A pointer to the time scale separation analysis problem.
     */
    CTSSAProblem * mpProblem;

    // Operations
  private:
    /**
     * Default constructor.
     */
    CTSSAMethod();

  protected:
    /**
     * Default constructor.
     * @param const CCopasiMethod::SubType & subType
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CTSSAMethod(const CCopasiMethod::SubType & subType,
                const CCopasiContainer * pParent = NULL);

  public:

    /**
     * Create a time scale separation analysis method for a special problem.
     * Note: the returned object has to be released after use with delete
     * a problem is also passed so that the method has a chance to choose an
     * appropriate simulation method.
     */
    static CTSSAMethod *
    createTSSAMethod(CCopasiMethod::SubType subType
                     = CCopasiMethod::unset,
                     CTSSAProblem * pProblem = NULL);

    /**
     * Copy constructor.
     * @param "const CTSSAMethod &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CTSSAMethod(const CTSSAMethod & src,
                const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CTSSAMethod();

    /**
     *  Set a pointer to the current state.
     *  This method is used by CTSSATask::process()
     *  The results of the simulation are passed via this CState variable
     *  @param "CState *" currentState
     */
    void setCurrentState(CState * currentState);

    /**
     *  Set a pointer to the problem.
     *  This method is used by CTSSA
     *  @param "CTSSAProblem *" problem
     */
    void setProblem(CTSSAProblem * problem);

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
    virtual void start(const CState * initialState);

    /**
     * Check if the method is suitable for this problem
     * @return bool suitability of the method
     */
    virtual bool isValidProblem(const CCopasiProblem * pProblem);

    /************ The following concerns the both ILDM Methods *******************************/

  protected:

    struct Data
      {
        C_INT dim;
        CTSSAMethod * pMethod;
      };

    /**
     *  A pointer to the current state in complete model view.
     */
    CState * mpState;

    /**
     * mData.dim is the dimension of the ODE system.
     */
    Data mData;

    /**
     *  Pointer to the array with left hand side values.
     */
    C_FLOAT64 * mY;

    /**
     * Vector containig the derivatives after calling eval
     */
    CVector< C_FLOAT64 > mYdot;

    /**
     *
    */
    CVector< C_FLOAT64 > mY_initial;

    /**
     *  Current time.
     */
    C_FLOAT64 mTime;

    /**
     *  Jacobian matrix
     */
    CMatrix <C_FLOAT64> mJacobian;

    /**
     *  Jacobian matrix at initial point
     */
    CMatrix <C_FLOAT64> mJacobian_initial;

    /**
     *
     */
    CMatrix <C_FLOAT64> mQ;

    /**
     *
     */
    CMatrix <C_FLOAT64> mR;

    /**
     *
     */
    CMatrix <C_FLOAT64> mTd;

    /**
     *
     */
    CMatrix <C_FLOAT64> mTdInverse;

    /**
     *
     */
    CMatrix <C_FLOAT64> mQz;

    /**
     *
     */
    CMatrix <C_FLOAT64> mTd_save;
    /**
         *
         */
    CMatrix <C_FLOAT64> mTdInverse_save;

    /**
     *
     */

    CVector<C_FLOAT64> mCfast;

    /**
      *
      */

    CVector<C_FLOAT64> mY_cons;

    /**
     *
     */
    CMatrix<C_FLOAT64> mVslow;

    /**
     *
     */
    CMatrix<C_FLOAT64> mVslow_metab;

    /**
     *
     */
    CVector<C_FLOAT64> mVslow_space;

    /**
       *
       */
    CVector<C_FLOAT64> mVfast_space;

    /**
     *
     */
    C_INT mSlow;

    /**
     *  LSODA state.
     */
    C_INT mLsodaStatus;

    /**
     * Whether to use the reduced model
     */
    bool mReducedModel;

    /**
     * Relative tolerance.
     */
    C_FLOAT64 mRtol;

    /**
     * A vector of absolute tolerances.
     */
    CVector< C_FLOAT64 > mAtol;

    /**
     * Stream to capture LSODA error messages
     */
    std::ostringstream mErrorMsg;

    /**
     * The LSODA integrator
     */
    CLSODA mLSODA;

    /**
     * The state of the integrator
     */
    C_INT mState;

    /**
     * LSODA C_FLOAT64 work area
     */
    CVector< C_FLOAT64 > mDWork;

    /**
     * LSODA C_INT work area
     */
    CVector< C_INT > mIWork;

    /**
     * The way LSODA calculates the jacobian
     */
    C_INT mJType;

    /**
     * A pointer to the model
     */
    CModel * mpModel;

    /**
     *  Tolerance for Deuflhard criterium
     */
    C_FLOAT64 mDtol;

    /**
     *
     */
    C_FLOAT64 mEPS;

    // Operations

    /**
     * Intialize the method parameter
     */

    void initializeILDMParameter();

    /**
     * This methods must be called to elevate subgroups to
     * derived objects. The default implementation does nothing.
     * @return bool success
     */
    bool elevateChildren();

    /**
     *  This instructs the method to calculate a time step of deltaT
     *  starting with the current state, i.e., the result of the previous
     *  step.
     *  The new state (after deltaT) is expected in the current state.
     *  The return value is the actual timestep taken.
     *  @param "const double &" deltaT
     **/

    /**
     **/
    void integrationStep(const double & deltaT);

    /**
     *  This instructs the method to prepare for integration
     *  starting with the initialState given.
     *  @param "const CState *" initialState
     */
    void ILDMstart(const CState * initialState);

    /**
     * Calculate the individual absolute tolerance
     */
    void initializeAtol();

    static void EvalF(const C_INT * n, const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);

    /**
     *  This evaluates the derivatives
     */
    void evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);

    /**
     *
     */
    void schur(C_INT &info);

    /**
     *
     */
    void sylvester (C_INT slow, C_INT & info);

    /**
     *
     **/
    void map_index(C_FLOAT64 *eval_r, C_INT *index, const C_INT & dim);

    /**
     *
     **/
    void update_nid(C_INT *index, C_INT *nid, const C_INT & dim);

    /**
     *
     **/
    void update_pid(C_INT *index, C_INT *pid, const C_INT & dim);

    /**
     *
     **/
    void calculateDerivativesX(C_FLOAT64 * X1, C_FLOAT64 * Y1);

    /**
      * This is not very elegant solution. But I don't know the better one.
     **/

    //    void calculateNextJacobian(const double & deltaT);

    /**
     *
     **/
    void mat_anal_mod(C_INT & slow);

    /**
     *
     **/
    void mat_anal_metab(C_INT & slow);

    /**
     *
     **/
    void mat_anal_mod_space(C_INT & slow);
    void mat_anal_fast_space(C_INT & slow);

    /**
         *
       **/
    double orthog(C_INT & number1, C_INT & number2);

    /**
     *vectors contain whole data for all calculationsteps
     **/
    std::vector< CMatrix<C_FLOAT64> > mVec_mVslow;
    std::vector< CMatrix<C_FLOAT64> > mVec_mVslowMetab;
    std::vector< CVector<C_FLOAT64> > mVec_mVslowSpace;
    std::vector< CVector<C_FLOAT64> > mVec_mVfastSpace;
    std::vector< CVector<C_FLOAT64> > mVec_TimeScale;
    std::vector< int > mVec_SlowModes;
    std::vector< C_FLOAT64 > mCurrentTime;

    /**
     *CArraAnnotations for every ILDM-tab in the CQTSSAResultSubWidget
     **/
    CArrayAnnotation* pVslowPrintAnn;
    CArrayAnnotation* pVslowMetabPrintAnn;
    CArrayAnnotation* pVslowSpacePrintAnn;
    CArrayAnnotation* pVfastSpacePrintAnn;

    /**
    *required for creation of above listed CArrayAnnotation
    **/
    CArrayAnnotation* pTmp1;
    CArrayAnnotation* pTmp2;
    CArrayAnnotation* pTmp3;
    CArrayAnnotation* pTmp4;

    /**
    *input for every CArraAnnotations
    *contain data for single stepcalculation
    **/
    CMatrix<C_FLOAT64> mVslowPrint;
    CMatrix<C_FLOAT64> mVslowSpacePrint;
    CMatrix<C_FLOAT64> mVfastSpacePrint;
    CMatrix<C_FLOAT64> mVslowMetabPrint;

  public:

    /**
    * return CArrayAnnotation for visualization in ILDM-tab
    * in the CQTSSAResultSubWidget
    **/
    const CArrayAnnotation* getVslowPrintAnn() const
      {return pVslowPrintAnn;}
    const CArrayAnnotation* getVslowSpacePrintAnn() const
      {return pVslowSpacePrintAnn;}
    const CArrayAnnotation* getVfastSpacePrintAnn() const
      {return pVfastSpacePrintAnn;}
    const CArrayAnnotation* getVslowMetabPrintAnn() const
      {return pVslowMetabPrintAnn;}

    /**
    * upgrade all vectors with values from actually calculalion for current step
    **/
    void setVectors(int slowMode);

    /**
    *return required time-value from timevector
    **/
    C_FLOAT64 returnCurrentTime(int step){return mCurrentTime[step];};

    /**
    * create the CArraAnnotations for every ILDM-tab in the CQTSSAResultSubWidget
    * input for each CArraAnnotations is a seperate CMatrix
    **/
    void createAnnotationsM();

    /**
    * set the every CArrayAnnotation for the requested step
    * set the desription of CArayAnnotation for both dimensions
    **/
    void setAnnotationM(int step);

    /**
    * empty every vector to be able to fill them with new values for a new calculation
      * also nullify the step counter
      **/
    void emptyVectors();

    /**
      * stepcounter
      **/
    int mCurrentStep;
  };

#endif // COPASI_CTSSAMethod
