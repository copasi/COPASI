// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "LineEndingHandler.h"

/**
 * Replace LineEnding with the name type of the handler and implement the
 * three methods below.
 */
LineEndingHandler::LineEndingHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::LineEnding)
{
  init();
}

// virtual
LineEndingHandler::~LineEndingHandler()
{}

// virtual
CXMLHandler * LineEndingHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * LineEndingHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * LineEndingHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"LineEnding", LineEnding, {BEFORE}},
    {"BEFORE", BEFORE, {LineEnding, BEFORE}}
  };

  return Elements;
}
