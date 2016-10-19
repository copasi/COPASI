// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ExpressionHandler.h"

/**
 * Replace Expression with the name type of the handler and implement the
 * three methods below.
 */
ExpressionHandler::ExpressionHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Expression)
{
  init();
}

// virtual
ExpressionHandler::~ExpressionHandler()
{}

// virtual
CXMLHandler * ExpressionHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * ExpressionHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * ExpressionHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"Expression", Expression, {BEFORE}},
    {"BEFORE", BEFORE, {Expression, BEFORE}}
  };

  return Elements;
}
