// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfTasksHandler.h"

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

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * ListOfTasksHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * ListOfTasksHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfTasks", ListOfTasks, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfTasks, BEFORE}}
  };

  return Elements;
}
