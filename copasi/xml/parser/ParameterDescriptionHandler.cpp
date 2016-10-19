// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ParameterDescriptionHandler.h"

/**
 * Replace ParameterDescription with the name type of the handler and implement the
 * three methods below.
 */
ParameterDescriptionHandler::ParameterDescriptionHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ParameterDescription)
{
  init();
}

// virtual
ParameterDescriptionHandler::~ParameterDescriptionHandler()
{}

// virtual
CXMLHandler * ParameterDescriptionHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ParameterDescriptionHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case ParameterDescription:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ParameterDescriptionHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ParameterDescription", ParameterDescription, {BEFORE}},
    {"BEFORE", BEFORE, {ParameterDescription, BEFORE}}
  };

  return Elements;
}
