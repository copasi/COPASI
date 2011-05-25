// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/moieties/CMoietiesTask.cpp,v $
//   $Revision: 1.2.16.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/05/25 17:38:00 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CMoietiesTask.h"
#include "CMoietiesProblem.h"
#include "CMoietiesMethod.h"
#include "report/CKeyFactory.h"
#include "report/CReport.h"

#include "model/CModel.h"
#include "model/CState.h"

const unsigned int CMoietiesTask::ValidMethods[] =
{
  CCopasiMethod::Householder,
  CCopasiMethod::unset
};

CMoietiesTask::CMoietiesTask(const CCopasiTask::Type & type,
                             const CCopasiContainer * pParent):
    CCopasiTask(type, pParent)
{
  mpProblem = new CMoietiesProblem(type, this);
  mpMethod = CMoietiesMethod::createMethod();
  this->add(mpMethod, true);
}

CMoietiesTask::CMoietiesTask(const CMoietiesTask & src,
                             const CCopasiContainer * pParent):
    CCopasiTask(src, pParent)
{
  mpProblem = new CMoietiesProblem(* static_cast< CMoietiesProblem * >(src.mpProblem), this);
  mpMethod = CMoietiesMethod::createMethod(src.mpMethod->getSubType());
  this->add(mpMethod, true);
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
      std::vector< CCopasiContainer * > ListOfContainer;
      ListOfContainer.push_back(this);

      CCopasiDataModel* pDataModel = getObjectDataModel();
      assert(pDataModel != NULL);

      size_t Size = CCopasiMessage::size();

      mpOutputHandler->compile(ListOfContainer, pDataModel);

      // Remove error messages created by setExpression as this may fail
      // due to incomplete model specification at this time.
      while (CCopasiMessage::size() > Size)
        CCopasiMessage::getLastMessage();
    }

  output(COutputInterface::AFTER);

  return success;
}

// virtual
bool CMoietiesTask::restore()
{
  mpProblem->getModel()->updateInitialValues();
  return true;
}

bool CMoietiesTask::setMethodType(const int & type)
{
  CCopasiMethod::SubType Type = (CCopasiMethod::SubType) type;

  if (mpMethod->getSubType() == Type) return true;

  pdelete(mpMethod);

  mpMethod = createMethod(Type);
  this->add(mpMethod, true);

  return true;
}

// virtual
CCopasiMethod * CMoietiesTask::createMethod(const int & type) const
{
  CCopasiMethod::SubType Type = (CCopasiMethod::SubType) type;

  return CMoietiesMethod::createMethod(Type);
}
