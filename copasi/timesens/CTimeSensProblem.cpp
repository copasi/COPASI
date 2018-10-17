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

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CTimeSensProblem class.
 *  This class describes the time sensitivities problem, i.e., it allows to specify
 *  for example initial conditions and number of steps.
 *
 */

#include <limits.h>
#include <cmath>
#include <string>

#include "copasi.h"
#include "CTimeSensProblem.h"
#include "model/CModel.h"
//#include "model/CState.h"
#include "CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"

/**
 *  Default constructor.
 */
CTimeSensProblem::CTimeSensProblem(const CDataContainer * pParent):
  CTrajectoryProblem(CTaskEnum::Task::timeSens, pParent)
{
  initializeParameter();
  initObjects();
  CONSTRUCTOR_TRACE;
}

/**
 *  Copy constructor.
 *  @param "const CTimeSensProblem &" src
 */
CTimeSensProblem::CTimeSensProblem(const CTimeSensProblem & src,
                                       const CDataContainer * pParent):
  CTrajectoryProblem(src, pParent)
{
  initializeParameter();
  initObjects();
  CONSTRUCTOR_TRACE;
}

/**
 *  Destructor.
 */
CTimeSensProblem::~CTimeSensProblem()
{DESTRUCTOR_TRACE;}

void CTimeSensProblem::initializeParameter()
{
}

void CTimeSensProblem::initObjects()
{
}

//virtual
bool CTimeSensProblem::elevateChildren()
{
  return CTrajectoryProblem::elevateChildren();
}
