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

#include "copasi.h"

#include "CMoietiesTask.h"
#include "CMoietiesProblem.h"
#include "CMoietiesMethod.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"

#include "math/CMathContainer.h"

CMoietiesTask::CMoietiesTask(const CDataContainer * pParent,
                             const CTaskEnum::Task & type):
  CCopasiTask(pParent, type)
{
  mpProblem = new CMoietiesProblem(type, this);
  mpMethod = createMethod(CTaskEnum::Method::Householder);
  this->add(mpMethod, true);
}

CMoietiesTask::CMoietiesTask(const CMoietiesTask & src,
                             const CDataContainer * pParent):
  CCopasiTask(src, pParent)
{
  mpProblem = new CMoietiesProblem(* static_cast< CMoietiesProblem * >(src.mpProblem), this);
  mpMethod = createMethod(src.mpMethod->getSubType());
}

// virtual
CMoietiesTask::~CMoietiesTask()
{}

// virtual
bool CMoietiesTask::setCallBack(CProcessReport * pCallBack)
{
  bool success = CCopasiTask::setCallBack(pCallBack);

  if (!mpProblem->setCallBack(pCallBack)) success = false;

  if (!mpMethod->setCallBack(pCallBack)) success = false;

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
