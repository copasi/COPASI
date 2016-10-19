// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "DelayExpressionHandler.h"

/**
 * Replace DelayExpression with the name type of the handler and implement the
 * three methods below.
 */
DelayExpressionHandler::DelayExpressionHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::DelayExpression)
{
  init();
}

// virtual
DelayExpressionHandler::~DelayExpressionHandler()
{}

// virtual
CXMLHandler * DelayExpressionHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool DelayExpressionHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case COPASI:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * DelayExpressionHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"DelayExpression", DelayExpression, {BEFORE}},
    {"BEFORE", BEFORE, {DelayExpression, BEFORE}}
  };

  return Elements;
}
