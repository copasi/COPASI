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

#include "LayoutHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CListOfLayouts.h"

/**
 * Replace Layout with the name type of the handler and implement the
 * three methods below.
 */
LayoutHandler::LayoutHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Layout)
{
  init();
}

// virtual
LayoutHandler::~LayoutHandler()
{}

// virtual
CXMLHandler * LayoutHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  switch (mCurrentElement.first)
    {
      case Layout:
      {
        //workload
        const char * key;
        const char * name;
        key = mpParser->getAttributeValue("key", papszAttrs);
        name = mpParser->getAttributeValue("name", papszAttrs);

        mpData->pCurrentLayout = new CLayout();
        addFix(key, mpData->pCurrentLayout);
        mpData->pCurrentLayout->setObjectName(name);
      }
      break;

      case Dimensions:
      case ListOfCompartmentGlyphs:
      case ListOfMetabGlyphs:
      case ListOfReactionGlyphs:
      case ListOfTextGlyphs:
      case ListOfAdditionalGraphicalObjects:
      case ListOfRenderInformation:
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
bool LayoutHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Layout:
        mpData->pLayoutList->add(mpData->pCurrentLayout, true);
        mpData->pCurrentLayout = NULL;

        finished = true;
        break;

      case Dimensions:
        mpData->pCurrentLayout->setDimensions(*mpData->pDimensions);
        break;

      case ListOfCompartmentGlyphs:
      case ListOfMetabGlyphs:
      case ListOfReactionGlyphs:
      case ListOfTextGlyphs:
      case ListOfAdditionalGraphicalObjects:
      case ListOfRenderInformation:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * LayoutHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Layout, HANDLER_COUNT}},
    {"Layout", Layout, Layout, {Dimensions, HANDLER_COUNT}},
    {"Dimensions", Dimensions, Dimensions, {ListOfCompartmentGlyphs, ListOfMetabGlyphs, ListOfReactionGlyphs, ListOfTextGlyphs, ListOfAdditionalGraphicalObjects, ListOfRenderInformation, AFTER, HANDLER_COUNT}},
    {"ListOfCompartmentGlyphs", ListOfCompartmentGlyphs, ListOfCompartmentGlyphs, {ListOfMetabGlyphs, ListOfReactionGlyphs, ListOfTextGlyphs, ListOfAdditionalGraphicalObjects, ListOfRenderInformation, AFTER, HANDLER_COUNT}},
    {"ListOfMetabGlyphs", ListOfMetabGlyphs, ListOfMetabGlyphs, {ListOfReactionGlyphs, ListOfTextGlyphs, ListOfAdditionalGraphicalObjects, ListOfRenderInformation, AFTER, HANDLER_COUNT}},
    {"ListOfReactionGlyphs", ListOfReactionGlyphs, ListOfReactionGlyphs, {ListOfTextGlyphs, ListOfAdditionalGraphicalObjects, ListOfRenderInformation, AFTER, HANDLER_COUNT}},
    {"ListOfTextGlyphs", ListOfTextGlyphs, ListOfTextGlyphs, {ListOfAdditionalGraphicalObjects, ListOfRenderInformation, AFTER, HANDLER_COUNT}},
    {"ListOfAdditionalGraphicalObjects", ListOfAdditionalGraphicalObjects, ListOfAdditionalGraphicalObjects, {ListOfRenderInformation, AFTER, HANDLER_COUNT}},
    {"ListOfRenderInformation", ListOfRenderInformation, ListOfRenderInformation, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
