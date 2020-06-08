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

#include "MetaboliteGlyphHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CLayout.h"
#include "copasi/model/CMetab.h"

/**
 * Replace MetaboliteGlyph with the name type of the handler and implement the
 * three methods below.
 */
MetaboliteGlyphHandler::MetaboliteGlyphHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::MetaboliteGlyph)
{
  init();
}

// virtual
MetaboliteGlyphHandler::~MetaboliteGlyphHandler()
{}

// virtual
CXMLHandler * MetaboliteGlyphHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  switch (mCurrentElement.first)
    {
      case MetaboliteGlyph:
      {
        //workload
        const char * key;
        const char * name;
        const char * metabolite;
        key = mpParser->getAttributeValue("key", papszAttrs);
        name = mpParser->getAttributeValue("name", papszAttrs);
        metabolite = mpParser->getAttributeValue("metabolite", papszAttrs, false);

        mpData->pMetaboliteGlyph = new CLMetabGlyph(name);
        const char * objectRole = mpParser->getAttributeValue("objectRole", papszAttrs, false);

        if (objectRole != NULL && objectRole[0] != 0)
          {
            mpData->pMetaboliteGlyph->setObjectRole(objectRole);
          }

        if (metabolite && metabolite[0])
          {
            CMetab * pMetab = dynamic_cast< CMetab * >(mpData->mKeyMap.get(metabolite));

            if (!pMetab)
              {
                CCopasiMessage(CCopasiMessage::WARNING, MCXML + 19, "MetaboliteGlyph", key);
              }
            else
              {
                mpData->pMetaboliteGlyph->setModelObjectKey(pMetab->getKey());
              }
          }

        mpData->pCurrentLayout->addMetaboliteGlyph(mpData->pMetaboliteGlyph);
        addFix(key, mpData->pMetaboliteGlyph);
      }
      break;

      case BoundingBox:
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
bool MetaboliteGlyphHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case MetaboliteGlyph:
        finished = true;
        break;

      case BoundingBox:
        mpData->pMetaboliteGlyph->setBoundingBox(*mpData->pBoundingBox);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * MetaboliteGlyphHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {MetaboliteGlyph, HANDLER_COUNT}},
    {"MetaboliteGlyph", MetaboliteGlyph, MetaboliteGlyph, {BoundingBox, HANDLER_COUNT}},
    {"BoundingBox", BoundingBox, BoundingBox, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
