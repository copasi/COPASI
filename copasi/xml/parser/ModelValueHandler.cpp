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

#include "ModelValueHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/model/CModel.h"

/**
 * Replace ModelValue with the name type of the handler and implement the
 * three methods below.
 */
ModelValueHandler::ModelValueHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::ModelValue),
  mpMV(NULL),
  mKey()
{
  init();
}

// virtual
ModelValueHandler::~ModelValueHandler()
{}

// virtual
CXMLHandler * ModelValueHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  const char * Name;
  const char * simulationType;
  CModelEntity::Status SimulationType;
  bool AddNoise;

  switch (mCurrentElement.first)
    {
      case ModelValue:
        mKey = mpParser->getAttributeValue("key", papszAttrs);
        Name = mpParser->getAttributeValue("name", papszAttrs);
        simulationType = mpParser->getAttributeValue("simulationType", papszAttrs, false);

        // We need to handle old files which used the attribute status.
        if (!simulationType)
          {
            simulationType = mpParser->getAttributeValue("status", papszAttrs, false);

            if (!simulationType) // status and simulationType are both missing
              simulationType = mpParser->getAttributeValue("simulationType", papszAttrs);
          }

        SimulationType = CModelEntity::XMLStatus.toEnum(simulationType, CModelEntity::Status::FIXED);
        AddNoise = mpParser->toBool(mpParser->getAttributeValue("addNoise", papszAttrs, "false"));

        mpMV = new CModelValue();
        addFix(mKey, mpMV);
        mpMV->setObjectName(Name);
        mpMV->setStatus(SimulationType);
        mpMV->setHasNoise(AddNoise);

        mpData->pModel->getModelValues().add(mpMV, true);
        break;

      case MiriamAnnotation:
      case Comment:
      case Expression:
      case MathML:
      case InitialExpression:
      case NoiseExpression:
      case Unit:
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
bool ModelValueHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case ModelValue:
        finished = true;
        break;

      case MiriamAnnotation:
        mpMV->setMiriamAnnotation(mpData->CharacterData, mpMV->getKey(), mKey);
        mpData->CharacterData = "";
        break;

      case Comment:
        mpMV->setNotes(mpData->CharacterData);
        mpData->CharacterData = "";
        break;

      case ListOfUnsupportedAnnotations:
        mpMV->getUnsupportedAnnotations() = mpData->mUnsupportedAnnotations;
        break;

      case Expression:
      case MathML:
      {
        size_t Size = CCopasiMessage::size();

        mpMV->setExpression(mpData->CharacterData);

        // Remove error messages created by setExpression as this may fail
        // due to incomplete model specification at this time.

        while (CCopasiMessage::size() > Size)
          CCopasiMessage::getLastMessage();
      }

      break;

      case InitialExpression:

      {
        size_t Size = CCopasiMessage::size();

        mpMV->setInitialExpression(mpData->CharacterData);

        // Remove error messages created by setExpression as this may fail
        // due to incomplete model specification at this time.
        while (CCopasiMessage::size() > Size)
          CCopasiMessage::getLastMessage();
      }

      break;

      case NoiseExpression:

      {
        size_t Size = CCopasiMessage::size();

        mpMV->setNoiseExpression(mpData->CharacterData);

        // Remove error messages created by setExpression as this may fail
        // due to incomplete model specification at this time.
        while (CCopasiMessage::size() > Size)
          CCopasiMessage::getLastMessage();
      }

      break;

      case Unit:

      {
        size_t Size = CCopasiMessage::size();

        mpMV->setUnitExpression(mpData->CharacterData);

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
CXMLHandler::sProcessLogic * ModelValueHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {ModelValue, HANDLER_COUNT}},
    {"ModelValue", ModelValue, ModelValue, {MiriamAnnotation, Comment, ListOfUnsupportedAnnotations, Expression, MathML, InitialExpression, NoiseExpression, Unit, AFTER, HANDLER_COUNT}},
    {"MiriamAnnotation", MiriamAnnotation, MiriamAnnotation, {Comment, ListOfUnsupportedAnnotations, Expression, MathML, InitialExpression, NoiseExpression, Unit, AFTER, HANDLER_COUNT}},
    {"Comment", Comment, Comment, {ListOfUnsupportedAnnotations, Expression, MathML, InitialExpression, NoiseExpression, Unit, AFTER, HANDLER_COUNT}},
    {"ListOfUnsupportedAnnotations", ListOfUnsupportedAnnotations, ListOfUnsupportedAnnotations, {Expression, MathML, InitialExpression, NoiseExpression, Unit, AFTER, HANDLER_COUNT}},
    {"Expression", Expression, CharacterData, {InitialExpression, NoiseExpression, Unit, AFTER, HANDLER_COUNT}},
    {"MathML", MathML, MathML, {InitialExpression, NoiseExpression, Unit, AFTER, HANDLER_COUNT}},
    {"InitialExpression", InitialExpression, CharacterData, {NoiseExpression, Unit, AFTER, HANDLER_COUNT}},
    {"NoiseExpression", NoiseExpression, CharacterData, {Unit, AFTER, HANDLER_COUNT}},
    {"Unit", Unit, CharacterData, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
