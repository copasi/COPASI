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

#include "copasi/copasi.h"

#include "CMoietiesTask.h"
#include "CMoietiesProblem.h"
#include "CMoietiesMethod.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/report/CReport.h"

#include "copasi/math/CMathContainer.h"
#include "copasi/utilities/CMethodFactory.h"

CMoietiesTask::CMoietiesTask(const CDataContainer * pParent,
                             const CTaskEnum::Task & type):
  CCopasiTask(pParent, type)
{
  mpMethod = CMethodFactory::create(getType(), CTaskEnum::Method::Householder, this);
}

CMoietiesTask::CMoietiesTask(const CMoietiesTask & src,
                             const CDataContainer * pParent):
  CCopasiTask(src, pParent)
{}

// virtual
CMoietiesTask::~CMoietiesTask()
{}

// virtual
bool CMoietiesTask::setCallBack(CProcessReportLevel callBack)
{
  bool success = CCopasiTask::setCallBack(callBack);

  if (!mpProblem->setCallBack(mProcessReport)) success = false;

  if (!mpMethod->setCallBack(mProcessReport)) success = false;

  return success;
}

// virtual
bool CMoietiesTask::initialize(const OutputFlag & of,
                               COutputHandler * pOutputHandler,
                               std::ostream * pOstream)
{
  CMoietiesProblem * pProblem = dynamic_cast<CMoietiesProblem *>(mpProblem);
  CMoietiesMethod * pMethod = dynamic_cast<CMoietiesMethod *>(mpMethod);

  if (!pProblem || !pMethod) return false;

  pMethod->setProblem(pProblem);

  // Default initialization
  bool success = CCopasiTask::initialize(of, pOutputHandler, pOstream);

  success &= mpMethod->isValidProblem(mpProblem);

  return success;
}

// virtual
bool CMoietiesTask::process(const bool & /* useInitialValues */)
{
  bool success = true;

  output(COutputInterface::BEFORE);

  success = static_cast< CMoietiesMethod * >(mpMethod)->process();

  // The call to process may modify some object pointers. We therefore
  // have to recompile the output.

  if (mpOutputHandler != NULL)
    {
      CObjectInterface::ContainerList ListOfContainer;
      ListOfContainer.push_back(this);
      ListOfContainer.push_back(mpContainer);

      size_t Size = CCopasiMessage::size();

      mpOutputHandler->compile(ListOfContainer);

      // Remove error messages created by setExpression as this may fail
      // due to incomplete model specification at this time.
      while (CCopasiMessage::size() > Size)
        CCopasiMessage::getLastMessage();
    }

  output(COutputInterface::DURING);
  output(COutputInterface::AFTER);

  return success;
}

// virtual
const CTaskEnum::Method * CMoietiesTask::getValidMethods() const
{
  static const CTaskEnum::Method ValidMethods[] =
  {
    CTaskEnum::Method::Householder,
    CTaskEnum::Method::UnsetMethod
  };

  return ValidMethods;
}
