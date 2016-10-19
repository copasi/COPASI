// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfAssignmentsHandler.h"

/**
 * Replace ListOfAssignments with the name type of the handler and implement the
 * three methods below.
 */
ListOfAssignmentsHandler::ListOfAssignmentsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfAssignments)
{
  init();
}

// virtual
ListOfAssignmentsHandler::~ListOfAssignmentsHandler()
{}

// virtual
CXMLHandler * ListOfAssignmentsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ListOfAssignmentsHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case ListOfAssignments:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfAssignmentsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfAssignments", ListOfAssignments, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfAssignments, BEFORE}}
  };

  return Elements;
}
