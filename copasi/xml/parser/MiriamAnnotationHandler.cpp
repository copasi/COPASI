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

#include "MiriamAnnotationHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

/**
 * Replace MiriamAnnotation with the name type of the handler and implement the
 * three methods below.
 */
MiriamAnnotationHandler::MiriamAnnotationHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::MiriamAnnotation),
  mRDF(),
  mElementEmpty()
{
  init();
}

// virtual
MiriamAnnotationHandler::~MiriamAnnotationHandler()
{}

// virtual
void MiriamAnnotationHandler::start(const XML_Char * pszName,
                                    const XML_Char ** papszAttrs)
{
  processStart(pszName, papszAttrs);
  mLevel++;
}

// virtual
void MiriamAnnotationHandler::end(const XML_Char * pszName)
{
  mLevel--;

  if (processEnd(pszName))
    {
      mpParser->popElementHandler();
      mpParser->onEndElement(pszName);
    }
}

// virtual
CXMLHandler * MiriamAnnotationHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  const XML_Char ** ppAttrs;

  if (mLevel == 0)
    {
      mRDF.str("");
      mpParser->enableCharacterDataHandler();
      mElementEmpty.push(false);
    }
  else
    {
      if (mElementEmpty.top() == true)
        {
          mRDF << ">";
          mElementEmpty.top() = false;
        }

      mRDF << CCopasiXMLInterface::encode(mpParser->getCharacterData());
      mRDF << "<" << pszName;

      for (ppAttrs = papszAttrs; *ppAttrs && **ppAttrs; ppAttrs += 2)
        mRDF << " " << *ppAttrs << "=\""
             << CCopasiXMLInterface::encode(*(ppAttrs + 1), CCopasiXMLInterface::attribute) << "\"";

      mElementEmpty.push(true);
      mpParser->enableCharacterDataHandler();
    }

  return NULL;
}

// virtual
bool MiriamAnnotationHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  if (mLevel == 0)
    {
      finished = true;

      if (mRDF.str() != "")
        mRDF << CCopasiXMLInterface::encode(mpParser->getCharacterData());
      else
        mRDF << mpParser->getCharacterData();

      mpData->CharacterData = mRDF.str();

      {
        // remove leading whitepsaces
        std::string::size_type pos = mpData->CharacterData.find_first_not_of("\x0a\x0d\t ");

        if (pos != 0) mpData->CharacterData.erase(0, pos);

        // remove trailing whitepsace
        pos = mpData->CharacterData.find_last_not_of("\x0a\x0d\t ");

        if (pos < mpData->CharacterData.length())
          mpData->CharacterData = mpData->CharacterData.substr(0, pos + 1);
      }

      mElementEmpty.pop();
      assert(mElementEmpty.empty());
    }
  else
    {
      std::string rdf = mpParser->getCharacterData();

      // Check whether and how we need to close the attribute
      if (mElementEmpty.top() == true)
        {
          if (rdf != "")
            {
              mElementEmpty.top() = false;
              mRDF << ">";
            }
          else
            mRDF << " />";
        }

      if (rdf != "")
        mRDF << CCopasiXMLInterface::encode(rdf);

      if (mElementEmpty.top() == false)
        mRDF << "</" << pszName << ">";

      mElementEmpty.pop();
      mElementEmpty.top() = false;

      mpParser->enableCharacterDataHandler();
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * MiriamAnnotationHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {MiriamAnnotation, HANDLER_COUNT}},
    {"MiriamAnnotation", MiriamAnnotation, MiriamAnnotation, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
