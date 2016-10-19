// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ModelParameterSetHandler.h"

/**
 * Replace ModelParameterSet with the name type of the handler and implement the
 * three methods below.
 */
ModelParameterSetHandler::ModelParameterSetHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ModelParameterSet)
{
  init();
}

// virtual
ModelParameterSetHandler::~ModelParameterSetHandler()
{}

// virtual
CXMLHandler * ModelParameterSetHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ModelParameterSetHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case ModelParameterSet:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ModelParameterSetHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ModelParameterSet", ModelParameterSet, {BEFORE}},
    {"BEFORE", BEFORE, {ModelParameterSet, BEFORE}}
  };

  return Elements;
}
