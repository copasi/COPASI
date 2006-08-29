/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CEFMProblem.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/08/29 20:15:14 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CEFMProblem.h"
//  Default constructor
CEFMProblem::CEFMProblem(const CCopasiContainer * pParent):
    CCopasiProblem(CCopasiTask::optimization, pParent)
{
  initializeParameter();
  initObjects();
}

// copy constructor
CEFMProblem::CEFMProblem(const CEFMProblem& src,
                         const CCopasiContainer * pParent):
    CCopasiProblem(src, pParent)
{
  initializeParameter();
  initObjects();
}

// Destructor
CEFMProblem::~CEFMProblem()
{}

void CEFMProblem::initializeParameter()
{elevateChildren();}

bool CEFMProblem::elevateChildren()
{return true;}

bool CEFMProblem::setCallBack(CProcessReport * pCallBack)
{
  CCopasiProblem::setCallBack(pCallBack);

  return true;
}

void CEFMProblem::initObjects()
{}

bool CEFMProblem::initialize()
{
  return CCopasiProblem::initialize();
}
