// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "GUIHandler.h"

/**
 * Replace GUI with the name type of the handler and implement the
 * three methods below.
 */
GUIHandler::GUIHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::GUI)
{
  init();
}

// virtual
GUIHandler::~GUIHandler()
{}

// virtual
CXMLHandler * GUIHandler::processStart(const XML_Char * pszName,
                                       const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool GUIHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case GUI:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * GUIHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"GUI", GUI, {BEFORE}},
    {"BEFORE", BEFORE, {GUI, BEFORE}}
  };

  return Elements;
}
