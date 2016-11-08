// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "StyleGlobalHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"

#include "layout/CLayout.h"

/**
 * Replace StyleGlobal with the name type of the handler and implement the
 * three methods below.
 */
StyleGlobalHandler::StyleGlobalHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::StyleGlobal)
{
  init();
}

// virtual
StyleGlobalHandler::~StyleGlobalHandler()
{}

// virtual
CXMLHandler * StyleGlobalHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  switch (mCurrentElement.first)
    {
      case StyleGlobal:
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
bool StyleGlobalHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case StyleGlobal:
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
CXMLHandler::sProcessLogic * StyleGlobalHandler::getProcessLogic() const
{
  // TODO CRITICAL Implement me!

  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {StyleGlobal, HANDLER_COUNT}},
    {"StyleGlobal", StyleGlobal, StyleGlobal, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
