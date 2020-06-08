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

#include "LineEndingHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CLayout.h"

/**
 * Replace LineEnding with the name type of the handler and implement the
 * three methods below.
 */
LineEndingHandler::LineEndingHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::LineEnding)
{
  init();
}

// virtual
LineEndingHandler::~LineEndingHandler()
{}

// virtual
CXMLHandler * LineEndingHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  const char * Id;
  const char * EnableRotationalMapping;

  switch (mCurrentElement.first)
    {
      case LineEnding:
        Id = mpParser->getAttributeValue("id", papszAttrs);
        EnableRotationalMapping = mpParser->getAttributeValue("enableRotationalMapping", papszAttrs, "true");
        mpData->pLineEnding = mpData->pRenderInformation->createLineEnding();
        mpData->pLineEnding->setId(Id);

        if (!strcmp(EnableRotationalMapping, "true"))
          {
            mpData->pLineEnding->setEnableRotationalMapping(true);
          }
        else
          {
            mpData->pLineEnding->setEnableRotationalMapping(false);
          }

        break;

      case BoundingBox:
      case Group:
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
bool LineEndingHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case LineEnding:
        mpData->pLineEnding = NULL;
        finished = true;
        break;

      case BoundingBox:
        mpData->pLineEnding->setBoundingBox(mpData->pBoundingBox);
        break;

      case Group:
        mpData->pLineEnding->setGroup(mpData->pGroup);
        pdelete(mpData->pGroup);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * LineEndingHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {LineEnding, HANDLER_COUNT}},
    {"LineEnding", LineEnding, LineEnding, {BoundingBox, HANDLER_COUNT}},
    {"BoundingBox", BoundingBox, BoundingBox, {Group, HANDLER_COUNT}}, //  case BoundingBox:
    {"Group", Group, Group, {AFTER, HANDLER_COUNT}}, //  case Group:
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
