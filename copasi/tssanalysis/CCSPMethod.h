// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tssanalysis/CCSPMethod.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2008/03/04 16:54:18 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc., EML Research, gGmbH, University of Heidelberg, 
// and The University of Manchester. 
// All rights reserved. 

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual 
// Properties, Inc. and EML Research, gGmbH. 
// All rights reserved. 

#ifndef COPASI_CCSPMethod
#define COPASI_CCSPMethod

#define CSP_DEBUG

#include <sstream>
#include "utilities/CVector.h"
#include "utilities/CMatrix.h"

#include "tssanalysis/CTSSAMethod.h"

#include "odepack++/CLSODA.h"

class CModel;
class CState;

class CCSPMethod : public CTSSAMethod
  {
    friend CTSSAMethod *
    CTSSAMethod::createTSSAMethod(CCopasiMethod::SubType subType,
                                  CTSSAProblem * pProblem);

  public:
    struct Data
      {
        C_INT dim;
        CCSPMethod * pMethod;
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
     *  Current time.
     */
    C_FLOAT64 mTime;

    /**
     *  Jacobian matrix
     */
    CMatrix <C_FLOAT64> mJacobian;

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
     *  CSP related staff
     */

    /**
     * Unit matrix 
     */
    CMatrix<C_FLOAT64> mI;

    /**
     *  A value related to a mesure of the time scale separation of the fast and slow modes
     */
    C_FLOAT64 mEps;

    /**
     *  A maximux relative error
     */
    C_FLOAT64 mRerror;

    /**
     *  A maximux absolute error
     */
    C_FLOAT64 mAerror;

    /**
     *  A vector of the current right hand side
     */
    CVector<C_FLOAT64> mG;

    /**
     *  An error vector build on the basis of the solution vector
     */
    CVector<C_FLOAT64> mYerror;

    // Operations
  private:
    /**
     * Default constructor.
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCSPMethod(const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Copy constructor.
     * @param "const CCSPMethod &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCSPMethod(const CCSPMethod & src,
               const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CCSPMethod();

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
     * Intialize the method parameter
     */
    void initializeParameter();

    /**
     *  CSP related staff
     */

    /**
     *  Multiplication of  submatrix
     */

    void smmult(CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B, CMatrix< C_FLOAT64 > & C, C_INT & n1, C_INT & n2, C_INT & n3);

    /**
     *  Substruction of  submatrix
     */

    void smsubst(CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B, CMatrix< C_FLOAT64 > & C, C_INT & n1, C_INT & n2);

    /**
     *   Addition of submatrix
     */

    void smadd(CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B, CMatrix< C_FLOAT64 > & C, C_INT & n1, C_INT & n2);

    /**
     *   Normalize  submatrix
     */

    void smnorm(C_INT & n, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B, C_INT & n1);

    /**
     *   Inverse  submatrix
     */

    void sminverse(C_INT & n, C_INT & m, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B);


    /**
    * the CSP refinement procedure, step 1 :
    * refine the row  vectors B ,
    *  colume vectors A  are known
    */

    void bRefinement(C_INT & n, C_INT & m, CMatrix< C_FLOAT64 > & TAU0, CMatrix< C_FLOAT64 > & B0, CMatrix< C_FLOAT64 > & J, CMatrix< C_FLOAT64 > & B);

    /**
     * the CSP refinement procedure, step 2 :
     * refine the columen vectors A
     *  as the row vectors B  use the refined in step 1
     */

    void aRefinement(C_INT & n, C_INT & m, CMatrix< C_FLOAT64 > & A0, CMatrix< C_FLOAT64 > & B, CMatrix<C_FLOAT64 > & J, CMatrix< C_FLOAT64 > & A);

    /**
     * Build the fast subspace projection matrix
    */

    void fastSubspaceProjectionMatrix(C_INT & n, C_INT & m, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B, CMatrix< C_FLOAT64 > & Q);

    /**
     *  Start procedure of the CSP algorithm.
     *  S.H. Lam and D.A. Gaussis, International Journal of Chemical Kinetics,
     *  26, pp. 461-486, 1994
     */
    void cspstep(C_INT & n, C_INT & m, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B);

    /**
     *  correct for the contribution of the fast time-scales  to y
     **/
    void yCorrection(C_INT & n, C_INT & m, CVector< C_FLOAT64 > & y, CVector< C_FLOAT64 > & g, CMatrix< C_FLOAT64 > & J, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B);

    /**
     * evaluate Jacobian for the current y
     **/
    void calculateJacobianX(C_INT & n, CVector<C_FLOAT64> & y, CMatrix <C_FLOAT64> & J);

    /**
     * enforce the criterion to declare a mode exhausted
     **/
    void exhaustedFastModesDetection(C_INT & n, C_INT & m, C_INT & tot, C_FLOAT64 & tisc , CVector< C_FLOAT64 > & g, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B);

    /**
     * find the new number of  dead modes  according to the time-scale separation ratio 
     **/
    void findNewNumberOfDeadModes(C_INT & n, C_INT & m, C_INT & k, CVector< C_FLOAT64 > & tsc);
  };
#endif // COPASI_CCSPMethod
