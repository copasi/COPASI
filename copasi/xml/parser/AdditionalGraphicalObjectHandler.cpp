// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "AdditionalGraphicalObjectHandler.h"

/**
 * Replace AdditionalGraphicalObject with the name type of the handler and implement the
 * three methods below.
 */
AdditionalGraphicalObjectHandler::AdditionalGraphicalObjectHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::AdditionalGraphicalObject)
{
  init();
}

// virtual
AdditionalGraphicalObjectHandler::~AdditionalGraphicalObjectHandler()
{}

// virtual
CXMLHandler * AdditionalGraphicalObjectHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool AdditionalGraphicalObjectHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case AdditionalGraphicalObject:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * AdditionalGraphicalObjectHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"AdditionalGraphicalObject", AdditionalGraphicalObject, {BEFORE}},
    {"BEFORE", BEFORE, {AdditionalGraphicalObject, BEFORE}}
  };

  return Elements;
}
