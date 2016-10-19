// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfCurveSegmentsHandler.h"

/**
 * Replace ListOfCurveSegments with the name type of the handler and implement the
 * three methods below.
 */
ListOfCurveSegmentsHandler::ListOfCurveSegmentsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfCurveSegments)
{
  init();
}

// virtual
ListOfCurveSegmentsHandler::~ListOfCurveSegmentsHandler()
{}

// virtual
CXMLHandler * ListOfCurveSegmentsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * ListOfCurveSegmentsHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * ListOfCurveSegmentsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfCurveSegments", ListOfCurveSegments, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfCurveSegments, BEFORE}}
  };

  return Elements;
}
