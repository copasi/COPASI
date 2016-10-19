// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "InitialExpressionHandler.h"

/**
 * Replace InitialExpression with the name type of the handler and implement the
 * three methods below.
 */
InitialExpressionHandler::InitialExpressionHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::InitialExpression)
{
  init();
}

// virtual
InitialExpressionHandler::~InitialExpressionHandler()
{}

// virtual
CXMLHandler * InitialExpressionHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool InitialExpressionHandler::processEnd(const XML_Char * pszName)
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
CXMLHandler::sProcessLogic * InitialExpressionHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"InitialExpression", InitialExpression, {BEFORE}},
    {"BEFORE", BEFORE, {InitialExpression, BEFORE}}
  };

  return Elements;
}
