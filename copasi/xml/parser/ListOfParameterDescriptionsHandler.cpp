// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfParameterDescriptionsHandler.h"

/**
 * Replace ListOfParameterDescriptions with the name type of the handler and implement the
 * three methods below.
 */
ListOfParameterDescriptionsHandler::ListOfParameterDescriptionsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfParameterDescriptions)
{
  init();
}

// virtual
ListOfParameterDescriptionsHandler::~ListOfParameterDescriptionsHandler()
{}

// virtual
CXMLHandler * ListOfParameterDescriptionsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ListOfParameterDescriptionsHandler::processEnd(const XML_Char * pszName)
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
CXMLHandler::sProcessLogic * ListOfParameterDescriptionsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfParameterDescriptions", ListOfParameterDescriptions, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfParameterDescriptions, BEFORE}}
  };

  return Elements;
}
