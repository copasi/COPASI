// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "NoiseExpressionHandler.h"

/**
 * Replace NoiseExpression with the name type of the handler and implement the
 * three methods below.
 */
NoiseExpressionHandler::NoiseExpressionHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::NoiseExpression)
{
  init();
}

// virtual
NoiseExpressionHandler::~NoiseExpressionHandler()
{}

// virtual
CXMLHandler * NoiseExpressionHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool NoiseExpressionHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case NoiseExpression:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * NoiseExpressionHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"NoiseExpression", NoiseExpression, {BEFORE}},
    {"BEFORE", BEFORE, {NoiseExpression, BEFORE}}
  };

  return Elements;
}
