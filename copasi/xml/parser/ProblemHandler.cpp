// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ProblemHandler.h"

/**
 * Replace Problem with the name type of the handler and implement the
 * three methods below.
 */
ProblemHandler::ProblemHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Problem)
{
  init();
}

// virtual
ProblemHandler::~ProblemHandler()
{}

// virtual
CXMLHandler * ProblemHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * ProblemHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * ProblemHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"Problem", Problem, {BEFORE}},
    {"BEFORE", BEFORE, {Problem, BEFORE}}
  };

  return Elements;
}
