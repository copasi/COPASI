// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/copasi.h"

#include "UNKNOWNHandler.h"
#include "CXMLParser.h"

/**
 * Replace UNKNOWN with the name type of the handler and implement the
 * three methods below.
 */
UNKNOWNHandler::UNKNOWNHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::UNKNOWN),
  mLevel(0)
{
  init();
}

// virtual
UNKNOWNHandler::~UNKNOWNHandler()
{}

// virtual
void UNKNOWNHandler::start(const XML_Char * pszName,
                           const XML_Char ** papszAttrs)
{
  if (mLevel == 0)
    {
      // std::cout << "UNKNOWN" << std::endl;
    }

  processStart(pszName, papszAttrs);
}

// virtual
void UNKNOWNHandler::end(const XML_Char * pszName)
{
  if (processEnd(pszName))
    {
      mpParser->popElementHandler();
      mpParser->onEndElement(pszName);
    }
}

// virtual
CXMLHandler * UNKNOWNHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mLevel++;

  return NULL;
}

// virtual
bool UNKNOWNHandler::processEnd(const XML_Char * pszName)
{
  mLevel--;

  return (mLevel == 0);
}

// virtual
CXMLHandler::sProcessLogic * UNKNOWNHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {UNKNOWN, HANDLER_COUNT}},
    {"UNKNOWN", UNKNOWN, UNKNOWN, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
