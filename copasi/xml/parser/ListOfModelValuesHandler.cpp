// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfModelValuesHandler.h"

/**
 * Replace ListOfModelValues with the name type of the handler and implement the
 * three methods below.
 */
ListOfModelValuesHandler::ListOfModelValuesHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfModelValues)
{
  init();
}

// virtual
ListOfModelValuesHandler::~ListOfModelValuesHandler()
{}

// virtual
CXMLHandler * ListOfModelValuesHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ListOfModelValuesHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case ListOfModelValues:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfModelValuesHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfModelValues", ListOfModelValues, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfModelValues, BEFORE}}
  };

  return Elements;
}
