// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfReportsHandler.h"

/**
 * Replace ListOfReports with the name type of the handler and implement the
 * three methods below.
 */
ListOfReportsHandler::ListOfReportsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfReports)
{
  init();
}

// virtual
ListOfReportsHandler::~ListOfReportsHandler()
{}

// virtual
CXMLHandler * ListOfReportsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * ListOfReportsHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * ListOfReportsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfReports", ListOfReports, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfReports, BEFORE}}
  };

  return Elements;
}
