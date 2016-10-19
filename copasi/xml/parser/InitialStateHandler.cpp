// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "InitialStateHandler.h"

/**
 * Replace InitialState with the name type of the handler and implement the
 * three methods below.
 */
InitialStateHandler::InitialStateHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::InitialState)
{
  init();
}

// virtual
InitialStateHandler::~InitialStateHandler()
{}

// virtual
CXMLHandler * InitialStateHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool InitialStateHandler::processEnd(const XML_Char * pszName)
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
CXMLHandler::sProcessLogic * InitialStateHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"InitialState", InitialState, {BEFORE}},
    {"BEFORE", BEFORE, {InitialState, BEFORE}}
  };

  return Elements;
}
