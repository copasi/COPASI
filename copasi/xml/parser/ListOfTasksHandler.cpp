// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfTasksHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"

#include "utilities/CCopasiTask.h"

/**
 * Replace ListOfTasks with the name type of the handler and implement the
 * three methods below.
 */
ListOfTasksHandler::ListOfTasksHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfTasks)
{
  init();
}

// virtual
ListOfTasksHandler::~ListOfTasksHandler()
{}

// virtual
CXMLHandler * ListOfTasksHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  switch (mCurrentElement.first)
    {
      case ListOfTasks:

        if (!mpData->pTaskList)
          {
            mpData->pTaskList = new CCopasiVectorN<CCopasiTask>("TaskList");
          }

        break;

      case Task:
        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool ListOfTasksHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case ListOfTasks:
        finished = true;
        break;

      case Task:
        mpData->pCurrentTask = NULL;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfTasksHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {ListOfTasks, HANDLER_COUNT}},
    {"ListOfTasks", ListOfTasks, ListOfTasks, {Task, AFTER, HANDLER_COUNT}},
    {"Task", Task, Task, {Task, AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
