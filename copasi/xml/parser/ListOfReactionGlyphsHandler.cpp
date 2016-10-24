// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfReactionGlyphsHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"

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

  switch (mCurrentElement.first)
    {
      case ListOfReactionGlyphs:
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
bool ListOfReactionGlyphsHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case ListOfReactionGlyphs:
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
CXMLHandler::sProcessLogic * ListOfReactionGlyphsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {ListOfReactionGlyphs, HANDLER_COUNT}},
    {"ListOfReactionGlyphs", ListOfReactionGlyphs, ListOfReactionGlyphs, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
