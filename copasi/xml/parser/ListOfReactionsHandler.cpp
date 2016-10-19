// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfReactionsHandler.h"

/**
 * Replace ListOfReactions with the name type of the handler and implement the
 * three methods below.
 */
ListOfReactionsHandler::ListOfReactionsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfReactions)
{
  init();
}

// virtual
ListOfReactionsHandler::~ListOfReactionsHandler()
{}

// virtual
CXMLHandler * ListOfReactionsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ListOfReactionsHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case ListOfReactions:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfReactionsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfReactions", ListOfReactions, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfReactions, BEFORE}}
  };

  return Elements;
}
