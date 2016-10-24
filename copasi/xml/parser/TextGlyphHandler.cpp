// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "TextGlyphHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"

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

  switch (mCurrentElement.first)
    {
      case TextGlyph:
        // TODO CRITICAL Implement me!
        break;

        // TODO CRITICAL Implement me!

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool TextGlyphHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case TextGlyph:
        finished = true;
        // TODO CRITICAL Implement me!
        break;

        // TODO CRITICAL Implement me!

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * TextGlyphHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {TextGlyph, HANDLER_COUNT}},
    {"TextGlyph", TextGlyph, TextGlyph, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
