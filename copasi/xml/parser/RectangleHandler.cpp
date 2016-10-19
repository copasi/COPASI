// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "RectangleHandler.h"

/**
 * Replace Rectangle with the name type of the handler and implement the
 * three methods below.
 */
RectangleHandler::RectangleHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Rectangle)
{
  init();
}

// virtual
RectangleHandler::~RectangleHandler()
{}

// virtual
CXMLHandler * RectangleHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool RectangleHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case Rectangle:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * RectangleHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"Rectangle", Rectangle, {BEFORE}},
    {"BEFORE", BEFORE, {Rectangle, BEFORE}}
  };

  return Elements;
}
