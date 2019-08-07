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

#include "ListOfHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

/**
 * Replace ListOfAssignments with the name type of the handler and implement the
 * three methods below.
 */
ListOfHandler::ListOfHandler(const CXMLHandler::sProcessLogic &listLogic,
                             const CXMLHandler::sProcessLogic &contentLogic,
                             CXMLParser & parser,
                             CXMLParserData & data):
  CXMLHandler(parser, data, listLogic.handlerType),
  mListLogic(listLogic),
  mContentLogic(contentLogic)
{
  mElementName2Type["BEFORE"] = std::make_pair(BEFORE, BEFORE);
  mValidElements[BEFORE].insert(mListLogic.elementType);

  mElementName2Type[mListLogic.elementName] = std::make_pair(mListLogic.elementType, mListLogic.handlerType);
  mValidElements[mListLogic.elementType].insert(mContentLogic.elementType);
  mValidElements[mListLogic.elementType].insert(AFTER);

  mElementName2Type[mContentLogic.elementName] = std::make_pair(mContentLogic.elementType, mContentLogic.handlerType);
  mValidElements[mContentLogic.elementType].insert(mContentLogic.elementType);
  mValidElements[mContentLogic.elementType].insert(AFTER);
}

// virtual
ListOfHandler::~ListOfHandler()
{}

// virtual
CXMLHandler * ListOfHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  if (mCurrentElement.first == mListLogic.elementType)
    {}
  else if (mCurrentElement.first == mContentLogic.elementType)
    {
      pHandlerToCall = getHandler(mCurrentElement.second);
    }
  else
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                     mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
    }

  return pHandlerToCall;
}

// virtual
bool ListOfHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  if (mCurrentElement.first == mListLogic.elementType)
    {
      finished = true;
    }
  else if (mCurrentElement.first == mContentLogic.elementType)
    {}
  else
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                     mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * ListOfHandler::getProcessLogic() const
{
  return NULL;
}
