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

#include "SliderHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/utilities/CSlider.h"

/**
 * Replace Slider with the name type of the handler and implement the
 * three methods below.
 */
SliderHandler::SliderHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Slider)
{
  init();
}

// virtual
SliderHandler::~SliderHandler()
{}

// virtual
CXMLHandler * SliderHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CSlider * pSlider = NULL;
  const char * Key;
  const char * AssociatedEntityKey;
  const char * ObjectCN;
  const char * objectType;
  CSlider::Type ObjectType;
  const char * tmp;
  C_FLOAT64 ObjectValue;
  C_FLOAT64 MinValue;
  C_FLOAT64 MaxValue;
  unsigned C_INT32 TickNumber;
  unsigned C_INT32 TickFactor;
  const char* scaling;

  switch (mCurrentElement.first)
    {
      case Slider:
        Key = mpParser->getAttributeValue("key", papszAttrs);
        AssociatedEntityKey = mpParser->getAttributeValue("associatedEntityKey", papszAttrs);
        ObjectCN = mpParser->getAttributeValue("objectCN", papszAttrs);
        objectType = mpParser->getAttributeValue("objectType", papszAttrs);
        ObjectType = toEnum(objectType, CSlider::TypeName, CSlider::Float);
        tmp = mpParser->getAttributeValue("objectValue", papszAttrs);
        ObjectValue = CCopasiXMLInterface::DBL(tmp);
        tmp = mpParser->getAttributeValue("minValue", papszAttrs);
        MinValue = CCopasiXMLInterface::DBL(tmp);
        tmp = mpParser->getAttributeValue("maxValue", papszAttrs);
        MaxValue = CCopasiXMLInterface::DBL(tmp);
        tmp = mpParser->getAttributeValue("tickNumber", papszAttrs, "1000");
        TickNumber = strToUnsignedInt(tmp);
        tmp = mpParser->getAttributeValue("tickFactor", papszAttrs, "100");
        TickFactor = strToUnsignedInt(tmp);

        scaling = mpParser->getAttributeValue("scaling", papszAttrs, "linear");

        // This is always the case if the XML is conforming to the schema.

        if (mpData->mKeyMap.get(AssociatedEntityKey))
          {
            pSlider = new CSlider("slider", mpData->pGUI->getSliderList());
            addFix(Key, pSlider);

            if (strncmp(AssociatedEntityKey, "", 1))
              {
                pSlider->setAssociatedEntityKey(mpData->mKeyMap.get(AssociatedEntityKey)->getKey());
              }
            else
              {
                pSlider->setAssociatedEntityKey("");
              }

            pSlider->setSliderObject((std::string) ObjectCN);
            pSlider->setSliderType(ObjectType);
            pSlider->setMaxValue(MaxValue);
            pSlider->setMinValue(MinValue);
            pSlider->setSliderValue(ObjectValue);
            pSlider->setTickNumber(TickNumber);
            pSlider->setTickFactor(TickFactor);
            pSlider->setScaling(pSlider->convertScaleNameToScale(scaling));
            mpData->pGUI->getSliderList()->add(pSlider, true);
          }

        break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return NULL;
}

// virtual
bool SliderHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Slider:
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
CXMLHandler::sProcessLogic * SliderHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Slider, HANDLER_COUNT}},
    {"Slider", Slider, Slider, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
