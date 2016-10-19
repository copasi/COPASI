// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfGlobalRenderInformationHandler.h"

/**
 * Replace ListOfGlobalRenderInformation with the name type of the handler and implement the
 * three methods below.
 */
ListOfGlobalRenderInformationHandler::ListOfGlobalRenderInformationHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfGlobalRenderInformation)
{
  init();
}

// virtual
ListOfGlobalRenderInformationHandler::~ListOfGlobalRenderInformationHandler()
{}

// virtual
CXMLHandler * ListOfGlobalRenderInformationHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * ListOfGlobalRenderInformationHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * ListOfGlobalRenderInformationHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfGlobalRenderInformation", ListOfGlobalRenderInformation, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfGlobalRenderInformation, BEFORE}}
  };

  return Elements;
}
