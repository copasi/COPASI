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

#include "copasi/copasi.h"

#include "CMoietiesMethod.h"
#include "CMoietiesProblem.h"

#include "copasi/math/CMathContainer.h"
#include "copasi/model/CModel.h"

CMoietiesMethod::CMoietiesMethod(const CDataContainer * pParent,
                                 const CTaskEnum::Method & methodType,
                                 const CTaskEnum::Task & taskType):
  CCopasiMethod(pParent, methodType, taskType),
  mpProblem(NULL)
{}

CMoietiesMethod::CMoietiesMethod(const CMoietiesMethod & src,
                                 const CDataContainer * pParent):
  CCopasiMethod(src, pParent),
  mpProblem(src.mpProblem)
{}

// virtual
CMoietiesMethod::~CMoietiesMethod()
{}

// virtual
bool CMoietiesMethod::process()
{
  try
    {
      const_cast< CModel * >(&mpContainer->getModel())->compileIfNecessary(mProcessReport.toProcessReportPtr());
    }

  catch (...)
    {}

  return true;
}

void CMoietiesMethod::setProblem(CMoietiesProblem * pProblem)
{
  mpProblem = pProblem;
}
