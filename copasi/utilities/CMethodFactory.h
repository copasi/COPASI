// Copyright (C) 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CMethodFactory
#define COPASI_CMethodFactory

#include "copasi/utilities/CTaskEnum.h"

class CCopasiMethod;
class CDataContainer;

class CMethodFactory
{
public:
  /**
   * Create a COPASI method
   * @param const CTaskEnum::Task & taskType
   * @param const CTaskEnum::Method & methodType
   * @param const CDataContainer * pParent
   */
  static CCopasiMethod * create(const CTaskEnum::Task & taskType,
                                const CTaskEnum::Method & methodType,
                                const CDataContainer * pParent);

  /**
   * Copy a COPASI method
   * @param const const CCopasiMethod * pSrc
   * @param const CDataContainer * pParent
   */
  static CCopasiMethod * copy(const CCopasiMethod * pSrc,
                              const CDataContainer * pParent);
};

#endif //COPASI_CMethodFactory
