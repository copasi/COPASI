// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "ListOfModelParameterSetsHandler.h"
#include "CXMLParser.h"
#include "utilities/CCopasiMessage.h"

#include "model/CModel.h"

/**
 * Replace ListOfModelParameterSets with the name type of the handler and implement the
 * three methods below.
 */
ListOfModelParameterSetsHandler::ListOfModelParameterSetsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ListOfModelParameterSets),
  mActiveSet()
{
  init();
}

// virtual
ListOfModelParameterSetsHandler::~ListOfModelParameterSetsHandler()
{}

// virtual
CXMLHandler * ListOfModelParameterSetsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  switch (mCurrentElement.first)
    {
      case ListOfModelParameterSets:
        mpData->pModel->getModelParameterSets().clear();
        mActiveSet = mpParser->getAttributeValue("activeSet", papszAttrs, "");

        break;

      case ModelParameterSet:
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
bool ListOfModelParameterSetsHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case ListOfModelParameterSets:
        finished = true;
        break;

      case ModelParameterSet:

      {
        const CModelParameterSet * pModelParameterSet = dynamic_cast< CModelParameterSet * >(mpData->mKeyMap.get(mActiveSet));

        if (pModelParameterSet != NULL)
          {
            size_t Size = CCopasiMessage::size();

            mpData->pModel->getActiveModelParameterSet().assignSetContent(*pModelParameterSet, false);
            delete pModelParameterSet;
            mActiveSet = "";

            // Remove error messages created by setExpression as this may fail
            // due to incomplete model specification at this time.
            while (CCopasiMessage::size() > Size)
              CCopasiMessage::getLastMessage();
          }
      }

      break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfModelParameterSetsHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {ListOfModelParameterSets, HANDLER_COUNT}},
    {"ListOfModelParameterSets", ListOfModelParameterSets, ListOfModelParameterSets, {ModelParameterSet, AFTER, HANDLER_COUNT}},
    {"ModelParameterSet", ModelParameterSet, ModelParameterSet, {ModelParameterSet, AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
