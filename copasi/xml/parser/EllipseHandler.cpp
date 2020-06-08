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

#include "EllipseHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CLEllipse.h"

/**
 * Replace Ellipse with the name type of the handler and implement the
 * three methods below.
 */
EllipseHandler::EllipseHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Ellipse)
{
  init();
}

// virtual
EllipseHandler::~EllipseHandler()
{}

// virtual
CXMLHandler * EllipseHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  const char * Transform;
  const char * Stroke;
  const char * StrokeWidth;
  const char * StrokeDashArray;
  const char * Fill;
  const char * FillRule;
  const char * CX;
  const char * CY;
  const char * CZ;
  const char * RX;
  const char * RY;

  switch (mCurrentElement.first)
    {
      case Ellipse:
        Transform = mpParser->getAttributeValue("transform", papszAttrs, false);
        Stroke = mpParser->getAttributeValue("stroke", papszAttrs, false);
        StrokeWidth = mpParser->getAttributeValue("stroke-width", papszAttrs, false);
        StrokeDashArray = mpParser->getAttributeValue("stroke-dasharray", papszAttrs, false);
        Fill = mpParser->getAttributeValue("fill", papszAttrs, false);
        FillRule = mpParser->getAttributeValue("fill-rule", papszAttrs, false);
        CX = mpParser->getAttributeValue("cx", papszAttrs);
        CY = mpParser->getAttributeValue("cy", papszAttrs);
        CZ = mpParser->getAttributeValue("cz", papszAttrs, "0.0");
        RX = mpParser->getAttributeValue("rx", papszAttrs);
        RY = mpParser->getAttributeValue("ry", papszAttrs, RX);
        mpData->pEllipse = new CLEllipse();

        if (Transform != NULL)
          {
            mpData->pEllipse->parseTransformation(Transform);
          }

        if (Stroke != NULL)
          {
            mpData->pEllipse->setStroke(Stroke);
          }

        if (StrokeWidth != NULL)
          {
            double width = strToDouble(StrokeWidth, NULL);
            mpData->pEllipse->setStrokeWidth(width);
          }

        if (StrokeDashArray != NULL)
          {
            mpData->pEllipse->parseDashArray(StrokeDashArray);
          }

        if (Fill != NULL)
          {
            mpData->pEllipse->setFillColor(Fill);
          }

        if (FillRule != NULL)
          {
            std::string f(FillRule);

            if (f == "nonzero")
              {
                mpData->pEllipse->setFillRule(CLGraphicalPrimitive2D::NONZERO);
              }
            else if (f == "evenodd")
              {
                mpData->pEllipse->setFillRule(CLGraphicalPrimitive2D::EVENODD);
              }
            else
              {
                mpData->pEllipse->setFillRule(CLGraphicalPrimitive2D::INHERIT);
              }
          }

        mpData->pEllipse->setCenter3D(CLRelAbsVector(CX), CLRelAbsVector(CY), CLRelAbsVector(CZ));
        mpData->pEllipse->setRadii(CLRelAbsVector(RX), CLRelAbsVector(RY));
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return NULL;
}

// virtual
bool EllipseHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Ellipse:
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
CXMLHandler::sProcessLogic * EllipseHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Ellipse, HANDLER_COUNT}},
    {"Ellipse", Ellipse, Ellipse, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
