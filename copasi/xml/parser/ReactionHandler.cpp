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

#include "ReactionHandler.h"
#include "CXMLParser.h"
#include "copasi/utilities/CCopasiMessage.h"

#include "copasi/model/CModel.h"

/**
 * Replace Reaction with the name type of the handler and implement the
 * three methods below.
 */
ReactionHandler::ReactionHandler(CXMLParser & parser, CXMLParserData & data):
  CXMLHandler(parser, data, CXMLHandler::Reaction),
  mKey()
{
  init();
}

// virtual
ReactionHandler::~ReactionHandler()
{}

// virtual
CXMLHandler * ReactionHandler::processStart(const XML_Char * pszName,
    const XML_Char ** papszAttrs)
{
  CXMLHandler * pHandlerToCall = NULL;
  CCompartment * pCompartment;
  const char * Name;
  const char * Compartment; // Default Compartment_00
  const char * reversible;
  bool Reversible;
  const char * fast;
  bool Fast;
  const char * SBMLId;
  bool AddNoise;

  switch (mCurrentElement.first)
    {
      case Reaction:
        mKey = mpParser->getAttributeValue("key", papszAttrs);
        Name = mpParser->getAttributeValue("name", papszAttrs);
        Compartment = mpParser->getAttributeValue("compartment", papszAttrs, "Compartment_00");

        reversible = mpParser->getAttributeValue("reversible", papszAttrs);
        Reversible = mpParser->toBool(reversible);

        fast = mpParser->getAttributeValue("fast", papszAttrs, "false");
        Fast = mpParser->toBool(fast);

        AddNoise = mpParser->toBool(mpParser->getAttributeValue("addNoise", papszAttrs, "false"));

        mpData->pReaction = new CReaction();
        addFix(mKey, mpData->pReaction);
        mpData->pReaction->setObjectName(Name);
        mpData->pReaction->setReversible(Reversible);
        mpData->pReaction->setFast(Fast);
        mpData->pReaction->setHasNoise(AddNoise);

        SBMLId = mpParser->getAttributeValue("sbmlid", papszAttrs, "");

        if (std::string(SBMLId) != std::string(""))
          {
            mpData->pReaction->setSBMLId(SBMLId);
          }

        if (strcmp(Compartment, "Compartment_00")) //TODO necessary?
          {
            pCompartment =
              dynamic_cast< CCompartment* >(mpData->mKeyMap.get(Compartment));

            if (!pCompartment) fatalError();
          }

        mpData->pModel->getReactions().add(mpData->pReaction, true);
        break;

      case MiriamAnnotation:
      case Comment:
      case ListOfSubstrates:
      case ListOfProducts:
      case ListOfModifiers:
      case ListOfConstants:
      case KineticLaw:
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
bool ReactionHandler::processEnd(const XML_Char * pszName)
{
  bool finished = false;

  switch (mCurrentElement.first)
    {
      case Reaction:
        finished = true;
        break;

      case MiriamAnnotation:
        mpData->pReaction->setMiriamAnnotation(mpData->CharacterData, mpData->pReaction->getKey(), mKey);
        mpData->CharacterData = "";
        break;

      case Comment:
        mpData->pReaction->setNotes(mpData->CharacterData);
        mpData->CharacterData = "";
        break;

      case ListOfUnsupportedAnnotations:
        mpData->pReaction->getUnsupportedAnnotations() = mpData->mUnsupportedAnnotations;
        break;

      case ListOfSubstrates:
      case ListOfProducts:
      case ListOfModifiers:
      case ListOfConstants:
      case KineticLaw:
        break;

      case NoiseExpression:

      {
        size_t Size = CCopasiMessage::size();

        mpData->pReaction->setNoiseExpression(mpData->CharacterData);

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
CXMLHandler::sProcessLogic * ReactionHandler::getProcessLogic() const
{
  static sProcessLogic Elements[] =
  {
    {"BEFORE", BEFORE, BEFORE, {Reaction, HANDLER_COUNT}},
    {"Reaction", Reaction, Reaction, {MiriamAnnotation, Comment, ListOfUnsupportedAnnotations, ListOfSubstrates, ListOfProducts, ListOfModifiers, ListOfConstants, KineticLaw, NoiseExpression, AFTER, HANDLER_COUNT}},
    {"MiriamAnnotation", MiriamAnnotation, MiriamAnnotation, {Comment, ListOfUnsupportedAnnotations, ListOfSubstrates, ListOfProducts, ListOfModifiers, ListOfConstants, KineticLaw, NoiseExpression, AFTER, HANDLER_COUNT}},
    {"Comment", Comment, Comment, {ListOfUnsupportedAnnotations, ListOfSubstrates, ListOfProducts, ListOfModifiers, ListOfConstants, KineticLaw, NoiseExpression, AFTER, HANDLER_COUNT}},
    {"ListOfUnsupportedAnnotations", ListOfUnsupportedAnnotations, ListOfUnsupportedAnnotations, {ListOfSubstrates, ListOfProducts, ListOfModifiers, ListOfConstants, KineticLaw, NoiseExpression, AFTER, HANDLER_COUNT}},
    {"ListOfSubstrates", ListOfSubstrates, ListOfSubstrates, {ListOfProducts, ListOfModifiers, ListOfConstants, KineticLaw, NoiseExpression, AFTER, HANDLER_COUNT}},
    {"ListOfProducts", ListOfProducts, ListOfProducts, {ListOfModifiers, ListOfConstants, KineticLaw, NoiseExpression, AFTER, HANDLER_COUNT}},
    {"ListOfModifiers", ListOfModifiers, ListOfModifiers, {ListOfConstants, KineticLaw, NoiseExpression, AFTER, HANDLER_COUNT}},
    {"ListOfConstants", ListOfConstants, ListOfConstants, {KineticLaw, NoiseExpression, AFTER, HANDLER_COUNT}},
    {"KineticLaw", KineticLaw, KineticLaw, {NoiseExpression, AFTER, HANDLER_COUNT}},
    {"NoiseExpression", NoiseExpression, CharacterData, {AFTER, HANDLER_COUNT}},
    {"AFTER", AFTER, AFTER, {HANDLER_COUNT}}
  };

  return Elements;
}
