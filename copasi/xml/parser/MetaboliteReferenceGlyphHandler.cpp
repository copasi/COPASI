// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "MetaboliteReferenceGlyphHandler.h"

/**
 * Replace MetaboliteReferenceGlyph with the name type of the handler and implement the
 * three methods below.
 */
MetaboliteReferenceGlyphHandler::MetaboliteReferenceGlyphHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::MetaboliteReferenceGlyph)
{
  init();
}

// virtual
MetaboliteReferenceGlyphHandler::~MetaboliteReferenceGlyphHandler()
{}

// virtual
CXMLHandler * MetaboliteReferenceGlyphHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * MetaboliteReferenceGlyphHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * MetaboliteReferenceGlyphHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"MetaboliteReferenceGlyph", MetaboliteReferenceGlyph, {BEFORE}},
    {"BEFORE", BEFORE, {MetaboliteReferenceGlyph, BEFORE}}
  };

  return Elements;
}
