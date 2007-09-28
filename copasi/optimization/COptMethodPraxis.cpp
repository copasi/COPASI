// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodPraxis.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: jdada $
//   $Date: 2007/09/28 12:02:28 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "COptMethodPraxis.h"
#include "COptProblem.h"
#include "COptItem.h"
#include "COptTask.h"

#include "parameterFitting/CFitProblem.h"
#include "report/CCopasiObjectReference.h"

COptMethodPraxis::COptMethodPraxis(const CCopasiContainer * pParent):
    COptMethod(CCopasiTask::optimization, CCopasiMethod::Praxis, pParent)
{
  addParameter("Iteration Limit", CCopasiParameter::UINT, (unsigned C_INT32) 200);
  addParameter("Tolerance", CCopasiParameter::DOUBLE, (C_FLOAT64) 1.e-005);

  initObjects();
}

COptMethodPraxis::COptMethodPraxis(const COptMethodPraxis & src,
                                   const CCopasiContainer * pParent):
    COptMethod(src, pParent)
{initObjects();}

COptMethodPraxis::~COptMethodPraxis()
{cleanup();}

void COptMethodPraxis::initObjects()
{
  addObjectReference("Current Iteration", mIteration, CCopasiObject::ValueInt);
}

#ifdef WIN32
// warning C4056: overflow in floating-point constant arithmetic
// warning C4756: overflow in constant arithmetic
# pragma warning (disable: 4056 4756)
#endif

bool COptMethodPraxis::optimise()
{
  if (!initialize()) return false;

  return true;
}

bool COptMethodPraxis::initialize()
{
  cleanup();

  return true;
}

bool COptMethodPraxis::cleanup()
{
  return true;
}
