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

#include "StyleHandler.h"

#include "copasi/copasi.h"

#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CLayout.h"
#include "copasi/layout/CLGlobalRenderInformation.h"
#include "copasi/layout/CLGlobalStyle.h"

/**
 * Replace StyleLocal with the name type of the handler and implement the
 * three methods below.
 */
StyleHandler::StyleHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Style)
{
  init();
}

// virtual
StyleHandler::~StyleHandler()
{}

// virtual
CXMLHandler * StyleHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  const char * RoleList;
  const char * TypeList;
  const char * KeyList;

  switch (mCurrentElement.first)
    {
      case Style:
        mpData->pStyle = mpData->pRenderInformation->createStyle();

        RoleList = mpParser->getAttributeValue("roleList", papszAttrs, false);
        TypeList = mpParser->getAttributeValue("typeList", papszAttrs, false);
        KeyList = mpParser->getAttributeValue("keyList", papszAttrs, false);

        if (RoleList != NULL)
          {
            std::set<std::string> s;
            CLStyle::readIntoSet(RoleList, s);
            mpData->pStyle->setRoleList(s);
          }

        if (TypeList != NULL)
          {
            std::set<std::string> s;
            CLStyle::readIntoSet(TypeList, s);
            mpData->pStyle->setTypeList(s);
          }

        if (dynamic_cast< CLLocalStyle * >(mpData->pStyle) != NULL && KeyList != NULL)
          {
            std::set<std::string> s;
            CLStyle::readIntoSet(KeyList, s);
            // we need to translate the keys from the file to the actual keys assigned now
            std::set<std::string> s_conv;
            std::set<std::string>::const_iterator keyIt = s.begin(), keyEndit = s.end();
            CLGraphicalObject* pGO = NULL;

            while (keyIt != keyEndit)
              {
                pGO = dynamic_cast<CLGraphicalObject *>(mpData->mKeyMap.get(*keyIt));
                assert(pGO);

                if (pGO != NULL)
                  {
                    s_conv.insert(pGO->getKey());
                  }

                ++keyIt;
              }

            static_cast< CLLocalStyle * >(mpData->pStyle)->setKeyList(s_conv);
          }

        break;

      case Group:
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
bool StyleHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Style:
        finished = true;
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

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * StyleHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Style, HANDLER_COUNT}},
    {"Style", Style, Style, {Group, HANDLER_COUNT}},
    {"Group", Group, Group, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
