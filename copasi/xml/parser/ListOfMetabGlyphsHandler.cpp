// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfMetabGlyphsHandler.h"

/**
 * Replace ListOfMetabGlyphs with the name type of the handler and implement the
 * three methods below.
 */
ListOfMetabGlyphsHandler::ListOfMetabGlyphsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfMetabGlyphs)
{
  init();
}

// virtual
ListOfMetabGlyphsHandler::~ListOfMetabGlyphsHandler()
{}

// virtual
CXMLHandler * ListOfMetabGlyphsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * ListOfMetabGlyphsHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * ListOfMetabGlyphsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfMetabGlyphs", ListOfMetabGlyphs, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfMetabGlyphs, BEFORE}}
  };

  return Elements;
}
