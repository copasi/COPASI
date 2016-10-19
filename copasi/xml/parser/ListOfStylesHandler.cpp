// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfStylesHandler.h"

/**
 * Replace ListOfStyles with the name type of the handler and implement the
 * three methods below.
 */
ListOfStylesHandler::ListOfStylesHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfStyles)
{
  init();
}

// virtual
ListOfStylesHandler::~ListOfStylesHandler()
{}

// virtual
CXMLHandler * ListOfStylesHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ListOfStylesHandler::processEnd(const XML_Char * pszName)
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
CXMLHandler::sProcessLogic * ListOfStylesHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfStyles", ListOfStyles, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfStyles, BEFORE}}
  };

  return Elements;
}
