// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "PolygonHandler.h"

/**
 * Replace Polygon with the name type of the handler and implement the
 * three methods below.
 */
PolygonHandler::PolygonHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Polygon)
{
  init();
}

// virtual
PolygonHandler::~PolygonHandler()
{}

// virtual
CXMLHandler * PolygonHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool PolygonHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case Polygon:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * PolygonHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"Polygon", Polygon, {BEFORE}},
    {"BEFORE", BEFORE, {Polygon, BEFORE}}
  };

  return Elements;
}
