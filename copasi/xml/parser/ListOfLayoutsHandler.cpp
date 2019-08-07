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

#include "ListOfLayoutsHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

/**
 * Replace ListOfLayouts with the name type of the handler and implement the
 * three methods below.
 */
ListOfLayoutsHandler::ListOfLayoutsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfLayouts)
{
  init();
}

// virtual
ListOfLayoutsHandler::~ListOfLayoutsHandler()
{}

// virtual
CXMLHandler * ListOfLayoutsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  switch (mCurrentElement.first)
    {
      case ListOfLayouts:
        break;

      case Layout:
        mpData->LocalRenderInformation = true;
        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

      case ListOfGlobalRenderInformation:
        mpData->LocalRenderInformation = false;
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
bool ListOfLayoutsHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case ListOfLayouts:
        finished = true;
        break;

      case Layout:
      case ListOfGlobalRenderInformation:
        mpData->LocalRenderInformation = true;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfLayoutsHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {ListOfLayouts, HANDLER_COUNT}},
    {"ListOfLayouts", ListOfLayouts, ListOfLayouts, {Layout, ListOfGlobalRenderInformation, AFTER, HANDLER_COUNT}},
    {"Layout", Layout, Layout, {Layout, ListOfGlobalRenderInformation, AFTER, HANDLER_COUNT}},
    {"ListOfGlobalRenderInformation", ListOfGlobalRenderInformation, ListOfGlobalRenderInformation, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
