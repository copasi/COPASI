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

#include "CXMLHandler.h"
#include "CXMLParser.h"

CXMLHandler::CXMLHandler(CXMLParser & parser, CXMLParserData & data, const CXMLHandler::Type & type):
  mpParser(&parser),
  mpData(&data),
  mHandlerType(type),
  mElementName2Type(),
  mValidElements(),
  mCurrentElement(BEFORE, BEFORE),
  mLastKnownElement(BEFORE, BEFORE),
  mLevel(0)
{}

// virtual
CXMLHandler::~CXMLHandler() {}

void CXMLHandler::start(const XML_Char * pszName,
                        const XML_Char ** papszAttrs)
{
  CXMLHandler * pNextHandler = NULL;
  bool IncreaseLevel = false;

  std::map< std::string, std::pair< Type, Type > >::iterator itElementType = mElementName2Type.find(pszName);

  if (itElementType != mElementName2Type.end())
    {
      if (mLevel == 0)
        {
          mElementType = itElementType->second.first;
          IncreaseLevel = true;
        }
      else if (mElementType == itElementType->second.first)
        {
          IncreaseLevel = true;
        }

      const std::set< Type > ValidElements =  mValidElements[mLastKnownElement.first];
      std::set< Type >::iterator itValidElement = ValidElements.find(itElementType->second.first);

      if (itValidElement != ValidElements.end())
        {
          mCurrentElement = itElementType->second;
          mLastKnownElement = mCurrentElement;
        }
      else
        {
          // The element is out of order
          CCopasiMessage(CCopasiMessage::WARNING, MCXML + 10,
                         pszName, getExpectedElements(mCurrentElement.first).c_str(), mpParser->getCurrentLineNumber());

          // We ignore it
          mCurrentElement = std::make_pair(UNKNOWN, UNKNOWN);
        }
    }
  else
    {
      CCopasiMessage(CCopasiMessage::WARNING, MCXML + 3,
                     pszName, mpParser->getCurrentLineNumber());

      mCurrentElement = std::make_pair(UNKNOWN, UNKNOWN);
    }

  if (mCurrentElement.first != UNKNOWN)
    {
      pNextHandler = processStart(pszName, papszAttrs);
    }
  else
    {
      pNextHandler = getHandler(UNKNOWN);
    }

  if (IncreaseLevel) mLevel++;

  if (pNextHandler != NULL)
    {
      mpParser->pushElementHandler(pNextHandler);
      mpParser->onStartElement(pszName, papszAttrs);
    }
}

void CXMLHandler::end(const XML_Char * pszName)
{
  bool finished = false;
  std::map< std::string, std::pair< Type, Type > >::iterator itElementType = mElementName2Type.find(pszName);

  if (itElementType != mElementName2Type.end())
    {
      if (itElementType->second == std::make_pair(mElementType, mHandlerType))
        {
          const std::set< Type > ValidElements =  mValidElements[mLastKnownElement.first];

          if (ValidElements.find(AFTER) == ValidElements.end())
            {
              // We have an element closing without finding all required child elements
              CCopasiMessage(CCopasiMessage::WARNING, MCXML + 24,
                             getExpectedElements(mLastKnownElement.first).c_str(), mpParser->getCurrentLineNumber());
            }

          mCurrentElement = std::make_pair(mElementType, mHandlerType);
          mLevel--;
        }

      if (itElementType->second == mCurrentElement)
        {
          finished = processEnd(pszName);
        }
    }
  else if (mCurrentElement.first == UNKNOWN)
    {
      mCurrentElement = mLastKnownElement;
    }
  else
    {
      CCopasiMessage(CCopasiMessage::WARNING, MCXML + 11,
                     pszName, getElementName(mCurrentElement.first).c_str(), mpParser->getCurrentLineNumber());
    }

  if (finished)
    {
      mCurrentElement = std::make_pair(BEFORE, BEFORE);
      mLastKnownElement = std::make_pair(BEFORE, BEFORE);
      mpParser->popElementHandler();
      mpParser->onEndElement(pszName);
    }
}

CXMLHandler * CXMLHandler::getHandler(const Type & type)
{
  return mpParser->getHandler(type);
}

void CXMLHandler::addFix(const std::string & key, CDataObject * pObject)
{
  if (!mpData->mKeyMap.addFix(key, pObject))
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

      mElementName2Type[pElementInfo->elementName] = std::make_pair(pElementInfo->elementType, pElementInfo->handlerType);
      mValidElements[pElementInfo->elementType] = ValidElements;

      ++pElementInfo;
    }
}

std::string CXMLHandler::getElementName(const Type & type) const
{
  std::map< std::string, std::pair< Type, Type > >::const_iterator it = mElementName2Type.begin();
  std::map< std::string, std::pair< Type, Type > >::const_iterator end = mElementName2Type.end();

  for (; it != end; ++it)
    {
      if (it->second.first == type) return it->first;
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
