// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "StyleLocalHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"

#include "layout/CLayout.h"

/**
 * Replace StyleLocal with the name type of the handler and implement the
 * three methods below.
 */
StyleLocalHandler::StyleLocalHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::StyleLocal)
{
  init();
}

// virtual
StyleLocalHandler::~StyleLocalHandler()
{}

// virtual
CXMLHandler * StyleLocalHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  switch (mCurrentElement.first)
    {
      case StyleLocal:
        // TODO CRITICAL Implement me!
        break;

        // TODO CRITICAL Implement me!

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool StyleLocalHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case StyleLocal:
        finished = true;
        // TODO CRITICAL Implement me!
        break;

      case Group:
        if (!mpData->pGroup->isSetStroke())
          {
            mpData->pGroup->setStroke("none");
          }

        if (!mpData->pGroup->isSetStrokeWidth())
          {
            mpData->pGroup->setStrokeWidth(0.0);
          }

        if (!mpData->pGroup->isSetFill())
          {
            mpData->pGroup->setFillColor("none");
          }

        if (!mpData->pGroup->isSetFillRule())
          {
            mpData->pGroup->setFillRule(CLGraphicalPrimitive2D::NONZERO);
          }

        if (!mpData->pGroup->isSetFontFamily())
          {
            mpData->pGroup->setFontFamily("sans-serif");
          }

        if (!mpData->pGroup->isSetFontWeight())
          {
            mpData->pGroup->setFontWeight(CLText::WEIGHT_NORMAL);
          }

        if (!mpData->pGroup->isSetFontStyle())
          {
            mpData->pGroup->setFontStyle(CLText::STYLE_NORMAL);
          }

        if (!mpData->pGroup->isSetTextAnchor())
          {
            mpData->pGroup->setTextAnchor(CLText::ANCHOR_START);
          }

        if (!mpData->pGroup->isSetVTextAnchor())
          {
            mpData->pGroup->setVTextAnchor(CLText::ANCHOR_TOP);
          }

        if (!mpData->pGroup->isSetStartHead())
          {
            mpData->pGroup->setStartHead("none");
          }

        if (!mpData->pGroup->isSetEndHead())
          {
            mpData->pGroup->setEndHead("none");
          }

        mpData->pStyle->setGroup(mpData->pGroup);
        // delete the group element again since the add/set methods made a copy
        pdelete(mpData->pGroup);

        break;

        // TODO CRITICAL Implement me!

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * StyleLocalHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {StyleLocal, HANDLER_COUNT}},
    {"StyleLocal", StyleLocal, StyleLocal, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
