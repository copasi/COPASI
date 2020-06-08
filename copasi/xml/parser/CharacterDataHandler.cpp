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

#include "CharacterDataHandler.h"
#include "CXMLParser.h"

/**
 * Replace CharacterData with the name type of the handler and implement the
 * three methods below.
 */
CharacterDataHandler::CharacterDataHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::CharacterData),
  mCurrentElementName("")
{
  init();
}

// virtual
CharacterDataHandler::~CharacterDataHandler()
{}

// virtual
void CharacterDataHandler::start(const XML_Char * pszName,
                                 const XML_Char ** papszAttrs)
{
  processStart(pszName, papszAttrs);
}

// virtual
void CharacterDataHandler::end(const XML_Char * pszName)
{
  if (processEnd(pszName))
    {
      mpParser->popElementHandler();
      mpParser->onEndElement(pszName);
    }
}

// virtual
CXMLHandler * CharacterDataHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  mCurrentElementName = pszName;
  mpParser->enableCharacterDataHandler(true);

  return NULL;
}

// virtual
bool CharacterDataHandler::processEnd(const XML_Char * pszName)
{
  if (strcmp(pszName, mCurrentElementName.c_str()))
    CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 11,
                   pszName, mCurrentElementName.c_str(), mpParser->getCurrentLineNumber());

  mpData->CharacterData = mpParser->getCharacterData("\x0a\x0d\t", "");

  std::string::size_type Start = mpData->CharacterData.find_first_not_of(" ");

  if (Start == std::string::npos)
    mpData->CharacterData = "";
  else
    {
      std::string::size_type End = mpData->CharacterData.find_last_not_of(" ");

      if (End == std::string::npos)
        mpData->CharacterData = mpData->CharacterData.substr(Start);
      else
        mpData->CharacterData = mpData->CharacterData.substr(Start, End - Start + 1);
    }

  return true;
}

// virtual
CXMLHandler::sProcessLogic * CharacterDataHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {CharacterData, HANDLER_COUNT}},
    {"CharacterData", CharacterData, CharacterData, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
