// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

/**
 *  CTSSAMethod class.
 *  This class describes the interface to all time scale separation analysis methods.
 *  The various method like ILDM or CSP have to be derived from
 *  this class.
 *
 */

#ifndef COPASI_CTSSAMethod
#define COPASI_CTSSAMethod

#include <string>
#include <sstream>

#include "copasi/utilities/CCopasiMethod.h"
#include "copasi/core/CVector.h"
#include "copasi/odepack++/CLSODA.h"
#include "copasi/core/CMatrix.h"

#include "copasi/core/CDataArray.h"
#include "copasi/core/CDataObjectReference.h"

class CTSSAProblem;
class CLsodaMethod;

/**
 * @brief The CTSSAMethod class is the base class for all time scale separation analysis methods
 */
class CTSSAMethod : public CCopasiMethod
{

private:
  /**
   * Default constructor.
   */
  CTSSAMethod();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType
   * @param const CTaskEnum::Task & taskType (default: tssAnalysis)
   */
  CTSSAMethod(const CDataContainer * pParent,
              const CTaskEnum::Method & methodType,
              const CTaskEnum::Task & taskType = CTaskEnum::Task::tssAnalysis);

  /**
   * Copy constructor.
   * @param "const CTSSAMethod &" src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CTSSAMethod(const CTSSAMethod & src,
              const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  virtual ~CTSSAMethod();

  const std::vector<std::string>& getTableNames() const;

  const CDataArray* getTable(const std::string& name);

  virtual bool setAnnotationM(size_t s) = 0;

  /**
   * initialize output for the result elements, this method
   * initializes the output elements so that an output handler
   * can be used afterwards
   **/
  virtual void initializeOutput();

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
   */
  virtual void start();

  /**
   * Check if the method is suitable for this problem
   * @return bool suitability of the method
   */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);

  /**
   *  Initialize the method parameter
   */
  virtual void initializeParameter();

  /**
   * Retrieve the current step
   */
  const int & getCurrentStep() const;

  /**
   * @return mVec_TimeScale for visualization in ILDM-tab
   * in the CQTSSAResultSubWidget
   **/
  CVector< C_FLOAT64> getVec_TimeScale(int step);

  /**
   * @return required time-value from timevector
   **/
  C_FLOAT64 getTimeForStep(int step) const;

  /**
   * upgrade all vectors with values from actually calculalion for current step
   **/
  void setVectors(int slowMode);

  /**
   * empty every vector to be able to fill them with new values for a
   * new calculation also nullify the step counter
   **/
  void emptyVectors();

  /**
   * create the CArraAnnotations for every ILDM-tab in the CQTSSAResultSubWidget
   * input for each CArraAnnotations is a seperate CMatrix
   **/
  virtual void createAnnotationsM();

protected:

  /**
   * stores the current time in the time vector
   */
  virtual void updateCurrentTime();

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
  void integrationStep(const double & deltaT);

  /**
   *  This instructs the method to prepare for integration
   *  starting with the initialState given.
   */
  void integrationMethodStart();

  /**
   *
   */
  void schur(C_INT &info);
  void schur_desc(C_INT &info);

  /**
   *
   */
  void sylvester(C_INT slow, C_INT & info);

  /**
   *
   **/
  void map_index(C_FLOAT64 *eval_r, C_INT *index, const C_INT & dim);

  void map_index_desc(C_FLOAT64 *eval_r, C_INT *index, const C_INT & dim);
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
  void calculateDerivatives(C_FLOAT64 * X1, C_FLOAT64 * Y1, bool useReducedModel);

  /**
   * This is not very elegant solution. But I don't know the better one.
   **/

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
  void mat_anal_fast_space_thomas(C_INT & slow);
  /**
   *
   **/
  double orthog(C_INT & number1, C_INT & number2);

  /************ The following concerns the both ILDM Methods *******************************/

protected:
  /**
   *  A pointer to the time scale separation analysis problem.
   */
  CTSSAProblem * mpProblem;
  std::map< std::string, CDataArray* > mapTableToName;
  std::vector<std::string>  tableNames;

  CLsodaMethod * mpLsodaMethod;

  C_INT mDim;

  /**
   *
   */
  CVector< C_FLOAT64 > mY_initial;

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
  CMatrix <C_FLOAT64> mQ_desc;

  /**
   *
   */
  CMatrix <C_FLOAT64> mR;
  CMatrix <C_FLOAT64> mR_desc;

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
  C_INT32 mSlow;

  /**
   *  Tolerance for Deuflhard criterion
   */
  C_FLOAT64 mDtol;

  /**
   *
   */
  C_FLOAT64 mEPS;

  C_FLOAT64 mNumber2Concentration;
  C_FLOAT64 mConcentration2Number;

  CVectorCore< C_FLOAT64 > mContainerState;
  C_FLOAT64 * mpContainerStateTime;

  C_FLOAT64 *mpFirstSpecies;
  const C_FLOAT64 *mpFirstSpeciesRate;

  /**
   * vectors contain whole data for all calculationsteps
   **/
  std::vector< C_INT > mVec_SlowModes;
  std::vector< C_FLOAT64 > mCurrentTime;
  std::vector< CVector<C_FLOAT64> > mVec_TimeScale;

  /**
   * stepcounter
   **/
  int mCurrentStep;
};

#endif // COPASI_CTSSAMethod
