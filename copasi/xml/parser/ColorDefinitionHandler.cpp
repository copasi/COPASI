// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ColorDefinitionHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"

#include "layout/CLayout.h"

ColorDefinitionHandler::ColorDefinitionHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ColorDefinition)
{
  init();
}

// virtual
ColorDefinitionHandler::~ColorDefinitionHandler()
{}

// virtual
CXMLHandler * ColorDefinitionHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  const char * Id;
  const char * Value;
  CLColorDefinition * pColorDef;

  switch (mCurrentElement.first)
    {
      case ColorDefinition:
        Id = mpParser->getAttributeValue("id", papszAttrs);
        Value = mpParser->getAttributeValue("value", papszAttrs);

        pColorDef = mpData->pRenderInformation->createColorDefinition();
        pColorDef->setColorValue(Value);
        pColorDef->setId(Id);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return NULL;
}

// virtual
bool ColorDefinitionHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case ColorDefinition:
        finished = true;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ColorDefinitionHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {ColorDefinition, HANDLER_COUNT}},
    {"ColorDefinition", ColorDefinition, ColorDefinition, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
