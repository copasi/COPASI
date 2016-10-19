// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfCompartmentsHandler.h"

/**
 * Replace ListOfCompartments with the name type of the handler and implement the
 * three methods below.
 */
ListOfCompartmentsHandler::ListOfCompartmentsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfCompartments)
{
  init();
}

// virtual
ListOfCompartmentsHandler::~ListOfCompartmentsHandler()
{}

// virtual
CXMLHandler * ListOfCompartmentsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ListOfCompartmentsHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case ListOfCompartments:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfCompartmentsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfCompartments", ListOfCompartments, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfCompartments, BEFORE}}
  };

  return Elements;
}
