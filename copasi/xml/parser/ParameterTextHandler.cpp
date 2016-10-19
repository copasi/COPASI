// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ParameterTextHandler.h"

/**
 * Replace ParameterText with the name type of the handler and implement the
 * three methods below.
 */
ParameterTextHandler::ParameterTextHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ParameterText)
{
  init();
}

// virtual
ParameterTextHandler::~ParameterTextHandler()
{}

// virtual
CXMLHandler * ParameterTextHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ParameterTextHandler::processEnd(const XML_Char * pszName)
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
CXMLHandler::sProcessLogic * ParameterTextHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ParameterText", ParameterText, {BEFORE}},
    {"BEFORE", BEFORE, {ParameterText, BEFORE}}
  };

  return Elements;
}
