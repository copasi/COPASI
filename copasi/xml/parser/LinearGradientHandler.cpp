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

#include "LinearGradientHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CLayout.h"

/**
 * Replace LinearGradient with the name type of the handler and implement the
 * three methods below.
 */
LinearGradientHandler::LinearGradientHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::LinearGradient)
{
  init();
}

// virtual
LinearGradientHandler::~LinearGradientHandler()
{}

// virtual
CXMLHandler * LinearGradientHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  const char * X1;
  const char * Y1;
  const char * Z1;
  const char * X2;
  const char * Y2;
  const char * Z2;
  const char * ID;
  const char * SPREADMETHOD;
  CLLinearGradient* pLinearGradient = NULL;

  switch (mCurrentElement.first)
    {
      case LinearGradient:
        X1 = mpParser->getAttributeValue("x1", papszAttrs);
        Y1 = mpParser->getAttributeValue("y1", papszAttrs);
        Z1 = mpParser->getAttributeValue("z1", papszAttrs, false);
        X2 = mpParser->getAttributeValue("x2", papszAttrs);
        Y2 = mpParser->getAttributeValue("y2", papszAttrs);
        Z2 = mpParser->getAttributeValue("z2", papszAttrs, false);
        ID = mpParser->getAttributeValue("id", papszAttrs);
        SPREADMETHOD = mpParser->getAttributeValue("spreadMethod", papszAttrs, "pad");
        pLinearGradient = mpData->pRenderInformation->createLinearGradientDefinition();
        pLinearGradient->setId(ID);

        if (Z1 == NULL)
          {
            pLinearGradient->setPoint1(CLRelAbsVector(X1), CLRelAbsVector(Y1));
          }
        else
          {
            pLinearGradient->setPoint1(CLRelAbsVector(X1), CLRelAbsVector(Y1), CLRelAbsVector(Z1));
          }

        if (Z2 == NULL)
          {
            pLinearGradient->setPoint2(CLRelAbsVector(X2), CLRelAbsVector(Y2));
          }
        else
          {
            pLinearGradient->setPoint2(CLRelAbsVector(X2), CLRelAbsVector(Y2), CLRelAbsVector(Z2));
          }

        if (!strcmp(SPREADMETHOD, "reflect"))
          {
            pLinearGradient->setSpreadMethod(CLGradientBase::REFLECT);
          }
        else if (!strcmp(SPREADMETHOD, "repeat"))
          {
            pLinearGradient->setSpreadMethod(CLGradientBase::REPEAT);
          }
        else
          {
            pLinearGradient->setSpreadMethod(CLGradientBase::PAD);
          }

        mpData->pGradient = pLinearGradient;
        break;

      case GradientStop:
        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return pHandlerToCall;
}

// virtual
bool LinearGradientHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case LinearGradient:
        mpData->pGradient = NULL;
        finished = true;
        break;

      case GradientStop:
        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * LinearGradientHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {LinearGradient, HANDLER_COUNT}},
    {"LinearGradient", LinearGradient, LinearGradient, {GradientStop, HANDLER_COUNT}},
    {"Stop", GradientStop, GradientStop, {GradientStop, AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
