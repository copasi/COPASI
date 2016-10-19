// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfModifiersHandler.h"

/**
 * Replace ListOfModifiers with the name type of the handler and implement the
 * three methods below.
 */
ListOfModifiersHandler::ListOfModifiersHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfModifiers)
{
  init();
}

// virtual
ListOfModifiersHandler::~ListOfModifiersHandler()
{}

// virtual
CXMLHandler * ListOfModifiersHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ListOfModifiersHandler::processEnd(const XML_Char * pszName)
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
CXMLHandler::sProcessLogic * ListOfModifiersHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfModifiers", ListOfModifiers, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfModifiers, BEFORE}}
  };

  return Elements;
}
