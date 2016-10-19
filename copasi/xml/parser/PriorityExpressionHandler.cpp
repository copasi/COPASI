// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "PriorityExpressionHandler.h"

/**
 * Replace PriorityExpression with the name type of the handler and implement the
 * three methods below.
 */
PriorityExpressionHandler::PriorityExpressionHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::PriorityExpression)
{
  init();
}

// virtual
PriorityExpressionHandler::~PriorityExpressionHandler()
{}

// virtual
CXMLHandler * PriorityExpressionHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * PriorityExpressionHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * PriorityExpressionHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"PriorityExpression", PriorityExpression, {BEFORE}},
    {"BEFORE", BEFORE, {PriorityExpression, BEFORE}}
  };

  return Elements;
}
