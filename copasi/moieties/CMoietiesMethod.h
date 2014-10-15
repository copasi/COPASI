// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

class CProcessReport;
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
   * @param const CCopasiContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: Householder)
   * @param const CTaskEnum::Task & taskType (default: moieties)
   */
  CMoietiesMethod(const CCopasiContainer * pParent,
                  const CTaskEnum::Method & methodType = CTaskEnum::Householder,
                  const CTaskEnum::Task & taskType = CTaskEnum::moieties);

  /**
   * Copy constructor
   * @param const CMoietiesMethod & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  CMoietiesMethod(const CMoietiesMethod & src,
                  const CCopasiContainer * pParent = NULL);

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
