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

#ifndef COPASI_CMoietiesMethod
#define COPASI_CMoietiesMethod

#include "copasi/utilities/CCopasiMethod.h"

class CProcessReportLevel;
class CMoietiesProblem;

class CMoietiesMethod : public CCopasiMethod
{
private:
  /**
   * Default constructor
   */
  CMoietiesMethod();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: Householder)
   * @param const CTaskEnum::Task & taskType (default: moieties)
   */
  CMoietiesMethod(const CDataContainer * pParent,
                  const CTaskEnum::Method & methodType = CTaskEnum::Method::Householder,
                  const CTaskEnum::Task & taskType = CTaskEnum::Task::moieties);

  /**
   * Copy constructor
   * @param const CMoietiesMethod & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  CMoietiesMethod(const CMoietiesMethod & src,
                  const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~CMoietiesMethod();

  /**
   * Determine the independent metabolites.
   */
  virtual bool process();

  /**
   * Set the problem
   * @param CMoietiesProblem * pProblem
   */
  void setProblem(CMoietiesProblem * pProblem);

  // Attributes
protected:
  /**
   * The problem to be processed
   */
  CMoietiesProblem * mpProblem;
};

#endif // COPASI_CMoietiesMethod
