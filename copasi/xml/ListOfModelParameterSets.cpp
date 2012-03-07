// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/xml/ListOfModelParameterSets.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/03/07 17:14:43 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CExpat.h"
#include "CCopasiXMLParser.h"
#include "CCopasiXMLInterface.h"

#include "model/CModel.h"
#include "model/CModelParameterSet.h"

#define START_ELEMENT   -1
#define UNKNOWN_ELEMENT -2

// Model Parameter Sets
CCopasiXMLParser::ListOfModelParameterSetsElement::ListOfModelParameterSetsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
    mActiveSet(),
    mpModelParameterSetElement(NULL)
{}

// virtual
CCopasiXMLParser::ListOfModelParameterSetsElement::~ListOfModelParameterSetsElement()
{
  pdelete(mpModelParameterSetElement);
}

// virtual
void CCopasiXMLParser::ListOfModelParameterSetsElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mpCurrentHandler = NULL;
  mCurrentElement = mLastKnownElement;

  while (mpCurrentHandler == NULL)
    {
      mCurrentElement++; /* We should always be on the next element */

      switch (mCurrentElement)
        {
          case ListOfModelParameterSets:

            if (strcmp(pszName, "ListOfModelParameterSets"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                             pszName, "ListOfModelParameterSets", mParser.getCurrentLineNumber());

            mLastKnownElement = ListOfModelParameterSets;

            mCommon.pModel->getModelParameterSets().clear();
            mActiveSet = mParser.getAttributeValue("activeSet", papszAttrs);

            return;

          case ModelParameterSet:

            if (!strcmp(pszName, "ModelParameterSet"))
              {
                /* If we do not have a ModelParameterSet element handler we create one. */
                if (!mpModelParameterSetElement)
                  mpModelParameterSetElement = new ModelParameterSetElement(mParser, mCommon);

                mpCurrentHandler = mpModelParameterSetElement;
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

}

// virtual
void CCopasiXMLParser::ListOfModelParameterSetsElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case ListOfModelParameterSets:

        if (strcmp(pszName, "ListOfModelParameterSets"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfModelParameterSets", mParser.getCurrentLineNumber());

        {
          const CCopasiObject * pModelParameterSet = mCommon.KeyMap.get(mActiveSet);

          if (pModelParameterSet != NULL)
            {
              mActiveSet = pModelParameterSet->getKey();
            }
          else
            {
              mActiveSet = "";
            }
        }

        mCommon.pModel->setActiveParameterSetKey(mActiveSet);

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case ModelParameterSet:

        if (strcmp(pszName, "ModelParameterSet"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ModelParameterSet", mParser.getCurrentLineNumber());

        mCurrentElement = ListOfModelParameterSets;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::ModelParameterSetElement::ModelParameterSetElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
    mKey(),
    mpModelParameterGroupElement(NULL),
    mpModelParameterElement(NULL)
{}

CCopasiXMLParser::ModelParameterSetElement::~ModelParameterSetElement()
{
  pdelete(mpModelParameterGroupElement);
  pdelete(mpModelParameterElement);
}

void CCopasiXMLParser::ModelParameterSetElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * Name;

  mpCurrentHandler = NULL;
  mCurrentElement = mLastKnownElement;

  while (mpCurrentHandler == NULL)
    {
      mCurrentElement++; /* We should always be on the next element */

      switch (mCurrentElement)
        {
          case ModelParameterSet:

            if (strcmp(pszName, "ModelParameterSet"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                             pszName, "ModelParameterSet", mParser.getCurrentLineNumber());

            mLastKnownElement = ModelParameterSet;

            // Element specific code.
            mKey = mParser.getAttributeValue("key", papszAttrs);
            Name = mParser.getAttributeValue("name", papszAttrs);

            {
              CModelParameterSet * pModelParameterSet = new CModelParameterSet(Name);
              mCommon.pModel->getModelParameterSets().add(pModelParameterSet, true);
              mCommon.ModelParameterGroupStack.push(pModelParameterSet);

              mCommon.KeyMap.addFix(mKey, pModelParameterSet);
            }
            return;

          case MiriamAnnotation:

            if (!strcmp(pszName, "MiriamAnnotation"))
              {
                mpCurrentHandler = &mParser.mMiriamAnnotationElement;
                mLastKnownElement = mCurrentElement;
              }

            break;

          case Comment:

            if (!strcmp(pszName, "Comment"))
              {
                mpCurrentHandler = &mParser.mCommentElement;
                mLastKnownElement = mCurrentElement;
              }

            break;


          case Content:

            if (!strcmp(pszName, "ModelParameterGroup"))
              {
                /* If we do not have an etc element handler we create one. */
                if (!mpModelParameterGroupElement)
                  mpModelParameterGroupElement = new ModelParameterGroupElement(mParser, mCommon);

                mpCurrentHandler = mpModelParameterGroupElement;
              }
            else if (!strcmp(pszName, "ModelParameter"))
              {
                /* If we do not have an etc element handler we create one. */
                if (!mpModelParameterElement)
                  mpModelParameterElement = new ModelParameterElement(mParser, mCommon);

                mpCurrentHandler = mpModelParameterElement;
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

void CCopasiXMLParser::ModelParameterSetElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case ModelParameterSet:

        if (strcmp(pszName, "ModelParameterSet"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ModelParameterSet", mParser.getCurrentLineNumber());

        mCommon.ModelParameterGroupStack.pop();

        mParser.popElementHandler();
        mLastKnownElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case MiriamAnnotation:

        if (strcmp(pszName, "MiriamAnnotation"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "MiriamAnnotation", mParser.getCurrentLineNumber());

        {
          CModelParameterSet * pModelParameterSet = static_cast< CModelParameterSet * >(mCommon.ModelParameterGroupStack.top());
          pModelParameterSet->setMiriamAnnotation(mCommon.CharacterData, pModelParameterSet->getKey(), mKey);
        }

        mCommon.CharacterData = "";
        break;

      case Comment:

        if (strcmp(pszName, "Comment"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "Comment", mParser.getCurrentLineNumber());

        static_cast< CModelParameterSet * >(mCommon.ModelParameterGroupStack.top())->setNotes(mCommon.CharacterData);
        mCommon.CharacterData = "";
        break;


      case Content:

        if (strcmp(pszName, "ModelParameterGroup") &&
            strcmp(pszName, "ModelParameter"))
          {
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                           pszName, "ModelParameterGroup or ModelParameter", mParser.getCurrentLineNumber());
          }

        if (mCommon.pCurrentModelParameter != NULL)
          {
            mCommon.ModelParameterGroupStack.top()->add(mCommon.pCurrentModelParameter);
            mCommon.pCurrentModelParameter = NULL;
          }

        // Content may be repeated therefore we set to the previous element which is Comment.
        mCurrentElement = Comment;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::ModelParameterGroupElement::ModelParameterGroupElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
    mpModelParameterGroupElement(NULL),
    mpModelParameterElement(NULL)
{}

CCopasiXMLParser::ModelParameterGroupElement::~ModelParameterGroupElement()
{
  pdelete(mpModelParameterGroupElement);
  pdelete(mpModelParameterElement);
}

void CCopasiXMLParser::ModelParameterGroupElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * CN;

  mpCurrentHandler = NULL;
  mCurrentElement = mLastKnownElement;

  while (mpCurrentHandler == NULL)
    {
      mCurrentElement++; /* We should always be on the next element */

      switch (mCurrentElement)
        {
          case ModelParameterGroup:

            if (strcmp(pszName, "ModelParameterGroup"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                             pszName, "ModelParameterGroup", mParser.getCurrentLineNumber());

            mLastKnownElement = ModelParameterGroup;

            // Element specific code.
            CN = mParser.getAttributeValue("cn", papszAttrs);

            {
              CModelParameterGroup * pModelParameterGroup = new CModelParameterGroup(mCommon.ModelParameterGroupStack.top());
              pModelParameterGroup->setCN(std::string(CN));
              mCommon.ModelParameterGroupStack.push(pModelParameterGroup);
            }
            return;

          case Content:

            if (!strcmp(pszName, "ModelParameterGroup"))
              {
                /* If we do not have an etc element handler we create one. */
                if (!mpModelParameterGroupElement)
                  mpModelParameterGroupElement = new ModelParameterGroupElement(mParser, mCommon);

                mpCurrentHandler = mpModelParameterGroupElement;
              }
            else if (!strcmp(pszName, "ModelParameter"))
              {
                /* If we do not have an etc element handler we create one. */
                if (!mpModelParameterElement)
                  mpModelParameterElement = new ModelParameterElement(mParser, mCommon);

                mpCurrentHandler = mpModelParameterElement;
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


void CCopasiXMLParser::ModelParameterGroupElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case ModelParameterGroup:

        if (strcmp(pszName, "ModelParameterGroup"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ModelParameterGroup", mParser.getCurrentLineNumber());

        mCommon.pCurrentModelParameter = mCommon.ModelParameterGroupStack.top();
        mCommon.ModelParameterGroupStack.pop();

        mParser.popElementHandler();
        mLastKnownElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case Content:

        if (strcmp(pszName, "ModelParameterGroup") &&
            strcmp(pszName, "ModelParameter"))
          {
            CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                           pszName, "ModelParameterGroup or ModelParameter", mParser.getCurrentLineNumber());
          }

        if (mCommon.pCurrentModelParameter != NULL)
          {
            mCommon.ModelParameterGroupStack.top()->add(mCommon.pCurrentModelParameter);
            mCommon.pCurrentModelParameter = NULL;
          }

        // Content may be repeated therefore we set to the previous element which is ModelParameterGroup.
        mCurrentElement = ModelParameterGroup;
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

CCopasiXMLParser::ModelParameterElement::ModelParameterElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
    CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common)
{}

CCopasiXMLParser::ModelParameterElement::~ModelParameterElement()
{}

void CCopasiXMLParser::ModelParameterElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  const char * CN;
  const char * pValue;
  C_FLOAT64 Value = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
  const char * pType;
  CModelParameter::Type Type;

  mpCurrentHandler = NULL;
  mCurrentElement = mLastKnownElement;

  while (mpCurrentHandler == NULL)
    {
      mCurrentElement++; /* We should always be on the next element */

      switch (mCurrentElement)
        {
          case ModelParameter:

            if (strcmp(pszName, "ModelParameter"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                             pszName, "ModelParameter", mParser.getCurrentLineNumber());

            mLastKnownElement = ModelParameter;

            // Element specific code.
            CN = mParser.getAttributeValue("cn", papszAttrs);
            pValue = mParser.getAttributeValue("value", papszAttrs);
            pType = mParser.getAttributeValue("type", papszAttrs);

            if (pValue != NULL)
              {
                Value = CCopasiXMLInterface::DBL(pValue);
              }

            Type = toEnum(pType, CModelParameter::TypeNames, CModelParameter::unknown);

            mCommon.pCurrentModelParameter = new CModelParameter(mCommon.ModelParameterGroupStack.top(), Type);
            mCommon.pCurrentModelParameter->setCN(std::string(CN));
            mCommon.pCurrentModelParameter->setValue(Value);
            return;

          case InitialExpression:

            if (!strcmp(pszName, "InitialExpression"))
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


void CCopasiXMLParser::ModelParameterElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case ModelParameter:

        if (strcmp(pszName, "ModelParameter"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ModelParameter", mParser.getCurrentLineNumber());

        mCommon.pCurrentModelParameter = mCommon.ModelParameterGroupStack.top();
        mCommon.ModelParameterGroupStack.pop();

        mParser.popElementHandler();
        mLastKnownElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case InitialExpression:

        if (strcmp(pszName, "InitialExpression"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "InitialExpression", mParser.getCurrentLineNumber());

        {
          size_t Size = CCopasiMessage::size();

          mCommon.pCurrentModelParameter->setInitialExpression(mCommon.CharacterData);

          // Remove error messages created by setExpression as this may fail
          // due to incomplete model specification at this time.
          while (CCopasiMessage::size() > Size)
            CCopasiMessage::getLastMessage();
        }
        break;

      case UNKNOWN_ELEMENT:
        mCurrentElement = mLastKnownElement;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                       pszName, "???", mParser.getCurrentLineNumber());
        break;
    }

  return;
}

