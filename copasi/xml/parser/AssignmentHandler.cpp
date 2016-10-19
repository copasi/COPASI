// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "AssignmentHandler.h"

/**
 * Replace Assignment with the name type of the handler and implement the
 * three methods below.
 */
AssignmentHandler::AssignmentHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Assignment)
{
  init();
}

// virtual
AssignmentHandler::~AssignmentHandler()
{}

// virtual
CXMLHandler * AssignmentHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool AssignmentHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case Assignment:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * AssignmentHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"Assignment", Assignment, {BEFORE}},
    {"BEFORE", BEFORE, {Assignment, BEFORE}}
  };

  return Elements;
}
