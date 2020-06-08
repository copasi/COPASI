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

#include "PointHandler.h"

#include "copasi/copasi.h"

#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CLBase.h"

PointHandler::PointHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Point)
{
  init();

  if (mpData->pPosition == NULL)
    {
      mpData->pPosition = new CLPoint();
    }
}

// virtual
PointHandler::~PointHandler()
{
  pdelete(mpData->pPosition);
}

// virtual
CXMLHandler * PointHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  const char * attr;

  switch (mCurrentElement.first)
    {
      case Position:
      case Start:
      case End:
      case BasePoint1:
      case BasePoint2:
        attr = mpParser->getAttributeValue("x", papszAttrs, "0");
        mpData->pPosition->setX(CCopasiXMLInterface::DBL(attr));
        attr = mpParser->getAttributeValue("y", papszAttrs, "0");
        mpData->pPosition->setY(CCopasiXMLInterface::DBL(attr));
        attr = mpParser->getAttributeValue("z", papszAttrs, "0");
        mpData->pPosition->setZ(CCopasiXMLInterface::DBL(attr));

        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return NULL;
}

// virtual
bool PointHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Position:
      case Start:
      case End:
      case BasePoint1:
      case BasePoint2:
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
CXMLHandler::sProcessLogic * PointHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Position, Start, End, BasePoint1, BasePoint2, HANDLER_COUNT}},
    {"Position", Position, Point, {AFTER, HANDLER_COUNT}},
    {"Start", Start, Point, {AFTER, HANDLER_COUNT}},
    {"End", End, Point, {AFTER, HANDLER_COUNT}},
    {"BasePoint1", BasePoint1, Point, {AFTER, HANDLER_COUNT}},
    {"BasePoint2", BasePoint2, Point, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
