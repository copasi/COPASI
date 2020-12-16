// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CTaskFactory
#define COPASI_CTaskFactory

#include "copasi/utilities/CTaskEnum.h"

class CCopasiTask;
class CDataContainer;

class CTaskFactory
{
public:
  static CCopasiTask * create(const CTaskEnum::Task & type, const CDataContainer * pParent);

  static CCopasiTask * copy(const CCopasiTask * pSrc, const CDataContainer * pParent);
};

#endif //COPASI_CTaskFactory
