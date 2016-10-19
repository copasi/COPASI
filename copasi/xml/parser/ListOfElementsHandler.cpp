// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfElementsHandler.h"

/**
 * Replace ListOfElements with the name type of the handler and implement the
 * three methods below.
 */
ListOfElementsHandler::ListOfElementsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfElements)
{
  init();
}

// virtual
ListOfElementsHandler::~ListOfElementsHandler()
{}

// virtual
CXMLHandler * ListOfElementsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * ListOfElementsHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * ListOfElementsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfElements", ListOfElements, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfElements, BEFORE}}
  };

  return Elements;
}
