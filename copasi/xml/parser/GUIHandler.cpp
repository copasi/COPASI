// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "GUIHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"

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

  switch (mCurrentElement.first)
    {
      case GUI:
        break;

      case ListOfSliders:
        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool GUIHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case GUI:
        finished = true;
        break;

      case ListOfSliders:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * GUIHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {GUI, HANDLER_COUNT}},
    {"GUI", GUI, GUI, {ListOfSliders, AFTER, HANDLER_COUNT}},
    {"ListOfSliders", ListOfSliders, ListOfSliders, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
