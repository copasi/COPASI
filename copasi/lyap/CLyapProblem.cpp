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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CLyapProblem class.
 */

#include <cmath>
#include <string>

#include "copasi/copasi.h"
#include "CLyapProblem.h"
#include "CLyapTask.h"
#include "copasi/model/CModel.h"
//#include "copasi/model/CState.h"
#include "copasi/CopasiDataModel/CDataModel.h"

/**
 *  Default constructor.
 */
CLyapProblem::CLyapProblem(const CDataContainer * pParent):
  CCopasiProblem(CTaskEnum::Task::lyap, pParent),
  mpExponentNumber(NULL),
  //mpTimeSeriesRequested(NULL),
  mpDivergenceRequested(NULL),
  mpTransientTime(NULL)
{
  initializeParameter();
  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CLyapProblem &" src
 */
CLyapProblem::CLyapProblem(const CLyapProblem & src,
                           const CDataContainer * pParent):
  CCopasiProblem(src, pParent),
  mpExponentNumber(NULL),
  //mpTimeSeriesRequested(NULL),
  mpDivergenceRequested(NULL),
  mpTransientTime(NULL)
{
  initializeParameter();
  CONSTRUCTOR_TRACE;
}

/**
 *  Destructor.
 */
CLyapProblem::~CLyapProblem()
{DESTRUCTOR_TRACE;}

bool CLyapProblem::elevateChildren()
{
  return true;
}

void CLyapProblem::initializeParameter()
{
  mpExponentNumber =
    assertParameter("ExponentNumber", CCopasiParameter::Type::UINT, (unsigned C_INT32) 3);
  mpDivergenceRequested =
    assertParameter("DivergenceRequested", CCopasiParameter::Type::BOOL, (bool) true);
  mpTransientTime =
    assertParameter("TransientTime", CCopasiParameter::Type::DOUBLE, (C_FLOAT64) 0.0);

  elevateChildren();
}

void CLyapProblem::setExponentNumber(const unsigned C_INT32 & number)
{
  *mpExponentNumber = number;
}

const unsigned C_INT32 & CLyapProblem::getExponentNumber() const
{return *mpExponentNumber;}

void CLyapProblem::setTransientTime(const C_FLOAT64 & startTime)
{
  *mpTransientTime = startTime;
}

const C_FLOAT64 & CLyapProblem::getTransientTime() const
{return *mpTransientTime;}

/*void CLyapProblem::setTimeSeriesRequested(bool flag)
{
  *mpTimeSeriesRequested = flag;
}

bool CLyapProblem::timeSeriesRequested() const
  {return *mpTimeSeriesRequested;}
 */

void CLyapProblem::setDivergenceRequested(bool flag)
{
  *mpDivergenceRequested = flag;
}

bool CLyapProblem::divergenceRequested() const
{return *mpDivergenceRequested;}

void CLyapProblem::printResult(std::ostream * ostream) const
{
  CLyapTask* parent = dynamic_cast<CLyapTask*>(getObjectParent());

  if (!parent) return;

  parent->printResult(ostream);
}
