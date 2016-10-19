// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfFunctionsHandler.h"

/**
 * Replace ListOfFunctions with the name type of the handler and implement the
 * three methods below.
 */
ListOfFunctionsHandler::ListOfFunctionsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfFunctions)
{
  init();
}

// virtual
ListOfFunctionsHandler::~ListOfFunctionsHandler()
{}

// virtual
CXMLHandler * ListOfFunctionsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * ListOfFunctionsHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * ListOfFunctionsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfFunctions", ListOfFunctions, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfFunctions, BEFORE}}
  };

  return Elements;
}
