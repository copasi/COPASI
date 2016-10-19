// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "FunctionHandler.h"

/**
 * Replace Function with the name type of the handler and implement the
 * three methods below.
 */
FunctionHandler::FunctionHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Function)
{
  init();
}

// virtual
FunctionHandler::~FunctionHandler()
{}

// virtual
CXMLHandler * FunctionHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * FunctionHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * FunctionHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"Function", Function, {BEFORE}},
    {"BEFORE", BEFORE, {Function, BEFORE}}
  };

  return Elements;
}
