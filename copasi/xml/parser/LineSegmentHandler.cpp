// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "LineSegmentHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"

#include "layout/CLCurve.h"

/**
 * Replace LineSegment with the name type of the handler and implement the
 * three methods below.
 */
LineSegmentHandler::LineSegmentHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::LineSegment)
{
  init();
}

// virtual
LineSegmentHandler::~LineSegmentHandler()
{}

// virtual
CXMLHandler * LineSegmentHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  switch (mCurrentElement.first)
    {
      case LineSegment:
      case CurveSegment:
        break;

      case Start:
      case End:
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
bool LineSegmentHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case LineSegment:
        finished = true;
        break;

      case Start:
        mpData->pLineSegment->setStart(*mpData->pPosition);
        break;

      case End:
        mpData->pLineSegment->setEnd(*mpData->pPosition);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * LineSegmentHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {LineSegment, CurveSegment, HANDLER_COUNT}},
    {"LineSegment", LineSegment, LineSegment, {Start, HANDLER_COUNT}},
    {"CurveSegment", CurveSegment, LineSegment, {Start, HANDLER_COUNT}},
    {"Start", Start, Point, {End, HANDLER_COUNT}},
    {"End", End, Point, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
