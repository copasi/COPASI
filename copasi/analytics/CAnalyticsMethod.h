// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CANALYTICSMETHOD_H
#define CANALYTICSMETHOD_H

#include "utilities/CCopasiMethod.h"

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
   * @param const CCopasiContainer * pParent
   * @param const CTaskEnum::Method & methodType
   * @param const CTaskEnum::Task & taskType (default: analytics)
   */
  CAnalyticsMethod(const CCopasiContainer * pParent,
                      const CTaskEnum::Method & methodType,
                      const CTaskEnum::Task & taskType = CTaskEnum::analytics);

  /**Analytics
   * Copy constructor.
   * @param "const CAnalyticsMethod &" src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CAnalyticsMethod(const CAnalyticsMethod & src,
                      const CCopasiContainer * pParent = NULL);

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
