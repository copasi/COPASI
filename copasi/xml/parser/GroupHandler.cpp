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

#include "GroupHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CLayout.h"
#include "copasi/layout/CLRenderCurve.h"
#include "copasi/layout/CLPolygon.h"
#include "copasi/layout/CLRectangle.h"
#include "copasi/layout/CLEllipse.h"
#include "copasi/layout/CLImage.h"
#include "copasi/layout/CLText.h"

/**
 * Replace Group with the name type of the handler and implement the
 * three methods below.
 */
GroupHandler::GroupHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Group),
  mGroupStack()
{
  init();
}

// virtual
GroupHandler::~GroupHandler()
{}

// virtual
CXMLHandler * GroupHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  const char * Transform;
  const char * Stroke;
  const char * StrokeWidth;
  const char * StrokeDashArray;
  const char * Fill;
  const char * FillRule;
  const char * FontFamily;
  const char * FontSize;
  const char * FontWeight;
  const char * FontStyle;
  const char * TextAnchor;
  const char * VTextAnchor;
  const char * StartHead;
  const char * EndHead;

  switch (mCurrentElement.first)
    {
      case Group:
        Transform = mpParser->getAttributeValue("transform", papszAttrs, false);
        Stroke = mpParser->getAttributeValue("stroke", papszAttrs, false);
        StrokeWidth = mpParser->getAttributeValue("stroke-width", papszAttrs, false);
        StrokeDashArray = mpParser->getAttributeValue("stroke-dasharray", papszAttrs, false);
        Fill = mpParser->getAttributeValue("fill", papszAttrs, false);
        FillRule = mpParser->getAttributeValue("fill-rule", papszAttrs, false);
        FontFamily = mpParser->getAttributeValue("font-family", papszAttrs, false);
        FontSize = mpParser->getAttributeValue("font-size", papszAttrs, false);
        FontWeight = mpParser->getAttributeValue("font-weight", papszAttrs, false);
        FontStyle = mpParser->getAttributeValue("font-style", papszAttrs, false);
        TextAnchor = mpParser->getAttributeValue("text-anchor", papszAttrs, false);
        VTextAnchor = mpParser->getAttributeValue("vtext-anchor", papszAttrs, false);
        StartHead = mpParser->getAttributeValue("startHead", papszAttrs, false);
        EndHead = mpParser->getAttributeValue("endHead", papszAttrs, false);

        mpData->pGroup = new CLGroup();
        mGroupStack.push(mpData->pGroup);

        if (Transform != NULL)
          {
            mpData->pGroup->parseTransformation(Transform);
          }

        if (Stroke != NULL)
          {
            mpData->pGroup->setStroke(Stroke);
          }

        if (StrokeWidth != NULL)
          {
            double width = strToDouble(StrokeWidth, NULL);
            mpData->pGroup->setStrokeWidth(width);
          }

        if (StrokeDashArray != NULL)
          {
            mpData->pGroup->parseDashArray(StrokeDashArray);
          }

        if (Fill != NULL)
          {
            mpData->pGroup->setFillColor(Fill);
          }

        if (FillRule != NULL)
          {
            std::string f(FillRule);

            if (f == "nonzero")
              {
                mpData->pGroup->setFillRule(CLGraphicalPrimitive2D::NONZERO);
              }
            else if (f == "evenodd")
              {
                mpData->pGroup->setFillRule(CLGraphicalPrimitive2D::EVENODD);
              }
            else
              {
                mpData->pGroup->setFillRule(CLGraphicalPrimitive2D::INHERIT);
              }
          }

        if (FontFamily != NULL)
          {
            mpData->pGroup->setFontFamily(FontFamily);
          }

        if (FontSize != NULL)
          {
            mpData->pGroup->setFontSize(CLRelAbsVector(FontSize));
          }

        if (FontStyle != NULL)
          {
            std::string s(FontStyle);

            if (s == "normal")
              {
                mpData->pGroup->setFontStyle(CLText::STYLE_NORMAL);
              }
            else if (s == "italic")
              {
                mpData->pGroup->setFontStyle(CLText::STYLE_ITALIC);
              }
          }

        if (FontWeight != NULL)
          {
            std::string s(FontWeight);

            if (s == "normal")
              {
                mpData->pGroup->setFontWeight(CLText::WEIGHT_NORMAL);
              }
            else if (s == "bold")
              {
                mpData->pGroup->setFontWeight(CLText::WEIGHT_BOLD);
              }
          }

        if (TextAnchor != NULL)
          {
            std::string s(TextAnchor);

            if (s == "start")
              {
                mpData->pGroup->setTextAnchor(CLText::ANCHOR_START);
              }
            else if (s == "middle")
              {
                mpData->pGroup->setTextAnchor(CLText::ANCHOR_MIDDLE);
              }
            else if (s == "end")
              {
                mpData->pGroup->setTextAnchor(CLText::ANCHOR_END);
              }
          }

        if (VTextAnchor != NULL)
          {
            std::string s(VTextAnchor);

            if (s == "top")
              {
                mpData->pGroup->setVTextAnchor(CLText::ANCHOR_TOP);
              }
            else if (s == "middle")
              {
                mpData->pGroup->setVTextAnchor(CLText::ANCHOR_MIDDLE);
              }
            else if (s == "bottom")
              {
                mpData->pGroup->setVTextAnchor(CLText::ANCHOR_BOTTOM);
              }
          }

        if (StartHead != NULL)
          {
            mpData->pGroup->setStartHead(StartHead);
          }

        if (EndHead != NULL)
          {
            mpData->pGroup->setEndHead(EndHead);
          }

        assert(mpData->pGroup != NULL);
        break;

        // a group can have many different children
      case Curve:
      case RenderText:
      case Rectangle:
      case Polygon:
      case Ellipse:
      case Image:
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
bool GroupHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Group:
        finished = (mLevel == 0);

        if (mLevel > 0)
          {
            CLGroup * pGroup = mpData->pGroup;
            mGroupStack.pop();
            mpData->pGroup = mGroupStack.top();
            mpData->pGroup->addChildElement(pGroup);

            // delete the group element again since the add/set methods made a copy
            delete pGroup;
          }

        break;

      case Curve:
        mpData->pGroup->addChildElement(mpData->pRenderCurve);
        pdelete(mpData->pRenderCurve);
        break;

      case Polygon:
        mpData->pGroup->addChildElement(mpData->pPolygon);
        pdelete(mpData->pPolygon);
        break;

      case Rectangle:
        mpData->pGroup->addChildElement(mpData->pRectangle);
        pdelete(mpData->pRectangle);
        break;

      case Ellipse:
        mpData->pGroup->addChildElement(mpData->pEllipse);
        // delete the gradient stop since the add method made a copy
        pdelete(mpData->pEllipse);
        break;

      case RenderText:
        mpData->pGroup->addChildElement(mpData->pText);
        // delete the text element again since the add method made a copy
        pdelete(mpData->pText);
        break;

      case Image:
        mpData->pGroup->addChildElement(mpData->pImage);
        // delete the image since the add method made a copy
        pdelete(mpData->pImage);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * GroupHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Group, HANDLER_COUNT}},
    {"Group", Group, Group, {Group, Curve, RenderText, Rectangle, Polygon, Ellipse, Image, AFTER, HANDLER_COUNT}},
    {"Curve", Curve, RenderCurve, {Group, Curve, RenderText, Rectangle, Polygon, Ellipse, Image, AFTER, HANDLER_COUNT}},
    {"Text", RenderText, RenderText, {Group, Curve, RenderText, Rectangle, Polygon, Ellipse, Image, AFTER, HANDLER_COUNT}},
    {"Rectangle", Rectangle, Rectangle, {Group, Curve, RenderText, Rectangle, Polygon, Ellipse, Image, AFTER, HANDLER_COUNT}},
    {"Polygon", Polygon, Polygon, {Group, Curve, RenderText, Rectangle, Polygon, Ellipse, Image, AFTER, HANDLER_COUNT}},
    {"Ellipse", Ellipse, Ellipse, {Group, Curve, RenderText, Rectangle, Polygon, Ellipse, Image, AFTER, HANDLER_COUNT}},
    {"Image", Image, Image, {Group, Curve, RenderText, Rectangle, Polygon, Ellipse, Image, AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
