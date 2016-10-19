// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "RenderPointHandler.h"

/**
 * Replace RenderPoint with the name type of the handler and implement the
 * three methods below.
 */
RenderPointHandler::RenderPointHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::RenderPoint)
{
  init();
}

// virtual
RenderPointHandler::~RenderPointHandler()
{}

// virtual
CXMLHandler * RenderPointHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * RenderPointHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * RenderPointHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"RenderPoint", RenderPoint, {BEFORE}},
    {"BEFORE", BEFORE, {RenderPoint, BEFORE}}
  };

  return Elements;
}
