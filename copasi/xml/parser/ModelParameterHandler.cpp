// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ModelParameterHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"

/**
 * Replace ModelParameter with the name type of the handler and implement the
 * three methods below.
 */
ModelParameterHandler::ModelParameterHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ModelParameter)
{
  init();
}

// virtual
ModelParameterHandler::~ModelParameterHandler()
{}

// virtual
CXMLHandler * ModelParameterHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  switch (mCurrentElement.first)
    {
      case ModelParameter:
        // TODO CRITICAL Implement me!
        break;

        // TODO CRITICAL Implement me!

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool ModelParameterHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case ModelParameter:
        finished = true;
        // TODO CRITICAL Implement me!
        break;

        // TODO CRITICAL Implement me!

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ModelParameterHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {ModelParameter, HANDLER_COUNT}},
    {"ModelParameter", ModelParameter, ModelParameter, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
