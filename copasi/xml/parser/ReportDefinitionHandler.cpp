// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

#include "ReportDefinitionHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/utilities/CTaskEnum.h"
#include "copasi/report/CReportDefinitionVector.h"

/**
 * Replace ReportDefinition with the name type of the handler and implement the
 * three methods below.
 */
ReportDefinitionHandler::ReportDefinitionHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ReportDefinition)
{
  init();
}

// virtual
ReportDefinitionHandler::~ReportDefinitionHandler()
{}

// virtual
CXMLHandler * ReportDefinitionHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  const char * Key;
  const char * Name;
  const char * Separator;
  const char * Precision;
  CTaskEnum::Task type;

  switch (mCurrentElement.first)
    {
      case ReportDefinition:
        Key = mpParser->getAttributeValue("key", papszAttrs);
        Name = mpParser->getAttributeValue("name", papszAttrs);
        type = CTaskEnum::TaskXML.toEnum(mpParser->getAttributeValue("taskType", papszAttrs), CTaskEnum::Task::UnsetTask);

        Separator = mpParser->getAttributeValue("separator", papszAttrs, "\t");
        Precision = mpParser->getAttributeValue("precision", papszAttrs, "6");

        // create a new report
        mpData->pReport = new CReportDefinition();
        mpData->pReport->setTaskType(type);
        mpData->pReport->setSeparator(Separator);
        mpData->pReport->setPrecision(strToUnsignedInt(Precision));

        {
          // We need to make sure that the name is unique.
          std::string ValidName(Name);
          size_t Index = 1;

          while (mpData->pReportList->getIndex(ValidName) != C_INVALID_INDEX)
            {
              std::ostringstream ValidNameStream;
              ValidNameStream << Name << " " << Index++;
              ValidName = ValidNameStream.str();
            }

          mpData->pReport->setObjectName(ValidName);
        }

        /* We have a new report and add it to the list */
        mpData->pReportList->add(mpData->pReport, true);
        addFix(Key, mpData->pReport);
        break;

      case Comment:
        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

      case Header:
      case Body:
      case Footer:
        mpData->pReport->setIsTable(false);
        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

      case Table:
        mpData->pReport->setIsTable(true);
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
bool ReportDefinitionHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case ReportDefinition:
        finished = true;
        break;

      case Comment:
        // check parameter type CCopasiStaticString
        mpData->pReport->setComment(mpData->CharacterData);
        mpData->CharacterData = "";
        break;

      case Table:
      case Header:
      case Body:
      case Footer:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ReportDefinitionHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {ReportDefinition, HANDLER_COUNT}},
    {"Report", ReportDefinition, ReportDefinition, {Comment, Table, Header, Body, Footer, AFTER, AFTER, HANDLER_COUNT}},
    {"Comment", Comment, Comment, {Table, Header, Body, Footer, AFTER, HANDLER_COUNT}},
    {"Header", Header, ReportSection, {Body, Footer, AFTER, HANDLER_COUNT}},
    {"Body", Body, ReportSection, {Footer, AFTER, HANDLER_COUNT}},
    {"Footer", Footer, ReportSection, {AFTER, HANDLER_COUNT}},
    {"Table", Table, Table, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
