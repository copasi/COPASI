// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CProblemFactory
#define COPASI_CProblemFactory

#include "copasi/utilities/CTaskEnum.h"

class CCopasiProblem;
class CDataContainer;

class CProblemFactory
{
public:
  static CCopasiProblem * create(const CTaskEnum::Task & type, const CDataContainer * pParent);

  static CCopasiProblem * copy(const CCopasiProblem * pSrc, const CDataContainer * pParent);
};

#endif //COPASI_CProblemFactory
