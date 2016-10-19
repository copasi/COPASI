// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CubicBezierHandler.h"

/**
 * Replace CubicBezier with the name type of the handler and implement the
 * three methods below.
 */
CubicBezierHandler::CubicBezierHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::CubicBezier)
{
  init();
}

// virtual
CubicBezierHandler::~CubicBezierHandler()
{}

// virtual
CXMLHandler * CubicBezierHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool CubicBezierHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case CubicBezier:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * CubicBezierHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"CubicBezier", CubicBezier, {BEFORE}},
    {"BEFORE", BEFORE, {CubicBezier, BEFORE}}
  };

  return Elements;
}
