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

#include "TextGlyphHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CLayout.h"
#include "copasi/model/CModelValue.h"
#include "copasi/model/CReaction.h"

/**
 * Replace TextGlyph with the name type of the handler and implement the
 * three methods below.
 */
TextGlyphHandler::TextGlyphHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::TextGlyph)
{
  init();
}

// virtual
TextGlyphHandler::~TextGlyphHandler()
{}

// virtual
CXMLHandler * TextGlyphHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  switch (mCurrentElement.first)
    {
      case TextGlyph:
      {
        //workload
        const char * key;
        const char * name;
        const char * graphicalObject;
        const char * originOfText;
        const char * text;
        key = mpParser->getAttributeValue("key", papszAttrs);
        name = mpParser->getAttributeValue("name", papszAttrs);
        graphicalObject = mpParser->getAttributeValue("graphicalObject", papszAttrs); //TODO
        originOfText = mpParser->getAttributeValue("originOfText", papszAttrs, false);
        text = mpParser->getAttributeValue("text", papszAttrs, false);

        mpData->pTextGlyph = new CLTextGlyph(name);
        const char * objectRole = mpParser->getAttributeValue("objectRole", papszAttrs, false);

        if (objectRole != NULL && objectRole[0] != 0)
          {
            mpData->pTextGlyph->setObjectRole(objectRole);
          }

        CLGraphicalObject * pGO = dynamic_cast<CLGraphicalObject *>(mpData->mKeyMap.get(graphicalObject));

        if (pGO)
          mpData->pTextGlyph->setGraphicalObjectKey(pGO->getKey());

        if (text)
          mpData->pTextGlyph->setText(text);
        else if (originOfText && originOfText[0])
          {
            CDataObject * pObj = mpData->mKeyMap.get(originOfText);
            CModelEntity * pME = dynamic_cast<CModelEntity *>(pObj);
            CReaction * pR = dynamic_cast<CReaction *>(pObj);

            if (pME)
              {
                mpData->pTextGlyph->setModelObjectKey(pME->getKey());
              }
            else if (pR)
              {
                mpData->pTextGlyph->setModelObjectKey(pR->getKey());
              }
            else
              {
                if (!text)
                  {
                    mpData->pTextGlyph->setText("unset");
                    CCopasiMessage(CCopasiMessage::WARNING, MCXML + 20, key);
                  }
              }

            //TODO: When we have a way to handle references to metab references, this needs to be adapted.
          }

        mpData->pCurrentLayout->addTextGlyph(mpData->pTextGlyph);
        addFix(key, mpData->pTextGlyph);
      }
      break;

      case BoundingBox:
        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool TextGlyphHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case TextGlyph:
        finished = true;
        break;

      case BoundingBox:
        mpData->pTextGlyph->setBoundingBox(*mpData->pBoundingBox);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * TextGlyphHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {TextGlyph, HANDLER_COUNT}},
    {"TextGlyph", TextGlyph, TextGlyph, {BoundingBox, HANDLER_COUNT}},
    {"BoundingBox", BoundingBox, BoundingBox, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
