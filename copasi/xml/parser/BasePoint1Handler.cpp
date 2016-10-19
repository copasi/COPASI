// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "BasePoint1Handler.h"

/**
 * Replace BasePoint1 with the name type of the handler and implement the
 * three methods below.
 */
BasePoint1Handler::BasePoint1Handler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::BasePoint1)
{
  init();
}

// virtual
BasePoint1Handler::~BasePoint1Handler()
{}

// virtual
CXMLHandler * BasePoint1Handler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool BasePoint1Handler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case BasePoint1:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * BasePoint1Handler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"BasePoint1", BasePoint1, {BEFORE}},
    {"BEFORE", BEFORE, {BasePoint1, BEFORE}}
  };

  return Elements;
}
