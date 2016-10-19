// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "TaskHandler.h"

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

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * TaskHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * TaskHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"Task", Task, {BEFORE}},
    {"BEFORE", BEFORE, {Task, BEFORE}}
  };

  return Elements;
}
