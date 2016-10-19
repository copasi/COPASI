// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "BasePoint2Handler.h"

/**
 * Replace BasePoint2 with the name type of the handler and implement the
 * three methods below.
 */
BasePoint2Handler::BasePoint2Handler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::BasePoint2)
{
  init();
}

// virtual
BasePoint2Handler::~BasePoint2Handler()
{}

// virtual
CXMLHandler * BasePoint2Handler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool BasePoint2Handler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case BasePoint2:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * BasePoint2Handler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"BasePoint2", BasePoint2, {BEFORE}},
    {"BEFORE", BEFORE, {BasePoint2, BEFORE}}
  };

  return Elements;
}
