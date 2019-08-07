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

#include "copasi/xml/parser/UnitDefinitionHandler.h"
#include "copasi/xml/parser/CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/utilities/CUnitDefinition.h"
#include "copasi/utilities/CUnitDefinitionDB.h"
/**
 * Replace UnitDefinition with the name type of the handler and implement the
 * three methods below.
 */
UnitDefinitionHandler::UnitDefinitionHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::UnitDefinition),
  mKey()
{
  init();
}

// virtual
UnitDefinitionHandler::~UnitDefinitionHandler()
{}

// virtual
CXMLHandler * UnitDefinitionHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  const char * Name;
  const char * Symbol;

  switch (mCurrentElement.first)
    {
      case UnitDefinition:
        // Element specific code.
        mKey = mpParser->getAttributeValue("key", papszAttrs);
        Name = mpParser->getAttributeValue("name", papszAttrs);
        Symbol = mpParser->getAttributeValue("symbol", papszAttrs);

        // Need a CUnitDefinition.
        // This is manipulated in this case and the Expression case.
        // No test for NULL here. If this already was pointing to something,
        // we don't want that object for this.
        mpData->pCurrentUnitDefinition = new CUnitDefinition(Name, NULL);
        mpData->pCurrentUnitDefinition->setSymbol(Symbol);
        mpData->pUnitDefinitionImportList->add(mpData->pCurrentUnitDefinition, true);
        break;;

      case MiriamAnnotation:
      case Comment:
      case ListOfUnsupportedAnnotations:
      case Expression:
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
bool UnitDefinitionHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case UnitDefinition:
        mpData->mKeyMap.addFix(mKey, mpData->pCurrentUnitDefinition);
        finished = true;
        break;

      case MiriamAnnotation:
        mpData->pCurrentUnitDefinition->setMiriamAnnotation(mpData->CharacterData, mpData->pCurrentUnitDefinition->getKey(), mKey);
        mpData->CharacterData = "";
        break;

      case Comment:
        mpData->pCurrentUnitDefinition->setNotes(mpData->CharacterData);
        mpData->CharacterData = "";
        break;

      case ListOfUnsupportedAnnotations:
        mpData->pCurrentUnitDefinition->getUnsupportedAnnotations() = mpData->mUnsupportedAnnotations;
        break;

        break;

      case Expression:
      {
        size_t Size = CCopasiMessage::size();

        mpData->pCurrentUnitDefinition->setExpression(mpData->CharacterData);

        // Remove error messages created by setExpression as this may fail
        // due to incomplete model specification at this time.
        while (CCopasiMessage::size() > Size)
          CCopasiMessage::getLastMessage();
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
CXMLHandler::sProcessLogic * UnitDefinitionHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {UnitDefinition, HANDLER_COUNT}},
    {"UnitDefinition", UnitDefinition, UnitDefinition, {MiriamAnnotation, Comment, ListOfUnsupportedAnnotations, Expression, AFTER, HANDLER_COUNT}},
    {"MiriamAnnotation", MiriamAnnotation, MiriamAnnotation, {Comment, ListOfUnsupportedAnnotations, Expression, AFTER, HANDLER_COUNT}},
    {"Comment", Comment, Comment, {ListOfUnsupportedAnnotations, Expression, AFTER, HANDLER_COUNT}},
    {"ListOfUnsupportedAnnotations", ListOfUnsupportedAnnotations, ListOfUnsupportedAnnotations, {Expression, AFTER, HANDLER_COUNT}},
    {"Expression", Expression, CharacterData, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
