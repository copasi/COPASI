// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ReactionHandler.h"

/**
 * Replace Reaction with the name type of the handler and implement the
 * three methods below.
 */
ReactionHandler::ReactionHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Reaction)
{
  init();
}

// virtual
ReactionHandler::~ReactionHandler()
{}

// virtual
CXMLHandler * ReactionHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * ReactionHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * ReactionHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"Reaction", Reaction, {BEFORE}},
    {"BEFORE", BEFORE, {Reaction, BEFORE}}
  };

  return Elements;
}
