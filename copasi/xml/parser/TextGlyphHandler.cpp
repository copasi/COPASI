// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "TextGlyphHandler.h"

/**
 * Replace TextGlyph with the name type of the handler and implement the
 * three methods below.
 */
TextGlyphHandler::TextGlyphHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::TextGlyph)
{
  init();
}

// virtual
TextGlyphHandler::~TextGlyphHandler()
{}

// virtual
CXMLHandler * TextGlyphHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool TextGlyphHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case TextGlyph:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * TextGlyphHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"TextGlyph", TextGlyph, {BEFORE}},
    {"BEFORE", BEFORE, {TextGlyph, BEFORE}}
  };

  return Elements;
}
