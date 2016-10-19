// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "RenderInformationHandler.h"

/**
 * Replace RenderInformation with the name type of the handler and implement the
 * three methods below.
 */
RenderInformationHandler::RenderInformationHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::RenderInformation)
{
  init();
}

// virtual
RenderInformationHandler::~RenderInformationHandler()
{}

// virtual
CXMLHandler * RenderInformationHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool RenderInformationHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case RenderInformation:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * RenderInformationHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"RenderInformation", RenderInformation, {BEFORE}},
    {"BEFORE", BEFORE, {RenderInformation, BEFORE}}
  };

  return Elements;
}
