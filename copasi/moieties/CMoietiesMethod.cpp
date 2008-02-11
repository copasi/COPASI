// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/moieties/CMoietiesMethod.cpp,v $
//   $Revision: 1.1.2.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/11 18:30:54 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CMoietiesMethod.h"
#include "CMoietiesProblem.h"

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
    CCopasiMethod(CCopasiTask::moieties, CCopasiMethod::unset),
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
  bool success = true;

  try
    {
      success = mpProblem->getModel()->forceCompile(mpCallBack);
    }

  catch (...)
    {
      success = false;
    }

  return success;
}

void CMoietiesMethod::setProblem(CMoietiesProblem * pProblem)
{mpProblem = pProblem;}
