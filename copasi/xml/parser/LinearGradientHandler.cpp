// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "LinearGradientHandler.h"

/**
 * Replace LinearGradient with the name type of the handler and implement the
 * three methods below.
 */
LinearGradientHandler::LinearGradientHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::LinearGradient)
{
  init();
}

// virtual
LinearGradientHandler::~LinearGradientHandler()
{}

// virtual
CXMLHandler * LinearGradientHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool LinearGradientHandler::processEnd(const XML_Char * pszName)
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
CXMLHandler::sProcessLogic * LinearGradientHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"LinearGradient", LinearGradient, {BEFORE}},
    {"BEFORE", BEFORE, {LinearGradient, BEFORE}}
  };

  return Elements;
}
