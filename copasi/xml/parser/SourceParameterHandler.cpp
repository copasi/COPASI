// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "SourceParameterHandler.h"

/**
 * Replace SourceParameter with the name type of the handler and implement the
 * three methods below.
 */
SourceParameterHandler::SourceParameterHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::SourceParameter)
{
  init();
}

// virtual
SourceParameterHandler::~SourceParameterHandler()
{}

// virtual
CXMLHandler * SourceParameterHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool SourceParameterHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case COPASI:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * SourceParameterHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"SourceParameter", SourceParameter, {BEFORE}},
    {"BEFORE", BEFORE, {SourceParameter, BEFORE}}
  };

  return Elements;
}
