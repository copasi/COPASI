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

#include "RectangleHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CLRectangle.h"

/**
 * Replace Rectangle with the name type of the handler and implement the
 * three methods below.
 */
RectangleHandler::RectangleHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Rectangle)
{
  init();
}

// virtual
RectangleHandler::~RectangleHandler()
{}

// virtual
CXMLHandler * RectangleHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  const char * Transform;
  const char * Stroke;
  const char * StrokeWidth;
  const char * StrokeDashArray;
  const char * Fill;
  const char * FillRule;
  const char * X;
  const char * Y;
  const char * Z;
  const char * WIDTH;
  const char * HEIGHT;
  const char * RX;
  const char * RY;

  switch (mCurrentElement.first)
    {
      case Rectangle:
        Transform = mpParser->getAttributeValue("transform", papszAttrs, false);
        Stroke = mpParser->getAttributeValue("stroke", papszAttrs, false);
        StrokeWidth = mpParser->getAttributeValue("stroke-width", papszAttrs, false);
        StrokeDashArray = mpParser->getAttributeValue("stroke-dasharray", papszAttrs, false);
        Fill = mpParser->getAttributeValue("fill", papszAttrs, false);
        FillRule = mpParser->getAttributeValue("fill-rule", papszAttrs, false);
        X = mpParser->getAttributeValue("x", papszAttrs);
        Y = mpParser->getAttributeValue("y", papszAttrs);
        Z = mpParser->getAttributeValue("z", papszAttrs, "0.0");
        WIDTH = mpParser->getAttributeValue("width", papszAttrs);
        HEIGHT = mpParser->getAttributeValue("height", papszAttrs);
        RX = mpParser->getAttributeValue("rx", papszAttrs, "0.0");
        RY = mpParser->getAttributeValue("ry", papszAttrs, "0.0");
        mpData->pRectangle = new CLRectangle();

        if (Transform != NULL)
          {
            mpData->pRectangle->parseTransformation(Transform);
          }

        if (Stroke != NULL)
          {
            mpData->pRectangle->setStroke(Stroke);
          }

        if (StrokeWidth != NULL)
          {
            double width = strToDouble(StrokeWidth, NULL);
            mpData->pRectangle->setStrokeWidth(width);
          }

        if (StrokeDashArray != NULL)
          {
            mpData->pRectangle->parseDashArray(StrokeDashArray);
          }

        if (Fill != NULL)
          {
            mpData->pRectangle->setFillColor(Fill);
          }

        if (FillRule != NULL)
          {
            std::string f(FillRule);

            if (f == "nonzero")
              {
                mpData->pRectangle->setFillRule(CLGraphicalPrimitive2D::NONZERO);
              }
            else if (f == "evenodd")
              {
                mpData->pRectangle->setFillRule(CLGraphicalPrimitive2D::EVENODD);
              }
            else
              {
                mpData->pRectangle->setFillRule(CLGraphicalPrimitive2D::INHERIT);
              }
          }

        mpData->pRectangle->setCoordinatesAndSize(CLRelAbsVector(X), CLRelAbsVector(Y), CLRelAbsVector(Z), CLRelAbsVector(WIDTH), CLRelAbsVector(HEIGHT));
        mpData->pRectangle->setRadii(CLRelAbsVector(RX), CLRelAbsVector(RY));
        // delete the gradient stop again since the add method made a copy
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return NULL;
}

// virtual
bool RectangleHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Rectangle:
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
CXMLHandler::sProcessLogic * RectangleHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Rectangle, HANDLER_COUNT}},
    {"Rectangle", Rectangle, Rectangle, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
