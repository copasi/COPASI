// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "RadialGradientHandler.h"

/**
 * Replace RadialGradient with the name type of the handler and implement the
 * three methods below.
 */
RadialGradientHandler::RadialGradientHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::RadialGradient)
{
  init();
}

// virtual
RadialGradientHandler::~RadialGradientHandler()
{}

// virtual
CXMLHandler * RadialGradientHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * RadialGradientHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * RadialGradientHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"RadialGradient", RadialGradient, {BEFORE}},
    {"BEFORE", BEFORE, {RadialGradient, BEFORE}}
  };

  return Elements;
}
