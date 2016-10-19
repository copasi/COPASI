// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfTextGlyphsHandler.h"

/**
 * Replace ListOfTextGlyphs with the name type of the handler and implement the
 * three methods below.
 */
ListOfTextGlyphsHandler::ListOfTextGlyphsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfTextGlyphs)
{
  init();
}

// virtual
ListOfTextGlyphsHandler::~ListOfTextGlyphsHandler()
{}

// virtual
CXMLHandler * ListOfTextGlyphsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ListOfTextGlyphsHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case ListOfTextGlyphs:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfTextGlyphsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfTextGlyphs", ListOfTextGlyphs, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfTextGlyphs, BEFORE}}
  };

  return Elements;
}
