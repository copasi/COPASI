// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ColorDefinitionHandler.h"

/**
 * Replace ColorDefinition with the name type of the handler and implement the
 * three methods below.
 */
ColorDefinitionHandler::ColorDefinitionHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ColorDefinition)
{
  init();
}

// virtual
ColorDefinitionHandler::~ColorDefinitionHandler()
{}

// virtual
CXMLHandler * ColorDefinitionHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ColorDefinitionHandler::processEnd(const XML_Char * pszName)
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
CXMLHandler::sProcessLogic * ColorDefinitionHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ColorDefinition", ColorDefinition, {BEFORE}},
    {"BEFORE", BEFORE, {ColorDefinition, BEFORE}}
  };

  return Elements;
}
