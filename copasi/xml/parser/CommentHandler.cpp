// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

#include "CommentHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

/**
 * Replace Comment with the name type of the handler and implement the
 * three methods below.
 */
CommentHandler::CommentHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Comment)
{
  init();
}

// virtual
CommentHandler::~CommentHandler()
{}

// virtual
void CommentHandler::start(const XML_Char * pszName,
                           const XML_Char ** papszAttrs)
{
  processStart(pszName, papszAttrs);
  mLevel++;
}

// virtual
void CommentHandler::end(const XML_Char * pszName)
{
  mLevel--;

  if (processEnd(pszName))
    {
      mpParser->popElementHandler();
      mpParser->onEndElement(pszName);
    }
}

// virtual
CXMLHandler * CommentHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  const XML_Char ** ppAttrs;

  if (mLevel == 0)
    {
      mXhtml.str("");
      mpParser->enableCharacterDataHandler();
      mpParser->enableSkippedEntityHandler();
      mpParser->setCharacterEncoding(CCopasiXMLInterface::character);
      mElementEmpty.push(false);
    }
  else
    {
      if (mElementEmpty.top() == true)
        {
          mXhtml << ">";
          mElementEmpty.top() = false;
        }

      mXhtml << CCopasiXMLInterface::encode(mpParser->getCharacterData(), CCopasiXMLInterface::none);
      mXhtml << "<" << pszName;

      for (ppAttrs = papszAttrs; *ppAttrs && **ppAttrs; ppAttrs += 2)
        mXhtml << " " << *ppAttrs << "=\""
               << CCopasiXMLInterface::encode(*(ppAttrs + 1), CCopasiXMLInterface::attribute) << "\"";

      mElementEmpty.push(true);
      mpParser->enableCharacterDataHandler();
    }

  return NULL;
}

// virtual
bool CommentHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;
  std::string Xhtml;

  if (mLevel == 0)
    {
      finished = true;

      mXhtml << mpParser->getCharacterData();
      mpData->CharacterData = mXhtml.str();

      // remove leading whitepsaces
      std::string::size_type pos = mpData->CharacterData.find_first_not_of("\x0a\x0d\t ");

      if (pos != 0) mpData->CharacterData.erase(0, pos);

      // remove trailing whitepsace
      pos = mpData->CharacterData.find_last_not_of("\x0a\x0d\t ");

      if (pos < mpData->CharacterData.length())
        mpData->CharacterData = mpData->CharacterData.substr(0, pos + 1);

      mpParser->enableSkippedEntityHandler(false);
      mpParser->setCharacterEncoding(CCopasiXMLInterface::none);
      mElementEmpty.pop();
      assert(mElementEmpty.empty());
    }
  else
    {
      Xhtml = mpParser->getCharacterData();

      // Check whether and how we need to close the attribute
      if (mElementEmpty.top() == true)
        {
          if (Xhtml != "")
            {
              mElementEmpty.top() = false;
              mXhtml << ">";
            }
          else
            mXhtml << " />";
        }

      mXhtml << Xhtml;

      if (mElementEmpty.top() == false)
        mXhtml << "</" << pszName << ">";

      mElementEmpty.pop();
      mElementEmpty.top() = false;

      mpParser->enableCharacterDataHandler();
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * CommentHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Comment, HANDLER_COUNT}},
    {"Comment", Comment, Comment, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
