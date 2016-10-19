// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ParameterGroupHandler.h"

/**
 * Replace ParameterGroup with the name type of the handler and implement the
 * three methods below.
 */
ParameterGroupHandler::ParameterGroupHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ParameterGroup)
{
  init();
}

// virtual
ParameterGroupHandler::~ParameterGroupHandler()
{}

// virtual
CXMLHandler * ParameterGroupHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * ParameterGroupHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * ParameterGroupHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ParameterGroup", ParameterGroup, {BEFORE}},
    {"BEFORE", BEFORE, {ParameterGroup, BEFORE}}
  };

  return Elements;
}
