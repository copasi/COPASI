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

#ifndef CCROSSSECTIONMETHOD_H
#define CCROSSSECTIONMETHOD_H

#include "copasi/utilities/CCopasiMethod.h"

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
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType
   * @param const CTaskEnum::Task & taskType (default: crosssection)
   */
  CCrossSectionMethod(const CDataContainer * pParent,
                      const CTaskEnum::Method & methodType,
                      const CTaskEnum::Task & taskType = CTaskEnum::Task::crosssection);

  /**
   * Copy constructor.
   * @param "const CCrossSectionMethod &" src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CCrossSectionMethod(const CCrossSectionMethod & src,
                      const CDataContainer * pParent);

  /**
   *  Destructor.
   */
  ~CCrossSectionMethod();

  /**
   */
  bool process();

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
