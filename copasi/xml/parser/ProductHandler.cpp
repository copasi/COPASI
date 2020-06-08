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

#include "ProductHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/model/CReaction.h"

/**
 * Replace Product with the name type of the handler and implement the
 * three methods below.
 */
ProductHandler::ProductHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Product)
{
  init();
}

// virtual
ProductHandler::~ProductHandler()
{}

// virtual
CXMLHandler * ProductHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  const char * Metabolite;
  CMetab * pMetabolite;
  const char * Stoichiometry;

  switch (mCurrentElement.first)
    {
      case Product:
        Metabolite = mpParser->getAttributeValue("metabolite", papszAttrs);
        Stoichiometry = mpParser->getAttributeValue("stoichiometry", papszAttrs);

        pMetabolite = dynamic_cast< CMetab * >(mpData->mKeyMap.get(Metabolite));

        if (!pMetabolite) fatalError();

        mpData->pReaction->addProduct(pMetabolite->getKey(),
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
bool ProductHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Product:
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
CXMLHandler::sProcessLogic * ProductHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Product, HANDLER_COUNT}},
    {"Product", Product, Product, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
