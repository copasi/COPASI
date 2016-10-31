// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "TableHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"

#include "report/CReportDefinition.h"

/**
 * Replace Table with the name type of the handler and implement the
 * three methods below.
 */
TableHandler::TableHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Table)
{
  init();
}

// virtual
TableHandler::~TableHandler()
{}

// virtual
CXMLHandler * TableHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  const char * printTitle;

  switch (mCurrentElement.first)
    {
      case Table:
        printTitle = mpParser->getAttributeValue("printTitle", papszAttrs, "false");
        mpData->pReport->setTitle(mpParser->toBool(printTitle));
        break;

      case Object:
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
bool TableHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Table:
        finished = true;
        break;

      case Object:
        mpData->pReport->getTableAddr()->push_back(mpData->CharacterData);
        mpData->CharacterData = "";
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * TableHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Table, HANDLER_COUNT}},
    {"Table", Table, Table, {Object, AFTER, HANDLER_COUNT}},
    {"Object", Object, Object, {Object, AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
