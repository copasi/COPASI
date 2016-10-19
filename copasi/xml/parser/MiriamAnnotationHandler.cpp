// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "MiriamAnnotationHandler.h"

/**
 * Replace MiriamAnnotation with the name type of the handler and implement the
 * three methods below.
 */
MiriamAnnotationHandler::MiriamAnnotationHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::MiriamAnnotation)
{
  init();
}

// virtual
MiriamAnnotationHandler::~MiriamAnnotationHandler()
{}

// virtual
CXMLHandler * MiriamAnnotationHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * MiriamAnnotationHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * MiriamAnnotationHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"MiriamAnnotation", MiriamAnnotation, {BEFORE}},
    {"BEFORE", BEFORE, {MiriamAnnotation, BEFORE}}
  };

  return Elements;
}
