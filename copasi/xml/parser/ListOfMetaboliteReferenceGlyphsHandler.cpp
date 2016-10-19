// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfMetaboliteReferenceGlyphsHandler.h"

/**
 * Replace ListOfMetaboliteReferenceGlyphs with the name type of the handler and implement the
 * three methods below.
 */
ListOfMetaboliteReferenceGlyphsHandler::ListOfMetaboliteReferenceGlyphsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfMetaboliteReferenceGlyphs)
{
  init();
}

// virtual
ListOfMetaboliteReferenceGlyphsHandler::~ListOfMetaboliteReferenceGlyphsHandler()
{}

// virtual
CXMLHandler * ListOfMetaboliteReferenceGlyphsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ListOfMetaboliteReferenceGlyphsHandler::processEnd(const XML_Char * pszName)
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
CXMLHandler::sProcessLogic * ListOfMetaboliteReferenceGlyphsHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfMetaboliteReferenceGlyphs", ListOfMetaboliteReferenceGlyphs, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfMetaboliteReferenceGlyphs, BEFORE}}
  };

  return Elements;
}
