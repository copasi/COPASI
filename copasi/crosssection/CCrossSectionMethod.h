// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CCROSSSECTIONMETHOD_H
#define CCROSSSECTIONMETHOD_H

#include "utilities/CCopasiMethod.h"

class CCrossSectionProblem;

class CCrossSectionMethod : public CCopasiMethod
{
private:
  /**
   * Default constructor
   */
  CCrossSectionMethod();

public:
  /**
   * Specific constructor
   * @param const CCopasiContainer * pParent
   * @param const CTaskEnum::Method & methodType
   * @param const CTaskEnum::Task & taskType (default: crosssection)
   */
  CCrossSectionMethod(const CCopasiContainer * pParent,
                      const CTaskEnum::Method & methodType,
                      const CTaskEnum::Task & taskType = CTaskEnum::crosssection);

  /**
   * Copy constructor.
   * @param "const CCrossSectionMethod &" src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CCrossSectionMethod(const CCrossSectionMethod & src,
                      const CCopasiContainer * pParent = NULL);

  /**
   *  Destructor.
   */
  ~CCrossSectionMethod();

  /**
   */
  bool process(CProcessReport * handler);

  /**
   * initializes the subtask, creates the internal data structures of the method
   * resizes the result arrays and creates the array annotations
   */
  bool initialize(CCrossSectionProblem* problem);

  /**
   * Check if the method is suitable for this problem
   * @return bool suitability of the method
   */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);
};

#endif // CCROSSSECTIONMETHOD_H
