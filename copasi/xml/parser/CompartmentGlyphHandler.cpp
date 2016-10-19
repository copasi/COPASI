// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CompartmentGlyphHandler.h"

/**
 * Replace CompartmentGlyph with the name type of the handler and implement the
 * three methods below.
 */
CompartmentGlyphHandler::CompartmentGlyphHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::CompartmentGlyph)
{
  init();
}

// virtual
CompartmentGlyphHandler::~CompartmentGlyphHandler()
{}

// virtual
CXMLHandler * CompartmentGlyphHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * CompartmentGlyphHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * CompartmentGlyphHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"CompartmentGlyph", CompartmentGlyph, {BEFORE}},
    {"BEFORE", BEFORE, {CompartmentGlyph, BEFORE}}
  };

  return Elements;
}
