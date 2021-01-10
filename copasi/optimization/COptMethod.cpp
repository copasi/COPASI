// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  COptMethod class
 *  This class describes the interface to all optimization methods.
 *  The various method like RandomSearch or GA have to be derived from
 *  this class.
 *
 *  Created for COPASI by Stefan Hoops 2002
 */

#include <limits.h>

#include "copasi/copasi.h"

#include "copasi/optimization/COptTask.h"
#include "copasi/optimization/COptMethod.h"
#include "copasi/optimization/COptProblem.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/commandline/CConfigurationFile.h"

COptMethod::COptMethod(const CDataContainer * pParent,
                       const CTaskEnum::Method & methodType,
                       const CTaskEnum::Task & taskType)
  : CCopasiMethod(pParent, methodType, taskType)
  , mpParentTask(NULL)
  , mLogVerbosity(0)
  , mMethodLog()
  , mProblemContext(NULL)
  , mMathContext(NULL)
{
  assertParameter("Log Verbosity", CCopasiParameter::Type::UINT, (unsigned C_INT32) 0, eUserInterfaceFlag::editable);
}

COptMethod::COptMethod(const COptMethod & src,
                       const CDataContainer * pParent)
  : CCopasiMethod(src, pParent)
  , mpParentTask(src.mpParentTask)
  , mLogVerbosity(src.mLogVerbosity)
  , mMethodLog(src.mMethodLog)
  , mProblemContext(src.mProblemContext.master())
  , mMathContext(src.mMathContext.master())
{
  mProblemContext.setMathContext(mMathContext);
}

//YOHE: seems "virtual" cannot be outside of class declaration
COptMethod::~COptMethod()
{}

void COptMethod::setProblem(COptProblem * pProblem)
{
  mProblemContext.setMaster(pProblem);
  mProblemContext.setMathContext(mMathContext);
}

//virtual C_INT32 COptMethod::Optimise(C_FLOAT64 (*func) (void))
bool COptMethod::optimise(void)
{
  return false;
}

bool COptMethod::initialize()
{
  if (mProblemContext.master() == NULL)
    return false;

  mpParentTask = dynamic_cast<COptTask *>(getObjectParent());

  if (!mpParentTask) return false;

  //new log
  mLogVerbosity = getValue< unsigned C_INT32 >("Log Verbosity");
  mMethodLog = COptLog();

  return true;
}

// virtual
void COptMethod::signalMathContainerChanged()
{
  mMathContext.setMaster(mpContainer);
  mProblemContext.setMathContext(mMathContext);
}

bool COptMethod::cleanup()
{return true;}

//virtual
bool COptMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (!CCopasiMethod::isValidProblem(pProblem)) return false;

  const COptProblem * pTP = dynamic_cast<const COptProblem *>(pProblem);

  if (!pTP)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, "Problem is not an optimization problem.");
      return false;
    }

  return true;
}

unsigned C_INT32 COptMethod::getMaxLogVerbosity() const
{
  return 0;
}

const COptLog &COptMethod::getMethodLog() const
{
  return mMethodLog;
}
