// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfGradientDefinitionsHandler.h"

/**
 * Replace ListOfGradientDefinitions with the name type of the handler and implement the
 * three methods below.
 */
ListOfGradientDefinitionsHandler::ListOfGradientDefinitionsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfGradientDefinitions)
{
  init();
}

// virtual
ListOfGradientDefinitionsHandler::~ListOfGradientDefinitionsHandler()
{}

// virtual
CXMLHandler * ListOfGradientDefinitionsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ListOfGradientDefinitionsHandler::processEnd(const XML_Char * pszName)
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
CXMLHandler::sProcessLogic * ListOfGradientDefinitionsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfGradientDefinitions", ListOfGradientDefinitions, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfGradientDefinitions, BEFORE}}
  };

  return Elements;
}
