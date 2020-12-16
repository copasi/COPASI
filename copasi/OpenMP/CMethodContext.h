// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CMethodContext
#define COPASI_CMethodContext

#include "copasi/OpenMP/CContext.h"
#include "copasi/utilities/CCopasiMethod.h"

class CMathContext;

class CMethodContext : public CContext< CCopasiMethod * >
{
public:
  CMethodContext() = delete;

  CMethodContext(const CMethodContext & src) = delete;

  CMethodContext(CCopasiMethod * pMethod);

  ~CMethodContext();

  /**
   * Set the pointer to container used for calculations
   * @param CCopasiMethod * pMethod
   */
  void setMethod(CCopasiMethod * pMethod);

  /**
   * Set the pointer to container used for calculations
   * @param CMathContext * pContext
   */
  void setMathContext(CMathContext * pContext);

private:
  CMathContext * mpMathContext;
};

#endif // COPASI_CMethodContext
