// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "StyleGlobalHandler.h"

/**
 * Replace StyleGlobal with the name type of the handler and implement the
 * three methods below.
 */
StyleGlobalHandler::StyleGlobalHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::StyleGlobal)
{
  init();
}

// virtual
StyleGlobalHandler::~StyleGlobalHandler()
{}

// virtual
CXMLHandler * StyleGlobalHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool StyleGlobalHandler::processEnd(const XML_Char * pszName)
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
CXMLHandler::sProcessLogic * StyleGlobalHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"StyleGlobal", StyleGlobal, {BEFORE}},
    {"BEFORE", BEFORE, {StyleGlobal, BEFORE}}
  };

  return Elements;
}
