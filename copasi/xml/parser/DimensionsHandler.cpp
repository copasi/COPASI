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

#include "DimensionsHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CLBase.h"

DimensionsHandler::DimensionsHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Dimensions)
{
  init();

  if (mpData->pDimensions == NULL)
    {
      mpData->pDimensions = new CLDimensions();
    }
}

// virtual
DimensionsHandler::~DimensionsHandler()
{
  pdelete(mpData->pDimensions);
}

// virtual
CXMLHandler * DimensionsHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  const char * attr;

  switch (mCurrentElement.first)
    {
      case Dimensions:
        attr = mpParser->getAttributeValue("width", papszAttrs, "0");
        mpData->pDimensions->setWidth(CCopasiXMLInterface::DBL(attr));
        attr = mpParser->getAttributeValue("height", papszAttrs, "0");
        mpData->pDimensions->setHeight(CCopasiXMLInterface::DBL(attr));
        attr = mpParser->getAttributeValue("depth", papszAttrs, "0");
        mpData->pDimensions->setDepth(CCopasiXMLInterface::DBL(attr));
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return NULL;
}

// virtual
bool DimensionsHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Dimensions:
        finished = true;
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * DimensionsHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Dimensions, HANDLER_COUNT}},
    {"Dimensions", Dimensions, Dimensions, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
