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

#include "ReportTargetHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/utilities/CCopasiTask.h"

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
  std::string target;
  bool append;
  bool confirmOverwrite;
  std::string reference;

  switch (mCurrentElement.first)
    {
      case ReportTarget:
        reference = mpParser->getAttributeValue("reference", papszAttrs);
        target = mpParser->getAttributeValue("target", papszAttrs);

        append = mpParser->toBool(mpParser->getAttributeValue("append", papszAttrs, "false"));
        mpData->pCurrentTask->getReport().setAppend(append);
        confirmOverwrite = mpParser->toBool(mpParser->getAttributeValue("confirmOverwrite", papszAttrs, "false"));

        mpData->pCurrentTask->getReport().setConfirmOverwrite(confirmOverwrite);
        mpData->pCurrentTask->getReport().setTarget(target);

        if (mpData->taskReferenceMap.find(reference) == mpData->taskReferenceMap.end())
          {
            mpData->taskReferenceMap[reference] = std::vector<CCopasiTask*>();
          }

        mpData->taskReferenceMap[reference].push_back(mpData->pCurrentTask);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return NULL;
}

// virtual
bool ReportTargetHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case ReportTarget:
        finished = true;
        break;

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
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {ReportTarget, HANDLER_COUNT}},
    {"Report", ReportTarget, ReportTarget, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
