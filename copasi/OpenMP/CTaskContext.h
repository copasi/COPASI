// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CTaskContext
#define COPASI_CTaskContext

#include "copasi/OpenMP/CContext.h"
#include "copasi/utilities/CCopasiTask.h"

class CMathContext;

class CTaskContext : public CContext< CCopasiTask * >
{
public:
  CTaskContext() = delete;

  CTaskContext(const CTaskContext & src) = delete;

  CTaskContext(CCopasiTask * pTask);

  ~CTaskContext();

  /**
   * Set the pointer to container used for calculations
   * @param CCopasiTask * pTask
   */
  void setTask(CCopasiTask * pTask);

  /**
   * Set the pointer to container used for calculations
   * @param CMathContext * pContext
   */
  void setMathContext(CMathContext * pContext);

private:
  CMathContext * mpMathContext;
};

#endif // COPASI_CTaskContext