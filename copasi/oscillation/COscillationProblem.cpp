// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/oscillation/COscillationProblem.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/11/11 16:47:54 $
// End CVS Header
// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "COscillationProblem.h"

//#include "CopasiDataModel/CCopasiDataModel.h"

#include "model/CModel.h"

#include "report/CCopasiObjectReference.h"
#include "report/CKeyFactory.h"

#include "utilities/CProcessReport.h"
#include "utilities/CCopasiException.h"

//  Default constructor
COscillationProblem::COscillationProblem(const CCopasiTask::Type & type,
    const CCopasiContainer * pParent):
    CCopasiProblem(type, pParent)
{
  initializeParameter();
  initObjects();
}

// copy constructor
COscillationProblem::COscillationProblem(const COscillationProblem& src,
    const CCopasiContainer * pParent):
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
  //    assertParameter("Maximize", CCopasiParameter::BOOL, false)-> getValue().pBOOL;

  //  mpGrpItems = assertGroup("OptimizationItemList");

  elevateChildren();
}

bool COscillationProblem::elevateChildren()
{
  return true;
}

bool COscillationProblem::setModel(CModel * pModel)
{
  mpModel = pModel;
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
  //  addObjectReference("Function Evaluations", mCounter, CCopasiObject::ValueInt);
}

bool COscillationProblem::initialize()
{

  if (!mpModel) return false;
  mpModel->compileIfNecessary(mpCallBack);

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
