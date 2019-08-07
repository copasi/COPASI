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

#ifndef COPASI_COscMethod
#define COPASI_COscMethod

#include "copasi/utilities/CCopasiMethod.h"

class COscillationProblem;
class COscillationTask;

class COscillationMethod : public CCopasiMethod
{
public:

protected:

  COscillationProblem * mpOscProblem;

  //    COptTask * mpParentTask;

private:
  /**
   * Default constructor.
   */
  COscillationMethod();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType
   * @param const CTaskEnum::Task & taskType (default: optimization)
   */
  COscillationMethod(const CDataContainer * pParent,
                     const CTaskEnum::Method & methodType,
                     const CTaskEnum::Task & taskType = CTaskEnum::optimization);

  /**
   * Copy constructor
   * @param const COscillationMethod & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  COscillationMethod(const COscillationMethod & src,
                     const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~COscillationMethod();

  /**
   * Execute the algorithm
   * @ return success;
   */
  virtual bool run() = 0;

  /**
   * Set the problem to be optmised
   * @param "COscillationProblem *" problem
   */
  void setProblem(COscillationProblem * problem);

  /**
   * Initialize arrays and pointer.
   * @return bool success
   */
  virtual bool initialize();

  /**
   * Check if the method is suitable for this problem
   * @return bool suitability of the method
   */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);

protected:
  /**
   * Cleanup arrays and pointers.
   * @return bool success
   */
  virtual bool cleanup();
};

#endif  // COPASI_COscillationMethod
