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

#include "ModifierHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/model/CReaction.h"

/**
 * Replace Modifier with the name type of the handler and implement the
 * three methods below.
 */
ModifierHandler::ModifierHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Modifier)
{
  init();
}

// virtual
ModifierHandler::~ModifierHandler()
{}

// virtual
CXMLHandler * ModifierHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  const char * Metabolite;
  CMetab * pMetabolite;

  switch (mCurrentElement.first)
    {
      case Modifier:
        Metabolite = mpParser->getAttributeValue("metabolite", papszAttrs);

        pMetabolite = dynamic_cast< CMetab * >(mpData->mKeyMap.get(Metabolite));

        if (pMetabolite != NULL)
          {
            mpData->pReaction->addModifier(pMetabolite->getKey());
          }

        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return NULL;
}

// virtual
bool ModifierHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Modifier:
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
CXMLHandler::sProcessLogic * ModifierHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Modifier, HANDLER_COUNT}},
    {"Modifier", Modifier, Modifier, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
