// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CMoietiesMethod.h"
#include "CMoietiesProblem.h"

#include "math/CMathContainer.h"
#include "model/CModel.h"

CMoietiesMethod::CMoietiesMethod(const CCopasiContainer * pParent,
                                 const CTaskEnum::Method & methodType,
                                 const CTaskEnum::Task & taskType):
  CCopasiMethod(pParent, methodType, taskType),
  mpProblem(NULL)
{}

CMoietiesMethod::CMoietiesMethod(const CMoietiesMethod & src,
                                 const CCopasiContainer * pParent):
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
      const_cast< CModel * >(&mpContainer->getModel())->compileIfNecessary(mpCallBack);
    }

  catch (...)
    {}

  return true;
}

void CMoietiesMethod::setProblem(CMoietiesProblem * pProblem)
{
  mpProblem = pProblem;
}
