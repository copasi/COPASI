// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "EndHandler.h"

/**
 * Replace End with the name type of the handler and implement the
 * three methods below.
 */
EndHandler::EndHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::End)
{
  init();
}

// virtual
EndHandler::~EndHandler()
{}

// virtual
CXMLHandler * EndHandler::processStart(const XML_Char * pszName,
                                       const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool EndHandler::processEnd(const XML_Char * pszName)
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
CXMLHandler::sProcessLogic * EndHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"End", End, {BEFORE}},
    {"BEFORE", BEFORE, {End, BEFORE}}
  };

  return Elements;
}
