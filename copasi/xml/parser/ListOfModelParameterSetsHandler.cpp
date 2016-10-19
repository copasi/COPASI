// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfModelParameterSetsHandler.h"

/**
 * Replace ListOfModelParameterSets with the name type of the handler and implement the
 * three methods below.
 */
ListOfModelParameterSetsHandler::ListOfModelParameterSetsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfModelParameterSets)
{
  init();
}

// virtual
ListOfModelParameterSetsHandler::~ListOfModelParameterSetsHandler()
{}

// virtual
CXMLHandler * ListOfModelParameterSetsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ListOfModelParameterSetsHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case ListOfModelParameterSets:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfModelParameterSetsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfModelParameterSets", ListOfModelParameterSets, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfModelParameterSets, BEFORE}}
  };

  return Elements;
}
