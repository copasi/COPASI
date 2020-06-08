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

#include "UnsupportedAnnotationHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

/**
 * Replace UnsupportedAnnotation with the name type of the handler and implement the
 * three methods below.
 */
UnsupportedAnnotationHandler::UnsupportedAnnotationHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::UnsupportedAnnotation),
  mName(),
  mXML(),
  mElementEmpty()
{
  init();
}

// virtual
UnsupportedAnnotationHandler::~UnsupportedAnnotationHandler()
{}

// virtual
void UnsupportedAnnotationHandler::start(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  processStart(pszName, papszAttrs);
  mLevel++;
}

// virtual
void UnsupportedAnnotationHandler::end(const XML_Char * pszName)
{
  mLevel--;

  if (processEnd(pszName))
    {
      mpParser->popElementHandler();
      mpParser->onEndElement(pszName);
    }
}

// virtual
CXMLHandler * UnsupportedAnnotationHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  const XML_Char ** ppAttrs;

  if (mLevel == 0)
    {
      mName = mpParser->getAttributeValue("name", papszAttrs);
      mXML.str("");
      mpParser->enableCharacterDataHandler();
      mElementEmpty.push(false);
    }
  else
    {
      if (mElementEmpty.top() == true)
        {
          mXML << ">";
          mElementEmpty.top() = false;
        }

      mXML << CCopasiXMLInterface::encode(mpParser->getCharacterData(), CCopasiXMLInterface::character);
      mXML << "<" << pszName;

      for (ppAttrs = papszAttrs; *ppAttrs && **ppAttrs; ppAttrs += 2)
        mXML << " " << *ppAttrs << "=\""
             << CCopasiXMLInterface::encode(*(ppAttrs + 1), CCopasiXMLInterface::attribute) << "\"";

      mElementEmpty.push(true);
      mpParser->enableCharacterDataHandler();
    }

  return NULL;
}

// virtual
bool UnsupportedAnnotationHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;
  std::string XML;

  if (mLevel == 0)
    {
      finished = true;
      mXML << CCopasiXMLInterface::encode(mpParser->getCharacterData(), CCopasiXMLInterface::character);
      XML = mXML.str();

      // remove leading whitepsaces
      std::string::size_type pos = XML.find_first_not_of("\x0a\x0d\t ");

      if (pos != 0) XML.erase(0, pos);

      // remove trailing whitepsace
      pos = XML.find_last_not_of("\x0a\x0d\t ");

      if (pos < XML.length())
        XML = XML.substr(0, pos + 1);

      mXML.str(XML);

      mElementEmpty.pop();
      assert(mElementEmpty.empty());

      mpData->mUnsupportedAnnotations[mName] = mXML.str();
    }
  else
    {
      XML = mpParser->getCharacterData();

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

      mpParser->enableCharacterDataHandler();
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * UnsupportedAnnotationHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {UnsupportedAnnotation, HANDLER_COUNT}},
    {"UnsupportedAnnotation", UnsupportedAnnotation, UnsupportedAnnotation, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
