// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

#include "MetaboliteHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/model/CModel.h"

/**
 * Replace Metabolite with the name type of the handler and implement the
 * three methods below.
 */
MetaboliteHandler::MetaboliteHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Metabolite),
  mpMetabolite(NULL),
  mKey()
{
  init();
}

// virtual
MetaboliteHandler::~MetaboliteHandler()
{}

// virtual
CXMLHandler * MetaboliteHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;

  CCompartment * pCompartment = NULL;
  const char * Name;
  const char * simulationType;
  CModelEntity::Status SimulationType;
  const char reactions[] = "reactions";
  const char * Compartment;
  bool AddNoise;

  switch (mCurrentElement.first)
    {
      case Metabolite:
        mKey = mpParser->getAttributeValue("key", papszAttrs);
        Name = mpParser->getAttributeValue("name", papszAttrs);

        simulationType = mpParser->getAttributeValue("simulationType", papszAttrs, false);

        // We need to handle old files which used the attribute status.
        if (!simulationType)
          {
            simulationType = mpParser->getAttributeValue("status", papszAttrs, false);

            if (!simulationType) // status and simulationType are both missing
              simulationType = mpParser->getAttributeValue("simulationType", papszAttrs);
            else if (!strcmp(simulationType, "variable")) // reactions was named variable
              simulationType = reactions;
          }

        SimulationType = CModelEntity::XMLStatus.toEnum(simulationType, CModelEntity::Status::REACTIONS);
        Compartment = mpParser->getAttributeValue("compartment", papszAttrs);
        AddNoise = mpParser->toBool(mpParser->getAttributeValue("addNoise", papszAttrs, "false"));

        mpMetabolite = new CMetab();
        addFix(mKey, mpMetabolite);
        mpMetabolite->setObjectName(Name);
        mpMetabolite->setStatus(SimulationType);
        mpMetabolite->setHasNoise(AddNoise);

        pCompartment =
          dynamic_cast< CCompartment* >(mpData->mKeyMap.get(Compartment));

        if (!pCompartment)
          fatalError();

        if (!pCompartment->addMetabolite(mpMetabolite))
          fatalError();

        if (!mpMetabolite->getCompartment())
          fatalError();

        mpData->pModel->getMetabolites().add(mpMetabolite, false);
        break;;

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
bool MetaboliteHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Metabolite:
        finished = true;
        break;

      case MiriamAnnotation:
        mpMetabolite->setMiriamAnnotation(mpData->CharacterData, mpMetabolite->getKey(), mKey);
        mpData->CharacterData = "";
        break;

      case Comment:
        mpMetabolite->setNotes(mpData->CharacterData);
        mpData->CharacterData = "";
        break;

      case ListOfUnsupportedAnnotations:
        mpMetabolite->getUnsupportedAnnotations() = mpData->mUnsupportedAnnotations;
        break;

      case Expression:

      {
        size_t Size = CCopasiMessage::size();

        mpMetabolite->setExpression(mpData->CharacterData);

        // Remove error messages created by setExpression as this may fail
        // due to incomplete model specification at this time.
        while (CCopasiMessage::size() > Size)
          CCopasiMessage::getLastMessage();
      }

      break;

      case InitialExpression:

      {
        size_t Size = CCopasiMessage::size();

        mpMetabolite->setInitialExpression(mpData->CharacterData);

        // Remove error messages created by setExpression as this may fail
        // due to incomplete model specification at this time.
        while (CCopasiMessage::size() > Size)
          CCopasiMessage::getLastMessage();
      }

      break;

      case NoiseExpression:

      {
        size_t Size = CCopasiMessage::size();

        mpMetabolite->setNoiseExpression(mpData->CharacterData);

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
CXMLHandler::sProcessLogic * MetaboliteHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Metabolite, HANDLER_COUNT}},
    {"Metabolite", Metabolite, Metabolite, {MiriamAnnotation, Comment, ListOfUnsupportedAnnotations, Expression, InitialExpression, NoiseExpression, AFTER, HANDLER_COUNT}},
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
