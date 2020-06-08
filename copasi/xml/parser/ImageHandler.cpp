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

#include "ImageHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CLImage.h"

/**
 * Replace Image with the name type of the handler and implement the
 * three methods below.
 */
ImageHandler::ImageHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Image)
{
  init();
}

// virtual
ImageHandler::~ImageHandler()
{}

// virtual
CXMLHandler * ImageHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  const char * Transform;
  const char * X;
  const char * Y;
  const char * Z;
  const char * WIDTH;
  const char * HEIGHT;
  const char * HREF;

  switch (mCurrentElement.first)
    {
      case Image:
        Transform = mpParser->getAttributeValue("transform", papszAttrs, false);
        X = mpParser->getAttributeValue("x", papszAttrs);
        Y = mpParser->getAttributeValue("y", papszAttrs);
        Z = mpParser->getAttributeValue("z", papszAttrs, "0.0");
        WIDTH = mpParser->getAttributeValue("width", papszAttrs);
        HEIGHT = mpParser->getAttributeValue("height", papszAttrs);
        HREF = mpParser->getAttributeValue("href", papszAttrs);
        mpData->pImage = new CLImage();

        if (Transform != NULL)
          {
            mpData->pImage->parseTransformation(Transform);
          }

        mpData->pImage->setCoordinates(CLRelAbsVector(X), CLRelAbsVector(Y), CLRelAbsVector(Z));
        mpData->pImage->setDimensions(CLRelAbsVector(WIDTH), CLRelAbsVector(HEIGHT));
        mpData->pImage->setImageReference(HREF);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return NULL;
}

// virtual
bool ImageHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Image:
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
CXMLHandler::sProcessLogic * ImageHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Image, HANDLER_COUNT}},
    {"Image", Image, Image, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
