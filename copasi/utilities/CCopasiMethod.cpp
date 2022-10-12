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

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CCopasiMethod class.
 *  This class is used to describe a task in COPASI. This class is
 *  intended to be used as the parent class for all methods within COPASI.
 *
 *  Created for COPASI by Stefan Hoops 2003
 */

#include "copasi/copasi.h"

#include "copasi/utilities/CCopasiMethod.h"
#include "copasi/utilities/CCopasiMessage.h"
#include "copasi/utilities/CCopasiProblem.h"

#include "copasi/math/CMathContainer.h"

CCopasiMethod::CCopasiMethod(const CDataContainer * pParent,
                             const CTaskEnum::Method & methodType,
                             const CTaskEnum::Task & taskType):
  CCopasiParameterGroup(CTaskEnum::MethodName[methodType], pParent, "Method"),
  mTaskType(taskType),
  mSubType(methodType),
  mpContainer(NULL),
  mProcessReport()
{}

CCopasiMethod::CCopasiMethod(const CCopasiMethod & src,
                             const CDataContainer * pParent):
  CCopasiParameterGroup(src, pParent),
  mTaskType(src.mTaskType),
  mSubType(src.mSubType),
  mpContainer(src.mpContainer),
  mProcessReport(src.mProcessReport)
{}

CCopasiMethod & CCopasiMethod::operator=(const CCopasiMethod & rhs)
{
  CCopasiParameterGroup::operator=(rhs);

  // Check for assignment to itself
  if (this == &rhs) return *this;

  mTaskType = rhs.mTaskType;
  mSubType = rhs.mSubType;
  mpContainer = rhs.mpContainer;
  mProcessReport = rhs.mProcessReport;

  return *this;
}

CCopasiMethod::~CCopasiMethod() {}

void CCopasiMethod::setMathContainer(CMathContainer * pContainer)
{
  mpContainer = pContainer;
  signalMathContainerChanged();
}

// virtual
void CCopasiMethod::signalMathContainerChanged()
{}

CMathContainer * CCopasiMethod::getMathContainer() const
{
  return mpContainer;
}

bool CCopasiMethod::setCallBack(CProcessReportLevel callBack)
{
  mProcessReport = callBack;
  return true;
}

const CProcessReportLevel & CCopasiMethod::getCallBack() const
{
  return mProcessReport;
}

void CCopasiMethod::clearCallBack()
{
  setCallBack(NULL);
}

const CTaskEnum::Task & CCopasiMethod::getType() const {return mTaskType;}

// void CCopasiMethod::setType(const CTaskEnum::Task & type) {mTaskType = type;}

const CTaskEnum::Method & CCopasiMethod::getSubType() const
{return mSubType;}

// void CCopasiMethod::setSubType(const CTaskEnum::Method & subType)
// {mSubType = subType;}

//virtual
bool CCopasiMethod::isValidProblem(const CCopasiProblem * pProblem)
{
  if (pProblem == NULL)
    {
      //no problem
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCCopasiMethod + 2);
      return false;
    }

  if (mpContainer == NULL)
    {
      //no model
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCCopasiMethod + 3);
      return false;
    }

  if (mpContainer->getEvents().size())
    {
      if (mTaskType == CTaskEnum::Task::lyap)
        {
          CCopasiMessage(CCopasiMessage::ERROR, MCCopasiMethod + 4, "Lyapunov Exponents");
          return false;
        }

      if (mTaskType == CTaskEnum::Task::tssAnalysis)
        {
          CCopasiMessage(CCopasiMessage::ERROR, MCCopasiMethod + 4, "Time Scale Separation Analysis");
          return false;
        }

      if (mTaskType == CTaskEnum::Task::lna)
        {
          CCopasiMessage(CCopasiMessage::ERROR, MCCopasiMethod + 4, "Linear Noise Approximation");
          return false;
        }
    }

  return true;
}

void CCopasiMethod::load(CReadConfig & /* configBuffer */,
                         CReadConfig::Mode /* mode */)
{fatalError();}

void CCopasiMethod::print(std::ostream * ostream) const
{*ostream << *this;}

std::ostream &operator<<(std::ostream &os, const CCopasiMethod & o)
{
  os << "Method: " << o.getObjectName() << std::endl;

  CCopasiParameterGroup::elements::const_iterator it = o.beginIndex();
  CCopasiParameterGroup::elements::const_iterator end = o.endIndex();

  for (; it != end; ++it)
    {
      (*it)->print(&os);
      os << std::endl;
    }

  return os;
}

void CCopasiMethod::printResult(std::ostream * ostream) const
{*ostream << " Not implemented.";}
