// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "StateTemplateVariableHandler.h"

/**
 * Replace StateTemplateVariable with the name type of the handler and implement the
 * three methods below.
 */
StateTemplateVariableHandler::StateTemplateVariableHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::StateTemplateVariable)
{
  init();
}

// virtual
StateTemplateVariableHandler::~StateTemplateVariableHandler()
{}

// virtual
CXMLHandler * StateTemplateVariableHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * StateTemplateVariableHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * StateTemplateVariableHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"StateTemplateVariable", StateTemplateVariable, {BEFORE}},
    {"BEFORE", BEFORE, {StateTemplateVariable, BEFORE}}
  };

  return Elements;
}
