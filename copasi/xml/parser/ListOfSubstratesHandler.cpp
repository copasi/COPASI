// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfSubstratesHandler.h"

/**
 * Replace ListOfSubstrates with the name type of the handler and implement the
 * three methods below.
 */
ListOfSubstratesHandler::ListOfSubstratesHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfSubstrates)
{
  init();
}

// virtual
ListOfSubstratesHandler::~ListOfSubstratesHandler()
{}

// virtual
CXMLHandler * ListOfSubstratesHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ListOfSubstratesHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case ListOfSubstrates:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfSubstratesHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfSubstrates", ListOfSubstrates, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfSubstrates, BEFORE}}
  };

  return Elements;
}
