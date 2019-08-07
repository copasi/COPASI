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

#include "ListOfGradientDefinitionsHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

ListOfGradientDefinitionsHandler::ListOfGradientDefinitionsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfGradientDefinitions)
{
  init();
}

// virtual
ListOfGradientDefinitionsHandler::~ListOfGradientDefinitionsHandler()
{}

// virtual
CXMLHandler * ListOfGradientDefinitionsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  switch (mCurrentElement.first)
    {
      case ListOfGradientDefinitions:
        break;

      case RadialGradient:
      case LinearGradient:
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
bool ListOfGradientDefinitionsHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case ListOfGradientDefinitions:
        finished = true;
        break;

      case RadialGradient:
      case LinearGradient:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfGradientDefinitionsHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {ListOfGradientDefinitions, HANDLER_COUNT}},
    {"ListOfGradientDefinitions", ListOfGradientDefinitions, ListOfGradientDefinitions, {RadialGradient, LinearGradient, AFTER, HANDLER_COUNT}},
    {"RadialGradient", RadialGradient, RadialGradient, {RadialGradient, LinearGradient, AFTER, HANDLER_COUNT}},
    {"LinearGradient", LinearGradient, LinearGradient, {RadialGradient, LinearGradient, AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
