// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CCSPMethod
#define COPASI_CCSPMethod

#include <sstream>

#include "copasi/core/CMatrix.h"
#include "copasi/core/CVector.h"
#include "copasi/tssanalysis/CTSSAMethod.h"

#include "copasi/odepack++/CLSODA.h"

class CModel;
class CState;

/**
 * @brief The CCSPMethod class implements the CSP method
 *
 * more information under: http://copasi.org/Support/User_Manual/Methods/Time_Scale_Separation_Methods/CSP/
 */
class CCSPMethod : public CTSSAMethod
{
private:
  /**
   * Default constructor.
   */
  CCSPMethod();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (defaulf: tssCSP)
   * @param const CTaskEnum::Task & taskType (default: tssAnalysis)
   */
  CCSPMethod(const CDataContainer * pParent,
             const CTaskEnum::Method & methodType = CTaskEnum::Method::tssCSP,
             const CTaskEnum::Task & taskType = CTaskEnum::Task::tssAnalysis);

  /**
   * Copy constructor.
   * @param "const CCSPMethod &" src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CCSPMethod(const CCSPMethod & src,
             const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  virtual ~CCSPMethod();

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
   */
  virtual void start();

  /**
   * Intialize the method parameter
   */
  void initializeParameter();

  /**
  * return CArrayAnnotation for visualization
  * in the CQTSSAResultSubWidget
  **/

  const CDataArray* getRadicalPointerAnn() const;

  const CDataArray* getFastReactionPointerAnn() const;

  const CDataArray* getFastReactionPointerNormedAnn() const;

  const CDataArray* getParticipationIndexAnn() const;

  const CDataArray* getParticipationIndexNormedRowAnn() const;

  const CDataArray* getParticipationIndexNormedColumnAnn() const;

  const CDataArray* getFastParticipationIndexAnn() const;

  const CDataArray* getSlowParticipationIndexAnn() const;

  const CDataArray* getImportanceIndexAnn() const;

  const CDataArray* getImportanceIndexNormedRowAnn() const;

  /**
   *  CSP output
  **/

  void CSPOutput(C_INT & N, C_INT & M, C_INT & R);
  /**
   * upgrade all vectors with values from actually calculalion for current step
   **/
  void setVectors(int fast);

  /**
   *  set vectors to NaN when the reduction was not possible
   **/
  void setVectorsToNaN();

  /**
  * empty every vector to be able to fill them with new values for a
  * new calculation also nullify the step counter
  **/
  void emptyVectors();

  /**
   * create the CArraAnnotations for every table in the CQTSSAResultSubWidget
   * input for each CArraAnnotations is a seperate CMatrix
   **/
  virtual void createAnnotationsM();

  /**
   * initialize output for the result elements, this method
   * initializes the output elements so that an output handler
   * can be used afterwards
   **/
  virtual void initializeOutput();

  /**
  * set the every CArrayAnnotation for the requested step
  * set the desription of CArayAnnotation for both dimensions
  **/
  virtual bool setAnnotationM(size_t step);

  /**
   *  print of the standart report sequence for ILDM Method
   *  @param std::ostream * ostream
   **/
  virtual void printResult(std::ostream * ostream) const;

protected:

  /**
   *  CSP related staff
   */

  /**
   *  Multiplication of  submatrix
   */

  void smmult(const CMatrix< C_FLOAT64 > & A, const CMatrix< C_FLOAT64 > & B, CMatrix< C_FLOAT64 > & C, C_INT n1, C_INT n2, C_INT n3);

  /**
   *  Substruction of  submatrix
   */

  void smsubst(const CMatrix< C_FLOAT64 > & A, const CMatrix< C_FLOAT64 > & B, CMatrix< C_FLOAT64 > & C, C_INT n1, C_INT n2);

  /**
   *   Addition of submatrix
   */

  void smadd(const CMatrix< C_FLOAT64 > & A, const CMatrix< C_FLOAT64 > & B, CMatrix< C_FLOAT64 > & C, C_INT n1, C_INT n2);

  /**
   *   Normalize  submatrix
   */

  void smnorm(C_INT n, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B, C_INT n1);

  /**
   *   Inverse  submatrix
   */

  void sminverse(C_INT n, const CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B);

  /**
   * compute amplitudes of fast and slow modes
   **/

  void modesAmplitude(C_INT N, const CVector< C_FLOAT64 > & g, const CMatrix< C_FLOAT64 > & B, CMatrix< C_FLOAT64 > & F);

  /**
   * compute CSP radical pointer and  fast reaction pointers
   **/

  void CSPradicalPointer(C_INT & N, C_INT & M, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B);

  /**
   * compute CSP Participation Index
   **/

  void CSPParticipationIndex(C_INT & N, C_INT & M, C_FLOAT64 & tauM1, CMatrix< C_FLOAT64 > & B0); //NEW

  /**
   * compute CSP Importance Index
   **/

  void CSPImportanceIndex(C_INT & N, C_FLOAT64 & tauM1, CMatrix< C_FLOAT64 > & Q);

  /**
   *  correct for the contribution of the fast time-scales  to y
   **/
  void yCorrection(C_INT & N, C_INT & M,
                   CVector< C_FLOAT64 > & y, CMatrix< C_FLOAT64 > & TAUM,
                   CMatrix< C_FLOAT64 > & F, CMatrix< C_FLOAT64 > & A);

  /**
   * Refinement Procedre :
   *  Lamm, Combustion Science and Technoligy, 1993.
   **/
  void basisRefinement(C_INT N, C_INT M,
                       const CMatrix< C_FLOAT64 > & ALA, const CMatrix< C_FLOAT64 > & TAU,
                       CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B,
                       CMatrix< C_FLOAT64 > & A0, CMatrix< C_FLOAT64 > & B0);

  /**
   * evaluate Jacobian for the current y
   **/
  //void calculateJacobianX(C_INT & n, CVector<C_FLOAT64> & y, CMatrix <C_FLOAT64> & J);
  void calculateJacobian(C_INT & n, CVector<C_FLOAT64> & y, CMatrix <C_FLOAT64> & J);

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

  bool modesAreExhausted(C_INT N, C_INT M, C_FLOAT64 & tauM, C_FLOAT64 & tauM1, CVector< C_FLOAT64 > & g,
                         const CMatrix< C_FLOAT64 > & A, const CMatrix< C_FLOAT64 > & B, CMatrix< C_FLOAT64 > & F);

  /**
   * compute  the norm C  of the off-diagonal blocks
   **/
  C_INT isBlockDiagonal(C_INT N, C_INT M, const CMatrix< C_FLOAT64 > & ALA, const C_FLOAT64 & SMALL);

  /**
   *  Start procedure of the CSP algorithm.
   *  S.H. Lam and D.A. Gaussis, International Journal of Chemical Kinetics,
   *  26, pp. 461-486, 1994
   */
  void cspstep(const double & deltaT, C_INT & n, C_INT & m, CMatrix< C_FLOAT64 > & A, CMatrix< C_FLOAT64 > & B);

  /**
   * CSP output : empty
   **/

  void emptyOutputData(C_INT N, C_INT M, C_INT R);


protected:

  /**
   *  CSP related staff
   */

  /**
   *
   */
  bool mReducedModel;

  /**
   * Unit matrix
   */
  CMatrix<C_FLOAT64> mI;

  /**
   *  A value related to a measure of the time scale separation of the fast and slow modes
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
   *
   */
  CVectorCore< C_FLOAT64 > mY;

  /**
   *  A vector of the current right hand side
   */
  CVectorCore< const C_FLOAT64 > mG;

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
  CMatrix<C_FLOAT64> mFastReactionPointerNormed;

  /**
   * Participation Index : is a mesure of participation of the r-th elementary reaction
   * to the balancing act of the i-th mode (matrix)
   **/

  CMatrix<C_FLOAT64> mParticipationIndex;
  CMatrix<C_FLOAT64> mParticipationIndexNormedRow;
  CMatrix<C_FLOAT64> mParticipationIndexNormedColumn;
  CVector<C_FLOAT64> mFastParticipationIndex;
  CVector<C_FLOAT64> mSlowParticipationIndex;

  /**
   * Importance Index: is a measure of relative importance of the contribution of r-th elementary
   * reaction to the current reaction rate of i-th species
   **/

  CMatrix<C_FLOAT64> mImportanceIndex;
  CMatrix<C_FLOAT64> mImportanceIndexNormedRow;


  /**
   *vectors contain whole data for all calculation steps
   **/
  //std::vector< CMatrix<C_FLOAT64> > mVec_mAmplitude;
  std::vector< CMatrix<C_FLOAT64> > mVec_mRadicalPointer;
  std::vector< CMatrix<C_FLOAT64> > mVec_mFastReactionPointer;
  std::vector< CMatrix<C_FLOAT64> > mVec_mFastReactionPointerNormed;
  std::vector< CMatrix<C_FLOAT64> > mVec_mParticipationIndex;
  std::vector< CMatrix<C_FLOAT64> > mVec_mParticipationIndexNormedRow;
  std::vector< CMatrix<C_FLOAT64> > mVec_mParticipationIndexNormedColumn;
  std::vector< CMatrix<C_FLOAT64> > mVec_mFastParticipationIndex;
  std::vector< CMatrix<C_FLOAT64> > mVec_mSlowParticipationIndex;
  std::vector< CMatrix<C_FLOAT64> > mVec_mImportanceIndex;
  std::vector< CMatrix<C_FLOAT64> > mVec_mImportanceIndexNormedRow;

  /**
   *CArraAnnotations for  CQTSSAResultSubWidget
   **/

  //CDataArray* pAmplitudeAnn;
  CDataArray* pRadicalPointerAnn;
  CDataArray* pFastReactionPointerAnn;
  CDataArray* pFastReactionPointerNormedAnn;
  CDataArray* pParticipationIndexAnn;
  CDataArray* pParticipationIndexNormedRowAnn;
  CDataArray* pParticipationIndexNormedColumnAnn;
  CDataArray* pFastParticipationIndexAnn;
  CDataArray* pSlowParticipationIndexAnn;
  CDataArray* pImportanceIndexAnn;
  CDataArray* pImportanceIndexNormedRowAnn;

  /**
  *input for every CArraAnnotations
  *contain data for single stepcalculation
  **/
  //CMatrix<C_FLOAT64> mAmplitudeTab;
  CMatrix<C_FLOAT64> mRadicalPointerTab;
  CMatrix<C_FLOAT64> mFastReactionPointerTab;
  CMatrix<C_FLOAT64> mFastReactionPointerNormedTab;
  CMatrix<C_FLOAT64> mParticipationIndexTab;
  CMatrix<C_FLOAT64> mParticipationIndexNormedRowTab;
  CMatrix<C_FLOAT64> mParticipationIndexNormedColumnTab;
  CMatrix<C_FLOAT64> mImportanceIndexTab;
  CMatrix<C_FLOAT64> mImportanceIndexNormedRowTab;

  CMatrix<C_FLOAT64>  mFastParticipationIndexTab;
  CMatrix<C_FLOAT64>  mSlowParticipationIndexTab;

};
#endif // COPASI_CCSPMethod
