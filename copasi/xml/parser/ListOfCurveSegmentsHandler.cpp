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

#include "ListOfCurveSegmentsHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CLCurve.h"

/**
 * Replace ListOfCurveSegments with the name type of the handler and implement the
 * three methods below.
 */
ListOfCurveSegmentsHandler::ListOfCurveSegmentsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfCurveSegments)
{
  init();

  if (mpData->pLineSegment == NULL)
    {
      mpData->pLineSegment = new CLLineSegment();
    }
}

// virtual
ListOfCurveSegmentsHandler::~ListOfCurveSegmentsHandler()
{
  pdelete(mpData->pLineSegment);
}

// virtual
CXMLHandler * ListOfCurveSegmentsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  const char * type;

  switch (mCurrentElement.first)
    {
      case ListOfCurveSegments:
        break;

      case CurveSegment:
        type = mpParser->getAttributeValue("xsi:type", papszAttrs);
        mpData->pLineSegment->setIsBezier(!strcmp(type, "CubicBezier"));

        if (mpData->pLineSegment->isBezier())
          pHandlerToCall = getHandler(CubicBezier);
        else
          pHandlerToCall = getHandler(LineSegment);

        break;

      case LineSegment:
        mpData->pLineSegment->setIsBezier(false);
        pHandlerToCall = getHandler(LineSegment);
        break;

      case CubicBezier:
        mpData->pLineSegment->setIsBezier(true);
        pHandlerToCall = getHandler(CubicBezier);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool ListOfCurveSegmentsHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case ListOfCurveSegments:
        finished = true;
        break;

      case CurveSegment:
      case LineSegment:
      case CubicBezier:
        mpData->pCurve->addCurveSegment(mpData->pLineSegment);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfCurveSegmentsHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {ListOfCurveSegments, HANDLER_COUNT}},
    {"ListOfCurveSegments", ListOfCurveSegments, ListOfCurveSegments, {CurveSegment, LineSegment, CubicBezier, AFTER, HANDLER_COUNT}},
    {"CurveSegment", CurveSegment, LineSegment, {CurveSegment, LineSegment, CubicBezier, AFTER, HANDLER_COUNT}},
    {"LineSegment", LineSegment, LineSegment, {CurveSegment, LineSegment, CubicBezier, AFTER, HANDLER_COUNT}},
    {"CubicBezier", CubicBezier, CubicBezier, {CurveSegment, LineSegment, CubicBezier, AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
