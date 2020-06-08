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

#include "PolygonHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CLPolygon.h"

PolygonHandler::PolygonHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Polygon)
{
  init();
}

// virtual
PolygonHandler::~PolygonHandler()
{}

// virtual
CXMLHandler * PolygonHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  const char * Transform;
  const char * Stroke;
  const char * StrokeWidth;
  const char * StrokeDashArray;
  const char * Fill;
  const char * FillRule;

  switch (mCurrentElement.first)
    {
      case Polygon:
        mpData->pPolygon =  new CLPolygon();

        Transform = mpParser->getAttributeValue("transform", papszAttrs, false);
        Stroke = mpParser->getAttributeValue("stroke", papszAttrs, false);
        StrokeWidth = mpParser->getAttributeValue("stroke-width", papszAttrs, false);
        StrokeDashArray = mpParser->getAttributeValue("stroke-dasharray", papszAttrs, false);
        Fill = mpParser->getAttributeValue("fill", papszAttrs, false);
        FillRule = mpParser->getAttributeValue("fill-rule", papszAttrs, false);

        if (Transform != NULL)
          {
            mpData->pPolygon->parseTransformation(Transform);
          }

        if (Stroke != NULL)
          {
            mpData->pPolygon->setStroke(Stroke);
          }

        if (StrokeWidth != NULL)
          {
            double width = strToDouble(StrokeWidth, NULL);
            mpData->pPolygon->setStrokeWidth(width);
          }

        if (StrokeDashArray != NULL)
          {
            mpData->pPolygon->parseDashArray(StrokeDashArray);
          }

        if (Fill != NULL)
          {
            mpData->pPolygon->setFillColor(Fill);
          }

        if (FillRule != NULL)
          {
            std::string f(FillRule);

            if (f == "nonzero")
              {
                mpData->pPolygon->setFillRule(CLGraphicalPrimitive2D::NONZERO);
              }
            else if (f == "evenodd")
              {
                mpData->pPolygon->setFillRule(CLGraphicalPrimitive2D::EVENODD);
              }
            else
              {
                mpData->pPolygon->setFillRule(CLGraphicalPrimitive2D::INHERIT);
              }
          }

        break;

      case ListOfElements:
        mpData->pListOfCurveElements = mpData->pPolygon->getListOfElements();
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
bool PolygonHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Polygon:
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
CXMLHandler::sProcessLogic * PolygonHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Polygon, HANDLER_COUNT}},
    {"Polygon", Polygon, Polygon, {ListOfElements, HANDLER_COUNT}},
    {"ListOfElements", ListOfElements, ListOfElements, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
