// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ModelValueHandler.h"

/**
 * Replace ModelValue with the name type of the handler and implement the
 * three methods below.
 */
ModelValueHandler::ModelValueHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ModelValue)
{
  init();
}

// virtual
ModelValueHandler::~ModelValueHandler()
{}

// virtual
CXMLHandler * ModelValueHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ModelValueHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case ModelValue:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ModelValueHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ModelValue", ModelValue, {BEFORE}},
    {"BEFORE", BEFORE, {ModelValue, BEFORE}}
  };

  return Elements;
}
