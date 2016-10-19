// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfProductsHandler.h"

/**
 * Replace ListOfProducts with the name type of the handler and implement the
 * three methods below.
 */
ListOfProductsHandler::ListOfProductsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfProducts)
{
  init();
}

// virtual
ListOfProductsHandler::~ListOfProductsHandler()
{}

// virtual
CXMLHandler * ListOfProductsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * ListOfProductsHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * ListOfProductsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfProducts", ListOfProducts, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfProducts, BEFORE}}
  };

  return Elements;
}
