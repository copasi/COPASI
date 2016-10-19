// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "SubstrateHandler.h"

/**
 * Replace Substrate with the name type of the handler and implement the
 * three methods below.
 */
SubstrateHandler::SubstrateHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Substrate)
{
  init();
}

// virtual
SubstrateHandler::~SubstrateHandler()
{}

// virtual
CXMLHandler * SubstrateHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * SubstrateHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * SubstrateHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"Substrate", Substrate, {BEFORE}},
    {"BEFORE", BEFORE, {Substrate, BEFORE}}
  };

  return Elements;
}
