// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "TextHandler.h"

/**
 * Replace Text with the name type of the handler and implement the
 * three methods below.
 */
TextHandler::TextHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Text)
{
  init();
}

// virtual
TextHandler::~TextHandler()
{}

// virtual
CXMLHandler * TextHandler::processStart(const XML_Char * pszName,
                                        const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler * TextHandler::processEnd(const XML_Char * pszName)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
CXMLHandler::sProcessLogic * TextHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"Text", Text, {BEFORE}},
    {"BEFORE", BEFORE, {Text, BEFORE}}
  };

  return Elements;
}
