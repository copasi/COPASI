// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/moieties/CMoietiesProblem.cpp,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/09 00:58:16 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <float.h>

#include "copasi.h"

#include "CMoietiesProblem.h"

//  Default constructor
CMoietiesProblem::CMoietiesProblem(const CCopasiTask::Type & type,
                                   const CCopasiContainer * pParent):
    CCopasiProblem(type, pParent)
{}

// copy constructor
CMoietiesProblem::CMoietiesProblem(const CMoietiesProblem& src,
                                   const CCopasiContainer * pParent):
    CCopasiProblem(src, pParent)
{}

// Destructor
CMoietiesProblem::~CMoietiesProblem()
{}

// virtual
bool CMoietiesProblem::setModel(CModel * pModel)
{
  // TODO Implement or delete.
  return true;
}

// virtual
bool CMoietiesProblem::setCallBack(CProcessReport * pCallBack)
{
  // TODO Implement or delete.
  return true;
}

bool CMoietiesProblem::initialize()
{
  // TODO Implement or delete.
  return true;
}

bool CMoietiesProblem::restore(const bool & updateModel)
{
  // TODO Implement or delete.
  return true;
}

void CMoietiesProblem::print(std::ostream * ostream) const
  {
    // TODO Implement or delete.
    return;
  }

void CMoietiesProblem::printResult(std::ostream * ostream) const
  {
    // TODO Implement or delete.
    return;
  }

std::ostream &operator<<(std::ostream &os, const CMoietiesProblem & o)
{
  // TODO Implement or delete.
  return os;
}
