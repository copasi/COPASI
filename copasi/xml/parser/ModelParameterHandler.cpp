// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ModelParameterHandler.h"

/**
 * Replace ModelParameter with the name type of the handler and implement the
 * three methods below.
 */
ModelParameterHandler::ModelParameterHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ModelParameter)
{
  init();
}

// virtual
ModelParameterHandler::~ModelParameterHandler()
{}

// virtual
CXMLHandler * ModelParameterHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * ModelParameterHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * ModelParameterHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ModelParameter", ModelParameter, {BEFORE}},
    {"BEFORE", BEFORE, {ModelParameter, BEFORE}}
  };

  return Elements;
}
