// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CExpat.h"
#include "CCopasiXMLParser.h"
#include "CCopasiXMLInterface.h"
#include "report/CCopasiRootContainer.h"

#define START_ELEMENT   -1
#define UNKNOWN_ELEMENT -2

CCopasiXMLParser::UnitDefinitionElement::UnitDefinitionElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mKey()
{}

CCopasiXMLParser::UnitDefinitionElement::~UnitDefinitionElement()
{
}

void CCopasiXMLParser::UnitDefinitionElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * Name;
  const char * Symbol;

  mpCurrentHandler = NULL;
  mCurrentElement = mLastKnownElement;

  while (mpCurrentHandler == NULL)
    {
      mCurrentElement++; /* We should always be on the next element */

      switch (mCurrentElement)
        {
          case UnitDefinition:

            if (strcmp(pszName, "UnitDefinition"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                             pszName, "UnitDefinition", mParser.getCurrentLineNumber());

            mLastKnownElement = UnitDefinition;

            // Element specific code.
            mKey = mParser.getAttributeValue("key", papszAttrs);
            Name = mParser.getAttributeValue("name", papszAttrs);
            Symbol = mParser.getAttributeValue("symbol", papszAttrs);

            // Need a CUnitDefinition.
            // This is manipulated in this case and the Expression case.
            // No test for NULL here. If this already was pointing to something,
            // we don't want that object for this.
            mCommon.pCurrentUnitDefinition = new CUnitDefinition(Name, NULL);

            mCommon.pCurrentUnitDefinition->setSymbol(Symbol);

            return;

          case MiriamAnnotation:

            if (!strcmp(pszName, "MiriamAnnotation"))
              mpCurrentHandler = &mParser.mMiriamAnnotationElement;

            break;

          case Comment:

            if (!strcmp(pszName, "Comment"))
              mpCurrentHandler = &mParser.mCommentElement;

            break;

          case ListOfUnsupportedAnnotations:

            if (!strcmp(pszName, "ListOfUnsupportedAnnotations"))
              mpCurrentHandler = &mParser.mListOfUnsupportedAnnotationsElement;

            break;

          case Expression:

            if (!strcmp(pszName, "Expression"))
              mpCurrentHandler = &mParser.mCharacterDataElement;

            break;

          default:
            mCurrentElement = UNKNOWN_ELEMENT;
            mpCurrentHandler = &mParser.mUnknownElement;
            break;
        }
    }

  mParser.pushElementHandler(mpCurrentHandler);

  if (mpCurrentHandler != &mParser.mUnknownElement)
    {
      mLastKnownElement = mCurrentElement;
    }

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

void CCopasiXMLParser::UnitDefinitionElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case UnitDefinition:

        if (strcmp(pszName, "UnitDefinition"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "UnitDefinition", mParser.getCurrentLineNumber());

        if (!mCommon.pUnitDefinitionImportList->add(mCommon.pCurrentUnitDefinition, true))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 23,
                         mCommon.pCurrentUnitDefinition->getObjectName().c_str(), mParser.getCurrentLineNumber());

        mCommon.KeyMap.addFix(mKey, mCommon.pCurrentUnitDefinition);

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;
        mLastKnownElement = mCurrentElement;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);

        return;
        break;

      case MiriamAnnotation:

        if (strcmp(pszName, "MiriamAnnotation"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "MiriamAnnotation", mParser.getCurrentLineNumber());

        mCommon.pCurrentUnitDefinition->setMiriamAnnotation(mCommon.CharacterData, mCommon.pCurrentUnitDefinition->getKey(), mKey);
        mCommon.CharacterData = "";
        break;

      case Comment:

        if (strcmp(pszName, "Comment"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Comment", mParser.getCurrentLineNumber());

        mCommon.pCurrentUnitDefinition->setNotes(mCommon.CharacterData);
        mCommon.CharacterData = "";
        break;

      case ListOfUnsupportedAnnotations:

        if (strcmp(pszName, "ListOfUnsupportedAnnotations"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfUnsupportedAnnotations", mParser.getCurrentLineNumber());

        mCommon.pCurrentUnitDefinition->getUnsupportedAnnotations() = mParser.mListOfUnsupportedAnnotationsElement.getUnsupportedAnnotations();

        break;

      case Expression:

        if (strcmp(pszName, "Expression"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Expression", mParser.getCurrentLineNumber());

        {
          size_t Size = CCopasiMessage::size();

          mCommon.pCurrentUnitDefinition->setExpression(mCommon.CharacterData, CUnit::Avogadro);

          // Remove error messages created by setExpression as this may fail
          // due to incomplete model specification at this time.
          while (CCopasiMessage::size() > Size)
            CCopasiMessage::getLastMessage();
        }
        break;

      case UNKNOWN_ELEMENT:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  mCurrentElement = UnitDefinition;
  return;
}

// List of Unit Definitions
CCopasiXMLParser::ListOfUnitDefinitionsElement::ListOfUnitDefinitionsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common)
  : CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
  , mpUnitDefinitionElement(NULL)
{}

// virtual
CCopasiXMLParser::ListOfUnitDefinitionsElement::~ListOfUnitDefinitionsElement()
{
}

// virtual
void CCopasiXMLParser::ListOfUnitDefinitionsElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mpCurrentHandler = NULL;
  mCurrentElement = mLastKnownElement;

  while (mpCurrentHandler == NULL)
    {
      mCurrentElement++; /* We should always be on the next element */

      switch (mCurrentElement)
        {
          case ListOfUnitDefinitions:

            if (strcmp(pszName, "ListOfUnitDefinitions"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                             pszName, "ListOfUnitDefinitions", mParser.getCurrentLineNumber());

            if (!mCommon.pUnitDefinitionImportList)
              mCommon.pUnitDefinitionImportList = new CUnitDefinitionDB("importUnitDefintionsList");

            mLastKnownElement = ListOfUnitDefinitions;

            return;
            break;

          case UnitDefinition:

            if (!strcmp(pszName, "UnitDefinition"))
              {
                /* If we do not have a UnitDefinition element handler we create one. */
                if (!mpUnitDefinitionElement)
                  mpUnitDefinitionElement = new UnitDefinitionElement(mParser, mCommon);

                mpCurrentHandler = mpUnitDefinitionElement;
              }

            break;

          default:
            mCurrentElement = UNKNOWN_ELEMENT;
            mpCurrentHandler = &mParser.mUnknownElement;
            break;
        }
    }

  mParser.pushElementHandler(mpCurrentHandler);

  if (mpCurrentHandler != &mParser.mUnknownElement)
    {
      mLastKnownElement = mCurrentElement;
    }

  mParser.onStartElement(pszName, papszAttrs);

  return;
}

// virtual
void CCopasiXMLParser::ListOfUnitDefinitionsElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case ListOfUnitDefinitions:

        if (strcmp(pszName, "ListOfUnitDefinitions"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfUnitDefinitions", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;
        mLastKnownElement = mCurrentElement;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        return;
        break;

      case UnitDefinition:

        if (strcmp(pszName, "UnitDefinition"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "UnitDefinition", mParser.getCurrentLineNumber());

        mCurrentElement = ListOfUnitDefinitions;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  mLastKnownElement = mCurrentElement;

  return;
}
