// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/moieties/CMoietiesMethod.cpp,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/09 00:58:16 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CMoietiesMethod.h"

CMoietiesMethod * CMoietiesMethod::createMethod(const CCopasiMethod::SubType & subType)
{
  CMoietiesMethod * pMethod = NULL;

  switch (subType)
    {
    case Householder:
      // pMethod = new CMoietiesMethodHouseholder();
      break;

    default:
      // pMethod = new CMoietiesMethodHouseholder();
      break;
    }

  return pMethod;
}

CMoietiesMethod::CMoietiesMethod():
    CCopasiMethod(CCopasiTask::moieties, CCopasiMethod::unset)
{}

CMoietiesMethod::CMoietiesMethod(const CCopasiTask::Type & taskType,
                                 const CMoietiesMethod::SubType & subType,
                                 const CCopasiContainer * pParent):
    CCopasiMethod(taskType, subType, pParent)
{}

CMoietiesMethod::CMoietiesMethod(const CMoietiesMethod & src,
                                 const CCopasiContainer * pParent):
    CCopasiMethod(src, pParent)
{}

// virtual
CMoietiesMethod::~CMoietiesMethod()
{}

// virtual
bool CMoietiesMethod::setCallBack(CProcessReport * pCallBack)
{
  // TODO Implement or delete.
  return true;
}

// virtual
bool CMoietiesMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  // TODO Implement or delete.
  return true;
}

// virtual
void CMoietiesMethod::print(std::ostream * ostream) const
  {
    // TODO Implement or delete.
    return;
  }
