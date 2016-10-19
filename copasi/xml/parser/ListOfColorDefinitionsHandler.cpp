// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfColorDefinitionsHandler.h"

/**
 * Replace ListOfColorDefinitions with the name type of the handler and implement the
 * three methods below.
 */
ListOfColorDefinitionsHandler::ListOfColorDefinitionsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfColorDefinitions)
{
  init();
}

// virtual
ListOfColorDefinitionsHandler::~ListOfColorDefinitionsHandler()
{}

// virtual
CXMLHandler * ListOfColorDefinitionsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ListOfColorDefinitionsHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case ListOfColorDefinitions:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfColorDefinitionsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfColorDefinitions", ListOfColorDefinitions, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfColorDefinitions, BEFORE}}
  };

  return Elements;
}
