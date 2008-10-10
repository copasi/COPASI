// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tssanalysis/CCSPMethod.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/10/10 09:54:13 $
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
     *  An alternative  value related to a mesure of the time scale separation of the fast and slow modes
     */
    C_FLOAT64 mTsc;

    /**
     *  A maximux relative error
     */
    C_FLOAT64 mRerror;

    /**
     *  A maximux absolute error
     */
    C_FLOAT64 mAerror;

    /**
     *  Max number of the refinement iterations
     */
    C_INT mIter;

    /**
     *  A vector of the current right hand side
     */
    CVector<C_FLOAT64> mG;

    /**
     *  An error vector build on the basis of the solution vector
     */
    CVector<C_FLOAT64> mYerror;

    /**
    *  The basis vectors B from the time step (T - delta T)
    */
    CMatrix<C_FLOAT64> mB;

    C_INT mTStep;
    /**
    *  indicates whether the basis vectors B were computed on the time step (T - delta T)
    */
    C_INT mCSPbasis;

    /**
     * CSP Output
     */

    C_INT mSetVectors;

    /**
     *  Amplitudes of  reaction modes (column vector);
     **/

    CVector<C_FLOAT64> mAmplitude;

    /**
     *  Radical Pointer: whenever is not a small number, species k is said to be CSP radical
     **/

    CMatrix<C_FLOAT64> mRadicalPointer;

    /**
    *  Fast Reaction Pointer of the m-th reaction mode : whenever is not a small number,
    *  the r-th reaction is said to be a fast reaction
    **/

    CMatrix<C_FLOAT64> mFastReactionPointer;

    /**
     * Participation Index : is a mesure of participation of the r-th elementary reaction
     * to the balancing act of the i-th mode (matrix)
     **/

    CMatrix<C_FLOAT64> mParticipationIndex;

    /**
     * Importance Index: is a mesure of relative importance of the contribution of r-th elementary
     * reaction to the current reaction rate of i-th spiecies
     **/

    CMatrix<C_FLOAT64> mImportanceIndex;

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
     *   TEST: perturbate basis vectors A
     */

    void perturbateA(C_INT & n, CMatrix< C_FLOAT64 > & A, C_FLOAT64 delta);

    /**
     *   Inverse  submatrix
     */

    void sminverse(C_INT & n, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B);

    /**
     * compute amplitudes of fast and slow modes
     **/

    void modesAmplitude(C_INT & N, C_INT & M, CVector< C_FLOAT64 > & g, CMatrix< C_FLOAT64 > & B, CMatrix< C_FLOAT64 > & F);

    /**
     * compute CSP radical pointer and  fast reaction pointers
     **/

    void CSPradicalPointer(C_INT & N, C_INT & M, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B);

    /**
     * compute CSP Participation Index
     **/

    void CSPParticipationIndex(C_INT & N, C_FLOAT64 & tauM1, CMatrix< C_FLOAT64 > & B0);

    /**
     * compute CSP Importance Index
     **/

    void CSPImportanceIndex(C_INT & N, C_FLOAT64 & tauM1, CMatrix< C_FLOAT64 > & Q);

    /**
     *  correct for the contribution of the fast time-scales  to y
     **/
    void yCorrection(C_INT & N, C_INT & M, CVector< C_FLOAT64 > & y, CMatrix< C_FLOAT64 > & TAUM, CMatrix< C_FLOAT64 > & F, CMatrix< C_FLOAT64 > & A);

    /**
     * Refinement Procedre :
     *  Lamm, Combustion Science and Technoligy, 1993.
     **/
    void basisRefinement(C_INT & N, C_INT & M, CMatrix< C_FLOAT64 > & ALA, CMatrix< C_FLOAT64 > & TAU, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B, CMatrix< C_FLOAT64 > & A0, CMatrix< C_FLOAT64 > & B0);

    /**
     * evaluate Jacobian for the current y
     **/
    void calculateJacobianX(C_INT & n, CVector<C_FLOAT64> & y, CMatrix <C_FLOAT64> & J);

    /**
     * find  the new number of fast  according to the time-scale separation ratio
     **/
    void findTimeScaleSeparation(C_INT & n, C_INT & k, CVector< C_FLOAT64 > & tsc, C_INT & info);

    /**
     * find  the number of candidates to fast  according to the time-scale separation ratio
     **/
    void findCandidatesNumber(C_INT & n, C_INT & k, CVector< C_FLOAT64 > & tsc, C_INT & info);

    /**
     * check : whether each of the analysed M modes is exhausted
     **/

    bool modesAreExhausted(C_INT & N, C_INT & M, C_FLOAT64 & tauM, C_FLOAT64 & tauM1 , CVector< C_FLOAT64 > & g, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B, CMatrix< C_FLOAT64 > & F);

    /**
     * compute  the norm C  of the off-diagonal blocks
     **/
    bool isBlockDiagonal(C_INT & N, C_INT & M, CMatrix< C_FLOAT64 > & ALA, C_FLOAT64 small);

    /**
     *  Start procedure of the CSP algorithm.
     *  S.H. Lam and D.A. Gaussis, International Journal of Chemical Kinetics,
     *  26, pp. 461-486, 1994
     */
    void cspstep(const double & deltaT, C_INT & n, C_INT & m, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B);

    /**
     * CSP output
     **/

    void CSPOutput(C_INT & N, C_INT & M, C_INT & R);

    /**
     * CSP output : empty
     **/

    void emptyOutputData(C_INT & N, C_INT & M, C_INT & R);

    /**
     *vectors contain whole data for all calculation steps
     **/
    std::vector< CMatrix<C_FLOAT64> > mVec_mAmplitude;
    std::vector< CMatrix<C_FLOAT64> > mVec_mRadicalPointer;
    std::vector< CMatrix<C_FLOAT64> > mVec_mFastReactionPointer;
    std::vector< CMatrix<C_FLOAT64> > mVec_mParticipationIndex;
    std::vector< CMatrix<C_FLOAT64> > mVec_mImportanceIndex;

    /**
     *CArraAnnotations for every ILDM-tab in the CQTSSAResultSubWidget
     **/
    CArrayAnnotation* pAmplitudeAnn;
    CArrayAnnotation* pRadicalPointerAnn;
    CArrayAnnotation* pFastReactionPointerAnn;
    CArrayAnnotation* pParticipationIndexAnn;
    CArrayAnnotation* pImportanceIndexAnn;

    /**
    *required for creation of above listed CArrayAnnotation
    **/
    CArrayAnnotation* pTmp1;
    CArrayAnnotation* pTmp2;
    CArrayAnnotation* pTmp3;
    CArrayAnnotation* pTmp4;
    CArrayAnnotation* pTmp5;

    /**
    *input for every CArraAnnotations
    *contain data for single stepcalculation
    **/
    CMatrix<C_FLOAT64> mAmplitudeTab;
    CMatrix<C_FLOAT64> mRadicalPointerTab;
    CMatrix<C_FLOAT64> mFastReactionPointerTab;
    CMatrix<C_FLOAT64> mParticipationIndexTab;
    CMatrix<C_FLOAT64> mImportanceIndexTab;

    /**
    * return CArrayAnnotation for visualization in ILDM-tab
    * in the CQTSSAResultSubWidget
    **/
    const CArrayAnnotation* getAmplitudeAnn() const
      {return pAmplitudeAnn;}
    const CArrayAnnotation* getRadicalPointerAnn() const
      {return pRadicalPointerAnn;}
    const CArrayAnnotation* getFastReactionPointerAnn() const
      {return pFastReactionPointerAnn;}
    const CArrayAnnotation* getParticipationIndexAnn() const
      {return pParticipationIndexAnn;}
    const CArrayAnnotation* getImportanceIndexAnn() const
      {return pImportanceIndexAnn;}

    /**
     * upgrade all vectors with values from actually calculalion for current step
     **/
    void setVectors();

    /**
    * empty every vector to be able to fill them with new values for a
    * new calculation also nullify the step counter
    **/
    void emptyVectors();

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
  };
#endif // COPASI_CCSPMethod
