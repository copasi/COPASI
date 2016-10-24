// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ReportTargetHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"

/**
 * Replace ReportTarget with the name type of the handler and implement the
 * three methods below.
 */
ReportTargetHandler::ReportTargetHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ReportTarget)
{
  init();
}

// virtual
ReportTargetHandler::~ReportTargetHandler()
{}

// virtual
CXMLHandler * ReportTargetHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  switch (mCurrentElement.first)
    {
      case ReportTarget:
        // TODO CRITICAL Implement me!
        break;

        // TODO CRITICAL Implement me!

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool ReportTargetHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case ReportTarget:
        finished = true;
        // TODO CRITICAL Implement me!
        break;

        // TODO CRITICAL Implement me!

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ReportTargetHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {ReportTarget, HANDLER_COUNT}},
    {"ReportTarget", ReportTarget, ReportTarget, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
