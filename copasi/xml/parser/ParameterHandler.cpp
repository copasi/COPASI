// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ParameterHandler.h"

/**
 * Replace Parameter with the name type of the handler and implement the
 * three methods below.
 */
ParameterHandler::ParameterHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Parameter)
{
  init();
}

// virtual
ParameterHandler::~ParameterHandler()
{}

// virtual
CXMLHandler * ParameterHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * ParameterHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * ParameterHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"Parameter", Parameter, {BEFORE}},
    {"BEFORE", BEFORE, {Parameter, BEFORE}}
  };

  return Elements;
}
