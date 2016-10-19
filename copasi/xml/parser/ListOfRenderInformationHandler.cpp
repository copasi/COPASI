// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfRenderInformationHandler.h"

/**
 * Replace ListOfRenderInformation with the name type of the handler and implement the
 * three methods below.
 */
ListOfRenderInformationHandler::ListOfRenderInformationHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfRenderInformation)
{
  init();
}

// virtual
ListOfRenderInformationHandler::~ListOfRenderInformationHandler()
{}

// virtual
CXMLHandler * ListOfRenderInformationHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ListOfRenderInformationHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case ListOfRenderInformation:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfRenderInformationHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ListOfRenderInformation", ListOfRenderInformation, {BEFORE}},
    {"BEFORE", BEFORE, {ListOfRenderInformation, BEFORE}}
  };

  return Elements;
}
