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

CMoietiesMethod * CMoietiesMethod::createMethod(const CCopasiMethod::SubType & subType)
{
  CMoietiesMethod * pMethod = NULL;

  switch (subType)
    {
      case Householder:
      default:
        pMethod = new CMoietiesMethod();
        break;
    }

  return pMethod;
}

CMoietiesMethod::CMoietiesMethod():
  CCopasiMethod(CCopasiTask::moieties, CCopasiMethod::Householder),
  mpProblem(NULL)
{}

CMoietiesMethod::CMoietiesMethod(const CCopasiTask::Type & taskType,
                                 const CMoietiesMethod::SubType & subType,
                                 const CCopasiContainer * pParent):
  CCopasiMethod(taskType, subType, pParent),
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
