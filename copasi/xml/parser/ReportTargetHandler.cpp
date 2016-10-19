// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ReportTargetHandler.h"

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

  // TODO CRITICAL Implement me!

  return pHandlerToCall;
}

// virtual
bool ReportTargetHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement)
    {
      case ReportTarget:
        finished = true;
        break;

        // TODO CRITICAL Implement me!
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ReportTargetHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"ReportTarget", ReportTarget, {BEFORE}},
    {"BEFORE", BEFORE, {ReportTarget, BEFORE}}
  };

  return Elements;
}
