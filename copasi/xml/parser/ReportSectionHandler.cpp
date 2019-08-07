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

#include "ReportSectionHandler.h"

#include "copasi/copasi.h"

#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/report/CReportDefinition.h"
/**
 * Replace Header with the name type of the handler and implement the
 * three methods below.
 */
ReportSectionHandler::ReportSectionHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ReportSection),
  mpSectionContent(NULL)
{
  init();
}

// virtual
ReportSectionHandler::~ReportSectionHandler()
{}

// virtual
CXMLHandler * ReportSectionHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  switch (mCurrentElement.first)
    {
      case Header:
        mpSectionContent = mpData->pReport->getHeaderAddr();;
        break;

      case Body:
        mpSectionContent = mpData->pReport->getBodyAddr();
        break;

      case Footer:
        mpSectionContent = mpData->pReport->getFooterAddr();
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
bool ReportSectionHandler::processEnd(const XML_Char * pszName)
{
  assert(mpSectionContent != NULL);

  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Header:
      case Body:
      case Footer:
        mpSectionContent = NULL;
        finished = true;
        break;

      case Object:
        mpSectionContent->push_back(CCommonName(mpData->CharacterData));
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ReportSectionHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Header, Body, Footer, HANDLER_COUNT}},
    {"Header", Header, ReportSection, {Object, AFTER, HANDLER_COUNT}},
    {"Body", Body, ReportSection, {Object, AFTER, HANDLER_COUNT}},
    {"Footer", Footer, ReportSection, {Object, AFTER, HANDLER_COUNT}},
    {"Object", Object, Object, {Object, AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}

void ReportSectionHandler::setSectionContent(std::vector< CRegisteredCommonName > * pSectionContent)
{
  mpSectionContent = pSectionContent;
}
