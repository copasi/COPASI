// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "UnsupportedAnnotationHandler.h"

/**
 * Replace UnsupportedAnnotation with the name type of the handler and implement the
 * three methods below.
 */
UnsupportedAnnotationHandler::UnsupportedAnnotationHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::UnsupportedAnnotation)
{
  init();
}

// virtual
UnsupportedAnnotationHandler::~UnsupportedAnnotationHandler()
{}

// virtual
CXMLHandler * UnsupportedAnnotationHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * UnsupportedAnnotationHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * UnsupportedAnnotationHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"UnsupportedAnnotation", UnsupportedAnnotation, {BEFORE}},
    {"BEFORE", BEFORE, {UnsupportedAnnotation, BEFORE}}
  };

  return Elements;
}
