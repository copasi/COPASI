// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

/**
 *  CTimeSensMethod class.
 *  This class describes the interface to all integration methods.
 *  The various method like LSODA or Gillespie have to be derived from
 *  this class.
 *
 *  Created for COPASI by Stefan Hoops 2002
 */

#ifndef COPASI_CTimeSensMethod
#define COPASI_CTimeSensMethod

#include <string>

#include "copasi/utilities/CCopasiMethod.h"
#include "copasi/core/CVector.h"
#include "copasi/math/CMathEnum.h"
#include "copasi/core/CMatrix.h"


class CTimeSensTask;
class CTimeSensProblem;
class CMathContainer;

class CTimeSensMethod : public CCopasiMethod
{
public:
  /**
   * Enumeration value for the return value
   */
  enum Status
  {
    FAILURE = -1,
    NORMAL = 0,
    ROOT = 1
  };

  // Operations
private:
  /**
   * Default constructor.
   */
  CTimeSensMethod();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType
   * @param const CTaskEnum::Task & taskType (default: timeCourse)
   */
  CTimeSensMethod(const CDataContainer * pParent,
                  const CTaskEnum::Method & methodType,
                  const CTaskEnum::Task & taskType = CTaskEnum::Task::timeCourse);

  /**
   * Copy constructor.
   * @param const CTimeSensMethod & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CTimeSensMethod(const CTimeSensMethod & src,
                  const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  ~CTimeSensMethod();

  /**
   *  Set a pointer to the problem.
   *  This method is used by CTrajectory
   *  @param "CTimeSensProblem *" problem
   */
  void setProblem(CTimeSensProblem * problem);

  /**
   * Inform the trajectory method that the state has changed outside
   * its control
   * @param const CMath::StateChange & change
   */
  virtual void stateChange(const CMath::StateChange & change);

  /**
   *  This instructs the method to calculate a time step of deltaT
   *  starting with the current state, i.e., the result of the previous
   *  step.
   *  The new state (after deltaT) is expected in the current state.
   *  The return value is the actual timestep taken.
   *  @param const double & deltaT
   *  @param const bool & final (default: false)
   *  @return Status status
   */
  virtual Status step(const double & deltaT, const bool & final = false);

  /**
   *  This instructs the method to prepare for integration
   */
  virtual void start();

  /**
   * This initializes the Matrix for the results
   */
  virtual void initResult();

  /**
   * Retrieve the roots.
   * @return const CVectorCore< C_INT > & roots
   */
  const CVectorCore< C_INT > & getRoots() const;

  /**
   * Check if the method is suitable for this problem
   * @return bool suitability of the method
   */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);

  /**
   * Check whether to integrate the reduced model
   * @return const bool & integrateReducedModel
   */
  const bool & integrateReducedModel() const;

  /**
   * This updates the result matrices from the internal calculations. To be called before output.
   */
  virtual void copySensitivitiesToResultMatrix() = 0;


  /**
   * Initialize everything that is needed for the various derivatives,
   * e.g. lists of value pointers, update sequences, etc.
   */
  void initializeDerivativesCalculations(bool reduced);
protected:
  /**
   * Signal that the math container has changed
   */
  virtual void signalMathContainerChanged();

  void output(const bool & useMoieties);


  /**
   * This calculates the derivatives of the initial state with respect to the requested parameters
   */
  void calculate_dInitialState_dPar(CMatrix<C_FLOAT64>& s);

  /**
   * This calculates the derivatives of the RHS with respect to the requested parameters
   */
  void calculate_dRate_dPar(CMatrix<C_FLOAT64>& s, bool reduced);

  /**
   * This calculates the derivatives of the assignments with respect to the state variables
   */
  void calculate_dAssignments_dState(CMatrix<C_FLOAT64>& s, bool reduced);

  /**
   * This calculates the derivatives of the assignments with respect to the requested parameters
   */
  void calculate_dAssignments_dPar(CMatrix<C_FLOAT64>& s);

  // Attributes
protected:
  /**
   *  A reference to the current state. This is set from outside
   *  with the setState() method and never changed anywhere else.
   *  It's used to report the results to the calling TrajectoryTask
   */
  CVectorCore< C_FLOAT64 > mContainerState;

  /**
   * A pointer to the time value of the current state.
   */
  C_FLOAT64 * mpContainerStateTime;

  /**
   * The task calling the method
   */
  CTimeSensTask * mpTask;

  /**
   *  A pointer to the trajectory problem.
   */
  CTimeSensProblem * mpProblem;

  /**
   * Vector containing information on the current roots
   */
  CVectorCore< C_INT > mRootsFound;

  /**
   * Pointer to the value indicating whether to integrate the reduced model.
   */
  const bool * mpReducedModel;

  /**
   * Default value indicating whether to integrate the reduced model
   * initialized to false.
   */
  static const bool ReducedModel;

  /**
   *  Number of variables in the model
   */
  size_t mSystemSize;

  /**
   *  Number of parameters for the sensitivities to calculate
   */
  unsigned C_INT32 mNumParameters;

  /// Number of assignment targets for which sensitivities are calculated
  size_t mNumAssTargets;

  CMatrix<C_FLOAT64> mJacobian;
  CMatrix<C_FLOAT64> mdRate_dPar;
  CMatrix<C_FLOAT64> mAssignmentJacobian;
  CMatrix<C_FLOAT64> mdAssignment_dPar;

  /**
   * pointers to the values of the parameters
   */

  /// the pointers to the values of the objects as provided by the problem (generally initial values)
  CVector< C_FLOAT64* > mParameterInitialValuePointers;

  /// the pointers as used during the simulation, initial values of fixed quantities are replaced by their transient counterparts.
  CVector< C_FLOAT64* > mParameterTransientValuePointers;

  CVector<bool> mParameterIsInitialConcentration;
  /**
   * pointers to the values of the assignment targets
   */
  CVector< C_FLOAT64* > mAssTargetValuePointers;

  CCore::CUpdateSequence mSeq1;
  CCore::CUpdateSequence mSeq2;
  CCore::CUpdateSequence mSeq3;

  ///some methods for doing debug output
  static void printObjectSet(const std::string & s, const CObjectInterface::ObjectSet & os);
  static void printUpdateSeq(const std::string & s, const CCore::CUpdateSequence & us);


};

#endif // COPASI_CTimeSensMethod
