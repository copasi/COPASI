// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfReactionGlyphsHandler.h"

/**
 * Replace ListOfReactionGlyphs with the name type of the handler and implement the
 * three methods below.
 */
ListOfReactionGlyphsHandler::ListOfReactionGlyphsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfReactionGlyphs)
{
  init();
}

// virtual
ListOfReactionGlyphsHandler::~ListOfReactionGlyphsHandler()
{}

// virtual
CXMLHandler * ListOfReactionGlyphsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * ListOfReactionGlyphsHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * ListOfReactionGlyphsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfReactionGlyphs", ListOfReactionGlyphs, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfReactionGlyphs, BEFORE}}
  };

  return Elements;
}
