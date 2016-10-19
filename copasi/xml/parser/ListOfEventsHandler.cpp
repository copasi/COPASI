// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfEventsHandler.h"

/**
 * Replace ListOfEvents with the name type of the handler and implement the
 * three methods below.
 */
ListOfEventsHandler::ListOfEventsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfEvents)
{
  init();
}

// virtual
ListOfEventsHandler::~ListOfEventsHandler()
{}

// virtual
CXMLHandler * ListOfEventsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ListOfEventsHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case ListOfEvents:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfEventsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfEvents", ListOfEvents, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfEvents, BEFORE}}
  };

  return Elements;
}
