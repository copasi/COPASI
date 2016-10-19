// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfUnitDefinitionsHandler.h"

/**
 * Replace ListOfUnitDefinitions with the name type of the handler and implement the
 * three methods below.
 */
ListOfUnitDefinitionsHandler::ListOfUnitDefinitionsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfUnitDefinitions)
{
  init();
}

// virtual
ListOfUnitDefinitionsHandler::~ListOfUnitDefinitionsHandler()
{}

// virtual
CXMLHandler * ListOfUnitDefinitionsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ListOfUnitDefinitionsHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case ListOfUnitDefinitions:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfUnitDefinitionsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfUnitDefinitions", ListOfUnitDefinitions, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfUnitDefinitions, BEFORE}}
  };

  return Elements;
}
