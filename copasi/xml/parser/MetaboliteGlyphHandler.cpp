// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "MetaboliteGlyphHandler.h"

/**
 * Replace MetaboliteGlyph with the name type of the handler and implement the
 * three methods below.
 */
MetaboliteGlyphHandler::MetaboliteGlyphHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::MetaboliteGlyph)
{
  init();
}

// virtual
MetaboliteGlyphHandler::~MetaboliteGlyphHandler()
{}

// virtual
CXMLHandler * MetaboliteGlyphHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool MetaboliteGlyphHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case MetaboliteGlyph:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * MetaboliteGlyphHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"MetaboliteGlyph", MetaboliteGlyph, {BEFORE}},
    {"BEFORE", BEFORE, {MetaboliteGlyph, BEFORE}}
  };

  return Elements;
}
