// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "DimensionsHandler.h"

/**
 * Replace Dimensions with the name type of the handler and implement the
 * three methods below.
 */
DimensionsHandler::DimensionsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Dimensions)
{
  init();
}

// virtual
DimensionsHandler::~DimensionsHandler()
{}

// virtual
CXMLHandler * DimensionsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * DimensionsHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * DimensionsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"Dimensions", Dimensions, {BEFORE}},
    {"BEFORE", BEFORE, {Dimensions, BEFORE}}
  };

  return Elements;
}
