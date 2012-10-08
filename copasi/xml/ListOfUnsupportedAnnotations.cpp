// Copyright (C) 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * ListOfUnsupportedAnnotations.cpp
 *
 *  Created on: May 24, 2012
 *      Author: shoops
 */

#include "copasi.h"

#include "CExpat.h"
#include "CCopasiXMLParser.h"
#include "CCopasiXMLInterface.h"

#define START_ELEMENT   -1
#define UNKNOWN_ELEMENT -2

CCopasiXMLParser::UnsupportedAnnotationElement::UnsupportedAnnotationElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mName(),
  mXML(),
  mLevel(0),
  mElementEmpty()
{}

// virtual
CCopasiXMLParser::UnsupportedAnnotationElement::~UnsupportedAnnotationElement()
{}

// virtual
void CCopasiXMLParser::UnsupportedAnnotationElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mCurrentElement++; /* We should always be on the next element */
  const XML_Char ** ppAttrs;

  if (mLevel) mCurrentElement = Content;

  switch (mCurrentElement)
    {
      case UnsupportedAnnotation:

        if (strcmp(pszName, "UnsupportedAnnotation"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                         pszName, "UnsupportedAnnotation", mParser.getCurrentLineNumber());

        mName = mParser.getAttributeValue("name", papszAttrs);
        mXML.str("");
        mLevel = 0;
        mParser.enableCharacterDataHandler();
        mElementEmpty.push(false);
        break;

      case Content:

        if (mElementEmpty.top() == true)
          {
            mXML << ">";
            mElementEmpty.top() = false;
          }

        mXML << CCopasiXMLInterface::encode(mParser.getCharacterData(), CCopasiXMLInterface::character);
        mXML << "<" << pszName;

        for (ppAttrs = papszAttrs; *ppAttrs && **ppAttrs; ppAttrs += 2)
          mXML << " " << *ppAttrs << "=\""
               << CCopasiXMLInterface::encode(*(ppAttrs + 1), CCopasiXMLInterface::attribute) << "\"";

        mLevel++;
        mElementEmpty.push(true);

        mParser.enableCharacterDataHandler();
        break;

      default:
        mLastKnownElement = mCurrentElement - 1;
        mCurrentElement = UNKNOWN_ELEMENT;
        mParser.pushElementHandler(&mParser.mUnknownElement);
        mParser.onStartElement(pszName, papszAttrs);
        break;
    }

  return;
}

// virtual
void CCopasiXMLParser::UnsupportedAnnotationElement::end(const XML_Char *pszName)
{
  std::string XML;

  switch (mCurrentElement)
    {
      case UnsupportedAnnotation:

        if (strcmp(pszName, "UnsupportedAnnotation"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "UnsupportedAnnotation", mParser.getCurrentLineNumber());

        mXML << CCopasiXMLInterface::encode(mParser.getCharacterData(), CCopasiXMLInterface::character);

        XML = mXML.str();

        {
          // remove leading whitepsaces
          std::string::size_type pos = XML.find_first_not_of("\x0a\x0d\t ");

          if (pos != 0) XML.erase(0, pos);

          // remove trailing whitepsace
          pos = XML.find_last_not_of("\x0a\x0d\t ");

          if (pos < XML.length())
            XML = XML.substr(0, pos + 1);
        }

        mXML.str(XML);

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;
        mElementEmpty.pop();

        deleteCurrentHandler();

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case Content:
        XML = mParser.getCharacterData();

        // Check whether and how we need to close the element
        if (mElementEmpty.top() == true)
          {
            if (XML != "")
              {
                mElementEmpty.top() = false;
                mXML << ">";
              }
            else
              mXML << " />";
          }

        if (XML != "")
          mXML << CCopasiXMLInterface::encode(XML, CCopasiXMLInterface::character);

        if (mElementEmpty.top() == false)
          mXML << "</" << pszName << ">";

        mElementEmpty.pop();
        mElementEmpty.top() = false;
        mLevel--;

        if (!mLevel) mCurrentElement = UnsupportedAnnotation;

        mParser.enableCharacterDataHandler();
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

const std::string & CCopasiXMLParser::UnsupportedAnnotationElement::getName() const
{
  return mName;
}

std::string CCopasiXMLParser::UnsupportedAnnotationElement::getXML() const
{
  return mXML.str();
}

CCopasiXMLParser::ListOfUnsupportedAnnotationsElement::ListOfUnsupportedAnnotationsElement(CCopasiXMLParser & parser,
    SCopasiXMLParserCommon & common):
  CXMLElementHandler< CCopasiXMLParser, SCopasiXMLParserCommon >(parser, common),
  mUnsupportedAnnotations(),
  mpUnsupportedAnnotationElement(NULL)
{}

// virtual
CCopasiXMLParser::ListOfUnsupportedAnnotationsElement::~ListOfUnsupportedAnnotationsElement()
{
  pdelete(mpUnsupportedAnnotationElement);
}

// virtual
void CCopasiXMLParser::ListOfUnsupportedAnnotationsElement::start(const XML_Char *pszName,
    const XML_Char **papszAttrs)
{
  mpCurrentHandler = NULL;
  mCurrentElement = mLastKnownElement;

  while (mpCurrentHandler == NULL)
    {
      mCurrentElement++; /* We should always be on the next element */

      switch (mCurrentElement)
        {
          case ListOfUnsupportedAnnotations:

            if (strcmp(pszName, "ListOfUnsupportedAnnotations"))
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 10,
                             pszName, "ListOfUnsupportedAnnotations", mParser.getCurrentLineNumber());

            mLastKnownElement = ListOfUnsupportedAnnotations;
            mUnsupportedAnnotations.clear();

            return;

          case UnsupportedAnnotation:

            if (!strcmp(pszName, "UnsupportedAnnotation"))
              {
                /* If we do not have a ModelParameterSet element handler we create one. */
                if (!mpUnsupportedAnnotationElement)
                  mpUnsupportedAnnotationElement = new UnsupportedAnnotationElement(mParser, mCommon);

                mpCurrentHandler = mpUnsupportedAnnotationElement;
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
void CCopasiXMLParser::ListOfUnsupportedAnnotationsElement::end(const XML_Char *pszName)
{
  switch (mCurrentElement)
    {
      case ListOfUnsupportedAnnotations:

        if (strcmp(pszName, "ListOfUnsupportedAnnotations"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "ListOfUnsupportedAnnotations", mParser.getCurrentLineNumber());

        mParser.popElementHandler();
        mCurrentElement = START_ELEMENT;

        /* Tell the parent element we are done. */
        mParser.onEndElement(pszName);
        break;

      case UnsupportedAnnotation:

        if (strcmp(pszName, "UnsupportedAnnotation"))
          CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                         pszName, "UnsupportedAnnotation", mParser.getCurrentLineNumber());

        if (mpUnsupportedAnnotationElement != NULL)
          {
            mUnsupportedAnnotations[mpUnsupportedAnnotationElement->getName()] =
              mpUnsupportedAnnotationElement->getXML();
          }

        mLastKnownElement = ListOfUnsupportedAnnotations;
        mCurrentElement = ListOfUnsupportedAnnotations;
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

const CAnnotation::UnsupportedAnnotation & CCopasiXMLParser::ListOfUnsupportedAnnotationsElement::getUnsupportedAnnotations() const
{
  return mUnsupportedAnnotations;
}
