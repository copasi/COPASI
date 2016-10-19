// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "PlotItemHandler.h"

/**
 * Replace PlotItem with the name type of the handler and implement the
 * three methods below.
 */
PlotItemHandler::PlotItemHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::PlotItem)
{
  init();
}

// virtual
PlotItemHandler::~PlotItemHandler()
{}

// virtual
CXMLHandler * PlotItemHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * PlotItemHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * PlotItemHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"PlotItem", PlotItem, {BEFORE}},
    {"BEFORE", BEFORE, {PlotItem, BEFORE}}
  };

  return Elements;
}
