// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfLayoutsHandler.h"

/**
 * Replace ListOfLayouts with the name type of the handler and implement the
 * three methods below.
 */
ListOfLayoutsHandler::ListOfLayoutsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfLayouts)
{
  init();
}

// virtual
ListOfLayoutsHandler::~ListOfLayoutsHandler()
{}

// virtual
CXMLHandler * ListOfLayoutsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ListOfLayoutsHandler::processEnd(const XML_Char * pszName)
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
CXMLHandler::sProcessLogic * ListOfLayoutsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfLayouts", ListOfLayouts, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfLayouts, BEFORE}}
  };

  return Elements;
}
