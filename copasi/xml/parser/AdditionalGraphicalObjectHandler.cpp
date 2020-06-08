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

#include "AdditionalGraphicalObjectHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CLayout.h"

AdditionalGraphicalObjectHandler::AdditionalGraphicalObjectHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::AdditionalGraphicalObject)
{
  init();
}

// virtual
AdditionalGraphicalObjectHandler::~AdditionalGraphicalObjectHandler()
{}

// virtual
CXMLHandler * AdditionalGraphicalObjectHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  const char * key;
  const char * name;
  const char * objectRole;

  switch (mCurrentElement.first)
    {
      case AdditionalGraphicalObject:
        key = mpParser->getAttributeValue("key", papszAttrs);
        name = mpParser->getAttributeValue("name", papszAttrs);
        objectRole = mpParser->getAttributeValue("objectRole", papszAttrs, false);

        mpData->pGeneralGlyph = new CLGeneralGlyph(name);

        if (objectRole != NULL && objectRole[0] != 0)
          {
            mpData->pGeneralGlyph->setObjectRole(objectRole);
          }

        mpData->pCurrentLayout->addGeneralGlyph(mpData->pGeneralGlyph);
        addFix(key, mpData->pGeneralGlyph);
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
bool AdditionalGraphicalObjectHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case AdditionalGraphicalObject:
        finished = true;
        break;

      case BoundingBox:
        mpData->pGeneralGlyph->setBoundingBox(*mpData->pBoundingBox);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * AdditionalGraphicalObjectHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {AdditionalGraphicalObject, HANDLER_COUNT}},
    {"AdditionalGraphicalObject", AdditionalGraphicalObject, AdditionalGraphicalObject, {BoundingBox, HANDLER_COUNT}},
    {"BoundingBox", BoundingBox, BoundingBox, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
