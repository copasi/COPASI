// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_SENSMethod
#define COPASI_SENSMethod

#include <string>

#include "copasi/utilities/CCopasiMethod.h"
#include "copasi/core/CDataArray.h"

class CSensProblem;
//class CProcessReport;

class CSensMethodLocalData
{
public:
  CArray tmp1;
  CArray tmp2;

  /**
   * A vector pointers to variables.
   */
  CVector< C_FLOAT64 * > mInitialStateVariables;

  /**
   * Update sequences to synchronize the initial state
   * after changing an initial value.
   */
  CCore::CUpdateSequence mInitialSequences;

  /**
   * holds the index in the index array corresponding to the given level.
   * I.e. which dimension of the result array the variables correspond to.
   */
  size_t index;
};

class CSensMethod : public CCopasiMethod
{
  // Operations
private:
  /**
   * Default constructor.
   */
  CSensMethod();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType
   * @param const CTaskEnum::Task & taskType (default: scan)
   */
  CSensMethod(const CDataContainer * pParent,
              const CTaskEnum::Method & methodType,
              const CTaskEnum::Task & taskType = CTaskEnum::Task::sens);

  /**
  * Copy constructor.
  * @param "const CTSSMethod &" src
  * @param const CDataContainer * pParent (default: NULL)
  */
  CSensMethod(const CSensMethod & src,
              const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  ~CSensMethod();

  /**
   */
  bool process();

  /**
   * initializes the subtask, creates the internal data structures of the method,
   * resizes the result arrays and creates the array annotations
   */
  bool initialize(CSensProblem* problem);

  /**
   * Do all necessary restore procedures so that the
   * model is in the same state as before
   * @param const bool & updateModel
   * @result bool success
   */
  bool restore(const bool & updateModel);

  /**
   * Check if the method is suitable for this problem
   * @return bool suitability of the method
   */
  virtual bool isValidProblem(const CCopasiProblem * pProblem) override;

  /**
   * Set the call back of the problem
   * @param CProcessReport * pCallBack
   * @result bool succes
   */
  virtual bool setCallBack(CProcessReportLevel callBack) override;

  /**
   * estimate how many calls to the subtask are necessary. Works only after
   * initialize() was called.
   */
  size_t getNumberOfSubtaskCalculations();

protected:

  bool calculate_one_level(size_t level, CArray & result);
  bool do_target_calculation(size_t level, CArray & result, bool first);

  C_FLOAT64 do_variation(C_FLOAT64 & variable);

  void calculate_difference(size_t level, const C_FLOAT64 & delta,
                            CArray & result, CArray::index_type & resultindex);

  /**
   * calculate the scaled sensitivities. Calls scaling_variables().
   * It is assumed that the scaled result array is already of the correct size
   * (this is done in initialize()).
   */
  void do_scaling();

  /**
   * This contains the loop over the target functions for scaling the sensitivities
   */
  void scaling_targetfunction(const C_FLOAT64 & factor,
                              CArray::index_type & resultindex);

  /**
   * This contains the loop over the variables for scaling the sensitivities. Works recursively
   * and calls scaling_targetfunction() in the end.
   */
  void scaling_variables(size_t level, const C_FLOAT64 & factor,
                         CArray::index_type & resultindex);

  /**
   * collapse the first dimension of the scaled result (by
   * calculating the 2-norm over the target functions)
   */
  void do_collapsing();

  C_FLOAT64 do_collapsing_innerloop(CArray::index_type & fullindex);

  // Attributes
protected:
  /**
   *  A pointer to the sensitivities problem.
   */
  CSensProblem * mpProblem;

  std::vector<CSensMethodLocalData> mLocalData;

  CVector< C_FLOAT64 * > mTargetValuePointers;

  CCopasiTask * mpSubTask;

  /**
   * The sequence need to calculate all target functions
   */
  CCore::CUpdateSequence mTargetValueSequence;

  C_FLOAT64 * mpDeltaFactor;
  C_FLOAT64 * mpMinDelta;

  ///stores the update model flag of the subtask
  bool mStoreSubtasktUpdateFlag;

private:
  size_t mProgressHandler;
  unsigned C_INT32 mProgress;

  size_t mCounter;
  size_t mFailedCounter;
};

#endif
