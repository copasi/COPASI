// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CXMLHandler.h"
#include "CXMLParser.h"

CXMLHandler::CXMLHandler(CXMLParser & parser, CXMLParserData & data, const CXMLHandler::Type & type):
  mpParser(&parser),
  mpData(&data),
  mType(type),
  mElementName2Type(),
  mValidElements(),
  mCurrentElement(BEFORE),
  mLastKnownElement(BEFORE)
{}

// virtual
CXMLHandler::~CXMLHandler() {}

void CXMLHandler::start(const XML_Char * pszName,
                        const XML_Char ** papszAttrs)
{
  CXMLHandler * pNextHandler = NULL;
  std::map< std::string, Type >::iterator itElementType = mElementName2Type.find(pszName);

  if (itElementType != mElementName2Type.end())
    {
      const std::set< Type > ValidElements =  mValidElements[mLastKnownElement];
      std::set< Type >::iterator itValidElement = ValidElements.find(itElementType->second);

      if (itValidElement != ValidElements.end())
        {
          mCurrentElement = itElementType->second;
          mLastKnownElement = mCurrentElement;
        }
      else
        {
          // The element is out of order
          CCopasiMessage(CCopasiMessage::WARNING, MCXML + 10,
                         pszName, getExpectedElements(mCurrentElement).c_str(), mpParser->getCurrentLineNumber());

          // We ignore it
          mCurrentElement = UNKNOWN;
        }
    }
  else
    {
      CCopasiMessage(CCopasiMessage::WARNING, MCXML + 3,
                     pszName, mpParser->getCurrentLineNumber());

      mCurrentElement = UNKNOWN;
    }

  if (mCurrentElement != UNKNOWN)
    {
      pNextHandler = processStart(pszName, papszAttrs);
    }
  else
    {
      pNextHandler = getHandler(UNKNOWN);
    }

  if (pNextHandler != NULL)
    {
      mpParser->pushElementHandler(pNextHandler);
      mpParser->onStartElement(pszName, papszAttrs);
    }
}

void CXMLHandler::end(const XML_Char * pszName)
{
  bool finished = false;
  std::map< std::string, Type >::iterator itElementType = mElementName2Type.find(pszName);

  if (itElementType != mElementName2Type.end())
    {
      if (itElementType->second == mType)
        {
          const std::set< Type > ValidElements =  mValidElements[mLastKnownElement];

          if (ValidElements.find(AFTER) == ValidElements.end())
            {
              // We have an element closing without finding all required child elements
              CCopasiMessage(CCopasiMessage::WARNING, MCXML + 24,
                             getExpectedElements(mLastKnownElement).c_str(), mpParser->getCurrentLineNumber());
            }

          mCurrentElement = mType;
        }

      if (itElementType->second == mCurrentElement)
        {
          finished = processEnd(pszName);
        }
    }
  else if (mCurrentElement == UNKNOWN)
    {
      mCurrentElement = mLastKnownElement;
    }
  else
    {
      CCopasiMessage(CCopasiMessage::WARNING, MCXML + 11,
                     pszName, getElementName(mCurrentElement).c_str(), mpParser->getCurrentLineNumber());
    }

  if (finished)
    {
      mCurrentElement = BEFORE;
      mLastKnownElement = BEFORE;
      mpParser->popElementHandler();
      mpParser->onEndElement(pszName);
    }
}

CXMLHandler * CXMLHandler::getHandler(const Type & type)
{
  return mpParser->getHandler(type);
}

void CXMLHandler::addFix(const std::string & key, CCopasiObject * pObject)
{
  if (!mpData->mpKeyMap->addFix(key, pObject))
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 22, key.c_str(), mpParser->getCurrentLineNumber());
    }
}

void CXMLHandler::init()
{
  sProcessLogic * pElementInfo = getProcessLogic();
  assert(pElementInfo != NULL);

  while (pElementInfo != NULL && pElementInfo->elementType != AFTER)
    {
      std::set< CXMLHandler::Type > ValidElements;
      Type * pValidElement = pElementInfo->validElements;

      while (pValidElement != NULL && *pValidElement != HANDLER_COUNT)
        {
          ValidElements.insert(*pValidElement);
          ++pValidElement;
        }

      mElementName2Type[pElementInfo->elementName] = pElementInfo->elementType;
      mValidElements[pElementInfo->elementType] = ValidElements;

      ++pElementInfo;
    }
}

std::string CXMLHandler::getElementName(const Type & type) const
{
  std::map< std::string, Type >::const_iterator it = mElementName2Type.begin();
  std::map< std::string, Type >::const_iterator end = mElementName2Type.end();

  for (; it != end; ++it)
    {
      if (it->second == type) return it->first;
    }

  return "UNKNOWN";
}

std::string CXMLHandler::getExpectedElements(const Type & type) const
{
  std::map< Type, std::set< Type > >::const_iterator found = mValidElements.find(type);

  if (found == mValidElements.end())
    {
      return "NONE";
    }

  bool firstTime = true;
  std::string ExpectedElements;
  std::set< Type >::const_iterator it = found->second.begin();
  std::set< Type >::const_iterator end = found->second.end();

  for (; it != end; ++it)
    {
      if (!firstTime)
        {
          ExpectedElements += ", ";
        }

      ExpectedElements += getElementName(*it);
      firstTime = false;
    }

  if (firstTime)
    {
      return "NONE";
    }

  return ExpectedElements;
}
