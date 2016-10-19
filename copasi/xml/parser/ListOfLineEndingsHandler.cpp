// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfLineEndingsHandler.h"

/**
 * Replace ListOfLineEndings with the name type of the handler and implement the
 * three methods below.
 */
ListOfLineEndingsHandler::ListOfLineEndingsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfLineEndings)
{
  init();
}

// virtual
ListOfLineEndingsHandler::~ListOfLineEndingsHandler()
{}

// virtual
CXMLHandler * ListOfLineEndingsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ListOfLineEndingsHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case ListOfLineEndings:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfLineEndingsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfLineEndings", ListOfLineEndings, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfLineEndings, BEFORE}}
  };

  return Elements;
}
