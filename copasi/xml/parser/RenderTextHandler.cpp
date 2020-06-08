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

#include "RenderTextHandler.h"

#include "copasi/copasi.h"

#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CLText.h"

/**
 * Replace Text with the name type of the handler and implement the
 * three methods below.
 */
RenderTextHandler::RenderTextHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::RenderText)
{
  init();
}

// virtual
RenderTextHandler::~RenderTextHandler()
{}

// virtual
CXMLHandler * RenderTextHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  const char * Transform;
  const char * Stroke;
  const char * StrokeWidth;
  const char * StrokeDashArray;
  const char * X;
  const char * Y;
  const char * Z;
  const char * FontFamily;
  const char * FontSize;
  const char * FontWeight;
  const char * FontStyle;
  const char * TextAnchor;
  const char * VTextAnchor;

  switch (mCurrentElement.first)
    {
      case RenderText:
        Transform = mpParser->getAttributeValue("transform", papszAttrs, false);
        Stroke = mpParser->getAttributeValue("stroke", papszAttrs, false);
        StrokeWidth = mpParser->getAttributeValue("stroke-width", papszAttrs, false);
        StrokeDashArray = mpParser->getAttributeValue("stroke-dasharray", papszAttrs, false);
        X = mpParser->getAttributeValue("x", papszAttrs);
        Y = mpParser->getAttributeValue("y", papszAttrs);
        Z = mpParser->getAttributeValue("z", papszAttrs, "0.0");
        FontFamily = mpParser->getAttributeValue("font-family", papszAttrs, false);
        FontSize = mpParser->getAttributeValue("font-size", papszAttrs, false);
        FontWeight = mpParser->getAttributeValue("font-weight", papszAttrs, false);
        FontStyle = mpParser->getAttributeValue("font-style", papszAttrs, false);
        TextAnchor = mpParser->getAttributeValue("text-anchor", papszAttrs, false);
        VTextAnchor = mpParser->getAttributeValue("vtext-anchor", papszAttrs, false);

        mpData->pText = new CLText();

        if (Transform != NULL)
          {
            mpData->pText->parseTransformation(Transform);
          }

        if (Stroke != NULL)
          {
            mpData->pText->setStroke(Stroke);
          }

        if (StrokeWidth != NULL)
          {
            double width = strToDouble(StrokeWidth, NULL);
            mpData->pText->setStrokeWidth(width);
          }

        if (StrokeDashArray != NULL)
          {
            mpData->pText->parseDashArray(StrokeDashArray);
          }

        mpData->pText->setCoordinates(CLRelAbsVector(X), CLRelAbsVector(Y), CLRelAbsVector(Z));

        if (FontFamily != NULL)
          {
            mpData->pText->setFontFamily(FontFamily);
          }

        if (FontSize != NULL)
          {
            mpData->pText->setFontSize(CLRelAbsVector(FontSize));
          }

        if (FontStyle != NULL)
          {
            std::string s(FontStyle);

            if (s == "normal")
              {
                mpData->pText->setFontStyle(CLText::STYLE_NORMAL);
              }
            else if (s == "italic")
              {
                mpData->pText->setFontStyle(CLText::STYLE_ITALIC);
              }
          }

        if (FontWeight != NULL)
          {
            std::string s(FontWeight);

            if (s == "normal")
              {
                mpData->pText->setFontWeight(CLText::WEIGHT_NORMAL);
              }
            else if (s == "bold")
              {
                mpData->pText->setFontWeight(CLText::WEIGHT_BOLD);
              }
          }

        if (TextAnchor != NULL)
          {
            std::string s(TextAnchor);

            if (s == "start")
              {
                mpData->pText->setTextAnchor(CLText::ANCHOR_START);
              }
            else if (s == "middle")
              {
                mpData->pText->setTextAnchor(CLText::ANCHOR_MIDDLE);
              }
            else if (s == "end")
              {
                mpData->pText->setTextAnchor(CLText::ANCHOR_END);
              }
          }

        if (VTextAnchor != NULL)
          {
            std::string s(VTextAnchor);

            if (s == "top")
              {
                mpData->pText->setVTextAnchor(CLText::ANCHOR_TOP);
              }
            else if (s == "middle")
              {
                mpData->pText->setVTextAnchor(CLText::ANCHOR_MIDDLE);
              }
            else if (s == "bottom")
              {
                mpData->pText->setVTextAnchor(CLText::ANCHOR_BOTTOM);
              }
          }

        pHandlerToCall = getHandler(CharacterData);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool RenderTextHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case RenderText:
        mpData->pText->setText(mpData->CharacterData);
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
CXMLHandler::sProcessLogic * RenderTextHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {RenderText, HANDLER_COUNT}},
    {"Text", RenderText, CharacterData, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
