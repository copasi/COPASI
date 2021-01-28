// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CANALYTICSMETHOD_H
#define CANALYTICSMETHOD_H

#include "copasi/utilities/CCopasiMethod.h"

class CAnalyticsProblem;

class CAnalyticsMethod : public CCopasiMethod
{
private:
  /**
   * Default constructor
   */
  CAnalyticsMethod();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType
   * @param const CTaskEnum::Task & taskType (default: analytics)
   */
  CAnalyticsMethod(const CDataContainer * pParent,
                   const CTaskEnum::Method & methodType,
                   const CTaskEnum::Task & taskType = CTaskEnum::Task::analytics);

  /**Analytics
   * Copy constructor.
   * @param "const CAnalyticsMethod &" src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CAnalyticsMethod(const CAnalyticsMethod & src,
                   const CDataContainer * pParent = NULL);

  /**
   *  Destructor.
   */
  ~CAnalyticsMethod();

  /**
   */
  bool process(CProcessReport * handler);

  /**
   * initializes the subtask, creates the internal data structures of the method
   * resizes the result arrays and creates the array annotations
   */
  bool initialize(CAnalyticsProblem* problem);

  /**
   * Check if the method is suitable for this problem
   * @return bool suitability of the method
   */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);
};

#endif // CANALYTICSMETHOD_H
