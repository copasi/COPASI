// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "UnitDefinitionHandler.h"

/**
 * Replace UnitDefinition with the name type of the handler and implement the
 * three methods below.
 */
UnitDefinitionHandler::UnitDefinitionHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::UnitDefinition)
{
  init();
}

// virtual
UnitDefinitionHandler::~UnitDefinitionHandler()
{}

// virtual
CXMLHandler * UnitDefinitionHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool UnitDefinitionHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case UnitDefinition:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * UnitDefinitionHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"UnitDefinition", UnitDefinition, {BEFORE}},
    {"BEFORE", BEFORE, {UnitDefinition, BEFORE}}
  };

  return Elements;
}
