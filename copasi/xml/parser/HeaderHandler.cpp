// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "HeaderHandler.h"

/**
 * Replace Header with the name type of the handler and implement the
 * three methods below.
 */
HeaderHandler::HeaderHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Header)
{
  init();
}

// virtual
HeaderHandler::~HeaderHandler()
{}

// virtual
CXMLHandler * HeaderHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * HeaderHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * HeaderHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"Header", Header, {BEFORE}},
    {"BEFORE", BEFORE, {Header, BEFORE}}
  };

  return Elements;
}
