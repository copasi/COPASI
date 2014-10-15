// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CCopasiProblem class.
 *  This class is used to describe a task in COPASI. This class is
 *  intended to be used as the parent class for all tasks within COPASI.
 *
 *  Created for COPASI by Stefan Hoops 2003
 */

#include "copasi.h"

#include "CCopasiProblem.h"
#include "model/CMetab.h"
#include "model/CModel.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "CCopasiVector.h"
#include "math/CMathContainer.h"

CCopasiProblem::CCopasiProblem():
  CCopasiParameterGroup("NoName", NULL, "Problem"),
  mType(CTaskEnum::UnsetTask),
  mpContainer(NULL),
  mpCallBack(NULL),
  mpReport(NULL)
{}

CCopasiProblem::CCopasiProblem(const CTaskEnum::Task & type,
                               const CCopasiContainer * pParent):
  CCopasiParameterGroup(CTaskEnum::TaskName[type], pParent, "Problem"),
  mType(type),
  mpContainer(NULL),
  mpCallBack(NULL),
  mpReport(NULL)
{}

CCopasiProblem::CCopasiProblem(const CCopasiProblem & src,
                               const CCopasiContainer * pParent):
  CCopasiParameterGroup(src, pParent),
  mType(src.mType),
  mpContainer(src.mpContainer),
  mpCallBack(src.mpCallBack),
  mpReport(src.mpReport)
{}

CCopasiProblem::~CCopasiProblem() {}

const CTaskEnum::Task & CCopasiProblem::getType() const {return mType;}

void CCopasiProblem::setMathContainer(CMathContainer * pContainer)
{
  if (pContainer != mpContainer)
    {
      mpContainer = pContainer;
      signalMathContainerChanged();
    }
}

// virtual
void CCopasiProblem::signalMathContainerChanged()
{}

CMathContainer * CCopasiProblem::getMathContainer() const
{
  return mpContainer;
}

bool CCopasiProblem::setCallBack(CProcessReport * pCallBack)
{
  mpCallBack = pCallBack;
  return true;
}

// propably for optimization only

bool CCopasiProblem::initialize() {return true;}

bool CCopasiProblem::restore(const bool & /* updateModel */) {return true;}

void CCopasiProblem::print(std::ostream * ostream) const
{*ostream << *this;}

void CCopasiProblem::printResult(std::ostream * ostream) const
{*ostream << "Not implemented.";}

std::ostream &operator<<(std::ostream &os, const CCopasiProblem & o)
{
  os << "Problem Description:" << std::endl;

  CCopasiParameterGroup::parameterGroup::const_iterator it =
    o.CCopasiParameter::getValue().pGROUP->begin();
  CCopasiParameterGroup::parameterGroup::const_iterator end =
    o.CCopasiParameter::getValue().pGROUP->end();

  for (; it != end; ++it)
    {
      (*it)->print(&os);
      os << std::endl;
    }

  return os;
}
