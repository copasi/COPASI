// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "StateTemplateHandler.h"

/**
 * Replace StateTemplate with the name type of the handler and implement the
 * three methods below.
 */
StateTemplateHandler::StateTemplateHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::StateTemplate)
{
  init();
}

// virtual
StateTemplateHandler::~StateTemplateHandler()
{}

// virtual
CXMLHandler * StateTemplateHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * StateTemplateHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * StateTemplateHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"StateTemplate", StateTemplate, {BEFORE}},
    {"BEFORE", BEFORE, {StateTemplate, BEFORE}}
  };

  return Elements;
}
