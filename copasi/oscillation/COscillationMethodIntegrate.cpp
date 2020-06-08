// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

#include "COscillationMethodIntegrate.h"

#include "COscillationProblem.h"
#include "COscillationTask.h"

#include "copasi/core/CDataObjectReference.h"

COscillationMethodIntegrate::COscillationMethodIntegrate():
  COscillationMethod(CCopasiTask::oscillation, CCopasiMethod::oscillationIntegrate)
{
  //  assertParameter("Number of Iterations", CCopasiParameter::Type::UINT, (unsigned C_INT32) 100000);

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
  //  addObjectReference("Current Iteration", mCurrentIteration, CDataObject::ValueInt);
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
