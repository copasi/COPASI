// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tssanalysis/CILDMMethod.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/10/29 10:28:57 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CILDMMethod
#define COPASI_CILDMMethod

#include <sstream>
#include "utilities/CVector.h"
#include "utilities/CMatrix.h"

#include "CTSSAMethod.h"

#include "odepack++/CLSODA.h"

#include "utilities/CMatrix.h"
#include "utilities/CAnnotatedMatrix.h"

class CModel;
class CState;

class CILDMMethod : public CTSSAMethod
  {
    friend CTSSAMethod *
    CTSSAMethod::createTSSAMethod(CCopasiMethod::SubType subType,
                                  CTSSAProblem * pProblem);

  public:
    struct Data
      {
        C_INT dim;
        CILDMMethod * pMethod;
      };

    // Attributes
  private:
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
  private:
    /**
     * Default constructor.
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CILDMMethod(const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Copy constructor.
     * @param "const CILDMMethod &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CILDMMethod(const CILDMMethod & src,
                const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CILDMMethod();

    /**
     * This methods must be called to elevate subgroups to
     * derived objects. The default implementation does nothing.
     * @return bool success
     */
    virtual bool elevateChildren();

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
     **/
    virtual void integrationStep(const double & deltaT);

    /**
     *  This instructs the method to prepare for integration
     *  starting with the initialState given.
     *  @param "const CState *" initialState
     */
    virtual void start(const CState * initialState);

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
     */
    void evalsort(C_FLOAT64 * reval, const C_INT & dim_x);

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
     *
     **/
    void newton(C_FLOAT64 *ys, C_INT & slow, C_INT & info);
    //  void newton_new(CVector<C_FLOAT64> *ys, CVector< C_INT> & index_metab, C_INT & slow, C_INT & info);

    /**
      * This is not very elegant solution. But I don't know the better one.
     **/

    void calculateNextJacobian(const double & deltaT);

    /**
     *
     **/

    void newton_for_timestep(C_INT metabolite_number, C_FLOAT64 &y_consistent, C_INT & info);

    /**
     *
     **/

    void deuflhard(C_INT & slow, C_INT & info);

    /**
       *
       **/

    void transformation_norm(C_INT & slow, C_INT & info);

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
    std::vector< CVector<C_FLOAT64> > mVec_TimeScale;
    std::vector< int > mVec_SlowModes;
    std::vector< C_FLOAT64 > mCurrentTime;

    /**
    *return required time-value from timevector
    **/
    C_FLOAT64 returnCurrentTime(int step){return mCurrentTime[step];};

    /**
     *CArraAnnotations for every ILDM-tab in the CQTSSAResultSubWidget
     **/
    CArrayAnnotation* pVslowPrintAnn;
    CArrayAnnotation* pVslowSpacePrintAnn;
    CArrayAnnotation* pVslowMetabPrintAnn;

    /**
    *required for creation of above listed CArrayAnnotation
    **/
    CArrayAnnotation* pTmp1;
    CArrayAnnotation* pTmp2;
    CArrayAnnotation* pTmp3;

    /**
    *input for every CArraAnnotations
    *contain data for single stepcalculation
    **/
    CMatrix<C_FLOAT64> mVslowPrint;
    CMatrix<C_FLOAT64> mVslowSpacePrint;
    CMatrix<C_FLOAT64> mVslowMetabPrint;

    /**
    * return CArrayAnnotation for visualization in ILDM-tab
    * in the CQTSSAResultSubWidget
    **/
    const CArrayAnnotation* getVslowPrintAnn() const
      {return pVslowPrintAnn;}
    const CArrayAnnotation* getVslowSpacePrintAnn() const
      {return pVslowSpacePrintAnn;}
    const CArrayAnnotation* getVslowMetabPrintAnn() const
      {return pVslowMetabPrintAnn;}

    /**
    * upgrade all vectors with values from actually calculalion for current step
    **/
    void setVectors(int slowMode);

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

  private:
    /**
     * Intialize the method parameter
     */
    void initializeParameter();
  };
#endif // COPASI_CILDMMethod
