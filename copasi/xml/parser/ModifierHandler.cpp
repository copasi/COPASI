// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ModifierHandler.h"

/**
 * Replace Modifier with the name type of the handler and implement the
 * three methods below.
 */
ModifierHandler::ModifierHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Modifier)
{
  init();
}

// virtual
ModifierHandler::~ModifierHandler()
{}

// virtual
CXMLHandler * ModifierHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ModifierHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case Modifier:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ModifierHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"Modifier", Modifier, {BEFORE}},
    {"BEFORE", BEFORE, {Modifier, BEFORE}}
  };

  return Elements;
}
