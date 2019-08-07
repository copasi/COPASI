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

#include "RadialGradientHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/layout/CLayout.h"

RadialGradientHandler::RadialGradientHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::RadialGradient)
{
  init();
}

// virtual
RadialGradientHandler::~RadialGradientHandler()
{}

// virtual
CXMLHandler * RadialGradientHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  const char * CX;
  const char * CY;
  const char * CZ;
  const char * R;
  const char * FX;
  const char * FY;
  const char * FZ;
  const char * ID;
  const char * SPREADMETHOD;
  CLRadialGradient* pRadialGradient = NULL;

  switch (mCurrentElement.first)
    {
      case RadialGradient:
        CX = mpParser->getAttributeValue("cx", papszAttrs, false);
        CY = mpParser->getAttributeValue("cy", papszAttrs, false);
        CZ = mpParser->getAttributeValue("cz", papszAttrs, false);
        FX = mpParser->getAttributeValue("fx", papszAttrs, false);
        FY = mpParser->getAttributeValue("fy", papszAttrs, false);
        FZ = mpParser->getAttributeValue("fz", papszAttrs, false);
        R =  mpParser->getAttributeValue("r", papszAttrs);
        ID = mpParser->getAttributeValue("id", papszAttrs);
        SPREADMETHOD = mpParser->getAttributeValue("spreadMethod", papszAttrs, "pad");
        pRadialGradient = mpData->pRenderInformation->createRadialGradientDefinition();
        pRadialGradient->setId(ID);

        if (CX == NULL)
          {
            CX = "50%";
          }

        if (CY == NULL)
          {
            CY = "50%";
          }

        if (CZ == NULL)
          {
            CZ = "50%";
          }

        pRadialGradient->setCenter(CLRelAbsVector(CX), CLRelAbsVector(CY), CLRelAbsVector(CZ));

        if (R == NULL)
          {
            R = "50%";
          }

        pRadialGradient->setRadius(CLRelAbsVector(R));

        if (FX == NULL)
          {
            FX = CX;
          }

        if (FY == NULL)
          {
            FY = CY;
          }

        if (FZ == NULL)
          {
            FZ = CZ;
          }

        pRadialGradient->setFocalPoint(CLRelAbsVector(FX), CLRelAbsVector(FY), CLRelAbsVector(FZ));

        if (!strcmp(SPREADMETHOD, "reflect"))
          {
            pRadialGradient->setSpreadMethod(CLGradientBase::REFLECT);
          }
        else if (!strcmp(SPREADMETHOD, "repeat"))
          {
            pRadialGradient->setSpreadMethod(CLGradientBase::REPEAT);
          }
        else
          {
            pRadialGradient->setSpreadMethod(CLGradientBase::PAD);
          }

        mpData->pGradient = pRadialGradient;
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
bool RadialGradientHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case RadialGradient:
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
CXMLHandler::sProcessLogic * RadialGradientHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {RadialGradient, HANDLER_COUNT}},
    {"RadialGradient", RadialGradient, RadialGradient, {GradientStop, HANDLER_COUNT}},
    {"Stop", GradientStop, GradientStop, {GradientStop, AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
