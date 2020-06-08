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

#include "SubstrateHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/model/CReaction.h"

/**
 * Replace Substrate with the name type of the handler and implement the
 * three methods below.
 */
SubstrateHandler::SubstrateHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Substrate)
{
  init();
}

// virtual
SubstrateHandler::~SubstrateHandler()
{}

// virtual
CXMLHandler * SubstrateHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  const char * Metabolite;
  CMetab * pMetabolite;
  const char * Stoichiometry;

  switch (mCurrentElement.first)
    {
      case Substrate:
        Metabolite = mpParser->getAttributeValue("metabolite", papszAttrs);
        Stoichiometry = mpParser->getAttributeValue("stoichiometry", papszAttrs);

        pMetabolite = dynamic_cast< CMetab * >(mpData->mKeyMap.get(Metabolite));

        if (!pMetabolite) fatalError();

        mpData->pReaction->addSubstrate(pMetabolite->getKey(),
                                        CCopasiXMLInterface::DBL(Stoichiometry));
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return NULL;
}

// virtual
bool SubstrateHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Substrate:
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
CXMLHandler::sProcessLogic * SubstrateHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Substrate, HANDLER_COUNT}},
    {"Substrate", Substrate, Substrate, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
