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

#include "CompartmentGlyphHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CLayout.h"
#include "copasi/model/CCompartment.h"

CompartmentGlyphHandler::CompartmentGlyphHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::CompartmentGlyph)
{
  init();
}

// virtual
CompartmentGlyphHandler::~CompartmentGlyphHandler()
{}

// virtual
CXMLHandler * CompartmentGlyphHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  switch (mCurrentElement.first)
    {
      case CompartmentGlyph:
      {
        //workload
        const char * key;
        const char * name;
        const char * compartment;
        key = mpParser->getAttributeValue("key", papszAttrs);
        name = mpParser->getAttributeValue("name", papszAttrs);
        compartment = mpParser->getAttributeValue("compartment", papszAttrs);

        mpData->pCompartmentGlyph = new CLCompartmentGlyph(name);
        const char * objectRole = mpParser->getAttributeValue("objectRole", papszAttrs, false);

        if (objectRole != NULL && objectRole[0] != 0)
          {
            mpData->pCompartmentGlyph->setObjectRole(objectRole);
          }

        if (compartment && compartment[0])
          {
            CCompartment * pComp = dynamic_cast< CCompartment * >(mpData->mKeyMap.get(compartment));

            if (!pComp)
              {
                CCopasiMessage(CCopasiMessage::WARNING, MCXML + 19 , "CompartmentGlyph", key);
              }
            else
              {
                mpData->pCompartmentGlyph->setModelObjectKey(pComp->getKey());
              }
          }

        mpData->pCurrentLayout->addCompartmentGlyph(mpData->pCompartmentGlyph);
        addFix(key, mpData->pCompartmentGlyph);
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
bool CompartmentGlyphHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case CompartmentGlyph:
        finished = true;
        break;

      case BoundingBox:
        mpData->pCompartmentGlyph->setBoundingBox(*mpData->pBoundingBox);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * CompartmentGlyphHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {CompartmentGlyph, HANDLER_COUNT}},
    {"CompartmentGlyph", CompartmentGlyph, CompartmentGlyph, {BoundingBox, HANDLER_COUNT}},
    {"BoundingBox", BoundingBox, BoundingBox, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
