// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ModelParameterGroupHandler.h"

/**
 * Replace ModelParameterGroup with the name type of the handler and implement the
 * three methods below.
 */
ModelParameterGroupHandler::ModelParameterGroupHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ModelParameterGroup)
{
  init();
}

// virtual
ModelParameterGroupHandler::~ModelParameterGroupHandler()
{}

// virtual
CXMLHandler * ModelParameterGroupHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ModelParameterGroupHandler::processEnd(const XML_Char * pszName)
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
CXMLHandler::sProcessLogic * ModelParameterGroupHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ModelParameterGroup", ModelParameterGroup, {BEFORE}},
    {"BEFORE", BEFORE, {ModelParameterGroup, BEFORE}}
  };

  return Elements;
}
