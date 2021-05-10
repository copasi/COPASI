// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/copasi.h"

#include "TaskHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "ParameterGroupHandler.h"
#include "copasi/utilities/CCopasiTask.h"
#include "copasi/utilities/CCopasiProblem.h"
#include "copasi/utilities/CCopasiMethod.h"
#include "copasi/utilities/CTaskFactory.h"
#include "copasi/model/CModel.h"
#include "copasi/function/CExpression.h"

/**
 * Replace Task with the name type of the handler and implement the
 * three methods below.
 */
TaskHandler::TaskHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Task)
{
  init();
}

// virtual
TaskHandler::~TaskHandler()
{}

// virtual
CXMLHandler * TaskHandler::processStart(const XML_Char * pszName,
                                        const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  const char * Key;
  const char * type;
  CTaskEnum::Task Type;
  bool Scheduled = false;
  bool UpdateModel = false;

  switch (mCurrentElement.first)
    {
      case Task:
        mpData->pCurrentTask = NULL;

        Key = mpParser->getAttributeValue("key", papszAttrs, false);
        type = mpParser->getAttributeValue("type", papszAttrs);
        Type = CTaskEnum::TaskXML.toEnum(type, CTaskEnum::Task::UnsetTask);
        Scheduled = mpParser->toBool(mpParser->getAttributeValue("scheduled", papszAttrs, "false"));
        UpdateModel = mpParser->toBool(mpParser->getAttributeValue("updateModel", papszAttrs, "false"));

        mpData->pCurrentTask = CTaskFactory::create(Type, mpData->pTaskList);

        if (mpData->pCurrentTask != NULL)
          {
            mpData->pCurrentTask->setScheduled(Scheduled);
            mpData->pCurrentTask->setUpdateModel(UpdateModel);
            mpData->pCurrentTask->setMathContainer(&mpData->pModel->getMathContainer());

            if (Key != NULL)
              {
                addFix(Key, mpData->pCurrentTask);
              }
          }
        else
          {
            CCopasiMessage(CCopasiMessage::WARNING, MCXML + 5, type, mpParser->getCurrentLineNumber());
            pHandlerToCall = getHandler(UNKNOWN);
          }

        break;

      case ReportTarget:
      case Method:
        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

      case Problem:
        pHandlerToCall = getHandler(mCurrentElement.second);
        static_cast< ParameterGroupHandler * >(pHandlerToCall)->setDerivedElement(pszName, mpData->pCurrentTask->getProblem());
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool TaskHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Task:
        finished = true;
        break;

      case ReportTarget:
        break;

      case Problem:

        // This is needed for old files containing the objective function as
        // part of the list of function definitions
        if (mpData->pCurrentTask->getType() == CTaskEnum::Task::optimization)
          {
            CCopasiProblem * pProblem = mpData->pCurrentTask->getProblem();
            CCopasiParameter * pParameter = pProblem->getParameter("ObjectiveFunction");

            if (pParameter != NULL)
              {
                if (mpData->mKey2ObjectiveFunction.find(pParameter->getValue< std::string >()) !=
                    mpData->mKey2ObjectiveFunction.end())
                  {
                    std::string Infix = mpData->mKey2ObjectiveFunction[pParameter->getValue< std::string >()]->getInfix();
                    pProblem->setValue("ObjectiveExpression", Infix);
                  }

                pProblem->remove(pParameter);
              }

            std::map< std::string, CExpression * >::iterator it = mpData->mKey2ObjectiveFunction.begin();
            std::map< std::string, CExpression * >::iterator end = mpData->mKey2ObjectiveFunction.end();

            for (; it != end; ++it)
              {
                pdelete(it->second);
              }

            mpData->mKey2ObjectiveFunction.clear();
          }

        mpData->pCurrentTask->getProblem()->elevateChildren();
        break;

      case Method:
        mpData->pCurrentTask->getMethod()->elevateChildren();
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * TaskHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Task, HANDLER_COUNT}},
    {"Task", Task, Task, {ReportTarget, Problem, HANDLER_COUNT}},
    {"Report", ReportTarget, ReportTarget, {Problem, HANDLER_COUNT}},
    {"Problem", Problem, ParameterGroup, {Method, HANDLER_COUNT}},
    {"Method", Method, Method, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
