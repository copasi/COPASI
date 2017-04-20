// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "SBMLMapHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"

#include "function/CFunction.h"
#include "model/CModel.h"

/**
 * Replace SBMLMap with the name type of the handler and implement the
 * three methods below.
 */
SBMLMapHandler::SBMLMapHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::SBMLMap)
{
  init();
}

// virtual
SBMLMapHandler::~SBMLMapHandler()
{}

// virtual
CXMLHandler * SBMLMapHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  const char * SBMLid;
  const char * COPASIkey;
  CDataObject * pObject;

  switch (mCurrentElement.first)
    {
      case SBMLMap:
        SBMLid = mpParser->getAttributeValue("SBMLid", papszAttrs);
        COPASIkey = mpParser->getAttributeValue("COPASIkey", papszAttrs);

        if ((pObject = mpData->mKeyMap.get(COPASIkey)))
          {
            CFunction * pFunction;
            CCompartment* pCompartment;
            CMetab * pMetab;
            CModelValue * pModelValue;
            CReaction * pReaction;

            if ((pFunction = dynamic_cast<CFunction *>(pObject)))
              pFunction->setSBMLId(SBMLid);
            else if ((pCompartment = dynamic_cast<CCompartment *>(pObject)))
              pCompartment->setSBMLId(SBMLid);
            else if ((pMetab = dynamic_cast<CMetab *>(pObject)))
              pMetab->setSBMLId(SBMLid);
            else if ((pModelValue = dynamic_cast<CModelValue *>(pObject)))
              pModelValue->setSBMLId(SBMLid);
            else if ((pReaction = dynamic_cast<CReaction *>(pObject)))
              pReaction->setSBMLId(SBMLid);
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
bool SBMLMapHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case SBMLMap:
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
CXMLHandler::sProcessLogic * SBMLMapHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {SBMLMap, HANDLER_COUNT}},
    {"SBMLMap", SBMLMap, SBMLMap, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
