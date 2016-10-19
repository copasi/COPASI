// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfSlidersHandler.h"

/**
 * Replace ListOfSliders with the name type of the handler and implement the
 * three methods below.
 */
ListOfSlidersHandler::ListOfSlidersHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfSliders)
{
  init();
}

// virtual
ListOfSlidersHandler::~ListOfSlidersHandler()
{}

// virtual
CXMLHandler * ListOfSlidersHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * ListOfSlidersHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * ListOfSlidersHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfSliders", ListOfSliders, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfSliders, BEFORE}}
  };

  return Elements;
}
