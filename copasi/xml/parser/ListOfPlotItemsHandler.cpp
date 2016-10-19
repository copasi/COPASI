// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfPlotItemsHandler.h"

/**
 * Replace ListOfPlotItems with the name type of the handler and implement the
 * three methods below.
 */
ListOfPlotItemsHandler::ListOfPlotItemsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfPlotItems)
{
  init();
}

// virtual
ListOfPlotItemsHandler::~ListOfPlotItemsHandler()
{}

// virtual
CXMLHandler * ListOfPlotItemsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * ListOfPlotItemsHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * ListOfPlotItemsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfPlotItems", ListOfPlotItems, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfPlotItems, BEFORE}}
  };

  return Elements;
}
