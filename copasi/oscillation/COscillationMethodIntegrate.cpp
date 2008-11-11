// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/oscillation/COscillationMethodIntegrate.cpp,v $
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

#include "COscillationMethodIntegrate.h"

#include "COscillationProblem.h"
#include "COscillationTask.h"

#include "report/CCopasiObjectReference.h"

COscillationMethodIntegrate::COscillationMethodIntegrate():
    COscillationMethod(CCopasiTask::oscillation, CCopasiMethod::oscillationIntegrate)
{
  //  addParameter("Number of Iterations", CCopasiParameter::UINT, (unsigned C_INT32) 100000);

  initObjects();
}

COscillationMethodIntegrate::COscillationMethodIntegrate(const COscillationMethodIntegrate & src):
    COscillationMethod(src)
{
  initObjects();
}

COscillationMethodIntegrate::~COscillationMethodIntegrate()
{
  cleanup();
}

void COscillationMethodIntegrate::initObjects()
{
  //  addObjectReference("Current Iteration", mCurrentIteration, CCopasiObject::ValueInt);
}

bool COscillationMethodIntegrate::initialize()
{
  cleanup();

  if (!COscillationMethod::initialize()) return false;

  //  mIterations = * getValue("Number of Iterations").pUINT;

  return true;
}

bool COscillationMethodIntegrate::run()
{
  return false;
}
