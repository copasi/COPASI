// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfPlotsHandler.h"

/**
 * Replace ListOfPlots with the name type of the handler and implement the
 * three methods below.
 */
ListOfPlotsHandler::ListOfPlotsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfPlots)
{
  init();
}

// virtual
ListOfPlotsHandler::~ListOfPlotsHandler()
{}

// virtual
CXMLHandler * ListOfPlotsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * ListOfPlotsHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * ListOfPlotsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfPlots", ListOfPlots, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfPlots, BEFORE}}
  };

  return Elements;
}
