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

#include "RenderInformationHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CLayout.h"

RenderInformationHandler::RenderInformationHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::RenderInformation)
{
  init();
}

// virtual
RenderInformationHandler::~RenderInformationHandler()
{}

// virtual
CXMLHandler * RenderInformationHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  const char * background;

  switch (mCurrentElement.first)
    {
      case RenderInformation:
        mpData->pRenderInformation = CXMLParserData::createRenderInformation(mpData);

        background = mpParser->getAttributeValue("backgroundColor", papszAttrs);
        assert(background != NULL);

        if (background != NULL)
          {
            mpData->pRenderInformation->setBackgroundColor(background);
          }

        break;

      case ListOfColorDefinitions:
      case ListOfGradientDefinitions:
      case ListOfLineEndings:
      case ListOfStyles:
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
bool RenderInformationHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case RenderInformation:
        finished = true;
        break;

      case ListOfColorDefinitions:
      case ListOfGradientDefinitions:
      case ListOfLineEndings:
      case ListOfStyles:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * RenderInformationHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {RenderInformation, HANDLER_COUNT}},
    {"RenderInformation", RenderInformation, RenderInformation, {ListOfColorDefinitions, ListOfGradientDefinitions, ListOfLineEndings, ListOfStyles, AFTER, HANDLER_COUNT}},
    {"ListOfColorDefinitions", ListOfColorDefinitions, ListOfColorDefinitions, {ListOfGradientDefinitions, ListOfLineEndings, ListOfStyles, AFTER, HANDLER_COUNT}},
    {"ListOfGradientDefinitions", ListOfGradientDefinitions, ListOfGradientDefinitions, {ListOfLineEndings, ListOfStyles, AFTER, HANDLER_COUNT}},
    {"ListOfLineEndings", ListOfLineEndings, ListOfLineEndings, {ListOfStyles, AFTER, HANDLER_COUNT}},
    {"ListOfStyles", ListOfStyles, ListOfStyles, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
