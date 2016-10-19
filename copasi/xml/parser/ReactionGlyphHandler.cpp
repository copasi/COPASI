// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ReactionGlyphHandler.h"

/**
 * Replace ReactionGlyph with the name type of the handler and implement the
 * three methods below.
 */
ReactionGlyphHandler::ReactionGlyphHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ReactionGlyph)
{
  init();
}

// virtual
ReactionGlyphHandler::~ReactionGlyphHandler()
{}

// virtual
CXMLHandler * ReactionGlyphHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ReactionGlyphHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case COPASI:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ReactionGlyphHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ReactionGlyph", ReactionGlyph, {BEFORE}},
    {"BEFORE", BEFORE, {ReactionGlyph, BEFORE}}
  };

  return Elements;
}
