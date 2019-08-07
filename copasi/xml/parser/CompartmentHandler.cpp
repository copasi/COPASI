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

#include "CompartmentHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/model/CModel.h"

/**
 * Replace Compartment with the name type of the handler and implement the
 * three methods below.
 */
CompartmentHandler::CompartmentHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Compartment),
  mpCompartment(NULL),
  mKey()
{
  init();
}

// virtual
CompartmentHandler::~CompartmentHandler()
{}

// virtual
CXMLHandler * CompartmentHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  const char * Name;
  const char * simulationType;
  const char * Dimensionality;
  CModelEntity::Status SimulationType;
  bool AddNoise;

  switch (mCurrentElement.first)
    {
      case Compartment:
        mKey = mpParser->getAttributeValue("key", papszAttrs);
        Name = mpParser->getAttributeValue("name", papszAttrs);
        simulationType = mpParser->getAttributeValue("simulationType", papszAttrs, "fixed");
        SimulationType = CModelEntity::XMLStatus.toEnum(simulationType, CModelEntity::Status::FIXED);
        Dimensionality = mpParser->getAttributeValue("dimensionality", papszAttrs, "3");
        AddNoise = mpParser->toBool(mpParser->getAttributeValue("addNoise", papszAttrs, "false"));

        mpCompartment = new CCompartment();
        addFix(mKey, mpCompartment);

        mpCompartment->setObjectName(Name);
        mpCompartment->setStatus(SimulationType);
        mpCompartment->setDimensionality(strToUnsignedInt(Dimensionality));
        mpCompartment->setHasNoise(AddNoise);

        mpData->pModel->getCompartments().add(mpCompartment, true);
        break;

      case MiriamAnnotation:
      case Comment:
      case Expression:
      case InitialExpression:
      case NoiseExpression:
        pHandlerToCall = getHandler(mCurrentElement.second);
        break;

      case ListOfUnsupportedAnnotations:
        mpData->mUnsupportedAnnotations.clear();
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
bool CompartmentHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Compartment:
        finished = true;
        break;

      case MiriamAnnotation:
        mpCompartment->setMiriamAnnotation(mpData->CharacterData, mpCompartment->getKey(), mKey);
        mpData->CharacterData = "";
        break;

      case Comment:
        mpCompartment->setNotes(mpData->CharacterData);
        mpData->CharacterData = "";
        break;

      case ListOfUnsupportedAnnotations:
        mpCompartment->getUnsupportedAnnotations() = mpData->mUnsupportedAnnotations;
        break;

      case Expression:

      {
        size_t Size = CCopasiMessage::size();

        mpCompartment->setExpression(mpData->CharacterData);

        // Remove error messages created by setExpression as this may fail
        // due to incomplete model specification at this time.
        while (CCopasiMessage::size() > Size)
          CCopasiMessage::getLastMessage();
      }

      break;

      case InitialExpression:

      {
        size_t Size = CCopasiMessage::size();

        mpCompartment->setInitialExpression(mpData->CharacterData);

        // Remove error messages created by setExpression as this may fail
        // due to incomplete model specification at this time.
        while (CCopasiMessage::size() > Size)
          CCopasiMessage::getLastMessage();
      }

      break;

      case NoiseExpression:

      {
        size_t Size = CCopasiMessage::size();

        mpCompartment->setNoiseExpression(mpData->CharacterData);

        // Remove error messages created by setExpression as this may fail
        // due to incomplete model specification at this time.
        while (CCopasiMessage::size() > Size)
          CCopasiMessage::getLastMessage();
      }

      break;

      default:
        CCopasiMessage(CCopasiMessage::EXCEPTION, MCXML + 2,
                       mpParser->getCurrentLineNumber(), mpParser->getCurrentColumnNumber(), pszName);
        break;
    }

  return finished;
}

// virtual
CXMLHandler::sProcessLogic * CompartmentHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Compartment, HANDLER_COUNT}},
    {"Compartment", Compartment, Compartment, {MiriamAnnotation, Comment, ListOfUnsupportedAnnotations, Expression, InitialExpression, NoiseExpression, AFTER, HANDLER_COUNT}},
    {"MiriamAnnotation", MiriamAnnotation, MiriamAnnotation, {Comment, ListOfUnsupportedAnnotations, Expression, InitialExpression, NoiseExpression, AFTER, HANDLER_COUNT}},
    {"Comment", Comment, Comment, {ListOfUnsupportedAnnotations, Expression, InitialExpression, NoiseExpression, AFTER, HANDLER_COUNT}},
    {"ListOfUnsupportedAnnotations", ListOfUnsupportedAnnotations, ListOfUnsupportedAnnotations, {Expression, InitialExpression, NoiseExpression, AFTER, HANDLER_COUNT}},
    {"Expression", Expression, CharacterData, {InitialExpression, NoiseExpression, AFTER, HANDLER_COUNT}},
    {"InitialExpression", InitialExpression, CharacterData, {NoiseExpression, AFTER, HANDLER_COUNT}},
    {"NoiseExpression", NoiseExpression, CharacterData, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
