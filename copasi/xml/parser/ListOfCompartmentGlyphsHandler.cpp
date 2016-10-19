// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfCompartmentGlyphsHandler.h"

/**
 * Replace ListOfCompartmentGlyphs with the name type of the handler and implement the
 * three methods below.
 */
ListOfCompartmentGlyphsHandler::ListOfCompartmentGlyphsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfCompartmentGlyphs)
{
  init();
}

// virtual
ListOfCompartmentGlyphsHandler::~ListOfCompartmentGlyphsHandler()
{}

// virtual
CXMLHandler * ListOfCompartmentGlyphsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * ListOfCompartmentGlyphsHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * ListOfCompartmentGlyphsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfCompartmentGlyphs", ListOfCompartmentGlyphs, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfCompartmentGlyphs, BEFORE}}
  };

  return Elements;
}
