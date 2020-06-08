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

#include "ReactionGlyphHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CLayout.h"
#include "copasi/model/CReaction.h"

/**
 * Replace ReactionGlyph with the name type of the handler and implement the
 * three methods below.
 */
ReactionGlyphHandler::ReactionGlyphHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ReactionGlyph)
{
  init();
}

// virtual
ReactionGlyphHandler::~ReactionGlyphHandler()
{}

// virtual
CXMLHandler * ReactionGlyphHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  switch (mCurrentElement.first)
    {
      case ReactionGlyph:
      {
        //workload
        const char * key;
        const char * name;
        const char * reaction;
        key = mpParser->getAttributeValue("key", papszAttrs);
        name = mpParser->getAttributeValue("name", papszAttrs);
        reaction = mpParser->getAttributeValue("reaction", papszAttrs, false);

        mpData->pReactionGlyph = new CLReactionGlyph(name);
        const char * objectRole = mpParser->getAttributeValue("objectRole", papszAttrs, false);

        if (objectRole != NULL && objectRole[0] != 0)
          {
            mpData->pReactionGlyph->setObjectRole(objectRole);
          }

        if (reaction && reaction[0])
          {
            CReaction * pReaction = dynamic_cast< CReaction * >(mpData->mKeyMap.get(reaction));

            if (!pReaction)
              {
                CCopasiMessage(CCopasiMessage::WARNING, MCXML + 19, "ReactionGlyph" , key);
              }
            else
              {
                mpData->pReactionGlyph->setModelObjectKey(pReaction->getKey());
              }
          }

        mpData->pCurrentLayout->addReactionGlyph(mpData->pReactionGlyph);
        addFix(key, mpData->pReactionGlyph);
      }
      break;

      case BoundingBox:
      case Curve:
      case ListOfMetaboliteReferenceGlyphs:
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
bool ReactionGlyphHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case ReactionGlyph:
        finished = true;
        break;

      case BoundingBox:
        mpData->pReactionGlyph->setBoundingBox(*mpData->pBoundingBox);
        break;

      case Curve:
        mpData->pReactionGlyph->setCurve(*mpData->pCurve);
        break;

      case ListOfMetaboliteReferenceGlyphs:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ReactionGlyphHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {ReactionGlyph, HANDLER_COUNT}},
    {"ReactionGlyph", ReactionGlyph, ReactionGlyph, {BoundingBox, Curve, ListOfMetaboliteReferenceGlyphs, AFTER, HANDLER_COUNT}},
    {"BoundingBox", BoundingBox, BoundingBox, {Curve, ListOfMetaboliteReferenceGlyphs, AFTER, HANDLER_COUNT}},
    {"Curve", Curve, Curve, {ListOfMetaboliteReferenceGlyphs, AFTER, HANDLER_COUNT}},
    {"ListOfMetaboliteReferenceGlyphs", ListOfMetaboliteReferenceGlyphs, ListOfMetaboliteReferenceGlyphs, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
