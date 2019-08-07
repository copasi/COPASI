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

#include "RenderCurveHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CLRenderCurve.h"

/**
 * Replace RenderCurve with the name type of the handler and implement the
 * three methods below.
 */
RenderCurveHandler::RenderCurveHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::RenderCurve)
{
  init();
}

// virtual
RenderCurveHandler::~RenderCurveHandler()
{}

// virtual
CXMLHandler * RenderCurveHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  const char * Transform;
  const char * Stroke;
  const char * StrokeWidth;
  const char * StrokeDashArray;
  const char * StartHead;
  const char * EndHead;

  switch (mCurrentElement.first)
    {
      case RenderCurve:
        mpData->pRenderCurve = new CLRenderCurve();

        Transform = mpParser->getAttributeValue("transform", papszAttrs, false);
        Stroke = mpParser->getAttributeValue("stroke", papszAttrs, false);
        StrokeWidth = mpParser->getAttributeValue("stroke-width", papszAttrs, false);
        StrokeDashArray = mpParser->getAttributeValue("stroke-dasharray", papszAttrs, false);
        StartHead = mpParser->getAttributeValue("startHead", papszAttrs, false);
        EndHead = mpParser->getAttributeValue("endHead", papszAttrs, false);

        if (Transform != NULL)
          {
            mpData->pRenderCurve->parseTransformation(Transform);
          }

        if (Stroke != NULL)
          {
            mpData->pRenderCurve->setStroke(Stroke);
          }

        if (StrokeWidth != NULL)
          {
            double width = strToDouble(StrokeWidth, NULL);
            mpData->pRenderCurve->setStrokeWidth(width);
          }

        if (StrokeDashArray != NULL)
          {
            mpData->pRenderCurve->parseDashArray(StrokeDashArray);
          }

        if (StartHead != NULL)
          {
            mpData->pRenderCurve->setStartHead(StartHead);
          }

        if (EndHead != NULL)
          {
            mpData->pRenderCurve->setEndHead(EndHead);
          }

        break;

      case ListOfElements:
        mpData->pListOfCurveElements = mpData->pRenderCurve->getListOfCurveElements();
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
bool RenderCurveHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case RenderCurve:
        finished = true;
        break;

      case ListOfElements:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * RenderCurveHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {RenderCurve, HANDLER_COUNT}},
    {"Curve", RenderCurve, RenderCurve, {ListOfElements, HANDLER_COUNT}},
    {"ListOfElements", ListOfElements, ListOfElements, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
