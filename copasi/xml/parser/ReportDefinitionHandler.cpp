// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ReportDefinitionHandler.h"

/**
 * Replace ReportDefinition with the name type of the handler and implement the
 * three methods below.
 */
ReportDefinitionHandler::ReportDefinitionHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ReportDefinition)
{
  init();
}

// virtual
ReportDefinitionHandler::~ReportDefinitionHandler()
{}

// virtual
CXMLHandler * ReportDefinitionHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * ReportDefinitionHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * ReportDefinitionHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ReportDefinition", ReportDefinition, {BEFORE}},
    {"BEFORE", BEFORE, {ReportDefinition, BEFORE}}
  };

  return Elements;
}
