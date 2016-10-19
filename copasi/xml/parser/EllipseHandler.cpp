// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "EllipseHandler.h"

/**
 * Replace Ellipse with the name type of the handler and implement the
 * three methods below.
 */
EllipseHandler::EllipseHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Ellipse)
{
  init();
}

// virtual
EllipseHandler::~EllipseHandler()
{}

// virtual
CXMLHandler * EllipseHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool EllipseHandler::processEnd(const XML_Char * pszName)
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
CXMLHandler::sProcessLogic * EllipseHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"Ellipse", Ellipse, {BEFORE}},
    {"BEFORE", BEFORE, {Ellipse, BEFORE}}
  };

  return Elements;
}
