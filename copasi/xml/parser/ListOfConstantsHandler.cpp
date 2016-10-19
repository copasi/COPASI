// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfConstantsHandler.h"

/**
 * Replace ListOfConstants with the name type of the handler and implement the
 * three methods below.
 */
ListOfConstantsHandler::ListOfConstantsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfConstants)
{
  init();
}

// virtual
ListOfConstantsHandler::~ListOfConstantsHandler()
{}

// virtual
CXMLHandler * ListOfConstantsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ListOfConstantsHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case ListOfConstants:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfConstantsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfConstants", ListOfConstants, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfConstants, BEFORE}}
  };

  return Elements;
}
