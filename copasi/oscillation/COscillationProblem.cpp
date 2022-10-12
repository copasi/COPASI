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

#include "COscillationProblem.h"

//#include "copasi/CopasiDataModel/CDataModel.h"

#include "copasi/model/CModel.h"

#include "copasi/core/CDataObjectReference.h"
#include "copasi/report/CKeyFactory.h"

#include "copasi/utilities/CProcessReport.h"
#include "copasi/utilities/CCopasiException.h"

//  Default constructor
COscillationProblem::COscillationProblem(const CTaskEnum::Task & type,
    const CDataContainer * pParent):
  CCopasiProblem(type, pParent)
{
  initializeParameter();
  initObjects();
}

// copy constructor
COscillationProblem::COscillationProblem(const COscillationProblem& src,
    const CDataContainer * pParent):
  CCopasiProblem(src, pParent)
{
  initializeParameter();
  initObjects();
}

// Destructor
COscillationProblem::~COscillationProblem()
{}

void COscillationProblem::initializeParameter()
{
  //  mpParmMaximize =
  //    assertParameter("Maximize", CCopasiParameter::Type::BOOL, false)-> getValue().pBOOL;

  //  mpGrpItems = assertGroup("OptimizationItemList");

  elevateChildren();
}

bool COscillationProblem::elevateChildren()
{
  return true;
}

bool COscillationProblem::setCallBack(CProcessReportLevel callBack)
{
  CCopasiProblem::setCallBack(pCallBack);

  if (pCallBack)
    {}

  return true;
}

void COscillationProblem::initObjects()
{
  //  addObjectReference("Function Evaluations", mCounter, CDataObject::ValueInt);
}

bool COscillationProblem::initialize()
{

  if (!mpContainer) return false;

  mpContainer->compileIfNecessary(mProcessReport);

  bool success = true;

  return success;
}

void COscillationProblem::print(std::ostream * ostream) const
{*ostream << *this;}

void COscillationProblem::printResult(std::ostream * ostream) const
{
  std::ostream & os = *ostream;

  //TODO
}

std::ostream &operator<<(std::ostream &os, const COscillationProblem & o)
{
  os << "Problem Description:" << std::endl;
  os << "not implemented yet" << std::endl;
  //TODO

  return os;
}
