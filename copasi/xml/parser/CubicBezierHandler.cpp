// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CubicBezierHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"

#include "layout/CLCurve.h"

/**
 * Replace CubicBezier with the name type of the handler and implement the
 * three methods below.
 */
CubicBezierHandler::CubicBezierHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::CubicBezier)
{
  init();
}

// virtual
CubicBezierHandler::~CubicBezierHandler()
{}

// virtual
CXMLHandler * CubicBezierHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  switch (mCurrentElement.first)
    {
      case CubicBezier:
      case CurveSegment:
        break;

      case Start:
      case End:
      case BasePoint1:
      case BasePoint2:
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
bool CubicBezierHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case CubicBezier:
      case CurveSegment:
        finished = true;
        break;

      case Start:
        mpData->pLineSegment->setStart(*mpData->pPosition);
        break;

      case End:
        mpData->pLineSegment->setEnd(*mpData->pPosition);
        break;

      case BasePoint1:
        mpData->pLineSegment->setBase1(*mpData->pPosition);
        break;

      case BasePoint2:
        mpData->pLineSegment->setBase2(*mpData->pPosition);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * CubicBezierHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {CubicBezier, CurveSegment, HANDLER_COUNT}},
    {"CubicBezier", CubicBezier, CubicBezier, {Start, HANDLER_COUNT}},
    {"CurveSegment", CurveSegment, CubicBezier, {Start, HANDLER_COUNT}},
    {"Start", Start, Point, {End, HANDLER_COUNT}},
    {"End", End, Point, {BasePoint1, HANDLER_COUNT}},
    {"BasePoint1", BasePoint1, Point, {BasePoint2, HANDLER_COUNT}},
    {"BasePoint2", BasePoint2, Point, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
