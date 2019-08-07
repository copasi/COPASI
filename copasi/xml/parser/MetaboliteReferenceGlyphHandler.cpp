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

#include "MetaboliteReferenceGlyphHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CLReactionGlyph.h"

/**
 * Replace MetaboliteReferenceGlyph with the name type of the handler and implement the
 * three methods below.
 */
MetaboliteReferenceGlyphHandler::MetaboliteReferenceGlyphHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::MetaboliteReferenceGlyph)
{
  init();
}

// virtual
MetaboliteReferenceGlyphHandler::~MetaboliteReferenceGlyphHandler()
{}

// virtual
CXMLHandler * MetaboliteReferenceGlyphHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  switch (mCurrentElement.first)
    {
      case MetaboliteReferenceGlyph:
      {
        //workload
        const char * key;
        const char * name;
        const char * metaboliteGlyph;
        const char * role;
        key = mpParser->getAttributeValue("key", papszAttrs);
        name = mpParser->getAttributeValue("name", papszAttrs);
        metaboliteGlyph = mpParser->getAttributeValue("metaboliteGlyph", papszAttrs);
        role = mpParser->getAttributeValue("role", papszAttrs);

        mpData->pMetaboliteReferenceGlyph = new CLMetabReferenceGlyph(name);
        const char * objectRole = mpParser->getAttributeValue("objectRole", papszAttrs, false);

        if (objectRole != NULL && objectRole[0] != 0)
          {
            mpData->pMetaboliteReferenceGlyph->setObjectRole(objectRole);
          }

        CLMetabGlyph * pMetabGlyph = dynamic_cast< CLMetabGlyph * >(mpData->mKeyMap.get(metaboliteGlyph));

        //if (!pMetabGlyph) fatalError();

        if (pMetabGlyph)
          mpData->pMetaboliteReferenceGlyph->setMetabGlyphKey(pMetabGlyph->getKey());

        //interpret role string
        C_INT32 i;

        for (i = 0; (CLMetabReferenceGlyph::XMLRole[i] != "") && (CLMetabReferenceGlyph::XMLRole[i] != role); ++i) {};

        if (CLMetabReferenceGlyph::XMLRole[i] == "")
          mpData->pMetaboliteReferenceGlyph->setRole(CLMetabReferenceGlyph::UNDEFINED);
        else
          mpData->pMetaboliteReferenceGlyph->setRole(CLMetabReferenceGlyph::Role(i));

        mpData->pReactionGlyph->addMetabReferenceGlyph(mpData->pMetaboliteReferenceGlyph);
        addFix(key, mpData->pMetaboliteReferenceGlyph);
      }
      break;

      case BoundingBox:
      case Curve:
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
bool MetaboliteReferenceGlyphHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case MetaboliteReferenceGlyph:
        finished = true;
        break;

      case BoundingBox:
        mpData->pMetaboliteReferenceGlyph->setBoundingBox(*mpData->pBoundingBox);
        break;

      case Curve:
        mpData->pMetaboliteReferenceGlyph->setCurve(*mpData->pCurve);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * MetaboliteReferenceGlyphHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {MetaboliteReferenceGlyph, HANDLER_COUNT}},
    {"MetaboliteReferenceGlyph", MetaboliteReferenceGlyph, MetaboliteReferenceGlyph, {BoundingBox, Curve, AFTER, HANDLER_COUNT}},
    {"BoundingBox", BoundingBox, BoundingBox, {Curve, AFTER, HANDLER_COUNT}},
    {"Curve", Curve, Curve, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
