// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CProblemContext
#define COPASI_CProblemContext

#include "copasi/OpenMP/CContext.h"
#include "copasi/utilities/CCopasiProblem.h"

class CMathContext;

class CProblemContext : public CContext< CCopasiProblem * >
{
public:
  CProblemContext() = delete;

  CProblemContext(const CProblemContext & src) = delete;

  CProblemContext(CCopasiProblem * pProblem);

  ~CProblemContext();

  /**
   * Set the pointer to container used for calculations
   * @param CCopasiProblem * pProblem
   */
  void setProblem(CCopasiProblem * pProblem);

  /**
   * Set the pointer to container used for calculations
   * @param CMathContext * pContext
   */
  void setMathContext(CMathContext * pContext);

private:
  CMathContext * mpMathContext;
};

#endif // COPASI_CProblemContext
