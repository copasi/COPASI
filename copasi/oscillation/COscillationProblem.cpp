// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi.h"

#include "COscillationProblem.h"

//#include "CopasiDataModel/CDataModel.h"

#include "model/CModel.h"

#include "copasi/core/CDataObjectReference.h"
#include "report/CKeyFactory.h"

#include "utilities/CProcessReport.h"
#include "utilities/CCopasiException.h"

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

bool COscillationProblem::setCallBack(CProcessReport * pCallBack)
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

  mpContainer->compileIfNecessary(mpCallBack);

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
